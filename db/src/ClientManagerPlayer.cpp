#include "stdafx.h"

#include "ClientManager.h"

#include "Main.h"
#include "QID.h"
#include "ItemAwardManager.h"
#include "HB.h"
#include "Cache.h"

extern bool g_bHotBackup;

extern std::string g_stLocale;
extern int g_test_server;
extern int g_log;

//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!! IMPORTANT !!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
// Check all SELECT syntax on item table before change this function!!!
//
bool CreateItemTableFromRes(MYSQL_RES* res, std::vector<TPlayerItem>* pVec, DWORD dwPID)
{
	if (!res)
	{
		pVec->clear();
		return true;
	}

	int rows;

	if ((rows = static_cast<int>(mysql_num_rows(res))) <= 0) // 데이터 없음
	{
		pVec->clear();
		return true;
	}

	pVec->resize(rows);

	for (int i = 0; i < rows; ++i)
	{
		MYSQL_ROW row = mysql_fetch_row(res);
		TPlayerItem& item = pVec->at(i);

		int cur = 0;

		// Check all SELECT syntax on item table before change this function!!!
		// Check all SELECT syntax on item table before change this function!!!
		// Check all SELECT syntax on item table before change this function!!!
		str_to_number(item.dwID, row[cur++]);
		str_to_number(item.bWindow, row[cur++]);
		str_to_number(item.wPos, row[cur++]);
		str_to_number(item.dwVnum, row[cur++]);
		str_to_number(item.dwCount, row[cur++]);

#if defined(__SOUL_BIND_SYSTEM__)
		str_to_number(item.lSealDate, row[cur++]);
#endif

		for (BYTE i = 0; i < ITEM_SOCKET_MAX_NUM; i++)
			str_to_number(item.alSockets[i], row[cur++]);

		for (int j = 0; j < ITEM_ATTRIBUTE_MAX_NUM; j++)
		{
			str_to_number(item.aAttr[j].wType, row[cur++]);
			str_to_number(item.aAttr[j].lValue, row[cur++]);
		}

#if defined(__CHANGE_LOOK_SYSTEM__)
		str_to_number(item.dwTransmutationVnum, row[cur++]);
#endif

#if defined(__REFINE_ELEMENT_SYSTEM__)
		str_to_number(item.RefineElement.wApplyType, row[cur++]);
		str_to_number(item.RefineElement.bGrade, row[cur++]);
		for (BYTE i = 0; i < REFINE_ELEMENT_MAX; i++)
			str_to_number(item.RefineElement.abValue[i], row[cur++]);
		for (BYTE i = 0; i < REFINE_ELEMENT_MAX; i++)
			str_to_number(item.RefineElement.abBonusValue[i], row[cur++]);
#endif

#if defined(__ITEM_APPLY_RANDOM__)
		for (int j = 0; j < ITEM_APPLY_MAX_NUM; j++)
		{
			str_to_number(item.aApplyRandom[j].wType, row[cur++]);
			str_to_number(item.aApplyRandom[j].lValue, row[cur++]);
			str_to_number(item.aApplyRandom[j].bPath, row[cur++]);
		}
#endif

#if defined(__SET_ITEM__)
		str_to_number(item.bSetValue, row[cur++]);
#endif

		item.dwOwner = dwPID;
	}

	return true;
}

size_t CreatePlayerSaveQuery(char* pszQuery, size_t querySize, TPlayerTable* pkTab)
{
	size_t queryLen;

	queryLen = snprintf(pszQuery, querySize,
		"UPDATE player%s SET "
		"`job` = %d, "
		"`voice` = %d, "
		"`dir` = %d, "
		"`x` = %d, "
		"`y` = %d, "
		"`z` = %d, "
		"`map_index` = %d, "
		"`exit_x` = %ld, "
		"`exit_y` = %ld, "
		"`exit_map_index` = %ld, "
		"`hp` = %d, "
		"`mp` = %d, "
		"`stamina` = %d, "
		"`random_hp` = %d, "
		"`random_sp` = %d, "
		"`playtime` = %d, "
		"`level` = %d, "
		"`level_step` = %d, "
		"`st` = %d, "
		"`ht` = %d, "
		"`dx` = %d, "
		"`iq` = %d, "
#if defined(__EXTEND_INVEN_SYSTEM__)
		"`inven_stage` = %d, "
#endif
		"`gold` = %d, "
#if defined(__CHEQUE_SYSTEM__)
		"`cheque` = %d, "
#endif
#if defined(__GEM_SYSTEM__)
		"`gem` = %d, "
#endif
		"`exp` = %u, "
		"`stat_point` = %d, "
		"`skill_point` = %d, "
		"`sub_skill_point` = %d, "
		"`stat_reset_count` = %d, "
		"`ip` = '%s', "
		"`part_main` = %d, "
		"`part_hair` = %d, "
#if defined(__ACCE_COSTUME_SYSTEM__)
		"`part_acce` = %d, "
#endif
		"`last_play` = NOW(), "
		"`skill_group` = %d, "
		"`alignment` = %ld, "
#if defined(__CONQUEROR_LEVEL__)
		"`conqueror_level` = %d, "
		"`conqueror_level_step` = %d, "
		"`sungma_str` = %d, "
		"`sungma_hp` = %d, "
		"`sungma_move` = %d, "
		"`sungma_immune` = %d, "
		"`conqueror_exp` = %u, "
		"`conqueror_point` = %d, "
#endif
		"`horse_level` = %d, "
		"`horse_riding` = %d, "
		"`horse_hp` = %d, "
		"`horse_hp_droptime` = %u, "
		"`horse_stamina` = %d, "
		"`horse_skill_point` = %d, "
		,
		GetTablePostfix(),
		pkTab->job,
		pkTab->voice,
		pkTab->dir,
		pkTab->x,
		pkTab->y,
		pkTab->z,
		pkTab->lMapIndex,
		pkTab->lExitX,
		pkTab->lExitY,
		pkTab->lExitMapIndex,
		pkTab->hp,
		pkTab->sp,
		pkTab->stamina,
		pkTab->sRandomHP,
		pkTab->sRandomSP,
		pkTab->playtime,
		pkTab->level,
		pkTab->level_step,
		pkTab->st,
		pkTab->ht,
		pkTab->dx,
		pkTab->iq,
#if defined(__EXTEND_INVEN_SYSTEM__)
		pkTab->inven_stage,
#endif
		pkTab->gold,
#if defined(__CHEQUE_SYSTEM__)
		pkTab->cheque,
#endif
#if defined(__GEM_SYSTEM__)
		pkTab->gem,
#endif
		pkTab->exp,
		pkTab->stat_point,
		pkTab->skill_point,
		pkTab->sub_skill_point,
		pkTab->stat_reset_count,
		pkTab->ip,
		pkTab->adwParts[PART_MAIN],
		pkTab->adwParts[PART_HAIR],
#if defined(__ACCE_COSTUME_SYSTEM__)
		pkTab->adwParts[PART_ACCE],
#endif
		pkTab->skill_group,
		pkTab->lAlignment,
#if defined(__CONQUEROR_LEVEL__)
		pkTab->conqueror_level,
		pkTab->conqueror_level_step,
		pkTab->sungma_str,
		pkTab->sungma_hp,
		pkTab->sungma_move,
		pkTab->sungma_immune,
		pkTab->conqueror_exp,
		pkTab->conqueror_point,
#endif
		pkTab->horse.bLevel,
		pkTab->horse.bRiding,
		pkTab->horse.sHealth,
		pkTab->horse.dwHorseHealthDropTime,
		pkTab->horse.sStamina,
		pkTab->horse_skill_point);

	// Binary 로 바꾸기 위한 임시 공간
	static char text[QUERY_MAX_LEN];

	CDBManager::instance().EscapeString(text, pkTab->skills, sizeof(pkTab->skills));
	queryLen += snprintf(pszQuery + queryLen, querySize - queryLen, "`skill_level` = '%s', ", text);

	CDBManager::instance().EscapeString(text, pkTab->quickslot, sizeof(pkTab->quickslot));
	queryLen += snprintf(pszQuery + queryLen, querySize - queryLen, "`quickslot` = '%s' ", text);

	queryLen += snprintf(pszQuery + queryLen, querySize - queryLen, " WHERE `id` = %d", pkTab->id);
	return queryLen;
}

CPlayerTableCache* CClientManager::GetPlayerCache(DWORD id)
{
	TPlayerTableCacheMap::iterator it = m_map_playerCache.find(id);

	if (it == m_map_playerCache.end())
		return NULL;

	TPlayerTable* pTable = it->second->Get(false);
	pTable->logoff_interval = static_cast<DWORD>(GetCurrentTime()) - it->second->GetLastUpdateTime();
	return it->second;
}

void CClientManager::PutPlayerCache(TPlayerTable* pNew)
{
	CPlayerTableCache* c;

	c = GetPlayerCache(pNew->id);

	if (!c)
	{
		c = new CPlayerTableCache;
		m_map_playerCache.insert(TPlayerTableCacheMap::value_type(pNew->id, c));
	}

	if (g_bHotBackup)
		PlayerHB::instance().Put(pNew->id);

	c->Put(pNew);
}

