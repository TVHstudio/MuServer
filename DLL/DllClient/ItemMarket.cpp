#include "stdafx.h"
#include "Interface.h"
#include "Protocol.h"
#include "Object.h"
#include "Controller.h"
#include "ItemMarket.h"
#include "Console.h"
#include "TMemory.h"
#include "Console.h"
#include "ItemPacket.h"
//#include "UltraDebuger.h"
#include "Item.h"

#if(DEV_PLAYERSHOP)

CItemMarket g_ItemMarket;

CItemMarket::CItemMarket()
{
	this->Init();
}

CItemMarket::~CItemMarket()
{
}

void CItemMarket::Init()
{
	this->m_ScrollPos = 0;

	this->m_ItemBuyID = -1;

	this->m_SelectItemPos = -1;

	this->m_SelectItemPriceType1 = 1;

	this->m_SelectItemPriceType2 = 0;

	this->m_SelectItemPriceType3 = 0;

	this->m_SellPriceType = 0;

	memset(this->m_SelectItemPrice, 0, sizeof(this->m_SelectItemPrice));

	sprintf(this->m_SelectItemPrice, "0");

	this->m_FilterType = 16;

	this->m_FilterLevel = 0;

	this->m_FilterLuck = 0;

	this->m_FilterExl = 0;

	this->m_FilterAnc = 0;

	#if(MARKET_VIEWE_DEV)

	this->m_VieweNumber = -1;

	this->m_SelectNumber = -1;

	#endif

	#if(MARKET_PAGE_DEV)

	this->InitPage();

	#endif
}

void CItemMarket::Load()
{
	this->Init();
}

void CItemMarket::LoadIMG()
{

}

void CItemMarket::Bind()
{
	gInterface.BindObject(eMARKET_MAIN, 0x7A5A, 222, 440, -1, -1);

	gInterface.BindObject(eMARKET_TITLE, 0x7A63, 230, 67, -1, -1);

	//gInterface.BindObject(eMARKET_TITLE, 0x7A57, 230, 67, -1, -1);

	gInterface.BindObject(eMARKET_FRAME, 0x7A58, 230, 15, -1, -1);

	gInterface.BindObject(eMARKET_FOOTER, 0x7A59, 230, 50, -1, -1);

	gInterface.BindObject(eMARKET_DIV, 0x7A62, 223, 21, -1, -1);

	gInterface.BindObject(eMARKET_OK, 0x7A5F, 62, 27, -1, -1);

	gInterface.BindObject(eMARKET_CLOSE, 0x7A5F, 62, 27, -1, -1);

	gInterface.BindObject(eMARKET_INFOBG, 0x7AA3, 170, 21, -1, -1);

	gInterface.BindObject(eMARKET_INFOBG2, 0x7AA1, 170, 22, -1, -1);

	gInterface.BindObject(eMARKET_INFOBG3, zt_TEXT_BOX3, 170, 21, -1, -1);

	gInterface.BindObject(eMARKET_SCROLL, 0x7A29, 15, 30, -1, -1);

	gInterface.BindObject(eMARKET_BUY, 0x7A5E, 108, 29, -1, -1);


	gInterface.BindObject(eMARKET_PRICE_MAIN, 0x7A5A, 222, 166, -1, -1);

	gInterface.BindObject(eMARKET_PRICE_TITLE, 0x7A63, 230, 67, -1, -1);

	gInterface.BindObject(eMARKET_PRICE_FRAME, 0x7A58, 230, 15, -1, -1);

	gInterface.BindObject(eMARKET_PRICE_FOOTER, 0x7A59, 230, 50, -1, -1);

	gInterface.BindObject(eMARKET_PRICE_OK, 0x7A5F, 62, 27, -1, -1);

	gInterface.BindObject(eMARKET_PRICE_CLOSE, 0x7A5F, 62, 27, -1, -1);

	gInterface.BindObject(eMARKET_PRICE_INFOBG, 0x7AA3, 170, 21, -1, -1);

	gInterface.BindObject(eMARKET_PRICE_POINT, 0x7B68, 10, 10, -1, -1);

	gInterface.BindObject(eMARKET_PRICE_LINE, 0x7B67, 154, 3, -1, -1);

	gInterface.BindObject(eMARKET_PRICE_CHECK1, 0x7B69, 15, 15, -1, -1);

	gInterface.BindObject(eMARKET_PRICE_CHECK2, 0x7B69, 15, 15, -1, -1);

	gInterface.BindObject(eMARKET_PRICE_CHECK3, 0x7B69, 15, 15, -1, -1);
	

	gInterface.BindObject(eMARKET_FILTER_MAIN, 0x7A5A, 222, 212, -1, -1);

	gInterface.BindObject(eMARKET_FILTER_TITLE, 0x7A63, 230, 67, -1, -1);

	gInterface.BindObject(eMARKET_FILTER_FRAME, 0x7A58, 230, 15, -1, -1);

	gInterface.BindObject(eMARKET_FILTER_FOOTER, 0x7A59, 230, 50, -1, -1);

	gInterface.BindObject(eMARKET_FILTER_POINT, 0x7B68, 10, 10, -1, -1);

	gInterface.BindObject(eMARKET_FILTER_PAGEUP, 0x7AA4, 15, 15, -1, -1);

	gInterface.BindObject(eMARKET_FILTER_PAGEDN, 0x7C0D, 15, 15, -1, -1);

	gInterface.BindObject(eMARKET_FILTER_LINE, 0x7B67, 154, 3, -1, -1);

	gInterface.BindObject(eMARKET_FILTER_CHECK1, 0x7B69, 15, 15, -1, -1);

	gInterface.BindObject(eMARKET_FILTER_CHECK2, 0x7B69, 15, 15, -1, -1);

	gInterface.BindObject(eMARKET_FILTER_CHECK3, 0x7B69, 15, 15, -1, -1);

	gInterface.BindObject(eMARKET_FILTER_CHECK4, 0x7B69, 15, 15, -1, -1);

	gInterface.BindObject(eMARKET_FILTER_CHECK5, 0x7B69, 15, 15, -1, -1);

	gInterface.BindObject(eMARKET_FILTER_CHECK6, 0x7B69, 15, 15, -1, -1);

	gInterface.BindObject(eMARKET_FILTER_NAME, 0x7AA3, 170, 21, -1, -1);

	gInterface.BindObject(eMARKET_FILTER_CAATEGORY, 0x7AA3, 170, 21, -1, -1);

	gInterface.BindObject(eMARKET_FILTER_DIV, 0x7A62, 223, 21, -1, -1);


	gInterface.BindObject(eMARKET_ITEM_MAIN, 0x7A5A, 222, 210, -1, -1);

	gInterface.BindObject(eMARKET_ITEM_TITLE, 0x7A63, 230, 67, -1, -1);

	gInterface.BindObject(eMARKET_ITEM_FRAME, 0x7A58, 230, 15, -1, -1);

	gInterface.BindObject(eMARKET_ITEM_FOOTER, 0x7A59, 230, 50, -1, -1);

	gInterface.BindObject(eMARKET_ITEM_BG, zt_SMITHY_ITEM, 152, 124, -1, -1);

	gInterface.BindObject(eMARKET_ITEM_OK, 0x7A5F, 62, 27, -1, -1);

	gInterface.BindObject(eMARKET_ITEM_CLOSE, 0x7A5F, 62, 27, -1, -1);


	#if(MARKET_PAGE_DEV)

	this->BindPage();

	#endif
}

