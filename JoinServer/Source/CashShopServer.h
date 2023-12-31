#if !defined(CASHSHOPSERVER_H)
#define CASHSHOPSERVER_H

#include "stdafx.h"
#include "CQuery.h"
#define MAX_NTF_TRANSACTIONS	16
#define MAX_SELL_ITEMS			128
#define MAX_ITEM_PRICE			3
#define MAX_STORAGE_PAGE_ITEMS	9

#define CS_INISECTION			"CashShopServer"

struct CS_INFO
{
	WORD TCPPort;
	char dbDSN[64];
	char mydbDSN[64];
};

#pragma pack(1)
struct sellItemPrice
{
	DWORD dwPriceGuid;	// 0
	DWORD dwItemGuid;	// 4
	DWORD dwUseTime;	// 8
	DWORD dwAmount;	// C
	DWORD dwPrice;	// 10
	DWORD dwSellRate;	// 14
};

struct sellItem
{
	DWORD dwItemGuid;	// 0
	DWORD dwItemCODE;	// 4
	DWORD dwCategoryID;	// 8
	DWORD dwUseType;	// C
	//DWORD dwBuyType;	// 10
	//DWORD dwCoolTime;	// 14
	//double dbVarEndDate;	// 18
	//DWORD dwLimitSellCount;	// 20
	//DWORD dwState;	// 24
	DWORD dwPriceCount;	// E8
	sellItemPrice itemPrice[3];	// EC
};


struct sellPackage
{
	DWORD dwPackageGuid;	// 0
	sellItemPrice itemPrice;	// 4
	DWORD dwImageCode;	// 1C
	DWORD dwCategory;	// 20
	DWORD dwBuyType;	// 24
	DWORD dwLimitSellCount;	// 28
	DWORD dwInItemCount;	// 2C
	double dbVarEndDate;	// 30
	DWORD dwState;	// 38
	sellItemPrice inItemPrices[16];	// 3C
	char szPackageName[64];	// 1BC
	char szPackageDesc[128];	// 1FC
};


struct buyItemTransaction
{
	DWORD dwTransactionGuid;	// 0
	DWORD dwPriceGuid;	// 4
	DWORD dwResult;	// 8
};


struct itemBranch
{
	DWORD dwBranchID;	// 0
	DWORD dwGuid;	// 4
	DWORD dwItemType;	// 8
};



#pragma pack()



namespace protocol
{
	class HDRMessageID
	{
	public:
		WORD category;	// 0
		WORD messageID;	// 2
	};

	class MSG_HEADER
	{
	public:

		DWORD size;	// 0
		union
		{
			DWORD id;	// 4
			HDRMessageID hdrid;	// 4
		};


	};


	class MSG_GTOS_USER_CASH_REQ : public MSG_HEADER
	{
	public:
		DWORD dwUserGuid;	// 8	

		MSG_GTOS_USER_CASH_REQ()
		{
			this->size = sizeof(MSG_GTOS_USER_CASH_REQ);
			this->id = 0x100;
		};	// line : 74

		~MSG_GTOS_USER_CASH_REQ()
		{
		};

	};

	class MSG_STOG_USER_CASH_ANS : public MSG_HEADER
	{
	public:
		DWORD dwUserGuid;	// 8
		DWORD dwUserCash;	// C

		MSG_STOG_USER_CASH_ANS()
		{
			this->size = sizeof(MSG_STOG_USER_CASH_ANS);
			this->id = 0x200;
		};

		~MSG_STOG_USER_CASH_ANS()
		{
		};
	};

	class MSG_GTOS_ITEM_LIST_REQ : public MSG_HEADER
	{
	public:
		MSG_GTOS_ITEM_LIST_REQ()
		{
			this->size = sizeof(MSG_GTOS_ITEM_LIST_REQ);
			this->id = 0x300;
		};

		~MSG_GTOS_ITEM_LIST_REQ()
		{
		};
	};


