#pragma once

#define DEV_PLAYERSHOP	1

#if(DEV_PLAYERSHOP)

//(фильтр включает имя, опции,заточку,анц,катогории предметов)

//gInterface.Data[eMARKET_FILTER_MAIN].Height = g_UltraDebuger.GetNumber(eULTRA_2, 440, 1);

//int iAlign = g_UltraDebuger.GetNumber(eULTRA_1, 1, 1);

#define MARKET_ITEM_BUFFER		16
#define MARKET_ITEM_MAX			100
#define MARKET_NAME_LEN			11

#define MARKET_DEBUG			0
#define MARKET_FILTER_DEV		1
#define MARKET_INTERFACE_DEV	0
#define MARKET_CATEGORY_DEV		1
#define MARKET_VIEWE_DEV		1
#define MARKET_SCROLL_DEV		1
#define MARKET_BUY_DEV			1
#define MARKET_TITLE_DEV		1
#define MARKET_PAGE_DEV			1
#define MARKET_PLAYER_BUY		1

enum
{
	eMarketPriceTypeZen = 0,
	eMarketPriceTypeWcoin = 1,
	eMarketPriceTypeCredit = 2,
};

#if(MARKET_CATEGORY_DEV)
static char* MarketCategory[] = 
{
	"Swords",
	"Axes",
	"Maces / Scepters",
	"Spears",
	"Bows / Crossbows",
	"Staffs / Books",
	"Shields",
	"Helms",
	"Armors",
	"Pants",
	"Gloves",
	"Boots",
	"Wings / Misc",
	"Pets / Misc",
	"Misc",
	"Skills",
	"All Item",
};
#endif

struct MARKET_INFO
{
	int ID;
	char Name[MARKET_NAME_LEN];
	short ItemType;
	float ItemDurability;
	BYTE ItemData[MARKET_ITEM_BUFFER];
	int PriceType;
	int Price;
};

#if(MARKET_FILTER_DEV)
struct MARKET_FILTER
{
	int FilterType;
	int FilterLevel;
	int FilterLuck;
	int FilterExl;
	int FilterAnc;
};
#endif

struct PMSG_REQ_MARKET_ITEM
{
	PBMSG_HEAD2 h;
	int Result;
	int PriceType;
	#if(MARKET_FILTER_DEV)
	MARKET_FILTER Filter;
	#endif
	#if(MARKET_PAGE_DEV)
	int PageNumber;
	#endif
};

struct PMSG_ANS_MARKET_ITEM
{
	PWMSG_HEAD2 h;
	int Result;
	MARKET_INFO Info[MARKET_ITEM_MAX];
};

struct PMSG_REQ_MARKET_SELL
{
	PBMSG_HEAD2 h;
	int Result;
	int ItemPos;
	int ItemPriceType;
	int ItemPrice;
};

struct PMSG_ANS_MARKET_SELL
{
	PBMSG_HEAD2 h;
	int Result;
};

struct PMSG_REQ_MARKET_BUY
{
	PBMSG_HEAD2 h;
	int Result;
	int ID;
};

struct PMSG_ANS_MARKET_BUY
{
	PBMSG_HEAD2 h;
	int Result;
};

class CItemMarket
{
public:
		 CItemMarket();
		 ~CItemMarket();

	void Init();
	void Load();
	void LoadIMG();
	void Bind();
	void DrawMain();
	void DrawShop();
	void DrawPrice();
	void DrawFilter(float PosX, float PosY);
	void DrawTest(float PosX, float PosY, int ItemID);

	void Keyboard(DWORD Event);
	void Mouse(MOUSEHOOKSTRUCTEX * Mouse, WPARAM wParam);

	void CGReqItemList();
	void GCAnsItemList(PMSG_ANS_MARKET_ITEM* lpMsg);
	void CGReqItemSell(int ItemPos);
	void CGAnsItemSell();
	void CGReqItemBuy();
	void GCAnsItemBuy(PMSG_ANS_MARKET_BUY* lpMsg);

	int GetItemPos(ObjectItem *Item);
	int CheckItemInfo(signed int a1);
	DWORD GetItemNameColor(int Level, int Luck, int Excellent, int Ancent, int Socket);
	ObjectItem GetItemObject(short Type, float Durability, LPBYTE Data);
	bool GetCheckMoney(int PriceType, int PriceValue);

#if(MARKET_PAGE_DEV)

	void InitPage();
	void BindPage();
	void DrawPage(float X, float Y);
	void ButtonPage(DWORD Event);

	int m_PageNumber;

#endif

	int m_ScrollPos;
	int m_ItemBuyID;
	int m_SelectItemPriceType1;
	int m_SelectItemPriceType2;
	int m_SelectItemPriceType3;
	int m_SellPriceType;
	int m_SelectItemPos;
	char m_SelectItemPrice[12];

	int m_FilterPriceType1;
	int m_FilterPriceType2;
	int m_FilterPriceType3;
	int m_FilterType;
	int m_FilterLevel;
	int m_FilterLuck;
	int m_FilterExl;
	int m_FilterAnc;
	char m_FilterName[11];

	#if(MARKET_VIEWE_DEV)
	int m_VieweNumber;
	int m_SelectNumber;	//rename
	#endif

	ObjectItem m_ItemEx;

	MARKET_INFO m_Info[MARKET_ITEM_MAX];
};

extern CItemMarket g_ItemMarket;

#endif