void CItemMarket::DrawMain()
{
	this->DrawShop();

	this->DrawPrice();
}

void CItemMarket::DrawShop()
{
	if(!gInterface.CheckWindowZt(ObjWindowsZt::ztWinItemMarket))
	{
		return;
	}

	#if(MARKET_DEBUG)



	#else

	if(this->m_ItemBuyID != -1)
	{
		this->CGReqItemBuy();

		this->m_ItemBuyID = -1;

		return;
	}

	#endif

	pSetCursorFocus = true;

	float MainWidth = 230.0;

	float StartY = 0;

	float StartX = 0;

	float ContentX = StartX;

	float ContentY = StartY + 20;

	gInterface.DrawWindow(eMARKET_MAIN, eMARKET_TITLE, eMARKET_FRAME, eMARKET_FOOTER, 21, StartX, StartY, "Item Market");

	#if(MARKET_INTERFACE_DEV)

	int iDrawItemCount = 0;

	int iDrawItemInfo = -1;

	for(int i = this->m_ScrollPos; i < MARKET_ITEM_MAX; i++)
	{
		if(!this->m_Info[i].ID)
		{
			continue;
		}

		gInterface.DrawGUI(eMARKET_DIV, ContentX, ContentY);

		ContentY += gInterface.Data[eMARKET_DIV].Height / 2 + 1;

		gInterface.DrawGUI(eMARKET_INFOBG3, ContentX + 30, ContentY);

		gInterface.DrawFormat(eGold, ContentX, ContentY + 10, 35, 3, "%d", i+1);

		ObjectItem objItem = this->GetItemObject(this->m_Info[i].ItemType, this->m_Info[i].ItemDurability, this->m_Info[i].ItemData);
		
		DWORD dwColor = this->GetItemNameColor(objItem.Level, objItem.Unknown18, objItem.ExcellentOption, objItem.AncientOption, objItem.SocketSet);
		
		int iLevel = ( objItem.Level >> 3 ) & 0x0F;

		if(iLevel > 0)
		{
			gInterface.DrawFormat(dwColor, ContentX + 30 + 5, ContentY + 5, 170, 3, "%s + %d", 
				gItem.GetItemName(this->m_Info[i].ItemType),
				iLevel);
		}
		else
		{
			gInterface.DrawFormat(dwColor, ContentX + 30 + 5, ContentY + 5, 170, 3, "%s", gItem.GetItemName(this->m_Info[i].ItemType));
		}

		ContentY += gInterface.Data[eMARKET_INFOBG3].Height - 3;

		gInterface.DrawGUI(eMARKET_INFOBG2, ContentX + 30, ContentY);

		char szItemPrice[64] = { 0 };
		
		gInterface.DrawFormat(eWhite, StartX + 30 + 5, ContentY + 5, 100, 1, "Price:");

		pGetMoneyFormat((double)(int)this->m_Info[i].Price, szItemPrice, 0);

		gInterface.DrawFormat(eYellow, StartX + 30 + 70, ContentY + 5, 100, 3, "%s", szItemPrice);

		ContentY += gInterface.Data[eMARKET_DIV].Height / 2 - 2;

		if(gInterface.IsWorkZone(ContentX + 30, ContentY, ContentX + 30 + 170, ContentY + 21))
		{
			iDrawItemInfo = i;
		}

		iDrawItemCount++;

		if(iDrawItemCount >= 10)
		{
			gInterface.DrawGUI(eMARKET_DIV, ContentX, ContentY);

			break;
		}
	}

	#else

	#if(MARKET_TITLE_DEV)

	gInterface.DrawFormat(eOrange, ContentX, ContentY + 21, 35, 3, "#");

	gInterface.DrawFormat(eOrange,  ContentX + 30 + 10, ContentY + 20, 170, 1, "Item Name");

	gInterface.DrawFormat(eOrange, ContentX + 30 - 10, ContentY + 20, 170, 4, "Item Value");

	gInterface.DrawFormat(eOrange, ContentX + 30 + 14, ContentY + 20, 170, 4, "Price");

	#endif

	ContentY += 30;

	gInterface.DrawGUI(eMARKET_DIV, ContentX, ContentY);

	#if(MARKET_SCROLL_DEV)

	ContentX -= 7;

	#endif

	#if(MARKET_VIEWE_DEV)

	ContentY += 20;	

	#else

	ContentY += 35;	

	#endif

	int iDrawItemCount = 0;

	int iDrawItemInfo = -1;

	for(int i = this->m_ScrollPos; i < MARKET_ITEM_MAX; i++)
	{
		if(!this->m_Info[i].ID)
		{
			continue;
		}

		ObjectItem objItem = this->GetItemObject(this->m_Info[i].ItemType, this->m_Info[i].ItemDurability, this->m_Info[i].ItemData);

		DWORD dwColor = this->GetItemNameColor(objItem.Level, objItem.Unknown18, objItem.ExcellentOption, objItem.AncientOption, objItem.SocketSet);
		
		int iLevel = ( objItem.Level >> 3 ) & 0x0F;

		gInterface.DrawGUI(eMARKET_INFOBG3, ContentX + 30, ContentY);

		#if(MARKET_BUY_DEV)

		if(this->m_SelectNumber == i)
		{
			//gInterface.DrawColoredGUI(eMARKET_INFOBG3,  ContentX + 30, ContentY, eGray150);

			gInterface.DrawColorGUI(
				gInterface.Data[eMARKET_INFOBG3].ModelID, 
				ContentX + 30, ContentY, 
				gInterface.Data[eMARKET_INFOBG3].Width, gInterface.Data[eMARKET_INFOBG3].Height, 
				eGray150);
		}

		#endif

		gInterface.DrawFormat(eGold, ContentX + 3, ContentY + 6, 35, 3, "%d", i+1);

		if(iLevel > 0)
		{
			gInterface.DrawFormat(dwColor, ContentX + 30 + 10, ContentY + 5, 170, 1, "%s + %d", 
				gItem.GetItemName(this->m_Info[i].ItemType),
				iLevel);
		}
		else
		{
			gInterface.DrawFormat(dwColor,  ContentX + 30 + 10, ContentY + 5, 170, 1, "%s",
				gItem.GetItemName(this->m_Info[i].ItemType));
		}

		char szItemPrice[64] = { 0 };

		pGetMoneyFormat((double)(int)this->m_Info[i].Price, szItemPrice, 0);

		dwColor = eYellow;
		
#if(MARKET_PLAYER_BUY)

		lpCharObj lpPlayer = pUserObjectStruct;

		if(!strcmp(lpPlayer->Name, this->m_Info[i].Name))
		{
			dwColor = eYellow;
		}
		else if(!this->GetCheckMoney(this->m_Info[i].PriceType, this->m_Info[i].Price))
		{
			dwColor = eRed;
		}

#else

		if(!this->GetCheckMoney(this->m_Info[i].PriceType, this->m_Info[i].Price))
		{
			dwColor = eRed;
		}
#endif
		gInterface.DrawFormat(dwColor, ContentX + 30 - 10, ContentY + 5, 170, 4, "%s", szItemPrice);
		
		// --

		if(this->m_Info[i].PriceType == eMarketPriceTypeZen)
		{
			gInterface.DrawFormat(dwColor, ContentX + 30 + 14, ContentY + 5, 170, 4, "ZN");
		}
		else if(this->m_Info[i].PriceType == eMarketPriceTypeWcoin)
		{
			gInterface.DrawFormat(dwColor, ContentX + 30 + 14, ContentY + 5, 170, 4, "WC");
		}
		else if(this->m_Info[i].PriceType == eMarketPriceTypeCredit)
		{
			gInterface.DrawFormat(dwColor, ContentX + 30 + 14, ContentY + 5, 170, 4, "CR");
		}		

		// --

		//if(gInterface.IsWorkZone(ContentX + 30, ContentY, ContentX + 30 + 170, ContentY + 21))
		if(gInterface.IsWorkZone(eMARKET_INFOBG3))
		{
			iDrawItemInfo = i;
		}

		ContentY += 25;

		iDrawItemCount++;

		if(iDrawItemCount >= 10)
		{
			break;
		}
	}

	#endif

	#if(MARKET_VIEWE_DEV)

	this->m_VieweNumber = iDrawItemInfo;

	#endif

	#if(MARKET_BUY_DEV)

	ContentX = gInterface.Data[eMARKET_FOOTER].X;

	ContentY = gInterface.Data[eMARKET_FOOTER].Y - 68;	//g_UltraDebuger.GetNumber(eULTRA_1, 40, 1);
	
	//ContentY -= 5;	//g_UltraDebuger.GetNumber(eULTRA_1, 5, 1);

	gInterface.DrawGUI(eMARKET_DIV, ContentX, ContentY);

	ContentY += 15;

	/*

	gInterface.DrawButtonMini(eMARKET_OK, ContentX + 30, ContentY + 5, true, "Refresh");

	ContentX += 105;

	gInterface.DrawButtonMini(eMARKET_CLOSE, ContentX + 30, ContentY + 5, true, "Close");

	*/

	bool bBuyResult = false;

	if(this->m_SelectNumber != -1)
	{
#if(MARKET_PLAYER_BUY)

		lpCharObj lpPlayer = pUserObjectStruct;

		if(!strcmp(lpPlayer->Name, this->m_Info[this->m_SelectNumber].Name))
		{
			bBuyResult = true;
		}
		else if(this->GetCheckMoney(this->m_Info[this->m_SelectNumber].PriceType, this->m_Info[this->m_SelectNumber].Price))
		{
			bBuyResult = true;
		}

#else
		if(this->GetCheckMoney(this->m_Info[this->m_SelectNumber].PriceType, this->m_Info[this->m_SelectNumber].Price))
		{
			bBuyResult = true;
		}
#endif
	}

	gInterface.DrawButtonBig(eMARKET_BUY, bBuyResult, ContentX + 60, ContentY + 5, "Item Buy");

	#endif

	ContentX = gInterface.Data[eMARKET_FOOTER].X;

	ContentY = gInterface.Data[eMARKET_FOOTER].Y - 20;
	
	gInterface.DrawGUI(eMARKET_DIV, ContentX, ContentY);

	ContentY += 15;

	gInterface.DrawButtonMini(eMARKET_OK, ContentX + 30, ContentY + 5, true, "Refresh");

	ContentX += 105;

	gInterface.DrawButtonMini(eMARKET_CLOSE, ContentX + 30, ContentY + 5, true, "Close");

	#if(MARKET_PAGE_DEV)

	this->DrawPage(ContentX - 12, ContentY + 10);

	#endif

	#if(MARKET_SCROLL_DEV)

	int iMaxScrollCount = 0;

	for(int i = 0; i < MARKET_ITEM_MAX; i++)
	{
		if(this->m_Info[i].ID)
		{
			iMaxScrollCount++;
		}
	}

	//int iUltra1 = g_UltraDebuger.GetNumber(eULTRA_1, 35, 1);

	float flScrollDiv = 0;
	
	if(iMaxScrollCount > 0)
	{
		flScrollDiv = ( 10 * 40 ) / iMaxScrollCount;	//
	}

	gInterface.DrawGUI(eMARKET_SCROLL, ContentX + 104, this->m_ScrollPos * flScrollDiv + 90);

	//gInterface.DrawGUI(eMARKET_SCROLL, ContentX + 105, 90 + this->m_ScrollPos * 3.0);

	#endif

	this->DrawFilter(230, 0);

	#if(MARKET_VIEWE_DEV)

	if(this->m_VieweNumber != -1)
	{
		this->DrawTest(0, 0, this->m_VieweNumber);
	}
	else if(this->m_SelectNumber != -1)
	{
		this->DrawTest(0, 0, this->m_SelectNumber);
	}

	return;

	#endif

	#if(MARKET_DEBUG)

	if(this->m_ItemBuyID != -1)
	{
		this->DrawTest(0, 0, iDrawItemInfo);
	}
	else
	{
		this->DrawTest(0, 0, iDrawItemInfo);
	}
	
	#else

	this->DrawTest(0, 0, iDrawItemInfo);

	#endif
}

