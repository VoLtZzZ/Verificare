#ifndef __INC_CHAR_H__
#define __INC_CHAR_H__

#include "../../common/stl.h"
#include "entity.h"
#include "FSM.h"
#include "horse_rider.h"
#include "vid.h"
#include "constants.h"
#include "affect.h"
#include "affect_flag.h"
#include "cube.h"
#include "mining.h"
#include "packet.h"

#if defined(__LUCKY_BOX__)
#	include "item_manager.h"
#endif
#if defined(__CHANGE_LOOK_SYSTEM__)
#	include "changelook.h"
#endif
#if defined(__MAILBOX__)
#	include "MailBox.h"
#endif
#if defined(__GEM_SHOP__)
#	include "GemShop.h"
#endif
#if defined(__RANKING_SYSTEM__)
#	include "Ranking.h"
#endif
#if defined(__MINI_GAME_RUMI__)
#	include "minigame_rumi.h"
#endif
#if defined(__MINI_GAME_YUTNORI__)
#	include "minigame_yutnori.h"
#endif
#if defined(__MINI_GAME_CATCH_KING__)
#	include "minigame_catchking.h"
#endif
#if defined(__FLOWER_EVENT__)
#	include "flower_event.h"
#endif
#if defined(__SUMMER_EVENT_ROULETTE__)
#	include "minigame_roulette.h"
#endif
#if defined(__INGAME_EVENT_MANAGER__)
#	include "ingame_event_manager.h"
#endif

#if defined(__GUILD_DRAGONLAIR_SYSTEM__)
#	include "guild_dragonlair.h"
#endif

class CBuffOnAttributes;
class CPetSystem;
#if defined(__LOOT_FILTER_SYSTEM__)
class CLootFilter;
#endif

#define INSTANT_FLAG_DEATH_PENALTY (1 << 0)
#define INSTANT_FLAG_SHOP (1 << 1)
#define INSTANT_FLAG_EXCHANGE (1 << 2)
#define INSTANT_FLAG_STUN (1 << 3)
#define INSTANT_FLAG_NO_REWARD (1 << 4)

#define AI_FLAG_NPC (1 << 0)
#define AI_FLAG_AGGRESSIVE (1 << 1)
#define AI_FLAG_HELPER (1 << 2)
#define AI_FLAG_STAYZONE (1 << 3)

#define SET_OVER_TIME(ch, time) (ch)->SetOverTime(time)

extern int g_nPortalLimitTime;

extern bool IS_SUMMON_ITEM(LPITEM item, int map_index = 0);
extern bool IS_SUMMONABLE_ZONE(int map_index);

extern bool IS_MONKEY_DUNGEON(int map_index);
extern bool IS_MAZE_DUNGEON(int map_index);

#if defined(__SNOW_DUNGEON__)
extern bool IS_SNOW_DUNGEON(int map_index);
#endif

#if defined(__ELEMENTAL_DUNGEON__)
extern bool IS_ELEMENTAL_DUNGEON(int map_index);
#endif

extern bool CAN_ENTER_ZONE(const LPCHARACTER& ch, int map_index);

enum
{
	MAIN_RACE_WARRIOR_M,
	MAIN_RACE_ASSASSIN_W,
	MAIN_RACE_SURA_M,
	MAIN_RACE_SHAMAN_W,
	MAIN_RACE_WARRIOR_W,
	MAIN_RACE_ASSASSIN_M,
	MAIN_RACE_SURA_W,
	MAIN_RACE_SHAMAN_M,
	MAIN_RACE_WOLFMAN_M,
	MAIN_RACE_MAX_NUM,
};

enum
{
	POISON_LENGTH = 30,
	BLEEDING_LENGTH = 30,
	STAMINA_PER_STEP = 1,
	SAFEBOX_PAGE_SIZE = 9,
	AI_CHANGE_ATTACK_POISITION_TIME_NEAR = 10000,
	AI_CHANGE_ATTACK_POISITION_TIME_FAR = 1000,
	AI_CHANGE_ATTACK_POISITION_DISTANCE = 100,
	SUMMON_MONSTER_COUNT = 3,
};

enum
{
	FLY_NONE,
	FLY_EXP,
	FLY_HP_MEDIUM,
	FLY_HP_BIG,
	FLY_SP_SMALL,
	FLY_SP_MEDIUM,
	FLY_SP_BIG,
	FLY_FIREWORK1,
	FLY_FIREWORK2,
	FLY_FIREWORK3,
	FLY_FIREWORK4,
	FLY_FIREWORK5,
	FLY_FIREWORK6,
	FLY_FIREWORK_CHRISTMAS,
	FLY_CHAIN_LIGHTNING,
	FLY_HP_SMALL,
	FLY_SKILL_MUYEONG,
#if defined(__QUIVER_SYSTEM__)
	FLY_QUIVER_ATTACK_NORMAL,
#endif
#if defined(__CONQUEROR_LEVEL__)
	FLY_ILGWANGPYO_NORMAL,
	FLY_ILGWANGPYO_MASTER,
	FLY_ILGWANGPYO_GRAND_MASTER,
	FLY_ILGWANGPYO_PERFECT_MASTER,
	FLY_CONQUEROR_EXP,
#endif
};

enum EDamageType
{
	DAMAGE_TYPE_NONE,
	DAMAGE_TYPE_NORMAL,
	DAMAGE_TYPE_NORMAL_RANGE,
	// 스킬
	DAMAGE_TYPE_MELEE,
	DAMAGE_TYPE_RANGE,
	DAMAGE_TYPE_FIRE,
	DAMAGE_TYPE_ICE,
	DAMAGE_TYPE_ELEC,
	DAMAGE_TYPE_MAGIC,
	DAMAGE_TYPE_POISON,
	DAMAGE_TYPE_SPECIAL,
	DAMAGE_TYPE_BLEEDING,
};

enum DamageFlag
{
	DAMAGE_NORMAL = (1 << 0),
	DAMAGE_POISON = (1 << 1),
	DAMAGE_DODGE = (1 << 2),
	DAMAGE_BLOCK = (1 << 3),
	DAMAGE_PENETRATE = (1 << 4),
	DAMAGE_CRITICAL = (1 << 5),
	DAMAGE_BLEEDING = (1 << 6),
};

enum EPKModes
{
	PK_MODE_PEACE,
	PK_MODE_REVENGE,
	PK_MODE_FREE,
	PK_MODE_PROTECT,
	PK_MODE_GUILD,
	PK_MODE_MAX_NUM
};

enum EPositions
{
	POS_DEAD,
	POS_SLEEPING,
	POS_RESTING,
	POS_SITTING,
	POS_FISHING,
	POS_FIGHTING,
	POS_MOUNTING,
	POS_STANDING
};

enum EBlockAction
{
	BLOCK_EXCHANGE = (1 << 0),
	BLOCK_PARTY_INVITE = (1 << 1),
	BLOCK_GUILD_INVITE = (1 << 2),
	BLOCK_WHISPER = (1 << 3),
	BLOCK_MESSENGER_INVITE = (1 << 4),
	BLOCK_PARTY_REQUEST = (1 << 5),
};

enum EAlignmentGrade
{
	ALIGN_GRADE_GOOD_4,
	ALIGN_GRADE_GOOD_3,
	ALIGN_GRADE_GOOD_2,
	ALIGN_GRADE_GOOD_1,
	ALIGN_GRADE_NORMAL,
	ALIGN_GRADE_EVIL_1,
	ALIGN_GRADE_EVIL_2,
	ALIGN_GRADE_EVIL_3,
	ALIGN_GRADE_EVIL_4,
};

enum EPointTypes
{
	POINT_NONE,								// 0
	POINT_LEVEL,							// 1
	POINT_VOICE,							// 2
	POINT_EXP,								// 3
	POINT_NEXT_EXP,							// 4
	POINT_HP,								// 5
	POINT_MAX_HP,							// 6
	POINT_SP,								// 7
	POINT_MAX_SP,							// 8
	POINT_STAMINA,							// 9 스테미너
	POINT_MAX_STAMINA,						// 10 최대 스테미너

	POINT_GOLD,								// 11
	POINT_ST,								// 12 근력
	POINT_HT,								// 13 체력
	POINT_DX,								// 14 민첩성
	POINT_IQ,								// 15 정신력
	POINT_DEF_GRADE,						// 16 ...
	POINT_ATT_SPEED,						// 17 공격속도
	POINT_ATT_GRADE,						// 18 공격력 MAX
	POINT_MOV_SPEED,						// 19 이동속도
	POINT_CLIENT_DEF_GRADE,					// 20 방어등급
	POINT_CASTING_SPEED,					// 21 주문속도 (쿨다운타임*100) / (100 + 이값) = 최종 쿨다운 타임
	POINT_MAGIC_ATT_GRADE,					// 22 마법공격력
	POINT_MAGIC_DEF_GRADE,					// 23 마법방어력
	POINT_EMPIRE_POINT,						// 24 제국점수
	POINT_LEVEL_STEP,						// 25 한 레벨에서의 단계.. (1 2 3 될 때 보상, 4 되면 레벨 업)
	POINT_STAT,								// 26 능력치 올릴 수 있는 개수
	POINT_SUB_SKILL,						// 27 보조 스킬 포인트
	POINT_SKILL,							// 28 액티브 스킬 포인트
	POINT_WEAPON_MIN,						// 29 무기 최소 데미지
	POINT_WEAPON_MAX,						// 30 무기 최대 데미지
	POINT_PLAYTIME,							// 31 플레이시간
	POINT_HP_REGEN,							// 32 HP 회복률
	POINT_SP_REGEN,							// 33 SP 회복률

	POINT_BOW_DISTANCE,						// 34 활 사정거리 증가치 (meter)

	POINT_HP_RECOVERY,						// 35 체력 회복 증가량
	POINT_SP_RECOVERY,						// 36 정신력 회복 증가량

	POINT_POISON_PCT,						// 37 독 확률
	POINT_STUN_PCT,							// 38 기절 확률
	POINT_SLOW_PCT,							// 39 슬로우 확률
	POINT_CRITICAL_PCT,						// 40 크리티컬 확률
	POINT_PENETRATE_PCT,					// 41 관통타격 확률
	POINT_CURSE_PCT,						// 42 저주 확률

	POINT_ATTBONUS_HUMAN,					// 43 인간에게 강함
	POINT_ATTBONUS_ANIMAL,					// 44 동물에게 데미지 % 증가
	POINT_ATTBONUS_ORC,						// 45 웅귀에게 데미지 % 증가
	POINT_ATTBONUS_MILGYO,					// 46 밀교에게 데미지 % 증가
	POINT_ATTBONUS_UNDEAD,					// 47 시체에게 데미지 % 증가
	POINT_ATTBONUS_DEVIL,					// 48 마귀(악마)에게 데미지 % 증가
	POINT_ATTBONUS_INSECT,					// 49 벌레족
	POINT_ATTBONUS_FIRE,					// 50 화염족
	POINT_ATTBONUS_ICE,						// 51 빙설족
	POINT_ATTBONUS_DESERT,					// 52 사막족
	POINT_ATTBONUS_MONSTER,					// 53 모든 몬스터에게 강함
	POINT_ATTBONUS_WARRIOR,					// 54 무사에게 강함
	POINT_ATTBONUS_ASSASSIN,				// 55 자객에게 강함
	POINT_ATTBONUS_SURA,					// 56 수라에게 강함
	POINT_ATTBONUS_SHAMAN,					// 57 무당에게 강함
	POINT_ATTBONUS_TREE,					// 58 나무에게 강함 20050729.myevan UNUSED5

	POINT_RESIST_WARRIOR,					// 59 무사에게 저항
	POINT_RESIST_ASSASSIN,					// 60 자객에게 저항
	POINT_RESIST_SURA,						// 61 수라에게 저항
	POINT_RESIST_SHAMAN,					// 62 무당에게 저항

	POINT_STEAL_HP,							// 63 생명력 흡수
	POINT_STEAL_SP,							// 64 정신력 흡수

	POINT_MANA_BURN_PCT,					// 65 마나 번

	/// 피해시 보너스 ///

	POINT_DAMAGE_SP_RECOVER,				// 66 공격당할 시 정신력 회복 확률

	POINT_BLOCK,							// 67 블럭율
	POINT_DODGE,							// 68 회피율

	POINT_RESIST_SWORD,						// 69
	POINT_RESIST_TWOHAND,					// 70
	POINT_RESIST_DAGGER,					// 71
	POINT_RESIST_BELL,						// 72
	POINT_RESIST_FAN,						// 73
	POINT_RESIST_BOW,						// 74 화살 저항 : 대미지 감소
	POINT_RESIST_FIRE,						// 75 화염 저항 : 화염공격에 대한 대미지 감소
	POINT_RESIST_ELEC,						// 76 전기 저항 : 전기공격에 대한 대미지 감소
	POINT_RESIST_MAGIC,						// 77 술법 저항 : 모든술법에 대한 대미지 감소
	POINT_RESIST_WIND,						// 78 바람 저항 : 바람공격에 대한 대미지 감소

	POINT_REFLECT_MELEE,					// 79 공격 반사

	/// 특수 피해시 ///
	POINT_REFLECT_CURSE,					// 80 저주 반사
	POINT_POISON_REDUCE,					// 81 독데미지 감소

	/// 적 소멸시 ///
	POINT_KILL_SP_RECOVER,					// 82 적 소멸시 MP 회복
	POINT_EXP_DOUBLE_BONUS,					// 83
	POINT_GOLD_DOUBLE_BONUS,				// 84
	POINT_ITEM_DROP_BONUS,					// 85

	/// 회복 관련 ///
	POINT_POTION_BONUS,						// 86
	POINT_KILL_HP_RECOVERY,					// 87

	POINT_IMMUNE_STUN,						// 88
	POINT_IMMUNE_SLOW,						// 89
	POINT_IMMUNE_FALL,						// 90
	//////////////////

	POINT_PARTY_ATTACKER_BONUS,				// 91
	POINT_PARTY_TANKER_BONUS,				// 92

	POINT_ATT_BONUS,						// 93
	POINT_DEF_BONUS,						// 94

	POINT_ATT_GRADE_BONUS,					// 95
	POINT_DEF_GRADE_BONUS,					// 96
	POINT_MAGIC_ATT_GRADE_BONUS,			// 97
	POINT_MAGIC_DEF_GRADE_BONUS,			// 98

	POINT_RESIST_NORMAL_DAMAGE,				// 99

	POINT_HIT_HP_RECOVERY,					// 100
	POINT_HIT_SP_RECOVERY,					// 101
	POINT_MANASHIELD,						// 102 흑신수호 스킬에 의한 마나쉴드 효과 정도

	POINT_PARTY_BUFFER_BONUS,				// 103
	POINT_PARTY_SKILL_MASTER_BONUS,			// 104

	POINT_HP_RECOVER_CONTINUE,				// 105
	POINT_SP_RECOVER_CONTINUE,				// 106

	POINT_STEAL_GOLD,						// 107
	POINT_POLYMORPH,						// 108 변신한 몬스터 번호
	POINT_MOUNT,							// 109 타고있는 몬스터 번호

	POINT_PARTY_HASTE_BONUS,				// 110
	POINT_PARTY_DEFENDER_BONUS,				// 111
	POINT_STAT_RESET_COUNT,					// 112 피의 단약 사용을 통한 스텟 리셋 포인트 (1당 1포인트 리셋가능)

	POINT_HORSE_SKILL,						// 113

	POINT_MALL_ATTBONUS,					// 114 공격력 +x%
	POINT_MALL_DEFBONUS,					// 115 방어력 +x%
	POINT_MALL_EXPBONUS,					// 116 경험치 +x%
	POINT_MALL_ITEMBONUS,					// 117 아이템 드롭율 x/10배
	POINT_MALL_GOLDBONUS,					// 118 돈 드롭율 x/10배

