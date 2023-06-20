#include "stdafx.h"
#include ".\\DbSet\\DBConBase.h"
#include "..\\include\\prodef.h"
#include "MainFrm.h"
#include "ItemMarket.h"

#if(DEV_PLAYERSHOP)

CItemMarket g_ItemMarket;

CItemMarket::CItemMarket()
{
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

bool CItemMarket::Connect()
{
	bool Result = this->m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass);

	if(Result)
	{
		this->CreateTable();

		bool Result = this->m_DBItem.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass);
	}

	return Result;
}

void CItemMarket::CreateTable()
{
	this->m_DBQuery.WriteLog = false;

	/*
		CREATE TABLE [dbo].[ItemMarketData]( [ID] [int] IDENTITY(1,1) NOT NULL, [Account] [varchar](10) NULL, [Name] [varchar](10) NULL, ) ON [PRIMARY]
	*/

	this->m_DBQuery.Exec("CREATE TABLE [dbo].[ItemMarketData]( [ID] [int] IDENTITY(1,1) NOT NULL) ON [PRIMARY]");
	this->m_DBQuery.Fetch();
	this->m_DBQuery.Clear();

	this->m_DBQuery.Exec("ALTER TABLE [ItemMarketData] ADD [Account] [varchar](10) NULL");
	this->m_DBQuery.Fetch();
	this->m_DBQuery.Clear();

	#if(MARKET_NAME_DEV)

	this->m_DBQuery.Exec("ALTER TABLE [ItemMarketData] ADD [Name][varchar](10) NULL");
	this->m_DBQuery.Fetch();
	this->m_DBQuery.Clear();

	#endif

	this->m_DBQuery.Exec("ALTER TABLE [ItemMarketData] ADD [PriceType] INT not null default(0)");
	this->m_DBQuery.Fetch();
	this->m_DBQuery.Clear();

	this->m_DBQuery.Exec("ALTER TABLE [ItemMarketData] ADD [PriceValue] INT not null default(0)");
	this->m_DBQuery.Fetch();
	this->m_DBQuery.Clear();

	this->m_DBQuery.Exec("ALTER TABLE [ItemMarketData] ADD [Status] INT not null default(0)");
	this->m_DBQuery.Fetch();
	this->m_DBQuery.Clear();

	#if(MARKET_FILTER_DEV)

	this->m_DBQuery.Exec("ALTER TABLE [ItemMarketData] ADD [FilterType] INT not null default(0)");
	this->m_DBQuery.Fetch();
	this->m_DBQuery.Clear();

	this->m_DBQuery.Exec("ALTER TABLE [ItemMarketData] ADD [FilterLevel] INT not null default(0)");
	this->m_DBQuery.Fetch();
	this->m_DBQuery.Clear();

	this->m_DBQuery.Exec("ALTER TABLE [ItemMarketData] ADD [FilterLuck] INT not null default(0)");
	this->m_DBQuery.Fetch();
	this->m_DBQuery.Clear();

	this->m_DBQuery.Exec("ALTER TABLE [ItemMarketData] ADD [FilterExl] INT not null default(0)");
	this->m_DBQuery.Fetch();
	this->m_DBQuery.Clear();

	this->m_DBQuery.Exec("ALTER TABLE [ItemMarketData] ADD [FilterAnc] INT not null default(0)");
	this->m_DBQuery.Fetch();
	this->m_DBQuery.Clear();

	#endif

	this->m_DBQuery.Exec("ALTER TABLE [ItemMarketData] ADD [Date] [varchar](20) NULL");
	this->m_DBQuery.Fetch();
	this->m_DBQuery.Clear();

	this->m_DBQuery.Exec("ALTER TABLE [ItemMarketData] ADD [Item] [varbinary](16) NULL");
	this->m_DBQuery.Fetch();
	this->m_DBQuery.Clear();

	this->m_DBQuery.WriteLog = true;
}