void CItemMarket::DrawPrice()
{
	if(!gInterface.CheckWindowZt(ObjWindowsZt::ztWinItemMarketPrice))
	{
		return;
	}

	pSetCursorFocus = true;

	float MainWidth = 230.0;

	float StartY = 100.0;

	float StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);

	float ContentX = StartX;

	float ContentY = 120;

	gInterface.DrawWindow(eMARKET_PRICE_MAIN, eMARKET_PRICE_TITLE, eMARKET_PRICE_FRAME, eMARKET_PRICE_FOOTER, 4, StartX, StartY, "Item Price");

	ContentY += 20;

	gInterface.DrawCheckLineZt(this->m_SelectItemPriceType1, eMARKET_PRICE_POINT, eMARKET_PRICE_CHECK1, eMARKET_PRICE_LINE, ContentX, ContentY, eWhite, "Price type: 1");

	ContentY += 20;

	gInterface.DrawCheckLineZt(this->m_SelectItemPriceType2, eMARKET_PRICE_POINT, eMARKET_PRICE_CHECK2, eMARKET_PRICE_LINE, ContentX, ContentY, eWhite, "Price type: 2");

	ContentY += 20;

	gInterface.DrawCheckLineZt(this->m_SelectItemPriceType3, eMARKET_PRICE_POINT, eMARKET_PRICE_CHECK3, eMARKET_PRICE_LINE, ContentX, ContentY, eWhite, "Price type: 3");

	ContentY += 20;

	gInterface.DrawGUI(eMARKET_PRICE_INFOBG, ContentX + 30, ContentY);

	gInterface.DrawFormat(eYellow, ContentX + 15 + 30, ContentY + 5, 50, 3, "Item price:");

	gInterface.DrawFormat(eExcellent, ContentX + 95 + 30, ContentY + 5, 50, 3, "%u", atol(this->m_SelectItemPrice));
	
	ContentY += 20;

	gInterface.DrawButtonMini(eMARKET_PRICE_OK, ContentX + 30, ContentY + 5, true, "Sell");

	ContentX += 105;

	gInterface.DrawButtonMini(eMARKET_PRICE_CLOSE, ContentX + 30, ContentY + 5, true, "Cancel");
}