	POINT_MAX_HP_PCT,						// 119 최대생명력 +x%
	POINT_MAX_SP_PCT,						// 120 최대정신력 +x%

	POINT_SKILL_DAMAGE_BONUS,				// 121 스킬 데미지 *(100+x)%
	POINT_NORMAL_HIT_DAMAGE_BONUS,			// 122 평타 데미지 *(100+x)%

	// DEFEND_BONUS_ATTRIBUTES
	POINT_SKILL_DEFEND_BONUS,				// 123 스킬 방어 데미지
	POINT_NORMAL_HIT_DEFEND_BONUS,			// 124 평타 방어 데미지
	// END_OF_DEFEND_BONUS_ATTRIBUTES

	// PC_BANG_ITEM_ADD 
	POINT_PC_BANG_EXP_BONUS,				// 125 PC방 전용 경험치 보너스
	POINT_PC_BANG_DROP_BONUS,				// 126 PC방 전용 드롭률 보너스
	// END_PC_BANG_ITEM_ADD
	POINT_RAMADAN_CANDY_BONUS_EXP,			// 127 라마단 사탕 경험치 증가용

	POINT_ENERGY = 128,						// 128 기력

	// 기력 ui 용.
	// 서버에서 쓰지 않기만, 클라이언트에서 기력의 끝 시간을 POINT로 관리하기 때문에 이렇게 한다.
	// 아 부끄럽다
	POINT_ENERGY_END_TIME = 129,			// 129 기력 종료 시간

	POINT_COSTUME_ATTR_BONUS = 130,			// 130
	POINT_MAGIC_ATT_BONUS_PER = 131,		// 131
	POINT_MELEE_MAGIC_ATT_BONUS_PER = 132,	// 132

	// 추가 속성 저항
	POINT_RESIST_ICE = 133,					// 133 냉기 저항 : 얼음공격에 대한 대미지 감소
	POINT_RESIST_EARTH = 134,				// 134 대지 저항 : 얼음공격에 대한 대미지 감소
	POINT_RESIST_DARK = 135,				// 135 어둠 저항 : 얼음공격에 대한 대미지 감소

	POINT_RESIST_CRITICAL = 136,			// 136 크리티컬 저항 : 상대의 크리티컬 확률을 감소
	POINT_RESIST_PENETRATE = 137,			// 137 관통타격 저항 : 상대의 관통타격 확률을 감소

	POINT_BLEEDING_REDUCE = 138,			// 138
	POINT_BLEEDING_PCT = 139,				// 139
	POINT_ATTBONUS_WOLFMAN = 140,			// 140
	POINT_RESIST_WOLFMAN = 141,				// 141
	POINT_RESIST_CLAW = 142,				// 142

#if defined(__ACCE_COSTUME_SYSTEM__)
	POINT_ACCEDRAIN_RATE,
#endif
#if defined(__MAGIC_REDUCTION__)
	POINT_RESIST_MAGIC_REDUCTION,
#endif
#if defined(__CHEQUE_SYSTEM__)
	POINT_CHEQUE,
#endif
	POINT_BATTLE_POINT,
	POINT_RESIST_HUMAN,
	POINT_ENCHANT_ELECT,
	POINT_ENCHANT_FIRE,
	POINT_ENCHANT_ICE,
	POINT_ENCHANT_WIND,
	POINT_ENCHANT_EARTH,
	POINT_ENCHANT_DARK,
	POINT_ATTBONUS_CZ,
	POINT_BEAD,
#if defined(__GEM_SYSTEM__)
	POINT_GEM,
#endif
	POINT_ATTBONUS_SWORD,
	POINT_ATTBONUS_TWOHAND,
	POINT_ATTBONUS_DAGGER,
	POINT_ATTBONUS_BELL,
	POINT_ATTBONUS_FAN,
	POINT_ATTBONUS_BOW,
	POINT_ATTBONUS_CLAW,
	POINT_RESIST_MOUNT_FALL,
	POINT_RESIST_FIST,
	POINT_PREMIUM_EXPBONUS,
	POINT_PRIVILEGE_EXPBONUS,
	POINT_MARRIAGE_EXPBONUS,
	POINT_DEVILTOWER_EXPBONUS,
	POINT_PREMIUM_ITEMBONUS,
	POINT_PRIVILEGE_ITEMBONUS,
	POINT_PREMIUM_GOLDBONUS,
	POINT_PRIVILEGE_GOLDBONUS,
	POINT_SKILL_DAMAGE_SAMYEON,
	POINT_SKILL_DAMAGE_TANHWAN,
	POINT_SKILL_DAMAGE_PALBANG,
	POINT_SKILL_DAMAGE_GIGONGCHAM,
	POINT_SKILL_DAMAGE_GYOKSAN,
	POINT_SKILL_DAMAGE_GEOMPUNG,
	POINT_SKILL_DAMAGE_AMSEOP,
	POINT_SKILL_DAMAGE_GUNGSIN,
	POINT_SKILL_DAMAGE_CHARYUN,
	POINT_SKILL_DAMAGE_SANGONG,
	POINT_SKILL_DAMAGE_YEONSA,
	POINT_SKILL_DAMAGE_KWANKYEOK,
	POINT_SKILL_DAMAGE_GIGUNG,
	POINT_SKILL_DAMAGE_HWAJO,
	POINT_SKILL_DAMAGE_SWAERYUNG,
	POINT_SKILL_DAMAGE_YONGKWON,
	POINT_SKILL_DAMAGE_PABEOB,
	POINT_SKILL_DAMAGE_MARYUNG,
	POINT_SKILL_DAMAGE_HWAYEOMPOK,
	POINT_SKILL_DAMAGE_MAHWAN,
	POINT_SKILL_DAMAGE_BIPABU,
	POINT_SKILL_DAMAGE_YONGBI,
	POINT_SKILL_DAMAGE_PAERYONG,
	POINT_SKILL_DAMAGE_NOEJEON,
	POINT_SKILL_DAMAGE_BYEURAK,
	POINT_SKILL_DAMAGE_CHAIN,
	POINT_SKILL_DAMAGE_CHAYEOL,
	POINT_SKILL_DAMAGE_SALPOONG,
	POINT_SKILL_DAMAGE_GONGDAB,
	POINT_SKILL_DAMAGE_PASWAE,
	POINT_NORMAL_HIT_DEFEND_BONUS_BOSS_OR_MORE,
	POINT_SKILL_DEFEND_BONUS_BOSS_OR_MORE,
	POINT_NORMAL_HIT_DAMAGE_BONUS_BOSS_OR_MORE,
	POINT_SKILL_DAMAGE_BONUS_BOSS_OR_MORE,
	POINT_HIT_BUFF_ENCHANT_FIRE,
	POINT_HIT_BUFF_ENCHANT_ICE,
	POINT_HIT_BUFF_ENCHANT_ELEC,
	POINT_HIT_BUFF_ENCHANT_WIND,
	POINT_HIT_BUFF_ENCHANT_DARK,
	POINT_HIT_BUFF_ENCHANT_EARTH,
	POINT_HIT_BUFF_RESIST_FIRE,
	POINT_HIT_BUFF_RESIST_ICE,
	POINT_HIT_BUFF_RESIST_ELEC,
	POINT_HIT_BUFF_RESIST_WIND,
	POINT_HIT_BUFF_RESIST_DARK,
	POINT_HIT_BUFF_RESIST_EARTH,
	POINT_USE_SKILL_CHEONGRANG_MOV_SPEED,
	POINT_USE_SKILL_CHEONGRANG_CASTING_SPEED,
	POINT_USE_SKILL_CHAYEOL_CRITICAL_PCT,
	POINT_USE_SKILL_SANGONG_ATT_GRADE_BONUS,
	POINT_USE_SKILL_GIGUNG_ATT_GRADE_BONUS,
	POINT_USE_SKILL_JEOKRANG_DEF_BONUS,
	POINT_USE_SKILL_GWIGEOM_DEF_BONUS,
	POINT_USE_SKILL_TERROR_ATT_GRADE_BONUS,
	POINT_USE_SKILL_MUYEONG_ATT_GRADE_BONUS,
	POINT_USE_SKILL_MANASHILED_CASTING_SPEED,
	POINT_USE_SKILL_HOSIN_DEF_BONUS,
	POINT_USE_SKILL_GICHEON_ATT_GRADE_BONUS,
	POINT_USE_SKILL_JEONGEOP_ATT_GRADE_BONUS,
	POINT_USE_SKILL_JEUNGRYEOK_DEF_BONUS,
	POINT_USE_SKILL_GIHYEOL_ATT_GRADE_BONUS,
	POINT_USE_SKILL_CHUNKEON_CASTING_SPEED,
	POINT_USE_SKILL_NOEGEOM_ATT_GRADE_BONUS,
	POINT_SKILL_DURATION_INCREASE_EUNHYUNG,
	POINT_SKILL_DURATION_INCREASE_GYEONGGONG,
	POINT_SKILL_DURATION_INCREASE_GEOMKYUNG,
	POINT_SKILL_DURATION_INCREASE_JEOKRANG,
	POINT_USE_SKILL_PALBANG_HP_ABSORB,
	POINT_USE_SKILL_AMSEOP_HP_ABSORB,
	POINT_USE_SKILL_YEONSA_HP_ABSORB,
	POINT_USE_SKILL_YONGBI_HP_ABSORB,
	POINT_USE_SKILL_CHAIN_HP_ABSORB,
	POINT_USE_SKILL_PASWAE_SP_ABSORB,
	POINT_USE_SKILL_GIGONGCHAM_STUN,
	POINT_USE_SKILL_CHARYUN_STUN,
	POINT_USE_SKILL_PABEOB_STUN,
	POINT_USE_SKILL_MAHWAN_STUN,
	POINT_USE_SKILL_GONGDAB_STUN,
	POINT_USE_SKILL_SAMYEON_STUN,
	POINT_USE_SKILL_GYOKSAN_KNOCKBACK,
	POINT_USE_SKILL_SEOMJEON_KNOCKBACK,
	POINT_USE_SKILL_SWAERYUNG_KNOCKBACK,
	POINT_USE_SKILL_HWAYEOMPOK_KNOCKBACK,
	POINT_USE_SKILL_GONGDAB_KNOCKBACK,
	POINT_USE_SKILL_KWANKYEOK_KNOCKBACK,
	POINT_USE_SKILL_SAMYEON_NEXT_COOLTIME_DECREASE_10PER,
	POINT_USE_SKILL_GEOMPUNG_NEXT_COOLTIME_DECREASE_10PER,
	POINT_USE_SKILL_GUNGSIN_NEXT_COOLTIME_DECREASE_10PER,
	POINT_USE_SKILL_KWANKYEOK_NEXT_COOLTIME_DECREASE_10PER,
	POINT_USE_SKILL_YONGKWON_NEXT_COOLTIME_DECREASE_10PER,
	POINT_USE_SKILL_MARYUNG_NEXT_COOLTIME_DECREASE_10PER,
	POINT_USE_SKILL_BIPABU_NEXT_COOLTIME_DECREASE_10PER,
	POINT_USE_SKILL_NOEJEON_NEXT_COOLTIME_DECREASE_10PER,
	POINT_USE_SKILL_SALPOONG_NEXT_COOLTIME_DECREASE_10PER,
	POINT_USE_SKILL_PASWAE_NEXT_COOLTIME_DECREASE_10PER,
	POINT_ATTBONUS_STONE,
	POINT_DAMAGE_HP_RECOVERY,
	POINT_DAMAGE_SP_RECOVERY,
	POINT_ALIGNMENT_DAMAGE_BONUS,
	POINT_NORMAL_DAMAGE_GUARD,
	POINT_MORE_THEN_HP90_DAMAGE_REDUCE,
	POINT_USE_SKILL_TUSOK_HP_ABSORB,
	POINT_USE_SKILL_PAERYONG_HP_ABSORB,
	POINT_USE_SKILL_BYEURAK_HP_ABSORB,
	POINT_USE_SKILL_SAMYEON_NEXT_COOLTIME_DECREASE_20PER,
	POINT_USE_SKILL_GEOMPUNG_NEXT_COOLTIME_DECREASE_20PER,
	POINT_USE_SKILL_GUNGSIN_NEXT_COOLTIME_DECREASE_20PER,
	POINT_USE_SKILL_KWANKYEOK_NEXT_COOLTIME_DECREASE_20PER,
	POINT_USE_SKILL_YONGKWON_NEXT_COOLTIME_DECREASE_20PER,
	POINT_USE_SKILL_MARYUNG_NEXT_COOLTIME_DECREASE_20PER,
	POINT_USE_SKILL_BIPABU_NEXT_COOLTIME_DECREASE_20PER,
	POINT_USE_SKILL_NOEJEON_NEXT_COOLTIME_DECREASE_20PER,
	POINT_USE_SKILL_SALPOONG_NEXT_COOLTIME_DECREASE_20PER,
	POINT_USE_SKILL_PASWAE_NEXT_COOLTIME_DECREASE_20PER,
	POINT_USE_SKILL_CHAYEOL_HP_ABSORB,
	POINT_MEDAL_OF_HONOR,
	POINT_ALL_STAT_BONUS,
	POINT_SUNGMA_STR,
	POINT_SUNGMA_HP,
	POINT_SUNGMA_MOVE,
	POINT_SUNGMA_IMMUNE,
	POINT_CONQUEROR_LEVEL,
	POINT_CONQUEROR_LEVEL_STEP,
	POINT_CONQUEROR_EXP,
	POINT_CONQUEROR_NEXT_EXP,
	POINT_CONQUEROR_POINT,
	POINT_HIT_PCT,
	POINT_ATTBONUS_PER_HUMAN,
	POINT_ATTBONUS_PER_ANIMAL,
	POINT_ATTBONUS_PER_ORC,
	POINT_ATTBONUS_PER_MILGYO,
	POINT_ATTBONUS_PER_UNDEAD,
	POINT_ATTBONUS_PER_DEVIL,
	POINT_ENCHANT_PER_ELECT,
	POINT_ENCHANT_PER_FIRE,
	POINT_ENCHANT_PER_ICE,
	POINT_ENCHANT_PER_WIND,
	POINT_ENCHANT_PER_EARTH,
	POINT_ENCHANT_PER_DARK,
	POINT_ATTBONUS_PER_CZ,
	POINT_ATTBONUS_PER_INSECT,
	POINT_ATTBONUS_PER_DESERT,
	POINT_ATTBONUS_PER_STONE,
	POINT_ATTBONUS_PER_MONSTER,
	POINT_RESIST_PER_HUMAN,
	POINT_RESIST_PER_ICE,
	POINT_RESIST_PER_DARK,
	POINT_RESIST_PER_EARTH,
	POINT_RESIST_PER_FIRE,
	POINT_RESIST_PER_ELEC,
	POINT_RESIST_PER_MAGIC,
	POINT_RESIST_PER_WIND,
	POINT_HIT_BUFF_SUNGMA_STR,
	POINT_HIT_BUFF_SUNGMA_MOVE,
	POINT_HIT_BUFF_SUNGMA_HP,
	POINT_HIT_BUFF_SUNGMA_IMMUNE,
	POINT_MOUNT_MELEE_MAGIC_ATTBONUS_PER,
	POINT_DISMOUNT_MOVE_SPEED_BONUS_PER,
	POINT_HIT_AUTO_HP_RECOVERY,
	POINT_HIT_AUTO_SP_RECOVERY,
	POINT_USE_SKILL_COOLTIME_DECREASE_ALL,
	POINT_HIT_STONE_ATTBONUS_STONE,
	POINT_HIT_STONE_DEF_GRADE_BONUS,
	POINT_KILL_BOSS_ITEM_BONUS,
	POINT_MOB_HIT_MOB_AGGRESSIVE,
	POINT_NO_DEATH_AND_HP_RECOVERY30,
	POINT_AUTO_PICKUP,
	POINT_MOUNT_NO_KNOCKBACK,
	POINT_SUNGMA_PER_STR,
	POINT_SUNGMA_PER_HP,
	POINT_SUNGMA_PER_MOVE,
	POINT_SUNGMA_PER_IMMUNE,
	POINT_IMMUNE_POISON100,
	POINT_IMMUNE_BLEEDING100,
	POINT_MONSTER_DEFEND_BONUS,

