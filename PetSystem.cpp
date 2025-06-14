#include "stdafx.h"

#if defined(__PET_SYSTEM__)
#include "utils.h"
#include "vector.h"
#include "char.h"
#include "sectree_manager.h"
#include "char_manager.h"
#include "mob_manager.h"
#include "PetSystem.h"
#include "../../common/VnumHelper.h"
#include "packet.h"
#include "item_manager.h"
#include "item.h"
#include "config.h"
#if defined(__LOOT_FILTER_SYSTEM__)
#include "LootFilter.h"
#endif

EVENTINFO(petsystem_event_info)
{
	CPetSystem* pPetSystem;
};

// PetSystem聖 update 背爽澗 event.
// PetSystem精 CHRACTER_MANAGER拭辞 奄糎 FSM生稽 update 背爽澗 奄糎 chracters人 含軒,
// Owner税 STATE研 update 拝 凶 _UpdateFollowAI 敗呪稽 update 背層陥.
// 益訓汽 owner税 state研 update研 CHRACTER_MANAGER拭辞 背爽奄 凶庚拭,
// petsystem聖 update馬陥亜 pet聖 unsummon馬澗 採歳拭辞 庚薦亜 持医陥.
// (CHRACTER_MANAGER拭辞 update 馬檎 chracter destroy亜 pending鞠嬢, CPetSystem拭辞澗 dangling 匂昔斗研 亜走壱 赤惟 吉陥.)
// 魚虞辞 PetSystem幻 穣汽戚闘 背爽澗 event研 降持獣鉄.
EVENTFUNC(petsystem_update_event)
{
	petsystem_event_info* info = dynamic_cast<petsystem_event_info*>(event->info);
	if (!info)
	{
		sys_err("check_speedhack_event> <Factor> Null pointer");
		return 0;
	}

	CPetSystem* pPetSystem = info->pPetSystem;
	if (!pPetSystem)
		return 0;

	pPetSystem->Update(0);

	// 0.25段原陥 飴重.
	return PASSES_PER_SEC(1) / 4;
}

/// NOTE: 1蝶遣斗亜 護鯵税 楢聖 亜霜 呪 赤澗走 薦廃... 蝶遣斗原陥 鯵呪研 陥牽惟 拝暗虞檎 痕呪稽 隔去亜... 製..
/// 亜霜 呪 赤澗 鯵呪人 疑獣拭 社発拝 呪 赤澗 鯵呪亜 堂険 呪 赤澗汽 戚訓闇 奄塙 蒸生艦 析舘 巷獣
const float PET_COUNT_LIMIT = 3;

///////////////////////////////////////////////////////////////////////////////////////
// CPetActor
///////////////////////////////////////////////////////////////////////////////////////

CPetActor::CPetActor(LPCHARACTER owner, DWORD vnum, DWORD options)
{
	m_dwVnum = vnum;
	m_dwVID = 0;
	m_dwOptions = options;
	m_dwLastActionTime = 0;

	m_pkChar = 0;
	m_pkOwner = owner;

	m_originalMoveSpeed = 0;

	m_dwSummonItemVID = 0;
	m_dwSummonItemVnum = 0;
}

CPetActor::~CPetActor()
{
	this->Unsummon();

	m_pkOwner = 0;
}

void CPetActor::SetName(const char* name)
{
	std::string petName = m_pkOwner->GetName();

#if defined(__LOCALE_CLIENT__)
	if (IsSummoned())
		m_pkChar->SetName(petName);
#else
	if (0 != m_pkOwner &&
		0 == name &&
		0 != m_pkOwner->GetName())
	{
		petName += "'s Pet";
	}
	else
		petName += name;
#endif

	m_name = petName;
}

bool CPetActor::Mount()
{
	if (!m_pkOwner)
		return false;

	if (HasOption(EPetOption_Mountable))
		m_pkOwner->MountVnum(m_dwVnum);

	return m_pkOwner->GetMountVnum() == m_dwVnum;
}

void CPetActor::Unmount()
{
	if (!m_pkOwner)
		return;

	if (m_pkOwner->IsHorseRiding())
		m_pkOwner->StopRiding();
}

