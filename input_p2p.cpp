#include "stdafx.h"

#include "config.h"
#include "desc_client.h"
#include "desc_manager.h"
#include "char.h"
#include "char_manager.h"
#include "p2p.h"
#include "guild.h"
#include "guild_manager.h"
#include "party.h"
#include "messenger_manager.h"
#include "empire_text_convert.h"
#include "unique_item.h"
#include "xmas_event.h"
#include "affect.h"
#include "castle.h"
#include "dev_log.h"
#include "locale_service.h"
#include "questmanager.h"
#include "pcbang.h"
#include "skill.h"
#include "threeway_war.h"

////////////////////////////////////////////////////////////////////////////////
// Input Processor
CInputP2P::CInputP2P()
{
	BindPacketInfo(&m_packetInfoGG);
}

void CInputP2P::Login(LPDESC d, const char* c_pData)
{
	P2P_MANAGER::instance().Login(d, (TPacketGGLogin*)c_pData);
}

void CInputP2P::Logout(LPDESC d, const char* c_pData)
{
	TPacketGGLogout* p = (TPacketGGLogout*)c_pData;
	P2P_MANAGER::instance().Logout(p->szName);
}

int CInputP2P::Relay(LPDESC d, const char* c_pData, size_t uiBytes)
{
	TPacketGGRelay* p = (TPacketGGRelay*)c_pData;

	if (uiBytes < sizeof(TPacketGGRelay) + p->lSize)
		return -1;

	if (p->lSize < 0)
	{
		sys_err("invalid packet length %d", p->lSize);
		d->SetPhase(PHASE_CLOSE);
		return -1;
	}

	sys_log(0, "InputP2P::Relay : %s size %d", p->szName, p->lSize);

	LPCHARACTER pkChr = CHARACTER_MANAGER::instance().FindPC(p->szName);

	const BYTE* c_pbData = (const BYTE*)(c_pData + sizeof(TPacketGGRelay));

	if (!pkChr)
	{
		sys_log(0, "Relay could not find %s", p->szName);
		return p->lSize;
	}

	if (*c_pbData == HEADER_GC_WHISPER)
	{
		char buf[1024];
		memcpy(buf, c_pbData, MIN(p->lSize, sizeof(buf)));
		TPacketGCWhisper* p2 = (TPacketGCWhisper*)buf;

		if (pkChr->IsBlockMode(BLOCK_WHISPER) && !IS_SET(p2->bType, WHISPER_TYPE_GM))
		{
			// 귓속말 거부 상태에서 귓속말 거부.
			return p->lSize;
		}

		// bType 상위 4비트: Empire 번호
		// bType 하위 4비트: EWhisperType
		BYTE bToEmpire = (p2->bType >> 4);
		p2->bType = p2->bType & 0x0F;
		if (p2->bType == 0x0F)
		{
			// 시스템 메세지 귓속말은 bType의 상위비트까지 모두 사용함.
			p2->bType = WHISPER_TYPE_SYSTEM;
		}
		else
		{
			if (!pkChr->IsEquipUniqueGroup(UNIQUE_GROUP_RING_OF_LANGUAGE))
			{
				if (bToEmpire >= 1 && bToEmpire <= 3 && pkChr->GetEmpire() != bToEmpire)
				{
					ConvertEmpireText(bToEmpire,
						buf + sizeof(TPacketGCWhisper),
						p2->wSize - sizeof(TPacketGCWhisper),
						10 + 2 * pkChr->GetSkillPower(SKILL_LANGUAGE1 + bToEmpire - 1));
				}
			}
		}

		pkChr->GetDesc()->Packet(buf, p->lSize);
	}
	else
		pkChr->GetDesc()->Packet(c_pbData, p->lSize);

	return p->lSize;
}

int CInputP2P::Notice(LPDESC d, const char* c_pData, size_t uiBytes)
{
	TPacketGGNotice* p = (TPacketGGNotice*)c_pData;

	if (uiBytes < sizeof(TPacketGGNotice) + p->lSize)
		return -1;

	if (p->lSize < 0)
	{
		sys_err("invalid packet length %d", p->lSize);
		d->SetPhase(PHASE_CLOSE);
		return -1;
	}

	char szBuf[256 + 1];
	strlcpy(szBuf, c_pData + sizeof(TPacketGGNotice), MIN(p->lSize + 1, sizeof(szBuf)));
	SendNotice(szBuf, p->bBigFont);
	return (p->lSize);
}

