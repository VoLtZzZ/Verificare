#ifndef __INC_ITEM_H__
#define __INC_ITEM_H__

#include "entity.h"
#include "../common/VnumHelper.h"
#if defined(__ITEM_APPLY_RANDOM__)
#	include "item_apply_random_table.h"
#endif

class CItem : public CEntity
{
protected:
	// override methods from ENTITY class
	virtual void EncodeInsertPacket(LPENTITY entity);
	virtual void EncodeRemovePacket(LPENTITY entity);

public:
	CItem(DWORD dwVnum = -1);
	virtual ~CItem();

	int GetLevelLimit();
	int GetDurationLimit();

	bool CheckItemUseLevel(int nLevel);
	POINT_VALUE FindApplyValue(POINT_TYPE wApplyType);

	bool IsStackable();

	void Initialize();
	void Destroy();

	void Save();

	void SetWindow(BYTE b) { m_bWindow = b; }
	BYTE GetWindow() { return m_bWindow; }

	void SetID(DWORD id) { m_dwID = id; }
	DWORD GetID() { return m_dwID; }

	void SetProto(const TItemTable* table);
	TItemTable const* GetProto() { return m_pProto; }

	int GetGold();
	int GetShopSellPrice();
	int GetShopBuyPrice();
	const char* GetName() { return m_pProto ? m_pProto->szLocaleName : NULL; }
	const char* GetBaseName() { return m_pProto ? m_pProto->szName : NULL; }
	BYTE GetSize() { return m_pProto ? m_pProto->bSize : 0; }

	void SetFlag(long flag) { m_lFlag = flag; }
	long GetFlag() { return m_lFlag; }

	void AddFlag(long bit);
	void RemoveFlag(long bit);

	DWORD GetWearFlag() { return m_pProto ? m_pProto->dwWearFlags : 0; }
	uint64_t GetAntiFlag() { return m_pProto ? m_pProto->ullAntiFlags : 0; }
	DWORD GetImmuneFlag() { return m_pProto ? m_pProto->dwImmuneFlag : 0; }

	void SetVID(DWORD vid) { m_dwVID = vid; }
	DWORD GetVID() { return m_dwVID; }

	bool SetCount(DWORD count);
	DWORD GetCount();

	// GetVnum�� GetOriginalVnum�� ���� comment
	// GetVnum�� Masking �� Vnum�̴�. �̸� ��������ν�, �������� ���� Vnum�� 10������, Vnum�� 20�� ��ó�� ������ �� �ִ� ���̴�.
	// Masking ���� ori_to_new.txt���� ���ǵ� ���̴�.
	// GetOriginalVnum�� ������ ������ Vnum����, �α� ���� ��, Ŭ���̾�Ʈ�� ������ ���� ���� ��, ������ ���� �� Vnum�� ����Ͽ��� �Ѵ�.
	DWORD GetVnum() const { return m_dwMaskVnum ? m_dwMaskVnum : m_dwVnum; }
	DWORD GetOriginalVnum() const { return m_dwVnum; }
	BYTE GetType() const { return m_pProto ? m_pProto->bType : 0; }
	BYTE GetSubType() const { return m_pProto ? m_pProto->bSubType : 0; }
	BYTE GetLimitType(DWORD idx) const { return m_pProto ? m_pProto->aLimits[idx].bType : 0; }
	long GetLimitValue(DWORD idx) const { return m_pProto ? m_pProto->aLimits[idx].lValue : 0; }

	bool IsSocketModifyingItem()
	{
		return GetType() == ITEM_USE && (GetSubType() == USE_PUT_INTO_BELT_SOCKET
			|| GetSubType() == USE_PUT_INTO_RING_SOCKET
			|| GetSubType() == USE_PUT_INTO_ACCESSORY_SOCKET
			|| GetSubType() == USE_ADD_ACCESSORY_SOCKET
			|| GetSubType() == USE_CLEAN_SOCKET);
	}