	class MSG_STOG_ITEM_LIST_ANS : public MSG_HEADER
	{
	public:
		MSG_STOG_ITEM_LIST_ANS()
		{
			this->size = sizeof(MSG_STOG_ITEM_LIST_ANS);
			this->id = 0x400;
		};
		~MSG_STOG_ITEM_LIST_ANS()
		{
			return;
		};

		void resize();

		DWORD dwItemCount;	// 8
		sellItem sellItems[64];	// C
	};



	class MSG_GTOS_PACKAGE_LIST_REQ : public MSG_HEADER
	{
	public:
		MSG_GTOS_PACKAGE_LIST_REQ()
		{
			this->size = sizeof(MSG_GTOS_PACKAGE_LIST_REQ);
			this->id = 0x500;
		};

		~MSG_GTOS_PACKAGE_LIST_REQ()
		{
		};
	};

	class MSG_STOG_PACKAGE_LIST_ANS : public MSG_HEADER
	{
	public:
		MSG_STOG_PACKAGE_LIST_ANS()
		{
			this->size = sizeof(MSG_STOG_PACKAGE_LIST_ANS);
			this->id = 0x600;
		};

		~MSG_STOG_PACKAGE_LIST_ANS()
		{
		};
		void resize();

		DWORD dwPackageCount;	// 8
		sellPackage sellPackages[96];	// C
	};


	class MSG_GTOS_BRANCH_ITEM_LIST_REQ : public MSG_HEADER
	{
	public:
		MSG_GTOS_BRANCH_ITEM_LIST_REQ()
		{
			this->size = sizeof(MSG_GTOS_BRANCH_ITEM_LIST_REQ);
			this->id = 0x700;
		};

		~MSG_GTOS_BRANCH_ITEM_LIST_REQ()
		{
		};

	};

	class MSG_STOG_BRANCH_ITEM_LIST_ANS : public MSG_HEADER
	{
	public:
		DWORD dwItemCount;	// 8
		itemBranch branchItems[512];	// C

		MSG_STOG_BRANCH_ITEM_LIST_ANS()
		{
			this->size = sizeof(MSG_STOG_BRANCH_ITEM_LIST_ANS);
			this->id = 0x800;
		};


		~MSG_STOG_BRANCH_ITEM_LIST_ANS()
		{
		};

		void resize();
	};

	class MSG_GTOS_BUY_ITEM_REQ : public MSG_HEADER
	{
	public:
		DWORD dwServerGuid;	// 8
		DWORD dwUserGuid;	// C
		DWORD dwCharGuid;	// 10
		char szCharName[96];	// 14
		DWORD dwCount;	// 74
		DWORD dwPriceGuids[16];	// 78

		MSG_GTOS_BUY_ITEM_REQ()
		{
			this->size = sizeof(MSG_GTOS_BUY_ITEM_REQ);
			this->id = 0x900;
		};

		~MSG_GTOS_BUY_ITEM_REQ()
		{
		};

		void resize();
	};

	class MSG_STOG_BUY_ITEM_ANS : public MSG_HEADER
	{
	public:
		DWORD dwServerGuid;	// 8
		DWORD dwUserGuid;	// C
		DWORD dwCharGuid;	// 10
		DWORD dwUserCash;	// 14
		DWORD dwResult;	// 18
		DWORD dwCount;	// 1C
		buyItemTransaction transactions[16];	// 20

		MSG_STOG_BUY_ITEM_ANS()
		{
			this->size = sizeof(MSG_STOG_BUY_ITEM_ANS);
			this->id = 0xA00;
		};

		~MSG_STOG_BUY_ITEM_ANS()
		{
		};

		void resize();
	};

	class MSG_GTOS_BUY_ITEM_NTF : public MSG_HEADER
	{
	public:
		MSG_GTOS_BUY_ITEM_NTF()
		{
			this->size = sizeof(MSG_GTOS_BUY_ITEM_NTF);
			this->id = 0xB00;
		};


		~MSG_GTOS_BUY_ITEM_NTF()
		{
		};

		void resize()
		{
			this->size -= (16 - (DWORD)((WORD)(this->dwCount))) * sizeof(buyItemTransaction);
		};