/*
* PLAYER LOAD
*/
void CClientManager::QUERY_PLAYER_LOAD(CPeer* peer, DWORD dwHandle, TPlayerLoadPacket* packet)
{
	CPlayerTableCache* c;
	TPlayerTable* pTab;

	//
	// 한 계정에 속한 모든 캐릭터들 캐쉬처리
	//
	CLoginData* pLoginData = GetLoginDataByAID(packet->account_id);

	if (pLoginData)
	{
		for (int n = 0; n < PLAYER_PER_ACCOUNT; ++n)
			if (pLoginData->GetAccountRef().players[n].dwID != 0)
				DeleteLogoutPlayer(pLoginData->GetAccountRef().players[n].dwID);
	}

	// ---------------------------------------------------------------
	// 1. 유저정보가 DBCache 에 존재 : DBCache에서
	// 2. 유저정보가 DBCache 에 없음 : DB에서
	// ---------------------------------------------------------------

	// ---------------------------------------------------------------
	// 1. 유저정보가 DBCache 에 존재 : DBCache에서
	// ---------------------------------------------------------------
	if ((c = GetPlayerCache(packet->player_id)))
	{
		CLoginData* pkLD = GetLoginDataByAID(packet->account_id);

		if (!pkLD || pkLD->IsPlay())
		{
			sys_log(0, "PLAYER_LOAD_ERROR: LoginData %p IsPlay %d", pkLD, pkLD ? pkLD->IsPlay() : 0);
			peer->EncodeHeader(HEADER_DG_PLAYER_LOAD_FAILED, dwHandle, 0);
			return;
		}

		pTab = c->Get();

		pkLD->SetPlay(true);
		thecore_memcpy(pTab->aiPremiumTimes, pkLD->GetPremiumPtr(), sizeof(pTab->aiPremiumTimes));

		peer->EncodeHeader(HEADER_DG_PLAYER_LOAD_SUCCESS, dwHandle, sizeof(TPlayerTable));
		peer->Encode(pTab, sizeof(TPlayerTable));

		if (packet->player_id != pkLD->GetLastPlayerID())
		{
			TPacketNeedLoginLogInfo logInfo;
			logInfo.dwPlayerID = packet->player_id;

			pkLD->SetLastPlayerID(packet->player_id);

			peer->EncodeHeader(HEADER_DG_NEED_LOGIN_LOG, dwHandle, sizeof(TPacketNeedLoginLogInfo));
			peer->Encode(&logInfo, sizeof(TPacketNeedLoginLogInfo));
		}

		char szQuery[1024] = { 0, };

		TItemCacheSet* pSet = GetItemCacheSet(pTab->id);

		sys_log(0, "[PLAYER_LOAD] ID %s pid %d gold %d "
#if defined(__CHEQUE_SYSTEM__)
			"cheque %d "
#endif
#if defined(__GEM_SYSTEM__)
			"gem %d "
#endif
			, pTab->name
			, pTab->id
			, pTab->gold
#if defined(__CHEQUE_SYSTEM__)
			, pTab->cheque
#endif
#if defined(__GEM_SYSTEM__)
			, pTab->gem
#endif
		);

		// ---------------------------------------------------------------
		// 아이템 & AFFECT & QUEST 로딩 :
		// ---------------------------------------------------------------
		// 1) 아이템이 DBCache 에 존재 : DBCache 에서 가져옴
		// 2) 아이템이 DBCache 에 없음 : DB 에서 가져옴

		///////////////////////////////////////////////////////////////
		// 1) 아이템이 DBCache 에 존재 : DBCache 에서 가져옴
		///////////////////////////////////////////////////////////////
		if (pSet)
		{
			static std::vector<TPlayerItem> s_items;
			s_items.resize(pSet->size());

			DWORD dwCount = 0;
			TItemCacheSet::iterator it = pSet->begin();

			while (it != pSet->end())
			{
				CItemCache* c = *it++;
				TPlayerItem* p = c->Get();

				if (p->dwVnum) // vnum이 없으면 삭제된 아이템이다.
					thecore_memcpy(&s_items[dwCount++], p, sizeof(TPlayerItem));
			}

			if (g_test_server)
				sys_log(0, "ITEM_CACHE: HIT! %s count: %u", pTab->name, dwCount);

			peer->EncodeHeader(HEADER_DG_ITEM_LOAD, dwHandle, sizeof(DWORD) + sizeof(TPlayerItem) * dwCount);
			peer->EncodeDWORD(dwCount);

			if (dwCount)
				peer->Encode(&s_items[0], sizeof(TPlayerItem) * dwCount);

			// Quest
			snprintf(szQuery, sizeof(szQuery),
				"SELECT `dwPID`, `szName`, `szState`, `lValue` FROM quest%s WHERE `dwPID` = %d AND `lValue` <> 0",
				GetTablePostfix(), pTab->id);

			CDBManager::instance().ReturnQuery(szQuery, QID_QUEST, peer->GetHandle(), new ClientHandleInfo(dwHandle, 0, packet->account_id));

			// Affect
			snprintf(szQuery, sizeof(szQuery),
				"SELECT `dwPID`, `dwType`, `wApplyOn`, `lApplyValue`, `dwFlag`, `lDuration`, `lSPCost`"
#if defined(__AFFECT_RENEWAL__)
				", `bRealTime`"
#endif
				" FROM `affect%s` WHERE `dwPID` = %d",
				GetTablePostfix(), pTab->id);
			CDBManager::instance().ReturnQuery(szQuery, QID_AFFECT, peer->GetHandle(), new ClientHandleInfo(dwHandle, pTab->id));
		}
		///////////////////////////////////////////////////////////////
		// 2) 아이템이 DBCache 에 없음 : DB 에서 가져옴
		///////////////////////////////////////////////////////////////
		else
		{
			snprintf(szQuery, sizeof(szQuery),
				"SELECT `id`, `window`+0, `pos`, `vnum`, `count`"
#if defined(__SOUL_BIND_SYSTEM__)
				", `soulbind`"
#endif
				", `socket0`, `socket1`, `socket2`"
#if defined(__ITEM_SOCKET6__)
				", `socket3`, `socket4`, `socket5`"
#endif
				", `attrtype0`, `attrvalue0`"
				", `attrtype1`, `attrvalue1`"
				", `attrtype2`, `attrvalue2`"
				", `attrtype3`, `attrvalue3`"
				", `attrtype4`, `attrvalue4`"
				", `attrtype5`, `attrvalue5`"
				", `attrtype6`, `attrvalue6`"
#if defined(__CHANGE_LOOK_SYSTEM__)
				", `transmutation`"
#endif
#if defined(__REFINE_ELEMENT_SYSTEM__)
				", `refine_element_apply_type`"
				", `refine_element_grade`"
				", `refine_element_value0`, `refine_element_value1`, `refine_element_value2`"
				", `refine_element_bonus_value0`, `refine_element_bonus_value1`, `refine_element_bonus_value2`"
#endif
#if defined(__ITEM_APPLY_RANDOM__)
				", `apply_type0`, `apply_value0`, `apply_path0`"
				", `apply_type1`, `apply_value1`, `apply_path1`"
				", `apply_type2`, `apply_value2`, `apply_path2`"
				", `apply_type3`, `apply_value3`, `apply_path3`"
#endif
#if defined(__SET_ITEM__)
				", `set_value`"
#endif
				" FROM `item%s` WHERE `owner_id` = %u AND (`window` in ("
				"'INVENTORY', 'EQUIPMENT', 'DRAGON_SOUL_INVENTORY', 'BELT_INVENTORY'"
#if defined(__ATTR_6TH_7TH__)
				", 'NPC_STORAGE'"
#endif
				"))",
				GetTablePostfix(), pTab->id);

			CDBManager::instance().ReturnQuery(szQuery,
				QID_ITEM,
				peer->GetHandle(),
				new ClientHandleInfo(dwHandle, pTab->id));
			snprintf(szQuery, sizeof(szQuery),
				"SELECT `dwPID`, `szName`, `szState`, `lValue` FROM quest%s WHERE `dwPID` = %d",
				GetTablePostfix(), pTab->id);

			CDBManager::instance().ReturnQuery(szQuery,
				QID_QUEST,
				peer->GetHandle(),
				new ClientHandleInfo(dwHandle, pTab->id));
			snprintf(szQuery, sizeof(szQuery),
				"SELECT `dwPID`, `dwType`, `wApplyOn`, `lApplyValue`, `dwFlag`, `lDuration`, `lSPCost`"
#if defined(__AFFECT_RENEWAL__)
				", `bRealTime`"
#endif
				" FROM `affect%s` WHERE `dwPID` = %d",
				GetTablePostfix(), pTab->id);

			CDBManager::instance().ReturnQuery(szQuery,
				QID_AFFECT,
				peer->GetHandle(),
				new ClientHandleInfo(dwHandle, pTab->id));
		}
		// ljw
		//return;
	}
	// ---------------------------------------------------------------
	// 2. 유저정보가 DBCache 에 없음 : DB에서
	// ---------------------------------------------------------------
	else
	{
		sys_log(0, "[PLAYER_LOAD] Load from PlayerDB pid[%d]", packet->player_id);

		char queryStr[QUERY_MAX_LEN];

		// ---------------------------------------------------------------
		// 캐릭터 정보 얻어오기 : 무조건 DB에서
		// ---------------------------------------------------------------
		snprintf(queryStr, sizeof(queryStr),
			"SELECT "
			"`id`, `name`, `job`, `voice`, `dir`, `x`, `y`, `z`, `map_index`, "
			"`exit_x`, `exit_y`, `exit_map_index`, `hp`, `mp`, `stamina`, `random_hp`, `random_sp`, `playtime`, "
#if defined(__EXTEND_INVEN_SYSTEM__)
			"`inven_stage`, "
#endif
			"`gold`, "
#if defined(__CHEQUE_SYSTEM__)
			"`cheque`, "
#endif
#if defined(__GEM_SYSTEM__)
			"`gem`, "
#endif
			"`level`, "
			"`level_step`, "
			"`st`, `ht`, `dx`, `iq`, `exp`, "
			"`stat_point`, "
			"`skill_point`, "
			"`sub_skill_point`, "
			"`stat_reset_count`, "
			"`part_base`, `part_hair`, "
#if defined(__ACCE_COSTUME_SYSTEM__)
			"`part_acce`, "
#endif
			"`skill_level`, "
			"`quickslot`, "
			"`skill_group`, "
			"`alignment`, "
#if defined(__CONQUEROR_LEVEL__)
			"`conqueror_level`, "
			"`conqueror_level_step`, "
			"`sungma_str`, "
			"`sungma_hp`, "
			"`sungma_move`, "
			"`sungma_immune`, "
			"`conqueror_exp`, "
			"`conqueror_point`, "
#endif
			"`horse_level`, "
			"`horse_riding`, "
			"`horse_hp`, "
			"`horse_hp_droptime`, "
			"`horse_stamina`, "
			"UNIX_TIMESTAMP(NOW()) - UNIX_TIMESTAMP(`last_play`), "
			"`horse_skill_point`"
			" FROM player%s WHERE `id` = %d",
			GetTablePostfix(), packet->player_id);

		ClientHandleInfo* pkInfo = new ClientHandleInfo(dwHandle, packet->player_id);
		pkInfo->account_id = packet->account_id;
		CDBManager::instance().ReturnQuery(queryStr, QID_PLAYER, peer->GetHandle(), pkInfo);

		// ---------------------------------------------------------------
		// 아이템 가져오기
		// ---------------------------------------------------------------
		snprintf(queryStr, sizeof(queryStr),
			"SELECT `id`, `window`+0, `pos`, `vnum`, `count`"
#if defined(__SOUL_BIND_SYSTEM__)
			", `soulbind`"
#endif
			", `socket0`, `socket1`, `socket2`"
#if defined(__ITEM_SOCKET6__)
			", `socket3`, `socket4`, `socket5`"
#endif
			", `attrtype0`, `attrvalue0`"
			", `attrtype1`, `attrvalue1`"
			", `attrtype2`, `attrvalue2`"
			", `attrtype3`, `attrvalue3`"
			", `attrtype4`, `attrvalue4`"
			", `attrtype5`, `attrvalue5`"
			", `attrtype6`, `attrvalue6`"
#if defined(__CHANGE_LOOK_SYSTEM__)
			", `transmutation`"
#endif
#if defined(__REFINE_ELEMENT_SYSTEM__)
			", `refine_element_apply_type`"
			", `refine_element_grade`"
			", `refine_element_value0`, `refine_element_value1`, `refine_element_value2`"
			", `refine_element_bonus_value0`, `refine_element_bonus_value1`, `refine_element_bonus_value2`"
#endif
#if defined(__ITEM_APPLY_RANDOM__)
			", `apply_type0`, `apply_value0`, `apply_path0`"
			", `apply_type1`, `apply_value1`, `apply_path1`"
			", `apply_type2`, `apply_value2`, `apply_path2`"
			", `apply_type3`, `apply_value3`, `apply_path3`"
#endif
#if defined(__SET_ITEM__)
			", `set_value`"
#endif
			" FROM `item%s` WHERE `owner_id` = %u AND (`window` in ("
			"'INVENTORY', 'EQUIPMENT', 'DRAGON_SOUL_INVENTORY', 'BELT_INVENTORY'"
#if defined(__ATTR_6TH_7TH__)
			", 'NPC_STORAGE'"
#endif
			"))",
			GetTablePostfix(), packet->player_id);

		CDBManager::instance().ReturnQuery(queryStr, QID_ITEM, peer->GetHandle(), new ClientHandleInfo(dwHandle, packet->player_id));

		// ---------------------------------------------------------------
		// QUEST 가져오기
		// ---------------------------------------------------------------
		snprintf(queryStr, sizeof(queryStr),
			"SELECT `dwPID`, `szName`, `szState`, `lValue` FROM quest%s WHERE `dwPID` = %d",
			GetTablePostfix(), packet->player_id);
		CDBManager::instance().ReturnQuery(queryStr, QID_QUEST, peer->GetHandle(), new ClientHandleInfo(dwHandle, packet->player_id, packet->account_id));
		// 독일 선물 기능에서 item_award테이블에서 login 정보를 얻기위해 account id도 넘겨준다
		// ---------------------------------------------------------------
		// AFFECT 가져오기 
		// ---------------------------------------------------------------
		snprintf(queryStr, sizeof(queryStr),
			"SELECT `dwPID`, `dwType`, `wApplyOn`, `lApplyValue`, `dwFlag`, `lDuration`, `lSPCost`"
#if defined(__AFFECT_RENEWAL__)
			", `bRealTime`"
#endif
			" FROM `affect%s` WHERE `dwPID` = %d",
			GetTablePostfix(), packet->player_id);
		CDBManager::instance().ReturnQuery(queryStr, QID_AFFECT, peer->GetHandle(), new ClientHandleInfo(dwHandle, packet->player_id));
	}
}

