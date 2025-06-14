#include "stdafx.h"
#include "../../libgame/include/grid.h"
#include "utils.h"
#include "desc.h"
#include "desc_client.h"
#include "char.h"
#include "item.h"
#include "item_manager.h"
#include "packet.h"
#include "log.h"
#include "db.h"
#include "locale_service.h"
#include "../../common/length.h"
#include "exchange.h"
#include "questmanager.h"
#include "DragonSoul.h"
#if defined(__PET_SYSTEM__)
#	include "PetSystem.h"
#endif
#if defined(__MESSENGER_BLOCK_SYSTEM__)
#	include "messenger_manager.h"
#endif

void exchange_packet(LPCHARACTER ch, BYTE sub_header, bool is_me, DWORD arg1, TItemPos arg2, DWORD arg3, void* pvData = NULL);

// 교환 패킷
void exchange_packet(LPCHARACTER ch, BYTE sub_header, bool is_me, DWORD arg1, TItemPos arg2, DWORD arg3, void* pvData)
{
	if (!ch->GetDesc())
		return;

	struct packet_exchange pack_exchg;

	pack_exchg.header = HEADER_GC_EXCHANGE;
	pack_exchg.sub_header = sub_header;
	pack_exchg.is_me = is_me;
	pack_exchg.arg1 = arg1;
	pack_exchg.arg2 = arg2;
	pack_exchg.arg3 = arg3;

	if (sub_header == EXCHANGE_SUBHEADER_GC_ITEM_ADD && pvData)
	{
		pack_exchg.arg4 = TItemPos(((LPITEM)pvData)->GetWindow(), ((LPITEM)pvData)->GetCell());

		thecore_memcpy(&pack_exchg.alSockets, ((LPITEM)pvData)->GetSockets(), sizeof(pack_exchg.alSockets));
		thecore_memcpy(&pack_exchg.aAttr, ((LPITEM)pvData)->GetAttributes(), sizeof(pack_exchg.aAttr));
#if defined(__CHANGE_LOOK_SYSTEM__)
		pack_exchg.dwTransmutationVnum = static_cast<LPITEM>(pvData)->GetTransmutationVnum();
#endif
#if defined(__REFINE_ELEMENT_SYSTEM__)
		thecore_memcpy(&pack_exchg.RefineElement, ((LPITEM)pvData)->GetRefineElement(), sizeof(pack_exchg.RefineElement));
#endif
#if defined(__ITEM_APPLY_RANDOM__)
		thecore_memcpy(&pack_exchg.aApplyRandom, ((LPITEM)pvData)->GetRandomApplies(), sizeof(pack_exchg.aApplyRandom));
#endif
#if defined(__SET_ITEM__)
		pack_exchg.bSetItem = static_cast<LPITEM>(pvData)->GetItemSetValue();
#endif
	}
	else
	{
		pack_exchg.arg4 = TItemPos(RESERVED_WINDOW, 0);

		memset(&pack_exchg.alSockets, 0, sizeof(pack_exchg.alSockets));
		memset(&pack_exchg.aAttr, 0, sizeof(pack_exchg.aAttr));
#if defined(__CHANGE_LOOK_SYSTEM__)
		pack_exchg.dwTransmutationVnum = 0;
#endif
#if defined(__REFINE_ELEMENT_SYSTEM__)
		memset(&pack_exchg.RefineElement, 0, sizeof(pack_exchg.RefineElement));
#endif
#if defined(__ITEM_APPLY_RANDOM__)
		memset(&pack_exchg.aApplyRandom, 0, sizeof(pack_exchg.aApplyRandom));
#endif
#if defined(__SET_ITEM__)
		pack_exchg.bSetItem = 0;
#endif
	}

	ch->GetDesc()->Packet(&pack_exchg, sizeof(pack_exchg));
}