		DWORD dwServerGuid;	// 8
		DWORD dwUserGuid;	// C
		DWORD dwCharGuid;	// 10
		DWORD dwCount;	// 14
		buyItemTransaction transactions[16];	// 18

	};

	class MSG_GTOS_USER_CASH_REQ_ZT : public MSG_HEADER
	{
	public:
		DWORD dwUserGuid;	// 8	

		MSG_GTOS_USER_CASH_REQ_ZT()
		{
			this->size = sizeof(MSG_GTOS_USER_CASH_REQ_ZT);
			this->hdrid.category = 0x100;
			this->hdrid.messageID = 1;
		};	// line : 74

		~MSG_GTOS_USER_CASH_REQ_ZT()
		{
		};

	};

	class MSG_STOG_USER_CASH_ANS_ZT : public MSG_HEADER
	{
	public:
		DWORD dwUserGuid;
		DWORD dwUserCash[3];

		MSG_STOG_USER_CASH_ANS_ZT()
		{
			this->size = sizeof(MSG_STOG_USER_CASH_ANS_ZT);
			this->id = 0x200;
		};

		~MSG_STOG_USER_CASH_ANS_ZT()
		{
		};
	};

	class MSG_GTOS_ITEM_LIST_REQ_ZT : public MSG_HEADER
	{
	public:
		DWORD dwUserGuid;
		DWORD dwPageId;

		MSG_GTOS_ITEM_LIST_REQ_ZT()
		{
			this->size = sizeof(MSG_GTOS_ITEM_LIST_REQ_ZT);
			this->hdrid.category = 0x300;
			this->hdrid.messageID = 1;
		};

		~MSG_GTOS_ITEM_LIST_REQ_ZT()
		{
		};
	};

	struct productInfoEx
	{
		DWORD dwGuid;
		DWORD dwUnk1;
		DWORD dwUnk2;
		DWORD dwGroupIndex;
		DWORD dwProductIndex;
		double Durability;
		DWORD dwType;
	};

	class MSG_STOG_ITEM_LIST_ANS_ZT : public MSG_HEADER
	{
	public:
		DWORD dwUserGuid;
		DWORD dwPageId;
		DWORD dwType;
		DWORD dwItemCount;

		productInfoEx itemList[9];

		MSG_STOG_ITEM_LIST_ANS_ZT()
		{
			this->size = sizeof(MSG_STOG_ITEM_LIST_ANS_ZT);
			this->id = 0x400;
		};

		~MSG_STOG_ITEM_LIST_ANS_ZT()
		{
		};

		void resize()
		{
			this->size = sizeof(MSG_STOG_ITEM_LIST_ANS_ZT) - ((9 - this->dwItemCount)*sizeof(productInfoEx));
		};
	};

	class MSG_GTOS_ITEM_USE_REQ_ZT : public MSG_HEADER
	{
	public:
		DWORD dwUserGuid;
		DWORD dwItemGuid;
		DWORD dwUnkInfo;
		DWORD dwItemId;
		DWORD dwItemType;

		MSG_GTOS_ITEM_USE_REQ_ZT()
		{
			this->size = sizeof(MSG_GTOS_ITEM_USE_REQ_ZT);
			this->hdrid.category = 0x500;
			this->hdrid.messageID = 1;
		};

		~MSG_GTOS_ITEM_USE_REQ_ZT()
		{
		};
	};

	struct useInfoZt
	{
		DWORD	dwItemGuid;
		DWORD	dwItemId;
		DWORD	dwDurability;
		DWORD	dwUseTime;

#if (ZT700==1)
		BYTE btLevel;
		BYTE btOption1;
		BYTE btOption2;
		BYTE btOption3;
		BYTE btExcOp;
		BYTE btAncOp;
#endif
	};

	class MSG_STOG_ITEM_USE_ANS_ZT : public MSG_HEADER
	{
	public:
		DWORD dwUserGuid;
		DWORD dwResult;

		useInfoZt	itemInfo;

		MSG_STOG_ITEM_USE_ANS_ZT()
		{
			this->size = sizeof(MSG_STOG_ITEM_USE_ANS_ZT);
			this->id = 0x600;
		};