	// Weapon
	bool IsWeapon() { return GetType() == ITEM_WEAPON; }
	bool IsMainWeapon()
	{
		return GetType() == ITEM_WEAPON && (
			GetSubType() == WEAPON_SWORD
			|| GetSubType() == WEAPON_DAGGER
			|| GetSubType() == WEAPON_BOW
			|| GetSubType() == WEAPON_TWO_HANDED
			|| GetSubType() == WEAPON_BELL
			|| GetSubType() == WEAPON_FAN
			|| GetSubType() == WEAPON_CLAW
			);
	}
	bool IsSword() { return GetType() == ITEM_WEAPON && GetSubType() == WEAPON_SWORD; }
	bool IsDagger() { return GetType() == ITEM_WEAPON && GetSubType() == WEAPON_DAGGER; }
	bool IsBow() { return GetType() == ITEM_WEAPON && GetSubType() == WEAPON_BOW; }
	bool IsTwoHandSword() { return GetType() == ITEM_WEAPON && GetSubType() == WEAPON_TWO_HANDED; }
	bool IsBell() { return GetType() == ITEM_WEAPON && GetSubType() == WEAPON_BELL; }
	bool IsFan() { return GetType() == ITEM_WEAPON && GetSubType() == WEAPON_FAN; }
	bool IsArrow() { return GetType() == ITEM_WEAPON && GetSubType() == WEAPON_ARROW; }
	bool IsMountSpear() { return GetType() == ITEM_WEAPON && GetSubType() == WEAPON_MOUNT_SPEAR; }
#if defined(__QUIVER_SYSTEM__)
	bool IsQuiver() { return GetType() == ITEM_WEAPON && GetSubType() == WEAPON_QUIVER; }
#endif
	bool IsClaw() { return GetType() == ITEM_WEAPON && GetSubType() == WEAPON_CLAW; }

	// Armor
	bool IsArmor() { return GetType() == ITEM_ARMOR; }
	bool IsArmorType(BYTE bArmorType) { return GetType() == ITEM_ARMOR && GetSubType() == bArmorType; }
	bool IsArmorBody() { return GetType() == ITEM_ARMOR && GetSubType() == ARMOR_BODY; }
	bool IsHelmet() { return GetType() == ITEM_ARMOR && GetSubType() == ARMOR_HEAD; }
	bool IsShield() { return GetType() == ITEM_ARMOR && GetSubType() == ARMOR_SHIELD; }
	bool IsWrist() { return GetType() == ITEM_ARMOR && GetSubType() == ARMOR_WRIST; }
	bool IsShoe() { return GetType() == ITEM_ARMOR && GetSubType() == ARMOR_FOOTS; }
	bool IsNecklace() { return GetType() == ITEM_ARMOR && GetSubType() == ARMOR_NECK; }
	bool IsEarRing() { return GetType() == ITEM_ARMOR && GetSubType() == ARMOR_EAR; }

	bool IsBelt() { return GetType() == ITEM_BELT; }
#if defined(__PENDANT_SYSTEM__)
	bool IsPendant() { return GetType() == ITEM_ARMOR && GetSubType() == ARMOR_PENDANT; }
#endif
#if defined(__GLOVE_SYSTEM__)
	bool IsGlove() { return GetType() == ITEM_ARMOR && GetSubType() == ARMOR_GLOVE; }
#endif
	bool IsRing() { return GetType() == ITEM_RING; }
	bool IsUnique() { return GetType() == ITEM_UNIQUE; }
	bool IsCostume() { return GetType() == ITEM_COSTUME; }
	bool IsCostumeHair() { return GetType() == ITEM_COSTUME && GetSubType() == COSTUME_HAIR; }
	bool IsCostumeBody() { return GetType() == ITEM_COSTUME && GetSubType() == COSTUME_BODY; }
#if defined(__MOUNT_COSTUME_SYSTEM__)
	bool IsCostumeMount() { return GetType() == ITEM_COSTUME && GetSubType() == COSTUME_MOUNT; }
#endif

#if defined(__ACCE_COSTUME_SYSTEM__)
	bool IsCostumeAcce() { return GetType() == ITEM_COSTUME && GetSubType() == COSTUME_ACCE; }
	bool IsAcceReverseScroll() { return GetVnum() == 39046 || GetVnum() == 90000; }
#endif
#if defined(__AURA_COSTUME_SYSTEM__)
	bool IsCostumeAura() { return GetType() == ITEM_COSTUME && GetSubType() == COSTUME_AURA; }
#endif
#if defined(__WEAPON_COSTUME_SYSTEM__)
	bool IsCostumeWeapon() { return GetType() == ITEM_COSTUME && GetSubType() == COSTUME_WEAPON; }
#endif
	bool IsPet() { return GetType() == ITEM_PET && (GetSubType() == PET_PAY || GetSubType() == PET_UPBRINGING); }
#if defined(__EXPRESSING_EMOTIONS__)
	bool IsEmotionPack() { return GetType() == ITEM_USE && GetSubType() == USE_EMOTION_PACK; }
#endif
	bool IsOldHair() { return GetVnum() >= 74001 && GetVnum() <= 75620; }

