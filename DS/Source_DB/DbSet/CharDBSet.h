// CharDBSet.h: interface for the CCharDBSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHARDBSET_H__BED5C4C4_EA0B_4126_A05F_9584C5F0E889__INCLUDED_)
#define AFX_CHARDBSET_H__BED5C4C4_EA0B_4126_A05F_9584C5F0E889__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\\Sprodef.h"
#include "..\\StdAfx.h"

typedef struct
{
	int registry;
	char AccountID[MAX_IDSTRING+1];
	char Name[MAX_IDSTRING+1];
	BYTE Class;
	int Level;
	int LevelUpPoint;
	int Experience;
	int NextExperience;
	int Money;
	short Strength;
	short Dexterity;
	short Vitality;
	short Energy;
	short Leadership;
	WORD ChatLitmitTime;
	float Life;
	float MaxLife;
	float Mana;
	float MaxMana;
	int PkCount;
	int PkLevel;
	int PkTime;
	BYTE dbInventory[MAX_DBINVENTORY];
	BYTE dbMagicList[MAX_DBMAGIC];
	BYTE dbQuest[MAX_QUEST];
	BYTE MapNumber;
	BYTE MapX;
	BYTE MapY;
	BYTE Dir;
	BYTE CtlCode;
	BYTE DbVersion;
	int FruitPoint;
	int PCPoint;
	int ZtFreePoints;
	int Reset;
	int GReset;
	int ZtQuestNum;
	int ZtQuestKill;
	int PremiumTime;
#ifdef CONFLICT_PREM_TYPE
	int PremiumTimeType;
#endif
	float ZtCred;
	DWORD BanChat;
	DWORD BanPost;
	DWORD BanChar;
	int ChaosBank;
	int BlessBank;
	int SoulBank;
	int LifeBank;
	DWORD MTDate;
	short AutoParty;
	int Zen;
	DWORD QTDate;
	char Brother[11];
#ifdef S6E3
	int ExpandedInventory;
#endif
#if(CUSTOM_SAVE_PT==1)
	DWORD PartyIndex;
#endif
	int DonateCredit;
	DWORD ATDate;


}CharacterInfo_Struct, *LPCharacterInfo_Struct;

struct PMSG_ANS_USERID
{
	PBMSG_HEAD2 head;
	DWORD dwKey;
	DWORD dwUserGUID;
	char chUserID[MAX_IDSTRING+1];
	BYTE btResult;
};

struct PMSG_REQ_USERID
{
	PBMSG_HEAD2 head;
	DWORD dwKey;
	DWORD dwUserGUID;
	char chUserName[MAX_IDSTRING+1];
};

struct SDHP_CHANGE_NAME_RESULT
{
	PBMSG_HEAD h;
	int aIndex;
	char AccountId[MAX_IDSTRING];
	char OldName[MAX_IDSTRING];
	char NewName[MAX_IDSTRING];
	BYTE btResult;
};



class CCharDBSet  
{
public:
	CCharDBSet();
	virtual ~CCharDBSet();

	BOOL Connect();
	int DeleteCharacter(char* AccoundID, char* CharacterID);
	int DeleteCharacter_DregInfo(char* CharacterID);
	int CreateCharacter(CString accountId, CString Name, BYTE Class);
	#if(ENABLE_MULTI_CHAR)
	int CreateCharacter_Multi(CString accountId, CString Name, BYTE Class, int Page);
	#endif
	BOOL DefaultCharacterCreate(BYTE classskin);
	BOOL DefaultCreateCharacterInsert(LPCharacterInfo_Struct lpObj);
	BOOL DefaultCreateCharacterAllDelete();
	BYTE SaveCharacter(char* Name, LPCharacterInfo_Struct lpObj);
	BOOL GetCharacter(char* szAccountID, char* Name, LPCharacterInfo_Struct lpObj);
	BOOL GetCharacter(char* name);
	BOOL SaveItem(char* Name, BYTE* ItemBuf);
	int CharServerMove(char* Name);
	void SetSP_WZ_CreateCharacterGetVersion(int version);
	BOOL CheckSP_WZ_CreateCharacterGetVersion();
	BYTE CurCharNameSave(char* Name);
	int ChangeName(char* AccountId, char* OldName, char* NewName);
	int GetCharacterID(char* chName, char* chUserID);
	DWORD GetCharacterClass(char* chName);

	void SaveMacroInfo(char* szAccountID, char* Name, BYTE* lpMacroInfo);
	BOOL LoadMacroInfo(char* szAccountID, char* Name, BYTE* lpMacroInfo);


public:
	int m_CreateCharacterVer;
	CQuery m_DBQuery;
	CQuery m_MEMBQuery;
};

#endif // !defined(AFX_CHARDBSET_H__BED5C4C4_EA0B_4126_A05F_9584C5F0E889__INCLUDED_)
