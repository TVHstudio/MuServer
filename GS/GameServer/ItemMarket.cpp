#include "StdAfx.h"
#include "..\\include\\prodef.h"
#include "DBSockMng.h"
#include "giocp.h"
#include "..\\common\\zzzitem.h"
#include "user.h"
#include "ItemMarket.h"
#include "logproc.h"
#include "protocol.h"
#include "ZtUser.h"

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

}

void CItemMarket::Load()
{

}

void CItemMarket::Protocol(BYTE protoNum, BYTE *aRecv)
{

}

void CItemMarket::CGReqItemList(PMSG_REQ_MARKET_ITEM* lpMsg, int aIndex)
{
	SDHP_REQ_MARKET_ITEM pMsg;

	pMsg.h.set((LPBYTE)&pMsg, 0xEC, 0x00, sizeof(pMsg));

	pMsg.Result = 1;

	pMsg.aIndex = aIndex;

	pMsg.PriceType = lpMsg->PriceType;

	#if(MARKET_FILTER_DEV)

	pMsg.Filter.FilterType = lpMsg->Filter.FilterType;

	pMsg.Filter.FilterLevel = lpMsg->Filter.FilterLevel;

	pMsg.Filter.FilterLuck = lpMsg->Filter.FilterLuck;

	pMsg.Filter.FilterExl = lpMsg->Filter.FilterExl;

	pMsg.Filter.FilterAnc = lpMsg->Filter.FilterAnc;

	#endif

	#if(MARKET_PAGE_DEV)

	pMsg.PageNumber = lpMsg->PageNumber;

	#endif

	cDBSMng.Send((char*)&pMsg, pMsg.h.size);

	//LogAddC(2, "[DATA <- SERVER] : CGReqItemList");
}

void CItemMarket::GDReqItemList(int aIndex, int NumPage)
{

}

void CItemMarket::DGAnsItemList(SDHP_ANS_MARKET_ITEM* lpMsg)
{
	int aIndex = lpMsg->aIndex;

	// ----

	memset(this->m_MarketData[aIndex], 0, sizeof(this->m_MarketData[aIndex]));

	memcpy(this->m_MarketData[aIndex], lpMsg->Data, sizeof(this->m_MarketData[aIndex]));

	// ----

	PMSG_ANS_MARKET_ITEM pMsg;

	memset(&pMsg, 0, sizeof(pMsg));

	pMsg.h.set((LPBYTE)&pMsg, 0xFA, 0xF5, sizeof(pMsg));

	pMsg.Result = 1;

	CItem item;
	
	for(int i = 0; i < MARKET_ITEM_MAX; i++)
	{
		pMsg.Info[i].ID = lpMsg->Data[i].ID;

		memcpy(pMsg.Info[i].Name, lpMsg->Data[i].Name, 10);

		// ----

		item = this->GetByteToItem(this->m_MarketData[aIndex][i].Item);

		// ----

		pMsg.Info[i].ItemType = item.m_Type;

		pMsg.Info[i].ItemDurability = item.m_Durability;

		pMsg.Info[i].PriceType = lpMsg->Data[i].PriceType;

		pMsg.Info[i].Price = lpMsg->Data[i].Price;

		ItemByteConvert(pMsg.Info[i].ItemData, item);
	}

	DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));

	//LogAddC(2, "[SERVER -> CLIENT] [SIZE:%d]: DGAnsItemList", sizeof(pMsg));

	GCServerMsgStringSend("[ItemMarket] Item List Refresh", aIndex, 0);
}

void CItemMarket::CGReqItemSell(PMSG_REQ_MARKET_SELL* lpMsg, int aIndex)
{
	this->GDReqItemSell(aIndex, lpMsg->ItemPos, lpMsg->ItemPriceType, lpMsg->ItemPrice);
}