void CItemMarket::Protocol(BYTE protoNum, BYTE *aRecv, int uIndex)
{
	switch(protoNum)
	{
	case 0x00:
		this->GDReqItemList((SDHP_REQ_MARKET_ITEM *)aRecv, uIndex);
		break;
	case 0x01:
		this->GDReqItemSell((SDHP_REQ_MARKET_SELL *)aRecv, uIndex);
		break;
	case 0x02:
		this->GDReqBuyItem((SDHP_REQ_MARKET_BUY *)aRecv, uIndex);
		break;
	#if(MARKET_FILTER_DEV)
	case 0x03:
		this->GDReqItemStatus((SDHP_REQ_MARKET_STATUS *)aRecv, uIndex);
		break;
		#endif
	#if(MARKET_ITEM_RECV)
	case 0x04:
		this->GDAnsItemDate((SDHP_ANS_MARKET_ITEMRECV *)aRecv, uIndex);
		break;
	#endif
	}
}

void CItemMarket::GDReqItemList(SDHP_REQ_MARKET_ITEM* lpMsg, int uIndex)
{
	#if(MARKET_PRICE_DEV)

	this->GDReqItemListPage(lpMsg, uIndex);

	#else

	char szQuery[256];

	int iReturnCode = 0;

	int iCount = 0;

	SDHP_ANS_MARKET_ITEM pMsg;

	memset(&pMsg, 0, sizeof(pMsg));

	pMsg.h.set((LPBYTE)&pMsg, 0xFE, 0x00, sizeof(pMsg));

	pMsg.Result = 1;

	pMsg.aIndex = lpMsg->aIndex;

	// --

	char szPriceType[256];

	memset(szPriceType, 0, sizeof(szPriceType));

	if(lpMsg->PriceType == eMarketPriceTypeZen)
	{
		sprintf(szPriceType, "AND PriceType = %d ", lpMsg->PriceType);
	}

	if(lpMsg->PriceType == eMarketPriceTypeWcoin)
	{
		sprintf(szPriceType, "AND PriceType = %d ", lpMsg->PriceType);
	}

	if(lpMsg->PriceType == eMarketPriceTypeCredit)
	{
		sprintf(szPriceType, "AND PriceType = %d ", lpMsg->PriceType);
	}

	// --

	#if(MARKET_FILTER_DEV)

	char szFilter[256];

	memset(szFilter, 0, sizeof(szFilter));

	if(lpMsg->Filter.FilterType < 16)
	{
		sprintf(szFilter, "AND FilterType = %d ", lpMsg->Filter.FilterType);
	}

	if(lpMsg->Filter.FilterLevel > 0 && lpMsg->Filter.FilterLevel <= 15)	//=(
	{
		char szLevel[256];

		memset(szLevel, 0, sizeof(szLevel));

		sprintf(szLevel, "AND FilterLevel >= %d AND FilterLevel <= 15 ", lpMsg->Filter.FilterLevel);

		strcat(szFilter, szLevel);
	}
	
	if(lpMsg->Filter.FilterLuck)
	{
		strcat(szFilter, "AND FilterLuck = 1 ");
	}

	if(lpMsg->Filter.FilterExl)
	{
		strcat(szFilter, "AND FilterExl = 1 ");
	}

	if(lpMsg->Filter.FilterAnc)
	{
		strcat(szFilter, "AND FilterAnc = 1 ");
	}

	sprintf(szQuery, "SELECT TOP %d ID, Account, Name, PriceType, PriceValue FROM ItemMarketData WHERE Status = 0 %s %s ORDER BY ID DESC", MARKET_ITEM_MAX, szFilter, szPriceType);

	#else
	
	sprintf(szQuery, "SELECT TOP %d ID, Account, PriceType, PriceValue FROM ItemMarketData WHERE Status = 0 ORDER BY ID DESC", MARKET_ITEM_MAX); // <<== Arg

	#endif

	if(!this->m_DBQuery.Exec(szQuery))
	{
		this->m_DBQuery.Clear();

		pMsg.Result = 0;
	}	
	else
	{
		short sqlReturn = this->m_DBQuery.Fetch();

		while(sqlReturn != SQL_NO_DATA && sqlReturn != SQL_NULL_DATA)
		{
			iReturnCode = this->m_DBQuery.GetInt(1);

			if(iReturnCode < 0)
			{
				break;
			}

			char szSeller[MARKET_NAME_LEN];

			//this->m_DBQuery.GetStr("account", szSeller);
			this->m_DBQuery.GetStr("Name", szSeller);

			pMsg.Data[iCount].Name[MARKET_NAME_LEN-1] = 0;

			memcpy(pMsg.Data[iCount].Name, szSeller, MARKET_NAME_LEN-1);

			pMsg.Data[iCount].PriceType = this->m_DBQuery.GetInt("PriceType");

			pMsg.Data[iCount].Price = this->m_DBQuery.GetInt("PriceValue");

			// --

			int id = this->m_DBQuery.GetInt("ID");

			pMsg.Data[iCount].ID = id;

			sprintf(szQuery, "SELECT Item FROM ItemMarketData WHERE ID = %d", id);

			int	nRet = this->m_DBItem.ReadBlob(szQuery, pMsg.Data[iCount].Item);

			if(nRet < 0)
			{
				memset(pMsg.Data[iCount].Item, -1, sizeof(pMsg.Data[iCount].Item));
			}

			// --

			iCount++;

			if(iCount >= MARKET_ITEM_MAX)
			{
				break;
			}

			sqlReturn = this->m_DBQuery.Fetch();
		}

		this->m_DBQuery.Clear();
	}

	wsjServer.DataSend(uIndex, (char*)&pMsg, sizeof(pMsg));

	//LogAddC(2, "[DATA -> SERVER] : GDReqItemList");

	#endif
}