	DWORD GetRealImmuneFlag();

	long GetValue(DWORD idx);

	void SetCell(LPCHARACTER ch, WORD pos) { m_pOwner = ch, m_wCell = pos; }
	WORD GetCell() { return m_wCell; }

	LPITEM RemoveFromCharacter();

	bool AddToCharacter(LPCHARACTER ch, const TItemPos& Cell
#if defined(__WJ_PICKUP_ITEM_EFFECT__)
		, bool isHighLight = true
#endif
	);

	LPCHARACTER GetOwner() { return m_pOwner; }

	LPITEM RemoveFromGround();
	bool AddToGround(long lMapIndex, const PIXEL_POSITION& pos, bool skipOwnerCheck = false);

	int FindEquipCell(LPCHARACTER ch, int bCandidateCell = -1);
	bool IsEquipped() const { return m_bEquipped; }
	bool EquipTo(LPCHARACTER ch, BYTE bWearCell);
	bool IsEquipable() const;

	bool CanUsedBy(LPCHARACTER ch);

	bool DistanceValid(LPCHARACTER ch);

	void UpdatePacket();
	void UsePacketEncode(LPCHARACTER ch, LPCHARACTER victim, struct packet_item_use* packet);

	void SetExchanging(bool isOn = true);
	bool IsExchanging() { return m_bExchanging; }

#if defined(__MOVE_COSTUME_ATTR__)
	bool CanChangeCostumeAttr() const;
#endif

#if defined(__LOOT_FILTER_SYSTEM__)
	long GetWearingLevelLimit() const;
	bool IsHairDye() const;
#endif

	bool IsPolymorphItem();

	void ModifyPoints(bool bAdd); // �������� ȿ���� ĳ���Ϳ� �ο� �Ѵ�. bAdd�� false�̸� ������

	bool CreateSocket(BYTE bSlot, BYTE bGold);
	const long* GetSockets() { return &m_alSockets[0]; }
	long GetSocket(int i) { return m_alSockets[i]; }

	void SetSockets(const long* al);
	void SetSocket(int i, long v, bool bLog = true);

	int GetSocketCount();
	bool AddSocket();

	const TPlayerItemAttribute* GetAttributes() { return m_aAttr; }
	const TPlayerItemAttribute& GetAttribute(BYTE bIndex) { return m_aAttr[bIndex]; }

#if defined(__ITEM_APPLY_RANDOM__)
	const TPlayerItemAttribute* GetRandomApplies() { return m_aApplyRandom; }
	const TPlayerItemAttribute& GetRandomApply(BYTE bIndex) { return m_aApplyRandom[bIndex]; }

	void GetRandomApplyTable(TPlayerItemAttribute* pApplyRandomTable, BYTE bGetType = CApplyRandomTable::GET_CURRENT);
	void SetRandomApplies(const TPlayerItemAttribute* c_pApplyRandom);

	POINT_TYPE GetRandomApplyType(BYTE bIndex) { return m_aApplyRandom[bIndex].wType; }
	POINT_VALUE GetRandomApplyValue(BYTE bIndex) { return m_aApplyRandom[bIndex].lValue; }
	BYTE GetRandomApplyPath(BYTE bIndex) { return m_aApplyRandom[bIndex].bPath; }
#endif

#if defined(__GLOVE_SYSTEM__)
	DWORD GetRandomSungMaSocketValue(BYTE bType, int iRefineLevel, bool bMultiplier);
#endif