void CClientManager::ItemAward(CPeer* peer, char* login)
{
	char login_t[LOGIN_MAX_LEN + 1] = "";
	strlcpy(login_t, login, LOGIN_MAX_LEN + 1);
	std::set<TItemAward*>* pSet = ItemAwardManager::instance().GetByLogin(login_t);
	if (pSet == NULL)
		return;

	ItemAwardSet::iterator it = pSet->begin(); // taken_time 이 NULL 인것들 읽어옴
	while (it != pSet->end())
	{
		TItemAward* pItemAward = *(it++);
		char* whyStr = pItemAward->szWhy; // why 콜룸 읽기
		char cmdStr[100] = ""; // why콜룸에서 읽은 값을 임시 문자열에 복사해둠
		strcpy(cmdStr, whyStr); // 명령어 얻는 과정에서 토큰쓰면 원본도 토큰화 되기 때문
		char command[20] = "";
		GetCommand(cmdStr, command); // command 얻기
		if (!(strcmp(cmdStr, "GIFT"))) // command 가 GIFT 이면
		{
			TPacketItemAwardInfromer giftData;
			strcpy(giftData.login, pItemAward->szLogin); //로그인 아이디 복사
			strcpy(giftData.command, command); // 명령어 복사
			giftData.vnum = pItemAward->dwVnum; // 아이템 vnum 도 복사
			ForwardPacket(HEADER_DG_ITEMAWARD_INFORMER, &giftData, sizeof(TPacketItemAwardInfromer));
		}
	}
}

char* CClientManager::GetCommand(char* str, char* command)
{
	// char* command = new char[20];
	char* tok;

	if (str[0] == '[')
	{
		tok = strtok(str, "]");
		strcat(command, &tok[1]);
	}

	return command;
	// free(command);
}

