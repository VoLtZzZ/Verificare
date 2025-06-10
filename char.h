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
	// ��ų
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
	POINT_STAMINA,							// 9 ���׹̳�
	POINT_MAX_STAMINA,						// 10 �ִ� ���׹̳�

	POINT_GOLD,								// 11
	POINT_ST,								// 12 �ٷ�
	POINT_HT,								// 13 ü��
	POINT_DX,								// 14 ��ø��
	POINT_IQ,								// 15 ���ŷ�
	POINT_DEF_GRADE,						// 16 ...
	POINT_ATT_SPEED,						// 17 ���ݼӵ�
	POINT_ATT_GRADE,						// 18 ���ݷ� MAX
	POINT_MOV_SPEED,						// 19 �̵��ӵ�
	POINT_CLIENT_DEF_GRADE,					// 20 �����
	POINT_CASTING_SPEED,					// 21 �ֹ��ӵ� (��ٿ�Ÿ��*100) / (100 + �̰�) = ���� ��ٿ� Ÿ��
	POINT_MAGIC_ATT_GRADE,					// 22 �������ݷ�
	POINT_MAGIC_DEF_GRADE,					// 23 ��������
	POINT_EMPIRE_POINT,						// 24 ��������
	POINT_LEVEL_STEP,						// 25 �� ���������� �ܰ�.. (1 2 3 �� �� ����, 4 �Ǹ� ���� ��)
	POINT_STAT,								// 26 �ɷ�ġ �ø� �� �ִ� ����
	POINT_SUB_SKILL,						// 27 ���� ��ų ����Ʈ
	POINT_SKILL,							// 28 ��Ƽ�� ��ų ����Ʈ
	POINT_WEAPON_MIN,						// 29 ���� �ּ� ������
	POINT_WEAPON_MAX,						// 30 ���� �ִ� ������
	POINT_PLAYTIME,							// 31 �÷��̽ð�
	POINT_HP_REGEN,							// 32 HP ȸ����
	POINT_SP_REGEN,							// 33 SP ȸ����

	POINT_BOW_DISTANCE,						// 34 Ȱ �����Ÿ� ����ġ (meter)

	POINT_HP_RECOVERY,						// 35 ü�� ȸ�� ������
	POINT_SP_RECOVERY,						// 36 ���ŷ� ȸ�� ������

	POINT_POISON_PCT,						// 37 �� Ȯ��
	POINT_STUN_PCT,							// 38 ���� Ȯ��
	POINT_SLOW_PCT,							// 39 ���ο� Ȯ��
	POINT_CRITICAL_PCT,						// 40 ũ��Ƽ�� Ȯ��
	POINT_PENETRATE_PCT,					// 41 ����Ÿ�� Ȯ��
	POINT_CURSE_PCT,						// 42 ���� Ȯ��

	POINT_ATTBONUS_HUMAN,					// 43 �ΰ����� ����
	POINT_ATTBONUS_ANIMAL,					// 44 �������� ������ % ����
	POINT_ATTBONUS_ORC,						// 45 ���Ϳ��� ������ % ����
	POINT_ATTBONUS_MILGYO,					// 46 �б����� ������ % ����
	POINT_ATTBONUS_UNDEAD,					// 47 ��ü���� ������ % ����
	POINT_ATTBONUS_DEVIL,					// 48 ����(�Ǹ�)���� ������ % ����
	POINT_ATTBONUS_INSECT,					// 49 ������
	POINT_ATTBONUS_FIRE,					// 50 ȭ����
	POINT_ATTBONUS_ICE,						// 51 ������
	POINT_ATTBONUS_DESERT,					// 52 �縷��
	POINT_ATTBONUS_MONSTER,					// 53 ��� ���Ϳ��� ����
	POINT_ATTBONUS_WARRIOR,					// 54 ���翡�� ����
	POINT_ATTBONUS_ASSASSIN,				// 55 �ڰ����� ����
	POINT_ATTBONUS_SURA,					// 56 ���󿡰� ����
	POINT_ATTBONUS_SHAMAN,					// 57 ���翡�� ����
	POINT_ATTBONUS_TREE,					// 58 �������� ���� 20050729.myevan UNUSED5

	POINT_RESIST_WARRIOR,					// 59 ���翡�� ����
	POINT_RESIST_ASSASSIN,					// 60 �ڰ����� ����
	POINT_RESIST_SURA,						// 61 ���󿡰� ����
	POINT_RESIST_SHAMAN,					// 62 ���翡�� ����

	POINT_STEAL_HP,							// 63 ����� ���
	POINT_STEAL_SP,							// 64 ���ŷ� ���

	POINT_MANA_BURN_PCT,					// 65 ���� ��

	/// ���ؽ� ���ʽ� ///

	POINT_DAMAGE_SP_RECOVER,				// 66 ���ݴ��� �� ���ŷ� ȸ�� Ȯ��

	POINT_BLOCK,							// 67 ����
	POINT_DODGE,							// 68 ȸ����

	POINT_RESIST_SWORD,						// 69
	POINT_RESIST_TWOHAND,					// 70
	POINT_RESIST_DAGGER,					// 71
	POINT_RESIST_BELL,						// 72
	POINT_RESIST_FAN,						// 73
	POINT_RESIST_BOW,						// 74 ȭ�� ���� : ����� ����
	POINT_RESIST_FIRE,						// 75 ȭ�� ���� : ȭ�����ݿ� ���� ����� ����
	POINT_RESIST_ELEC,						// 76 ���� ���� : ������ݿ� ���� ����� ����
	POINT_RESIST_MAGIC,						// 77 ���� ���� : �������� ���� ����� ����
	POINT_RESIST_WIND,						// 78 �ٶ� ���� : �ٶ����ݿ� ���� ����� ����

	POINT_REFLECT_MELEE,					// 79 ���� �ݻ�

	/// Ư�� ���ؽ� ///
	POINT_REFLECT_CURSE,					// 80 ���� �ݻ�
	POINT_POISON_REDUCE,					// 81 �������� ����

	/// �� �Ҹ�� ///
	POINT_KILL_SP_RECOVER,					// 82 �� �Ҹ�� MP ȸ��
	POINT_EXP_DOUBLE_BONUS,					// 83
	POINT_GOLD_DOUBLE_BONUS,				// 84
	POINT_ITEM_DROP_BONUS,					// 85

	/// ȸ�� ���� ///
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
	POINT_MANASHIELD,						// 102 ��ż�ȣ ��ų�� ���� �������� ȿ�� ����

	POINT_PARTY_BUFFER_BONUS,				// 103
	POINT_PARTY_SKILL_MASTER_BONUS,			// 104

	POINT_HP_RECOVER_CONTINUE,				// 105
	POINT_SP_RECOVER_CONTINUE,				// 106

	POINT_STEAL_GOLD,						// 107
	POINT_POLYMORPH,						// 108 ������ ���� ��ȣ
	POINT_MOUNT,							// 109 Ÿ���ִ� ���� ��ȣ

	POINT_PARTY_HASTE_BONUS,				// 110
	POINT_PARTY_DEFENDER_BONUS,				// 111
	POINT_STAT_RESET_COUNT,					// 112 ���� �ܾ� ����� ���� ���� ���� ����Ʈ (1�� 1����Ʈ ���°���)

	POINT_HORSE_SKILL,						// 113

	POINT_MALL_ATTBONUS,					// 114 ���ݷ� +x%
	POINT_MALL_DEFBONUS,					// 115 ���� +x%
	POINT_MALL_EXPBONUS,					// 116 ����ġ +x%
	POINT_MALL_ITEMBONUS,					// 117 ������ ����� x/10��
	POINT_MALL_GOLDBONUS,					// 118 �� ����� x/10��

	POINT_MAX_HP_PCT,						// 119 �ִ����� +x%
	POINT_MAX_SP_PCT,						// 120 �ִ����ŷ� +x%

	POINT_SKILL_DAMAGE_BONUS,				// 121 ��ų ������ *(100+x)%
	POINT_NORMAL_HIT_DAMAGE_BONUS,			// 122 ��Ÿ ������ *(100+x)%

	// DEFEND_BONUS_ATTRIBUTES
	POINT_SKILL_DEFEND_BONUS,				// 123 ��ų ��� ������
	POINT_NORMAL_HIT_DEFEND_BONUS,			// 124 ��Ÿ ��� ������
	// END_OF_DEFEND_BONUS_ATTRIBUTES

	// PC_BANG_ITEM_ADD 
	POINT_PC_BANG_EXP_BONUS,				// 125 PC�� ���� ����ġ ���ʽ�
	POINT_PC_BANG_DROP_BONUS,				// 126 PC�� ���� ��ӷ� ���ʽ�
	// END_PC_BANG_ITEM_ADD
	POINT_RAMADAN_CANDY_BONUS_EXP,			// 127 �󸶴� ���� ����ġ ������

	POINT_ENERGY = 128,						// 128 ���

	// ��� ui ��.
	// �������� ���� �ʱ⸸, Ŭ���̾�Ʈ���� ����� �� �ð��� POINT�� �����ϱ� ������ �̷��� �Ѵ�.
	// �� �β�����
	POINT_ENERGY_END_TIME = 129,			// 129 ��� ���� �ð�

	POINT_COSTUME_ATTR_BONUS = 130,			// 130
	POINT_MAGIC_ATT_BONUS_PER = 131,		// 131
	POINT_MELEE_MAGIC_ATT_BONUS_PER = 132,	// 132

	// �߰� �Ӽ� ����
	POINT_RESIST_ICE = 133,					// 133 �ñ� ���� : �������ݿ� ���� ����� ����
	POINT_RESIST_EARTH = 134,				// 134 ���� ���� : �������ݿ� ���� ����� ����
	POINT_RESIST_DARK = 135,				// 135 ��� ���� : �������ݿ� ���� ����� ����

	POINT_RESIST_CRITICAL = 136,			// 136 ũ��Ƽ�� ���� : ����� ũ��Ƽ�� Ȯ���� ����
	POINT_RESIST_PENETRATE = 137,			// 137 ����Ÿ�� ���� : ����� ����Ÿ�� Ȯ���� ����

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

	// Ŭ���̾�Ʈ ����Ʈ
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