// 교환을 시작
bool CHARACTER::ExchangeStart(LPCHARACTER victim)
{
	if (this == victim) // 자기 자신과는 교환을 못한다.
		return false;

	if (IsObserverMode())
	{
		ChatPacket(CHAT_TYPE_INFO, LC_STRING("관전 상태에서는 교환을 할 수 없습니다."));
		return false;
	}

	if (victim->IsRunningQuest())
	{
		ChatPacket(CHAT_TYPE_INFO, LC_STRING("The other person is currently busy so you cannot trade right now."));
		return false;
	}

	if (IsRunningQuest())
		return false;

	if (victim->IsNPC())
		return false;

#if defined(__MESSENGER_BLOCK_SYSTEM__)
	if (CMessengerManager::instance().IsBlocked(GetName(), victim->GetName()))
	{
		ChatPacket(CHAT_TYPE_INFO, LC_STRING("Unblock %s to continue.", victim->GetName()));
		return false;
	}
	else if (CMessengerManager::instance().IsBlocked(victim->GetName(), GetName()))
	{
		ChatPacket(CHAT_TYPE_INFO, LC_STRING("%s has blocked you.", victim->GetName()));
		return false;
	}
#endif

	// PREVENT_TRADE_WINDOW
	if (PreventTradeWindow(WND_EXCHANGE, true/*except*/))
	{
		ChatPacket(CHAT_TYPE_INFO, LC_STRING("다른 거래창이 열려있을경우 거래를 할수 없습니다."));
		return false;
	}

	if (victim->PreventTradeWindow(WND_EXCHANGE, true/*except*/))
	{
		ChatPacket(CHAT_TYPE_INFO, LC_STRING("상대방이 다른 거래중이라 거래를 할수 없습니다."));
		return false;
	}
	// END_PREVENT_TRADE_WINDOW

	int iDist = DISTANCE_APPROX(GetX() - victim->GetX(), GetY() - victim->GetY());

	// 거리 체크
	if (iDist >= EXCHANGE_MAX_DISTANCE)
		return false;

	if (GetExchange())
		return false;

	if (victim->GetExchange())
	{
		exchange_packet(this, EXCHANGE_SUBHEADER_GC_ALREADY, 0, 0, NPOS, 0);
		return false;
	}

	if (victim->IsBlockMode(BLOCK_EXCHANGE))
	{
		ChatPacket(CHAT_TYPE_INFO, LC_STRING("상대방이 교환 거부 상태입니다."));
		return false;
	}

	SetExchange(M2_NEW CExchange(this));
	victim->SetExchange(M2_NEW CExchange(victim));

	victim->GetExchange()->SetCompany(GetExchange());
	GetExchange()->SetCompany(victim->GetExchange());

	//
	SetExchangeTime();
	victim->SetExchangeTime();

	exchange_packet(victim, EXCHANGE_SUBHEADER_GC_START, 0, GetVID(), NPOS, 0);
	exchange_packet(this, EXCHANGE_SUBHEADER_GC_START, 0, victim->GetVID(), NPOS, 0);

	return true;
}

CExchange::CExchange(LPCHARACTER pOwner)
{
	m_pCompany = NULL;

	m_bAccept = false;

	for (int i = 0; i < EXCHANGE_ITEM_MAX_NUM; ++i)
	{
		m_apItems[i] = NULL;
		m_aItemPos[i] = NPOS;
		m_abItemDisplayPos[i] = 0;
	}

	m_lGold = 0;
#if defined(__CHEQUE_SYSTEM__)
	m_lCheque = 0;
#endif

	m_pOwner = pOwner;
	pOwner->SetExchange(this);

	m_pGrid = M2_NEW CGrid(4, 3);
}

CExchange::~CExchange()
{
	M2_DELETE(m_pGrid);
}