bool CreatePlayerTableFromRes(MYSQL_RES* res, TPlayerTable* pkTab)
{
	if (mysql_num_rows(res) == 0) // 데이터 없음
		return false;

	memset(pkTab, 0, sizeof(TPlayerTable));

	MYSQL_ROW row = mysql_fetch_row(res);

	int col = 0;

	str_to_number(pkTab->id, row[col++]);
	strlcpy(pkTab->name, row[col++], sizeof(pkTab->name));
	str_to_number(pkTab->job, row[col++]);
	str_to_number(pkTab->voice, row[col++]);
	str_to_number(pkTab->dir, row[col++]);
	str_to_number(pkTab->x, row[col++]);
	str_to_number(pkTab->y, row[col++]);
	str_to_number(pkTab->z, row[col++]);
	str_to_number(pkTab->lMapIndex, row[col++]);
	str_to_number(pkTab->lExitX, row[col++]);
	str_to_number(pkTab->lExitY, row[col++]);
	str_to_number(pkTab->lExitMapIndex, row[col++]);
	str_to_number(pkTab->hp, row[col++]);
	str_to_number(pkTab->sp, row[col++]);
	str_to_number(pkTab->stamina, row[col++]);
	str_to_number(pkTab->sRandomHP, row[col++]);
	str_to_number(pkTab->sRandomSP, row[col++]);
	str_to_number(pkTab->playtime, row[col++]);
#if defined(__EXTEND_INVEN_SYSTEM__)
	str_to_number(pkTab->inven_stage, row[col++]);
#endif
	str_to_number(pkTab->gold, row[col++]);
#if defined(__CHEQUE_SYSTEM__)
	str_to_number(pkTab->cheque, row[col++]);
#endif
#if defined(__GEM_SYSTEM__)
	str_to_number(pkTab->gem, row[col++]);
#endif
	str_to_number(pkTab->level, row[col++]);
	str_to_number(pkTab->level_step, row[col++]);
	str_to_number(pkTab->st, row[col++]);
	str_to_number(pkTab->ht, row[col++]);
	str_to_number(pkTab->dx, row[col++]);
	str_to_number(pkTab->iq, row[col++]);
	str_to_number(pkTab->exp, row[col++]);
	str_to_number(pkTab->stat_point, row[col++]);
	str_to_number(pkTab->skill_point, row[col++]);
	str_to_number(pkTab->sub_skill_point, row[col++]);
	str_to_number(pkTab->stat_reset_count, row[col++]);
	str_to_number(pkTab->part_base, row[col++]);
	str_to_number(pkTab->adwParts[PART_HAIR], row[col++]);
#if defined(__ACCE_COSTUME_SYSTEM__)
	str_to_number(pkTab->adwParts[PART_ACCE], row[col++]);
#endif

	if (row[col])
		thecore_memcpy(pkTab->skills, row[col], sizeof(pkTab->skills));
	else
		memset(&pkTab->skills, 0, sizeof(pkTab->skills));

	col++;

	if (row[col])
		thecore_memcpy(pkTab->quickslot, row[col], sizeof(pkTab->quickslot));
	else
		memset(pkTab->quickslot, 0, sizeof(pkTab->quickslot));

	col++;

	str_to_number(pkTab->skill_group, row[col++]);
	str_to_number(pkTab->lAlignment, row[col++]);
#if defined(__CONQUEROR_LEVEL__)
	str_to_number(pkTab->conqueror_level, row[col++]);
	str_to_number(pkTab->conqueror_level_step, row[col++]);
	str_to_number(pkTab->sungma_str, row[col++]);
	str_to_number(pkTab->sungma_hp, row[col++]);
	str_to_number(pkTab->sungma_move, row[col++]);
	str_to_number(pkTab->sungma_immune, row[col++]);
	str_to_number(pkTab->conqueror_exp, row[col++]);
	str_to_number(pkTab->conqueror_point, row[col++]);
#endif
	str_to_number(pkTab->horse.bLevel, row[col++]);
	str_to_number(pkTab->horse.bRiding, row[col++]);
	str_to_number(pkTab->horse.sHealth, row[col++]);
	str_to_number(pkTab->horse.dwHorseHealthDropTime, row[col++]);
	str_to_number(pkTab->horse.sStamina, row[col++]);
	str_to_number(pkTab->logoff_interval, row[col++]);
	str_to_number(pkTab->horse_skill_point, row[col++]);

	// reset sub_skill_point
	{
		pkTab->skills[123].bLevel = 0; // SKILL_CREATE
		if (pkTab->skills[130].bMasterType != 0) // SKILL_HORSE
			pkTab->skills[130].bMasterType = SKILL_NORMAL;

		if (pkTab->level > 9)
		{
			int max_point = pkTab->level - 9;

			int skill_point =
				MIN(20, pkTab->skills[121].bLevel) + // SKILL_LEADERSHIP 통솔력
				MIN(20, pkTab->skills[124].bLevel) + // SKILL_MINING 채광
				MIN(10, pkTab->skills[131].bLevel) + // SKILL_HORSE_SUMMON 말소환
				MIN(20, pkTab->skills[141].bLevel) + // SKILL_ADD_HP HP보강
				MIN(20, pkTab->skills[142].bLevel) + // SKILL_RESIST_PENETRATE 관통저항
#if defined(__PARTY_PROFICY__)
				MIN(20, pkTab->skills[133].bLevel) + // SKILL_ROLE_PROFICIENCY
#endif
#if defined(__PARTY_INSIGHT__)
				MIN(20, pkTab->skills[134].bLevel) + // SKILL_INSIGHT
#endif
				MIN(20, pkTab->skills[246].bLevel); // SKILL_HIT

			pkTab->sub_skill_point = max_point - skill_point;
		}
		else
			pkTab->sub_skill_point = 0;
	}

	return true;
}

void CClientManager::RESULT_COMPOSITE_PLAYER(CPeer* peer, SQLMsg* pMsg, DWORD dwQID)
{
	CQueryInfo* qi = (CQueryInfo*)pMsg->pvUserData;
	std::unique_ptr<ClientHandleInfo> info((ClientHandleInfo*)qi->pvData);

	MYSQL_RES* pSQLResult = pMsg->Get()->pSQLResult;
	if (!pSQLResult)
	{
		sys_err("null MYSQL_RES QID %u", dwQID);
		return;
	}

	switch (dwQID)
	{
	case QID_PLAYER:
		sys_log(0, "QID_PLAYER %u %u", info->dwHandle, info->player_id);
		RESULT_PLAYER_LOAD(peer, pSQLResult, info.get());
		break;

	case QID_ITEM:
		sys_log(0, "QID_ITEM %u", info->dwHandle);
		RESULT_ITEM_LOAD(peer, pSQLResult, info->dwHandle, info->player_id);
		break;

	case QID_QUEST:
	{
		sys_log(0, "QID_QUEST %u", info->dwHandle);
		RESULT_QUEST_LOAD(peer, pSQLResult, info->dwHandle, info->player_id);

		// aid얻기
		ClientHandleInfo* temp1 = info.get();
		if (temp1 == NULL)
			break;

		CLoginData* pLoginData1 = GetLoginDataByAID(temp1->account_id);
		// 독일 선물 기능
		//if (pLoginData1->GetAccountRef().login == NULL)
		//	break;

		if (pLoginData1 == NULL)
			break;

		sys_log(0, "info of pLoginData1 before call ItemAwardfunction %d", pLoginData1);
		ItemAward(peer, pLoginData1->GetAccountRef().login);
	}
	break;

	case QID_AFFECT:
		sys_log(0, "QID_AFFECT %u", info->dwHandle);
		RESULT_AFFECT_LOAD(peer, pSQLResult, info->dwHandle, info->player_id);
		break;
	}
}

void CClientManager::RESULT_PLAYER_LOAD(CPeer* peer, MYSQL_RES* pRes, ClientHandleInfo* pkInfo)
{
	TPlayerTable tab;

	if (!CreatePlayerTableFromRes(pRes, &tab))
	{
		peer->EncodeHeader(HEADER_DG_PLAYER_LOAD_FAILED, pkInfo->dwHandle, 0);
		return;
	}

	CLoginData* pkLD = GetLoginDataByAID(pkInfo->account_id);

	if (!pkLD || pkLD->IsPlay())
	{
		sys_log(0, "PLAYER_LOAD_ERROR: LoginData %p IsPlay %d", pkLD, pkLD ? pkLD->IsPlay() : 0);
		peer->EncodeHeader(HEADER_DG_PLAYER_LOAD_FAILED, pkInfo->dwHandle, 0);
		return;
	}

	pkLD->SetPlay(true);
	thecore_memcpy(tab.aiPremiumTimes, pkLD->GetPremiumPtr(), sizeof(tab.aiPremiumTimes));

	peer->EncodeHeader(HEADER_DG_PLAYER_LOAD_SUCCESS, pkInfo->dwHandle, sizeof(TPlayerTable));
	peer->Encode(&tab, sizeof(TPlayerTable));

	if (tab.id != pkLD->GetLastPlayerID())
	{
		TPacketNeedLoginLogInfo logInfo;
		logInfo.dwPlayerID = tab.id;

		pkLD->SetLastPlayerID(tab.id);

		peer->EncodeHeader(HEADER_DG_NEED_LOGIN_LOG, pkInfo->dwHandle, sizeof(TPacketNeedLoginLogInfo));
		peer->Encode(&logInfo, sizeof(TPacketNeedLoginLogInfo));
	}
}

void CClientManager::RESULT_ITEM_LOAD(CPeer* peer, MYSQL_RES* pRes, DWORD dwHandle, DWORD dwPID)
{
	static std::vector<TPlayerItem> s_items;
	// DB에서 아이템 정보를 읽어온다.
	CreateItemTableFromRes(pRes, &s_items, dwPID);
	DWORD dwCount = s_items.size();

	peer->EncodeHeader(HEADER_DG_ITEM_LOAD, dwHandle, sizeof(DWORD) + sizeof(TPlayerItem) * dwCount);
	peer->EncodeDWORD(dwCount);

	// CacheSet을 만든다
	CreateItemCacheSet(dwPID);

	// ITEM_LOAD_LOG_ATTACH_PID
	sys_log(0, "ITEM_LOAD: count %u pid %u", dwCount, dwPID);
	// END_OF_ITEM_LOAD_LOG_ATTACH_PID

	if (dwCount)
	{
		peer->Encode(&s_items[0], sizeof(TPlayerItem) * dwCount);

		for (DWORD i = 0; i < dwCount; ++i)
			PutItemCache(&s_items[i], true); // 로드한 것은 따로 저장할 필요 없으므로, 인자 bSkipQuery에 true를 넣는다.
	}
}

void CClientManager::RESULT_AFFECT_LOAD(CPeer* peer, MYSQL_RES* pRes, DWORD dwHandle, DWORD dwRealPID)
{
	int iNumRows;

	if ((iNumRows = static_cast<int>(mysql_num_rows(pRes))) == 0) // 데이터 없음
	{
		static DWORD dwPID;
		static DWORD dwCount = 0; //1;
		static TPacketAffectElement paeTable = { 0 };

		dwPID = dwRealPID;
		sys_log(0, "AFFECT_LOAD: count %u PID %u RealPID %u", dwCount, dwPID, dwRealPID);

		peer->EncodeHeader(HEADER_DG_AFFECT_LOAD, dwHandle, sizeof(DWORD) + sizeof(DWORD) + sizeof(TPacketAffectElement) * dwCount);
		peer->Encode(&dwPID, sizeof(DWORD));
		peer->Encode(&dwCount, sizeof(DWORD));
		peer->Encode(&paeTable, sizeof(TPacketAffectElement) * dwCount);
		return;
	}

	static std::vector<TPacketAffectElement> s_elements;
	s_elements.resize(iNumRows);

	DWORD dwPID = 0;

	MYSQL_ROW row;

	for (int i = 0; i < iNumRows; ++i)
	{
		TPacketAffectElement& r = s_elements[i];
		row = mysql_fetch_row(pRes);

		if (dwPID == 0)
			str_to_number(dwPID, row[0]);

		str_to_number(r.dwType, row[1]);
		str_to_number(r.wApplyOn, row[2]);
		str_to_number(r.lApplyValue, row[3]);
		str_to_number(r.dwFlag, row[4]);
		str_to_number(r.lDuration, row[5]);
		str_to_number(r.lSPCost, row[6]);
#if defined(__AFFECT_RENEWAL__)
		str_to_number(r.bRealTime, row[7]);
		r.bUpdate = false;
#endif
	}

	sys_log(0, "AFFECT_LOAD: count %d PID %u", s_elements.size(), dwPID);

	DWORD dwCount = s_elements.size();

	peer->EncodeHeader(HEADER_DG_AFFECT_LOAD, dwHandle, sizeof(DWORD) + sizeof(DWORD) + sizeof(TPacketAffectElement) * dwCount);
	peer->Encode(&dwPID, sizeof(DWORD));
	peer->Encode(&dwCount, sizeof(DWORD));
	peer->Encode(&s_elements[0], sizeof(TPacketAffectElement) * dwCount);
}