void CPetActor::Unsummon()
{
	if (this->IsSummoned())
	{
		// 獄覗 肢薦
		this->ClearBuff();
		this->SetSummonItem(NULL);

		if (m_pkOwner)
		{
			m_pkOwner->ComputePoints();
#if defined(__SET_ITEM__)
			m_pkOwner->RefreshItemSetBonus();
#endif
		}

		if (m_pkChar)
			M2_DESTROY_CHARACTER(m_pkChar);

		m_pkChar = 0;
		m_dwVID = 0;
	}
}

DWORD CPetActor::Summon(const char* petName, LPITEM pSummonItem, bool bSpawnFar)
{
	if (SECTREE_MANAGER::Instance().IsBlockFilterMapIndex(SECTREE_MANAGER::PET_BLOCK_MAP_INDEX, m_pkOwner->GetMapIndex()))
	{
		m_pkOwner->ChatPacket(CHAT_TYPE_INFO, LC_STRING("You cannot summon your mount/pet right now."));
		return 0;
	}

	long x = m_pkOwner->GetX();
	long y = m_pkOwner->GetY();
	long z = m_pkOwner->GetZ();

	if (bSpawnFar)
	{
		x += (number(0, 1) * 2 - 1) * number(2000, 2500);
		y += (number(0, 1) * 2 - 1) * number(2000, 2500);
	}
	else
	{
		x += number(-100, 100);
		y += number(-100, 100);
	}

	if (m_pkChar)
	{
		m_pkChar->Show(m_pkOwner->GetMapIndex(), x, y);
		m_dwVID = m_pkChar->GetVID();

		return m_dwVID;
	}

	m_pkChar = CHARACTER_MANAGER::instance().SpawnMob(
		m_dwVnum,
		m_pkOwner->GetMapIndex(),
		x, y, z,
		false, static_cast<int>(m_pkOwner->GetRotation() + 180), false);

	if (!m_pkChar)
	{
		sys_err("[CPetSystem::Summon] Failed to summon the pet. (vnum: %d)", m_dwVnum);
		return 0;
	}

	m_pkChar->SetPet();

	//m_pkOwner->DetailLog();
	//m_pkChar->DetailLog();

	// 楢税 厩亜研 爽昔税 厩亜稽 竺舛敗.
	m_pkChar->SetEmpire(m_pkOwner->GetEmpire());

	m_dwVID = m_pkChar->GetVID();

	this->SetName(petName);

	//SetSummonItem(pSummonItem)研 採献 板拭 ComputePoints研 採牽檎 獄覗 旋遂喫.
	this->SetSummonItem(pSummonItem);
	m_pkOwner->ComputePoints();
#if defined(__SET_ITEM__)
	m_pkOwner->RefreshItemSetBonus();
#endif
	m_pkChar->Show(m_pkOwner->GetMapIndex(), x, y, z);

	return m_dwVID;
}

bool CPetActor::_UpdatAloneActionAI(float fMinDist, float fMaxDist)
{
	float fDist = fnumber(fMinDist, fMaxDist);
	float r = static_cast<float>(number(0, 359));
	float dest_x = GetOwner()->GetX() + fDist * cos(r);
	float dest_y = GetOwner()->GetY() + fDist * sin(r);

	//m_pkChar->SetRotation(number(0, 359)); // 号狽精 沓棋生稽 竺舛

	//GetDeltaByDegree(m_pkChar->GetRotation(), fDist, &fx, &fy);

	// 汗充廃 公姶 紗失 端滴; 置曽 是帖人 掻娃 是帖亜 哀呪蒸陥檎 亜走 省澗陥.
	/*
	if (!(SECTREE_MANAGER::instance().IsMovablePosition(m_pkChar->GetMapIndex(), m_pkChar->GetX() + (int) fx, m_pkChar->GetY() + (int) fy)
		&& SECTREE_MANAGER::instance().IsMovablePosition(m_pkChar->GetMapIndex(), m_pkChar->GetX() + (int) fx/2, m_pkChar->GetY() + (int) fy/2)))
		return true;
	*/

	m_pkChar->SetNowWalking(true);

	// if (m_pkChar->Goto(m_pkChar->GetX() + (int) fx, m_pkChar->GetY() + (int) fy))
		// m_pkChar->SendMovePacket(FUNC_WAIT, 0, 0, 0, 0);
	if (!m_pkChar->IsStateMove() && m_pkChar->Goto((long)dest_x, (long)dest_y))
		m_pkChar->SendMovePacket(FUNC_WAIT, 0, 0, 0, 0);

	m_dwLastActionTime = get_dword_time();

	return true;
}