void CItemMarket::GDReqItemSell(SDHP_REQ_MARKET_SELL* lpMsg, int uIndex)
{
	char szQuery[512];

	SDHP_ANS_MARKET_SELL pMsg;

	memset(&pMsg, 0, sizeof(pMsg));

	pMsg.h.set((LPBYTE)&pMsg, 0xFE, 0x01, sizeof(pMsg));

	pMsg.Result = 1;

	pMsg.aIndex = lpMsg->aIndex;

	pMsg.ItemPos = lpMsg->ItemPos;

	#if(MARKET_FILTER_DEV)

	char szAccount[11];
	memset(szAccount, 0, sizeof(szAccount));
	memcpy(szAccount, lpMsg->Account, sizeof(szAccount)-1);

	char szName[11];
	memset(szName, 0, sizeof(szName));
	memcpy(szName, lpMsg->Name, sizeof(szName)-1);

	#if(MARKET_ITEM_RECV)

	char szDate[20] = { 0 };

	SYSTEMTIME st;

	GetLocalTime(&st);

	sprintf(szDate, "%02d.%02d.%04d-%02d:%02d", st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute);

	sprintf(szQuery, 
		"INSERT INTO ItemMarketData (Account, PriceType, PriceValue, Date, Status, FilterLuck, FilterExl, FilterAnc, FilterType, FilterLevel, Name) VALUES ('%s', %d, %d, '%s', 0, %d, %d, %d, %d, %d, '%s')", 
		lpMsg->Account, 
		lpMsg->PriceType,
		lpMsg->Price, 
		szDate,
		lpMsg->Filter.FilterLuck,
		lpMsg->Filter.FilterExl,
		lpMsg->Filter.FilterAnc,
		lpMsg->Filter.FilterType,
		lpMsg->Filter.FilterLevel,
		lpMsg->Name
		);

	#else

	sprintf(szQuery, 
		"INSERT INTO ItemMarketData (Account, PriceType, PriceValue, Date, Status, FilterLuck, FilterExl, FilterAnc, FilterType, FilterLevel, Name) VALUES ('%s', %d, %d, '%s', 0, %d, %d, %d, %d, %d, '%s')", 
		lpMsg->Account, 
		lpMsg->PriceType,
		lpMsg->Price, 
		"19.12.2020",
		lpMsg->Filter.FilterLuck,
		lpMsg->Filter.FilterExl,
		lpMsg->Filter.FilterAnc,
		lpMsg->Filter.FilterType,
		lpMsg->Filter.FilterLevel,
		lpMsg->Name
		);

	#endif

	#else

	sprintf(szQuery, "INSERT INTO ItemMarketData (Account, PriceType, PriceValue, Date, Status) VALUES ('%s', %d, %d, '%s', 0)", 
		lpMsg->Account, lpMsg->PriceType, lpMsg->Price, "19.12.2020");

	#endif

	pMsg.Result = this->m_DBQuery.Exec(szQuery);

	this->m_DBQuery.Fetch();

	this->m_DBQuery.Clear();

	// --

	sprintf(szQuery, "SELECT TOP 1 ID FROM ItemMarketData ORDER BY ID DESC");	//need recode

	if(!this->m_DBQuery.Exec(szQuery) || this->m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		pMsg.Result = 0;
	}

	int id = this->m_DBQuery.GetInt("ID");

	this->m_DBQuery.Clear();

	// --

	sprintf(szQuery, "UPDATE ItemMarketData SET Item = ? WHERE ID = %d", id);

	this->m_DBItem.WriteBlob(szQuery, lpMsg->ItemData, 16);

	// --

	wsjServer.DataSend(uIndex, (char*)&pMsg, sizeof(pMsg));

	//LogAddC(2, "[DATA -> SERVER] : GDReqItemSell");
}

