#include "stdafx.h"
#include <sstream>

#include "../../common/length.h"

#include "db.h"

#include "config.h"
#include "desc_client.h"
#include "desc_manager.h"
#include "char.h"
#include "char_manager.h"
#include "item.h"
#include "item_manager.h"
#include "p2p.h"
#include "log.h"
#include "login_data.h"
#include "locale_service.h"
#include "pcbang.h"
#include "spam.h"
#include "auth_brazil.h"

extern std::string g_stBlockDate;

DBManager::DBManager() : m_bIsConnect(false)
{
}

DBManager::~DBManager()
{
}

bool DBManager::Connect(const char* host, const int port, const char* user, const char* pwd, const char* db)
{
	if (m_sql.Setup(host, user, pwd, db, g_stLocale.c_str(), false, port))
		m_bIsConnect = true;

	if (!m_sql_direct.Setup(host, user, pwd, db, g_stLocale.c_str(), true, port))
		sys_err("cannot open direct sql connection to host %s", host);

	if (m_bIsConnect && !g_bAuthServer)
	{
		LoadDBString();
	}

	return m_bIsConnect;
}

void DBManager::Query(const char* c_pszFormat, ...)
{
	char szQuery[4096];
	va_list args;

	va_start(args, c_pszFormat);
	vsnprintf(szQuery, sizeof(szQuery), c_pszFormat, args);
	va_end(args);

	m_sql.AsyncQuery(szQuery);
}

SQLMsg* DBManager::DirectQuery(const char* c_pszFormat, ...)
{
	char szQuery[4096];
	va_list args;

	va_start(args, c_pszFormat);
	vsnprintf(szQuery, sizeof(szQuery), c_pszFormat, args);
	va_end(args);

	return m_sql_direct.DirectQuery(szQuery);
}

bool DBManager::IsConnected()
{
	return m_bIsConnect;
}

void DBManager::ReturnQuery(int iType, DWORD dwIdent, void* pvData, const char* c_pszFormat, ...)
{
	//sys_log(0, "ReturnQuery %s", c_pszQuery);
	char szQuery[4096];
	va_list args;

	va_start(args, c_pszFormat);
	vsnprintf(szQuery, sizeof(szQuery), c_pszFormat, args);
	va_end(args);

	CReturnQueryInfo* p = M2_NEW CReturnQueryInfo;

	p->iQueryType = QUERY_TYPE_RETURN;
	p->iType = iType;
	p->dwIdent = dwIdent;
	p->pvData = pvData;

	m_sql.ReturnQuery(szQuery, p);
}

SQLMsg* DBManager::PopResult()
{
	SQLMsg* p;

	if (m_sql.PopResult(&p))
		return p;

	return NULL;
}

void DBManager::Process()
{
	SQLMsg* pMsg = NULL;

	while ((pMsg = PopResult()))
	{
		if (NULL != pMsg->pvUserData)
		{
			switch (reinterpret_cast<CQueryInfo*>(pMsg->pvUserData)->iQueryType)
			{
				case QUERY_TYPE_RETURN:
					AnalyzeReturnQuery(pMsg);
					break;

				case QUERY_TYPE_FUNCTION:
				{
					CFuncQueryInfo* qi = reinterpret_cast<CFuncQueryInfo*>(pMsg->pvUserData);
					qi->f(pMsg);
					M2_DELETE(qi);
				}
				break;

				case QUERY_TYPE_AFTER_FUNCTION:
				{
					CFuncAfterQueryInfo* qi = reinterpret_cast<CFuncAfterQueryInfo*>(pMsg->pvUserData);
					qi->f();
					M2_DELETE(qi);
				}
				break;
			}
		}

		delete pMsg;
	}
}

CLoginData* DBManager::GetLoginData(DWORD dwKey)
{
	std::map<DWORD, CLoginData*>::iterator it = m_map_pkLoginData.find(dwKey);

	if (it == m_map_pkLoginData.end())
		return NULL;

	return it->second;
}

void DBManager::InsertLoginData(CLoginData* pkLD)
{
	m_map_pkLoginData.insert(std::make_pair(pkLD->GetKey(), pkLD));
}

