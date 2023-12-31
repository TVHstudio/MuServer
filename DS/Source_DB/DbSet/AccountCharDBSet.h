// AccountCharDBSet.h: interface for the CAccountCharDBSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACCOUNTCHARDBSET_H__01C748D6_E836_4267_AF43_66BD9D34C7DC__INCLUDED_)
#define AFX_ACCOUNTCHARDBSET_H__01C748D6_E836_4267_AF43_66BD9D34C7DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\\Sprodef.h"
#include "..\\protocol.h"

typedef struct
{
	int DBNumber;
	char AccountId[MAX_IDSTRING+1];
	char GameID1[MAX_IDSTRING+1];
	char GameID2[MAX_IDSTRING+1];
	char GameID3[MAX_IDSTRING+1];
	char GameID4[MAX_IDSTRING+1];
	char GameID5[MAX_IDSTRING+1];
	BYTE CtlCode;
	BYTE MoveCnt;
#if(S6E3)
	BYTE ExpandedWarehouse;
#endif
}AccountCharacterInfo, *LPAccountCharacterInfo;

struct SDHP_ANS_SETACCOUNTINFO
{
	PBMSG_HEAD h;
	char AccountId[MAX_IDSTRING+1];
	short Number;
	BYTE Result;
};

struct SDHP_ANS_SET_EXTENDEDINVEN_COUNT
{
	PBMSG_HEAD h;
	WORD Number;
	BYTE Result;
	BYTE ExtendedInvenCount;
	DWORD EventIndex;
	int ItemPos;
	BYTE BuyAtInGameShop;
	BYTE IsReplace;
};

struct SDHP_ANS_SET_EXTENDEDWAREHOUSE_COUNT
{
	PBMSG_HEAD h;
	WORD Number;
	BYTE Result;
	BYTE ExtendedWarehouseCount;
	DWORD EventIndex;
	int ItemPos;
	BYTE BuyAtInGameShop;
	BYTE IsReplace;
};

#pragma pack(push, 1)
typedef struct
{
	PBMSG_HEAD2 h;
	int aIndex;
	char chAccountID[11];
	BYTE VaultID;

}PMSG_VAULT_INFO ,	*LPMSG_VAULT_INFO;
#pragma pack(pop)

// ----------------------------------------------------------------
struct PMSG_VAULT_RESULT
{
	PBMSG_HEAD2 h;
	int aIndex;
	BYTE Result;
};


class CAccountCharDBSet  
{
public:
	CAccountCharDBSet();
	virtual ~CAccountCharDBSet();

	BOOL Connect();
	BOOL CreateAccountCharacter(char* id);
	#if(ENABLE_MULTI_CHAR)
	BOOL CreateAccountCharacter_Multi(char* id, int Page);
	#endif
	BOOL SaveAccountCharacter(char* id, int pos, char* GameID);
	#if(ENABLE_MULTI_CHAR)
	BOOL SaveAccountCharacter_Multi(char* id, int pos, char* GameID, int Page);
	#endif
	BOOL SaveAccountCharacter(char* id, char* GameID1, char* GameID2, char* GameID3, char* GameID4, char* GameID5);
	int DeleteAccountCharacter(char* id, char* gameid);
	#if(ENABLE_MULTI_CHAR)
	int DeleteAccountCharacter_Multi(char* id, char* gameid, int Page);
	#endif
	BOOL GetAccountId(char* Id);
	#if(ENABLE_MULTI_CHAR)
	BOOL GetAccountId_Multi(char* Id, int Page);
	#endif
	BOOL GetAccountInfo(char* Id, LPAccountCharacterInfo lpACInfo);
	#if(ENABLE_MULTI_CHAR)
	BOOL GetAccountInfo_Multi(char* Id, LPAccountCharacterInfo lpACInfo, int Page);
	#endif
	int GetAccountCharBlank(char* Id);
	#if(ENABLE_MULTI_CHAR)
	int GetAccountCharBlank_Multi(char* Id, int Page);
	#endif
	BOOL CurAccountCharacterSet(char* id, char* GameID);
	BYTE GetAccountCharCtlCode(char* Id);
	BOOL GetSummonerCardInfo(char* Id);
	BOOL SetSummonerCardInfo(char* Id);

	int WcoinSelect(char* Acc,int count,int type);
	bool LoadGameShopStorage(char * AccountID, GAMESHOP_GD_STORAGE * Storage);
	bool SaveGameShopStorageItem(char * AccountID, STORAGE Item);
	bool DelGameShopStorageItem(char * AccountID, STORAGE Item);

	BOOL SetCharacterExtendedInvenCountAdd(char* Name, BYTE btAddExtendedInvenCount);
	BOOL SetCharacterExtendedInvenCountReplace(char* Name, BYTE btReplaceExtendedInvenCount);
	BOOL GetCharacterExtendedInvenCount(char* Name, BYTE* btAddExtendedInvenCount);
	BOOL SetCharacterExtendedWarehouseCountAdd(char* Name, BYTE btAddExtendedWarehouseCount);
	BOOL SetCharacterExtendedWarehouseCountReplace(char* Name, BYTE btReplaceExtendedWarehouseCount);
	BOOL GetCharacterExtendedWarehouseCount(char* Name, BYTE* btAddExtendedWarehouseCount);

public:
	CQuery m_DBQuery;
};

#endif // !defined(AFX_ACCOUNTCHARDBSET_H__01C748D6_E836_4267_AF43_66BD9D34C7DC__INCLUDED_)