bool CExchange::AddItem(TItemPos item_pos, BYTE display_pos)
{
	assert(m_pOwner != NULL && GetCompany());

	if (!item_pos.IsValidItemPosition())
		return false;

	// 장비는 교환할 수 없음
	if (item_pos.IsEquipPosition())
		return false;

	LPITEM item;

	if (!(item = m_pOwner->GetItem(item_pos)))
		return false;

	if (IS_SET(item->GetAntiFlag(), ITEM_ANTIFLAG_GIVE))
	{
		m_pOwner->ChatPacket(CHAT_TYPE_INFO, LC_STRING("아이템을 건네줄 수 없습니다."));
		return false;
	}

	if (true == item->isLocked())
		return false;

#if defined(__PET_SYSTEM__)
	CPetSystem* pPetSystem = m_pOwner->GetPetSystem();
	if (pPetSystem && pPetSystem->GetSummonItemVID() == item->GetVID())
		return false;
#endif

#if defined(__SOUL_BIND_SYSTEM__)
	if (item->IsSealed())
	{
		m_pOwner->ChatPacket(CHAT_TYPE_INFO, LC_STRING("You cannot give away a soulbound item."));
		return false;
	}
#endif

	// 이미 교환창에 추가된 아이템인가?
	if (item->IsExchanging())
	{
		sys_log(0, "EXCHANGE under exchanging");
		return false;
	}

	if (!m_pGrid->IsEmpty(display_pos, 1, item->GetSize()))
	{
		sys_log(0, "EXCHANGE not empty item_pos %d %d %d", display_pos, 1, item->GetSize());
		return false;
	}

	Accept(false);
	GetCompany()->Accept(false);

	for (int i = 0; i < EXCHANGE_ITEM_MAX_NUM; ++i)
	{
		if (m_apItems[i])
			continue;

		m_apItems[i] = item;
		m_aItemPos[i] = item_pos;
		m_abItemDisplayPos[i] = display_pos;
		m_pGrid->Put(display_pos, 1, item->GetSize());

		item->SetExchanging(true);

		exchange_packet(m_pOwner,
			EXCHANGE_SUBHEADER_GC_ITEM_ADD,
			true,
			item->GetVnum(),
			TItemPos(RESERVED_WINDOW, display_pos),
			item->GetCount(),
			item);

		exchange_packet(GetCompany()->GetOwner(),
			EXCHANGE_SUBHEADER_GC_ITEM_ADD,
			false,
			item->GetVnum(),
			TItemPos(RESERVED_WINDOW, display_pos),
			item->GetCount(),
			item);

		sys_log(0, "EXCHANGE AddItem success %s pos(%d, %d) %d", item->GetName(), item_pos.window_type, item_pos.cell, display_pos);

		return true;
	}

	// 추가할 공간이 없음
	return false;
}

bool CExchange::RemoveItem(BYTE pos)
{
	if (pos >= EXCHANGE_ITEM_MAX_NUM)
		return false;

	if (!m_apItems[pos])
		return false;

	TItemPos PosOfInventory = m_aItemPos[pos];
	m_apItems[pos]->SetExchanging(false);

	m_pGrid->Get(m_abItemDisplayPos[pos], 1, m_apItems[pos]->GetSize());

	exchange_packet(GetOwner(), EXCHANGE_SUBHEADER_GC_ITEM_DEL, true, pos, NPOS, 0);
	exchange_packet(GetCompany()->GetOwner(), EXCHANGE_SUBHEADER_GC_ITEM_DEL, false, pos, PosOfInventory, 0);

	Accept(false);
	GetCompany()->Accept(false);

	m_apItems[pos] = NULL;
	m_aItemPos[pos] = NPOS;
	m_abItemDisplayPos[pos] = 0;
	return true;
}