void DBManager::DeleteLoginData(CLoginData* pkLD)
{
	std::map<DWORD, CLoginData*>::iterator it = m_map_pkLoginData.find(pkLD->GetKey());

	if (it == m_map_pkLoginData.end())
		return;

	sys_log(0, "DeleteLoginData %s %p", pkLD->GetLogin(), pkLD);

	M2_DELETE(it->second);
	m_map_pkLoginData.erase(it);
}

void DBManager::SendLoginPing(const char* c_pszLogin)
{
	TPacketGGLoginPing ptog;

	ptog.bHeader = HEADER_GG_LOGIN_PING;
	strlcpy(ptog.szLogin, c_pszLogin, sizeof(ptog.szLogin));

	if (!g_pkAuthMasterDesc) // If I am master, broadcast to others
	{
		P2P_MANAGER::instance().Send(&ptog, sizeof(TPacketGGLoginPing));
	}
	else // If I am slave send login ping to master
	{
		g_pkAuthMasterDesc->Packet(&ptog, sizeof(TPacketGGLoginPing));
	}
}

void DBManager::SendAuthLogin(LPDESC d)
{
	const TAccountTable& r = d->GetAccountTable();

	CLoginData* pkLD = GetLoginData(d->GetLoginKey());

	if (!pkLD)
		return;

	TPacketGDAuthLogin ptod;
	ptod.dwID = r.id;

	trim_and_lower(r.login, ptod.szLogin, sizeof(ptod.szLogin));
	strlcpy(ptod.szSocialID, r.social_id, sizeof(ptod.szSocialID));
	ptod.dwLoginKey = d->GetLoginKey();

	thecore_memcpy(ptod.iPremiumTimes, pkLD->GetPremiumPtr(), sizeof(ptod.iPremiumTimes));
	thecore_memcpy(&ptod.adwClientKey, pkLD->GetClientKey(), sizeof(DWORD) * 4);

#if defined(__MULTI_LANGUAGE_SYSTEM__)
	strlcpy(ptod.szCountry, r.country, sizeof(ptod.szCountry));
#endif

	db_clientdesc->DBPacket(HEADER_GD_AUTH_LOGIN, d->GetHandle(), &ptod, sizeof(TPacketGDAuthLogin));
	sys_log(0, "SendAuthLogin %s key %u", ptod.szLogin, ptod.dwID);

	SendLoginPing(r.login);
}

void DBManager::LoginPrepare(long lRemainSecs, LPDESC d, DWORD* pdwClientKey, int* paiPremiumTimes)
{
	const TAccountTable& r = d->GetAccountTable();

	CLoginData* pkLD = M2_NEW CLoginData;

	pkLD->SetKey(d->GetLoginKey());
	pkLD->SetLogin(r.login);
	pkLD->SetRemainSecs(lRemainSecs);
	pkLD->SetIP(d->GetHostName());
	pkLD->SetClientKey(pdwClientKey);

	if (paiPremiumTimes)
		pkLD->SetPremium(paiPremiumTimes);

	InsertLoginData(pkLD);

	SendAuthLogin(d);
}