void CItemMarket::GDReqItemSell(int aIndex, int ItemPos, int ItemPriceType, int ItemPrice)
{
	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	SDHP_REQ_MARKET_SELL pMsg;

	pMsg.h.set((LPBYTE)&pMsg, 0xEC, 0x01, sizeof(pMsg));

	pMsg.Result = 1;

	pMsg.aIndex = aIndex;

	pMsg.PriceType = ItemPriceType;

	pMsg.Price = ItemPrice;
	
	//pMsg.Account[10] = 0;

	memcpy(pMsg.Account, lpUser->AccountID, sizeof(pMsg.Account)-1);

	#if(MARKET_NAME_DEV)

	//pMsg.Name[10] = 0;

	memcpy(pMsg.Name, lpUser->Name, sizeof(pMsg.Name)-1);

	#endif

	pMsg.ItemPos = ItemPos;

	ItemByteConvert16((LPBYTE)pMsg.ItemData, &lpUser->pInventory[ItemPos], 1);

	#if(MARKET_FILTER_DEV)

	BYTE btLuck = lpUser->pInventory[ItemPos].m_Option2;
	
	BYTE btOption = lpUser->pInventory[ItemPos].m_Option3;
	
	BYTE btNewOption = lpUser->pInventory[ItemPos].m_NewOption;

	BYTE btSetOption = lpUser->pInventory[ItemPos].m_SetOption;

	// --

	pMsg.Filter.FilterLuck = 0;

	pMsg.Filter.FilterExl = 0;

	pMsg.Filter.FilterAnc = 0;

	pMsg.Filter.FilterType = lpUser->pInventory[ItemPos].m_Type / 512;
	
	pMsg.Filter.FilterLevel = lpUser->pInventory[ItemPos].m_Level;

	if(btLuck)
	{
		pMsg.Filter.FilterLuck = 1;
	}

	if(btNewOption)
	{
		pMsg.Filter.FilterExl = 1;
	}

	if(btSetOption)
	{
		pMsg.Filter.FilterAnc = 1;
	}

	#endif

	cDBSMng.Send((char*)&pMsg, pMsg.h.size);

	//LogAddC(2, "[SERVER -> CLIENT] [SIZE:%d]: GDReqItemSell", sizeof(pMsg));
}

void CItemMarket::DGAnsItemSell(SDHP_ANS_MARKET_SELL* lpMsg)
{
	int aIndex = lpMsg->aIndex;

	if(lpMsg->Result)
	{
		GCServerMsgStringSend("[ItemMarket] SELL Result : 1", aIndex, 0);

		LPOBJ lpUser = &gObj[aIndex];

		int ItemPos = lpMsg->ItemPos;

		gObjInventoryItemSet(lpUser->m_Index, ItemPos, -1);

		lpUser->pInventory[ItemPos].Clear();

		GCInventoryItemDeleteSend(lpUser->m_Index, ItemPos, 1);
	}
	else
	{
		GCServerMsgStringSend("[ItemMarket] SELL Result : 0", aIndex, 0);
	}
}

// ----

void CItemMarket::CGReqItemBuy(PMSG_REQ_MARKET_BUY* lpMsg, int aIndex)
{
	this->GDReqItemBuy(aIndex, lpMsg->ID);
}

void CItemMarket::GDReqItemBuy(int aIndex, int ID)
{
	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	SDHP_REQ_MARKET_BUY pMsg;

	pMsg.h.set((LPBYTE)&pMsg, 0xEC, 0x02, sizeof(pMsg));

	pMsg.Result = 1;

	pMsg.aIndex = aIndex;

	pMsg.ID = ID;

	pMsg.Result = 0;

	for(int i = 0; i < MARKET_ITEM_MAX; i++)
	{
		if(ID == this->m_MarketData[aIndex][i].ID)
		{
#if(MARKET_PLAYER_BUY)
			if(!strcmp(lpUser->Name, this->m_MarketData[aIndex][i].Name))
			{
				pMsg.Result = 1;
			}
			else
			{
				pMsg.Result = this->GetCheckMoney(aIndex, this->m_MarketData[aIndex][i].PriceType, this->m_MarketData[aIndex][i].Price);
			}
#else
			pMsg.Result = this->GetCheckMoney(aIndex, this->m_MarketData[aIndex][i].PriceType, this->m_MarketData[aIndex][i].Price);
#endif
			break;
		}
	}

	cDBSMng.Send((char*)&pMsg, pMsg.h.size);

	//LogAddC(2, "[SERVER -> CLIENT] [SIZE:%d]: GDReqItemBuy", sizeof(pMsg));
}