	POINT_TYPE GetAttributeType(BYTE bIndex) { return m_aAttr[bIndex].wType; }
	POINT_VALUE GetAttributeValue(BYTE bIndex) { return m_aAttr[bIndex].lValue; }

	void SetAttributes(const TPlayerItemAttribute* c_pAttribute);

	int FindAttribute(POINT_TYPE wType);
	bool RemoveAttributeAt(int index);
	bool RemoveAttributeType(POINT_TYPE wType);

	bool HasAttr(POINT_TYPE wApply);
	bool HasRareAttr(POINT_TYPE wApply);

	void SetDestroyEvent(LPEVENT pkEvent);
	void StartDestroyEvent(int iSec = 300);

	DWORD GetRefinedVnum() { return m_pProto ? m_pProto->dwRefinedVnum : 0; }
	DWORD GetRefineFromVnum();
	int GetRefineLevel();

	void SetSkipSave(bool b) { m_bSkipSave = b; }
	bool GetSkipSave() { return m_bSkipSave; }

	bool IsOwnership(LPCHARACTER ch);
	void SetOwnership(LPCHARACTER ch, int iSec = 10);
	void SetOwnershipEvent(LPEVENT pkEvent);

	DWORD GetLastOwnerPID() { return m_dwLastOwnerPID; }

	int GetAttributeSetIndex(); // �Ӽ� �ٴ°��� ������ �迭�� ��� �ε����� ����ϴ��� �����ش�.
	void AlterToMagicItem(int iSecondPct = 0, int iThirdPct = 0);
	void AlterToSocketItem(int iSocketCount);

	WORD GetRefineSet() { return m_pProto ? m_pProto->wRefineSet : 0; }
	DWORD Get67AttrMaterial() { return m_pProto ? m_pProto->dw67AttrMaterial : 0; }

	void StartUniqueExpireEvent();
	void SetUniqueExpireEvent(LPEVENT pkEvent);

	void StartTimerBasedOnWearExpireEvent();
	void SetTimerBasedOnWearExpireEvent(LPEVENT pkEvent);

	void StartRealTimeExpireEvent();

	bool IsRealTimeItem();
	bool IsUsedTimeItem();

	void StopUniqueExpireEvent();
	void StopTimerBasedOnWearExpireEvent();
	void StopAccessorySocketExpireEvent();

	// �ϴ� REAL_TIME�� TIMER_BASED_ON_WEAR �����ۿ� ���ؼ��� ����� ������.
	int GetDuration();

	BYTE GetAttributeCount();
	void ClearAttribute();
	void ClearAllAttribute();
	void ChangeAttribute(const int* aiChangeProb = NULL);
	void AddAttribute();
	void AddAttribute(POINT_TYPE dwType, POINT_VALUE llValue);
#if defined(__CHANGED_ATTR__)
	void GetSelectAttr(TPlayerItemAttribute(&arr)[ITEM_ATTRIBUTE_MAX_NUM]);
#endif

	void ApplyAddon(int iAddonType);

	int GetSpecialGroup() const;
	bool IsSameSpecialGroup(const LPITEM item) const;

	// ACCESSORY_REFINE
	// �׼������� ������ ���� ������ �߰�
	bool IsAccessoryForSocket();
	bool IsRemovableSocket();

	int GetAccessorySocketGrade();
	int GetAccessorySocketMaxGrade();
	int GetAccessorySocketDownGradeTime();

	void SetAccessorySocketGrade(int iGrade);
	void SetAccessorySocketMaxGrade(int iMaxGrade);
	void SetAccessorySocketDownGradeTime(DWORD time);

	void AccessorySocketDegrade();

	// �Ǽ��縮 �� �����ۿ� �۾����� Ÿ�̸� ���ư��°�( ����, �� )
	void StartAccessorySocketExpireEvent();
	void SetAccessorySocketExpireEvent(LPEVENT pkEvent);