	// 클라이언트 포인트
	POINT_MIN_WEP,
	POINT_MAX_WEP,
	POINT_MIN_MAGIC_WEP,
	POINT_MAX_MAGIC_WEP,
	POINT_HIT_RATE
};

// <Factor> Dynamically evaluated CHARACTER* equivalent.
// Referring to SCharDeadEventInfo.
struct DynamicCharacterPtr
{
	DynamicCharacterPtr() : is_pc(false), id(0) {}
	DynamicCharacterPtr(const DynamicCharacterPtr& o)
		: is_pc(o.is_pc), id(o.id) {}

	// Returns the LPCHARACTER found in CHARACTER_MANAGER.
	LPCHARACTER Get() const;
	// Clears the current settings.
	void Reset()
	{
		is_pc = false;
		id = 0;
	}

	// Basic assignment operator.
	DynamicCharacterPtr& operator=(const DynamicCharacterPtr& rhs)
	{
		is_pc = rhs.is_pc;
		id = rhs.id;
		return *this;
	}
	// Supports assignment with LPCHARACTER type.
	DynamicCharacterPtr& operator=(LPCHARACTER character);
	// Supports type casting to LPCHARACTER.
	operator LPCHARACTER() const
	{
		return Get();
	}

	bool is_pc;
	uint32_t id;
};

/* 저장하는 데이터 */
typedef struct character_point
{
	POINT_VALUE lPoints[POINT_MAX_NUM];

	BYTE bJob;
	BYTE bVoice;

	BYTE bLevel;
	DWORD dwExp;

#if defined(__CONQUEROR_LEVEL__)
	BYTE bConquerorLevel;
	DWORD dwConquerorExp;
#endif

	int iGold;
#if defined(__CHEQUE_SYSTEM__)
	int iCheque;
#endif
#if defined(__GEM_SYSTEM__)
	int iGem;
#endif

	int iHP, iSP;
	int iRandomHP, iRandomSP;
	int iStamina;

	BYTE bSkillGroup;
} CHARACTER_POINT;

/* 저장되지 않는 캐릭터 데이터 */
typedef struct character_point_instant
{
	POINT_VALUE points[POINT_MAX_NUM];

	float fRot;

	int iMaxHP;
	int iMaxSP;

	long position;

	long instant_flag;
	DWORD dwAIFlag;
	DWORD dwImmuneFlag;
	DWORD dwLastShoutPulse;

	DWORD adwParts[PART_MAX_NUM];

	LPITEM pInventoryItems[INVENTORY_MAX_NUM];
	WORD wInventoryItemGrid[INVENTORY_MAX_NUM];

	LPITEM pEquipmentItems[EQUIPMENT_MAX_NUM];
	BYTE bEquipmentItemGrid[EQUIPMENT_MAX_NUM];

#if defined(__DRAGON_SOUL_SYSTEM__)
	// 용혼석 인벤토리.
	LPITEM pDragonSoulInventoryItems[DRAGON_SOUL_INVENTORY_MAX_NUM];
	WORD wDragonSoulInventoryItemGrid[DRAGON_SOUL_INVENTORY_MAX_NUM];
#endif

	LPITEM pBeltInventoryItems[BELT_INVENTORY_MAX_NUM];
	BYTE bBeltInventoryItemGrid[BELT_INVENTORY_MAX_NUM];

#if !defined(__CUBE_RENEWAL__)
	// by mhh
	LPITEM pCubeItems[CUBE_MAX_NUM];
#endif
	LPCHARACTER pCubeNpc;
#if defined(__MOVE_COSTUME_ATTR__)
	LPCHARACTER pItemCombNpc;
#endif
#if defined(__SUMMER_EVENT_ROULETTE__)
	LPCHARACTER pRouletteNPC;
#endif
#if defined(__ATTR_6TH_7TH__)
	LPITEM pNPCStorageItems;
#endif

	BYTE gm_level;

	BYTE bBasePart; // 평상복 번호

	int iMaxStamina;

	BYTE bBlockMode;

	int iDragonSoulActiveDeck;
	LPENTITY m_pDragonSoulRefineWindowOpener;
#if defined(__ACCE_COSTUME_SYSTEM__)
	LPENTITY m_pAcceRefineWindowOpener;
#endif
#if defined(__AURA_COSTUME_SYSTEM__)
	LPENTITY m_pAuraRefineWindowOpener;
#endif
} CHARACTER_POINT_INSTANT;

#define TRIGGERPARAM LPCHARACTER ch, LPCHARACTER causer

typedef struct trigger
{
	BYTE type;
	int (*func) (TRIGGERPARAM);
	long value;
} TRIGGER;

class CTrigger
{
public:
	CTrigger() : bType(0), pFunc(NULL)
	{
	}

	BYTE bType;
	int (*pFunc) (TRIGGERPARAM);
};

EVENTINFO(char_event_info)
{
	DynamicCharacterPtr ch;
};

struct TSkillUseInfo
{
	int iHitCount;
	int iMaxHitCount;
	int iSplashCount;
	DWORD dwNextSkillUsableTime;
	int iRange;
	bool bUsed;
	DWORD dwVID;
	bool isGrandMaster;

	std::unordered_map<DWORD, std::size_t> TargetVIDMap;

	TSkillUseInfo()
		: iHitCount(0), iMaxHitCount(0), iSplashCount(0), dwNextSkillUsableTime(0), iRange(0), bUsed(false),
		dwVID(0), isGrandMaster(false)
	{}

	bool HitOnce(DWORD dwVnum = 0);

	bool UseSkill(bool isGrandMaster, DWORD vid, DWORD dwCooltime, int splashcount = 1, int hitcount = -1, int range = -1);
	DWORD GetMainTargetVID() const { return dwVID; }
	void SetMainTargetVID(DWORD vid) { dwVID = vid; }
	void ResetHitCount() { if (iSplashCount) { iHitCount = iMaxHitCount; iSplashCount--; } }
};

typedef struct packet_party_update TPacketGCPartyUpdate;
class CExchange;
class CSkillProto;
class CParty;
class CDungeon;
#if defined(__DEFENSE_WAVE__)
class CDefenseWave;
#endif
class CWarMap;
class CAffect;
class CGuild;
class CSafebox;
class CArena;

class CShop;
typedef class CShop* LPSHOP;

class CMob;
class CMobInstance;
typedef struct SMobSkillInfo TMobSkillInfo;

// SKILL_POWER_BY_LEVEL
extern int GetSkillPowerByLevelFromType(int job, int skillgroup, int skilllevel);
// END_SKILL_POWER_BY_LEVEL

namespace marriage
{
	class WeddingMap;
}
enum e_overtime
{
	OT_NONE,
	OT_3HOUR,
	OT_5HOUR,
};

typedef std::list<CAffect*> AffectContainerList;
typedef std::unordered_map<DWORD, BYTE> AffectStackMap;
typedef std::map<int, LPEVENT> MobSkillEventMap;

class CHARACTER : public CEntity, public CFSM, public CHorseRider
{
protected:
	//////////////////////////////////////////////////////////////////////////////////
	// Entity 관련
	virtual void EncodeInsertPacket(LPENTITY entity);
	virtual void EncodeRemovePacket(LPENTITY entity);
	//////////////////////////////////////////////////////////////////////////////////

public:
	LPCHARACTER FindCharacterInView(const char* name, bool bFindPCOnly);
	void UpdatePacket();

	//////////////////////////////////////////////////////////////////////////////////
	// FSM (Finite State Machine) 관련
protected:
	CStateTemplate<CHARACTER> m_stateMove;
	CStateTemplate<CHARACTER> m_stateBattle;
	CStateTemplate<CHARACTER> m_stateIdle;

public:
	virtual void StateMove();
	virtual void StateBattle();
	virtual void StateIdle();
	virtual void StateFlag();
	virtual void StateFlagBase();
	void StateHorse();

protected:
	// STATE_IDLE_REFACTORING
	void __StateIdle_Monster();
	void __StateIdle_Stone();
	void __StateIdle_NPC();
	// END_OF_STATE_IDLE_REFACTORING

public:
	DWORD GetAIFlag() const { return m_pointsInstant.dwAIFlag; }

	void SetAggressive(bool bSet = true);
	bool IsAggressive() const;

	void SetCoward();
	bool IsCoward() const;
	void CowardEscape();

	void SetNoAttackShinsu();
	bool IsNoAttackShinsu() const;

	void SetNoAttackChunjo();
	bool IsNoAttackChunjo() const;

	void SetNoAttackJinno();
	bool IsNoAttackJinno() const;

	void SetAttackMob();
	bool IsAttackMob() const;

	void SetNoMove();
	bool IsNoMove() const;

	virtual void BeginStateEmpty();
	virtual void EndStateEmpty() {}

	void Restart(BYTE bSubCMD);
	void RestartAtSamePos();

protected:
	DWORD m_dwStateDuration;
	//////////////////////////////////////////////////////////////////////////////////

public:
	CHARACTER();
	virtual ~CHARACTER();

	void Create(const char* c_pszName, DWORD vid, bool isPC);
	void Destroy();

	void Disconnect(const char* c_pszReason);

protected:
	void Initialize();

	//////////////////////////////////////////////////////////////////////////////////
	// Basic Points

public:
	DWORD GetPlayerID() const { return m_dwPlayerID; }

	void SetPlayerProto(const TPlayerTable* table);
	void CreatePlayerProto(TPlayerTable& tab); // 저장 시 사용

	void SetProto(const CMob* c_pkMob);
	WORD GetRaceNum() const;

	void Save(); // DelayedSave
	void SaveReal(); // 실제 저장
	void FlushDelayedSaveItem();

	const char* GetName() const;
	const VID& GetVID() const { return m_vid; }

	void SetName(const std::string& name) { m_stName = name; }

	void SetRace(BYTE race);
	bool ChangeSex();

	bool IsFemale() const;
	bool IsMale() const;

	DWORD GetAID() const;
	int GetChangeEmpireCount() const;
	void SetChangeEmpireCount();
	int ChangeEmpire(BYTE empire);

	BYTE GetJob() const;
	BYTE GetCharType() const;

	bool IsPC() const { return GetDesc() ? true : false; }
	bool IsNPC() const { return m_bCharType != CHAR_TYPE_PC; }
	bool IsMonster() const { return m_bCharType == CHAR_TYPE_MONSTER; }
	bool IsStone() const { return m_bCharType == CHAR_TYPE_STONE; }
	bool IsDoor() const { return m_bCharType == CHAR_TYPE_DOOR; }
	bool IsBuilding() const { return m_bCharType == CHAR_TYPE_BUILDING; }
	bool IsWarp() const { return m_bCharType == CHAR_TYPE_WARP; }
	bool IsGoto() const { return m_bCharType == CHAR_TYPE_GOTO; }
	bool IsHorse() const { return m_bCharType == CHAR_TYPE_HORSE; }
	bool IsPetPay() const { return m_bCharType == CHAR_TYPE_PET_PAY; }
	//bool IsPet() const { return m_bCharType == CHAR_TYPE_PET; }

	DWORD GetLastShoutPulse() const { return m_pointsInstant.dwLastShoutPulse; }
	void SetLastShoutPulse(DWORD pulse) { m_pointsInstant.dwLastShoutPulse = pulse; }

	BYTE GetGMLevel() const;
	BOOL IsGM() const;
	void SetGMLevel();

	void SetLevel(BYTE bValue);
	BYTE GetLevel() const { return m_points.bLevel; }

	void SetExp(DWORD dwValue) { m_points.dwExp = dwValue; }
	DWORD GetExp() const { return m_points.dwExp; }
	DWORD GetNextExp() const;

#if defined(__CONQUEROR_LEVEL__)
	void SetConqueror(bool bSet = true);

	void SetConquerorLevel(BYTE bValue) { m_points.bConquerorLevel = bValue; }
	BYTE GetConquerorLevel() const { return m_points.bConquerorLevel; }

	void SetConquerorExp(DWORD dwValue) { m_points.dwConquerorExp = dwValue; }
	DWORD GetConquerorExp() const { return m_points.dwConquerorExp; }
	DWORD GetNextConquerorExp() const;
#endif

	LPCHARACTER DistributeExp(); // 제일 많이 때린 사람을 리턴한다.

	void DistributeHP(LPCHARACTER pkKiller);
	void DistributeSP(LPCHARACTER pkKiller, int iMethod = 0);

	void SetPosition(int pos);
	bool IsPosition(int pos) const { return m_pointsInstant.position == pos ? true : false; }
	int GetPosition() const { return m_pointsInstant.position; }

	void SetPart(BYTE bPartPos, DWORD dwVal);
	DWORD GetPart(BYTE bPartPos) const;
	DWORD GetOriginalPart(BYTE bPartPos) const;

	void SetHP(int val) { m_points.iHP = val; }
	int GetHP() const { return m_points.iHP; }

	void SetSP(int val) { m_points.iSP = val; }
	int GetSP() const { return m_points.iSP; }

	void SetMaxHP(int val) { m_pointsInstant.iMaxHP = val; }
	int GetMaxHP() const { return m_pointsInstant.iMaxHP; }

	void SetMaxSP(int val) { m_pointsInstant.iMaxSP = val; }
	int GetMaxSP() const { return m_pointsInstant.iMaxSP; }

	void SetStamina(int iValue) { m_points.iStamina = iValue; }
	int GetStamina() const { return m_points.iStamina; }

	void SetMaxStamina(int iValue) { m_pointsInstant.iMaxStamina = iValue; }
	int GetMaxStamina() const { return m_pointsInstant.iMaxStamina; }

	void SetRandomHP(int iValue) { m_points.iRandomHP = iValue; }
	int GetRandomHP() const { return m_points.iRandomHP; }

	void SetRandomSP(int iValue) { m_points.iRandomSP = iValue; }
	int GetRandomSP() const { return m_points.iRandomSP; }

	int GetHPPct() const;

	void SetRealPoint(POINT_TYPE wPointType, POINT_VALUE lPointValue);
	POINT_VALUE GetRealPoint(POINT_TYPE wPointType) const;

	void SetPoint(POINT_TYPE wPointType, POINT_VALUE lPointValue);
	POINT_VALUE GetPoint(POINT_TYPE wPointType) const;

	POINT_VALUE GetLimitPoint(POINT_TYPE wPointType) const;
	POINT_VALUE GetPolymorphPoint(POINT_TYPE wPointType) const;

	const TMobTable& GetMobTable() const;
	BYTE GetMobRank() const;
	BYTE GetMobType() const;
	BYTE GetMobBattleType() const;
	BYTE GetMobSize() const;
	DWORD GetMobDamageMin() const;
	DWORD GetMobDamageMax() const;
	WORD GetMobAttackRange() const;
	DWORD GetMobDropItemVnum() const;
	float GetMobDamageMultiply() const;
#if defined(__ELEMENT_SYSTEM__)
	int GetMobElement(BYTE bElement) const;
#endif
	float GetMonsterHitRange() const;

	// NEWAI
	bool IsBerserker() const;
	bool IsBerserk() const;
	void SetBerserk(bool mode);

	bool IsStoneSkinner() const;

	bool IsGodSpeeder() const;
	bool IsGodSpeed() const;
	void SetGodSpeed(bool mode);

	bool IsDeathBlower() const;
	bool IsDeathBlow() const;

	bool IsHealer() const;
	bool IsFaller() const;

	bool IsReviver() const;
	bool HasReviverInParty() const;
	bool IsRevive() const;
	void SetRevive(bool mode);
	// NEWAI END

	bool IsRaceFlag(DWORD dwBit) const;
	bool IsSummonMonster() const;
	DWORD GetSummonVnum() const;

