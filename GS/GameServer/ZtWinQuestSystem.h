#pragma once
// ----------------------------------------------------------------------------------------------

#include "StdAfx.h"
#include "..\\include\\prodef.h"

#if(CUSTOM_ZT_QUEST_SYSTEM==TRUE)
// ----------------------------------------------------------------------------------------------

#define EW_DEBUG				0

#define EW_MAX_ACT				3
#define EW_MAX_MISSION			5
#define EW_MAX_REWARD			3
#define EW_MAX_QUEST			1000
#define EW_MAX_DROP				100

#define ZT_QUEST_SYSTEM_SIZE	39
#define EW_NEW_DROP				TRUE

// ----------------------------------------------------------------------------------------------

enum ZTWinMission
{
	Hunting   = 1,
	Droping   = 2,
	Searching = 3,
};
// ----------------------------------------------------------------------------------------------

enum ZtWinReward
{
	ewZen		= 1,
	ewFreePoint = 2,
	ewItem		= 3,
	ewBonus		= 4,
	ewBuff		= 5,
};
// ----------------------------------------------------------------------------------------------

struct WinQuest_Table
{
	char NameQuest[25];
	BYTE b_accept;
	BYTE b_done;
	BYTE b_End;
	// -> User
	BYTE Start;
	WORD Number;
	WORD Count[EW_MAX_MISSION];
	//-> Need
	BYTE b_Level;
	WORD NeedLevel;
	BYTE b_Reset;
	WORD NeedReset;
	BYTE b_Grand;
	WORD NeedGrand;
	//- >Mission
	BYTE b_Mission[EW_MAX_MISSION];
	BYTE MissionType[EW_MAX_MISSION];
	WORD MissionID[EW_MAX_MISSION];
	WORD MissionIndex[EW_MAX_MISSION];
	BYTE MissionLevel[EW_MAX_MISSION];
	BYTE MissionLuck[EW_MAX_MISSION];	//Luck|Map
	BYTE MissionOpt[EW_MAX_MISSION];
	BYTE MissionExl[EW_MAX_MISSION];	
	WORD MissionCount[EW_MAX_MISSION];
	BYTE MissionProcent[EW_MAX_MISSION];
	//-> Reward
	WORD RewardType[EW_MAX_REWARD];
	DWORD RewardCount[EW_MAX_REWARD];
	WORD RewardItemType[EW_MAX_REWARD];
	WORD RewardItemIndex[EW_MAX_REWARD];
	WORD RewardItemLevel[EW_MAX_REWARD];
};
// ----------------------------------------------------------------------------------------------
struct GC_MainPacket
{
	PWMSG_HEAD2 h;
	WinQuest_Table ztQuest[EW_MAX_ACT];
};
// ----------------------------------------------------------------------------------------------

struct WinQuest_Mission
{
	char NameQuest[25];
	BYTE Start;
	WORD ZtWQuestCount[EW_MAX_MISSION];
	BYTE MissionType[EW_MAX_MISSION];
	WORD MissionID[EW_MAX_MISSION];
	WORD MissionIndex[EW_MAX_MISSION];
	BYTE MissionLevel[EW_MAX_MISSION];
	BYTE MissionLuck[EW_MAX_MISSION];
	BYTE MissionOpt[EW_MAX_MISSION];
	BYTE MissionExl[EW_MAX_MISSION];
	WORD MissionCount[EW_MAX_MISSION];
};
// ----------------------------------------------------------------------------------------------

struct GC_ZtWinMiniInfo
{
	PWMSG_HEAD2 h;
	WinQuest_Mission ztQuest[EW_MAX_ACT];
};
// ----------------------------------------------------------------------------------------------

struct GC_ZtWinMiniInfoExt
{
	PBMSG_HEAD2 h;
	BYTE a;
	BYTE m;
};
// ----------------------------------------------------------------------------------------------

struct CG_Accept_Done
{
	PBMSG_HEAD2 h;
	BYTE Result;
};
// ----------------------------------------------------------------------------------------------

struct GC_ZtWinStart
{
	PBMSG_HEAD2 h;
	BYTE Act;
	BYTE Start;
};
// ----------------------------------------------------------------------------------------------

struct GC_ZtWinMiniInfoExItem
{
	PBMSG_HEAD2 h;
	BYTE a;
	BYTE m;
	BYTE c;
};
// ----------------------------------------------------------------------------------------------

struct ZtWinQuest_DATA
{
	char NameQuest[25];
	int NeedLevel;
	int NeedReset;
	int NeedGrand;
	int MissionType[EW_MAX_MISSION];
	int MissionID[EW_MAX_MISSION];
	int MissionIndex[EW_MAX_MISSION];
	int MissionLevel[EW_MAX_MISSION];
	int MissionLuck[EW_MAX_MISSION];
	int MissionOpt[EW_MAX_MISSION];
	int MissionExl[EW_MAX_MISSION];
	int MissionCount[EW_MAX_MISSION];
	int MissionProcent[EW_MAX_MISSION];
	int RewardType[EW_MAX_REWARD];
	int RewardCount[EW_MAX_REWARD];
	int RewardItemType[EW_MAX_REWARD];
	int RewardItemIndex[EW_MAX_REWARD];
	int RewardItemLevel[EW_MAX_REWARD];
};
// ----------------------------------------------------------------------------------------------

struct ZtWinDrop_DATA
{
	int iAct;
	int iNeedQuest;
	int ItemType;
	int ItemIndex;
	int ItemMinLevel;
	int ItemMaxLevel;
	int ItemMaxOption;
	int ItemLuck;
	int ItemSkill;
	int ItemExcellent;
	int ItemAncent;
	int ItemDur;
	int ItemDropRate;
	int MonsterMinLevel;
	int MonsterMaxLevel;
	int MonsterMap;
};
// ----------------------------------------------------------------------------------------------

class ZtWinQuestSystem
{
public:
		 ZtWinQuestSystem();
		 ~ZtWinQuestSystem();
	//-> Load
	void Init();
	void Load();
	void Read(char* File);
	void ReadQuest(int a, char* File);
	void ReadDrop(char* File);
	//-> Game Comunication
	bool Dialog(int aIndex, int aNpcIndex);
	void GC_MainInfo(int aIndex);
	void GC_OpenWindow(int aIndex);
	void GC_MiniInfo(int aIndex);
	void GC_MiniInfoZt(int aIndex, int a, int m);
	void CG_AcceptQuest(int aIndex, CG_Accept_Done* aRecv);
	void GC_Start(int aIndex, int a, int s);
	//Mission
	bool MonsterKiller(int aIndexMonster, int aIndexUser);
	int PickUpItem(int aIndex, int ItemType);
	bool SearchItem(int aIndex, int a, int m);
	void DeleteItem(int aIndex, int a, int m);
	bool CheckMission(int aIndex, int a);
	void UserConnect(int aIndex);
	void RewardQuest(int aIndex, int Act);
	bool NewDrop(int aIndexMob, int aIndexUser);
	//DataServer
	void SaveQuest(int aIndex, LPBYTE buf);
	void LoadQuest(int aIndex, LPBYTE buf);

	bool Enable;
	int NPC_Class;
	int NPC_Map;
	int NPC_X;
	int NPC_Y;

	ZtWinQuest_DATA ewdata[EW_MAX_ACT][EW_MAX_QUEST];
	ZtWinDrop_DATA m_Drop[EW_MAX_DROP];

	int iLoaded[EW_MAX_ACT];
	int iDropLoaded;
};
extern ZtWinQuestSystem g_ZtWinQuestSystem;
// ----------------------------------------------------------------------------------------------
#endif