void CClientManager::RESULT_QUEST_LOAD(CPeer* peer, MYSQL_RES* pRes, DWORD dwHandle, DWORD pid)
{
	int iNumRows;

	if ((iNumRows = static_cast<int>(mysql_num_rows(pRes))) == 0)
	{
		DWORD dwCount = 0;
		peer->EncodeHeader(HEADER_DG_QUEST_LOAD, dwHandle, sizeof(DWORD));
		peer->Encode(&dwCount, sizeof(DWORD));
		return;
	}

	static std::vector<TQuestTable> s_table;
	s_table.resize(iNumRows);

	MYSQL_ROW row;

	for (int i = 0; i < iNumRows; ++i)
	{
		TQuestTable& r = s_table[i];

		row = mysql_fetch_row(pRes);

		str_to_number(r.dwPID, row[0]);
		strlcpy(r.szName, row[1], sizeof(r.szName));
		strlcpy(r.szState, row[2], sizeof(r.szState));
		str_to_number(r.lValue, row[3]);
	}

	sys_log(0, "QUEST_LOAD: count %d PID %u", s_table.size(), s_table[0].dwPID);

	DWORD dwCount = s_table.size();

	peer->EncodeHeader(HEADER_DG_QUEST_LOAD, dwHandle, sizeof(DWORD) + sizeof(TQuestTable) * dwCount);
	peer->Encode(&dwCount, sizeof(DWORD));
	peer->Encode(&s_table[0], sizeof(TQuestTable) * dwCount);
}

/*
* PLAYER SAVE
*/
void CClientManager::QUERY_PLAYER_SAVE(CPeer* peer, DWORD dwHandle, TPlayerTable* pkTab)
{
	if (g_test_server)
		sys_log(0, "PLAYER_SAVE: %s", pkTab->name);

	PutPlayerCache(pkTab);
}

typedef std::map<DWORD, time_t> time_by_id_map_t;
static time_by_id_map_t s_createTimeByAccountID;

/*
* PLAYER CREATE
*/
void CClientManager::__QUERY_PLAYER_CREATE(CPeer* peer, DWORD dwHandle, TPlayerCreatePacket* packet)
{
	char queryStr[QUERY_MAX_LEN];
	int queryLen;
	int player_id;

	// 한 계정에 X초 내로 캐릭터 생성을 할 수 없다.
	time_by_id_map_t::iterator it = s_createTimeByAccountID.find(packet->account_id);

	if (m_bDelayedCharacterCreation)
	{
		if (it != s_createTimeByAccountID.end())
		{
			time_t curtime = time(0);

			if (curtime - it->second < 30)
			{
				peer->EncodeHeader(HEADER_DG_PLAYER_CREATE_FAILED, dwHandle, 0);
				return;
			}
		}
	}

	queryLen = snprintf(queryStr, sizeof(queryStr),
		"SELECT `pid%d` FROM player_index%s WHERE `id` = %d", packet->account_index + 1, GetTablePostfix(), packet->account_id);

	std::unique_ptr<SQLMsg> pMsg0(CDBManager::instance().DirectQuery(queryStr));

	if (pMsg0->Get()->uiNumRows != 0)
	{
		if (!pMsg0->Get()->pSQLResult)
		{
			peer->EncodeHeader(HEADER_DG_PLAYER_CREATE_FAILED, dwHandle, 0);
			return;
		}

		MYSQL_ROW row = mysql_fetch_row(pMsg0->Get()->pSQLResult);

		DWORD dwPID = 0; str_to_number(dwPID, row[0]);
		if (row[0] && dwPID > 0)
		{
			peer->EncodeHeader(HEADER_DG_PLAYER_CREATE_ALREADY, dwHandle, 0);
			sys_log(0, "ALREADY EXIST AccountChrIdx %d ID %d", packet->account_index, dwPID);
			return;
		}
	}
	else
	{
		peer->EncodeHeader(HEADER_DG_PLAYER_CREATE_FAILED, dwHandle, 0);
		return;
	}

	if (g_stLocale == "sjis")
		snprintf(queryStr, sizeof(queryStr),
			"SELECT COUNT(*) AS count FROM player%s WHERE `name` = '%s' COLLATE sjis_japanese_ci",
			GetTablePostfix(), packet->player_table.name);
	else
		snprintf(queryStr, sizeof(queryStr),
			"SELECT COUNT(*) AS count FROM player%s WHERE `name` = '%s'", GetTablePostfix(), packet->player_table.name);

	std::unique_ptr<SQLMsg> pMsg1(CDBManager::instance().DirectQuery(queryStr));

	if (pMsg1->Get()->uiNumRows)
	{
		if (!pMsg1->Get()->pSQLResult)
		{
			peer->EncodeHeader(HEADER_DG_PLAYER_CREATE_FAILED, dwHandle, 0);
			return;
		}

		MYSQL_ROW row = mysql_fetch_row(pMsg1->Get()->pSQLResult);

		if (*row[0] != '0')
		{
			sys_log(0, "ALREADY EXIST name %s, row[0] %s query %s", packet->player_table.name, row[0], queryStr);
			peer->EncodeHeader(HEADER_DG_PLAYER_CREATE_ALREADY, dwHandle, 0);
			return;
		}
	}
	else
	{
		peer->EncodeHeader(HEADER_DG_PLAYER_CREATE_FAILED, dwHandle, 0);
		return;
	}

	queryLen = snprintf(queryStr, sizeof(queryStr),
		"INSERT INTO player%s "
		"(`id`, `account_id`, `name`, `level`, `st`, `ht`, `dx`, `iq`, "
		"`job`, `voice`, `dir`, `x`, `y`, `z`, "
		"`hp`, `mp`, `random_hp`, `random_sp`, `stat_point`, `stamina`, "
		"`part_base`, `part_main`, `part_hair`, "
#if defined(__ACCE_COSTUME_SYSTEM__)
		"`part_acce`, "
#endif
#if defined(__EXTEND_INVEN_SYSTEM__)
		"`inven_stage`, "
#endif
		"`gold`, "
#if defined(__CHEQUE_SYSTEM__)
		"`cheque`, "
#endif
#if defined(__GEM_SYSTEM__)
		"`gem`, "
#endif
		"`playtime`, `skill_level`, `quickslot`) "
		"VALUES (0, "
		"%u, "
		"'%s', " // name
		"%d, " // level
		"%d, " // st
		"%d, " // ht
		"%d, " // dx
		"%d, " // iq
		"%d, " // job
		"%d, " // voice
		"%d, " // dir
		"%d, " // x
		"%d, " // y
		"%d, " // z
		"%d, " // hp
		"%d, " // sp
		"%d, " // sRandomHP
		"%d, " // sRandomSP
		"%d, " // stat_point
		"%d, " // stamina
		"%d, " // part_base
		"%d, " // part_base
		"%d, " // part_base(hair)
#if defined(__ACCE_COSTUME_SYSTEM__)
		"%d, " // part_base(acce)
#endif
#if defined(__EXTEND_INVEN_SYSTEM__)
		"%d, " // inven_stage
#endif
		"%d, " // gold
#if defined(__CHEQUE_SYSTEM__)
		"%d, " // cheque
#endif
#if defined(__GEM_SYSTEM__)
		"%d, " // gem
#endif
		"0, "
		, GetTablePostfix()
		, packet->account_id
		, packet->player_table.name
		, packet->player_table.level
		, packet->player_table.st
		, packet->player_table.ht
		, packet->player_table.dx
		, packet->player_table.iq
		, packet->player_table.job
		, packet->player_table.voice
		, packet->player_table.dir
		, packet->player_table.x
		, packet->player_table.y
		, packet->player_table.z
		, packet->player_table.hp
		, packet->player_table.sp
		, packet->player_table.sRandomHP
		, packet->player_table.sRandomSP
		, packet->player_table.stat_point
		, packet->player_table.stamina
		, packet->player_table.part_base
		, packet->player_table.part_base
		, packet->player_table.adwParts[PART_HAIR]
#if defined(__ACCE_COSTUME_SYSTEM__)
		, packet->player_table.adwParts[PART_ACCE]
#endif
#if defined(__EXTEND_INVEN_SYSTEM__)
		, packet->player_table.inven_stage
#endif
		, packet->player_table.gold
#if defined(__CHEQUE_SYSTEM__)
		, packet->player_table.cheque
#endif
#if defined(__GEM_SYSTEM__)
		, packet->player_table.gem
#endif
	);

	sys_log(0, "PlayerCreate accountid %d name %s level %d gold %d"
#if defined(__CHEQUE_SYSTEM__)
		" cheque %d"
#endif
#if defined(__GEM_SYSTEM__)
		" gem %d"
#endif
		", st %d ht %d job %d"
		, packet->account_id
		, packet->player_table.name
		, packet->player_table.level
		, packet->player_table.gold
#if defined(__CHEQUE_SYSTEM__)
		, packet->player_table.cheque
#endif
#if defined(__GEM_SYSTEM__)
		, packet->player_table.gem
#endif
		, packet->player_table.st
		, packet->player_table.ht
		, packet->player_table.job
	);

	static char text[QUERY_MAX_LEN];

	CDBManager::instance().EscapeString(text, packet->player_table.skills, sizeof(packet->player_table.skills));
	queryLen += snprintf(queryStr + queryLen, sizeof(queryStr) - queryLen, "'%s', ", text);
	if (g_test_server)
		sys_log(0, "Create_Player queryLen[%d] TEXT[%s]", queryLen, text);

	CDBManager::instance().EscapeString(text, packet->player_table.quickslot, sizeof(packet->player_table.quickslot));
	queryLen += snprintf(queryStr + queryLen, sizeof(queryStr) - queryLen, "'%s')", text);

	std::unique_ptr<SQLMsg> pMsg2(CDBManager::instance().DirectQuery(queryStr));
	if (g_test_server)
		sys_log(0, "Create_Player queryLen[%d] TEXT[%s]", queryLen, text);

	if (pMsg2->Get()->uiAffectedRows <= 0)
	{
		peer->EncodeHeader(HEADER_DG_PLAYER_CREATE_ALREADY, dwHandle, 0);
		sys_log(0, "ALREADY EXIST3 query: %s AffectedRows %lu", queryStr, pMsg2->Get()->uiAffectedRows);
		return;
	}

	player_id = pMsg2->Get()->uiInsertID;

	snprintf(queryStr, sizeof(queryStr), "UPDATE player_index%s SET `pid%d` = %d WHERE `id` = %d",
		GetTablePostfix(), packet->account_index + 1, player_id, packet->account_id);
	std::unique_ptr<SQLMsg> pMsg3(CDBManager::instance().DirectQuery(queryStr));

	if (pMsg3->Get()->uiAffectedRows <= 0)
	{
		sys_err("QUERY_ERROR: %s", queryStr);

		snprintf(queryStr, sizeof(queryStr), "DELETE FROM player%s WHERE `id` = %d", GetTablePostfix(), player_id);
		CDBManager::instance().DirectQuery(queryStr);

		peer->EncodeHeader(HEADER_DG_PLAYER_CREATE_FAILED, dwHandle, 0);
		return;
	}

	TPacketDGCreateSuccess pack;
	memset(&pack, 0, sizeof(pack));

	pack.bAccountCharacterIndex = packet->account_index;

	pack.player.dwID = player_id;
	strlcpy(pack.player.szName, packet->player_table.name, sizeof(pack.player.szName));
	pack.player.byJob = packet->player_table.job;
	pack.player.byLevel = 1;
	pack.player.dwPlayMinutes = 0;
	pack.player.byST = packet->player_table.st;
	pack.player.byHT = packet->player_table.ht;
	pack.player.byDX = packet->player_table.dx;
	pack.player.byIQ = packet->player_table.iq;
#if defined(__CONQUEROR_LEVEL__)
	pack.player.byConquerorLevel = packet->player_table.conqueror_level;
	pack.player.bySungmaStr = packet->player_table.sungma_str;
	pack.player.bySungmaHp = packet->player_table.sungma_hp;
	pack.player.bySungmaMove = packet->player_table.sungma_move;
	pack.player.bySungmaImmune = packet->player_table.sungma_immune;
#endif
	pack.player.dwMainPart = packet->player_table.part_base;
	pack.player.x = packet->player_table.x;
	pack.player.y = packet->player_table.y;
	pack.player.last_play = packet->player_table.last_play;

	peer->EncodeHeader(HEADER_DG_PLAYER_CREATE_SUCCESS, dwHandle, sizeof(TPacketDGCreateSuccess));
	peer->Encode(&pack, sizeof(TPacketDGCreateSuccess));

	sys_log(0, "7 name %s job %d", pack.player.szName, pack.player.byJob);

	s_createTimeByAccountID[packet->account_id] = time(0);
}