	int m_newSummonInterval;
	int m_lastSummonTime;

	bool CanSummonMonster() const;
	void MarkSummonedMonster();

	DWORD GetPolymorphItemVnum() const;
	DWORD GetMonsterDrainSPPoint() const;

	void MainCharacterPacket(); // 내가 메인캐릭터라고 보내준다.

	void ComputePoints();
	void ComputeBattlePoints();

	void PointChange(POINT_TYPE wPointType, POINT_VALUE lPointAmount, bool bAmount = false, bool bBroadcast = false);
	void PointsPacket();
	void UpdatePointsPacket(POINT_TYPE wPointType, POINT_VALUE lPointValue, POINT_VALUE lPointAmount = 0, bool bAmount = false, bool bBroadcast = false);

	void ApplyPoint(POINT_TYPE wApplyType, POINT_VALUE lApplyValue);
	void CheckMaximumPoints(); // HP, SP 등의 현재 값이 최대값 보다 높은지 검사하고 높다면 낮춘다.


	bool Show(long lMapIndex, long x, long y, long z = LONG_MAX, bool bShowSpawnMotion = false
#if defined(__WJ_SHOW_MOB_INFO__)
		, bool bAggressive = false
#endif
	);

	void Sitdown(int is_ground);
	void Standup();

	void SetRotation(float fRot);
	void SetRotationToXY(long x, long y);
	float GetRotation() const { return m_pointsInstant.fRot; }

	void MotionPacketEncode(BYTE motion, LPCHARACTER victim, struct packet_motion* packet);
	void Motion(BYTE motion, LPCHARACTER victim = NULL);

	void ChatPacket(BYTE type, const char* format, ...);
#if defined(__MULTI_LANGUAGE_SYSTEM__)
	void ChatPacket(packet_chat pack_chat, const char* format, ...);
#endif
	void MonsterChat(BYTE bMonsterChatType);
	void SendGreetMessage();

	void ResetPoint(int iLv);
	void ResetExp();

#if defined(__CONQUEROR_LEVEL__)
	void ResetConquerorPoint(int iLv);
	void ResetConquerorExp();
#endif

	void SetBlockMode(BYTE bFlag);
	void SetBlockModeForce(BYTE bFlag);
	bool IsBlockMode(BYTE bFlag) const { return (m_pointsInstant.bBlockMode & bFlag) ? true : false; }

	bool IsPolymorphed() const { return m_dwPolymorphRace > 0; }
	bool IsPolyMaintainStat() const { return m_bPolyMaintainStat; } // 이전 스텟을 유지하는 폴리모프.
	void SetPolymorph(DWORD dwRaceNum, bool bMaintainStat = false);
	DWORD GetPolymorphVnum() const { return m_dwPolymorphRace; }
	int GetPolymorphPower() const;

	// FISING
	void fishing();
	void fishing_take();
	bool IsFishing() const { return m_pkFishingEvent ? true : false; }
	// END_OF_FISHING

	// MINING
	void mining(LPCHARACTER chLoad);
	void mining_cancel();
	void mining_take();
	bool IsMining() const { return m_pkMiningEvent ? true : false; }
	// END_OF_MINING

	void ResetPlayTime(DWORD dwTimeRemain = 0);

	void CreateFly(BYTE bType, LPCHARACTER pkVictim);

	void ResetChatCounter() { m_bChatCounter = 0; }
	void IncreaseChatCounter() { ++m_bChatCounter; }
	BYTE GetChatCounter() const { return m_bChatCounter; }

	void ResetWhisperCounter() { m_bWhisperCounter = 0; }
	bool IncreaseWhisperCounter() { ++m_bWhisperCounter; return m_bWhisperCounter; }
	BYTE GetWhisperCounter() const { return m_bWhisperCounter; }

protected:
	DWORD m_dwPolymorphRace;
	bool m_bPolyMaintainStat;
	DWORD m_dwLoginPlayTime;
	DWORD m_dwPlayerID;
	VID m_vid;
	std::string m_stName;
	BYTE m_bCharType;

	CHARACTER_POINT m_points;
	CHARACTER_POINT_INSTANT m_pointsInstant;

	int m_iMoveCount;
	DWORD m_dwPlayStartTime;
	BYTE m_bAddChrState;
	bool m_bSkipSave;
	BYTE m_bChatCounter;
	BYTE m_bWhisperCounter;

	// End of Basic Points

	//////////////////////////////////////////////////////////////////////////////////
	// Move & Synchronize Positions
	//////////////////////////////////////////////////////////////////////////////////
public:
	bool IsStateMove() const { return IsState((CState&)m_stateMove); }
	bool IsStateIdle() const { return IsState((CState&)m_stateIdle); }
	bool IsWalking() const { return m_bNowWalking || GetStamina() <= 0; }
	void SetWalking(bool bWalkFlag) { m_bWalking = bWalkFlag; }
	void SetNowWalking(bool bWalkFlag);
	void ResetWalking() { SetNowWalking(m_bWalking); }

	bool Goto(long x, long y); // 바로 이동 시키지 않고 목표 위치로 BLENDING 시킨다.
	void Stop();

	bool CanMove() const; // 이동할 수 있는가?

	void SyncPacket();
	bool Sync(long x, long y); // 실제 이 메소드로 이동 한다 (각 종 조건에 의한 이동 불가가 없음)
	bool Move(long x, long y); // 조건을 검사하고 Sync 메소드를 통해 이동 한다.
	void OnMove(bool bIsAttack = false); // 움직일때 불린다. Move() 메소드 이외에서도 불릴 수 있다.
	DWORD GetMotionMode() const;
	float GetMoveMotionSpeed() const;
	float GetMoveSpeed() const;
	void CalculateMoveDuration();
	void SendMovePacket(BYTE bFunc, BYTE bArg, DWORD x, DWORD y, DWORD dwDuration, DWORD dwTime = 0, int iRot = -1);

	DWORD GetCurrentMoveDuration() const { return m_dwMoveDuration; }
	DWORD GetWalkStartTime() const { return m_dwWalkStartTime; }
	DWORD GetLastMoveTime() const { return m_dwLastMoveTime; }
	DWORD GetLastAttackTime() const { return m_dwLastAttackTime; }

	void SetLastAttacked(DWORD time); // 마지막으로 공격받은 시간 및 위치를 저장함

	bool SetSyncOwner(LPCHARACTER ch, bool bRemoveFromList = true);
	bool IsSyncOwner(LPCHARACTER ch) const;

	bool WarpSet(long x, long y, long lRealMapIndex = 0);
	void SetWarpLocation(long lMapIndex, long x, long y);
	void WarpEnd();
	const PIXEL_POSITION& GetWarpPosition() const { return m_posWarp; }
	bool WarpToPID(DWORD dwPID, bool bWarpForce = false);

	void SaveExitLocation();
	void ExitToSavedLocation();

	void StartStaminaConsume();
	void StopStaminaConsume();
	bool IsStaminaConsume() const;
	bool IsStaminaHalfConsume() const;

	void ResetStopTime();
	DWORD GetStopTime() const;

#if defined(__MOVE_CHANNEL__)
	bool MoveChannel(long lNewAddr, WORD wNewPort);
	bool StartMoveChannel(long lNewAddr, WORD wNewPort);
#endif

protected:
	void ClearSync();

	float m_fSyncTime;
	LPCHARACTER m_pkChrSyncOwner;
	CHARACTER_LIST m_kLst_pkChrSyncOwned; // 내가 SyncOwner인 자들

	PIXEL_POSITION m_posDest;
	PIXEL_POSITION m_posStart;
	PIXEL_POSITION m_posWarp;
	long m_lWarpMapIndex;

	PIXEL_POSITION m_posExit;
	long m_lExitMapIndex;

	DWORD m_dwMoveStartTime;
	DWORD m_dwMoveDuration;

	DWORD m_dwLastMoveTime;
	DWORD m_dwLastAttackTime;
	DWORD m_dwWalkStartTime;
	DWORD m_dwStopTime;

	bool m_bWalking;
	bool m_bNowWalking;
	bool m_bStaminaConsume;

	// End

	// Quickslot 관련
public:
	void SyncQuickslot(BYTE bType, WORD wOldPos, WORD wNewPos);
	bool GetQuickslot(BYTE pos, TQuickslot** ppSlot);
	bool SetQuickslot(BYTE pos, TQuickslot& rSlot);
	bool DelQuickslot(BYTE pos);
	bool SwapQuickslot(BYTE a, BYTE b);
	void ChainQuickslotItem(LPITEM pItem, BYTE bType, WORD wOldPos);
	void MoveQuickSlotItem(BYTE bOldType, WORD wOldPos, BYTE bNewType, WORD wNewPos);

	void CheckQuickSlotItems();
	bool CanAddToQuickSlot(LPITEM pItem);

protected:
	TQuickslot m_quickslot[QUICKSLOT_MAX_NUM];

#if defined(__LUCKY_BOX__)
public:
	void SetLuckyBoxSrcItem(LPITEM lpItem);
	void SendLuckyBoxInfo();
	void LuckyBoxRetry();
	void LuckyBoxReceive();
	int GetLuckyBoxPrice() const;
	bool IsLuckyBoxOpen() const;
	void ResetLuckyBoxData();

private:
	struct
	{
		DWORD dwSrcItemVNum;
		DWORD dwSrcItemID;
		WORD wSrcSlotIndex;
		BYTE bTryCount;
		DWORD dwItemVNum;
		BYTE bItemCount;
	} m_sLuckyBox;
#endif

	////////////////////////////////////////////////////////////////////////////////////////
	// Affect
public:
	void StartAffectEvent();
	void ClearAffect(bool bSave = false);
	void ComputeAffect(const CAffect* pkAff, bool bAdd);
	bool AddAffect(DWORD dwType, POINT_TYPE wApplyOn, POINT_VALUE lApplyValue, DWORD dwFlag, long lDuration, long lSPCost, bool bOverride, bool IsCube = false
#if defined(__AFFECT_RENEWAL__)
		, bool bRealTime = false
#endif
#if defined(__9TH_SKILL__)
		, long lValue = 0 /* Skill iAmount2 */
#endif
	);
#if defined(__AFFECT_RENEWAL__)
	bool AddRealTimeAffect(DWORD dwType, POINT_TYPE wApplyOn, POINT_VALUE lApplyValue, DWORD dwFlag, long lDuration, long lSPCost, bool bOverride, bool IsCube = false, bool bRealTime = true);
#endif
	void RefreshAffect();
	bool RemoveAffect(DWORD dwType);
#if defined(__SOUL_SYSTEM__)
	void RemoveAffect(DWORD dwType, POINT_TYPE wApplyType);
#endif
	bool IsAffectFlag(DWORD dwAff) const;

	bool UpdateAffect(); // called from EVENT
	int ProcessAffect();

	void LoadAffect(DWORD dwCount, TPacketAffectElement* pElements);
	void SaveAffect();

public:
	// Affect loading이 끝난 상태인가?
	bool IsLoadedAffect() const { return m_bIsLoadedAffect; }

	bool IsGoodAffect(BYTE bAffectType) const;

	void RemoveGoodAffect();
	void RemoveBadAffect();

	CAffect* FindAffect(DWORD dwType, POINT_TYPE wApplyType = APPLY_NONE) const;
	const AffectContainerList& GetAffectContainer() const { return m_list_pkAffect; }
	bool RemoveAffect(CAffect* pkAff);

	//void SetAffectStack(CAffect* pkAff, BYTE value);
	//BYTE GetAffectStack(CAffect* pkAff);
	//void ClearAffectStack(CAffect* pkAff);
	//
	//AffectStackMap m_map_affectStack;

protected:
	bool m_bIsLoadedAffect;
	TAffectFlag m_afAffectFlag;
	AffectContainerList m_list_pkAffect;

public:
	// PARTY_JOIN_BUG_FIX
	void SetParty(LPPARTY pkParty);
	LPPARTY GetParty() const { return m_pkParty; }

	bool RequestToParty(LPCHARACTER leader);
	void DenyToParty(LPCHARACTER member);
	void AcceptToParty(LPCHARACTER member);

	/// 자신의 파티에 다른 character 를 초대한다.
	/**
	* @param pchInvitee 초대할 대상 character. 파티에 참여 가능한 상태이어야 한다.
	*
	* 양측 character 의 상태가 파티에 초대하고 초대받을 수 있는 상태가 아니라면 초대하는 캐릭터에게 해당하는 채팅 메세지를 전송한다.
	**/
	void PartyInvite(LPCHARACTER pchInvitee);

	/// 초대했던 character 의 수락을 처리한다.
	/**
	* @param pchInvitee 파티에 참여할 character. 파티에 참여가능한 상태이어야 한다.
	*
	* pchInvitee 가 파티에 가입할 수 있는 상황이 아니라면 해당하는 채팅 메세지를 전송한다.
	**/
	void PartyInviteAccept(LPCHARACTER pchInvitee);

	/// 초대했던 character 의 초대 거부를 처리한다.
	/**
	* @param [in] dwPID 초대 했던 character 의 PID
	**/
	void PartyInviteDeny(DWORD dwPID);

	bool BuildUpdatePartyPacket(TPacketGCPartyUpdate& out);
	int GetLeadershipSkillLevel() const;
#if defined(__PARTY_PROFICY__)
	int GetRoleProficiencySkillLevel() const;
#endif
#if defined(__PARTY_INSIGHT__)
	int GetInSightSkillLevel() const;
#endif

	bool CanSummon(int iLeaderShip);

	void SetPartyRequestEvent(LPEVENT pkEvent) { m_pkPartyRequestEvent = pkEvent; }

protected:

	/// 파티에 가입한다.
	/**
	* @param pkLeader 가입할 파티의 리더
	**/
	void PartyJoin(LPCHARACTER pkLeader);

	/**
	* 파티 가입을 할 수 없을 경우의 에러코드.
	* Error code 는 시간에 의존적인가에 따라 변경가능한(mutable) type 과 정적(static) type 으로 나뉜다.
	* Error code 의 값이 PERR_SEPARATOR 보다 낮으면 변경가능한 type 이고 높으면 정적 type 이다.
	**/
	enum PartyJoinErrCode
	{
		PERR_NONE = 0, ///< 처리성공
		PERR_SERVER, ///< 서버문제로 파티관련 처리 불가
		PERR_DUNGEON, ///< 캐릭터가 던전에 있음
		PERR_OBSERVER, ///< 관전모드임
		PERR_LVBOUNDARY, ///< 상대 캐릭터와 레벨차이가 남
		PERR_LOWLEVEL, ///< 상대파티의 최고레벨보다 30레벨 낮음
		PERR_HILEVEL, ///< 상대파티의 최저레벨보다 30레벨 높음
		PERR_ALREADYJOIN, ///< 파티가입 대상 캐릭터가 이미 파티중
		PERR_PARTYISFULL, ///< 파티인원 제한 초과
		PERR_SEPARATOR, ///< Error type separator.
		PERR_DIFFEMPIRE, ///< 상대 캐릭터와 다른 제국임
		PERR_MAX ///< Error code 최고치. 이 앞에 Error code 를 추가한다.
	};

	/// 파티 가입이나 결성 가능한 조건을 검사한다.
	/**
	* @param pchLeader 파티의 leader 이거나 초대한 character
	* @param pchGuest 초대받는 character
	* @return 모든 PartyJoinErrCode 가 반환될 수 있다.
	**/
	static PartyJoinErrCode IsPartyJoinableCondition(const LPCHARACTER pchLeader, const LPCHARACTER pchGuest);

	/// 파티 가입이나 결성 가능한 동적인 조건을 검사한다.
	/**
	* @param pchLeader 파티의 leader 이거나 초대한 character
	* @param pchGuest 초대받는 character
	* @return mutable type 의 code 만 반환한다.
	**/
	static PartyJoinErrCode IsPartyJoinableMutableCondition(const LPCHARACTER pchLeader, const LPCHARACTER pchGuest);

