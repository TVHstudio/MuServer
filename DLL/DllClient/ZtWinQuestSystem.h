#pragma once
// ----------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "Protocol.h"

#if(CUSTOM_ZT_QUEST_SYSTEM==TRUE)
// ----------------------------------------------------------------------------------------------

#define EW_MAX_ACT			3
#define EW_MAX_MISSION		5
#define EW_MAX_REWARD		3
#define EW_MAX_QUEST		1000
// ----------------------------------------------------------------------------------------------

enum ZtWinMission
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

struct CG_Accept_Done
{
	PBMSG_HEAD2 h;
	BYTE Result;
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

struct GC_ZtWinMiniInfoZt
{
	PBMSG_HEAD2 h;
	BYTE a;
	BYTE m;
};
// ----------------------------------------------------------------------------------------------

struct GC_ZtWinStart
{
	PBMSG_HEAD2 h;
	BYTE Act;
	BYTE Start;
};
// ----------------------------------------------------------------------------------------------

struct ZtWinQuest_DATA
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
	BYTE MissionLuck[EW_MAX_MISSION];
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

class ZtWinQuestSystem
{
public:
		 ZtWinQuestSystem();
		 ~ZtWinQuestSystem();
	void Init();
	void Load();
	void ImageLoad();
	void BindImages();
	void Draw();
	void DrawMiniInfo();
	void Button(DWORD Event);
	void GC_RecvMain(GC_MainPacket* aRecv);
	void CG_Ac�eptQuest();
	void GC_MiniInfoRecv(GC_ZtWinMiniInfo* aRecv);
	void GC_MiniInfoRecvZt(GC_ZtWinMiniInfoZt* aRecv);
	void GC_Start(GC_ZtWinStart* aRecv);

	int OpenTab;

	ZtWinQuest_DATA ewdata[EW_MAX_ACT];
};
extern ZtWinQuestSystem g_ZtWinQuestSystem;
// ----------------------------------------------------------------------------------------------
#endif