void CItemMarket::DrawFilter(float PosX, float PosY)
{
	pSetCursorFocus = true;

	float StartY = 210;

	float StartX = 226;

	float ContentX = StartX;

	float ContentY = StartY + 20;

	gInterface.DrawWindow(eMARKET_FILTER_MAIN, eMARKET_FILTER_TITLE, eMARKET_FILTER_FRAME, eMARKET_FILTER_FOOTER, 7, StartX, StartY, "Item Filter");

	ContentY += 15;

	gInterface.DrawCheckLineZt(this->m_FilterPriceType1, eMARKET_FILTER_POINT, eMARKET_FILTER_CHECK1, eMARKET_FILTER_LINE, ContentX, ContentY, eWhite, "Price type: 1");
			
	ContentY += 20;

	gInterface.DrawCheckLineZt(this->m_FilterPriceType2, eMARKET_FILTER_POINT, eMARKET_FILTER_CHECK2, eMARKET_FILTER_LINE, ContentX, ContentY, eWhite, "Price type: 2");
			
	ContentY += 20;

	gInterface.DrawCheckLineZt(this->m_FilterPriceType3, eMARKET_FILTER_POINT, eMARKET_FILTER_CHECK3, eMARKET_FILTER_LINE, ContentX, ContentY, eWhite, "Price type: 3");
			
	// ----

	ContentY += 15;

	gInterface.DrawGUI(eMARKET_DIV, ContentX, ContentY);

	ContentY += 15;

	gInterface.PartUPandDNEx(eMARKET_FILTER_POINT, eMARKET_FILTER_PAGEUP, eMARKET_FILTER_PAGEDN, eMARKET_FILTER_LINE, ContentX, ContentY, eWhite, this->m_FilterLevel, "Item Level");

	ContentY += 20;

	gInterface.DrawCheckLineZt(this->m_FilterLuck, eMARKET_FILTER_POINT, eMARKET_FILTER_CHECK4, eMARKET_FILTER_LINE, ContentX, ContentY, eWhite, "Luck Option +25%%");
			
	ContentY += 20;

	gInterface.DrawCheckLineZt(this->m_FilterExl, eMARKET_FILTER_POINT, eMARKET_FILTER_CHECK5, eMARKET_FILTER_LINE, ContentX, ContentY, eWhite, "Exellent Option");
			
	ContentY += 20;

	gInterface.DrawCheckLineZt(this->m_FilterAnc, eMARKET_FILTER_POINT, eMARKET_FILTER_CHECK6, eMARKET_FILTER_LINE, ContentX, ContentY, eWhite, "Ancent Option");
			
	ContentY += 20;

	//gInterface.DrawGUI(eMARKET_FILTER_NAME, ContentX + 30, ContentY);

	//gInterface.DrawFormat(eYellow, ContentX + 15 + 30, ContentY + 5, 50, 3, "Seller:");

	//gInterface.DrawFormat(eExcellent, ContentX + 95 + 30, ContentY + 5, 50, 3, "%s", this->m_FilterName);

	#if(MARKET_CATEGORY_DEV)

	gInterface.DrawGUI(eMARKET_FILTER_CAATEGORY, ContentX + 30, ContentY);

	gInterface.DrawFormat(eYellow, ContentX + 15 + 30, ContentY + 5, 50, 3, "Category:");

	gInterface.DrawFormat(eExcellent, ContentX + 75 + 30, ContentY + 5, 100, 3, "%s", MarketCategory[this->m_FilterType]);

	#endif
}