void CItemMarket::GDReqBuyItem(SDHP_REQ_MARKET_BUY* lpMsg, int uIndex)
{
	char szQuery[256];

	int iResult = lpMsg->Result;

	if(iResult)
	{
		sprintf(szQuery, "UPDATE ItemMarketData SET Status = 1 WHERE ID = %d", lpMsg->ID);

		iResult = this->m_DBQuery.Exec(szQuery);

		this->m_DBQuery.Clear();
	}

	SDHP_ANS_MARKET_BUY pMsg;

	memset(&pMsg, 0, sizeof(pMsg));

	pMsg.h.set((LPBYTE)&pMsg, 0xFE, 0x02, sizeof(pMsg));

	pMsg.Result = iResult;

	pMsg.aIndex = lpMsg->aIndex;

	pMsg.ID = lpMsg->ID;

	wsjServer.DataSend(uIndex, (char*)&pMsg, sizeof(pMsg));
}

#if(MARKET_PRICE_DEV)

void CItemMarket::GDReqItemStatus(SDHP_REQ_MARKET_STATUS* lpMsg, int uIndex)
{
	char szQuery[256];

	SDHP_ANS_MARKET_STATUS pMsg;

	memset(&pMsg, 0, sizeof(pMsg));

	pMsg.h.set((LPBYTE)&pMsg, 0xFE, 0x03, sizeof(pMsg));

	pMsg.Result = 1;

	pMsg.aIndex = lpMsg->aIndex;

	#if(MARKET_DEBUG)

	while(true)
	{
		pMsg.Result = 1;

		sprintf(szQuery, "SELECT * FROM ItemMarketData WHERE Account = '%s' AND Status = 1", lpMsg->Account);

		if(!this->m_DBQuery.Exec(szQuery) || this->m_DBQuery.Fetch() == SQL_NO_DATA)
		{
			pMsg.Result = 0;

			this->m_DBQuery.Clear();

			break;
		}
		else
		{
			int iID = this->m_DBQuery.GetInt("ID");

			pMsg.PriceType = this->m_DBQuery.GetInt("PriceType");

			pMsg.PriceValue = this->m_DBQuery.GetInt("PriceValue");

			this->m_DBQuery.GetStr("Account", pMsg.Account);

			this->m_DBQuery.Clear();

			// --
	
			if(pMsg.Result)
			{
				sprintf(szQuery, "DELETE FROM ItemMarketData WHERE ID = %d", iID);

				if(!this->m_DBQuery.Exec(szQuery) || this->m_DBQuery.Fetch() == SQL_NO_DATA)
				{
					pMsg.Result = 0;
				}

				this->m_DBQuery.Clear();
			}
		}

		wsjServer.DataSend(uIndex, (char*)&pMsg, sizeof(pMsg));
	}

	#if(MARKET_ITEM_RECV)

	this->GDReqItemDate(uIndex, lpMsg->Account, lpMsg->aIndex);

	#endif

	#else

	sprintf(szQuery, "SELECT * FROM ItemMarketData WHERE Account = '%s' AND Status = 1", lpMsg->Account);

	if(!this->m_DBQuery.Exec(szQuery) || this->m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		pMsg.Result = 0;
	}
	else
	{
		int iID = this->m_DBQuery.GetInt("ID");

		pMsg.PriceType = this->m_DBQuery.GetInt("PriceType");

		pMsg.PriceValue = this->m_DBQuery.GetInt("PriceValue");

		this->m_DBQuery.GetStr("Account", pMsg.Account);

		this->m_DBQuery.Clear();

		// --
	
		if(pMsg.Result)
		{
			sprintf(szQuery, "DELETE FROM ItemMarketData WHERE ID = %d", iID);

			if(!this->m_DBQuery.Exec(szQuery) || this->m_DBQuery.Fetch() == SQL_NO_DATA)
			{
				pMsg.Result = 0;
			}

			this->m_DBQuery.Clear();
		}
	}

	wsjServer.DataSend(uIndex, (char*)&pMsg, sizeof(pMsg));

	#endif
}