// char_state.cpp StateHorse敗呪 益撹 C&P -_-;
bool CPetActor::_UpdateFollowAI()
{
	if (!m_pkChar->m_pkMobData)
	{
		//sys_err("[CPetActor::_UpdateFollowAI] m_pkChar->m_pkMobData is NULL");
		return false;
	}

	// NOTE: 蝶遣斗(楢)税 据掘 戚疑 紗亀研 硝焼醤 馬澗汽, 背雁 葵(m_pkChar->m_pkMobData->m_table.sMovingSpeed)聖 送羨旋生稽 羨悦背辞 硝焼馨 呪亀 赤走幻
	// m_pkChar->m_pkMobData 葵戚 invalid廃 井酔亜 切爽 降持敗. 薄仙 獣娃淫域雌 据昔精 陥製拭 督焦馬壱 析舘精 m_pkChar->m_pkMobData 葵聖 焼森 紫遂馬走 省亀系 敗.
	// 食奄辞 古腰 伊紫馬澗 戚政澗 置段 段奄鉢 拝 凶 舛雌 葵聖 薦企稽 公条嬢神澗 井酔亀 赤製.. -_-;; ばばばばばばばばば
	if (!m_originalMoveSpeed)
	{
		const CMob* mobData = CMobManager::Instance().Get(m_dwVnum);
		if (mobData)
			m_originalMoveSpeed = mobData->m_table.sMovingSpeed;
	}

	float START_FOLLOW_DISTANCE = 300.0f; // 戚 暗軒 戚雌 恭嬢走檎 耐焼亜奄 獣拙敗
	float START_RUN_DISTANCE = 900.0f; // 戚 暗軒 戚雌 恭嬢走檎 禽嬢辞 耐焼姶.

	float RESPAWN_DISTANCE = 4500.f; // 戚 暗軒 戚雌 菰嬢走檎 爽昔 新生稽 社発敗.
	int APPROACH = 200; // 羨悦 暗軒

	bool bDoMoveAlone = true; // 蝶遣斗人 亜猿戚 赤聖 凶 肇切 食奄煽奄 崇送析闇走 食採 -_-;
	bool bRun = false; // 禽嬢醤 馬蟹?

	DWORD currentTime = get_dword_time();

	long ownerX = m_pkOwner->GetX(); long ownerY = m_pkOwner->GetY();
	long charX = m_pkChar->GetX(); long charY = m_pkChar->GetY();

	float fDist = DISTANCE_APPROX(charX - ownerX, charY - ownerY);

	if (fDist >= RESPAWN_DISTANCE)
	{
		float fOwnerRot = m_pkOwner->GetRotation() * 3.141592f / 180.f;
		float fx = -APPROACH * cos(fOwnerRot);
		float fy = -APPROACH * sin(fOwnerRot);

		if (m_pkChar->Show(m_pkOwner->GetMapIndex(), ownerX + fx, ownerY + fy))
			return true;
	}

	if (fDist >= START_FOLLOW_DISTANCE)
	{
		if (fDist >= START_RUN_DISTANCE)
			bRun = true;

		m_pkChar->SetNowWalking(!bRun); // NOTE: 敗呪 戚硯左壱 誇蓄澗闇匝 硝紹澗汽 SetNowWalking(false) 馬檎 禽澗暗績.. -_-;

		Follow(APPROACH);

		m_pkChar->SetLastAttacked(currentTime);
		m_dwLastActionTime = currentTime;
	}
	/*
	else
	{
		if (fabs(m_pkChar->GetRotation() - GetDegreeFromPositionXY(charX, charY, ownerX, ownerX)) > 10.f || fabs(m_pkChar->GetRotation() - GetDegreeFromPositionXY(charX, charY, ownerX, ownerX)) < 350.f)
		{
			m_pkChar->Follow(m_pkOwner, APPROACH);
			m_pkChar->SetLastAttacked(currentTime);
			m_dwLastActionTime = currentTime;
		}
	}
	*/
	// Follow 掻戚走幻 爽昔引 析舛 暗軒 戚鎧稽 亜猿趨然陥檎 誇茶
	else
		m_pkChar->SendMovePacket(FUNC_WAIT, 0, 0, 0, 0);
	/*
	else if (currentTime - m_dwLastActionTime > number(5000, 12000))
	{
		this->_UpdatAloneActionAI(START_FOLLOW_DISTANCE / 2, START_FOLLOW_DISTANCE);
	}
	*/

	return true;
}