/* �����ϴ� ������ */
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

/* ������� �ʴ� ĳ���� ������ */
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
	// ��ȥ�� �κ��丮.
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

	BYTE bBasePart; // ��� ��ȣ

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
	// Entity ����
	virtual void EncodeInsertPacket(LPENTITY entity);
	virtual void EncodeRemovePacket(LPENTITY entity);
	//////////////////////////////////////////////////////////////////////////////////

public:
	LPCHARACTER FindCharacterInView(const char* name, bool bFindPCOnly);
	void UpdatePacket();

	//////////////////////////////////////////////////////////////////////////////////
	// FSM (Finite State Machine) ����
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
	void CreatePlayerProto(TPlayerTable& tab); // ���� �� ���

	void SetProto(const CMob* c_pkMob);
	WORD GetRaceNum() const;

	void Save(); // DelayedSave
	void SaveReal(); // ���� ����
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

	LPCHARACTER DistributeExp(); // ���� ���� ���� ����� �����Ѵ�.

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

	void MainCharacterPacket(); // ���� ����ĳ���Ͷ�� �����ش�.

	void ComputePoints();
	void ComputeBattlePoints();

	void PointChange(POINT_TYPE wPointType, POINT_VALUE lPointAmount, bool bAmount = false, bool bBroadcast = false);
	void PointsPacket();
	void UpdatePointsPacket(POINT_TYPE wPointType, POINT_VALUE lPointValue, POINT_VALUE lPointAmount = 0, bool bAmount = false, bool bBroadcast = false);

	void ApplyPoint(POINT_TYPE wApplyType, POINT_VALUE lApplyValue);
	void CheckMaximumPoints(); // HP, SP ���� ���� ���� �ִ밪 ���� ������ �˻��ϰ� ���ٸ� �����.


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
	bool IsPolyMaintainStat() const { return m_bPolyMaintainStat; } // ���� ������ �����ϴ� ��������.
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

	bool Goto(long x, long y); // �ٷ� �̵� ��Ű�� �ʰ� ��ǥ ��ġ�� BLENDING ��Ų��.
	void Stop();

	bool CanMove() const; // �̵��� �� �ִ°�?

	void SyncPacket();
	bool Sync(long x, long y); // ���� �� �޼ҵ�� �̵� �Ѵ� (�� �� ���ǿ� ���� �̵� �Ұ��� ����)
	bool Move(long x, long y); // ������ �˻��ϰ� Sync �޼ҵ带 ���� �̵� �Ѵ�.
	void OnMove(bool bIsAttack = false); // �����϶� �Ҹ���. Move() �޼ҵ� �̿ܿ����� �Ҹ� �� �ִ�.
	DWORD GetMotionMode() const;
	float GetMoveMotionSpeed() const;
	float GetMoveSpeed() const;
	void CalculateMoveDuration();
	void SendMovePacket(BYTE bFunc, BYTE bArg, DWORD x, DWORD y, DWORD dwDuration, DWORD dwTime = 0, int iRot = -1);

	DWORD GetCurrentMoveDuration() const { return m_dwMoveDuration; }
	DWORD GetWalkStartTime() const { return m_dwWalkStartTime; }
	DWORD GetLastMoveTime() const { return m_dwLastMoveTime; }
	DWORD GetLastAttackTime() const { return m_dwLastAttackTime; }

	void SetLastAttacked(DWORD time); // ���������� ���ݹ��� �ð� �� ��ġ�� ������

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
	CHARACTER_LIST m_kLst_pkChrSyncOwned; // ���� SyncOwner�� �ڵ�

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

	// Quickslot ����
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
	// Affect loading�� ���� �����ΰ�?
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

	/// �ڽ��� ��Ƽ�� �ٸ� character �� �ʴ��Ѵ�.
	/**
	* @param pchInvitee �ʴ��� ��� character. ��Ƽ�� ���� ������ �����̾�� �Ѵ�.
	*
	* ���� character �� ���°� ��Ƽ�� �ʴ��ϰ� �ʴ���� �� �ִ� ���°� �ƴ϶�� �ʴ��ϴ� ĳ���Ϳ��� �ش��ϴ� ä�� �޼����� �����Ѵ�.
	**/
	void PartyInvite(LPCHARACTER pchInvitee);

	/// �ʴ��ߴ� character �� ������ ó���Ѵ�.
	/**
	* @param pchInvitee ��Ƽ�� ������ character. ��Ƽ�� ���������� �����̾�� �Ѵ�.
	*
	* pchInvitee �� ��Ƽ�� ������ �� �ִ� ��Ȳ�� �ƴ϶�� �ش��ϴ� ä�� �޼����� �����Ѵ�.
	**/
	void PartyInviteAccept(LPCHARACTER pchInvitee);

	/// �ʴ��ߴ� character �� �ʴ� �źθ� ó���Ѵ�.
	/**
	* @param [in] dwPID �ʴ� �ߴ� character �� PID
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

	/// ��Ƽ�� �����Ѵ�.
	/**
	* @param pkLeader ������ ��Ƽ�� ����
	**/
	void PartyJoin(LPCHARACTER pkLeader);

	/**
	* ��Ƽ ������ �� �� ���� ����� �����ڵ�.
	* Error code �� �ð��� �������ΰ��� ���� ���氡����(mutable) type �� ����(static) type ���� ������.
	* Error code �� ���� PERR_SEPARATOR ���� ������ ���氡���� type �̰� ������ ���� type �̴�.
	**/
	enum PartyJoinErrCode
	{
		PERR_NONE = 0, ///< ó������
		PERR_SERVER, ///< ���������� ��Ƽ���� ó�� �Ұ�
		PERR_DUNGEON, ///< ĳ���Ͱ� ������ ����
		PERR_OBSERVER, ///< ���������
		PERR_LVBOUNDARY, ///< ��� ĳ���Ϳ� �������̰� ��
		PERR_LOWLEVEL, ///< �����Ƽ�� �ְ������� 30���� ����
		PERR_HILEVEL, ///< �����Ƽ�� ������������ 30���� ����
		PERR_ALREADYJOIN, ///< ��Ƽ���� ��� ĳ���Ͱ� �̹� ��Ƽ��
		PERR_PARTYISFULL, ///< ��Ƽ�ο� ���� �ʰ�
		PERR_SEPARATOR, ///< Error type separator.
		PERR_DIFFEMPIRE, ///< ��� ĳ���Ϳ� �ٸ� ������
		PERR_MAX ///< Error code �ְ�ġ. �� �տ� Error code �� �߰��Ѵ�.
	};

	/// ��Ƽ �����̳� �Ἲ ������ ������ �˻��Ѵ�.
	/**
	* @param pchLeader ��Ƽ�� leader �̰ų� �ʴ��� character
	* @param pchGuest �ʴ�޴� character
	* @return ��� PartyJoinErrCode �� ��ȯ�� �� �ִ�.
	**/
	static PartyJoinErrCode IsPartyJoinableCondition(const LPCHARACTER pchLeader, const LPCHARACTER pchGuest);

	/// ��Ƽ �����̳� �Ἲ ������ ������ ������ �˻��Ѵ�.
	/**
	* @param pchLeader ��Ƽ�� leader �̰ų� �ʴ��� character
	* @param pchGuest �ʴ�޴� character
	* @return mutable type �� code �� ��ȯ�Ѵ�.
	**/
	static PartyJoinErrCode IsPartyJoinableMutableCondition(const LPCHARACTER pchLeader, const LPCHARACTER pchGuest);

	LPPARTY m_pkParty;
	DWORD m_dwLastDeadTime;
	LPEVENT m_pkPartyRequestEvent;

	/**
	* ��Ƽ��û Event map.
	* key: �ʴ���� ĳ������ PID
	* value: event�� pointer
	*
	* �ʴ��� ĳ���͵鿡 ���� event map.
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
	bool CanHandleItem(bool bSkipRefineCheck = false, bool bSkipObserver = false); // ������ ���� ������ �� �� �ִ°�?

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
	void UseSilkBotary(void); /// ��� ������ �������� ���

	/// DB ĳ�÷� ���� �޾ƿ� �������� ����Ʈ�� �������� �����ϰ� ������ ������ ����� ó���Ѵ�.
	/**
	* @param [in] p �������� ����Ʈ ��Ŷ
	*
	* ������ �� ó�� ��� ������ ������ ��� �� UseSilkBotary ���� DB ĳ�÷� �������� ����Ʈ�� ��û�ϰ�
	* ������� ������ �� �Լ����� ���� ��ܺ����� ����� ó���Ѵ�.
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

	// ���� item�� ������ �� �ִ� �� Ȯ���ϰ�, �Ұ��� �ϴٸ� ĳ���Ϳ��� ������ �˷��ִ� �Լ�
	bool CanEquipNow(const LPITEM item, const TItemPos& srcCell = NPOS, const TItemPos& destCell = NPOS);
	// �������� item�� ���� �� �ִ� �� Ȯ���ϰ�, �Ұ��� �ϴٸ� ĳ���Ϳ��� ������ �˷��ִ� �Լ�
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
	/// �� �����ۿ� ���� ���������� �����Ѵ�.
	/**
	* @param [in] dwItemVnum ������ vnum
	* @param [in] dwItemPrice ������ ����
	**/
	void SendMyShopPriceListCmd(DWORD dwItemVnum, DWORD dwItemPrice
#if defined(__CHEQUE_SYSTEM__)
		, DWORD dwItemCheque
#endif
	);

	bool m_bNoOpenedShop; ///< �̹� ���� �� ���λ����� �� ���� �ִ����� ����(������ ���� ���ٸ� true)

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
	void GiveGold(int iAmount); // ��Ƽ�� ������ ��Ƽ �й�, �α� ���� ó��

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
	void BeginFight(LPCHARACTER pkVictim); // pkVictimr�� �ο�� �����Ѵ�. (��������, ������ �� �ֳ� üũ�Ϸ��� CanBeginFight�� ���)

	bool CounterAttack(LPCHARACTER pkChr); // �ݰ��ϱ� (���͸� ���)

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

	// ����ġ ��� 
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
	TDamageMap m_map_kDamage; // � ĳ���Ͱ� ������ �󸶸�ŭ�� �������� �־��°�?
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
	LPCHARACTER m_pkChrStone; // ���� ������ ��
	CHARACTER_SET m_set_pkChrSpawnedBy; // ���� ������ ���
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
	DWORD m_dwLastSkillTime; ///< ���������� skill �� �� �ð�(millisecond).
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
	LPCHARACTER GetVictim() const; // ������ ��� ����
	void SetVictim(LPCHARACTER pkVictim);
	LPCHARACTER GetNearestVictim(LPCHARACTER pkChr);
	LPCHARACTER GetProtege() const; // ��ȣ�ؾ� �� ��� ����

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
	LPCHARACTER m_pkChrTarget; // �� Ÿ��
	CHARACTER_SET m_set_pkChrTargetedBy; // ���� Ÿ������ ������ �ִ� �����

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

	/// â�� ���� ��û
	/**
	* @param [in] pszPassword 1�� �̻� 6�� ������ â�� ��й�ȣ
	*
	* DB �� â���⸦ ��û�Ѵ�.
	* â��� �ߺ����� ���� ���ϸ�, �ֱ� â�� ���� �ð����� ���� 10�� �̳����� �� �� ���Ѵ�.
	**/
	void ReqSafeboxLoad(const char* pszPassword);

	/// â�� ���� ��û�� ���
	/**
	* ReqSafeboxLoad �� ȣ���ϰ� CloseSafebox ���� �ʾ��� �� �� �Լ��� ȣ���ϸ� â�� �� �� �ִ�.
	* â������ ��û�� DB �������� ���������� �޾��� ��� �� �Լ��� ����ؼ� ��û�� �� �� �ְ� ���ش�.
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
	bool m_bOpeningSafebox; ///< â�� ���� ��û ���̰ų� �����ִ°� ����, true �� ��� �����û�̰ų� ��������.

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

	LPCHARACTER GetHorse() const { return m_chHorse; } // ���� ��ȯ���� ��
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
	bool CannotMoveByAffect() const; // Ư�� ȿ���� ���� ������ �� ���� �����ΰ�?
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

	// ĳ���� �ν��Ͻ� ������Ʈ �Լ�. ������ �̻��� ��ӱ����� CFSM::Update �Լ��� ȣ���ϰų� UpdateStateMachine �Լ��� ����ߴµ�, ������ ������Ʈ �Լ� �߰���.
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
	static const DWORD msc_dwDefaultChangeItemAttrCycle; ///< ����Ʈ ������ �Ӽ����� ���� �ֱ�
	static const char msc_szLastChangeItemAttrFlag[]; ///< �ֱ� ������ �Ӽ��� ������ �ð��� Quest Flag �̸�
	static const char msc_szChangeItemAttrCycleFlag[]; ///< ������ �Ӽ����� ���� �ֱ��� Quest Flag �̸�
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

	// Hack ������ ���� üũ.
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
	// �߱� ����
	// 18�� �̸� ����
	// 3�ð� : 50 % 5 �ð� 0%
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
	// ���� : ��Ȱ�� �׽�Ʈ�� ���Ͽ�.

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

	// ���� ������ ����.
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

	// ���� ���� ��� ��Ŷ �ӽ� ����
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
	// ��ȥ��

	// ĳ������ affect, quest�� load �Ǳ� ���� DragonSoul_Initialize�� ȣ���ϸ� �ȵȴ�.
	// affect�� ���� �������� �ε�Ǿ� LoadAffect���� ȣ����.
	void DragonSoul_Initialize();

	bool DragonSoul_IsQualified() const;
	void DragonSoul_GiveQualification();

	int DragonSoul_GetActiveDeck() const;
	bool DragonSoul_IsDeckActivated() const;
	bool DragonSoul_ActivateDeck(int iDeckIdx);

	void DragonSoul_DeactivateAll();
	// �ݵ�� ClearItem ���� �ҷ��� �Ѵ�.
	// �ֳ��ϸ�....
	// ��ȥ�� �ϳ� �ϳ��� deactivate�� ������ ���� active�� ��ȥ���� �ִ��� Ȯ���ϰ�,
	// active�� ��ȥ���� �ϳ��� ���ٸ�, ĳ������ ��ȥ�� affect��, Ȱ�� ���¸� �����Ѵ�.
	// 
	// ������ ClearItem ��, ĳ���Ͱ� �����ϰ� �ִ� ��� �������� unequip�ϴ� �ٶ���,
	// ��ȥ�� Affect�� ���ŵǰ�, �ᱹ �α��� ��, ��ȥ���� Ȱ��ȭ���� �ʴ´�.
	// (Unequip�� ������ �α׾ƿ� ��������, �ƴ��� �� �� ����.)
	// ��ȥ���� deactivate��Ű�� ĳ������ ��ȥ�� �� Ȱ�� ���´� �ǵ帮�� �ʴ´�.
	void DragonSoul_CleanUp();

#if defined(__DS_SET__)
	// Dragon Soul Set Bonus
public:
	void DragonSoul_SetBonus();
	void DragonSoul_ActivateAll();
#endif

	// ��ȥ�� ��ȭâ
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
	// SyncPosition�� �ǿ��Ͽ� Ÿ������ �̻��� ������ ������ �� ����ϱ� ���Ͽ�,
	// SyncPosition�� �Ͼ ���� ���.
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