int CInputP2P::MonarchNotice(LPDESC d, const char* c_pData, size_t uiBytes)
{
	TPacketGGMonarchNotice* p = (TPacketGGMonarchNotice*)c_pData;

	if (uiBytes < p->lSize + sizeof(TPacketGGMonarchNotice))
		return -1;

	if (p->lSize < 0)
	{
		sys_err("invalid packet length %d", p->lSize);
		d->SetPhase(PHASE_CLOSE);
		return -1;
	}

	char szBuf[256 + 1];
	strlcpy(szBuf, c_pData + sizeof(TPacketGGMonarchNotice), MIN(p->lSize + 1, sizeof(szBuf)));
	SendMonarchNotice(p->bEmpire, szBuf);
	return (p->lSize);
}

int CInputP2P::MonarchTransfer(LPDESC d, const char* c_pData)
{
	TPacketMonarchGGTransfer* p = (TPacketMonarchGGTransfer*)c_pData;
	LPCHARACTER pTargetChar = CHARACTER_MANAGER::instance().FindByPID(p->dwTargetPID);

	if (pTargetChar != NULL)
	{
		unsigned int qIndex = quest::CQuestManager::instance().GetQuestIndexByName("monarch_transfer");

		if (qIndex != 0)
		{
			pTargetChar->SetQuestFlag("monarch_transfer.x", p->x);
			pTargetChar->SetQuestFlag("monarch_transfer.y", p->y);
			quest::CQuestManager::instance().Letter(pTargetChar->GetPlayerID(), qIndex, 0);
		}
	}

	return 0;
}

int CInputP2P::Guild(LPDESC d, const char* c_pData, size_t uiBytes)
{
	TPacketGGGuild* p = (TPacketGGGuild*)c_pData;
	uiBytes -= sizeof(TPacketGGGuild);
	c_pData += sizeof(TPacketGGGuild);

	CGuild* g = CGuildManager::instance().FindGuild(p->dwGuild);

	switch (p->bSubHeader)
	{
		case GUILD_SUBHEADER_GG_CHAT:
		{
			if (uiBytes < sizeof(TPacketGGGuildChat))
				return -1;

			TPacketGGGuildChat* p = (TPacketGGGuildChat*)c_pData;

			if (g)
				g->P2PChat(p->szText);

			return sizeof(TPacketGGGuildChat);
		}

		case GUILD_SUBHEADER_GG_SET_MEMBER_COUNT_BONUS:
		{
			if (uiBytes < sizeof(int))
				return -1;

			int iBonus = *((int*)c_pData);
			CGuild* pGuild = CGuildManager::instance().FindGuild(p->dwGuild);
			if (pGuild)
			{
				pGuild->SetMemberCountBonus(iBonus);
			}
			return sizeof(int);
		}
		default:
			sys_err("UNKNOWN GUILD SUB PACKET");
			break;
	}
	return 0;
}

struct FuncShout
{
	FuncShout(const char* c_szText, BYTE bEmpire
#if defined(__MESSENGER_BLOCK_SYSTEM__)
		, const char* c_szName
#endif
#if defined(__MULTI_LANGUAGE_SYSTEM__)
		, const char* c_szCountry
#endif
	) : m_szText(c_szText), m_bEmpire(bEmpire)
#if defined(__MESSENGER_BLOCK_SYSTEM__)
		, m_szName(c_szName)
#endif
#if defined(__MULTI_LANGUAGE_SYSTEM__)
		, m_szCountry(c_szCountry)
#endif
	{
	}

	void operator () (LPDESC d)
	{
		if (g_bGlobalShout)
		{
			if (!d->GetCharacter())
				return;
		}
		else
		{
			if (!d->GetCharacter() || (d->GetCharacter()->GetGMLevel() == GM_PLAYER && d->GetEmpire() != m_bEmpire))
				return;
		}

#if defined(__MESSENGER_BLOCK_SYSTEM__)
		if (CMessengerManager::instance().IsBlocked(d->GetCharacter()->GetName(), m_szName))
			return;
#endif

#if defined(__MULTI_LANGUAGE_SYSTEM__)
		packet_chat pack_chat;
		pack_chat.type = CHAT_TYPE_SHOUT;
		strlcpy(pack_chat.szCountry, m_szCountry, sizeof(pack_chat.szCountry));

		d->GetCharacter()->ChatPacket(pack_chat, "%s", m_szText);
#else
		d->GetCharacter()->ChatPacket(CHAT_TYPE_SHOUT, "%s", m_szText);
#endif
	}