bool CPetActor::Update(DWORD deltaTime)
{
	bool bResult = true;

	// 楢 爽昔戚 宋醸暗蟹, 社発吉 楢税 雌殿亜 戚雌馬陥檎 楢聖 蒸証. (NOTE: 亜懐亜陥 戚訓 煽訓 戚政稽 社発吉 楢戚 DEAD 雌殿拭 匙走澗 井酔亜 赤製-_-;)
	// 楢聖 社発廃 焼戚奴戚 蒸暗蟹, 鎧亜 亜遭 雌殿亜 焼艦虞檎 楢聖 蒸証.
	if (m_pkOwner->IsDead() || (IsSummoned() && m_pkChar->IsDead())
		|| !ITEM_MANAGER::instance().FindByVID(this->GetSummonItemVID())
		|| ITEM_MANAGER::instance().FindByVID(this->GetSummonItemVID())->GetOwner() != this->GetOwner()
		)
	{
		//this->Unsummon();
		return true;
	}

	if (this->IsSummoned() && HasOption(EPetOption_Followable))
		bResult = bResult && this->_UpdateFollowAI();

#if defined(__PET_LOOT_AI__)
	if (this->IsSummoned() && HasOption(EPetOption_Lootable))
		this->_UpdateLoot();
#endif

	return bResult;
}

// NOTE : 爽税!!! MinDistance研 滴惟 説生檎 益 痕是幻鏑税 痕鉢疑照精 follow馬走 省澗陥,
bool CPetActor::Follow(float fMinDist)
{
	// 亜形澗 是帖研 郊虞坐醤 廃陥.
	if (!m_pkOwner || !m_pkChar)
		return false;

	float fOwnerX = static_cast<float>(m_pkOwner->GetX());
	float fOwnerY = static_cast<float>(m_pkOwner->GetY());

	float fPetX = static_cast<float>(m_pkChar->GetX());
	float fPetY = static_cast<float>(m_pkChar->GetY());

	float fDist = DISTANCE_SQRT(fOwnerX - fPetX, fOwnerY - fPetY);
	if (fDist <= fMinDist)
		return false;

	m_pkChar->SetRotationToXY(fOwnerX, fOwnerY);

	float fx, fy;
	float fDistToGo = fDist - fMinDist;
	GetDeltaByDegree(m_pkChar->GetRotation(), fDistToGo, &fx, &fy);

	if (!m_pkChar->Goto(static_cast<int>(fPetX + fx + 0.5f), static_cast<int>(fPetY + fy + 0.5f)))
		return false;

	m_pkChar->SendMovePacket(FUNC_WAIT, 0, 0, 0, 0, 0);

	return true;
}

void CPetActor::SetSummonItem(LPITEM pItem)
{
	if (!pItem)
	{
		LPITEM pSummonItem = ITEM_MANAGER::instance().FindByVID(m_dwSummonItemVID);
		if (pSummonItem)
			pSummonItem->SetSocket(1, false);

		m_dwSummonItemVID = 0;
		m_dwSummonItemVnum = 0;
		return;
	}

	pItem->SetSocket(1, true);
	m_dwSummonItemVID = pItem->GetVID();
	m_dwSummonItemVnum = pItem->GetVnum();
}

void CPetActor::GiveBuff()
{
	if (!CheckBuff(this))
		return;

	LPITEM pSummonItem = ITEM_MANAGER::instance().FindByVID(m_dwSummonItemVID);
	if (pSummonItem)
		pSummonItem->ModifyPoints(true);
}

