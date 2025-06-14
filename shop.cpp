#include "stdafx.h"
#include "../../libgame/include/grid.h"
#include "constants.h"
#include "utils.h"
#include "config.h"
#include "shop.h"
#include "desc.h"
#include "desc_manager.h"
#include "char.h"
#include "char_manager.h"
#include "item.h"
#include "item_manager.h"
#include "buffer_manager.h"
#include "packet.h"
#include "log.h"
#include "db.h"
#include "questmanager.h"
#include "monarch.h"
#include "mob_manager.h"
#include "locale_service.h"

/* ------------------------------------------------------------------------------------ */
CShop::CShop() : m_dwVnum(0), m_dwNPCVnum(0), m_pkPC(NULL)
{
#if defined(__MYSHOP_EXPANSION__)
	m_pGrid = std::make_unique<CGrid>(SHOP_GRID_WIDTH, SHOP_GRID_HEIGHT);
	for (std::unique_ptr<CGrid>& rkTabGrid : m_apTabGrid)
		rkTabGrid = std::make_unique<CGrid>(SHOP_GRID_WIDTH, SHOP_GRID_HEIGHT);
#else
	m_pGrid = M2_NEW CGrid(SHOP_GRID_WIDTH, SHOP_GRID_HEIGHT);
#endif
}

CShop::~CShop()
{
	TPacketGCShop pack;

	pack.header = HEADER_GC_SHOP;
	pack.subheader = SHOP_SUBHEADER_GC_END;
	pack.size = sizeof(TPacketGCShop);

	Broadcast(&pack, sizeof(pack));

	GuestMapType::iterator it;

	it = m_map_guest.begin();
	while (it != m_map_guest.end())
	{
		LPCHARACTER ch = it->first;
		ch->SetShop(nullptr);
		++it;
	}

#if !defined(__MYSHOP_EXPANSION__)
	M2_DELETE(m_pGrid);
#endif
}

void CShop::SetPCShop(LPCHARACTER ch)
{
	m_pkPC = ch;
}

bool CShop::Create(DWORD dwVnum, DWORD dwNPCVnum, TShopItemTable* pTable)
{
	/*
	if (NULL == CMobManager::instance().Get(dwNPCVnum))
	{
		sys_err("No such a npc by vnum %d", dwNPCVnum);
		return false;
	}
	*/

	sys_log(0, "SHOP #%d (Shopkeeper %d)", dwVnum, dwNPCVnum);

	m_dwVnum = dwVnum;
	m_dwNPCVnum = dwNPCVnum;

	BYTE bItemCount;
	for (bItemCount = 0; bItemCount < SHOP_HOST_ITEM_MAX_NUM; ++bItemCount)
		if (0 == (pTable + bItemCount)->vnum)
			break;

	SetShopItems(pTable, bItemCount);
	return true;
}