bool CExchange::AddGold(long gold)
{
	if (gold <= 0 || gold > EXCHANGE_YANG_MAX)
		return false;

	if (GetOwner()->GetGold() < gold)
	{
		// 가지고 있는 돈이 부족.
		exchange_packet(GetOwner(), EXCHANGE_SUBHEADER_GC_LESS_GOLD, 0, 0, NPOS, 0);
		return false;
	}

	if (LC_IsCanada() == true || LC_IsEurope() == true)
	{
		if (m_lGold > 0)
		{
			return false;
		}
	}

	Accept(false);
	GetCompany()->Accept(false);

	m_lGold = gold;

	exchange_packet(GetOwner(), EXCHANGE_SUBHEADER_GC_GOLD_ADD, true, m_lGold, NPOS, 0);
	exchange_packet(GetCompany()->GetOwner(), EXCHANGE_SUBHEADER_GC_GOLD_ADD, false, m_lGold, NPOS, 0);
	return true;
}

#if defined(__CHEQUE_SYSTEM__)
bool CExchange::AddCheque(long cheque)
{
	if (cheque <= 0 || cheque > EXCHANGE_CHEQUE_MAX)
		return false;

	if (GetOwner()->GetCheque() < cheque)
	{
		exchange_packet(GetOwner(), EXCHANGE_SUBHEADER_GC_LESS_CHEQUE, 0, 0, NPOS, 0);
		return false;
	}

	LPCHARACTER victim = GetCompany()->GetOwner();

	if (m_lCheque)
	{
		long vic_cheque = victim->GetCheque() + m_lCheque;
		if (vic_cheque > CHEQUE_MAX)
		{
			exchange_packet(GetOwner(), EXCHANGE_SUBHEADER_GC_LESS_CHEQUE, 0, 0, NPOS, 0);
			GetOwner()->ChatPacket(CHAT_TYPE_INFO, LC_STRING("This user can not accept that much cheque."));
			return false;
		}
	}

	if (LC_IsCanada() == true || LC_IsEurope() == true)
	{
		if (m_lCheque > 0)
		{
			return false;
		}
	}

	Accept(false);
	GetCompany()->Accept(false);

	m_lCheque = cheque;

	exchange_packet(GetOwner(), EXCHANGE_SUBHEADER_GC_CHEQUE_ADD, true, m_lCheque, NPOS, 0);
	exchange_packet(GetCompany()->GetOwner(), EXCHANGE_SUBHEADER_GC_CHEQUE_ADD, false, m_lCheque, NPOS, 0);
	return true;
}
#endif

// 돈이 충분히 있는지, 교환하려는 아이템이 실제로 있는지 확인 한다.
bool CExchange::Check(int* piItemCount)
{
	if (GetOwner()->GetGold() < m_lGold)
		return false;

#if defined(__CHEQUE_SYSTEM__)
	if (GetOwner()->GetCheque() < m_lCheque)
		return false;
#endif

	int item_count = 0;

	for (int i = 0; i < EXCHANGE_ITEM_MAX_NUM; ++i)
	{
		if (!m_apItems[i])
			continue;

		if (!m_aItemPos[i].IsValidItemPosition())
			return false;

		if (m_apItems[i] != GetOwner()->GetItem(m_aItemPos[i]))
			return false;

		++item_count;
	}

	*piItemCount = item_count;
	return true;
}