void CPetActor::ClearBuff()
{
	if (NULL == m_pkOwner)
		return;

	TItemTable* pItemProto = ITEM_MANAGER::instance().GetTable(m_dwSummonItemVnum);
	if (pItemProto == nullptr)
		return;

	if (!CheckBuff(this))
		return;

	for (BYTE bIndex = 0; bIndex < ITEM_APPLY_MAX_NUM; bIndex++)
	{
		if (pItemProto->aApplies[bIndex].wType == APPLY_NONE)
			continue;

		m_pkOwner->ApplyPoint(pItemProto->aApplies[bIndex].wType, -pItemProto->aApplies[bIndex].lValue);
	}

	return;
}

bool CPetActor::CheckBuff(const CPetActor* pPetActor)
{
	bool bMustHaveBuff = true;
	switch (pPetActor->GetVnum())
	{
		case 34004:
		case 34009:
		{
			if (!pPetActor->GetOwner()->GetDungeon())
				bMustHaveBuff = false;
		}
		break;
	}

	return bMustHaveBuff;
}

#if defined(__PET_LOOT_AI__)
struct FuncPetActorLoot
{
	CPetActor* m_pPetActor;
	float m_fMaxDist;

	FuncPetActorLoot(CPetActor* pPetActor, float fMaxDist) : m_pPetActor(pPetActor), m_fMaxDist(fMaxDist) {}

	void operator()(LPENTITY pEntity)
	{
		const LPCHARACTER pPetOwner = m_pPetActor->GetOwner();
		if (!pPetOwner)
			return;

		if (pEntity->IsType(ENTITY_ITEM))
		{
			const LPITEM pItem = reinterpret_cast<LPITEM>(pEntity);
			if (!pItem)
				return;

			if (!pItem->GetSectree() || !pItem->IsOwnership(pPetOwner))
				return;

#if defined(__LOOT_FILTER_SYSTEM__)
			if (pPetOwner->GetLootFilter() && !pPetOwner->GetLootFilter()->CanPickUpItem(pItem))
				return;
#endif

			float fDist = DISTANCE_APPROX(pItem->GetX() - pPetOwner->GetX(), pItem->GetY() - pPetOwner->GetY());
			if (fDist > m_fMaxDist)
				return;

			m_pPetActor->Loot(pItem->GetVID());
		}
	}
};

void CPetActor::_UpdateLoot(float fMaxDist)
{
	if (!m_pkChar || !m_pkOwner)
		return;

	if (m_pkOwner->IsDead() || m_pkOwner->IsWarping())
		return;

	LPSECTREE pSectree = SECTREE_MANAGER::Instance().Get(m_pkChar->GetMapIndex(), m_pkChar->GetX(), m_pkChar->GetY());
	if (pSectree)
	{
		FuncPetActorLoot f(this, fMaxDist);
		pSectree->ForEachAround(f);
	}
}

bool CPetActor::Loot(DWORD dwVID, float fMinDist)
{
	if (!m_pkOwner || !m_pkChar)
		return false;

	if (!HasOption(EPetOption_Lootable))
		return false;

	const LPITEM pItem = ITEM_MANAGER::Instance().FindByVID(dwVID);
	if (!pItem)
		return false;

	if (!pItem->GetSectree() || !pItem->IsOwnership(m_pkOwner))
		return false;

#if defined(__LOOT_FILTER_SYSTEM__)
	if (m_pkOwner->GetLootFilter() && !m_pkOwner->GetLootFilter()->CanPickUpItem(pItem))
		return false;
#endif

	float fItemX = static_cast<float>(pItem->GetX());
	float fItemY = static_cast<float>(pItem->GetY());

	float fPetX = static_cast<float>(m_pkChar->GetX());
	float fPetY = static_cast<float>(m_pkChar->GetY());

	const float fDist = DISTANCE_SQRT(fItemX - fPetX, fItemY - fPetY);
	if (fDist <= fMinDist)
	{
		m_pkOwner->PickupItem(dwVID, true);
		m_pkChar->SendMovePacket(FUNC_WAIT, 0, 0, 0, 0, 0);
		return true;
	}

	m_pkChar->SetRotationToXY(fItemX, fItemY);

	float fX, fY;
	float fDistToGo = fDist - 20.0f;
	GetDeltaByDegree(m_pkChar->GetRotation(), fDistToGo, &fX, &fY);

	if (!m_pkChar->Goto(static_cast<int>(fPetX + fX + 0.5f), static_cast<int>(fPetY + fY + 0.5f)))
		return false;

	m_pkChar->SendMovePacket(FUNC_WAIT, 0, 0, 0, 0, 0);
	return true;
}
#endif