void CShop::SetShopItems(TShopItemTable* pTable, BYTE bItemCount)
{
#if defined(__MYSHOP_EXPANSION__)
	if (bItemCount > (m_pkPC ? SHOP_HOST_ITEM_MAX : SHOP_HOST_ITEM_MAX_NUM))
		return;

	m_pGrid->Clear();

	for (std::unique_ptr<CGrid>& rkTabGrid : m_apTabGrid)
		rkTabGrid->Clear();

	m_itemVector.resize(m_pkPC ? SHOP_HOST_ITEM_MAX : SHOP_HOST_ITEM_MAX_NUM);
#else
	if (bItemCount > SHOP_HOST_ITEM_MAX_NUM)
		return;

	m_pGrid->Clear();

	m_itemVector.resize(SHOP_HOST_ITEM_MAX_NUM);
#endif

	memset(&m_itemVector[0], 0, sizeof(SHOP_ITEM) * m_itemVector.size());

	for (BYTE i = 0; i < bItemCount; ++i)
	{
		LPITEM pkItem = NULL;
		const TItemTable* item_table;

		if (m_pkPC)
		{
			pkItem = m_pkPC->GetItem(pTable->pos);

			if (!pkItem)
			{
				sys_err("cannot find item on pos (%d, %d) (name: %s)", pTable->pos.window_type, pTable->pos.cell, m_pkPC->GetName());
				continue;
			}

			item_table = pkItem->GetProto();
		}
		else
		{
			if (!pTable->vnum)
				continue;

			item_table = ITEM_MANAGER::instance().GetTable(pTable->vnum);
		}

		if (!item_table)
		{
			sys_err("Shop: no item table by item vnum #%d", pTable->vnum);
			continue;
		}

		int iPos;

		if (m_pkPC)
		{
			sys_log(0, "MyShop: use position %d", pTable->display_pos);
			iPos = pTable->display_pos;
		}
		else
			iPos = m_pGrid->FindBlank(1, item_table->bSize);

		if (iPos < 0)
		{
			sys_err("not enough shop window");
			continue;
		}

#if defined(__MYSHOP_EXPANSION__)
		if (m_pkPC)
		{
			const BYTE bTabIdx = iPos / SHOP_HOST_ITEM_MAX_NUM;
			const int iSlotPos = iPos % SHOP_HOST_ITEM_MAX_NUM;

			if (bTabIdx >= m_pkPC->GetMyPrivShopTabCount())
			{
				sys_err("no access to tab %d for pc shop %s[%d]", bTabIdx, m_pkPC->GetName(), m_pkPC->GetPlayerID());
				continue;
			}

			if (bTabIdx >= MYSHOP_MAX_TABS)
			{
				sys_err("invalid tab %d for pc shop %s[%d]", bTabIdx, m_pkPC->GetName(), m_pkPC->GetPlayerID());
				continue;
			}

			if (!m_apTabGrid[bTabIdx]->IsEmpty(iSlotPos, 1, item_table->bSize))
			{
				sys_err("not empty position for pc shop %s[%d]", m_pkPC->GetName(), m_pkPC->GetPlayerID());
				continue;
			}

			m_apTabGrid[bTabIdx]->Put(iSlotPos, 1, item_table->bSize);
		}
		else
		{
			if (!m_pGrid->IsEmpty(iPos, 1, item_table->bSize))
			{
				sys_err("not empty position for npc shop");
				continue;
			}

			m_pGrid->Put(iPos, 1, item_table->bSize);
		}
#else
		if (!m_pGrid->IsEmpty(iPos, 1, item_table->bSize))
		{
			if (IsPCShop())
			{
				sys_err("not empty position for pc shop %s[%d]", m_pkPC->GetName(), m_pkPC->GetPlayerID());
			}
			else
			{
				sys_err("not empty position for npc shop");
			}
			continue;
		}

		m_pGrid->Put(iPos, 1, item_table->bSize);
#endif

		SHOP_ITEM& item = m_itemVector[iPos];

		item.pkItem = pkItem;
		item.itemid = 0;

		if (item.pkItem)
		{
			item.vnum = pkItem->GetVnum();
			item.count = pkItem->GetCount(); // PC 샵의 경우 아이템 개수는 진짜 아이템의 개수여야 한다.
			item.price = pTable->price; // 가격도 사용자가 정한대로..
#if defined(__CHEQUE_SYSTEM__)
			item.cheque = pTable->cheque;
#endif
			item.itemid = pkItem->GetID();
		}
		else
		{
			item.vnum = pTable->vnum;
			item.count = pTable->count;

			if (IS_SET(item_table->dwFlags, ITEM_FLAG_COUNT_PER_1GOLD))
			{
				if (item_table->dwShopBuyPrice == 0)
					item.price = item.count;
				else
					item.price = item.count / item_table->dwShopBuyPrice;
			}
			else
				item.price = item_table->dwShopBuyPrice * item.count;
		}

		char name[36];
		snprintf(name, sizeof(name), "%-20s(#%-5d) (x %d)", item_table->szName, (int)item.vnum, item.count);

#if defined(__CHEQUE_SYSTEM__)
		sys_log(0, "SHOP_ITEM: %-36s PRICE %-5d CHEQUE %-5d", name, item.price, item.cheque);
#else
		sys_log(0, "SHOP_ITEM: %-36s PRICE %-5d", name, item.price);
#endif
		++pTable;
	}

	m_pGrid->Print();
}

