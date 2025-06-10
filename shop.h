#ifndef __INC_SHOP_H__
#define __INC_SHOP_H__

enum
{
	SHOP_MAX_DISTANCE = 1000,
};

class CGrid;

/* ---------------------------------------------------------------------------------- */
class CShop
{
public:
	enum EShopGrid
	{
		SHOP_GRID_WIDTH = 5,
		SHOP_GRID_HEIGHT = 9,
	};

	typedef struct shop_item
	{
		DWORD vnum; // ������ ��ȣ
		long price; // ����
#if defined(__CHEQUE_SYSTEM__)
		long cheque;
#endif
		DWORD count; // ������ ����

		LPITEM pkItem;
		int itemid; // ������ �������̵�

#if defined(__SHOPEX_RENEWAL__)
		BYTE bPriceType;
		DWORD dwPriceVnum;
		long alSockets[ITEM_SOCKET_MAX_NUM];
#endif

		shop_item()
		{
			vnum = 0;
			price = 0;
#if defined(__CHEQUE_SYSTEM__)
			cheque = 0;
#endif
			count = 0;
			itemid = 0;
			pkItem = NULL;

#if defined(__SHOPEX_RENEWAL__)
			bPriceType = SHOP_COIN_TYPE_GOLD;
			dwPriceVnum = 0;
			memset(&alSockets, 0, sizeof(alSockets));
#endif
		}
	} SHOP_ITEM;

	CShop();
	virtual ~CShop();

	bool Create(DWORD dwVnum, DWORD dwNPCVnum, TShopItemTable* pItemTable);
	void SetShopItems(TShopItemTable* pItemTable, BYTE bItemCount);

	virtual void SetPCShop(LPCHARACTER ch);
	virtual bool IsPCShop() { return m_pkPC ? true : false; }
#if defined(__SHOPEX_RENEWAL__)
	virtual bool IsShopEx() const { return false; };
#endif

	// �Խ�Ʈ �߰�/����
	virtual bool AddGuest(LPCHARACTER ch, DWORD owner_vid, bool bOtherEmpire);
	void RemoveGuest(LPCHARACTER ch);

	// ���� ����
	virtual int Buy(LPCHARACTER ch, BYTE pos
#if defined(__PRIVATESHOP_SEARCH_SYSTEM__)
		, bool bIsShopSearch = false
#endif
	);

	// �Խ�Ʈ���� ��Ŷ�� ����
	void BroadcastUpdateItem(BYTE pos);

	// �Ǹ����� �������� ������ �˷��ش�.
	int GetNumberByVnum(DWORD dwVnum);

	// �������� ������ ��ϵǾ� �ִ��� �˷��ش�.
	virtual bool IsSellingItem(DWORD itemID);

	DWORD GetVnum() { return m_dwVnum; }
	DWORD GetNPCVnum() { return m_dwNPCVnum; }

#if defined(__PRIVATESHOP_SEARCH_SYSTEM__)
	const std::vector<SHOP_ITEM>& GetItemVector() const { return m_itemVector; }
	LPCHARACTER GetShopOwner() { return m_pkPC; }
#endif

protected:
	void Broadcast(const void* data, int bytes);

protected:
	DWORD m_dwVnum;
	DWORD m_dwNPCVnum;

#if defined(__MYSHOP_EXPANSION__)
	std::unique_ptr<CGrid> m_pGrid;
	std::array<std::unique_ptr<CGrid>, MYSHOP_MAX_TABS> m_apTabGrid;
#else
	CGrid* m_pGrid;
#endif

	typedef std::unordered_map<LPCHARACTER, bool> GuestMapType;
	GuestMapType m_map_guest;
	std::vector<SHOP_ITEM> m_itemVector; // �� �������� ����ϴ� ���ǵ�

	LPCHARACTER m_pkPC;
};

#endif // __INC_SHOP_H__