	LPPARTY m_pkParty;
	DWORD m_dwLastDeadTime;
	LPEVENT m_pkPartyRequestEvent;

	/**
	* 파티초청 Event map.
	* key: 초대받은 캐릭터의 PID
	* value: event의 pointer
	*
	* 초대한 캐릭터들에 대한 event map.
	**/
	typedef std::map<DWORD, LPEVENT> EventMap;
	EventMap m_PartyInviteEventMap;

	// END_OF_PARTY_JOIN_BUG_FIX

	////////////////////////////////////////////////////////////////////////////////////////
	// Dungeon
public:
	void SetDungeon(LPDUNGEON pkDungeon);
	LPDUNGEON GetDungeon() const { return m_pkDungeon; }
	LPDUNGEON GetDungeonForce() const;
protected:
	LPDUNGEON m_pkDungeon;
	int m_iEventAttr;

	////////////////////////////////////////////////////////////////////////////////////////
	// Guild
public:
	void SetGuild(CGuild* pGuild);
	CGuild* GetGuild() const { return m_pGuild; }

	void SetWarMap(CWarMap* pWarMap);
	CWarMap* GetWarMap() const { return m_pWarMap; }

protected:
	CGuild* m_pGuild;
	DWORD m_dwUnderGuildWarInfoMessageTime;
	CWarMap* m_pWarMap;

	////////////////////////////////////////////////////////////////////////////////////////
	// Item related
public:
	bool CanHandleItem(bool bSkipRefineCheck = false, bool bSkipObserver = false); // 아이템 관련 행위를 할 수 있는가?

	bool IsItemLoaded() const { return m_bItemLoaded; }
	void SetItemLoaded() { m_bItemLoaded = true; }

	void ClearItem();

	LPITEM GetInventoryItem(WORD wCell) const;
	LPITEM GetEquipmentItem(WORD wCell) const;
	LPITEM GetDragonSoulInventoryItem(WORD wCell) const;
	LPITEM GetBeltInventoryItem(WORD wCell) const;

	void SetItem(TItemPos Cell, LPITEM item
#if defined(__WJ_PICKUP_ITEM_EFFECT__)
		, bool isHighLight = false
#endif
	);

	LPITEM GetItem(TItemPos Cell) const;

	bool IsEmptyItemGrid(TItemPos Cell, BYTE size, int iExceptionCell = -1) const;

	void SetWear(WORD wCell, LPITEM item);
	LPITEM GetWear(WORD wCell) const;

	// MYSHOP_PRICE_LIST
	void UseSilkBotary(void); /// 비단 보따리 아이템의 사용

	/// DB 캐시로 부터 받아온 가격정보 리스트를 유저에게 전송하고 보따리 아이템 사용을 처리한다.
	/**
	* @param [in] p 가격정보 리스트 패킷
	*
	* 접속한 후 처음 비단 보따리 아이템 사용 시 UseSilkBotary 에서 DB 캐시로 가격정보 리스트를 요청하고
	* 응답받은 시점에 이 함수에서 실제 비단보따리 사용을 처리한다.
	**/
	void UseSilkBotaryReal(const TPacketMyshopPricelistHeader* p);
	// END_OF_MYSHOP_PRICE_LIST

	bool UseItemEx(LPITEM item, TItemPos DestCell);
	bool UseItem(TItemPos Cell, TItemPos DestCell = NPOS);

	// ADD_REFINE_BUILDING
	bool IsRefineThroughGuild() const;
	CGuild* GetRefineGuild() const;
	int ComputeRefineFee(int iCost, int iMultiply = 5) const;
	void PayRefineFee(int iTotalMoney);
	void SetRefineNPC(LPCHARACTER ch);
	// END_OF_ADD_REFINE_BUILDING

	bool RefineItem(LPITEM pkItem, LPITEM pkTarget);
	bool DropItem(TItemPos Cell, WORD wCount = 0);
#if defined(__NEW_DROP_DIALOG__)
	bool DestroyItem(TItemPos Cell);
#endif
	bool GiveRecallItem(LPITEM item);
	void ProcessRecallItem(LPITEM item);

	// void PotionPacket(int iPotionType);
	void EffectPacket(BYTE bEffectNum, BYTE bEffectType = SE_TYPE_NORMAL, const PIXEL_POSITION& rEffectPos = { 0, 0, 0 });
	void SpecificEffectPacket(const char filename[128]);

	// ADD_MONSTER_REFINE
	bool DoRefine(LPITEM item, bool bMoneyOnly = false);
	// END_OF_ADD_MONSTER_REFINE

	bool DoRefineWithScroll(LPITEM item);
	bool RefineInformation(WORD wCell, BYTE bType, int iAdditionalCell = -1);

	struct SRefineScrollData
	{
		BYTE bSuccessProb;
		bool bKeepGrade;
	};
	SRefineScrollData GetScrollRefinePct(BYTE bProb, BYTE bRefineLevel, BYTE bScrollType);

	void SetRefineMode(int iAdditionalCell = -1);
	void ClearRefineMode();

	bool GiveItem(LPCHARACTER victim, TItemPos Cell);
	bool CanReceiveItem(LPCHARACTER from, LPITEM item) const;
	void ReceiveItem(LPCHARACTER from, LPITEM item);
	//bool GiveItemFromSpecialItemGroup(DWORD dwGroupNum, std::vector<DWORD>& dwItemVnums,
	//	std::vector<DWORD>& dwItemCounts, std::vector<LPITEM>& item_gets, int& count);
	bool GiveItemFromSpecialItemGroup(DWORD dwGroupNum);

	bool MoveItem(TItemPos pos, TItemPos change_pos, WORD num);
	bool PickupItem(DWORD vid
#if defined(__PET_LOOT_AI__)
		, bool PetLoot = false
#endif
	);
	bool EquipItem(LPITEM item, int iCandidateCell = -1);
	bool UnequipItem(LPITEM item);

	// 현재 item을 착용할 수 있는 지 확인하고, 불가능 하다면 캐릭터에게 이유를 알려주는 함수
	bool CanEquipNow(const LPITEM item, const TItemPos& srcCell = NPOS, const TItemPos& destCell = NPOS);
	// 착용중인 item을 벗을 수 있는 지 확인하고, 불가능 하다면 캐릭터에게 이유를 알려주는 함수
	bool CanUnequipNow(const LPITEM item, const TItemPos& srcCell = NPOS, const TItemPos& destCell = NPOS);

	bool SwapItem(WORD wCell, WORD wDestCell);

	LPITEM AutoGiveItem(DWORD dwItemVnum, WORD wCount = 1, int iRarePct = -1, bool bMsg = true
#if defined(__WJ_PICKUP_ITEM_EFFECT__)
		, bool isHighLight = false
#endif
#if defined(__NEW_USER_CARE__)
		, bool bSystemDrop = true
#endif
	);

	void AutoGiveItem(LPITEM item, bool longOwnerShip = false, bool bMsg = true
#if defined(__WJ_PICKUP_ITEM_EFFECT__)
		, bool isHighLight = false
#endif
	);

	int GetEmptyInventory(BYTE size) const;
	int GetEmptyInventoryCount(BYTE size) const;

#if defined(__DRAGON_SOUL_SYSTEM__)
	int GetEmptyDragonSoulInventory(LPITEM pItem) const;
	void CopyDragonSoulItemGrid(std::vector<WORD>& vDragonSoulItemGrid) const;
#endif

	int CountEmptyInventory() const;
	bool HasEnoughInventorySpace(std::vector<TItemData>& vItems) const;

	int CountSpecifyItem(DWORD vnum, int iExceptionCell = -1
#if defined(__SOUL_BIND_SYSTEM__)
		, bool bIgnoreSealedItem = false
#endif
#if defined(__SET_ITEM__)
		, bool bIgnoreSetValue = false
#endif
	) const;
	void RemoveSpecifyItem(DWORD vnum, DWORD count = 1, int iExceptionCell = -1
#if defined(__SOUL_BIND_SYSTEM__)
		, bool bIgnoreSealedItem = false
#endif
#if defined(__SET_ITEM__)
		, bool bIgnoreSetValue = false
#endif
	);
	LPITEM FindSpecifyItem(DWORD dwVnum
#if defined(__SOUL_BIND_SYSTEM__)
		, bool bIgnoreSealedItem = false
#endif
#if defined(__SET_ITEM__)
		, bool bIgnoreSetValue = false
#endif
	) const;
	LPITEM FindItemByID(DWORD id) const;

	int CountSpecifyTypeItem(BYTE type) const;
	void RemoveSpecifyTypeItem(BYTE type, DWORD count = 1);

	bool IsEquipUniqueItem(DWORD dwItemVnum) const;

	// CHECK_UNIQUE_GROUP
	bool IsEquipUniqueGroup(DWORD dwGroupVnum) const;
	// END_OF_CHECK_UNIQUE_GROUP

	void SendEquipment(LPCHARACTER pChar);
	// End of Item

protected:
	/// 한 아이템에 대한 가격정보를 전송한다.
	/**
	* @param [in] dwItemVnum 아이템 vnum
	* @param [in] dwItemPrice 아이템 가격
	**/
	void SendMyShopPriceListCmd(DWORD dwItemVnum, DWORD dwItemPrice
#if defined(__CHEQUE_SYSTEM__)
		, DWORD dwItemCheque
#endif
	);

	bool m_bNoOpenedShop; ///< 이번 접속 후 개인상점을 연 적이 있는지의 여부(열었던 적이 없다면 true)

	bool m_bItemLoaded;
	int m_iRefineAdditionalCell;

public:
	bool IsUnderRefine() const { return m_bUnderRefine; }
	void SetUnderRefine(bool bState) { m_bUnderRefine = bState; }
protected:
	bool m_bUnderRefine;
	DWORD m_dwRefineNPCVID;

public:
	int GetGold() const { return m_points.iGold; }
	void SetGold(int iValue) { m_points.iGold = iValue; }

	bool DropGold(int iAmount);
	void GiveGold(int iAmount); // 파티가 있으면 파티 분배, 로그 등의 처리

	int GetAllowedGold() const;

#if defined(__CHEQUE_SYSTEM__)
	////////////////////////////////////////////////////////////////////////////////////////
	// Cheque related
	int GetCheque() const { return m_points.iCheque; }
	void SetCheque(int iValue) { m_points.iCheque = iValue; }
	bool DropCheque(int iAmount);
	void GiveCheque(int iAmount);
	// End of Cheque
#endif

#if defined(__GEM_SYSTEM__)
	////////////////////////////////////////////////////////////////////////////////////////
	int GetGem() const { return m_points.iGem; }
	void SetGem(int iValue) { m_points.iGem = iValue; }
	void GiveGem(int iAmount);
#endif

	////////////////////////////////////////////////////////////////////////////////////////
	// Shop related
public:
	void SetShop(LPSHOP pkShop);
	LPSHOP GetShop() const { return m_pkShop; }
	void ShopPacket(BYTE bSubHeader);

	void SetShopOwner(LPCHARACTER ch) { m_pkChrShopOwner = ch; }
	LPCHARACTER GetShopOwner() const { return m_pkChrShopOwner; }

	void OpenMyShop(const char* c_pszSign, TShopItemTable* pTable, BYTE bItemCount);
	LPSHOP GetMyShop() const { return m_pkMyShop; }
	void CloseMyShop();

protected:
	LPSHOP m_pkShop;
	LPSHOP m_pkMyShop;
	std::string m_stShopSign;
	LPCHARACTER m_pkChrShopOwner;
	// End of shop

	////////////////////////////////////////////////////////////////////////////////////////
	// Exchange related
public:
	bool ExchangeStart(LPCHARACTER victim);
	void SetExchange(CExchange* pkExchange);
	CExchange* GetExchange() const { return m_pkExchange; }

protected:
	CExchange* m_pkExchange;
	// End of Exchange

	////////////////////////////////////////////////////////////////////////////////////////
	// Battle
public:
	struct TBattleInfo
	{
		int iTotalDamage;
		int iAggro;

		TBattleInfo(int iTot, int iAggr)
			: iTotalDamage(iTot), iAggro(iAggr)
		{}
	};
	typedef std::map<VID, TBattleInfo> TDamageMap;

	typedef struct SAttackLog
	{
		DWORD dwVID;
		DWORD dwTime;
	} AttackLog;

	bool Damage(LPCHARACTER pAttacker, int dam, EDamageType type = DAMAGE_TYPE_NORMAL);
	bool __Profile__Damage(LPCHARACTER pAttacker, int dam, EDamageType type = DAMAGE_TYPE_NORMAL);
	void DeathPenalty(BYTE bExpLossPercent);
	void ReviveInvisible(int iDur);

	bool Attack(LPCHARACTER pkVictim, BYTE bType = 0);
	bool IsAlive() const { return m_pointsInstant.position == POS_DEAD ? false : true; }
	bool CanFight() const;

	bool CanBeginFight() const;
	void BeginFight(LPCHARACTER pkVictim); // pkVictimr과 싸우기 시작한다. (강제적임, 시작할 수 있나 체크하려면 CanBeginFight을 사용)

	bool CounterAttack(LPCHARACTER pkChr); // 반격하기 (몬스터만 사용)

	bool IsStun() const;
	void Stun(bool bImmediate = false);
	bool IsDead() const;
	void Dead(LPCHARACTER pkKiller = NULL, bool bImmediateDead = false);

	void Reward(bool bItemDrop);
	void RewardGold(LPCHARACTER pkAttacker);

	bool Shoot(BYTE bType);
	void FlyTarget(DWORD dwTargetVID, long x, long y, BYTE bHeader);

	void ForgetMyAttacker(bool bRevive = true);
	void AggregateMonster();
	void AttractRanger();
	void PullMonster();

	int GetArrowAndBow(LPITEM* ppkBow, LPITEM* ppkArrow, int iArrowCount = 1);
	void UseArrow(LPITEM pkArrow, DWORD dwArrowCount);

	void AttackedByPoison(LPCHARACTER pkAttacker);
	void RemovePoison();

	void AttackedByBleeding(LPCHARACTER pkAttacker);
	void RemoveBleeding();

	void AttackedByFire(LPCHARACTER pkAttacker, int amount, int count);
	void RemoveFire();

	void UpdateAlignment(int iAmount);
	int GetAlignment() const;

	// 선악치 얻기 
	int GetRealAlignment() const;
	void ShowAlignment(bool bShow);

	UINT GetAlignmentGrade() const;

	void SetKillerMode(bool bOn);
	bool IsKillerMode() const;
	void UpdateKillerMode();

	BYTE GetPKMode() const;
	void SetPKMode(BYTE bPKMode);

	void ItemDropPenalty(LPCHARACTER pkKiller);

	void UpdateAggrPoint(LPCHARACTER ch, EDamageType type, int dam);

	////////////////////////////////////////////////////////////////////////////////////////
	// HACK
public:
	void SetComboSequence(BYTE seq);
	BYTE GetComboSequence() const;

	void SetLastComboTime(DWORD time);
	DWORD GetLastComboTime() const;

	int GetValidComboInterval() const;
	void SetValidComboInterval(int interval);

	BYTE GetComboIndex() const;

	void IncreaseComboHackCount(int k = 1);
	void ResetComboHackCount();
	void SkipComboAttackByTime(int interval);
	DWORD GetSkipComboAttackByTime() const;

protected:
	BYTE m_bComboSequence;
	DWORD m_dwLastComboTime;
	int m_iValidComboInterval;
	BYTE m_bComboIndex;
	int m_iComboHackCount;
	DWORD m_dwSkipComboAttackByTime;

protected:
	void UpdateAggrPointEx(LPCHARACTER ch, EDamageType type, int dam, TBattleInfo& info);
	void ChangeVictimByAggro(int iNewAggro, LPCHARACTER pNewVictim);