void DBManager::AnalyzeReturnQuery(SQLMsg* pMsg)
{
	CReturnQueryInfo* qi = (CReturnQueryInfo*)pMsg->pvUserData;

	switch (qi->iType)
	{
		case QID_AUTH_LOGIN:
		{
			TPacketCGLogin3* pinfo = (TPacketCGLogin3*)qi->pvData;
			LPDESC d = DESC_MANAGER::instance().FindByLoginKey(qi->dwIdent);

			if (!d)
			{
				M2_DELETE(pinfo);
				break;
			}

			// 위치 변경 - By SeMinZ
			d->SetLogin(pinfo->login);

			sys_log(0, "QID_AUTH_LOGIN: START %u %p", qi->dwIdent, get_pointer(d));

			if (pMsg->Get()->uiNumRows == 0)
			{
				if (true == LC_IsBrazil())
				{
					// 계정이 없으면 새로 만들어야 한다
					ReturnQuery(QID_BRAZIL_CREATE_ID, qi->dwIdent, pinfo,
						"INSERT INTO account(login, password, social_id, create_time) "
						"VALUES('%s', password('%s'), '0000000', NOW()) ;",
						pinfo->login, pinfo->passwd);

					sys_log(0, "[AUTH_BRAZIL] : Create A new AccountID From OnGame");
				}
				else
				{
					sys_log(0, "   NOID");
					LoginFailure(d, "NOID");
					M2_DELETE(pinfo);
				}
			}
			else
			{
				MYSQL_ROW row = mysql_fetch_row(pMsg->Get()->pSQLResult);
				int col = 0;

				// PASSWORD('%s'), password, securitycode, social_id, id, status
				char szEncrytPassword[45 + 1];
				char szPassword[45 + 1];
				char szSocialID[SOCIAL_ID_MAX_LEN + 1];
				char szStatus[ACCOUNT_STATUS_MAX_LEN + 1];
				DWORD dwID = 0;

				if (!row[col])
				{
					sys_err("error column %d", col);
					M2_DELETE(pinfo);
					break;
				}
				strlcpy(szEncrytPassword, row[col++], sizeof(szEncrytPassword));

				if (!row[col])
				{
					sys_err("error column %d", col);
					M2_DELETE(pinfo);
					break;
				}
				strlcpy(szPassword, row[col++], sizeof(szPassword));

				if (!row[col])
				{
					sys_err("error column %d", col);
					M2_DELETE(pinfo);
					break;
				}
				strlcpy(szSocialID, row[col++], sizeof(szSocialID));

				if (!row[col])
				{
					sys_err("error column %d", col);
					M2_DELETE(pinfo);
					break;
				}
				str_to_number(dwID, row[col++]);

				if (!row[col])
				{
					sys_err("error column %d", col);
					M2_DELETE(pinfo);
					break;
				}
				strlcpy(szStatus, row[col++], sizeof(szStatus));

				BYTE bNotAvail = 0;
				str_to_number(bNotAvail, row[col++]);

				int aiPremiumTimes[PREMIUM_MAX_NUM];
				memset(&aiPremiumTimes, 0, sizeof(aiPremiumTimes));

				char szCreateDate[256] = "00000000";

				if (!g_iUseLocale)
				{
					str_to_number(aiPremiumTimes[PREMIUM_EXP], row[col++]);
					str_to_number(aiPremiumTimes[PREMIUM_ITEM], row[col++]);
					str_to_number(aiPremiumTimes[PREMIUM_SAFEBOX], row[col++]);
					str_to_number(aiPremiumTimes[PREMIUM_AUTOLOOT], row[col++]);
					str_to_number(aiPremiumTimes[PREMIUM_FISH_MIND], row[col++]);
					str_to_number(aiPremiumTimes[PREMIUM_MARRIAGE_FAST], row[col++]);
					str_to_number(aiPremiumTimes[PREMIUM_GOLD], row[col++]);
#if defined(__CONQUEROR_LEVEL__)
					str_to_number(aiPremiumTimes[PREMIUM_SUNGMA], row[col++]);
#endif
				}
				else
				{
					str_to_number(aiPremiumTimes[PREMIUM_EXP], row[col++]);
					str_to_number(aiPremiumTimes[PREMIUM_ITEM], row[col++]);
					str_to_number(aiPremiumTimes[PREMIUM_SAFEBOX], row[col++]);
					str_to_number(aiPremiumTimes[PREMIUM_AUTOLOOT], row[col++]);
					str_to_number(aiPremiumTimes[PREMIUM_FISH_MIND], row[col++]);
					str_to_number(aiPremiumTimes[PREMIUM_MARRIAGE_FAST], row[col++]);
					str_to_number(aiPremiumTimes[PREMIUM_GOLD], row[col++]);
#if defined(__CONQUEROR_LEVEL__)
					str_to_number(aiPremiumTimes[PREMIUM_SUNGMA], row[col++]);
#endif

					if (LC_IsEurope() || test_server)
					{
						long retValue = 0;
						str_to_number(retValue, row[col]);

						time_t create_time = retValue;
						struct tm* tm1;
						tm1 = localtime(&create_time);
						strftime(szCreateDate, 255, "%Y%m%d", tm1);

						sys_log(0, "Create_Time %d %s", retValue, szCreateDate);
						sys_log(0, "Block Time %d ", strncmp(szCreateDate, g_stBlockDate.c_str(), 8));
					}
				}

				int nPasswordDiff = strcmp(szEncrytPassword, szPassword);

				if (true == LC_IsBrazil())
				{
					nPasswordDiff = 0; // 브라질 버전에서는 비밀번호 체크를 하지 않는다.
				}

				if (nPasswordDiff)
				{
					LoginFailure(d, "WRONGPWD");
					sys_log(0, "   WRONGPWD");
					M2_DELETE(pinfo);
				}
				else if (bNotAvail)
				{
					LoginFailure(d, "NOTAVAIL");
					sys_log(0, "   NOTAVAIL");
					M2_DELETE(pinfo);
				}
				else if (DESC_MANAGER::instance().FindByLoginName(pinfo->login))
				{
					LoginFailure(d, "ALREADY");
					sys_log(0, "   ALREADY");
					M2_DELETE(pinfo);
				}
				else if (strcmp(szStatus, "OK"))
				{
					LoginFailure(d, szStatus);
					sys_log(0, "   STATUS: %s", szStatus);
					M2_DELETE(pinfo);
				}
#if defined(__MULTI_LANGUAGE_SYSTEM__)
				else if (!LocaleService_GetLocale(pinfo->country))
				{
					LoginFailure(d, "COUNTRYERR");
					sys_log(0, "   COUNTRYERR");
					M2_DELETE(pinfo);
				}
#endif
				else
				{
					if (LC_IsEurope())
					{
						// stBlockData >= 0 == 날짜가 BlockDate 보다 미래
						if (strncmp(szCreateDate, g_stBlockDate.c_str(), 8) >= 0)
						{
							LoginFailure(d, "BLKLOGIN");
							sys_log(0, "   BLKLOGIN");
							M2_DELETE(pinfo);
							break;
						}

						char szQuery[1024];
#if defined(__MULTI_LANGUAGE_SYSTEM__)
						snprintf(szQuery, sizeof(szQuery), "UPDATE `account` SET `last_play` = NOW(), `country` = '%s' WHERE `id` = %u",
							LocaleService_GetCountry(pinfo->country), dwID);
#else
						snprintf(szQuery, sizeof(szQuery), "UPDATE `account` SET `last_play` = NOW() WHERE `id` = %u", dwID);
#endif
						std::unique_ptr<SQLMsg> msg(DBManager::instance().DirectQuery(szQuery));
					}

					TAccountTable& r = d->GetAccountTable();

					r.id = dwID;
					trim_and_lower(pinfo->login, r.login, sizeof(r.login));
					strlcpy(r.passwd, pinfo->passwd, sizeof(r.passwd));
					strlcpy(r.social_id, szSocialID, sizeof(r.social_id));
#if defined(__MULTI_LANGUAGE_SYSTEM__)
					strlcpy(r.country, pinfo->country, sizeof(r.country));
#endif

					DESC_MANAGER::instance().ConnectAccount(r.login, d);

					{
						LoginPrepare(0, d, pinfo->adwClientKey, aiPremiumTimes);
						// By SeMinZ
						M2_DELETE(pinfo);
						break;
					}

					sys_log(0, "QID_AUTH_LOGIN: SUCCESS %s", pinfo->login);
				}
			}
		}
		break;

		case QID_SAFEBOX_SIZE:
		{
			LPCHARACTER ch = CHARACTER_MANAGER::instance().FindByPID(qi->dwIdent);

			if (ch)
			{
				if (pMsg->Get()->uiNumRows > 0)
				{
					MYSQL_ROW row = mysql_fetch_row(pMsg->Get()->pSQLResult);
					int size = 0;
					str_to_number(size, row[0]);
					ch->SetSafeboxSize(SAFEBOX_PAGE_SIZE * size);
				}
			}
		}
		break;

		case QID_DB_STRING:
		{
			m_map_dbstring.clear();
			m_vec_GreetMessage.clear();

			for (uint i = 0; i < pMsg->Get()->uiNumRows; ++i)
			{
				MYSQL_ROW row = mysql_fetch_row(pMsg->Get()->pSQLResult);
				//ch->SetSafeboxSize(SAFEBOX_PAGE_SIZE * atoi(row[0]));
				if (row[0] && row[1])
				{
					m_map_dbstring.insert(make_pair(std::string(row[0]), std::string(row[1])));
					sys_log(0, "DBSTR '%s' '%s'", row[0], row[1]);
				}
			}
			if (m_map_dbstring.find("GREET") != m_map_dbstring.end())
			{
				std::istringstream is(m_map_dbstring["GREET"]);
				while (!is.eof())
				{
					std::string str;
					getline(is, str);
					m_vec_GreetMessage.push_back(str);
				}
			}
		}
		break;

		case QID_LOTTO:
		{
			LPCHARACTER ch = CHARACTER_MANAGER::instance().FindByPID(qi->dwIdent);
			DWORD* pdw = (DWORD*)qi->pvData;

			if (ch)
			{
				if (pMsg->Get()->uiAffectedRows == 0 || pMsg->Get()->uiAffectedRows == (uint32_t)-1)
				{
					sys_log(0, "GIVE LOTTO FAIL TO pid %u", ch->GetPlayerID());
				}
				else
				{
					LPITEM pkItem = ch->AutoGiveItem(pdw[0], pdw[1]);

					if (pkItem)
					{
						sys_log(0, "GIVE LOTTO SUCCESS TO %s (pid %u)", ch->GetName(), qi->dwIdent);
						//ch->ChatPacket(CHAT_TYPE_INFO, LC_STRING("아이템 획득: %s", LC_ITEM(pkItem->GetVnum())));

						pkItem->SetSocket(0, pMsg->Get()->uiInsertID);
						pkItem->SetSocket(1, pdw[2]);
					}
					else
						sys_log(0, "GIVE LOTTO FAIL2 TO pid %u", ch->GetPlayerID());
				}
			}

			M2_DELETE_ARRAY(pdw);
		}
		break;

		case QID_HIGHSCORE_REGISTER:
		{
			THighscoreRegisterQueryInfo* info = (THighscoreRegisterQueryInfo*)qi->pvData;
			bool bQuery = true;

			if (pMsg->Get()->uiNumRows)
			{
				MYSQL_ROW row = mysql_fetch_row(pMsg->Get()->pSQLResult);

				if (row && row[0])
				{
					int iCur = 0;
					str_to_number(iCur, row[0]);

					if ((info->bOrder && iCur >= info->iValue) ||
						(!info->bOrder && iCur <= info->iValue))
						bQuery = false;
				}
			}

			if (bQuery)
				Query("REPLACE INTO highscore%s VALUES('%s', %u, %d)",
					get_table_postfix(), info->szBoard, info->dwPID, info->iValue);

			M2_DELETE(info);
		}
		break;

		case QID_HIGHSCORE_SHOW:
		{
		}
		break;

		// BLOCK_CHAT
		case QID_BLOCK_CHAT_LIST:
		{
			LPCHARACTER ch = CHARACTER_MANAGER::instance().FindByPID(qi->dwIdent);

			if (ch == NULL)
				break;
			if (pMsg->Get()->uiNumRows)
			{
				MYSQL_ROW row;
				while ((row = mysql_fetch_row(pMsg->Get()->pSQLResult)))
				{
					ch->ChatPacket(CHAT_TYPE_INFO, "%s %s sec", row[0], row[1]);
				}
			}
			else
			{
				ch->ChatPacket(CHAT_TYPE_INFO, "No one currently blocked.");
			}
		}
		break;
		// END_OF_BLOCK_CHAT

		// PCBANG_IP_LIST
		case QID_PCBANG_IP_LIST_CHECK:
		{
			const std::string PCBANG_IP_TABLE_NAME("pcbang_ip");

			if (pMsg->Get()->uiNumRows > 0)
			{
				MYSQL_ROW row;
				bool isFinded = false;

				while ((row = mysql_fetch_row(pMsg->Get()->pSQLResult)))
				{
					const char* c_szName = row[0];
					const char* c_szUpdateTime = row[12];

					if (test_server)
						sys_log(0, "%s:%s", c_szName, c_szUpdateTime);

					if (PCBANG_IP_TABLE_NAME == c_szName)
					{
						isFinded = true;

						static std::string s_stLastTime;
						if (s_stLastTime != c_szUpdateTime)
						{
							s_stLastTime = c_szUpdateTime;
							sys_log(0, "'%s' mysql table is UPDATED(%s)", PCBANG_IP_TABLE_NAME.c_str(), c_szUpdateTime);
							ReturnQuery(QID_PCBANG_IP_LIST_SELECT, 0, NULL, "SELECT pcbang_id, ip FROM %s;", PCBANG_IP_TABLE_NAME.c_str());
						}
						else
						{
							sys_log(0, "'%s' mysql table is NOT updated(%s)", PCBANG_IP_TABLE_NAME.c_str(), c_szUpdateTime);
						}
						break;
					}
				}

				if (!isFinded)
				{
					sys_err(0, "'%s' mysql table CANNOT FIND", PCBANG_IP_TABLE_NAME.c_str());
				}
			}
			else if (test_server)
			{
				sys_err(0, "'%s' mysql table is NOT EXIST", PCBANG_IP_TABLE_NAME.c_str());
			}
		}
		break;

		case QID_PCBANG_IP_LIST_SELECT:
		{
			if (pMsg->Get()->uiNumRows > 0)
			{
				MYSQL_ROW row;

				while ((row = mysql_fetch_row(pMsg->Get()->pSQLResult)))
				{
					CPCBangManager::instance().InsertIP(row[0], row[1]);
				}
			}
			else if (test_server)
			{
				sys_log(0, "PCBANG_IP_LIST is EMPTY");
			}
		}
		break;

		// END_OF_PCBANG_IP_LIST

		case QID_BRAZIL_CREATE_ID:
		{
			TPacketCGLogin3* pinfo = (TPacketCGLogin3*)qi->pvData;

			if (pMsg->Get()->uiAffectedRows == 0 || pMsg->Get()->uiAffectedRows == (uint32_t)-1)
			{
				LPDESC d = DESC_MANAGER::instance().FindByLoginKey(qi->dwIdent);
				sys_log(0, "[AUTH_BRAZIL]   NOID");
				sys_log(0, "[AUTH_BRAZIL] : Failed to create a new account %s", pinfo->login);
				LoginFailure(d, "NOID");
				M2_DELETE(pinfo);
			}
			else
			{
				sys_log(0, "[AUTH_BRAZIL] : Succeed to create a new account %s", pinfo->login);

				ReturnQuery(QID_AUTH_LOGIN, qi->dwIdent, pinfo,
					"SELECT CONCAT('*', UPPER(SHA1(UNHEX(SHA1('%s'))))), `password`, `securitycode`, `social_id`, `id`, `status`"
					", `availDt` - NOW() > 0"
					", UNIX_TIMESTAMP(`silver_expire`)"
					", UNIX_TIMESTAMP(`gold_expire`)"
					", UNIX_TIMESTAMP(`safebox_expire`)"
					", UNIX_TIMESTAMP(`autoloot_expire`)"
					", UNIX_TIMESTAMP(`fish_mind_expire`)"
					", UNIX_TIMESTAMP(`marriage_fast_expire`)"
					", UNIX_TIMESTAMP(`money_drop_rate_expire`)"
#if defined(__CONQUEROR_LEVEL__)
					", UNIX_TIMESTAMP(`sungma_expire`)"
#endif
					", UNIX_TIMESTAMP(`create_time`)"
					" FROM account WHERE `login` = '%s'",
					pinfo->passwd, pinfo->login);
			}
		}
		break;

		default:
			sys_err("FATAL ERROR!!! Unhandled return query id %d", qi->iType);
			break;
	}

	M2_DELETE(qi);
}