bool CExchange::CheckSpace()
{
	static CGrid s_grid1(5, INVENTORY_MAX_NUM / 5 / INVENTORY_PAGE_COUNT);
	static CGrid s_grid2(5, INVENTORY_MAX_NUM / 5 / INVENTORY_PAGE_COUNT);
#if defined(__EXTEND_INVEN_SYSTEM__)
	static CGrid s_grid3(5, INVENTORY_MAX_NUM / 5 / INVENTORY_PAGE_COUNT);
	static CGrid s_grid4(5, INVENTORY_MAX_NUM / 5 / INVENTORY_PAGE_COUNT);
#endif

	s_grid1.Clear();
	s_grid2.Clear();
#if defined(__EXTEND_INVEN_SYSTEM__)
	s_grid3.Clear();
	s_grid4.Clear();
#endif

	LPCHARACTER victim = GetCompany()->GetOwner();
	LPITEM item;

	int i;

	for (i = 0; i < INVENTORY_PAGE_SIZE * 1; ++i)
	{
		if (!(item = victim->GetInventoryItem(i)))
			continue;

		s_grid1.Put(i, 1, item->GetSize());
	}
	for (i = INVENTORY_PAGE_SIZE * 1; i < INVENTORY_PAGE_SIZE * 2; ++i)
	{
		if (!(item = victim->GetInventoryItem(i)))
			continue;

		s_grid2.Put(i - INVENTORY_PAGE_SIZE * 1, 1, item->GetSize());
	}
#if defined(__EXTEND_INVEN_SYSTEM__)
	for (i = INVENTORY_PAGE_SIZE * 2; i < INVENTORY_PAGE_SIZE * 3; ++i)
	{
		if (!(item = victim->GetInventoryItem(i)))
			continue;

		s_grid3.Put(i - INVENTORY_PAGE_SIZE * 2, 1, item->GetSize());
	}
	for (i = INVENTORY_PAGE_SIZE * 3; i < INVENTORY_PAGE_SIZE * 4; ++i)
	{
		if (!(item = victim->GetInventoryItem(i)))
			continue;

		s_grid4.Put(i - INVENTORY_PAGE_SIZE * 3, 1, item->GetSize());
	}
#endif

#if defined(__DRAGON_SOUL_SYSTEM__)
	// 아... 뭔가 개병신 같지만... 용혼석 인벤을 노멀 인벤 보고 따라 만든 내 잘못이다 ㅠㅠ
	static std::vector <WORD> s_vDSGrid(DRAGON_SOUL_INVENTORY_MAX_NUM);

	// 일단 용혼석을 교환하지 않을 가능성이 크므로, 용혼석 인벤 복사는 용혼석이 있을 때 하도록 한다.
	bool bDSInitialized = false;
#endif

	for (i = 0; i < EXCHANGE_ITEM_MAX_NUM; ++i)
	{
		if (!(item = m_apItems[i]))
			continue;

#if defined(__DRAGON_SOUL_SYSTEM__)
		if (item->IsDragonSoul())
		{
			if (!victim->DragonSoul_IsQualified())
				return false;

			if (!bDSInitialized)
			{
				bDSInitialized = true;
				victim->CopyDragonSoulItemGrid(s_vDSGrid);
			}

			bool bExistEmptySpace = false;
			WORD wBasePos = DSManager::instance().GetBasePosition(item);
			if (wBasePos >= DRAGON_SOUL_INVENTORY_MAX_NUM)
				return false;

			for (int i = 0; i < DRAGON_SOUL_BOX_SIZE; i++)
			{
				WORD wPos = wBasePos + i;
				if (0 == s_vDSGrid[wPos])
				{
					bool bEmpty = true;
					for (int j = 1; j < item->GetSize(); j++)
					{
						if (s_vDSGrid[wPos + j * DRAGON_SOUL_BOX_COLUMN_NUM])
						{
							bEmpty = false;
							break;
						}
					}
					if (bEmpty)
					{
						for (int j = 0; j < item->GetSize(); j++)
						{
							s_vDSGrid[wPos + j * DRAGON_SOUL_BOX_COLUMN_NUM] = wPos + 1;
						}
						bExistEmptySpace = true;
						break;
					}
				}
				if (bExistEmptySpace)
					break;
			}
			if (!bExistEmptySpace)
				return false;
		}
		else
#endif
		{
			int iPos;

			if ((iPos = s_grid1.FindBlank(1, item->GetSize())) >= 0)
				s_grid1.Put(iPos, 1, item->GetSize());
			else if ((iPos = s_grid2.FindBlank(1, item->GetSize())) >= 0)
				s_grid2.Put(iPos, 1, item->GetSize());
#if defined(__EXTEND_INVEN_SYSTEM__)
			else if ((iPos = s_grid3.FindBlank(1, item->GetSize())) >= 0)
			{
				int iExtendMaxPos = (INVENTORY_WIDTH * victim->GetExtendInvenStage()) - 1;
				if (iPos > iExtendMaxPos)
					return false;

				if (item->GetSize() > 1)
				{
					iExtendMaxPos -= (INVENTORY_WIDTH * (item->GetSize() - 1));
					if (iPos > iExtendMaxPos)
						return false;
				}
				s_grid3.Put(iPos, 1, item->GetSize());
			}
			else if ((iPos = s_grid4.FindBlank(1, item->GetSize())) >= 0)
			{
				int iExtendMaxPos = (INVENTORY_WIDTH * (victim->GetExtendInvenStage() - INVENTORY_HEIGHT)) - 1;
				if (iPos > iExtendMaxPos)
					return false;

				if (item->GetSize() > 1)
				{
					iExtendMaxPos -= (INVENTORY_WIDTH * (item->GetSize() - 1));
					if (iPos > iExtendMaxPos)
						return false;
				}
				s_grid4.Put(iPos, 1, item->GetSize());
			}
#endif
			else
				return false; // No space left in inventory
		}
	}

	return true;
}