#endif

#if(MARKET_PRICE_DEV)

void CItemMarket::GDReqItemListPage(SDHP_REQ_MARKET_ITEM* lpMsg, int uIndex)
{
	char szQuery[256];

	int iReturnCode = 0;

	int iCount = 0;

	int iPageNumber = lpMsg->PageNumber;

	SDHP_ANS_MARKET_ITEM pMsg;

	memset(&pMsg, 0, sizeof(pMsg));

	pMsg.h.set((LPBYTE)&pMsg, 0xFE, 0x00, sizeof(pMsg));

	pMsg.Result = 1;

	pMsg.aIndex = lpMsg->aIndex;

	// --

	char szPriceType[256];

	memset(szPriceType, 0, sizeof(szPriceType));

	if(lpMsg->PriceType == eMarketPriceTypeZen)
	{
		sprintf(szPriceType, "AND PriceType = %d ", lpMsg->PriceType);
	}

	if(lpMsg->PriceType == eMarketPriceTypeWcoin)
	{
		sprintf(szPriceType, "AND PriceType = %d ", lpMsg->PriceType);
	}

	if(lpMsg->PriceType == eMarketPriceTypeCredit)
	{
		sprintf(szPriceType, "AND PriceType = %d ", lpMsg->PriceType);
	}

	// --

	#if(MARKET_FILTER_DEV)

	char szFilter[256];

	memset(szFilter, 0, sizeof(szFilter));

	if(lpMsg->Filter.FilterType < 16)
	{
		sprintf(szFilter, "AND FilterType = %d ", lpMsg->Filter.FilterType);
	}

	if(lpMsg->Filter.FilterLevel > 0 && lpMsg->Filter.FilterLevel <= 15)	//=(
	{
		char szLevel[256];

		memset(szLevel, 0, sizeof(szLevel));

		sprintf(szLevel, "AND FilterLevel >= %d AND FilterLevel <= 15 ", lpMsg->Filter.FilterLevel);

		strcat(szFilter, szLevel);
	}
	
	if(lpMsg->Filter.FilterLuck)
	{
		strcat(szFilter, "AND FilterLuck = 1 ");
	}

	if(lpMsg->Filter.FilterExl)
	{
		strcat(szFilter, "AND FilterExl = 1 ");
	}

	if(lpMsg->Filter.FilterAnc)
	{
		strcat(szFilter, "AND FilterAnc = 1 ");
	}

	sprintf(szQuery, "SELECT TOP %d ID, Account, Name, PriceType, PriceValue FROM ItemMarketData WHERE Status = 0 %s %s ORDER BY ID DESC", MARKET_ITEM_MAX*10, szFilter, szPriceType);

	#else
	
	sprintf(szQuery, "SELECT TOP %d ID, Account, PriceType, PriceValue FROM ItemMarketData WHERE Status = 0 ORDER BY ID DESC", MARKET_ITEM_MAX); // <<== Arg

	#endif

	if(!this->m_DBQuery.Exec(szQuery))
	{
		this->m_DBQuery.Clear();

		pMsg.Result = 0;
	}	
	else
	{
		int iQueryCount = 0;

		short sqlReturn = this->m_DBQuery.Fetch();

		while(sqlReturn != SQL_NO_DATA && sqlReturn != SQL_NULL_DATA)
		{
			iReturnCode = this->m_DBQuery.GetInt(1);

			if(iReturnCode < 0)
			{
				break;
			}

			if(iQueryCount >= iPageNumber * MARKET_ITEM_MAX)
			{
				char szSeller[MARKET_NAME_LEN];

				//this->m_DBQuery.GetStr("account", szSeller);
				this->m_DBQuery.GetStr("Name", szSeller);

				pMsg.Data[iCount].Name[MARKET_NAME_LEN-1] = 0;

				memcpy(pMsg.Data[iCount].Name, szSeller, MARKET_NAME_LEN-1);

				pMsg.Data[iCount].PriceType = this->m_DBQuery.GetInt("PriceType");

				pMsg.Data[iCount].Price = this->m_DBQuery.GetInt("PriceValue");

				// --

				int id = this->m_DBQuery.GetInt("ID");

				pMsg.Data[iCount].ID = id;

				sprintf(szQuery, "SELECT Item FROM ItemMarketData WHERE ID = %d", id);

				int	nRet = this->m_DBItem.ReadBlob(szQuery, pMsg.Data[iCount].Item);

				if(nRet < 0)
				{
					memset(pMsg.Data[iCount].Item, -1, sizeof(pMsg.Data[iCount].Item));
				}

				// --

				iCount++;

				if(iCount >= MARKET_ITEM_MAX)
				{
					break;
				}
			}

			sqlReturn = this->m_DBQuery.Fetch();

			iQueryCount++;
		}

		this->m_DBQuery.Clear();
	}

	wsjServer.DataSend(uIndex, (char*)&pMsg, sizeof(pMsg));

	//LogAddC(2, "[DATA -> SERVER] : GDReqItemList");
}