		~MSG_STOG_ITEM_USE_ANS_ZT()
		{
		};
	};

	class MSG_GTOS_GIFT_LIST_REQ_ZT : public MSG_HEADER
	{
		public:
		DWORD dwUserGuid;
		DWORD dwPageId;

		MSG_GTOS_GIFT_LIST_REQ_ZT()
		{
			this->size = sizeof(MSG_GTOS_GIFT_LIST_REQ_ZT);
			this->hdrid.category = 0x700;
			this->hdrid.messageID = 1;
		};

		~MSG_GTOS_GIFT_LIST_REQ_ZT()
		{
		};
	};

	struct productGiftEx : public productInfoEx
	{
		char szFrom[11];
		char szText[200];
	};

	class MSG_STOG_GIFT_LIST_ANS_ZT : public MSG_HEADER
	{
	public:
		DWORD dwUserGuid;
		DWORD dwPageId;
		DWORD dwType;
		DWORD dwItemCount;

		productGiftEx itemList[9];

		MSG_STOG_GIFT_LIST_ANS_ZT()
		{
			this->size = sizeof(MSG_STOG_GIFT_LIST_ANS_ZT);
			this->id = 0x800;
		};

		~MSG_STOG_GIFT_LIST_ANS_ZT()
		{
		};

		void resize()
		{
			this->size = sizeof(MSG_STOG_ITEM_LIST_ANS_ZT) - ((9 - this->dwItemCount)*sizeof(productInfoEx));
		};
	};

	class MSG_GTOS_BUY_ITEM_REQ_ZT : public MSG_HEADER
	{
	public:
		DWORD dwServerGuid;
		DWORD dwUserGuid;
		DWORD dwCharGuid;
		char szCharName[11];
		DWORD dwPackageCategory;
		DWORD dwPackageId;
		DWORD dwProductId;
		short ItemID;


		MSG_GTOS_BUY_ITEM_REQ_ZT()
		{
			this->size = sizeof(MSG_GTOS_BUY_ITEM_REQ_ZT);
			this->hdrid.category = 0x900;
			this->hdrid.messageID = 1;
		};

		~MSG_GTOS_BUY_ITEM_REQ_ZT()
		{
		};

		void resize();
	};

	class MSG_STOG_BUY_ITEM_ANS_ZT : public MSG_HEADER
	{
	public:
		DWORD dwServerGuid;
		DWORD dwUserGuid;
		DWORD dwCharGuid;
		DWORD dwUserCash[3];
		DWORD dwResult;

		MSG_STOG_BUY_ITEM_ANS_ZT()
		{
			this->size = sizeof(MSG_STOG_BUY_ITEM_ANS_ZT);
			this->id = 0xA00;
		};

		~MSG_STOG_BUY_ITEM_ANS_ZT()
		{
		};

		void resize();
	};

	class MSG_GTOS_USE_ITEM_NTF_ZT : public MSG_HEADER
	{
	public:
		MSG_GTOS_USE_ITEM_NTF_ZT()
		{
			this->size = sizeof(MSG_GTOS_USE_ITEM_NTF_ZT);
			this->hdrid.category = 0xB00;
			this->hdrid.messageID = 1;
		};


		~MSG_GTOS_USE_ITEM_NTF_ZT()
		{
		};

		DWORD dwUserGuid;
		DWORD dwItemGuid;
	};


	class MSG_GTOS_GIFT_ITEM_REQ_ZT : public MSG_HEADER
	{
	public:
		DWORD dwServerGuid;
		DWORD dwUserGuid;
		DWORD dwCharGuid;
		char szCharName[11];
		DWORD dwPackageCategory;
		DWORD dwPackageId;
		DWORD dwProductId;
		short ItemID;

		char szToName[11];
		char szText[200];

		MSG_GTOS_GIFT_ITEM_REQ_ZT()
		{
			this->size = sizeof(MSG_GTOS_GIFT_ITEM_REQ_ZT);
			this->hdrid.category = 0xD00;
			this->hdrid.messageID = 1;
		};