int CShop::Buy(LPCHARACTER ch, BYTE pos
#if defined(__PRIVATESHOP_SEARCH_SYSTEM__)
	, bool bIsShopSearch
#endif
)
{
	if (pos >= m_itemVector.size())
	{
		sys_log(0, "Shop::Buy : invalid position %d : %s", pos, ch->GetName());
		return SHOP_SUBHEADER_GC_INVALID_POS;
	}

	sys_log(0, "Shop::Buy : name %s pos %d", ch->GetName(), pos);

	GuestMapType::iterator it = m_map_guest.find(ch);
	if (it == m_map_guest.end()
#if defined(__PRIVATESHOP_SEARCH_SYSTEM__)
		&& bIsShopSearch == false
#endif
		)
		return SHOP_SUBHEADER_GC_END;

	SHOP_ITEM& r_item = m_itemVector[pos];

	if (r_item.price <= 0
#if defined(__CHEQUE_SYSTEM__)
		&& r_item.cheque <= 0
#endif
		)
	{
		LogManager::instance().HackLog("SHOP_BUY_GOLD_OVERFLOW", ch);
		return SHOP_SUBHEADER_GC_NOT_ENOUGH_MONEY;
	}

	LPITEM pkSelectedItem = ITEM_MANAGER::instance().Find(r_item.itemid);

	if (IsPCShop())
	{
		if (!pkSelectedItem)
		{
#if defined(__PRIVATESHOP_SEARCH_SYSTEM__)
			if (bIsShopSearch == true)
				return SHOP_SUBHEADER_GC_SOLDOUT;
#endif

			sys_log(0, "Shop::Buy : Critical: This user seems to be a hacker : invalid pcshop item : BuyerPID:%d SellerPID:%d",
				ch->GetPlayerID(),
				m_pkPC->GetPlayerID());

			return SHOP_SUBHEADER_GC_SOLD_OUT;
		}

		if ((pkSelectedItem->GetOwner() != m_pkPC))
		{
#if defined(__PRIVATESHOP_SEARCH_SYSTEM__)
			if (bIsShopSearch == true)
				return SHOP_SUBHEADER_GC_SOLDOUT;
#endif

			sys_log(0, "Shop::Buy : Critical: This user seems to be a hacker : invalid pcshop item : BuyerPID:%d SellerPID:%d",
				ch->GetPlayerID(),
				m_pkPC->GetPlayerID());

			return SHOP_SUBHEADER_GC_SOLD_OUT;
		}
	}

	DWORD dwPrice = r_item.price;
#if defined(__CHEQUE_SYSTEM__)
	DWORD dwCheque = r_item.cheque;
#endif

#if defined(__PRIVATESHOP_SEARCH_SYSTEM__)
	if (bIsShopSearch == false && it->second) // if other empire, price is triple
		dwPrice *= 3;
#else
	if (it->second) // if other empire, price is triple
		dwPrice *= 3;
#endif

	if (ch->GetGold() < dwPrice)
	{
		sys_log(1, "Shop::Buy : Not enough money : %s has %lld, price %u", ch->GetName(), ch->GetGold(), dwPrice);
		return SHOP_SUBHEADER_GC_NOT_ENOUGH_MONEY;
	}

#if defined(__CHEQUE_SYSTEM__)
	if (ch->GetCheque() < dwCheque)
	{
		sys_log(1, "Shop::Buy : Not enough cheque : %s has %d, cheque %u", ch->GetName(), ch->GetCheque(), dwCheque);
		return SHOP_SUBHEADER_GC_NOT_ENOUGH_MONEY;
	}
#endif

	LPITEM item;

	if (m_pkPC) // 피씨가 운영하는 샵은 피씨가 실제 아이템을 가지고있어야 한다.
		item = r_item.pkItem;
	else
		item = ITEM_MANAGER::instance().CreateItem(r_item.vnum, r_item.count);

	if (!item)
		return SHOP_SUBHEADER_GC_SOLD_OUT;

	if (!m_pkPC)
	{
		if (quest::CQuestManager::instance().GetEventFlag("hivalue_item_sell") == 0)
		{
			// 축복의 구슬 && 만년한철 이벤트 
			if (item->GetVnum() == 70024 || item->GetVnum() == 70035)
			{
				return SHOP_SUBHEADER_GC_END;
			}
		}
	}

	int iEmptyPos;
#if defined(__DRAGON_SOUL_SYSTEM__)
	if (item->IsDragonSoul())
	{
		iEmptyPos = ch->GetEmptyDragonSoulInventory(item);
	}
	else
#endif
	{
		iEmptyPos = ch->GetEmptyInventory(item->GetSize());
	}

	if (iEmptyPos < 0)
	{
		if (m_pkPC)
		{
			sys_log(1, "Shop::Buy at PC Shop : Inventory full : %s size %d", ch->GetName(), item->GetSize());
			return SHOP_SUBHEADER_GC_INVENTORY_FULL;
		}
		else
		{
			sys_log(1, "Shop::Buy : Inventory full : %s size %d", ch->GetName(), item->GetSize());
			M2_DESTROY_ITEM(item);
			return SHOP_SUBHEADER_GC_INVENTORY_FULL;
		}
	}

	if (dwPrice)
		ch->PointChange(POINT_GOLD, -dwPrice, false);

#if defined(__CHEQUE_SYSTEM__)
	if (dwCheque)
		ch->PointChange(POINT_CHEQUE, -dwCheque, false);
#endif

	// 세금 계산
	DWORD dwTax = 0;
	int iVal = 0;

	if (LC_IsYMIR() || LC_IsKorea())
	{
		if (0 < (iVal = quest::CQuestManager::instance().GetEventFlag("trade_tax")))
		{
			if (iVal > 100)
				iVal = 100;

			dwTax = dwPrice * iVal / 100;
			dwPrice = dwPrice - dwTax;
		}
		else
		{
			iVal = 3;
			dwTax = dwPrice * iVal / 100;
			dwPrice = dwPrice - dwTax;
		}
	}
	else
	{
		iVal = quest::CQuestManager::instance().GetEventFlag("personal_shop");

		if (0 < iVal)
		{
			if (iVal > 100)
				iVal = 100;

			dwTax = dwPrice * iVal / 100;
			dwPrice = dwPrice - dwTax;
		}
		else
		{
			iVal = 0;
			dwTax = 0;
		}
	}

	// 상점에서 살떄 세금 5%
	if (!m_pkPC)
	{
		CMonarch::instance().SendtoDBAddMoney(dwTax, ch->GetEmpire(), ch);
	}

	// 군주 시스템 : 세금 징수
	if (m_pkPC)
	{
		m_pkPC->SyncQuickslot(SLOT_TYPE_INVENTORY, item->GetCell(), WORD_MAX);

		{
			char buf[512];

			if (item->GetVnum() >= 80003 && item->GetVnum() <= 80007)
			{
				snprintf(buf, sizeof(buf), "%s FROM: %u TO: %u PRICE: %u", item->GetName(), ch->GetPlayerID(), m_pkPC->GetPlayerID(), dwPrice);
				LogManager::instance().GoldBarLog(ch->GetPlayerID(), item->GetID(), SHOP_BUY, buf);
				LogManager::instance().GoldBarLog(m_pkPC->GetPlayerID(), item->GetID(), SHOP_SELL, buf);
			}

			item->RemoveFromCharacter();
#if defined(__DRAGON_SOUL_SYSTEM__)
			if (item->IsDragonSoul())
				item->AddToCharacter(ch, TItemPos(DRAGON_SOUL_INVENTORY, iEmptyPos));
			else
#endif
				item->AddToCharacter(ch, TItemPos(INVENTORY, iEmptyPos));
			ITEM_MANAGER::instance().FlushDelayedSave(item);

			snprintf(buf, sizeof(buf), "%s %u(%s) %u %u", item->GetName(), m_pkPC->GetPlayerID(), m_pkPC->GetName(), dwPrice, item->GetCount());
			LogManager::instance().ItemLog(ch, item, "SHOP_BUY", buf);

			snprintf(buf, sizeof(buf), "%s %u(%s) %u %u", item->GetName(), ch->GetPlayerID(), ch->GetName(), dwPrice, item->GetCount());
			LogManager::instance().ItemLog(m_pkPC, item, "SHOP_SELL", buf);
		}

		r_item.pkItem = NULL;
		BroadcastUpdateItem(pos);

		m_pkPC->PointChange(POINT_GOLD, dwPrice, false);
#if defined(__CHEQUE_SYSTEM__)
		m_pkPC->PointChange(POINT_CHEQUE, dwCheque, false);
#endif

		if (iVal > 0)
			m_pkPC->ChatPacket(CHAT_TYPE_INFO, LC_STRING("판매금액의 %d %% 가 세금으로 나가게됩니다", iVal));

		CMonarch::instance().SendtoDBAddMoney(dwTax, m_pkPC->GetEmpire(), m_pkPC);
	}
	else
	{
#if defined(__DRAGON_SOUL_SYSTEM__)
		if (item->IsDragonSoul())
			item->AddToCharacter(ch, TItemPos(DRAGON_SOUL_INVENTORY, iEmptyPos));
		else
#endif
			item->AddToCharacter(ch, TItemPos(INVENTORY, iEmptyPos));
		ITEM_MANAGER::instance().FlushDelayedSave(item);
		LogManager::instance().ItemLog(ch, item, "BUY", item->GetName());

		if (item->GetVnum() >= 80003 && item->GetVnum() <= 80007)
		{
			LogManager::instance().GoldBarLog(ch->GetPlayerID(), item->GetID(), PERSONAL_SHOP_BUY, "");
		}

		DBManager::instance().SendMoneyLog(MONEY_LOG_SHOP, item->GetVnum(), -dwPrice);
	}

	if (item)
		sys_log(0, "SHOP: BUY: name %s %s(x %d):%u price %u", ch->GetName(), item->GetName(), item->GetCount(), item->GetID(), dwPrice);

	ch->Save();

#if defined(__QUEST_EVENT_BUY_SELL__)
	ch->SetQuestNPCID(ch->GetShopOwner() ? ch->GetShopOwner()->GetVID() : 0);
	quest::CQuestManager::instance().BuyItem(ch->GetPlayerID(), GetNPCVnum(), item);
#endif

	return SHOP_SUBHEADER_GC_OK;
}