void CItemMarket::DrawTest(float PosX, float PosY, int ItemID)
{
	if(ItemID != -1)
	{
		this->m_ItemEx = this->GetItemObject(this->m_Info[ItemID].ItemType, this->m_Info[ItemID].ItemDurability, this->m_Info[ItemID].ItemData);
	}

	pSetCursorFocus = true;

	float StartY = 0;

	float StartX = 226;

	float ContentX = StartX;

	float ContentY = StartY + 20;

	gInterface.DrawWindow(eMARKET_ITEM_MAIN, eMARKET_ITEM_TITLE, eMARKET_ITEM_FRAME, eMARKET_ITEM_FOOTER, 7, StartX, StartY, "Item Info");

	//gInterface.DrawWindow(eMARKET_ITEM_MAIN, eMARKET_ITEM_TITLE, eMARKET_ITEM_FRAME, eMARKET_ITEM_FOOTER, 7, StartX, StartY, this->m_Info[ItemID].Name);

	ContentX = 265;

	ContentY = 27;

	gInterface.DrawGUI(eMARKET_ITEM_BG, ContentX, ContentY);

	if(ItemID != -1)
	{
		gInterface.DrawFormat(eYellow, ContentX, ContentY + 10, 152, 3, this->m_Info[ItemID].Name);
	}

	int Width = 152;

	int Height = 124;

	const int WidthValue = 24;

	const int HeightValue = 26;

	ItemBmdStruct * ItemInfo = pGetItemBmdStruct(this->m_Info[ItemID].ItemType);

	float barWidth = WidthValue * ItemInfo->ItemWidth;

	float barHeight = HeightValue * ItemInfo->ItemHeight;

	float flItemX = ContentX + ( Width / 2 ) - ( WidthValue * ItemInfo->ItemWidth / 2 );

	float flItemY = ContentY + ( Height / 2 ) - ( HeightValue * ItemInfo->ItemHeight / 2 );

	gInterface.DrawItem(flItemX, flItemY, barWidth, barHeight, this->m_Info[ItemID].ItemType, SET_ITEMOPT_LEVEL(this->m_ItemEx.Level), 1, 0, 0);

	/*
	ContentY += 135;

	ContentX -= 38;
	
	gInterface.DrawButtonMini(eMARKET_ITEM_CLOSE, ContentX + 30, ContentY + 5, false, "Return");

	ContentX += 105;

	#if(MARKET_DEBUG)

	bool bCheckBuy = false;

	if(this->m_ItemBuyID != -1)
	{
		bCheckBuy = true;
	}
		
	gInterface.DrawButtonMini(eMARKET_ITEM_OK, ContentX + 30, ContentY + 5, true, "Buy");

	#else
	
	gInterface.DrawButtonMini(eMARKET_ITEM_OK, ContentX + 30, ContentY + 5, true, "Buy");

	#endif

	*/

	if(ItemID != -1)
	{
		gInterface.DrawItemToolTipText((void*)&this->m_ItemEx, 343, 114 );
	}
}

void CItemMarket::Keyboard(DWORD Event)
{
#if(!ENABLE_MARKET_BUTTON)
	if(!gInterface.CheckWindowZt(ObjWindowsZt::ztWinItemMarket))
	{
		if(Event == VK_NUMPAD9)
		{
			this->m_ItemBuyID = -1;

			this->CGReqItemList();
		}
	}
#endif

	if(gInterface.CheckWindowZt(ObjWindowsZt::ztWinItemMarketPrice))
	{
		gInterface.KeyBoxEvent(Event, this->m_SelectItemPrice, 8);
	}
}