	const char* m_szText;
	BYTE m_bEmpire;
#if defined(__MESSENGER_BLOCK_SYSTEM__)
	const char* m_szName;
#endif
#if defined(__MULTI_LANGUAGE_SYSTEM__)
	const char* m_szCountry;
#endif
};

void SendShout(const char* c_szText, BYTE bEmpire
#if defined(__MESSENGER_BLOCK_SYSTEM__)
	, const char* c_szName
#endif
#if defined(__MULTI_LANGUAGE_SYSTEM__)
	, const char* c_szCountry
#endif
)
{
	const DESC_MANAGER::DESC_SET& c_ref_set = DESC_MANAGER::instance().GetClientSet();
	std::for_each(c_ref_set.begin(), c_ref_set.end(), FuncShout(c_szText, bEmpire
#if defined(__MESSENGER_BLOCK_SYSTEM__)
		, c_szName
#endif
#if defined(__MULTI_LANGUAGE_SYSTEM__)
		, c_szCountry
#endif
	));
}

void CInputP2P::Shout(const char* c_pData)
{
	TPacketGGShout* p = (TPacketGGShout*)c_pData;
	SendShout(p->szText, p->bEmpire
#if defined(__MESSENGER_BLOCK_SYSTEM__)
		, p->szName
#endif
#if defined(__MULTI_LANGUAGE_SYSTEM__)
		, p->szCountry
#endif
	);
}

void CInputP2P::Disconnect(const char* c_pData)
{
	TPacketGGDisconnect* p = (TPacketGGDisconnect*)c_pData;

	LPDESC d = DESC_MANAGER::instance().FindByLoginName(p->szLogin);

	if (!d)
		return;

	if (!d->GetCharacter())
	{
		d->SetPhase(PHASE_CLOSE);
	}
	else
		d->DisconnectOfSameLogin();
}

void CInputP2P::Setup(LPDESC d, const char* c_pData)
{
	TPacketGGSetup* p = (TPacketGGSetup*)c_pData;
	sys_log(0, "P2P: Setup %s:%d", d->GetHostName(), p->wPort);
	d->SetP2P(d->GetHostName(), p->wPort, p->bChannel);
}

void CInputP2P::MessengerAdd(const char* c_pData)
{
	TPacketGGMessenger* p = (TPacketGGMessenger*)c_pData;
	sys_log(0, "P2P: Messenger Add %s %s", p->szAccount, p->szCompanion);
	CMessengerManager::instance().__AddToList(p->szAccount, p->szCompanion);
}

void CInputP2P::MessengerRemove(const char* c_pData)
{
	TPacketGGMessenger* p = (TPacketGGMessenger*)c_pData;
	sys_log(0, "P2P: Messenger Remove %s %s", p->szAccount, p->szCompanion);
	CMessengerManager::instance().__RemoveFromList(p->szAccount, p->szCompanion);
}

#if defined(__MESSENGER_BLOCK_SYSTEM__)
void CInputP2P::MessengerBlockAdd(const char* c_pData)
{
	TPacketGGMessenger* p = (TPacketGGMessenger*)c_pData;
	CMessengerManager::instance().__AddToBlockList(p->szAccount, p->szCompanion);
}

void CInputP2P::MessengerBlockRemove(const char* c_pData)
{
	TPacketGGMessenger* p = (TPacketGGMessenger*)c_pData;
	CMessengerManager::instance().__RemoveFromBlockList(p->szAccount, p->szCompanion);
}
#endif

void CInputP2P::FindPosition(LPDESC d, const char* c_pData)
{
	TPacketGGFindPosition* p = (TPacketGGFindPosition*)c_pData;
	LPCHARACTER ch = CHARACTER_MANAGER::instance().FindByPID(p->dwTargetPID);
	if (ch && ch->GetMapIndex() < 10000)
	{
		TPacketGGWarpCharacter pw;
		pw.header = HEADER_GG_WARP_CHARACTER;
		pw.pid = p->dwFromPID;
		pw.x = ch->GetX();
		pw.y = ch->GetY();
		d->Packet(&pw, sizeof(pw));
	}
}