void DBManager::LoadDBString()
{
	ReturnQuery(QID_DB_STRING, 0, NULL, "SELECT `name`, `text` FROM `string%s`", get_table_postfix());
}

const std::string& DBManager::GetDBString(const std::string& key)
{
	static std::string null_str = "";
	auto it = m_map_dbstring.find(key);
	if (it == m_map_dbstring.end())
		return null_str;
	return it->second;
}

const std::vector<std::string>& DBManager::GetGreetMessage()
{
	return m_vec_GreetMessage;
}

void DBManager::SendMoneyLog(BYTE type, DWORD vnum, int gold
#if defined(__CHEQUE_SYSTEM__)
	, int cheque
#endif
)
{
	if (!gold)
		return;

	TPacketMoneyLog p;
	p.type = type;
	p.vnum = vnum;
	p.gold = gold;
#if defined(__CHEQUE_SYSTEM__)
	p.cheque = cheque;
#endif
	db_clientdesc->DBPacket(HEADER_GD_MONEY_LOG, 0, &p, sizeof(p));
}

void DBManager::RequestBlockException(const char* login, int cmd)
{
	TPacketBlockException packet;

	packet.cmd = cmd;
	strlcpy(packet.login, login, sizeof(packet.login));
	db_clientdesc->DBPacket(HEADER_GD_BLOCK_EXCEPTION, 0, &packet, sizeof(packet));
}