bool CShop::AddGuest(LPCHARACTER ch, DWORD owner_vid, bool bOtherEmpire)
{
	if (!ch)
		return false;

	if (ch->GetExchange())
		return false;

	if (ch->GetShop())
		return false;

	ch->SetShop(this);

	m_map_guest.insert(GuestMapType::value_type(ch, bOtherEmpire));

	TPacketGCShop pack;

	pack.header = HEADER_GC_SHOP;
	pack.subheader = SHOP_SUBHEADER_GC_START;

	TPacketGCShopStart pack2;

	memset(&pack2, 0, sizeof(pack2));
	pack2.owner_vid = owner_vid;
#if defined(__MYSHOP_DECO__)
	if (m_pkPC)
		pack2.shop_tab_count = MINMAX(1, m_pkPC->GetMyPrivShopTabCount(), MYSHOP_MAX_TABS);
	else
		pack2.shop_tab_count = 1;
#endif

#if defined(__MYSHOP_EXPANSION__)
	for (DWORD i = 0; i < m_itemVector.size() && i < (m_pkPC ? SHOP_HOST_ITEM_MAX : SHOP_HOST_ITEM_MAX_NUM); ++i)
#else
	for (DWORD i = 0; i < m_itemVector.size() && i < SHOP_HOST_ITEM_MAX_NUM; ++i)
#endif
	{
		const SHOP_ITEM& item = m_itemVector[i];

		// HIVALUE_ITEM_EVENT
		if (quest::CQuestManager::instance().GetEventFlag("hivalue_item_sell") == 0)
		{
			// 축복의 구슬 && 만년한철 이벤트 
			if (item.vnum == 70024 || item.vnum == 70035)
			{
				continue;
			}
		}
		// END_HIVALUE_ITEM_EVENT
		if (m_pkPC && !item.pkItem)
			continue;

		pack2.items[i].dwVnum = item.vnum;
		pack2.items[i].dwCount = item.count;
		if (bOtherEmpire) // no empire price penalty for pc shop
			pack2.items[i].dwPrice = item.price * 3;
		else
			pack2.items[i].dwPrice = item.price;
#if defined(__CHEQUE_SYSTEM__)
		pack2.items[i].dwCheque = item.cheque;
#endif

#if defined(__SHOPEX_RENEWAL__)
		pack2.items[i].bPriceType = SHOP_COIN_TYPE_GOLD;
		pack2.items[i].dwPriceVnum = 0;
#endif

		if (item.pkItem)
		{
			thecore_memcpy(pack2.items[i].alSockets, item.pkItem->GetSockets(), sizeof(pack2.items[i].alSockets));
			thecore_memcpy(pack2.items[i].aAttr, item.pkItem->GetAttributes(), sizeof(pack2.items[i].aAttr));
#if defined(__CHANGE_LOOK_SYSTEM__)
			pack2.items[i].dwTransmutationVnum = item.pkItem->GetTransmutationVnum();
#endif
#if defined(__REFINE_ELEMENT_SYSTEM__)
			thecore_memcpy(&pack2.items[i].RefineElement, item.pkItem->GetRefineElement(), sizeof(pack2.items[i].RefineElement));
#endif
#if defined(__ITEM_APPLY_RANDOM__)
			thecore_memcpy(pack2.items[i].aApplyRandom, item.pkItem->GetRandomApplies(), sizeof(pack2.items[i].aApplyRandom));
#endif
#if defined(__SET_ITEM__)
			pack2.items[i].bSetValue = item.pkItem->GetItemSetValue();
#endif
		}
	}

	pack.size = sizeof(pack) + sizeof(pack2);

	ch->GetDesc()->BufferedPacket(&pack, sizeof(TPacketGCShop));
	ch->GetDesc()->Packet(&pack2, sizeof(TPacketGCShopStart));
	return true;
}