void CItemMarket::DGAnsItemBuy(SDHP_ANS_MARKET_BUY* lpMsg)
{
	int aIndex = lpMsg->aIndex;

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	if(lpMsg->Result)
	{
		GCServerMsgStringSend("[ItemMarket] BUY Result : 1", aIndex, 0);

		// ----

		CItem item;

		for(int i = 0; i < MARKET_ITEM_MAX; i++)
		{
			if(lpMsg->ID == this->m_MarketData[aIndex][i].ID)
			{
#if(MARKET_PLAYER_BUY)

				//char szbuffname[64] = { 0 };
				//sprintf(szbuffname, "%s = %s", gObj[aIndex].Name, this->m_MarketData[aIndex][i].Name); 
				//GCServerMsgStringSend(szbuffname, aIndex, 0);

				if(!strcmp(gObj[aIndex].Name, this->m_MarketData[aIndex][i].Name))
				{
					item = this->GetByteToItem(this->m_MarketData[aIndex][i].Item);

					BYTE btItemPos = gObjInventoryInsertItem(lpMsg->aIndex, item);

					GCInventoryItemOneSend(lpMsg->aIndex, btItemPos);
				}
				else if(this->PlayerMoney(aIndex, this->m_MarketData[aIndex][i].PriceType, this->m_MarketData[aIndex][i].Price))
				{
					item = this->GetByteToItem(this->m_MarketData[aIndex][i].Item);

					BYTE btItemPos = gObjInventoryInsertItem(lpMsg->aIndex, item);

					GCInventoryItemOneSend(lpMsg->aIndex, btItemPos);
				}
#else
				if(this->PlayerMoney(aIndex, this->m_MarketData[aIndex][i].PriceType, this->m_MarketData[aIndex][i].Price))
				{
					item = this->GetByteToItem(this->m_MarketData[aIndex][i].Item);

					BYTE btItemPos = gObjInventoryInsertItem(lpMsg->aIndex, item);

					GCInventoryItemOneSend(lpMsg->aIndex, btItemPos);
				}
#endif
				break;
			}
		}

		// ----

	}
	else
	{
		GCServerMsgStringSend("[ItemMarket] BUY Result : 0", aIndex, 0);
	}

	PMSG_ANS_MARKET_BUY pMsg;

	pMsg.h.set((LPBYTE)&pMsg, 0xEC, 0x01, sizeof(pMsg));

	pMsg.Result = 1;

	DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));
}

#if(MARKET_PRICE_DEV)

void CItemMarket::GDReqItemStatus(int aIndex)
{
	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	SDHP_REQ_MARKET_STATUS pMsg;

	pMsg.h.set((LPBYTE)&pMsg, 0xEC, 0x03, sizeof(pMsg));

	pMsg.Result = 1;

	pMsg.aIndex = aIndex;

	memcpy(pMsg.Account, lpUser->AccountID, sizeof(pMsg.Account)-1);

	cDBSMng.Send((char*)&pMsg, pMsg.h.size);

	//LogAddC(2, "[SERVER -> DATA] [SIZE:%d]: GDReqItemBuy", sizeof(pMsg));
}