	DWORD m_dwFlyTargetID;
	std::vector<DWORD> m_vec_dwFlyTargets;
	TDamageMap m_map_kDamage; // 어떤 캐릭터가 나에게 얼마만큼의 데미지를 주었는가?
	//AttackLog m_kAttackLog;
	DWORD m_dwKillerPID;

	int m_iAlignment; // Lawful / Chaotic value -200000 ~ 200000
	int m_iRealAlignment;
	int m_iKillerModePulse;
	BYTE m_bPKMode;

	// Aggro
	DWORD m_dwLastVictimSetTime;
	int m_iMaxAggro;
	// End of Battle

	// Stone
public:
	void SetStone(LPCHARACTER pkChrStone);
	void ClearStone();
	void DetermineDropMetinStone();
	DWORD GetDropMetinStoneVnum() const { return m_dwDropMetinStone; }
	BYTE GetDropMetinStonePct() const { return m_bDropMetinStonePct; }

protected:
	LPCHARACTER m_pkChrStone; // 나를 스폰한 돌
	CHARACTER_SET m_set_pkChrSpawnedBy; // 내가 스폰한 놈들
	DWORD m_dwDropMetinStone;
	BYTE m_bDropMetinStonePct;
	// End of Stone

public:
	enum
	{
		SKILL_UP_BY_POINT,
		SKILL_UP_BY_BOOK,
		SKILL_UP_BY_TRAIN,

		// ADD_GRANDMASTER_SKILL
		SKILL_UP_BY_QUEST,
		// END_OF_ADD_GRANDMASTER_SKILL
	};

	void SkillLevelPacket();
	void SkillLevelUp(DWORD dwVnum, BYTE bMethod = SKILL_UP_BY_POINT);
	bool SkillLevelDown(DWORD dwVnum);
	// ADD_GRANDMASTER_SKILL
	bool UseSkill(DWORD dwVnum, LPCHARACTER pkVictim, bool bUseGrandMaster = true);
	void ResetSkill();
#if defined(__SKILL_COOLTIME_UPDATE__)
	void ResetSkillCoolTimes();
#endif
	void SetSkillLevel(DWORD dwVnum, BYTE bLev);
	int GetUsedSkillMasterType(DWORD dwVnum);

	bool IsLearnableSkill(DWORD dwSkillVnum) const;
	// END_OF_ADD_GRANDMASTER_SKILL

	bool CheckSkillHitCount(const BYTE SkillID, const VID dwTargetVID);
	bool CanUseSkill(DWORD dwSkillVnum) const;
	bool IsUsableSkillMotion(DWORD dwMotionIndex) const;
	int GetSkillLevel(DWORD dwVnum) const;
	int GetSkillMasterType(DWORD dwVnum) const;
	int GetSkillPower(DWORD dwVnum, BYTE bLevel = 0) const;

	time_t GetSkillNextReadTime(DWORD dwVnum) const;
	void SetSkillNextReadTime(DWORD dwVnum, time_t time);
	void SkillLearnWaitMoreTimeMessage(DWORD dwVnum);

	void ComputePassiveSkill(DWORD dwVnum);
	int ComputeSkill(DWORD dwVnum, LPCHARACTER pkVictim, BYTE bSkillLevel = 0);
	int ComputeSkillParty(DWORD dwVnum, LPCHARACTER pkVictim, BYTE bSkillLevel = 0);
	int ComputeSkillAtPosition(DWORD dwVnum, const PIXEL_POSITION& posTarget, BYTE bSkillLevel = 0);
#if defined(__PVP_BALANCE_IMPROVING__)
	int ComputeGyeongGongSkill(DWORD dwVnum, LPCHARACTER pkVictim, BYTE bSkillLevel = 0);
#endif
	void ComputeSkillPoints();

	void SetSkillGroup(BYTE bSkillGroup);
	BYTE GetSkillGroup() const { return m_points.bSkillGroup; }

	int ComputeCooltime(int time);

	void GiveRandomSkillBook();
	void GiveSkillBook(DWORD dwSkillVnum, WORD wCount);

	void DisableCooltime();
	bool LearnSkillByBook(DWORD dwSkillVnum, BYTE bProb = 0);
	bool LearnGrandMasterSkill(DWORD dwSkillVnum);

#if defined(__CONQUEROR_LEVEL__)
	bool IsConquerorSkill(DWORD dwVnum) const;
#endif

private:
	bool m_bDisableCooltime;
	DWORD m_dwLastSkillTime; ///< 마지막으로 skill 을 쓴 시간(millisecond).
	// End of Skill

	// MOB_SKILL
public:
	bool HasMobSkill() const;
	size_t CountMobSkill() const;
	const TMobSkillInfo* GetMobSkill(unsigned int idx) const;
	bool CanUseMobSkill(unsigned int idx) const;
	bool UseMobSkill(unsigned int idx);
	void ResetMobSkillCooltime();
protected:
	DWORD m_adwMobSkillCooltime[MOB_SKILL_MAX_NUM];
	// END_OF_MOB_SKILL

	// for SKILL_MUYEONG
public:
	void StartMuyeongEvent();
	void StopMuyeongEvent();

#if defined(__PVP_BALANCE_IMPROVING__)
	void StartGyeongGongEvent();
	void StopGyeongGongEvent();
#endif

#if defined(__9TH_SKILL__)
	void StartCheonunEvent(BYTE bChance, BYTE bDuration);
	void StopCheonunEvent();
#endif

private:
	LPEVENT m_pkMuyeongEvent;
#if defined(__PVP_BALANCE_IMPROVING__)
	LPEVENT m_pkGyeongGongEvent;
#endif
#if defined(__9TH_SKILL__)
	LPEVENT m_pkCheonunEvent;
#endif

	// for SKILL_CHAIN lighting
public:
	int GetChainLightningIndex() const { return m_iChainLightingIndex; }
	void IncChainLightningIndex() { ++m_iChainLightingIndex; }
	void AddChainLightningExcept(LPCHARACTER ch) { m_setExceptChainLighting.insert(ch); }
	void ResetChainLightningIndex() { m_iChainLightingIndex = 0; m_setExceptChainLighting.clear(); }
	int GetChainLightningMaxCount() const;
	const CHARACTER_SET& GetChainLightingExcept() const { return m_setExceptChainLighting; }

private:
	int m_iChainLightingIndex;
	CHARACTER_SET m_setExceptChainLighting;

	// for SKILL_EUNHYUNG
public:
	void SetAffectedEunhyung();
	void ClearAffectedEunhyung() { m_dwAffectedEunhyungLevel = 0; }
	bool GetAffectedEunhyung() const { return m_dwAffectedEunhyungLevel; }

private:
	DWORD m_dwAffectedEunhyungLevel;

	//
	// Skill levels
	//
protected:
	TPlayerSkill* m_pSkillLevels;
	std::unordered_map<BYTE, int> m_SkillDamageBonus;
	std::map<int, TSkillUseInfo> m_SkillUseInfo;

	////////////////////////////////////////////////////////////////////////////////////////
	// AI related
public:
	void AssignTriggers(const TMobTable* table);
	LPCHARACTER GetVictim() const; // 공격할 대상 리턴
	void SetVictim(LPCHARACTER pkVictim);
	LPCHARACTER GetNearestVictim(LPCHARACTER pkChr);
	LPCHARACTER GetProtege() const; // 보호해야 할 대상 리턴

	bool Follow(LPCHARACTER pkChr, float fMinimumDistance = 150.0f);
	bool Return();
	bool IsGuardNPC() const;
	bool IsChangeAttackPosition(LPCHARACTER target) const;
	void ResetChangeAttackPositionTime() { m_dwLastChangeAttackPositionTime = get_dword_time() - AI_CHANGE_ATTACK_POISITION_TIME_NEAR; }
	void SetChangeAttackPositionTime() { m_dwLastChangeAttackPositionTime = get_dword_time(); }

	bool OnIdle();

	void OnAttack(LPCHARACTER pkChrAttacker);
	void OnClick(LPCHARACTER pkChrCauser);

	VID m_kVIDVictim;

protected:
	DWORD m_dwLastChangeAttackPositionTime;
	CTrigger m_triggerOnClick;
	// End of AI

	////////////////////////////////////////////////////////////////////////////////////////
	// Target
protected:
	LPCHARACTER m_pkChrTarget; // 내 타겟
	CHARACTER_SET m_set_pkChrTargetedBy; // 나를 타겟으로 가지고 있는 사람들

public:
	void SetTarget(LPCHARACTER pkChrTarget);
	void BroadcastTargetPacket();
	void ClearTarget();
	void CheckTarget();
	LPCHARACTER GetTarget() const { return m_pkChrTarget; }

	////////////////////////////////////////////////////////////////////////////////////////
	// Safebox
public:
	int GetSafeboxSize() const;
	void QuerySafeboxSize();
	void SetSafeboxSize(int size);

	CSafebox* GetSafebox() const;
	void LoadSafebox(int iSize, DWORD dwGold, int iItemCount, TPlayerItem* pItems);
	void ChangeSafeboxSize(BYTE bSize);
	void CloseSafebox();

	/// 창고 열기 요청
	/**
	* @param [in] pszPassword 1자 이상 6자 이하의 창고 비밀번호
	*
	* DB 에 창고열기를 요청한다.
	* 창고는 중복으로 열지 못하며, 최근 창고를 닫은 시간으로 부터 10초 이내에는 열 지 못한다.
	**/
	void ReqSafeboxLoad(const char* pszPassword);

	/// 창고 열기 요청의 취소
	/**
	* ReqSafeboxLoad 를 호출하고 CloseSafebox 하지 않았을 때 이 함수를 호출하면 창고를 열 수 있다.
	* 창고열기의 요청이 DB 서버에서 실패응답을 받았을 경우 이 함수를 사용해서 요청을 할 수 있게 해준다.
	**/
	void CancelSafeboxLoad(void) { m_bOpeningSafebox = false; }

	void SetMallLoadTime(int t) { m_iMallLoadTime = t; }
	int GetMallLoadTime() const { return m_iMallLoadTime; }

	CSafebox* GetMall() const;
	void LoadMall(int iItemCount, TPlayerItem* pItems);
	void CloseMall();

	void SetSafeboxOpenPosition();
	float GetDistanceFromSafeboxOpen() const;

	void LoadSafeboxBuff();
	void SetSafeboxBuff();

protected:
	CSafebox* m_pkSafebox;
	int m_iSafeboxSize;
	int m_iSafeboxLoadTime;
	bool m_bOpeningSafebox; ///< 창고가 열기 요청 중이거나 열려있는가 여부, true 일 경우 열기요청이거나 열려있음.

	CSafebox* m_pkMall;
	int m_iMallLoadTime;

	PIXEL_POSITION m_posSafeboxOpen;

	////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////
	// Mounting
public:
	void UnMount(bool bUnequipItem = false);
	void MountVnum(DWORD vnum);
	DWORD GetMountVnum() const { return m_dwMountVnum; }
	DWORD GetLastMountTime() const { return m_dwMountTime; }

	bool CanUseHorseSkill();

	// Horse
	virtual void SetHorseLevel(int iLevel);

	virtual bool StartRiding();
	virtual bool StopRiding();

	virtual DWORD GetMyHorseVnum() const;

	virtual void HorseDie();
	virtual bool ReviveHorse();

	virtual void SendHorseInfo();
	virtual void ClearHorseInfo();

	void HorseSummon(bool bSummon, bool bFromFar = false, DWORD dwVnum = 0, const char* pHorseName = 0);

	LPCHARACTER GetHorse() const { return m_chHorse; } // 현재 소환중인 말
	LPCHARACTER GetRider() const; // rider on horse
	void SetRider(LPCHARACTER ch);

	bool IsRiding() const;

#if defined(__PET_SYSTEM__)
public:
	CPetSystem* GetPetSystem() { return m_petSystem; }

protected:
	CPetSystem* m_petSystem;

public:
#endif

protected:
	LPCHARACTER m_chHorse;
	LPCHARACTER m_chRider;

	DWORD m_dwMountVnum;
	DWORD m_dwMountTime;

	BYTE m_bSendHorseLevel;
	BYTE m_bSendHorseHealthGrade;
	BYTE m_bSendHorseStaminaGrade;

	////////////////////////////////////////////////////////////////////////////////////////
	// Detailed Log
public:
	void DetailLog() { m_bDetailLog = !m_bDetailLog; }
	void ToggleMonsterLog();
	void MonsterLog(const char* format, ...);

private:
	bool m_bDetailLog;
	bool m_bMonsterLog;

	////////////////////////////////////////////////////////////////////////////////////////
	// Empire
public:
	void SetEmpire(BYTE bEmpire);
	BYTE GetEmpire() const { return m_bEmpire; }

protected:
	BYTE m_bEmpire;

	////////////////////////////////////////////////////////////////////////////////////////
	// Regen
public:
	void SetRegen(LPREGEN pkRegen);

protected:
	PIXEL_POSITION m_posRegen;
	float m_fRegenAngle;
	LPREGEN m_pkRegen;
	size_t regen_id_; // to help dungeon regen identification
	// End of Regen

	////////////////////////////////////////////////////////////////////////////////////////
	// Resists & Proofs
public:
	bool CannotMoveByAffect() const; // 특정 효과에 의해 움직일 수 없는 상태인가?
	bool IsImmune(DWORD dwImmuneFlag);
	void SetImmuneFlag(DWORD dw) { m_pointsInstant.dwImmuneFlag = dw; }

protected:
	void ApplyMobAttribute(const TMobTable* table);
	// End of Resists & Proofs

	////////////////////////////////////////////////////////////////////////////////////////
	// QUEST
public:
	void SetQuestNPCID(DWORD vid);
	DWORD GetQuestNPCID() const { return m_dwQuestNPCVID; }
	LPCHARACTER GetQuestNPC() const;

	void SetQuestItemPtr(LPITEM item);
	void ClearQuestItemPtr();
	LPITEM GetQuestItemPtr() const;

	void SetQuestBy(DWORD dwQuestVnum) { m_dwQuestByVnum = dwQuestVnum; }
	DWORD GetQuestBy() const { return m_dwQuestByVnum; }

	int GetQuestFlag(const std::string& flag) const;
	void SetQuestFlag(const std::string& flag, int value);

	void ConfirmWithMsg(const char* szMsg, int iTimeout, DWORD dwRequestPID);
	bool IsRunningQuest() const;

private:
	DWORD m_dwQuestNPCVID;
	DWORD m_dwQuestByVnum;
	LPITEM m_pQuestItem;

	// Events
public:
	bool StartStateMachine(int iPulse = 1);
	void StopStateMachine();
	void UpdateStateMachine(DWORD dwPulse);
	void SetNextStatePulse(int iPulseNext);

	// 캐릭터 인스턴스 업데이트 함수. 기존엔 이상한 상속구조로 CFSM::Update 함수를 호출하거나 UpdateStateMachine 함수를 사용했는데, 별개의 업데이트 함수 추가함.
	void UpdateCharacter(DWORD dwPulse);

protected:
	DWORD m_dwNextStatePulse;

	// Marriage
public:
	LPCHARACTER GetMarryPartner() const;
	void SetMarryPartner(LPCHARACTER ch);
	int GetMarriageBonus(DWORD dwItemVnum, bool bSum = true);

	bool IsWearingDress() const;

	void SetWeddingMap(marriage::WeddingMap* pMap);
	marriage::WeddingMap* GetWeddingMap() const { return m_pWeddingMap; }

private:
	marriage::WeddingMap* m_pWeddingMap;
	LPCHARACTER m_pkChrMarried;

	// Warp Character
public:
	void StartWarpNPCEvent();

public:
	void StartSaveEvent();
	void StartRecoveryEvent();
	void StartCheckSpeedHackEvent();
	void StartDestroyWhenIdleEvent();