void CItemMarket::Mouse(MOUSEHOOKSTRUCTEX * Mouse, WPARAM wParam)
{
	if(gInterface.CheckWindowZt(ObjWindowsZt::ztWinItemMarket))
	{
		if(wParam == WM_MOUSEWHEEL)
		{
			if((int)Mouse->mouseData > 0)
			{
				if(this->m_ScrollPos > 0)
				{
					this->m_ScrollPos--;
				}
			}

			#if(MARKET_SCROLL_DEV)

			if((int)Mouse->mouseData < 0)
			{
				if(this->m_ScrollPos < MARKET_ITEM_MAX - 10)
				{
					if(this->m_Info[this->m_ScrollPos + 10].ID)
					{
						this->m_ScrollPos++;
					}	
				}
			}

			#else

			if((int)Mouse->mouseData < 0)
			{
				if(this->m_ScrollPos < MARKET_ITEM_MAX)
				{
					this->m_ScrollPos++;
				}
			}

			#endif

			return;
		}


		if(gInterface.ButtonZt(wParam, eMARKET_BUY, true))
		{
			//gInterface.CloseWindowZt(ObjWindowsZt::ztWinItemMarket);

			this->m_ItemBuyID = this->m_Info[this->m_SelectNumber].ID;

			this->CGReqItemBuy();

			this->m_ItemBuyID = -1;
		}

		#if(MARKET_VIEWE_DEV)

		if(wParam == WM_LBUTTONUP && this->m_VieweNumber != -1)
		{
			//this->m_ItemBuyID = this->m_Info[this->m_VieweNumber].ID;

			this->m_SelectNumber = this->m_VieweNumber;
		}

		if(wParam == WM_LBUTTONUP && this->m_VieweNumber == -1)
		{
			//this->m_ItemBuyID = -1;

			this->m_SelectNumber = -1;
		}

		#else

		if(wParam == WM_LBUTTONUP && this->m_ItemBuyID == -1)
		{
			int iDrawItemCount = 0;

			float ContentX = 0;

			float ContentY = 35 + 25 + 20;

			for(int i = this->m_ScrollPos; i < MARKET_ITEM_MAX; i++)
			{
				if(!this->m_Info[i].ID)
				{
					continue;
				}

				if(gInterface.IsWorkZone(ContentX + 30, ContentY, ContentX + 30 + 170, ContentY + 21))
				{
					if(!this->GetCheckMoney(this->m_Info[i].PriceType, this->m_Info[i].Price))
					{
						break;
					}

					this->m_ItemBuyID = this->m_Info[i].ID;

					break;
				}

				ContentY += 25;	

				iDrawItemCount++;

				if(iDrawItemCount >= 10)
				{
					break;
				}
			}
		}

		#endif
		
		// ----

		if(gInterface.ButtonZt(wParam, eMARKET_CLOSE, false))
		{
			gInterface.CloseWindowZt(ObjWindowsZt::ztWinItemMarket);
		}

		if(gInterface.ButtonZt(wParam, eMARKET_OK, false))
		{
			//gInterface.CloseWindowZt(ObjWindowsZt::ztWinItemMarket);

			this->CGReqItemList();
		}

		// ----

		if(gInterface.ButtonZt(wParam, eMARKET_FILTER_CHECK1, false))
		{
			//this->m_FilterPriceType1 = 1;
			this->m_FilterPriceType1 = !this->m_FilterPriceType1;
			this->m_FilterPriceType2 = 0;
			this->m_FilterPriceType3 = 0;
		}

		if(gInterface.ButtonZt(wParam, eMARKET_FILTER_CHECK2, false))
		{
			this->m_FilterPriceType1 = 0;
			//this->m_FilterPriceType2 = 1;
			this->m_FilterPriceType2 = !this->m_FilterPriceType2;
			this->m_FilterPriceType3 = 0;
		}

		if(gInterface.ButtonZt(wParam, eMARKET_FILTER_CHECK3, false))
		{
			this->m_FilterPriceType1 = 0;
			this->m_FilterPriceType2 = 0;
			//this->m_FilterPriceType3 = 1;
			this->m_FilterPriceType3 = !this->m_FilterPriceType3;
		}

		// ----

		if(gInterface.ButtonZt(wParam, eMARKET_FILTER_PAGEUP, false) && this->m_FilterLevel < 15)
		{
			this->m_FilterLevel++;
		}

		if(gInterface.ButtonZt(wParam, eMARKET_FILTER_PAGEDN, false) && this->m_FilterLevel > 0)
		{
			this->m_FilterLevel--;
		}

		if(gInterface.ButtonZt(wParam, eMARKET_FILTER_CHECK4, false))
		{
			this->m_FilterLuck = !this->m_FilterLuck;
		}

		if(gInterface.ButtonZt(wParam, eMARKET_FILTER_CHECK5, false))
		{
			this->m_FilterExl = !this->m_FilterExl;
		}

		if(gInterface.ButtonZt(wParam, eMARKET_FILTER_CHECK6, false))
		{
			this->m_FilterAnc = !this->m_FilterAnc;
		}

		// ----

		if(gInterface.ButtonZt(wParam, eMARKET_FILTER_CAATEGORY, false))
		{
			this->m_FilterType++;

			if(this->m_FilterType > 16)
			{
				this->m_FilterType = 0;
			}
		}

		if(gInterface.ButtonZtR(wParam, eMARKET_FILTER_CAATEGORY, false))
		{
			this->m_FilterType--;

			if(this->m_FilterType < 0)
			{
				this->m_FilterType = 16;
			}
		}

		// ----

		#if(MARKET_DEBUG)

		if(gInterface.ButtonZt(wParam, eMARKET_ITEM_OK, TRUE))
		{
			if(this->m_ItemBuyID != -1)
			{
				this->CGReqItemBuy();
			}
		}

		#endif

		#if(MARKET_PAGE_DEV)

		this->ButtonPage(wParam);

		#endif
	}

	// ----

	if(gInterface.CheckWindowZt(ObjWindowsZt::ztWinItemMarketPrice))
	{
		if(gInterface.ButtonZt(wParam, eMARKET_PRICE_OK, false))
		{
			gInterface.CloseWindowZt(ObjWindowsZt::ztWinItemMarketPrice);

			this->CGReqItemSell(this->m_SelectItemPos);
		}
		else if(gInterface.ButtonZt(wParam, eMARKET_PRICE_CLOSE, false))
		{
			gInterface.CloseWindowZt(ObjWindowsZt::ztWinItemMarketPrice);
		}

		// ----

		if(gInterface.ButtonZt(wParam, eMARKET_PRICE_CHECK1, false))
		{
			this->m_SelectItemPriceType1 = 1;
			this->m_SelectItemPriceType2 = 0;
			this->m_SelectItemPriceType3 = 0;
		}

		if(gInterface.ButtonZt(wParam, eMARKET_PRICE_CHECK2, false))
		{
			this->m_SelectItemPriceType1 = 0;
			this->m_SelectItemPriceType2 = 1;
			this->m_SelectItemPriceType3 = 0;
		}

		if(gInterface.ButtonZt(wParam, eMARKET_PRICE_CHECK3, false))
		{
			this->m_SelectItemPriceType1 = 0;
			this->m_SelectItemPriceType2 = 0;
			this->m_SelectItemPriceType3 = 1;
		}

		if(this->m_SelectItemPriceType1)
		{
			this->m_SellPriceType = eMarketPriceTypeZen;
		}

		if(this->m_SelectItemPriceType2)
		{
			this->m_SellPriceType = eMarketPriceTypeWcoin;
		}

		if(this->m_SelectItemPriceType3)
		{
			this->m_SellPriceType = eMarketPriceTypeCredit;
		}
	}
}