void CItemMarket::DGAnsItemStatus(SDHP_ANS_MARKET_STATUS * lpMsg)
{
	int aIndex = lpMsg->aIndex;

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	if(!lpMsg->Result)
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpMsg->PriceType == eMarketPriceTypeZen)
	{
		lpUser->Money += lpMsg->PriceValue;

		GCMoneySend(aIndex, lpUser->Money);

		MsgOutput(aIndex, "[MARKET][SELL] %s +%d Zen", lpMsg->Account, lpMsg->PriceValue);
	}

	if(lpMsg->PriceType == eMarketPriceTypeWcoin)
	{
		lpUser->GameShop.WCoinC += lpMsg->PriceValue;

		gGameShop.GDSaveUserInfo(lpUser->m_Index);

		MsgOutput(aIndex, "[MARKET][SELL] %s +%d Wcoin", lpMsg->Account, lpMsg->PriceValue);
	}

	if(lpMsg->PriceType == eMarketPriceTypeCredit)
	{
		lpUser->ZtCred += lpMsg->PriceValue;

		ZtUserDataSend(lpUser->m_Index);

		MsgOutput(aIndex, "[MARKET][SELL] %s +%d Credit", lpMsg->Account, lpMsg->PriceValue);
	}
}

#endif

CItem CItemMarket::GetByteToItem(LPBYTE lpByte)
{
	CItem item;

	item.Clear();

	int n = 0;

	int ItemDbByte = 16;
	
	int itype = lpByte[n*ItemDbByte];

	/*
	if(lpMsg->dbInventory[n*ItemDbByte] == 0xFF
		&& (lpMsg->dbInventory[n*ItemDbByte+7] & 0x80) == 0x80
		&& (lpMsg->dbInventory[n*ItemDbByte+9] & 0xF0) == 0xF0)
	{
		continue;
	}
	*/

	itype |= (lpByte[n*ItemDbByte+9] & 0xF0) * 32;

	itype |= (lpByte[n*ItemDbByte+7] & 0x80) * 2;

	int _type = itype;

	item.m_Level = DBI_GET_LEVEL(lpByte[n*ItemDbByte+1]);

	BYTE OptionData = lpByte[n*ItemDbByte+1];

	item.m_Option1 = ( ((OptionData) >> 7) & 0x01);

	item.m_Option2 = DBI_GET_LUCK(OptionData);

	item.m_Option3 = DBI_GET_OPTION(OptionData);

	item.m_Option3 |= DBI_GET_OPTION16(lpByte[n*ItemDbByte+7]) >> 4;

	item.m_Durability = lpByte[n*ItemDbByte+2];

	item.m_JewelOfHarmonyOption = lpByte[n*ItemDbByte+10];

	item.m_ItemOptionEx = DBI_GET_380OPTION(lpByte[n*ItemDbByte+9]);

	if(item.m_ItemOptionEx)
	{
		item.m_Type = itype;

		if(g_kItemSystemFor380.Is380Item(&item)==false)
		{
			item.m_ItemOptionEx = 0;
		}
	}

	BYTE SocketOption[5];

	BYTE SocketOptionIndex = 0xFF;

	memset(&SocketOption, 0xFF, 5);

	if ( g_SocketOption.CheckItemType(_type) == 1 )
	{
		for(int i = 0; i < 5; i++)
		{
			SocketOption[i] =  lpByte[((n*ItemDbByte)+11)+i];
		}

		SocketOptionIndex = lpByte[n*ItemDbByte+10];
	}
	else
	{
		for(int i = 0; i < 5; i++)
		{
			SocketOption[i] = 0xFF;
		}

		SocketOptionIndex = 0;
	}

	#ifdef PERIOD

	item.m_PeriodItemOption = (lpByte[n*ItemDbByte+DBI_OPTION380_DATA] & 6) >> 1;

	item.Convert(itype,item.m_Option1,item.m_Option2,item.m_Option3,DBI_GET_NOPTION(lpByte[n*ItemDbByte+7]),lpByte[n*ItemDbByte+8],item.m_ItemOptionEx,SocketOption, SocketOptionIndex, item.m_PeriodItemOption, 3); //season4 changed

	#else
		
	item.Convert(itype,item.m_Option1,item.m_Option2,item.m_Option3,DBI_GET_NOPTION(lpByte[n*ItemDbByte+7]),lpByte[n*ItemDbByte+8],item.m_ItemOptionEx,SocketOption, SocketOptionIndex, 0, 3); //season4 changed

	#endif

	WORD hiWord = ((lpByte[n*ItemDbByte+4])&0xFF)&0xFF | (((lpByte[n*ItemDbByte+3])&0xFF)&0xFF) * 256;

	WORD loWord = ((lpByte[n*ItemDbByte+6])&0xFF)&0xFF | (((lpByte[n*ItemDbByte+5])&0xFF)&0xFF) * 256;

	item.m_Number = ((loWord &0xFFFF)&0xFFFF) | ((hiWord & 0xFFFF)&0xFFFF) << 16;

	return item;	
}