	LPEVENT m_pkDeadEvent;
	LPEVENT m_pkStunEvent;
	LPEVENT m_pkSaveEvent;
	LPEVENT m_pkRecoveryEvent;
	LPEVENT m_pkTimedEvent;
	LPEVENT m_pkFishingEvent;
	LPEVENT m_pkAffectEvent;
	LPEVENT m_pkPoisonEvent;
	LPEVENT m_pkBleedingEvent;
	LPEVENT m_pkFireEvent;
#if defined(__DAWNMIST_DUNGEON__)
	LPEVENT m_pkHealEvent;
#endif
	LPEVENT m_pkWarpNPCEvent;
	// DELAYED_WARP
	// END_DELAYED_WARP

	// MINING
	LPEVENT m_pkMiningEvent;
	// END_OF_MINING
	LPEVENT m_pkWarpEvent;
	LPEVENT m_pkCheckSpeedHackEvent;
	LPEVENT m_pkDestroyWhenIdleEvent;
	LPEVENT m_pkPetSystemUpdateEvent;

	bool IsWarping() const { return m_pkWarpEvent ? true : false; }

	bool m_bHasPoisoned;
	bool m_bHasBled;

	const CMob* m_pkMobData;
	CMobInstance* m_pkMobInst;

	MobSkillEventMap m_mapMobSkillEvent;

	friend struct FuncSplashDamage;
	friend struct FuncSplashAffect;
	friend class CFuncShoot;

public:
	int GetPremiumRemainSeconds(BYTE bType) const;

private:
	int m_aiPremiumTimes[PREMIUM_MAX_NUM];

	// CHANGE_ITEM_ATTRIBUTES
	static const DWORD msc_dwDefaultChangeItemAttrCycle; ///< 디폴트 아이템 속성변경 가능 주기
	static const char msc_szLastChangeItemAttrFlag[]; ///< 최근 아이템 속성을 변경한 시간의 Quest Flag 이름
	static const char msc_szChangeItemAttrCycleFlag[]; ///< 아이템 속성병경 가능 주기의 Quest Flag 이름
	// END_OF_CHANGE_ITEM_ATTRIBUTES

	// PC_BANG_ITEM_ADD
private:
	bool m_isinPCBang;

public:
	bool SetPCBang(bool flag) { m_isinPCBang = flag; return m_isinPCBang; }
	bool IsPCBang() const { return m_isinPCBang; }
	// END_PC_BANG_ITEM_ADD

	// NEW_HAIR_STYLE_ADD
public:
	bool ItemProcess_Hair(LPITEM item, int iDestCell);
	// END_NEW_HAIR_STYLE_ADD

public:
	void ClearSkill();
	void ClearSubSkill();

	// RESET_ONE_SKILL
	bool ResetOneSkill(DWORD dwVnum);
	// END_RESET_ONE_SKILL

private:
	void SendDamagePacket(LPCHARACTER pAttacker, int Damage, BYTE DamageFlag);

	// ARENA
private:
	CArena* m_pArena;
	bool m_ArenaObserver;
	int m_nPotionLimit;

public:
	void SetArena(CArena* pArena) { m_pArena = pArena; }
	void SetArenaObserverMode(bool flag) { m_ArenaObserver = flag; }

	CArena* GetArena() const { return m_pArena; }
	bool GetArenaObserverMode() const { return m_ArenaObserver; }

	void SetPotionLimit(int count) { m_nPotionLimit = count; }
	int GetPotionLimit() const { return m_nPotionLimit; }
	// END_ARENA

	// PREVENT_TRADE_WINDOW
public:
	bool IsOpenSafebox() const { return m_isOpenSafebox ? true : false; }
	void SetOpenSafebox(bool b) { m_isOpenSafebox = b; }

	int GetSafeboxLoadTime() const { return m_iSafeboxLoadTime; }
	void SetSafeboxLoadTime() { m_iSafeboxLoadTime = thecore_pulse(); }

private:
	bool m_isOpenSafebox;
	// END_PREVENT_TRADE_WINDOW

public:
	int GetSkillPowerByLevel(int iLevel, bool bMob = false) const;

	// PREVENT_REFINE_HACK
	int GetRefineTime() const { return m_iRefineTime; }
	void SetRefineTime() { m_iRefineTime = thecore_pulse(); }
	int m_iRefineTime;
	// END_PREVENT_REFINE_HACK

	// RESTRICT_USE_SEED_OR_MOONBOTTLE
	int GetUseSeedOrMoonBottleTime() const { return m_iSeedTime; }
	void SetUseSeedOrMoonBottleTime() { m_iSeedTime = thecore_pulse(); }
	int m_iSeedTime;
	// END_RESTRICT_USE_SEED_OR_MOONBOTTLE

	// PREVENT_PORTAL_AFTER_EXCHANGE
	int GetExchangeTime() const { return m_iExchangeTime; }
	void SetExchangeTime() { m_iExchangeTime = thecore_pulse(); }
	int m_iExchangeTime;
	// END_PREVENT_PORTAL_AFTER_EXCHANGE

	int m_iMyShopTime;
	int GetMyShopTime() const { return m_iMyShopTime; }
	void SetMyShopTime() { m_iMyShopTime = thecore_pulse(); }

	// PREVENT_TRADE_WINDOW
	bool PreventTradeWindow(int flags, bool except = false) const;
	// END_PREVENT_TRADE_WINDOW

	// Hack 방지를 위한 체크.
	bool IsHack(bool bSendMsg = true, bool bCheckShopOwner = true, int limittime = g_nPortalLimitTime);

	// MONARCH
	BOOL IsMonarch() const;
	// END_MONARCH
	void Say(const std::string& s);

	enum MONARCH_COOLTIME
	{
		MC_HEAL = 10,
		MC_WARP = 60,
		MC_TRANSFER = 60,
		MC_TAX = (60 * 60 * 24 * 7),
		MC_SUMMON = (60 * 60),
	};

	enum MONARCH_INDEX
	{
		MI_HEAL = 0,
		MI_WARP,
		MI_TRANSFER,
		MI_TAX,
		MI_SUMMON,
		MI_MAX
	};

	DWORD m_dwMonarchCooltime[MI_MAX];
	DWORD m_dwMonarchCooltimelimit[MI_MAX];

	void InitMC();
	DWORD GetMC(enum MONARCH_INDEX e) const;
	void SetMC(enum MONARCH_INDEX e);
	bool IsMCOK(enum MONARCH_INDEX e) const;
	DWORD GetMCL(enum MONARCH_INDEX e) const;
	DWORD GetMCLTime(enum MONARCH_INDEX e) const;

public:
	bool ItemProcess_Polymorph(LPITEM item);

#if !defined(__CUBE_RENEWAL__)
	// by mhh
	LPITEM* GetCubeItem() { return m_pointsInstant.pCubeItems; }
#endif
	bool IsCubeOpen() const { return (m_pointsInstant.pCubeNpc ? true : false); }
	void SetCubeNpc(LPCHARACTER npc) { m_pointsInstant.pCubeNpc = npc; }
	bool CanDoCube() const;

public:
	bool IsSiegeNPC() const;

private:
	// 중국 전용
	// 18세 미만 전용
	// 3시간 : 50 % 5 시간 0%
	e_overtime m_eOverTime;

public:
	bool IsOverTime(e_overtime e) const { return (e == m_eOverTime); }
	void SetOverTime(e_overtime e) { m_eOverTime = e; }

private:
	int m_deposit_pulse;

public:
	void UpdateDepositPulse();
	bool CanDeposit() const;

private:
	void __OpenPrivateShop(
#if defined(__MYSHOP_DECO__)
		BYTE bTabCount = 1, bool bIsCashItem = false
#endif
	);

public:
	struct AttackedLog
	{
		DWORD dwPID;
		DWORD dwAttackedTime;

		AttackedLog() : dwPID(0), dwAttackedTime(0)
		{
		}
	};

	AttackLog m_kAttackLog;
	AttackedLog m_AttackedLog;
	int m_speed_hack_count;

private:
	std::string m_strNewName;

public:
	const std::string GetNewName() const { return this->m_strNewName; }
	void SetNewName(const std::string name) { this->m_strNewName = name; }

public:
	void GoHome();

private:
	std::set<DWORD> m_known_guild;

public:
	void SendGuildName(CGuild* pGuild);
	void SendGuildName(DWORD dwGuildID);

private:
	DWORD m_dwLogOffInterval;
	DWORD m_dwLastPlay;

public:
	DWORD GetLogOffInterval() const { return m_dwLogOffInterval; }
	DWORD GetLastPlay() const { return m_dwLastPlay; }

public:
	bool UnEquipSpecialRideUniqueItem();

	bool CanWarp() const;
	bool IsInSafezone() const;
	bool IsInBlockedArea(long x = 0, long y = 0) const;

private:
	DWORD m_dwLastGoldDropTime;
#if defined(__CHEQUE_SYSTEM__)
	DWORD m_dwLastChequeDropTime;
#endif

public:
	void AutoRecoveryItemProcess(const EAffectTypes);

public:
	void BuffOnAttr_AddBuffsFromItem(LPITEM pItem);
	void BuffOnAttr_RemoveBuffsFromItem(LPITEM pItem);

private:
	void BuffOnAttr_ValueChange(POINT_TYPE wPointType, POINT_VALUE lOldValue, POINT_VALUE lNewValue);
	void BuffOnAttr_ClearAll();

	typedef std::map<DWORD, CBuffOnAttributes*> TMapBuffOnAttrs;
	TMapBuffOnAttrs m_map_buff_on_attrs;
	// 무적 : 원활한 테스트를 위하여.

public:
	void SetArmada() { cannot_dead = true; }
	void ResetArmada() { cannot_dead = false; }

private:
	bool cannot_dead;

#if defined(__PET_SYSTEM__)
private:
	bool m_bIsPet;

public:
	void SetPet() { m_bIsPet = true; }
	bool IsPet() { return m_bIsPet; }
#endif

	// 최종 데미지 보정.
private:
	float m_fAttMul;
	float m_fDamMul;

public:
	float GetAttMul() { return this->m_fAttMul; }
	void SetAttMul(float newAttMul) { this->m_fAttMul = newAttMul; }
	float GetDamMul() { return this->m_fDamMul; }
	void SetDamMul(float newDamMul) { this->m_fDamMul = newDamMul; }

private:
	bool IsValidItemPosition(TItemPos Pos) const;

	// 독일 선물 기능 패킷 임시 저장
private:
	unsigned int itemAward_vnum;
	char itemAward_cmd[20];
	//bool itemAward_flag;
public:
	unsigned int GetItemAward_vnum() { return itemAward_vnum; }
	char* GetItemAward_cmd() { return itemAward_cmd; }
	//bool GetItemAward_flag() { return itemAward_flag; }
	void SetItemAward_vnum(unsigned int vnum) { itemAward_vnum = vnum; }
	void SetItemAward_cmd(char* cmd) { strcpy(itemAward_cmd, cmd); }
	//void SetItemAward_flag(bool flag) { itemAward_flag = flag; }

#if defined(__MOVE_COSTUME_ATTR__)
public:
	void ItemCombination(const short MediumIndex, const short BaseIndex, const short MaterialIndex);
	void OpenItemComb();

	bool IsItemComb() const { return m_pointsInstant.pItemCombNpc != NULL; }
	void SetItemCombNpc(const LPCHARACTER npc) { m_pointsInstant.pItemCombNpc = npc; }
#endif

#if defined(__CHANGED_ATTR__)
public:
	void SelectAttr(LPITEM material, LPITEM item);
	void SelectAttrResult(const bool bNew, const TItemPos& pos);
	bool IsSelectAttr() const;
private:
	struct SItemSelectAttr
	{
		DWORD dwItemID;
		TPlayerItemAttribute Attr[ITEM_ATTRIBUTE_MAX_NUM];
	} m_ItemSelectAttr;
#endif

#if defined(__MINI_GAME_CATCH_KING__)
public:
	void MiniGameCatchKingSetFieldCards(std::vector<TCatchKingCard> vec) { m_vecCatchKingFieldCards = vec; }

	DWORD MiniGameCatchKingGetScore() const { return dwCatchKingTotalScore; }
	void MiniGameCatchKingSetScore(DWORD dwScore) { dwCatchKingTotalScore = dwScore; }

	DWORD MiniGameCatchKingGetBetNumber() const { return bCatchKingBetSetNumber; }
	void MiniGameCatchKingSetBetNumber(BYTE bSetNr) { bCatchKingBetSetNumber = bSetNr; }

	BYTE MiniGameCatchKingGetHandCard() const { return bCatchKingHandCard; }
	void MiniGameCatchKingSetHandCard(BYTE bKingCard) { bCatchKingHandCard = bKingCard; }

	BYTE MiniGameCatchKingGetHandCardLeft() const { return bCatchKingHandCardLeft; }
	void MiniGameCatchKingSetHandCardLeft(BYTE bHandCard) { bCatchKingHandCardLeft = bHandCard; }

	bool MiniGameCatchKingGetGameStatus() const { return dwCatchKingGameStatus; }
	void MiniGameCatchKingSetGameStatus(bool bStatus) { dwCatchKingGameStatus = bStatus; }

	std::vector<TCatchKingCard> m_vecCatchKingFieldCards;

protected:
	BYTE bCatchKingHandCard;
	BYTE bCatchKingHandCardLeft;
	bool dwCatchKingGameStatus;

	BYTE bCatchKingBetSetNumber;
	DWORD dwCatchKingTotalScore;
#endif

#if defined(__DRAGON_SOUL_SYSTEM__)
public:
	// 용혼석

	// 캐릭터의 affect, quest가 load 되기 전에 DragonSoul_Initialize를 호출하면 안된다.
	// affect가 가장 마지막에 로드되어 LoadAffect에서 호출함.
	void DragonSoul_Initialize();

	bool DragonSoul_IsQualified() const;
	void DragonSoul_GiveQualification();

	int DragonSoul_GetActiveDeck() const;
	bool DragonSoul_IsDeckActivated() const;
	bool DragonSoul_ActivateDeck(int iDeckIdx);

	void DragonSoul_DeactivateAll();
	// 반드시 ClearItem 전에 불러야 한다.
	// 왜냐하면....
	// 용혼석 하나 하나를 deactivate할 때마다 덱에 active인 용혼석이 있는지 확인하고,
	// active인 용혼석이 하나도 없다면, 캐릭터의 용혼석 affect와, 활성 상태를 제거한다.
	// 
	// 하지만 ClearItem 시, 캐릭터가 착용하고 있는 모든 아이템을 unequip하는 바람에,
	// 용혼석 Affect가 제거되고, 결국 로그인 시, 용혼석이 활성화되지 않는다.
	// (Unequip할 때에는 로그아웃 상태인지, 아닌지 알 수 없다.)
	// 용혼석만 deactivate시키고 캐릭터의 용혼석 덱 활성 상태는 건드리지 않는다.
	void DragonSoul_CleanUp();

#if defined(__DS_SET__)
	// Dragon Soul Set Bonus
public:
	void DragonSoul_SetBonus();
	void DragonSoul_ActivateAll();
#endif

