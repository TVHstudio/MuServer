#pragma once
// ----------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "Object.h"
#ifdef _ITEM_PRICE_MANAGER_
// ----------------------------------------------------------------------------------------------

#define ITEMPRICE_DEBUG		0
#define MAX_ITEMPRICE_ITEM	512
// ----------------------------------------------------------------------------------------------

enum ePrice
{
	eZen,
	eCredit,
	eWCoin,
	eWCoinP,
	eGoblinPoint,
};
// ----------------------------------------------------------------------------------------------

struct ITEMPRICE_DATA
{
	WORD ItemType;
	WORD ItemIndex;
	BYTE ItemLevel;
	BYTE PriceType;
	__int64 Price;
};
// ----------------------------------------------------------------------------------------------

class ItemPrice
{
public:
	ItemPrice();
	~ItemPrice();
	// ----
	bool			Enable;
	bool			SellItemNullZen;
	// ----
	bool			ShowItem;
	int				ShowType;
	int				ShowItemLevel;
	__int64			ShowPrice;
	// ----
	void			Init();
	void			ReadList(char * File);
	void			Load();
	bool			CheckItemSell(short ItemCode, int ItemLevel, __int64 * Price);
	bool			CheckItemBuy(short ItemCode, int ItemLevel, __int64 * Price);
	// ----
	static __int64	GetPrice(ObjectItem * lpItem, int Mode);
	static void		ShowSellPrice(DWORD a1, const char *a2, char *Price);
	static void		ShowBuyPrice(DWORD a1, const char *a2, char *Price);
	static void		ShowItemLevelName(DWORD a1, const char *a2, char * Level);
	static int		PriceItemDiv(int a1, int a2);
	// ----
private:
	int				m_LoadedSellCount;
	int				m_LoadedBuyCount;
	// ----
	ITEMPRICE_DATA	m_SellData[MAX_ITEMPRICE_ITEM];
	ITEMPRICE_DATA	m_BuyData[MAX_ITEMPRICE_ITEM];
	// ----
}; extern ItemPrice gItemPrice;
// ----------------------------------------------------------------------------------------------

/*
INT3 breakpoints
Address   Module    Status       Disassembly                              Comment
0047428E  Main      Active       MOV EAX,DWORD PTR DS:[EDX+2]
004F4295  Main      Active       MOV EAX,DWORD PTR DS:[EDX+2]
0051BC8D  Main      Active       MOV EAX,DWORD PTR DS:[EDX+2]
00780CAE  Main      Active       MOV EAX,DWORD PTR DS:[EDX+2]
00780E40  Main      Active       MOV EAX,DWORD PTR DS:[EDX+2]
00799EA0  Main      Active       MOV EAX,DWORD PTR DS:[EDX+2]
007D9B5C  Main      Active       MOV EAX,DWORD PTR DS:[EDX+2]
007DA9F4  Main      Active       MOV EAX,DWORD PTR DS:[EDX+2]
007DFAF3  Main      Active       MOV EAX,DWORD PTR DS:[EDX+2]
007E0484  Main      Active       MOV EAX,DWORD PTR DS:[EDX+2]
007E3D64  Main      Active       JMP 5ADA5F70
00834E45  Main      Active       MOV EAX,DWORD PTR DS:[EDX+2]
00836FE5  Main      Active       MOV EAX,DWORD PTR DS:[EDX+2]
008382F6  Main      Active       MOV EAX,DWORD PTR DS:[EDX+2]
00839CCC  Main      Active       MOV EAX,DWORD PTR DS:[EDX+2]
0083A2EE  Main      Active       MOV EAX,DWORD PTR DS:[EDX+2]
0083AAC5  Main      Active       MOV EAX,DWORD PTR DS:[EDX+2]
008FF344  Main      Active       MOV EAX,DWORD PTR DS:[EDX+2]
0095F5C4  Main      Active       MOV EAX,DWORD PTR DS:[EDX+2]
0096818C  Main      Active       MOV EAX,DWORD PTR DS:[EDX+2]
00968B1C  Main      Active       MOV EAX,DWORD PTR DS:[EDX+2]


007DA9F4
007E0484

007D9B5C
00836FE5
*/
#endif