size_t DBManager::EscapeString(char* dst, size_t dstSize, const char* src, size_t srcSize)
{
	return m_sql_direct.EscapeString(dst, dstSize, src, srcSize);
}

//
// Common SQL
//
AccountDB::AccountDB() :
	m_IsConnect(false)
{
}

bool AccountDB::IsConnected()
{
	return m_IsConnect;
}

bool AccountDB::Connect(const char* host, const int port, const char* user, const char* pwd, const char* db)
{
	m_IsConnect = m_sql_direct.Setup(host, user, pwd, db, "", true, port);

	if (false == m_IsConnect)
	{
		fprintf(stderr, "cannot open direct sql connection to host: %s user: %s db: %s\n", host, user, db);
		return false;
	}

	return m_IsConnect;
}

bool AccountDB::ConnectAsync(const char* host, const int port, const char* user, const char* pwd, const char* db, const char* locale)
{
	m_sql.Setup(host, user, pwd, db, locale, false, port);
	return true;
}

void AccountDB::SetLocale(const std::string& stLocale)
{
	m_sql_direct.SetLocale(stLocale);
	m_sql_direct.QueryLocaleSet();
}

SQLMsg* AccountDB::DirectQuery(const char* query)
{
	return m_sql_direct.DirectQuery(query);
}