// 교환 끝 (아이템과 돈 등을 실제로 옮긴다)
bool CExchange::Done()
{
	int empty_pos, i;
	LPITEM item;

	LPCHARACTER victim = GetCompany()->GetOwner();

#if defined(__CHEQUE_SYSTEM__)
	if (m_lCheque)
	{
		long vic_cheque = victim->GetCheque() + m_lCheque;
		if (vic_cheque > CHEQUE_MAX)
		{
			// exchange_packet(GetOwner(), EXCHANGE_SUBHEADER_GC_LESS_CHEQUE, 0, 0, NPOS, 0);
			GetOwner()->ChatPacket(CHAT_TYPE_INFO, LC_STRING("The has reached cheque limit."));
			return false;
		}
	}
#endif

	for (i = 0; i < EXCHANGE_ITEM_MAX_NUM; ++i)
	{
		if (!(item = m_apItems[i]))
			continue;

#if defined(__DRAGON_SOUL_SYSTEM__)
		if (item->IsDragonSoul())
			empty_pos = victim->GetEmptyDragonSoulInventory(item);
		else
#endif
			empty_pos = victim->GetEmptyInventory(item->GetSize());

		if (empty_pos < 0)
		{
			sys_err("Exchange::Done : Cannot find blank position in inventory %s <-> %s item %s",
				m_pOwner->GetName(), victim->GetName(), item->GetName());
			continue;
		}

		if (empty_pos < 0)
		{
			sys_err("Exchange::Done : Cannot find blank position in inventory %s <-> %s item %s",
					m_pOwner->GetName(), victim->GetName(), item->GetName());
			continue;
		}

		assert(empty_pos >= 0);

		m_pOwner->SyncQuickslot(SLOT_TYPE_INVENTORY, item->GetCell(), WORD_MAX);

		item->RemoveFromCharacter();
#if defined(__DRAGON_SOUL_SYSTEM__)
		if (item->IsDragonSoul())
			item->AddToCharacter(victim, TItemPos(DRAGON_SOUL_INVENTORY, empty_pos));
		else
#endif
			item->AddToCharacter(victim, TItemPos(INVENTORY, empty_pos));
		ITEM_MANAGER::instance().FlushDelayedSave(item);

		item->SetExchanging(false);
		{
			char exchange_buf[51];

			snprintf(exchange_buf, sizeof(exchange_buf), "%s %u %u", item->GetName(), GetOwner()->GetPlayerID(), item->GetCount());
			LogManager::instance().ItemLog(victim, item, "EXCHANGE_TAKE", exchange_buf);

			snprintf(exchange_buf, sizeof(exchange_buf), "%s %u %u", item->GetName(), victim->GetPlayerID(), item->GetCount());
			LogManager::instance().ItemLog(GetOwner(), item, "EXCHANGE_GIVE", exchange_buf);

			if (item->GetVnum() >= 80003 && item->GetVnum() <= 80007)
			{
				LogManager::instance().GoldBarLog(victim->GetPlayerID(), item->GetID(), EXCHANGE_TAKE, "");
				LogManager::instance().GoldBarLog(GetOwner()->GetPlayerID(), item->GetID(), EXCHANGE_GIVE, "");
			}

			m_pOwner->CreateFly(FLY_SP_MEDIUM, victim);
			for (int i = 0; i < 3; i++)
				m_pOwner->CreateFly(FLY_SP_SMALL, victim);
		}

		m_apItems[i] = NULL;
	}

	if (m_lGold)
	{
		GetOwner()->PointChange(POINT_GOLD, -m_lGold, true);
		victim->PointChange(POINT_GOLD, m_lGold, true);

		if (m_lGold > 1000)
		{
			char exchange_buf[51];
			snprintf(exchange_buf, sizeof(exchange_buf), "%u %s", GetOwner()->GetPlayerID(), GetOwner()->GetName());
			LogManager::instance().CharLog(victim, m_lGold, "EXCHANGE_GOLD_TAKE", exchange_buf);

			snprintf(exchange_buf, sizeof(exchange_buf), "%u %s", victim->GetPlayerID(), victim->GetName());
			LogManager::instance().CharLog(GetOwner(), m_lGold, "EXCHANGE_GOLD_GIVE", exchange_buf);
		}
	}

#if defined(__CHEQUE_SYSTEM__)
	if (m_lCheque)
	{
		GetOwner()->PointChange(POINT_CHEQUE, -m_lCheque, true);
		victim->PointChange(POINT_CHEQUE, m_lCheque, true);

		if (m_lCheque > 1000)
		{
			char exchange_buf[51];
			snprintf(exchange_buf, sizeof(exchange_buf), "%u %s", GetOwner()->GetPlayerID(), GetOwner()->GetName());
			LogManager::instance().CharLog(victim, m_lCheque, "EXCHANGE_GOLD_TAKE", exchange_buf);

			snprintf(exchange_buf, sizeof(exchange_buf), "%u %s", victim->GetPlayerID(), victim->GetName());
			LogManager::instance().CharLog(GetOwner(), m_lCheque, "EXCHANGE_GOLD_GIVE", exchange_buf);
		}
	}
#endif

	m_pGrid->Clear();
	return true;
}