void CInputP2P::WarpCharacter(const char* c_pData)
{
	TPacketGGWarpCharacter* p = (TPacketGGWarpCharacter*)c_pData;
	LPCHARACTER ch = CHARACTER_MANAGER::instance().FindByPID(p->pid);
	if (ch)
	{
		ch->WarpSet(p->x, p->y);
	}
}

void CInputP2P::GuildWarZoneMapIndex(const char* c_pData)
{
	TPacketGGGuildWarMapIndex* p = (TPacketGGGuildWarMapIndex*)c_pData;
	CGuildManager& gm = CGuildManager::instance();

	sys_log(0, "P2P: GuildWarZoneMapIndex g1(%u) vs g2(%u), mapIndex(%d)", p->dwGuildID1, p->dwGuildID2, p->lMapIndex);

	CGuild* g1 = gm.FindGuild(p->dwGuildID1);
	CGuild* g2 = gm.FindGuild(p->dwGuildID2);

	if (g1 && g2)
	{
		g1->SetGuildWarMapIndex(p->dwGuildID2, p->lMapIndex);
		g2->SetGuildWarMapIndex(p->dwGuildID1, p->lMapIndex);
	}
}

void CInputP2P::Transfer(const char* c_pData)
{
	TPacketGGTransfer* p = (TPacketGGTransfer*)c_pData;

	LPCHARACTER ch = CHARACTER_MANAGER::instance().FindPC(p->szName);

	if (ch)
		ch->WarpSet(p->lX, p->lY);
}

#if defined(__XMAS_EVENT_2008__)
void CInputP2P::XmasWarpSanta(const char* c_pData)
{
	TPacketGGXmasWarpSanta* p = (TPacketGGXmasWarpSanta*)c_pData;

	if (p->bChannel == g_bChannel && map_allow_find(p->lMapIndex))
	{
		int iNextSpawnDelay = 60;

		if (LC_IsYMIR())
			iNextSpawnDelay = 20 * 60;
		else
			iNextSpawnDelay = 50 * 60;

		xmas::SpawnSanta(p->lMapIndex, iNextSpawnDelay); // 50분있다가 새로운 산타가 나타남 (한국은 20분)

		TPacketGGXmasWarpSantaReply pack_reply;
		pack_reply.bHeader = HEADER_GG_XMAS_WARP_SANTA_REPLY;
		pack_reply.bChannel = g_bChannel;
		P2P_MANAGER::instance().Send(&pack_reply, sizeof(pack_reply));
	}
}

void CInputP2P::XmasWarpSantaReply(const char* c_pData)
{
	TPacketGGXmasWarpSantaReply* p = (TPacketGGXmasWarpSantaReply*)c_pData;

	if (p->bChannel == g_bChannel)
	{
		CharacterVectorInteractor vec;
		if (CHARACTER_MANAGER::instance().GetCharactersByRaceNum(xmas::MOB_XMAS_SANTA_VNUM, vec))
		{
			CharacterVectorInteractor::iterator it = vec.begin();
			while (it != vec.end())
				M2_DESTROY_CHARACTER(*it++);
		}
	}
}
#endif

void CInputP2P::LoginPing(LPDESC d, const char* c_pData)
{
	TPacketGGLoginPing* p = (TPacketGGLoginPing*)c_pData;

	if (!g_pkAuthMasterDesc) // If I am master, I have to broadcast
		P2P_MANAGER::instance().Send(p, sizeof(TPacketGGLoginPing), d);
}

// BLOCK_CHAT
void CInputP2P::BlockChat(const char* c_pData)
{
	TPacketGGBlockChat* p = (TPacketGGBlockChat*)c_pData;

	LPCHARACTER ch = CHARACTER_MANAGER::instance().FindPC(p->szName);

	if (ch)
	{
		sys_log(0, "BLOCK CHAT apply name %s dur %d", p->szName, p->lBlockDuration);
		ch->AddAffect(AFFECT_BLOCK_CHAT, POINT_NONE, 0, AFF_NONE, p->lBlockDuration, 0, true);
	}
	else
	{
		sys_log(0, "BLOCK CHAT fail name %s dur %d", p->szName, p->lBlockDuration);
	}
}
// END_OF_BLOCK_CHAT
//

