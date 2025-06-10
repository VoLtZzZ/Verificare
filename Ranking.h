/**
* Filename: Ranking.h
* Author: Owsap
**/

#pragma once

#if defined(__RANKING_SYSTEM__)
#include "../../common/tables.h"

class CRanking
{
public:
	CRanking() = default;
	virtual ~CRanking() = default;

	static void Open(LPCHARACTER pChar, BYTE bType, BYTE bCategory);
	static void Register(DWORD dwPID, BYTE bType, BYTE bCategory, const TRankingData& rTable);

	static void Delete(BYTE bType, BYTE bCategory);
	static void DeleteByPID(DWORD dwPID, BYTE bType, BYTE bCategory);

public:
	enum ERankingType : BYTE
	{
		TYPE_RK_SOLO,
		TYPE_RK_PARTY,
		TYPE_RK_MAX
	};

	enum ESoloRanking : BYTE
	{
		SOLO_RK_CATEGORY_BF_WEAK,
		SOLO_RK_CATEGORY_BF_TOTAL,
		SOLO_RK_CATEGORY_MD_RED,
		SOLO_RK_CATEGORY_MD_BLUE,
		SOLO_RK_CATEGORY_UNKOWN4,
		SOLO_RK_CATEGORY_UNKOWN5,
		SOLO_RK_CATEGORY_BNW,
		SOLO_RK_CATEGORY_BATTLE_ROYALE,
		SOLO_RK_CATEGORY_WORLD_BOSS,
		SOLO_RK_CATEGORY_MAX
	};

	enum EPartyRanking : BYTE
	{
#if defined(__GUILD_DRAGONLAIR_PARTY_SYSTEM__)
		PARTY_RK_CATEGORY_GUILD_DRAGONLAIR_RED_ALL,
		PARTY_RK_CATEGORY_GUILD_DRAGONLAIR_RED_NOW_WEEK,
		PARTY_RK_CATEGORY_GUILD_DRAGONLAIR_RED_PAST_WEEK,
#endif
		PARTY_RK_CATEGORY_CZ_MOUSE,
		PARTY_RK_CATEGORY_CZ_COW,
		PARTY_RK_CATEGORY_CZ_TIGER,
		PARTY_RK_CATEGORY_CZ_RABBIT,
		PARTY_RK_CATEGORY_CZ_DRAGON,
		PARTY_RK_CATEGORY_CZ_SNAKE,
		PARTY_RK_CATEGORY_CZ_HORSE,
		PARTY_RK_CATEGORY_CZ_SHEEP,
		PARTY_RK_CATEGORY_CZ_MONKEY,
		PARTY_RK_CATEGORY_CZ_CHICKEN,
		PARTY_RK_CATEGORY_CZ_DOG,
		PARTY_RK_CATEGORY_CZ_PIG,
#if defined(__DEFENSE_WAVE__)
		PARTY_RK_CATEGORY_DEFENSE_WAVE,
#endif
		PARTY_RK_CATEGORY_MAX,
	};
};
#endif