/*
* PLAYER DELETE
*/
#if defined(__DELETE_FAILURE_TYPE__)
static char QUERY_CHECK_PLAYER_DELETE(DWORD dwPID, DWORD dwAID, INT* piWaitTime)
{
	*piWaitTime = 0;

	SQLMsg* pMsg = NULL;
	char szQuery[QUERY_MAX_LEN] = {};

#if defined(__SOUL_BIND_SYSTEM__)
	// Check if the player has any sealed items.
	snprintf(szQuery, sizeof(szQuery), "SELECT * FROM item%s WHERE `owner_id` = %d AND `soulbind` != 0", GetTablePostfix(), dwPID);
	pMsg = CDBManager::Instance().DirectQuery(szQuery);
	if (pMsg->Get()->uiNumRows)
		return DELETE_FAILURE_HAVE_SEALED_ITEM;
#endif

	// Check if the player is a member of a guild.
	snprintf(szQuery, sizeof(szQuery), "SELECT * FROM guild_member%s WHERE `pid` = %d", GetTablePostfix(), dwPID);
	pMsg = CDBManager::Instance().DirectQuery(szQuery);
	if (pMsg->Get()->uiNumRows)
		return DELETE_FAILURE_GUILD_MEMBER;

	// Check if the player is married.
	snprintf(szQuery, sizeof(szQuery), "SELECT * FROM marriage%s WHERE `pid1` = %d OR `pid2` = %d", GetTablePostfix(), dwPID, dwPID);
	pMsg = CDBManager::Instance().DirectQuery(szQuery);
	if (pMsg->Get()->uiNumRows)
		return DELETE_FAILURE_MARRIAGE;

	// Check if the player is the last character on the account and if there are any items in the safebox.
	snprintf(szQuery, sizeof(szQuery), "SELECT COUNT(*) FROM `player%s` WHERE `account_id` = %u;", GetTablePostfix(), dwAID);
	pMsg = CDBManager::Instance().DirectQuery(szQuery);
	if (pMsg->Get() && pMsg->Get()->uiNumRows)
	{
		MYSQL_ROW row = mysql_fetch_row(pMsg->Get()->pSQLResult);

		BYTE bPlayerCount = 0;
		str_to_number(bPlayerCount, row[0]);

		if (bPlayerCount == 1)
		{
			snprintf(szQuery, sizeof(szQuery), "SELECT * FROM `item%s` WHERE `owner_id` = %u AND `window` = 'SAFEBOX' > 0;", GetTablePostfix(), dwAID);
			pMsg = CDBManager::Instance().DirectQuery(szQuery);
			if (pMsg->Get()->uiNumRows)
				return DELETE_FAILURE_LAST_CHAR_SAFEBOX;
		}
	}

#if defined(__ATTR_6TH_7TH__)
	// Check if the player has any items in the NPC storage.
	snprintf(szQuery, sizeof(szQuery), "SELECT * FROM item%s WHERE `owner_id` = %d AND `window` = 'NPC_STORAGE'", GetTablePostfix(), dwPID);
	pMsg = CDBManager::Instance().DirectQuery(szQuery);
	if (pMsg->Get()->uiNumRows)
		return DELETE_FAILURE_ATTR67;
#endif

	// Check if the player has any items in the premium private shop.
	snprintf(szQuery, sizeof(szQuery), "SELECT * FROM item%s WHERE `owner_id` = %d AND `window` = 'PREMIUM_PRIVATE_SHOP'", GetTablePostfix(), dwPID);
	pMsg = CDBManager::Instance().DirectQuery(szQuery);
	if (pMsg->Get()->uiNumRows)
		return DELETE_FAILURE_PREMIUM_PRIVATE_SHOP;

	// Check if the player has at least 10 minutes of playtime.
	/*
	CPlayerTableCache* pPlayerTableCache = CClientManager::Instance().GetPlayerCache(dwPID);
	INT iPlayTime = pPlayerTableCache ? pPlayerTableCache->Get(false)->playtime : 0;
	if (iPlayTime < 10)
	{
		*piWaitTime = 10 - iPlayTime;
		return DELETE_FAILURE_REMAIN_TIME;
	}
	*/

	return -1;
}
#endif