	// 용혼석 강화창
public:
	bool DragonSoul_RefineWindow_Open(LPENTITY pEntity);
#if defined(__DS_CHANGE_ATTR__)
	bool DragonSoul_RefineWindow_ChangeAttr_Open(LPENTITY pEntity);
#endif
	bool DragonSoul_RefineWindow_Close();
	LPENTITY DragonSoul_RefineWindow_GetOpener() { return m_pointsInstant.m_pDragonSoulRefineWindowOpener; }
	bool DragonSoul_RefineWindow_CanRefine();
#endif

private:
	// SyncPosition을 악용하여 타유저를 이상한 곳으로 보내는 핵 방어하기 위하여,
	// SyncPosition이 일어날 때를 기록.
	timeval m_tvLastSyncTime;
	int m_iSyncHackCount;
public:
	void SetLastSyncTime(const timeval& tv) { memcpy(&m_tvLastSyncTime, &tv, sizeof(timeval)); }
	const timeval& GetLastSyncTime() { return m_tvLastSyncTime; }
	void SetSyncHackCount(int iCount) { m_iSyncHackCount = iCount; }
	int GetSyncHackCount() { return m_iSyncHackCount; }

#if defined(__PRIVATESHOP_SEARCH_SYSTEM__)
public:
	BYTE GetPrivateShopSearchState() const { return bPrivateShopSearchState; }
	void SetPrivateShopSearchState(BYTE bState) { bPrivateShopSearchState = bState; }
	void OpenPrivateShopSearch(DWORD dwVnum);
protected:
	BYTE bPrivateShopSearchState;
#endif

#if defined(__CHANGE_LOOK_SYSTEM__)
public:
	void SetChangeLook(CChangeLook* c);
	CChangeLook* GetChangeLook() const;
protected:
	CChangeLook* m_pkChangeLook;
#endif

#if defined(__MAILBOX__)
public:
	int GetMyMailBoxTime() const { return m_iMyMailBoxTime; }
	void SetMyMailBoxTime() { m_iMyMailBoxTime = thecore_pulse(); }

	void SetMailBox(CMailBox* m);

	void SetMailBoxLoading(const bool b) { bMailBoxLoading = b; }
	bool IsMailBoxLoading() const { return bMailBoxLoading; }

	CMailBox* GetMailBox() const { return m_pkMailBox; }

private:
	CMailBox* m_pkMailBox;
	bool bMailBoxLoading;
	int m_iMyMailBoxTime;
#endif

#if defined(__MINI_GAME_RUMI__)
public:
	void SetMiniGameRumi(CMiniGameRumi* pClass);
	CMiniGameRumi* GetMiniGameRumi() const { return m_pkMiniGameRumi; }
private:
	CMiniGameRumi* m_pkMiniGameRumi;
#endif

#if defined(__CONQUEROR_LEVEL__)
public:
	bool IsNewWorldMapIndex() const;
	long GetNewWorldSungMa(POINT_TYPE wPointType, bool bPremium = true) const;
	bool IsSungMaCursed(POINT_TYPE wPointType) const;
#endif

#if defined(__LOOT_FILTER_SYSTEM__)
public:
	CLootFilter* GetLootFilter();
	void SetLootFilter();
	void ClearLootFilter();
private:
	CLootFilter* m_pLootFilter;
#endif

#if defined(__ATTR_6TH_7TH__)
public:
	bool IsOpenAttr67Add() const { return m_bIsOpenAttr67Add ? true : false; }
	void SetOpenAttr67Add(bool bOpen) { m_bIsOpenAttr67Add = bOpen; }

	LPITEM GetNPCStorageItem(BYTE bCell = 0) const;
	bool Attr67Add(const TAttr67AddData kAttr67AddData);

private:
	bool m_bIsOpenAttr67Add;
#endif

#if defined(__FISHING_GAME__)
public:
	void SetFishingGameGoals(BYTE bCount) { m_bFishingGameGoals = bCount; }
	BYTE GetFishingGameGoals() { return m_bFishingGameGoals; }
private:
	BYTE m_bFishingGameGoals;
#endif

#if defined(__GEM_SYSTEM__)
public:
	void SelectItemEx(DWORD dwInventoryPos, BYTE bType);
	bool GemRefine(LPITEM lpMetinStoneItem);

#	if defined(__GEM_SHOP__)
public:
	void SetGemShop(CGemShop* pGemShop);
	CGemShop* GetGemShop() const { return m_pGemShop; }

	void SetGemShopLoading(const bool c_bLoading) { m_bGemShopLoading = c_bLoading; }
	bool IsGemShopLoading() const { return m_bGemShopLoading; }

private:
	CGemShop* m_pGemShop;
	bool m_bGemShopLoading;
#	endif
#endif

#if defined(__ACCE_COSTUME_SYSTEM__)
	//////////////////////////////////////////////////////////////////////////////////
	// Acce Costume System
public:
	void AcceRefineWindowOpen(const LPENTITY pEntity, BYTE bType);
	void AcceRefineWindowClose(bool bServerClose = false);
	bool IsAcceRefineWindowOpen() const { return m_bAcceRefineWindowOpen; }
	bool GetAcceRefineWindowType() const { return m_bAcceRefineWindowType; }

	bool IsAcceRefineWindowCanRefine();
	LPENTITY GetAcceRefineWindowOpener() const { return m_pointsInstant.m_pAcceRefineWindowOpener; }

	void AcceRefineWindowCheckIn(BYTE bType, TItemPos SelectedPos, TItemPos AttachedPos);
	void AcceRefineWindowCheckOut(BYTE bType, TItemPos SelectedPos);
	void AcceRefineWindowAccept(BYTE bType);

	int GetAcceWeaponAttack() const;
	int GetAcceWeaponMagicAttack() const;

	void ModifyAccePoints(const LPITEM& rAcceItem, bool bAdd);

protected:
	int __CalculateAcceDrainValues(BYTE bWeaponAttackType) const;
	int __CheckAcceRefineItem(const LPITEM& rLeftItem, const LPITEM& rRightItem) const;
	BYTE __GetNextDrainRate(const LPITEM& rAcceItem, BYTE bMinDrainRate) const;

private:
	bool m_bAcceRefineWindowOpen;
	BYTE m_bAcceRefineWindowType;
	TItemPos m_pAcceRefineWindowItemSlot[ACCE_SLOT_MAX];
#endif

#if defined(__AURA_COSTUME_SYSTEM__)
	//////////////////////////////////////////////////////////////////////////////////
	// Aura Costume System
public:
	void OpenAuraRefineWindow(const LPENTITY pEntity, BYTE bType);
	void AuraRefineWindowClose(bool bServerClose = false);
	bool IsAuraRefineWindowOpen() const { return m_bAuraRefineWindowOpen; }
	BYTE GetAuraRefineWindowType() const { return m_bAuraRefineWindowType; }

	bool IsAuraRefineWindowCanRefine();
	LPENTITY GetAuraRefineWindowOpener() const { return m_pointsInstant.m_pAuraRefineWindowOpener; }

	void AuraRefineWindowCheckIn(BYTE bType, TItemPos SelectedPos, TItemPos AttachedPos);
	void AuraRefineWindowCheckOut(BYTE bType, TItemPos SelectedPos);
	void AuraRefineWindowAccept(BYTE bType);

	void ModifyAuraPoints(const LPITEM& rAuraItem, bool bAdd);

private:
	BYTE m_bAuraRefineWindowType;
	bool m_bAuraRefineWindowOpen;
	TItemPos m_pAuraRefineWindowItemSlot[AURA_SLOT_MAX];
	TAuraRefineInfo m_bAuraRefineInfo[AURA_REFINE_INFO_SLOT_MAX];

protected:
	TAuraRefineInfo __GetAuraRefineInfo(TItemPos Cell);
	TAuraRefineInfo __CalcAuraRefineInfo(TItemPos Cell, TItemPos MaterialCell);
	TAuraRefineInfo __GetAuraEvolvedRefineInfo(TItemPos Cell);
#endif

#if defined(__SOUL_SYSTEM__)
public:
	void SoulItemProcess(ESoulSubTypes eSubType);

	int GetSoulDamage(ESoulSubTypes eSubType) const;
	bool DoRefineSoul(LPITEM item);
#endif

#if defined(__EXTEND_INVEN_SYSTEM__)
public:
	void SetExtendInvenStage(BYTE bStage) { m_bExtendInvenStage = bStage; }
	BYTE GetExtendInvenStage() const { return m_bExtendInvenStage; }

	WORD GetExtendInvenMax() const;

	void ExtendInvenRequest();
	void ExtendInvenUpgrade();

	void SendExtendInvenPacket();

private:
	BYTE m_bExtendInvenStage;
#endif

#if defined(__ATTR_6TH_7TH__)
public:
	void StartHitBuffEvent();
	void StopHitBuffEvent();
private:
	LPEVENT m_pHitBuffEvent;
#endif

#if defined(__CLIENT_TIMER__)
public:
	void SendClientTimer(BYTE bSubHeader, DWORD dwEndTime = 0, DWORD dwAlarmSec = 0);
#endif

#if defined(__EXPRESSING_EMOTIONS__)
public:
	void AddEmote(const INT iEmoteIndex = -1);
	void SetEmotes(const TPacketGDEmote* pTable, const WORD c_wSize);
#endif

#if defined(__SET_ITEM__)
public:
	using SetItemCountMap = std::map<BYTE, BYTE>;
	SetItemCountMap GetItemSetCountMap() const;

	void RefreshItemSetBonus();
	void RefreshItemSetBonusByValue();
#endif

#if defined(__RACE_SWAP__)
public:
	void SetEventRaceNum(DWORD dwRaceNum);
	DWORD GetEventRaceNum() const { return m_dwEventRaceNum; }
private:
	DWORD m_dwEventRaceNum;
#endif

#if defined(__GAME_OPTION_ESCAPE__)
public:
	void SetEscapeCooltime(const DWORD dwTime) { m_dwEscapeCooltime = dwTime; }
	DWORD GetEscapeCooltime() const { return m_dwEscapeCooltime; }
private:
	DWORD m_dwEscapeCooltime;
#endif

#if defined(__REFINE_ELEMENT_SYSTEM__)
public:
	void RefineElementInformation(const LPITEM& rSrcItem, const TItemPos& kItemDestCell);
	void RefineElement(WORD wElementType);

	bool IsUnderRefineElement() const { return m_bUnderRefineElement; }
	void SetUnderRefineElement(bool bState, BYTE bRefineType = 0, const TItemPos& rkSrcPos = NPOS, const TItemPos& rkDestPos = NPOS);

	WORD GetRefineElementEffect() const;

private:
	struct SRefineElementItemPos
	{
		SRefineElementItemPos() : RefineType(0), SrcPos(NPOS), DestPos(NPOS) {}
		BYTE RefineType;
		TItemPos SrcPos, DestPos;
	} m_kRefineElementItemPos;
	bool m_bUnderRefineElement;
#endif

#if defined(__HIDE_COSTUME_SYSTEM__)
public:
	void SetHiddenCostumePart(BYTE bCostumeSubType, bool bHidden, bool bSave = true);
	bool GetHiddenCostumeByPart(BYTE bPartPos) const;

	void SetHiddenCostumeParts();
private:
	DWORD m_dwHideCostumePulse;
	bool m_bHiddenCostumePart[COSTUME_NUM_TYPES];
#endif

#if defined(__MINI_GAME_YUTNORI__)
public:
	void SetMiniGameYutnori(CMiniGameYutnori* pClass);
	CMiniGameYutnori* GetMiniGameYutnori() const { return m_pkMiniGameYutnori; }
private:
	CMiniGameYutnori* m_pkMiniGameYutnori;
#endif

#if defined(__MULTI_LANGUAGE_SYSTEM__)
public:
	void SetCountry(const std::string& country) { m_stCountry = country; }
	const char* GetCountry() const { return m_stCountry.c_str(); }

protected:
	std::string m_stCountry;
#endif

#if defined(__MYSHOP_DECO__)
public:
	void SetMyShopDecoState(BYTE bState) { m_bMyShopDecoState = bState; };
	BYTE GetMyShopDecoState() const { return m_bMyShopDecoState; };

	void SetMyShopDecoType(BYTE bShopType) { m_bMyShopDecoType = bShopType; };
	BYTE GetMyShopDecoType() const { return m_bMyShopDecoType; };

	void SetMyShopDecoPolyVnum(DWORD dwPolyVnum) { m_bMyShopDecoPolyVnum = dwPolyVnum; };
	DWORD GetMyShopDecoPolyVnum() const { return m_bMyShopDecoPolyVnum; };

	void SetMyPrivShopTabCount(BYTE bTabCount) { m_bMyPrivShopTabCount = bTabCount; };
	BYTE GetMyPrivShopTabCount() const { return m_bMyPrivShopTabCount; };

	void SetMyPrivShopIsCashItem(bool bIsCashItem) { m_bMyPrivShopIsCashItem = bIsCashItem; };
	bool GetMyPrivShopIsCashItem() const { return m_bMyPrivShopIsCashItem; };

	void OpenPrivateShop(BYTE bTabCount = 1, bool bIsCashItem = false);

private:
	BYTE m_bMyShopDecoState;
	BYTE m_bMyShopDecoType;
	DWORD m_bMyShopDecoPolyVnum;

	BYTE m_bMyPrivShopTabCount;
	bool m_bMyPrivShopIsCashItem;
#endif

#if defined(__LEFT_SEAT__)
public:
	void SetLeftSeat(bool bLeftSeat);
	bool LeftSeat() const { return m_bLeftSeat; }

	void SetLeftSeatWaitTime(BYTE bIndex);
	DWORD GetLeftSeatWaitTime() const { return m_dwLeftSeatWaitTime; }

	void SetLeftSeatLogoutTime(BYTE bIndex);
	DWORD GetLeftSeatLogoutTime() const { return m_dwLeftSeatLogoutTime; }

	void DisableLeftSeatLogOutState(bool bClosePopup = false);

	void RestartLeftSeatWaitTimer();
	void RestartLeftSeatLogoutTimer();

	void SetLastRequestTime(DWORD dwRequestTime) { m_dwLastRequestTime = dwRequestTime; }
	DWORD GetLastRequestTime() const { return m_dwLastRequestTime; }

public:
	LPEVENT m_pLeftSeatWaitTimerEvent;
	LPEVENT m_pLeftSeatLogoutTimerEvent;

private:
	BOOL m_bLeftSeat;
	DWORD m_dwLeftSeatWaitTime;
	DWORD m_dwLeftSeatLogoutTime;
	DWORD m_dwLastRequestTime;
#endif

#if defined(__ELEMENTAL_DUNGEON__)
public:
	void StartElementalCurseEvent();
	void StopElementalCurseEvent();

	void SetAccumulatedDamage(DWORD dwDamage);
	DWORD GetAccumulatedDamage() const { return m_dwAccumulatedDamage; }

private:
	LPEVENT m_pElementalCurseEvent;
	DWORD m_dwAccumulatedDamage;
#endif

#if defined(__GUILD_DRAGONLAIR_SYSTEM__)
public:
	void SetGuildDragonLair(CGuildDragonLair* pGuildDragonLair);
	CGuildDragonLair* GetGuildDragonLair() const { return m_pGuildDragonLair; }
private:
	CGuildDragonLair* m_pGuildDragonLair;
#endif

#if defined(__SUMMER_EVENT_ROULETTE__)
public:
	void SetMiniGameRoulette(CMiniGameRoulette* pMiniGameRoulette);
	CMiniGameRoulette* GetMiniGameRoulette() const { return m_pMiniGameRoulette; }

	void SetMiniGameRoulette_RewardMapperNum(BYTE bMapNum) { m_bMiniGameRoulette_RewardMapperNum = bMapNum; }
	BYTE GetMiniGameRoulette_RewardMapperNum() const { return m_bMiniGameRoulette_RewardMapperNum; }

private:
	CMiniGameRoulette* m_pMiniGameRoulette;
	BYTE m_bMiniGameRoulette_RewardMapperNum;
#endif

#if defined(__FLOWER_EVENT__)
public:
	void SetLastFlowerEventExchangePulse(DWORD dwPulse) { m_dwLastFlowerEventExchangePulse = dwPulse; }
	DWORD GetLastFlowerEventExchangePulse() const { return m_dwLastFlowerEventExchangePulse; }
private:
	DWORD m_dwLastFlowerEventExchangePulse;
#endif

#if defined(__DEFENSE_WAVE__)
public:
	void SetDefenseWave(LPDEFENSE_WAVE pDefenseWave);
	LPDEFENSE_WAVE GetDefenseWave() const;
private:
	LPDEFENSE_WAVE m_pDefenseWave;
#endif
};

ESex GET_SEX(LPCHARACTER ch);

#endif // __INC_CHAR_H__