void CShop::RemoveGuest(LPCHARACTER ch)
{
	if (ch->GetShop() != this)
		return;

	m_map_guest.erase(ch);
	ch->SetShop(NULL);

	TPacketGCShop pack;

	pack.header = HEADER_GC_SHOP;
	pack.subheader = SHOP_SUBHEADER_GC_END;
	pack.size = sizeof(TPacketGCShop);

	ch->GetDesc()->Packet(&pack, sizeof(pack));
}

void CShop::Broadcast(const void* data, int bytes)
{
	sys_log(1, "Shop::Broadcast %p %d", data, bytes);

	GuestMapType::iterator it;

	it = m_map_guest.begin();

	while (it != m_map_guest.end())
	{
		LPCHARACTER ch = it->first;

		if (ch->GetDesc())
			ch->GetDesc()->Packet(data, bytes);

		++it;
	}
}

void CShop::BroadcastUpdateItem(BYTE pos)
{
	TPacketGCShop pack;
	TPacketGCShopUpdateItem pack2;

	TEMP_BUFFER buf;

	pack.header = HEADER_GC_SHOP;
	pack.subheader = SHOP_SUBHEADER_GC_UPDATE_ITEM;
	pack.size = sizeof(pack) + sizeof(pack2);

	pack2.pos = pos;

	if (m_pkPC && !m_itemVector[pos].pkItem)
		pack2.item.dwVnum = 0;
	else
	{
		pack2.item.dwVnum = m_itemVector[pos].vnum;
		if (m_itemVector[pos].pkItem)
		{
			thecore_memcpy(pack2.item.alSockets, m_itemVector[pos].pkItem->GetSockets(), sizeof(pack2.item.alSockets));
			thecore_memcpy(pack2.item.aAttr, m_itemVector[pos].pkItem->GetAttributes(), sizeof(pack2.item.aAttr));
#if defined(__CHANGE_LOOK_SYSTEM__)
			pack2.item.dwTransmutationVnum = m_itemVector[pos].pkItem->GetTransmutationVnum();
#endif
#if defined(__REFINE_ELEMENT_SYSTEM__)
			thecore_memcpy(&pack2.item.RefineElement, m_itemVector[pos].pkItem->GetRefineElement(), sizeof(pack2.item.RefineElement));
#endif
#if defined(__ITEM_APPLY_RANDOM__)
			thecore_memcpy(pack2.item.aApplyRandom, m_itemVector[pos].pkItem->GetRandomApplies(), sizeof(pack2.item.aApplyRandom));
#endif
#if defined(__SET_ITEM__)
			pack2.item.bSetValue = m_itemVector[pos].pkItem->GetItemSetValue();
#endif
		}
		else
		{
			memset(pack2.item.alSockets, 0, sizeof(pack2.item.alSockets));
			memset(pack2.item.aAttr, 0, sizeof(pack2.item.aAttr));
#if defined(__CHANGE_LOOK_SYSTEM__)
			pack2.item.dwTransmutationVnum = 0;
#endif
#if defined(__REFINE_ELEMENT_SYSTEM__)
			memset(&pack2.item.RefineElement, 0, sizeof(pack2.item.RefineElement));
#endif
#if defined(__ITEM_APPLY_RANDOM__)
			memset(pack2.item.aApplyRandom, 0, sizeof(pack2.item.aApplyRandom));
#endif
#if defined(__SET_ITEM__)
			pack2.item.bSetValue = 0;
#endif
		}
	}

	pack2.item.dwPrice = m_itemVector[pos].price;
#if defined(__CHEQUE_SYSTEM__)
	pack2.item.dwCheque = m_itemVector[pos].cheque;
#endif
	pack2.item.dwCount = m_itemVector[pos].count;

	buf.write(&pack, sizeof(pack));
	buf.write(&pack2, sizeof(pack2));

	Broadcast(buf.read_peek(), buf.size());
}