	bool CanPutInto(LPITEM item);
	// END_OF_ACCESSORY_REFINE

	void CopyAttributeTo(LPITEM pItem);
#if defined(__ITEM_APPLY_RANDOM__)
	void CopyRandomAppliesTo(LPITEM pItem);
#endif
	void CopySocketTo(LPITEM pItem);

	BYTE GetRareAttrCount();
	bool AddRareAttribute();
	bool ChangeRareAttribute();

	void AttrLog();

	void Lock(bool f) { m_isLocked = f; }
	bool isLocked() const { return m_isLocked; }

#if defined(__CHANGE_LOOK_SYSTEM__)
	void SetTransmutationVnum(DWORD blVnum);
	DWORD GetTransmutationVnum() const;
#endif

#if defined(__SET_ITEM__)
	void SetItemSetValue(BYTE bSet);
	BYTE GetItemSetValue() const;
#endif

#if defined(__REFINE_ELEMENT_SYSTEM__)
public:
	void SetRefineElement(const TPlayerItemRefineElement* pTable);
	void CopyElementTo(const LPITEM pItem);

	void UpgradeRefineElement(WORD wApplyType, BYTE bValue, BYTE bBonus);
	void DowngradeRefineElement();
	void ChangeRefineElement(WORD wApplyType);

	BYTE GetRefineElementGrade() const { return m_RefineElement.bGrade; }
	WORD GetRefineElementApplyType() const { return m_RefineElement.wApplyType; }
	BYTE GetRefineElementValue() const;
	BYTE GetRefineElementBonusValue() const;

	BYTE GetRefineElementValue(BYTE bGrade) const { return m_RefineElement.abValue[bGrade]; }
	BYTE GetRefineElementBonusValue(BYTE bGrade) const { return m_RefineElement.abBonusValue[bGrade]; }

	const TPlayerItemRefineElement* GetRefineElement() const { return &m_RefineElement; }
private:
	TPlayerItemRefineElement m_RefineElement;
#endif

private:
	void SetAttribute(BYTE bIndex, POINT_TYPE wType, POINT_VALUE lValue);
#if defined(__ITEM_APPLY_RANDOM__)
	void SetRandomApply(BYTE bIndex, POINT_TYPE wType, POINT_VALUE lValue, BYTE bPath);
#endif
public:
	void SetForceAttribute(BYTE bIndex, POINT_TYPE wType, POINT_VALUE lValue);
#if defined(__ITEM_APPLY_RANDOM__)
	void SetForceRandomApply(BYTE bIndex, POINT_TYPE wType, POINT_VALUE lValue, BYTE bPath);
#endif

protected:
	bool EquipEx(bool is_equip);
	bool Unequip();

	void AddAttr(POINT_TYPE wApply, BYTE bLevel);
	void PutAttribute(const int* aiAttrPercentTable);
	void PutAttributeWithLevel(BYTE bLevel);

protected:
	friend class CInputDB;
	bool OnAfterCreatedItem(); // ������ �������� ��� ������ �Բ� ������ ����(�ε�)�� �� �Ҹ���� �Լ�.

public:
	bool IsRideItem();

	void ClearMountAttributeAndAffect();
#if defined(__MOUNT_COSTUME_SYSTEM__)
	DWORD GetMountVnum();
#endif

	// ���Ͽ��� ���� ĳ�� �����۰� ������, ��ȯ ������ ĳ�� �������� ����ٰ� �Ͽ�,
	// �������� �����ۿ�, ��ȯ ���� �÷��׸� ������ ���ο� �����۵��� ���ο� ������ �뿪�� �Ҵ��Ͽ���.
	// ������ ���ο� �����۵� �������� �����۰� ���� ȿ���� �����ϴµ�,
	// ������, Ŭ���, vnum ������� �Ǿ��־�
	// ���ο� vnum�� �˴� ������ ���� �� �ھƾ��ϴ� ��Ÿ��� ��Ȳ�� �´�Ҵ�.
	// �׷��� �� vnum�� �������̸�, �������� ���ư� ���� �������� ������ vnum���� �ٲ㼭 ���� �ϰ�,
	// ������ ���� ���� vnum���� �ٲ��ֵ��� �Ѵ�.

