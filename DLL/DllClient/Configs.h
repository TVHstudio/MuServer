#pragma once

enum eINTERFACE_VERSION
{
	eINTERFACE_SEASON6	= 0,
	eINTERFACE_ZT700	= 1,
	eINTERFACE_SEASON3	= 2,
};

#define DIR_CONFIGS		"Data/ZtTeam/Common.ini"
#define GAMEINFO_DIR	"Data/ZtTeam/Game.ex"
#define CONNECT_IP_DIR	"Data/ZtTeam/Connect.ex"
#define ITEM_LOAD_DIR	"Data/ZtTeam/LoadItems.ini"
#define CONNECT_IP_DIR2	".\\Data\\ZtTeam\\Connect.ex"
#define GAMEBUFFER		"%d %d %d %d"

#define MAX_ITEM_LOAD	1000

extern bool gGENS;
extern bool gGRANDRESET;
extern bool gJEWELSBANK;
extern bool gRAGESYSTEM;
extern bool gWINQUEST;
extern bool gMONSTER_QUEST_SYSTEM;
extern bool gPARTY_SYSTEM;
extern DWORD gHelperLevel;
extern int iMonsterHPBar;
extern int iUserHpBar;
extern int iPartyHpBar;
extern bool bAntiHack;
extern bool gAutoLogin;
extern bool gFogEffect;
extern int g_MaxCharacter;
extern BYTE g_MaxPartyMember;

extern char gWindowTitle[50];
extern bool gMultiLang;
extern bool gFontEnable;
extern char gFontName[5][20];
extern int gFontSize[5];

extern bool gGlowEffect;
extern bool gCheckCloseWindow;
extern DWORD g_dwDivFireScreamSpeed;
extern bool gMiniMap;
extern bool gAutoMouseKey;
extern bool gMuHelperInventory;

extern bool gDamageTable;
extern bool gAdvanceStats;

extern int gInterfaceVersion;
extern int gInterfaceChat;
extern int gInterfaceBuffIcon;
extern int gInterfaceSelectServer;
extern int gInterfaceTime;
extern int gInterfaceTime;
extern int gInterfaceMUHelper;
extern int gInterfaceMasterSkill;

extern int gLoadVcorpDll;
extern int gLoadMUAutoClicker;

extern int gMultiWarehouse;
extern int gInfoLog;

extern int gMaxLevel;

struct LoadItem_DATA
{
	int Type;
	int Index;
	char BMD[50];
	char Dir1[50];
	char Dir2[50];
};

struct GlowItem_DATA
{
	int Type;
	int Index;
	float Red;
	float Green;
	float Blue;
};

class cConfig
{
public:
	void Configs();
	void Encode(char* buffer, int size);
	void SaveGame();
	void LoadGame();
	void ReedConnect();
	void ItemLoad();
	void Test();

	char MyIp[16];
	int  LauncherActive;
	char LauncherParameters[20];

	int CountItem;
	int CountGlow;
	LoadItem_DATA Item[MAX_ITEM_LOAD];
	GlowItem_DATA iGlow[MAX_ITEM_LOAD];


};

extern cConfig gConfig;