int CShop::GetNumberByVnum(DWORD dwVnum)
{
	int itemNumber = 0;

#if defined(__MYSHOP_EXPANSION__)
	for (DWORD i = 0; i < m_itemVector.size() && i < (m_pkPC ? SHOP_HOST_ITEM_MAX : SHOP_HOST_ITEM_MAX_NUM); ++i)
#else
	for (DWORD i = 0; i < m_itemVector.size() && i < SHOP_HOST_ITEM_MAX_NUM; ++i)
#endif
	{
		const SHOP_ITEM& item = m_itemVector[i];

		if (item.vnum == dwVnum)
		{
			itemNumber += item.count;
		}
	}

	return itemNumber;
}

bool CShop::IsSellingItem(DWORD itemID)
{
	bool isSelling = false;

#if defined(__MYSHOP_EXPANSION__)
	for (DWORD i = 0; i < m_itemVector.size() && i < (m_pkPC ? SHOP_HOST_ITEM_MAX : SHOP_HOST_ITEM_MAX_NUM); ++i)
#else
	for (DWORD i = 0; i < m_itemVector.size() && i < SHOP_HOST_ITEM_MAX_NUM; ++i)
#endif
	{
		if (m_itemVector[i].itemid == itemID)
		{
			isSelling = true;
			break;
		}
	}

	return isSelling;
}