#endif

#if(MARKET_ITEM_RECV)

CTime CItemMarket::StrToCTime(const char* str)
{
	int year, month, day, hh, mm, ss=0;

	sscanf(str, "%02d.%02d.%04d-%02d:%02d", &day, &month, &year, &hh, &mm);

	return CTime(year, month, day, hh, mm, ss);
}

void CItemMarket::RunItemDate()
{
	bool bResult = false;

	char szQuery[256] = { 0 };

	int iItemMaxTime = 60;	//86400

	while(true)
	{
		bResult = false;

		sprintf(szQuery, "SELECT * FROM ItemMarketData WHERE Status = 0");

		if(!this->m_DBQuery.Exec(szQuery) || this->m_DBQuery.Fetch() == SQL_NO_DATA)
		{
			this->m_DBQuery.Clear();

			break;
		}
		else
		{
			int iID = this->m_DBQuery.GetInt("ID");

			// --

			DWORD dwDate1 = 0;

			DWORD dwDate2 = 0;
	
			char szDate1[20] = { 0 };

			char szDate2[20] = { 0 };

			SYSTEMTIME st;

			GetLocalTime(&st);

			sprintf(szDate1, "%02d.%02d.%04d-%02d:%02d", st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute);

			this->m_DBQuery.GetStr("Date", szDate2);

			CTime ct1 = this->StrToCTime(szDate1);

			CTime ct2 = this->StrToCTime(szDate2);

			dwDate1 = ct1.GetTime();

			dwDate2 = ct2.GetTime();

			if(dwDate1 + iItemMaxTime > dwDate2)
			{
				bResult = true;
			}

			// --
	
			this->m_DBQuery.Clear();

			if(bResult)
			{
				sprintf(szQuery, "UPDATE ItemMarketData SET Status = 2 WHERE ID = %d", iID);

				this->m_DBQuery.Exec(szQuery);

				this->m_DBQuery.Clear();
			}
		}
	}
}