		~MSG_GTOS_GIFT_ITEM_REQ_ZT()
		{
		};

		void resize();
	};

	class MSG_STOG_GIFT_ITEM_ANS_ZT : public MSG_HEADER
	{
	public:
		DWORD dwServerGuid;
		DWORD dwUserGuid;
		DWORD dwCharGuid;
		DWORD dwUserCash[3];
		DWORD dwResult;

		MSG_STOG_GIFT_ITEM_ANS_ZT()
		{
			this->size = sizeof(MSG_STOG_GIFT_ITEM_ANS_ZT);
			this->id = 0xE00;
		};

		~MSG_STOG_GIFT_ITEM_ANS_ZT()
		{
		};

		void resize();
	};

	class MSG_GTOS_UPDATE_POINT_ZT : public MSG_HEADER
	{
	public:
		DWORD dwUserGuid;
		DWORD dwAddPoint[3];

		MSG_GTOS_UPDATE_POINT_ZT()
		{
			this->size = sizeof(MSG_GTOS_UPDATE_POINT_ZT);
			this->hdrid.category = 0xF00;
			this->hdrid.messageID = 1;
		};

		~MSG_GTOS_UPDATE_POINT_ZT()
		{
		};

		void resize();
	};

}

BOOL LoadCashItemList();
void CSProtocolCore(int aIndex, DWORD HeadCode, LPBYTE aRecv, int iSize);
void CashShopServerInit();

void LoadCashShopPackage();
void LoadCashShopProduct();

void SGAnsCashPoint(int aIndex,protocol::MSG_GTOS_USER_CASH_REQ *aRecv);
void SGAnsCashItemList(int aIndex);
void SGAnsBuyCashItem(int aIndex,protocol::MSG_GTOS_BUY_ITEM_REQ *aRecv);

void SGAnsCashPointEx(int aIndex,protocol::MSG_GTOS_USER_CASH_REQ_ZT *aRecv);
void SGAndCashItemListEx(int aIndex,protocol::MSG_GTOS_ITEM_LIST_REQ_ZT *aRecv);
void SGAnsCashItemUseEx(int aIndex,protocol::MSG_GTOS_ITEM_USE_REQ_ZT *aRecv);
void SGAndCashGiftListEx(int aIndex,protocol::MSG_GTOS_GIFT_LIST_REQ_ZT *aRecv);
void SGAnsBuyCashItemEx(int aIndex,protocol::MSG_GTOS_BUY_ITEM_REQ_ZT *aRecv);
void SGAnsUseCashItemNotifyEx(int aIndex,protocol::MSG_GTOS_USE_ITEM_NTF_ZT *aRecv);
void SGAnsGiftCashItemEx(int aIndex,protocol::MSG_GTOS_GIFT_ITEM_REQ_ZT *aRecv);
void SGUpdatePointInfo(int aIndex,protocol::MSG_GTOS_UPDATE_POINT_ZT *aRecv);


struct PACKAGE_INFO
{
	WORD wGuid;
	BYTE btUseType;
	BYTE bGift;
	BYTE btPriceType;
	int aItemId;
	int Price;
	WORD wProductGroup[8];
	BYTE btProductCount;
};

struct PRODUCT_INFO
{
	WORD wProductGuid;
	BYTE btDur;
	BYTE btItemType;
	int aItemId;
	int Price;
	int Duration;

#if (ZT700==1)
	BYTE btLevel;
	BYTE btOption1;
	BYTE btOption2;
	BYTE btOption3;
	BYTE btExcOp;
	BYTE btAncOp;
#endif
};

PACKAGE_INFO* SearchShopPackage(int CategoryID,int Guid);
PRODUCT_INFO* SearchShopProduct(int groupID,int Guid);
void ShopUserAddToStorage(char* szCharName,int memb_guid,int productGroup,PRODUCT_INFO* p);
void ShopUserAddToGift(char* szCharName,int memb_guid,int productGroup,PRODUCT_INFO* p,char* szFrom,char* szText);
void UpdateUserCashPoints(int memb_guid,int wCoin_c,int wCoin_p,int wCoin_g);


#endif