// 교환을 동의
bool CExchange::Accept(bool bAccept)
{
	if (m_bAccept == bAccept)
		return true;

	m_bAccept = bAccept;

	// 둘 다 동의 했으므로 교환 성립
	if (m_bAccept && GetCompany()->m_bAccept)
	{
		int iItemCount;

		LPCHARACTER victim = GetCompany()->GetOwner();

		// PREVENT_PORTAL_AFTER_EXCHANGE
		GetOwner()->SetExchangeTime();
		victim->SetExchangeTime();
		// END_PREVENT_PORTAL_AFTER_EXCHANGE

		if (GetOwner()->IsRunningQuest() || victim->IsRunningQuest())
			goto EXCHANGE_END;
	
		// exchange_check 에서는 교환할 아이템들이 제자리에 있나 확인하고,
		// 엘크도 충분히 있나 확인한다, 두번째 인자로 교환할 아이템 개수
		// 를 리턴한다.
		if (!Check(&iItemCount))
		{
			GetOwner()->ChatPacket(CHAT_TYPE_INFO, LC_STRING("돈이 부족하거나 아이템이 제자리에 없습니다."));
			victim->ChatPacket(CHAT_TYPE_INFO, LC_STRING("상대방의 돈이 부족하거나 아이템이 제자리에 없습니다."));
			goto EXCHANGE_END;
		}

		// 리턴 받은 아이템 개수로 상대방의 소지품에 남은 자리가 있나 확인한다.
		if (!CheckSpace())
		{
			GetOwner()->ChatPacket(CHAT_TYPE_INFO, LC_STRING("상대방의 소지품에 빈 공간이 없습니다."));
			victim->ChatPacket(CHAT_TYPE_INFO, LC_STRING("소지품에 빈 공간이 없습니다."));
			goto EXCHANGE_END;
		}

		// 상대방도 마찬가지로..
		if (!GetCompany()->Check(&iItemCount))
		{
			victim->ChatPacket(CHAT_TYPE_INFO, LC_STRING("돈이 부족하거나 아이템이 제자리에 없습니다."));
			GetOwner()->ChatPacket(CHAT_TYPE_INFO, LC_STRING("상대방의 돈이 부족하거나 아이템이 제자리에 없습니다."));
			goto EXCHANGE_END;
		}

		if (!GetCompany()->CheckSpace())
		{
			victim->ChatPacket(CHAT_TYPE_INFO, LC_STRING("상대방의 소지품에 빈 공간이 없습니다."));
			GetOwner()->ChatPacket(CHAT_TYPE_INFO, LC_STRING("소지품에 빈 공간이 없습니다."));
			goto EXCHANGE_END;
		}

		if (db_clientdesc->GetSocket() == INVALID_SOCKET)
		{
			sys_err("Cannot use exchange feature while DB cache connection is dead.");
			victim->ChatPacket(CHAT_TYPE_INFO, "Unknown error");
			GetOwner()->ChatPacket(CHAT_TYPE_INFO, "Unknown error");
			goto EXCHANGE_END;
		}

		if (Done())
		{
			if (m_lGold) // 돈이 있을 떄만 저장
				GetOwner()->Save();

#if defined(__CHEQUE_SYSTEM__)
			if (m_lCheque)
				GetOwner()->Save();
#endif

			if (GetCompany()->Done())
			{
				if (GetCompany()->m_lGold) // 돈이 있을 때만 저장
					victim->Save();

#if defined(__CHEQUE_SYSTEM__)
				if (GetCompany()->m_lCheque)
					victim->Save();
#endif

				// INTERNATIONAL_VERSION
				GetOwner()->ChatPacket(CHAT_TYPE_INFO, LC_STRING("%s 님과의 교환이 성사 되었습니다.", victim->GetName()));
				victim->ChatPacket(CHAT_TYPE_INFO, LC_STRING("%s 님과의 교환이 성사 되었습니다.", GetOwner()->GetName()));
				// END_OF_INTERNATIONAL_VERSION
			}
		}

	EXCHANGE_END:
		Cancel();
		return false;
	}
	else
	{
		// 아니면 accept에 대한 패킷을 보내자.
		exchange_packet(GetOwner(), EXCHANGE_SUBHEADER_GC_ACCEPT, true, m_bAccept, NPOS, 0);
		exchange_packet(GetCompany()->GetOwner(), EXCHANGE_SUBHEADER_GC_ACCEPT, false, m_bAccept, NPOS, 0);
		return true;
	}
}

// 교환 취소
void CExchange::Cancel()
{
	exchange_packet(GetOwner(), EXCHANGE_SUBHEADER_GC_END, 0, 0, NPOS, 0);
	GetOwner()->SetExchange(NULL);

	for (int i = 0; i < EXCHANGE_ITEM_MAX_NUM; ++i)
	{
		if (m_apItems[i])
			m_apItems[i]->SetExchanging(false);
	}

	if (GetCompany())
	{
		GetCompany()->SetCompany(NULL);
		GetCompany()->Cancel();
	}

	M2_DELETE(this);
}