void CInputP2P::PCBangUpdate(const char* c_pData)
{
	TPacketPCBangUpdate* p = (TPacketPCBangUpdate*)c_pData;

	CPCBangManager::instance().RequestUpdateIPList(p->ulPCBangID);
}

void CInputP2P::IamAwake(LPDESC d, const char* c_pData)
{
	std::string hostNames;
	P2P_MANAGER::instance().GetP2PHostNames(hostNames);
	sys_log(0, "P2P Awakeness check from %s. My P2P connection number is %d. and details...\n%s", d->GetHostName(), P2P_MANAGER::instance().GetDescCount(), hostNames.c_str());
}

int CInputP2P::Analyze(LPDESC d, BYTE bHeader, const char* c_pData)
{
	if (test_server)
		sys_log(0, "CInputP2P::Anlayze[Header %d]", bHeader);

	int iExtraLen = 0;

	switch (bHeader)
	{
		case HEADER_GG_SETUP:
			Setup(d, c_pData);
			break;

		case HEADER_GG_LOGIN:
			Login(d, c_pData);
			break;

		case HEADER_GG_LOGOUT:
			Logout(d, c_pData);
			break;

		case HEADER_GG_RELAY:
			if ((iExtraLen = Relay(d, c_pData, m_iBufferLeft)) < 0)
				return -1;
			break;

		case HEADER_GG_NOTICE:
			if ((iExtraLen = Notice(d, c_pData, m_iBufferLeft)) < 0)
				return -1;
			break;

		case HEADER_GG_SHUTDOWN:
			sys_err("Accept shutdown p2p command from %s.", d->GetHostName());
			Shutdown(10);
			break;

		case HEADER_GG_GUILD:
			if ((iExtraLen = Guild(d, c_pData, m_iBufferLeft)) < 0)
				return -1;
			break;

		case HEADER_GG_SHOUT:
			Shout(c_pData);
			break;

		case HEADER_GG_DISCONNECT:
			Disconnect(c_pData);
			break;

		case HEADER_GG_MESSENGER_ADD:
			MessengerAdd(c_pData);
			break;

		case HEADER_GG_MESSENGER_REMOVE:
			MessengerRemove(c_pData);
			break;

#if defined(__MESSENGER_BLOCK_SYSTEM__)
		case HEADER_GG_MESSENGER_BLOCK_ADD:
			MessengerBlockAdd(c_pData);
			break;

		case HEADER_GG_MESSENGER_BLOCK_REMOVE:
			MessengerBlockRemove(c_pData);
			break;
#endif

		case HEADER_GG_FIND_POSITION:
			FindPosition(d, c_pData);
			break;

		case HEADER_GG_WARP_CHARACTER:
			WarpCharacter(c_pData);
			break;

		case HEADER_GG_GUILD_WAR_ZONE_MAP_INDEX:
			GuildWarZoneMapIndex(c_pData);
			break;

		case HEADER_GG_TRANSFER:
			Transfer(c_pData);
			break;

#if defined(__XMAS_EVENT_2008__)
		case HEADER_GG_XMAS_WARP_SANTA:
			XmasWarpSanta(c_pData);
			break;

		case HEADER_GG_XMAS_WARP_SANTA_REPLY:
			XmasWarpSantaReply(c_pData);
			break;
#endif

		case HEADER_GG_RELOAD_CRC_LIST:
			LoadValidCRCList();
			break;

		case HEADER_GG_CHECK_CLIENT_VERSION:
			CheckClientVersion();
			break;

		case HEADER_GG_LOGIN_PING:
			LoginPing(d, c_pData);
			break;

		case HEADER_GG_BLOCK_CHAT:
			BlockChat(c_pData);
			break;

		case HEADER_GG_SIEGE:
		{
			TPacketGGSiege* pSiege = (TPacketGGSiege*)c_pData;
			castle_siege(pSiege->bEmpire, pSiege->bTowerCount);
		}
		break;

		case HEADER_GG_MONARCH_NOTICE:
			if ((iExtraLen = MonarchNotice(d, c_pData, m_iBufferLeft)) < 0)
				return -1;
			break;

		case HEADER_GG_MONARCH_TRANSFER:
			MonarchTransfer(d, c_pData);
			break;

		case HEADER_GG_PCBANG_UPDATE:
			PCBangUpdate(c_pData);
			break;

		case HEADER_GG_CHECK_AWAKENESS:
			IamAwake(d, c_pData);
			break;
	}

	return (iExtraLen);
}