void CItemMarket::GDReqItemDate(int uIndex, char* Account, int aIndex)
{
	char szQuery[256] = { 0 };

	SDHP_REQ_MARKET_ITEMRECV pMsg;

	memset(&pMsg, 0, sizeof(pMsg));

	pMsg.h.set((LPBYTE)&pMsg, 0xFE, 0x04, sizeof(pMsg));

	pMsg.Result = 0;

	pMsg.aIndex = aIndex;

	sprintf(szQuery, "SELECT * FROM ItemMarketData WHERE Account = '%s' AND Status = 2", Account);

	if(!this->m_DBQuery.Exec(szQuery))
	{
		this->m_DBQuery.Clear();
	}
	else
	{
		int iReturnCode = 0;

		short sqlReturn = this->m_DBQuery.Fetch();

		while(sqlReturn != SQL_NO_DATA && sqlReturn != SQL_NULL_DATA)
		{
			iReturnCode = this->m_DBQuery.GetInt(1);

			if(iReturnCode < 0)
			{
				break;
			}

			pMsg.Result = 1;

			int iID = this->m_DBQuery.GetInt("ID");	

			pMsg.ID = iID;

			sprintf(szQuery, "SELECT Item FROM ItemMarketData WHERE ID = %d", iID);

			int	nRet = this->m_DBItem.ReadBlob(szQuery, pMsg.Item);

			if(nRet < 0)
			{
				pMsg.Result = 0;
			}	
	
			if(pMsg.Result)
			{
				wsjServer.DataSend(uIndex, (char*)&pMsg, sizeof(pMsg));
			}

			sqlReturn = this->m_DBQuery.Fetch();
		}

		this->m_DBQuery.Clear();
	}

	//while(true)
	//{
	//	

	//	if(!this->m_DBQuery.Exec(szQuery) || this->m_DBQuery.Fetch() == SQL_NO_DATA)
	//	{
	//		this->m_DBQuery.Clear();

	//		break;
	//	}
	//	else
	//	{
	//		pMsg.Result = 1;

	//		int iID = this->m_DBQuery.GetInt("ID");	

	//		pMsg.ID = iID;

	//		sprintf(szQuery, "SELECT Item FROM ItemMarketData WHERE ID = %d", iID);

	//		int	nRet = this->m_DBItem.ReadBlob(szQuery, pMsg.Item);

	//		if(nRet < 0)
	//		{
	//			pMsg.Result = 0;
	//		}

	//		this->m_DBQuery.Clear();
	//
	//		if(pMsg.Result)
	//		{
	//			wsjServer.DataSend(uIndex, (char*)&pMsg, sizeof(pMsg));
	//		}
	//	}		
	//}
}

void CItemMarket::GDAnsItemDate(SDHP_ANS_MARKET_ITEMRECV* lpMsg, int uIndex)
{
	char szQuery[256];

	sprintf(szQuery, "DELETE FROM ItemMarketData WHERE ID = %d", lpMsg->ID);

	this->m_DBQuery.Exec(szQuery);

	this->m_DBQuery.Fetch();

	this->m_DBQuery.Clear();		
}

#endif

#endif