void CClientManager::__QUERY_PLAYER_DELETE(CPeer* peer, DWORD dwHandle, TPlayerDeletePacket* packet)
{
	if (!packet->login[0] || !packet->player_id || packet->account_index >= PLAYER_PER_ACCOUNT)
		return;

	CLoginData* ld = GetLoginDataByLogin(packet->login);

	if (!ld)
	{
#if defined(__DELETE_FAILURE_TYPE__)
		TPlayerDeleteFailurePacket DelFailurePacket = {};
		DelFailurePacket.bType = DELETE_FAILURE_NORMAL;
		DelFailurePacket.iTime = 0;
		peer->EncodeHeader(HEADER_DG_PLAYER_DELETE_FAILED, dwHandle, sizeof(TPlayerDeleteFailurePacket));
		peer->Encode(&DelFailurePacket, sizeof(TPlayerDeleteFailurePacket));
#else
		peer->EncodeHeader(HEADER_DG_PLAYER_DELETE_FAILED, dwHandle, sizeof(BYTE));
		peer->EncodeBYTE(packet->account_index);
#endif
		return;
	}

	TAccountTable& r = ld->GetAccountRef();

	// block for japan
	if (g_stLocale != "sjis")
	{
		if (!IsChinaEventServer())
		{
			if (strlen(r.social_id) < 7 || strncmp(packet->private_code, r.social_id + strlen(r.social_id) - 7, 7))
			{
				sys_log(0, "PLAYER_DELETE FAILED len(%d)", strlen(r.social_id));
#if defined(__DELETE_FAILURE_TYPE__)
				TPlayerDeleteFailurePacket DelFailurePacket;
				DelFailurePacket.bType = DELETE_FAILURE_PRIVATE_CODE_ERROR;
				DelFailurePacket.iTime = 0;
				peer->EncodeHeader(HEADER_DG_PLAYER_DELETE_FAILED, dwHandle, sizeof(TPlayerDeleteFailurePacket));
				peer->Encode(&DelFailurePacket, sizeof(TPlayerDeleteFailurePacket));
#else
				peer->EncodeHeader(HEADER_DG_PLAYER_DELETE_FAILED, dwHandle, sizeof(BYTE));
				peer->EncodeBYTE(packet->account_index);
#endif
				return;
			}

			CPlayerTableCache* pkPlayerCache = GetPlayerCache(packet->player_id);
			if (pkPlayerCache)
			{
				TPlayerTable* pTab = pkPlayerCache->Get();

				if (pTab->level >= m_iPlayerDeleteLevelLimit)
				{
					sys_log(0, "PLAYER_DELETE FAILED LEVEL %u >= DELETE LIMIT %d", pTab->level, m_iPlayerDeleteLevelLimit);
#if defined(__DELETE_FAILURE_TYPE__)
					TPlayerDeleteFailurePacket DelFailurePacket;
					DelFailurePacket.bType = DELETE_FAILURE_LIMITE_LEVEL_HIGHER;
					DelFailurePacket.iTime = 0;
					peer->EncodeHeader(HEADER_DG_PLAYER_DELETE_FAILED, dwHandle, sizeof(TPlayerDeleteFailurePacket));
					peer->Encode(&DelFailurePacket, sizeof(TPlayerDeleteFailurePacket));
#else
					peer->EncodeHeader(HEADER_DG_PLAYER_DELETE_FAILED, dwHandle, sizeof(BYTE));
					peer->EncodeBYTE(packet->account_index);
#endif
					return;
				}

				if (pTab->level < m_iPlayerDeleteLevelLimitLower)
				{
					sys_log(0, "PLAYER_DELETE FAILED LEVEL %u < DELETE LIMIT %d", pTab->level, m_iPlayerDeleteLevelLimitLower);
#if defined(__DELETE_FAILURE_TYPE__)
					TPlayerDeleteFailurePacket DelFailurePacket;
					DelFailurePacket.bType = DELETE_FAILURE_LIMITE_LEVEL_LOWER;
					DelFailurePacket.iTime = 0;
					peer->EncodeHeader(HEADER_DG_PLAYER_DELETE_FAILED, dwHandle, sizeof(TPlayerDeleteFailurePacket));
					peer->Encode(&DelFailurePacket, sizeof(TPlayerDeleteFailurePacket));
#else
					peer->EncodeHeader(HEADER_DG_PLAYER_DELETE_FAILED, dwHandle, sizeof(BYTE));
					peer->EncodeBYTE(packet->account_index);
#endif
					return;
				}
			}
		}
	}

#if defined(__DELETE_FAILURE_TYPE__)
	INT iWaitTime;
	const char bFailureType = QUERY_CHECK_PLAYER_DELETE(packet->player_id, r.id, &iWaitTime);
	if (bFailureType != -1)
	{
		TPlayerDeleteFailurePacket DelFailurePacket;
		DelFailurePacket.bType = bFailureType;
		DelFailurePacket.iTime = iWaitTime;
		peer->EncodeHeader(HEADER_DG_PLAYER_DELETE_FAILED, dwHandle, sizeof(TPlayerDeleteFailurePacket));
		peer->Encode(&DelFailurePacket, sizeof(TPlayerDeleteFailurePacket));
		return;
}
#endif

	char szQuery[128];
	snprintf(szQuery, sizeof(szQuery), "SELECT p.`id`, p.`level`, p.`name` FROM player_index%s AS i, player%s AS p WHERE `pid%d` = %u AND `pid%d` = p.`id`",
		GetTablePostfix(), GetTablePostfix(), packet->account_index + 1, packet->player_id, packet->account_index + 1);

	ClientHandleInfo* pi = new ClientHandleInfo(dwHandle, packet->player_id);
	pi->account_index = packet->account_index;

	sys_log(0, "PLAYER_DELETE TRY: %s %d pid%d", packet->login, packet->player_id, packet->account_index + 1);
	CDBManager::instance().ReturnQuery(szQuery, QID_PLAYER_DELETE, peer->GetHandle(), pi);
}

//
// @version	05/06/10 Bang2ni - 플레이어 삭제시 가격정보 리스트 삭제 추가.
//
void CClientManager::__RESULT_PLAYER_DELETE(CPeer* peer, SQLMsg* msg)
{
	CQueryInfo* qi = (CQueryInfo*)msg->pvUserData;
	ClientHandleInfo* pi = (ClientHandleInfo*)qi->pvData;

	if (msg->Get() && msg->Get()->uiNumRows)
	{
		MYSQL_ROW row = mysql_fetch_row(msg->Get()->pSQLResult);

		DWORD dwPID = 0;
		str_to_number(dwPID, row[0]);

		int deletedLevelLimit = 0;
		str_to_number(deletedLevelLimit, row[1]);

		char szName[64];
		strlcpy(szName, row[2], sizeof(szName));

		if (deletedLevelLimit >= m_iPlayerDeleteLevelLimit && !IsChinaEventServer())
		{
			sys_log(0, "PLAYER_DELETE FAILED LEVEL %u >= DELETE LIMIT %d", deletedLevelLimit, m_iPlayerDeleteLevelLimit);
			peer->EncodeHeader(HEADER_DG_PLAYER_DELETE_FAILED, pi->dwHandle, 1);
			peer->EncodeBYTE(pi->account_index);
			return;
		}

		if (deletedLevelLimit < m_iPlayerDeleteLevelLimitLower)
		{
			sys_log(0, "PLAYER_DELETE FAILED LEVEL %u < DELETE LIMIT %d", deletedLevelLimit, m_iPlayerDeleteLevelLimitLower);
			peer->EncodeHeader(HEADER_DG_PLAYER_DELETE_FAILED, pi->dwHandle, 1);
			peer->EncodeBYTE(pi->account_index);
			return;
		}

		char queryStr[QUERY_MAX_LEN];

		snprintf(queryStr, sizeof(queryStr), "INSERT INTO player_deleted%s SELECT * FROM player%s WHERE `id` = %d",
			GetTablePostfix(), GetTablePostfix(), pi->player_id);
		std::unique_ptr<SQLMsg> pIns(CDBManager::instance().DirectQuery(queryStr));

		if (pIns->Get()->uiAffectedRows == 0 || pIns->Get()->uiAffectedRows == (uint32_t)-1)
		{
			sys_log(0, "PLAYER_DELETE FAILED %u CANNOT INSERT TO player_deleted%s", dwPID, GetTablePostfix());

			peer->EncodeHeader(HEADER_DG_PLAYER_DELETE_FAILED, pi->dwHandle, 1);
			peer->EncodeBYTE(pi->account_index);
			return;
		}

		// 삭제 성공
		sys_log(0, "PLAYER_DELETE SUCCESS %u", dwPID);

		// char account_index_string[16];

		// snprintf(account_index_string, sizeof(account_index_string), "player_id%d", m_iPlayerIDStart + pi->account_index);

		// 플레이어 테이블을 캐쉬에서 삭제한다.
		CPlayerTableCache* pkPlayerCache = GetPlayerCache(pi->player_id);

		if (pkPlayerCache)
		{
			m_map_playerCache.erase(pi->player_id);
			delete pkPlayerCache;
		}

		// 아이템들을 캐쉬에서 삭제한다.
		TItemCacheSet* pSet = GetItemCacheSet(pi->player_id);

		if (pSet)
		{
			TItemCacheSet::iterator it = pSet->begin();

			while (it != pSet->end())
			{
				CItemCache* pkItemCache = *it++;
				DeleteItemCache(pkItemCache->Get()->dwID);
			}

			pSet->clear();
			delete pSet;

			m_map_pkItemCacheSetPtr.erase(pi->player_id);
		}

		snprintf(queryStr, sizeof(queryStr), "UPDATE player_index%s SET `pid%d` = 0 WHERE `pid%d` = %d",
			GetTablePostfix(),
			pi->account_index + 1,
			pi->account_index + 1,
			pi->player_id);

		std::unique_ptr<SQLMsg> pMsg(CDBManager::instance().DirectQuery(queryStr));

		if (pMsg->Get()->uiAffectedRows == 0 || pMsg->Get()->uiAffectedRows == (uint32_t)-1)
		{
			sys_log(0, "PLAYER_DELETE FAIL WHEN UPDATE account table");
			peer->EncodeHeader(HEADER_DG_PLAYER_DELETE_FAILED, pi->dwHandle, 1);
			peer->EncodeBYTE(pi->account_index);
			return;
		}

		snprintf(queryStr, sizeof(queryStr), "DELETE FROM `player%s` WHERE `id` = %u", GetTablePostfix(), pi->player_id);
		delete CDBManager::instance().DirectQuery(queryStr);

		snprintf(queryStr, sizeof(queryStr), "DELETE FROM `item%s` WHERE `owner_id` = %u AND (`window` in ("
			"'INVENTORY', 'EQUIPMENT', 'DRAGON_SOUL_INVENTORY', 'BELT_INVENTORY'"
#if defined(__ATTR_6TH_7TH__)
			", 'NPC_STORAGE'"
#endif
			"))", GetTablePostfix(), pi->player_id);
		delete CDBManager::instance().DirectQuery(queryStr);

		snprintf(queryStr, sizeof(queryStr), "DELETE FROM `quest%s` WHERE `dwPID` = %d", GetTablePostfix(), pi->player_id);
		CDBManager::instance().AsyncQuery(queryStr);

		snprintf(queryStr, sizeof(queryStr), "DELETE FROM `affect%s` WHERE `dwPID` = %d", GetTablePostfix(), pi->player_id);
		CDBManager::instance().AsyncQuery(queryStr);

		snprintf(queryStr, sizeof(queryStr), "DELETE FROM `guild_member%s` WHERE `pid` = %u", GetTablePostfix(), pi->player_id);
		CDBManager::instance().AsyncQuery(queryStr);

		// MYSHOP_PRICE_LIST
		snprintf(queryStr, sizeof(queryStr), "DELETE FROM `myshop_pricelist%s` WHERE `owner_id` = %u", GetTablePostfix(), pi->player_id);
		CDBManager::instance().AsyncQuery(queryStr);
		// END_OF_MYSHOP_PRICE_LIST

		snprintf(queryStr, sizeof(queryStr), "DELETE FROM `messenger_list%s` WHERE `account` = '%s' OR `companion` = '%s'", GetTablePostfix(), szName, szName);
		CDBManager::instance().AsyncQuery(queryStr);

		peer->EncodeHeader(HEADER_DG_PLAYER_DELETE_SUCCESS, pi->dwHandle, 1);
		peer->EncodeBYTE(pi->account_index);
	}
	else
	{
		// 삭제 실패
		sys_log(0, "PLAYER_DELETE FAIL NO ROW");
		peer->EncodeHeader(HEADER_DG_PLAYER_DELETE_FAILED, pi->dwHandle, 1);
		peer->EncodeBYTE(pi->account_index);
	}
}