void CItemMarket::ConnectPlayer(int aIndex)
{
	this->GDReqItemStatus(aIndex);
}

bool CItemMarket::GetCheckMoney(int aIndex, int PriceType, int PriceValue)
{
	bool Result = true;

	LPOBJ lpUser = &gObj[aIndex];

	if(PriceType == eMarketPriceTypeZen)
	{
		if(PriceValue > lpUser->Money)
		{
			Result = false;
		}
	}

	if(PriceType == eMarketPriceTypeWcoin)
	{
		if(PriceValue > lpUser->GameShop.WCoinC)
		{
			Result = false;
		}
	}

	if(PriceType == eMarketPriceTypeCredit)
	{
		if(PriceValue > lpUser->ZtCred)
		{
			Result = false;
		}
	}

	return Result;
}

bool CItemMarket::PlayerMoney(int aIndex, int PriceType, int PriceValue)
{
	bool Result = this->GetCheckMoney(aIndex, PriceType, PriceValue);

	LPOBJ lpUser = &gObj[aIndex];

	if(Result)
	{
		if(PriceType == eMarketPriceTypeZen)
		{
			lpUser->Money -= PriceValue;

			GCMoneySend(aIndex, lpUser->Money);

			MsgOutput(aIndex, "[MARKET][BUY] %s +%d Zen", lpUser->AccountID, PriceValue);
		}

		if(PriceType == eMarketPriceTypeWcoin)
		{
			lpUser->GameShop.WCoinC -= PriceValue;

			gGameShop.GDSaveUserInfo(lpUser->m_Index);

			MsgOutput(aIndex, "[MARKET][BUY] %s +%d Wcoin", lpUser->AccountID, PriceValue);
		}

		if(PriceType == eMarketPriceTypeCredit)
		{
			lpUser->ZtCred += PriceValue;

			ZtUserDataSend(lpUser->m_Index);

			MsgOutput(aIndex, "[MARKET][BUY] %s +%d Credit", lpUser->AccountID, PriceValue);
		}
	}

	return Result;
}

#if(MARKET_ITEM_RECV)

void CItemMarket::GDReqItemDate(SDHP_REQ_MARKET_ITEMRECV* lpMsg)
{
	int aIndex = lpMsg->aIndex;

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	SDHP_ANS_MARKET_ITEMRECV pMsg;

	pMsg.h.set((LPBYTE)&pMsg, 0xEC, 0x04, sizeof(pMsg));

	pMsg.Result = 1;

	pMsg.ID = lpMsg->ID;

	GCServerMsgStringSend("[ItemMarket] Item Recv : 1", aIndex, 0);

	CItem item;

	item = this->GetByteToItem(lpMsg->Item);

	BYTE btItemPos = gObjInventoryInsertItem(aIndex, item);

	if(btItemPos == -1)
	{
		return;
	}

	GCInventoryItemOneSend(lpMsg->aIndex, btItemPos);

	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}

#endif

#endif