void AccountDB::AsyncQuery(const char* query)
{
	m_sql.AsyncQuery(query);
}

void AccountDB::ReturnQuery(int iType, DWORD dwIdent, void* pvData, const char* c_pszFormat, ...)
{
	char szQuery[4096];
	va_list args;

	va_start(args, c_pszFormat);
	vsnprintf(szQuery, sizeof(szQuery), c_pszFormat, args);
	va_end(args);

	CReturnQueryInfo* p = M2_NEW CReturnQueryInfo;

	p->iQueryType = QUERY_TYPE_RETURN;
	p->iType = iType;
	p->dwIdent = dwIdent;
	p->pvData = pvData;

	m_sql.ReturnQuery(szQuery, p);
}

SQLMsg* AccountDB::PopResult()
{
	SQLMsg* p;

	if (m_sql.PopResult(&p))
		return p;

	return NULL;
}

void AccountDB::Process()
{
	SQLMsg* pMsg = NULL;

	while ((pMsg = PopResult()))
	{
		CQueryInfo* qi = (CQueryInfo*)pMsg->pvUserData;

		switch (qi->iQueryType)
		{
			case QUERY_TYPE_RETURN:
				AnalyzeReturnQuery(pMsg);
				break;
		}
	}

	delete pMsg;
}