	// Mask vnum�� � ����(ex. ���� ��Ȳ)�� ���� vnum�� �ٲ�� ���ư��� �������� ���� �ִ�.
	void SetMaskVnum(DWORD vnum) { m_dwMaskVnum = vnum; }
	DWORD GetMaskVnum() { return m_dwMaskVnum; }
	bool IsMaskedItem() { return m_dwMaskVnum != 0; }

#if defined(__DRAGON_SOUL_SYSTEM__)
	// ��ȥ��
	bool IsDragonSoul();

	int GiveMoreTime_Per(float fPercent);
	int GiveMoreTime_Fix(DWORD dwTime);
#endif

private:
	TItemTable const* m_pProto; // ������ Ÿ��

	DWORD m_dwVnum;
#if defined(__CHANGE_LOOK_SYSTEM__)
	DWORD m_dwTransmutationVnum;
#endif
#if defined(__SET_ITEM__)
	BYTE m_bSetValue;
#endif
	LPCHARACTER m_pOwner;

	BYTE m_bWindow; // ���� �������� ��ġ�� ������ 
	DWORD m_dwID; // ������ȣ
	bool m_bEquipped; // ���� �Ǿ��°�?
	DWORD m_dwVID; // VID
	WORD m_wCell; // ��ġ
	DWORD m_dwCount; // ����
	long m_lFlag; // �߰� flag
	DWORD m_dwLastOwnerPID; // ������ ������ �־��� ����� PID

	bool m_bExchanging; ///< ���� ��ȯ�� ����

	long m_alSockets[ITEM_SOCKET_MAX_NUM]; // ������ ��Ĺ
#if defined(__ITEM_APPLY_RANDOM__)
	TPlayerItemAttribute m_aApplyRandom[ITEM_APPLY_MAX_NUM];
#endif
	TPlayerItemAttribute m_aAttr[ITEM_ATTRIBUTE_MAX_NUM];

	LPEVENT m_pkDestroyEvent;
	LPEVENT m_pkExpireEvent;
	LPEVENT m_pkUniqueExpireEvent;
	LPEVENT m_pkTimerBasedOnWearExpireEvent;
	LPEVENT m_pkRealTimeExpireEvent;
	LPEVENT m_pkAccessorySocketExpireEvent;
	LPEVENT m_pkOwnershipEvent;

	DWORD m_dwOwnershipPID;

	bool m_bSkipSave;

	bool m_isLocked;

	DWORD m_dwMaskVnum;
	DWORD m_dwSIGVnum;

#if defined(__SOUL_BIND_SYSTEM__)
public:
	bool CanSealItem() const;

	void SealItem(long lSealDate = U_SEAL_DATE_DEFAULT_TIMESTAMP);
	bool IsSealed() const { return m_lSealDate != E_SEAL_DATE_DEFAULT_TIMESTAMP; }
	long GetSealDate() const { return m_lSealDate; }

	void StartSealDateExpireTimerEvent();
	void StopSealDateExpireTimerEvent();

private:
	long m_lSealDate;
	LPEVENT m_pkSealDateExpireEvent;
#endif

#if defined(__SOUL_SYSTEM__)
public:
	void StartSoulTimerUseEvent();
	void ResetSoulTimerUseEvent();
private:
	LPEVENT m_pkSoulTimerUseEvent;
#endif

public:
	void SetSIGVnum(DWORD dwSIG)
	{
		m_dwSIGVnum = dwSIG;
	}
	DWORD GetSIGVnum() const
	{
		return m_dwSIGVnum;
	}
};

EVENTINFO(item_event_info)
{
	LPITEM item;
	char szOwnerName[CHARACTER_NAME_MAX_LEN];

	item_event_info()
		: item(0)
	{
		::memset(szOwnerName, 0, CHARACTER_NAME_MAX_LEN);
	}
};

EVENTINFO(item_vid_event_info)
{
	DWORD item_vid;

	item_vid_event_info()
		: item_vid(0)
	{
	}
};

#endif // __INC_ITEM_H__