void CItemMarket::CGReqItemList()
{
	PMSG_REQ_MARKET_ITEM pMsg;

	pMsg.h.set((LPBYTE)&pMsg, 0x80, 0x00, sizeof(pMsg));

	pMsg.Result = 1;

	pMsg.PriceType = -1;

	if(this->m_FilterPriceType1)
	{
		pMsg.PriceType = eMarketPriceTypeZen;
	}

	if(this->m_FilterPriceType2)
	{
		pMsg.PriceType = eMarketPriceTypeWcoin;
	}

	if(this->m_FilterPriceType3)
	{
		pMsg.PriceType = eMarketPriceTypeCredit;
	}

	#if(MARKET_FILTER_DEV)

	pMsg.Filter.FilterType = this->m_FilterType;

	pMsg.Filter.FilterLevel = this->m_FilterLevel;

	pMsg.Filter.FilterLuck = this->m_FilterLuck;

	pMsg.Filter.FilterExl = this->m_FilterExl;

	pMsg.Filter.FilterAnc = this->m_FilterAnc;

	#endif

	#if(MARKET_PAGE_DEV)

	pMsg.PageNumber = this->m_PageNumber;

	#endif

	gProtocol.DataSend((LPBYTE)&pMsg, pMsg.h.size);

	gConsole.Output(cGREY, "[CLIENT -> SERVER] : CGReqItemList");
}

void CItemMarket::GCAnsItemList(PMSG_ANS_MARKET_ITEM* lpMsg)
{
	if(lpMsg->Result == 0)
	{
		return;
	}

	memset(this->m_Info, 0, sizeof(this->m_Info));

	for(int i = 0; i < MARKET_ITEM_MAX; i++)
	{
		this->m_Info[i].ID = lpMsg->Info[i].ID;

		memcpy(this->m_Info[i].Name, lpMsg->Info[i].Name, MARKET_NAME_LEN-1);

		memcpy(this->m_Info[i].ItemData, lpMsg->Info[i].ItemData, MARKET_ITEM_BUFFER);

		this->m_Info[i].ItemType = lpMsg->Info[i].ItemType;

		this->m_Info[i].ItemDurability = lpMsg->Info[i].ItemDurability;

		this->m_Info[i].PriceType = lpMsg->Info[i].PriceType;

		this->m_Info[i].Price = lpMsg->Info[i].Price;
	}

	gInterface.OpenWindowZt(ObjWindowsZt::ztWinItemMarket);
}

void CItemMarket::CGReqItemSell(int ItemPos)
{
	PMSG_REQ_MARKET_SELL pMsg;

	pMsg.h.set((LPBYTE)&pMsg, 0x80, 0x01, sizeof(pMsg));

	pMsg.Result = 1;

	pMsg.ItemPos = ItemPos;

	pMsg.ItemPriceType = this->m_SellPriceType;

	pMsg.ItemPrice = atol(this->m_SelectItemPrice);

	gProtocol.DataSend((LPBYTE)&pMsg, pMsg.h.size);

	gConsole.Output(cGREY, "[CLIENT -> SERVER] : CGReqItemSell");
}

void CItemMarket::CGAnsItemSell()
{
	
}

void CItemMarket::CGReqItemBuy()
{
	#if(!MARKET_DEBUG)
	gInterface.CloseWindowZt(ObjWindowsZt::ztWinItemMarket);
	#endif

	PMSG_REQ_MARKET_BUY pMsg;

	pMsg.h.set((LPBYTE)&pMsg, 0x80, 0x02, sizeof(pMsg));

	pMsg.Result = 1;

	pMsg.ID = this->m_ItemBuyID;

	gProtocol.DataSend((LPBYTE)&pMsg, pMsg.h.size);

	gConsole.Output(cGREY, "[CLIENT -> SERVER] : CGReqItemBuy");

	if(gInterface.CheckWindowZt(ObjWindowsZt::ztWinItemMarket))
	{
		gInterface.CloseWindowZt(ObjWindowsZt::ztWinItemMarket);
	}
}

void CItemMarket::GCAnsItemBuy(PMSG_ANS_MARKET_BUY* lpMsg)
{
	//memset(this->m_Info, 0, sizeof(this->m_Info));

	#if(!MARKET_DEBUG)
	gInterface.CloseWindowZt(ObjWindowsZt::ztWinItemMarket);
	#else
	this->CGReqItemList();
	#endif
}

int CItemMarket::GetItemPos(ObjectItem *Item)
{
	int Result = 0;

	if ((pCursorX > 460))
	{
		Result = Item->PosX + Item->PosY * 8 + 12;
	}
	else if (gInterface.CheckWindow(ExpandInventory) && pCursorX > 260)
	{
		Result = Item->PosX + Item->PosY * 8 + 12 + 64;

		if (pCursorY > 130)
		{
			Result += 32;
		}
	}
	else
	{
		Result = Item->PosX + Item->PosY * 8;
	}

	return Result;
}

int CItemMarket::CheckItemInfo(signed int a1)	// -> Recode
{
	if ( a1 > 3092 )
	{
		if ( a1 > 4661 )
		{
			if ( a1 > 5685 || a1 < 5676 && (a1 < 5164 || a1 > 5173) )
				return 0;
		}
		else if ( a1 < 4652 && (a1 > 4149 || a1 < 4140 && (a1 < 3628 || a1 > 3637)) )
		{
			return 0;
		}

		return 1;
	}

	if ( a1 >= 3089 )
		return 1;

	if ( a1 > 2071 )
	{
		if ( a1 != 2580 && (a1 <= 2589 || a1 > 2592) )
			return 0;
		return 1;
	}

	if ( a1 == 2071 || a1 <= 1041 && (a1 >= 1040 || a1 >= 26 && a1 <= 28) )
		return 1;

	return 0;
}