///////////////////////////////////////////////////////////////////////////////////////
// CPetSystem
///////////////////////////////////////////////////////////////////////////////////////

CPetSystem::CPetSystem(LPCHARACTER owner)
{
	//assert(0 != owner && "[CPetSystem::CPetSystem] Invalid owner");

	m_pkOwner = owner;
	m_dwUpdatePeriod = 400;

	m_dwLastUpdateTime = 0;
}

CPetSystem::~CPetSystem()
{
	Destroy();
}

void CPetSystem::Destroy()
{
	for (auto& it : m_petActorMap)
	{
		CPetActor* petActor = it.second;
		if (petActor)
			delete petActor;
	}

	event_cancel(&m_pkPetSystemUpdateEvent);
	m_petActorMap.clear();
}

/// 楢 獣什奴 穣汽戚闘. 去系吉 楢級税 AI 坦軒 去聖 敗.
bool CPetSystem::Update(DWORD deltaTime)
{
	bool bResult = true;

	DWORD currentTime = get_dword_time();

	// CHARACTER_MANAGER拭辞 蝶遣斗嫌 Update拝 凶 古鯵痕呪稽 爽澗 (Pulse虞壱 鞠嬢赤澗)葵戚 戚穿 覗傾績引税 獣娃託戚昔匝 硝紹澗汽
	// 穿粕 陥献 葵戚虞辞-_-; 食奄拭 脊径生稽 級嬢神澗 deltaTime精 税耕亜 蒸製ばば

	if (m_dwUpdatePeriod > currentTime - m_dwLastUpdateTime)
		return true;

	std::vector<CPetActor*> v_garbageActor;
	for (const auto& it : m_petActorMap)
	{
		if (auto* petActor = it.second; petActor && petActor->IsSummoned())
		{
			if (!CHARACTER_MANAGER::instance().Find(petActor->GetCharacter()->GetVID()))
				v_garbageActor.push_back(petActor);
			else
				bResult = bResult && petActor->Update(deltaTime);
		}
	}

	for (auto petActor : v_garbageActor)
		DeletePet(petActor);

	m_dwLastUpdateTime = currentTime;

	return bResult;
}

/// 淫軒 鯉系拭辞 楢聖 走崇
void CPetSystem::DeletePet(DWORD mobVnum)
{
	auto it = m_petActorMap.find(mobVnum);
	if (m_petActorMap.end() == it)
	{
		sys_err("[CPetSystem::DeletePet] Can't find pet on my list (VNUM: %d)", mobVnum);
		return;
	}

	CPetActor* petActor = it->second;
	if (!petActor)
		sys_err("[CPetSystem::DeletePet] Null Pointer (petActor)");
	else
		delete petActor;

	m_petActorMap.erase(it);
}

/// 淫軒 鯉系拭辞 楢聖 走崇
void CPetSystem::DeletePet(CPetActor* petActor)
{
	auto it = std::find_if(m_petActorMap.begin(), m_petActorMap.end(),
		[petActor](const auto& it) { return it.second == petActor; });

	if (it != m_petActorMap.end())
	{
		delete petActor;
		m_petActorMap.erase(it);
	}
	else
	{
		sys_err("[CPetSystem::DeletePet] Can't find petActor(0x%x) on my list(size: %d) ", petActor, m_petActorMap.size());
	}
}

void CPetSystem::Unsummon(DWORD vnum, bool bDeleteFromList)
{
	CPetActor* petActor = this->GetByVnum(vnum);
	if (!petActor)
	{
		sys_err("[CPetSystem::GetByVnum(%d)] Null Pointer (petActor)", vnum);
		return;
	}
	petActor->Unsummon();

	if (true == bDeleteFromList)
		this->DeletePet(petActor);

	bool bActive = std::any_of(m_petActorMap.begin(), m_petActorMap.end(),
		[](const auto& it) { return it.second->IsSummoned(); });

	if (!bActive)
	{
		event_cancel(&m_pkPetSystemUpdateEvent);
		m_pkPetSystemUpdateEvent = nullptr;
	}
}