extern unsigned int g_uiSpamReloadCycle;

enum EAccountQID
{
	QID_SPAM_DB,
};

// 10분마다 리로드
static LPEVENT s_pkReloadSpamEvent = NULL;

EVENTINFO(reload_spam_event_info)
{
	// used to send command
	DWORD empty;
};

EVENTFUNC(reload_spam_event)
{
	AccountDB::instance().ReturnQuery(QID_SPAM_DB, 0, NULL, "SELECT word, score FROM spam_db WHERE type='SPAM'");
	return PASSES_PER_SEC(g_uiSpamReloadCycle);
}

void LoadSpamDB()
{
	AccountDB::instance().ReturnQuery(QID_SPAM_DB, 0, NULL, "SELECT word, score FROM spam_db WHERE type='SPAM'");

	if (NULL == s_pkReloadSpamEvent)
	{
		reload_spam_event_info* info = AllocEventInfo<reload_spam_event_info>();
		s_pkReloadSpamEvent = event_create(reload_spam_event, info, PASSES_PER_SEC(g_uiSpamReloadCycle));
	}
}

void CancelReloadSpamEvent()
{
	s_pkReloadSpamEvent = NULL;
}

void AccountDB::AnalyzeReturnQuery(SQLMsg* pMsg)
{
	CReturnQueryInfo* qi = (CReturnQueryInfo*)pMsg->pvUserData;

	switch (qi->iType)
	{
		case QID_SPAM_DB:
		{
			if (pMsg->Get()->uiNumRows > 0)
			{
				MYSQL_ROW row;

				SpamManager::instance().Clear();

				while ((row = mysql_fetch_row(pMsg->Get()->pSQLResult)))
					SpamManager::instance().Insert(row[0], atoi(row[1]));
			}
		}
		break;
	}

	M2_DELETE(qi);
}