DWORD CItemMarket::GetItemNameColor(int Level, int Luck, int Excellent, int Ancent, int Socket)
{
	DWORD dwColor = eWhite;

	if(Level >= 3 && Level <= 6)
	{
		dwColor = eBlue;
	}

	if(Level >= 7 && Level <= 15)
	{
		dwColor = eYellow;
	}

	if(Luck > 0)
	{
		dwColor = eBlue;
	}

	if(Excellent > 0)
	{
		dwColor = eExcellent;
	}

	if(Ancent > 0)
	{
		dwColor = eAncient;
	}

	if(Socket > 0)
	{
		dwColor = eSocket;
	}

	return dwColor;
}

ObjectItem CItemMarket::GetItemObject(short Type, float Durability, LPBYTE Data)
{
	ObjectItem ItemResult;

	DWORD dwAddress = (DWORD)&ItemResult;

	*(WORD *)dwAddress = Type;
	int a5 = Durability;
	*(BYTE *)(dwAddress + 22) = a5;
	int a6 = Data[3];
	*(BYTE *)(dwAddress + 23) = a6;
	int a7 = Data[4];
	*(BYTE *)(dwAddress + 24) = a7;
	int a8 = Data[5];
	*(BYTE *)(dwAddress + 97) = (a8 & 2) >> 1 > 0;
	*(BYTE *)(dwAddress + 98) = (a8 & 4) >> 2 > 0;
	*(BYTE *)(dwAddress + 73) = 16 * (a8 & 8) >> 7 > 0;
	int a9 = Data[6];
	*(WORD *)(dwAddress + 69) = (a9 & 0xF0) >> 4;
	*(WORD *)(dwAddress + 71) = a9 & 0xF;

	DWORD a10 = (DWORD)&Data[7];

	if ( a10 )
	{
		*(BYTE *)(dwAddress + 79) = 5;

		for (int i = 0; i < 5; ++i )
			*(BYTE *)(i + dwAddress + 74) = *(BYTE *)(i + a10);

		for (int j = 0; j < 5; ++j )
		{
			if ( *(BYTE *)(j + a10) == 255 )
			{
				*(BYTE *)(dwAddress + 79) = j;
				break;
			}

			if ( *(BYTE *)(j + a10) == 254 )
			{
				*(BYTE *)(j + dwAddress + 80) = -1;
			}
			else
			{
				*(BYTE *)(j + dwAddress + 80) = *(BYTE *)(j + a10) % 50;
				*(BYTE *)(j + dwAddress + 85) = *(BYTE *)(j + a10) / 50 + 1;
			}
		}

		if ( this->CheckItemInfo(*(WORD *)dwAddress) )
		{
			*(BYTE *)(dwAddress + 90) = a9;
			*(WORD *)(dwAddress + 69) = 0;
			*(WORD *)(dwAddress + 71) = 0;
		}
		else
		{
			*(BYTE *)(dwAddress + 90) = -1;
		}
	}
	else
	{
		*(BYTE *)(dwAddress + 79) = 0;
	}

	*(BYTE *)(dwAddress + 96) = 0;
    *(DWORD *)(dwAddress + 103) = 1;

#if(DEV_PACKET_ITEM)
	*((BYTE *)dwAddress + 91) = Data[12];	// -> InDev
#endif

	pSetItemOption(&ItemResult, Data[1], Data[3], Data[4]);

	return ItemResult;
}

bool CItemMarket::GetCheckMoney(int PriceType, int PriceValue)
{
	bool Result = true;

	if(PriceType == eMarketPriceTypeZen)
	{
		lpCharObj lpPlayer = pUserObjectStruct;

		if(PriceValue > lpPlayer->MoneyInventory)
		{
			Result = false;
		}
	}

	if(PriceType == eMarketPriceTypeWcoin)
	{
		if(PriceValue > gObjUser.WCoinC)
		{
			Result = false;
		}
	}

	if(PriceType == eMarketPriceTypeCredit)
	{
		if(PriceValue > (int)gObjUser.ZtCred)
		{
			Result = false;
		}
	}

	return Result;
}

#if(MARKET_PAGE_DEV)

void CItemMarket::InitPage()
{
	this->m_PageNumber = 0;
}

void CItemMarket::BindPage()
{
	gInterface.BindObject(eMARKET_L, 0x7BAA, 17, 17, -1, -1);

	gInterface.BindObject(eMARKET_R, 0x7BAB, 17, 17, -1, -1);
}

void CItemMarket::DrawPage(float X, float Y)
{
	DWORD Color = eGray100;

	float ContentX = X;

	float ContentY = Y;

	gInterface.DrawGUI(eMARKET_L, ContentX , ContentY);

	gInterface.DrawGUI(eMARKET_R, ContentX + 25, ContentY);

	if(gInterface.IsWorkZone(eMARKET_L))
	{
		Color = eGray100;

		if( gInterface.Data[eMARKET_L].OnClick )
		{
			Color = eGray150;
		}

		gInterface.DrawColoredGUI(eMARKET_L, gInterface.Data[eMARKET_L].X, gInterface.Data[eMARKET_L].Y, Color);
	}

	if(gInterface.IsWorkZone(eMARKET_R))
	{
		Color = eGray100;

		if( gInterface.Data[eMARKET_R].OnClick )
		{
			Color = eGray150;
		}

		gInterface.DrawColoredGUI(eMARKET_R, gInterface.Data[eMARKET_R].X, gInterface.Data[eMARKET_R].Y, Color);
	}

	gInterface.DrawFormat(eGold, ContentX, ContentY + 4, 45, 3, "%d", this->m_PageNumber + 1);
}

void CItemMarket::ButtonPage(DWORD Event)
{
	if(gInterface.ButtonZt(Event, eMARKET_L, false))
	{
		if(this->m_PageNumber > 0)
		{
			this->m_PageNumber--;
		}

		this->CGReqItemList();
	}

	if(gInterface.ButtonZt(Event, eMARKET_R, false))
	{
		if(this->m_PageNumber < 9)
		{
			this->m_PageNumber++;
		}

		this->CGReqItemList();
	}
}


#endif

#endif