CPetActor* CPetSystem::Summon(DWORD mobVnum, LPITEM pSummonItem, const char* petName, bool bSpawnFar, DWORD options)
{
	CPetActor* petActor = this->GetByVnum(mobVnum);

	// 去系吉 楢戚 焼艦虞檎 歯稽 持失 板 淫軒 鯉系拭 去系敗.
	if (!petActor)
	{
		petActor = M2_NEW CPetActor(m_pkOwner, mobVnum, options);
		m_petActorMap.insert(std::make_pair(mobVnum, petActor));
	}

	DWORD petVID = petActor->Summon(petName, pSummonItem, bSpawnFar);

	if (!m_pkPetSystemUpdateEvent)
	{
		petsystem_event_info* info = AllocEventInfo<petsystem_event_info>();
		info->pPetSystem = this;
		m_pkPetSystemUpdateEvent = event_create(petsystem_update_event, info, PASSES_PER_SEC(1) / 4); // 0.25 seconds.
	}

	return petActor;
}

CPetActor* CPetSystem::GetByVID(DWORD vid) const
{
	for (const auto& it : m_petActorMap)
	{
		CPetActor* petActor = it.second;
		if (!petActor)
		{
			sys_err("[CPetSystem::GetByVID(%d)] Null Pointer (petActor)");
			continue;
		}

		if (petActor->GetVID() == vid)
			return petActor;
	}

	return nullptr;
}

/// 去系 吉 楢 掻拭辞 爽嬢遭 光 VNUM聖 亜遭 衝斗研 鋼発馬澗 敗呪.
CPetActor* CPetSystem::GetByVnum(DWORD vnum) const
{
	if (auto it = m_petActorMap.find(vnum); it != m_petActorMap.end())
		return it->second;
	return nullptr;
}

DWORD CPetSystem::GetVnum() const
{
	for (const auto& it : m_petActorMap)
		if (auto* petActor = it.second; petActor && petActor->IsSummoned())
			return it.first;
	return 0;
}

DWORD CPetSystem::GetSummonItemVID() const
{
	for (const auto& it : m_petActorMap)
		if (auto* petActor = it.second; petActor && petActor->IsSummoned())
			return petActor->GetSummonItemVID();
	return 0;
}

DWORD CPetSystem::GetSummonItemVnum() const
{
	for (const auto& it : m_petActorMap)
		if (auto* petActor = it.second; petActor && petActor->IsSummoned())
			return petActor->GetSummonItemVnum();
	return 0;
}

size_t CPetSystem::CountSummoned() const
{
	size_t count = 0;
	for (const auto& it : m_petActorMap)
		if (auto* petActor = it.second; petActor && petActor->IsSummoned())
			++count;
	return count;
}

void CPetSystem::RefreshBuff()
{
	for (const auto& it : m_petActorMap)
		if (auto* petActor = it.second; petActor && petActor->IsSummoned())
			petActor->GiveBuff();
}

#if defined(__PET_LOOT__)
bool CPetSystem::SummonedLooter() const
{
	for (const auto& it : m_petActorMap)
		if (auto* petActor = it.second; petActor && petActor->IsSummoned())
			return petActor->HasOption(CPetActor::EPetOption_Lootable);
	return false;
}

bool CPetSystem::LootItem(const LPITEM pItem)
{
	bool bLoot = false;

	for (const auto& it : m_petActorMap)
	{
		if (auto* petActor = it.second; petActor && petActor->IsSummoned())
		{
			if (petActor->HasOption(CPetActor::EPetOption_Lootable))
			{
				bLoot = true;
				break;
			}
		}
	}

#if defined(__LOOT_FILTER_SYSTEM__)
	if (bLoot && m_pkOwner->GetLootFilter() && !m_pkOwner->GetLootFilter()->CanPickUpItem(pItem))
	{
		m_pkOwner->ChatPacket(CHAT_TYPE_INFO, LC_STRING("No loot will be collected as the loot filter is deactivated."));
		return false;
	}
#endif

	return bLoot;
}
#endif
#endif // __PET_SYSTEM__
