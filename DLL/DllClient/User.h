#pragma once

#include "stdafx.h"
#include "Object.h"
#include "Protocol.h"
#include "NewParty.h"

#define MAX_TYPE_PLAYER			6

enum eClassNumber 
{
	CLASS_WIZARD	= 0,
	CLASS_KNIGHT	= 1,
	CLASS_ELF		= 2,
	CLASS_MAGUMSA	= 3,
	CLASS_DARKLORD	= 4,
	CLASS_SUMMONER	= 5,
	CLASS_MONK		= 6,
};
// ----------------------------------------------------------------------------------------------

struct ExViewePort
{
	PBMSG_HEAD2 h;
	short aIndex;
	int Life;
	int MaxLife;
	int SD;
	int MaxSD;
	int Level;
	int Reset;
	int GrandReset;
	int Defence;
	int Class;
	short AutoParty;
#ifdef PREM_TYPE
	int PremType;
#endif
	BYTE TvTTeam;
#ifdef VIEW_MONSTER
	char Name[20];
#endif
};

struct GC_RESET_CHAR_UPDATE
{
	PBMSG_HEAD2	h;
	WORD Level;
	DWORD Exp;
	DWORD MaxExp;
	WORD Str;
	WORD Agi;
	WORD Vit;
	WORD Ene;
	WORD Cmd;
	DWORD UpPoint;
	WORD Reset;
	WORD Grand;
};

struct DEFAULTCLASSTYPE
{
	WORD Strength;	// 4
	WORD Dexterity;	// 6
	WORD Vitality;	// 8
	WORD Energy;	// A
	WORD Leadership;	// 9CC
};

struct CHANGEWAREHOUSE
{
	PBMSG_HEAD2 h;
	int Number;
};

struct PMSG_OFFTRADE
{
	PBMSG_HEAD2 h;
	bool Active;
};

struct PARTY_MAP_DATA
{
	char Name[10];
	BYTE Map;
	BYTE X;
	BYTE Y;
};

struct PMSG_PARTY_MINIMAP
{
	PBMSG_HEAD2 h;
	int Count;
	PARTY_MAP_DATA Data[MAX_USER_IN_PARTY];
};

#if(ENABLR_DEN_DEV)
struct MINIMAP_SPOT_DATA
{
	BYTE X;
	BYTE Y;
};

struct MINIMAP_SPOT_SEND
{
	PWMSG_HEAD2 h;
	int Count;
	MINIMAP_SPOT_DATA Spot[300];
};

#endif

class User
{
public:
	void Load();
	void Refresh();
	static bool	IsMasterClass(BYTE Class);
	static bool IsBattleServer();
	bool IsMasterLevel();
	void UpdateCharInfo(CHAR_UPDATEINFO * aRecv);
	int GetClass();
	int GetActiveSkill();
	void ResetSystemGC_CharUpdate(GC_RESET_CHAR_UPDATE* Recv);
	bool GetCheckSkill(int skillnumber);
	bool InSafeZone();

	void SetCharacter(int Class, int Str, int Dex, int Vit, int Energy, int Leadership);
	void WarehouseReq(CHANGEWAREHOUSE * aRecv);
	
	void PartyMiniMapInfo(PMSG_PARTY_MINIMAP* aRecv);
	#if(ENABLR_DEN_DEV)
	void MiniMapSpotRecv(MINIMAP_SPOT_SEND* aRecv);
	#endif
	
	//lpCharObj	lpPlayer;

	int	m_MapNumber;
	int	m_CursorX;
	int	m_CursorY;
	int MagickAttack;
	int VieweTargetID;
	bool BattleCursor;
	WORD Reset;
	WORD GReset;
	int Premium;
	int ChaosBank;
	int BlessBank;
	int SoulBank;
	int LifeBank;
	int CreateonBank;
	int GuardianBank;
	int HarmonyBank;
	int LowStoneBank;
	int HighStoneBank;
	int GemStoneBank;
	float ZtCred;
	int Zen;
	int Class;
	int SUM;
	int RF;
	int WCoinC;
	int WCoinP;
	int WCoinG;
	DWORD Money;
	ExViewePort	ExViewe[MAX_VIEWPORT];
	DEFAULTCLASSTYPE DefClass[MAX_TYPE_PLAYER];

	int GuildNamber;

	bool m_MapQuestShow;
	int m_MapQuestCount;
	int m_MapQuestMaxCount;

	BYTE PremiumType;
	int	CursorX_Ex;
	int CursorY_Ex;
	int WarehouseNumber;
	int m_iDonateCredit;

	int m_PartyMapCount;
	PARTY_MAP_DATA m_PartyMapData[MAX_USER_IN_PARTY];
	#if(DEV_PLAYERINFO)
	bool m_TargetInfo;
	INFOPLAYER_DATA m_TargetData;
	#endif
	#if(DEV_DAMAGE_TABLE)
	bool m_SecondInfo;
	int m_SecondDamageMax;
	int m_SecondDamage;
	int m_SecondDefence;
	int m_SecondReflect;
	#endif
	int m_PCPoint;
	#if(DEV_GUILDBANK)
	bool m_bGuildBank;
	#endif
	#if(ENABLR_DEN_DEV)
	MINIMAP_SPOT_DATA m_MiniMapSpot[200];
	int	m_MiniMapSpotCount;
	#endif
};
extern User gObjUser;