void CClientManager::QUERY_ADD_AFFECT(CPeer* peer, TPacketGDAddAffect* p)
{
	char query[QUERY_MAX_LEN];
#if defined(__AFFECT_RENEWAL__)
	if (p->elem.bUpdate)
	{
		snprintf(query, sizeof(query),
			"UPDATE `affect%s` SET `lApplyValue` = %ld, `dwFlag` = %u, `lDuration` = %ld, `lSPCost` = %ld, `bRealTime` = %d "
			"WHERE `dwPID` = %u AND `dwType` = %u AND `wApplyOn` = %u",
			GetTablePostfix(),
			p->elem.lApplyValue,
			p->elem.dwFlag,
			p->elem.lDuration,
			p->elem.lSPCost,
			p->elem.bRealTime ? 1 : 0,
			p->dwPID,
			p->elem.dwType,
			p->elem.wApplyOn);
	}
	else
	{
		snprintf(query, sizeof(query),
			"REPLACE INTO `affect%s` (`dwPID`, `dwType`, `wApplyOn`, `lApplyValue`, `dwFlag`, `lDuration`, `lSPCost`, `bRealTime`) "
			"VALUES(%u, %u, %u, %ld, %u, %ld, %ld, %d)",
			GetTablePostfix(),
			p->dwPID,
			p->elem.dwType,
			p->elem.wApplyOn,
			p->elem.lApplyValue,
			p->elem.dwFlag,
			p->elem.lDuration,
			p->elem.lSPCost,
			p->elem.bRealTime ? 1 : 0);
	}
#else
	snprintf(query, sizeof(query),
		"REPLACE INTO `affect%s` (`dwPID`, `dwType`, `wApplyOn`, `lApplyValue`, `dwFlag`, `lDuration`, `lSPCost`) "
		"VALUES(%u, %u, %u, %ld, %u, %ld, %ld)",
		GetTablePostfix(),
		p->dwPID,
		p->elem.dwType,
		p->elem.wApplyOn,
		p->elem.lApplyValue,
		p->elem.dwFlag,
		p->elem.lDuration,
		p->elem.lSPCost
	);
#endif
	CDBManager::instance().AsyncQuery(query);
}

void CClientManager::QUERY_REMOVE_AFFECT(CPeer* peer, TPacketGDRemoveAffect* p)
{
	char query[QUERY_MAX_LEN];
	snprintf(query, sizeof(query),
		"DELETE FROM `affect%s` WHERE `dwPID` = %u AND `dwType` = %u AND `wApplyOn` = %u",
		GetTablePostfix(), p->dwPID, p->dwType, p->wApplyOn);
	CDBManager::instance().AsyncQuery(query);
}

void CClientManager::QUERY_HIGHSCORE_REGISTER(CPeer* peer, TPacketGDHighscore* data)
{
	char szQuery[128];
	snprintf(szQuery, sizeof(szQuery), "SELECT `value` FROM highscore%s WHERE `board` = '%s' AND `pid` = %u", GetTablePostfix(), data->szBoard, data->dwPID);

	sys_log(0, "HEADER_GD_HIGHSCORE_REGISTER: PID %u", data->dwPID);

	ClientHandleInfo* pi = new ClientHandleInfo(0);
	strlcpy(pi->login, data->szBoard, sizeof(pi->login));
	pi->account_id = (DWORD)data->lValue;
	pi->player_id = data->dwPID;
	pi->account_index = (data->cDir > 0);

	CDBManager::instance().ReturnQuery(szQuery, QID_HIGHSCORE_REGISTER, peer->GetHandle(), pi);
}

void CClientManager::RESULT_HIGHSCORE_REGISTER(CPeer* pkPeer, SQLMsg* msg)
{
	CQueryInfo* qi = (CQueryInfo*)msg->pvUserData;
	ClientHandleInfo* pi = (ClientHandleInfo*)qi->pvData;
	//DWORD dwHandle = pi->dwHandle;

	char szBoard[21];
	strlcpy(szBoard, pi->login, sizeof(szBoard));
	int value = (int)pi->account_id;

	SQLResult* res = msg->Get();

	if (res->uiNumRows == 0)
	{
		// 새로운 하이스코어를 삽입
		char buf[256];
		snprintf(buf, sizeof(buf), "INSERT INTO highscore%s VALUES('%s', %u, %d)", GetTablePostfix(), szBoard, pi->player_id, value);
		CDBManager::instance().AsyncQuery(buf);
	}
	else
	{
		if (!res->pSQLResult)
		{
			delete pi;
			return;
		}

		MYSQL_ROW row = mysql_fetch_row(res->pSQLResult);
		if (row && row[0])
		{
			int current_value = 0; str_to_number(current_value, row[0]);
			if ((pi->account_index && current_value >= value) || (!pi->account_index && current_value <= value))
			{
				value = current_value;
			}
			else
			{
				char buf[256];
				snprintf(buf, sizeof(buf), "REPLACE INTO highscore%s VALUES('%s', %u, %d)", GetTablePostfix(), szBoard, pi->player_id, value);
				CDBManager::instance().AsyncQuery(buf);
			}
		}
		else
		{
			char buf[256];
			snprintf(buf, sizeof(buf), "INSERT INTO highscore%s VALUES('%s', %u, %d)", GetTablePostfix(), szBoard, pi->player_id, value);
			CDBManager::instance().AsyncQuery(buf);
		}
	}
	// TODO: 이곳에서 하이스코어가 업데이트 되었는지 체크하여 공지를 뿌려야한다.
	delete pi;
}

void CClientManager::InsertLogoutPlayer(DWORD pid)
{
	TLogoutPlayerMap::iterator it = m_map_logout.find(pid);

	// 존재하지 않을경우 추가
	if (it != m_map_logout.end())
	{
		// 존재할경우 시간만 갱신
		if (g_log)
			sys_log(0, "LOGOUT: Update player time pid(%d)", pid);

		it->second->time = time(0);
		return;
	}

	TLogoutPlayer* pLogout = new TLogoutPlayer;
	pLogout->pid = pid;
	pLogout->time = time(0);
	m_map_logout.insert(std::make_pair(pid, pLogout));

	if (g_log)
		sys_log(0, "LOGOUT: Insert player pid(%d)", pid);
}

void CClientManager::DeleteLogoutPlayer(DWORD pid)
{
	TLogoutPlayerMap::iterator it = m_map_logout.find(pid);

	if (it != m_map_logout.end())
	{
		delete it->second;
		m_map_logout.erase(it);
	}
}

extern int g_iLogoutSeconds;

void CClientManager::UpdateLogoutPlayer()
{
	time_t now = time(0);

	TLogoutPlayerMap::iterator it = m_map_logout.begin();

	while (it != m_map_logout.end())
	{
		TLogoutPlayer* pLogout = it->second;

		if (now - g_iLogoutSeconds > pLogout->time)
		{
			FlushItemCacheSet(pLogout->pid);
			FlushPlayerCacheSet(pLogout->pid);

			delete pLogout;
			m_map_logout.erase(it++);
		}
		else
			++it;
	}
}

void CClientManager::FlushPlayerCacheSet(DWORD pid)
{
	TPlayerTableCacheMap::iterator it = m_map_playerCache.find(pid);

	if (it != m_map_playerCache.end())
	{
		CPlayerTableCache* c = it->second;
		m_map_playerCache.erase(it);

		c->Flush();
		delete c;
	}
}
