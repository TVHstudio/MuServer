#pragma once

#include "StdAfx.h"
#include "protocol.h"
#include "ZtLicenseProtocolDefine.h"

//#define ZTLICENSE_SERVER		1

// ----------------------------------------------------------------------------------------------

#define TOTAL_CLIENT		200
#define ZTNEW_VERISON		"New Update:"
#define DISK_DIR			"`?T"										//"c:\\"

// ----------------------------------------------------------------------------------------------
/*
Premium Type Interface - 60
Button Reset Rage system - 30
Monster Balans system - 20
*/
#define LICENSE_UKRAINE	1

#if(LICENSE_UKRAINE)

#define CUSTOM_ITEM_MOVE		1

#endif

enum eZtUB
{
	Local,
	drynea,
	t34,
	ztgames,
	Gints,
	SaneaMD,
	MarksSevcuks,
	SILVER1,
	SILVER2,
	Vadim,
	DavitRazmadze,	
	lemiks,
	spoke,
	Daboy_1,
	Daboy_2,
	Encode,
	Pavel,
	PrideMu,
	Cherkashin,
	Semushkin,
	Gints_2,
	zerocool,
	Vadim_2,
	ulasevich,	// - твоя лицензия
	Local2,
	DavitRazmadze2,
	PrideMuLocal,
	lexbzk, 
	Local3,
	DavitRazmadze3,
	snaker,
	testuser,
	Gredy,
	GredyLocal,
	Gredy2,
	Pavel2,
	ulasevich2,// - твоя лицензия
	feqan,
	Selfmylife,
	NoCustom,
	ConflictNoCustom,
	Emanuel,
	maksim844495,
	SILVER_Local,
	Matias,
	MMProduction,
	absolute,
	DICE,
	Artem,
	Artem2,
	MedoniAndrei,
	SirJ,
	Eduardo,
	bassreflexive,
	MU2Play,
	Stone,
	Sentinel,
	Almdar,
	thinnakorn,
	EpicMU,
	masonX,
	MatiasLeiva,
	AlterMU,
	Almdar2,
	Escalate,
	RafaelLorenzet,
	TGBA_LLC,
	RevoMU,
	DrXAOS,
	masonX2,
	GloryMU,
	MuRelic,
	ArcMu,
	muheroia,
	HomeLan,
	ProtectDebug,
	UpdateDebug,
	MegaM,
	mu4you,
	eternalmu,
	WarBorn,
	NSGames,
	FinalMU,
	MUDev,
	FoxMU,
	// ----
	MUCustom,
	Chebuk,
	Jancis,
	Atomic,
	jammal,
	MuPrime,
	Berlin,
	Thinnakorn,
	InfinityMU,
	MuInsane,
	Jeancarlos,
	NoriaMU,
	FlameMu,
	AsteraMU,
	MU_GE,
	SaksonPavel,

	
};

struct LICENSE_DATA
{
	char Login[25];
	char Password[10];
	unsigned long hwid;
	char mac[18];
	char ip[16];
	unsigned int Credit;
	bool Baned;
	bool Rage;
	bool WinQuest;
	bool BloodHound;
	bool MonsterQuest;
	bool TvTEvent;	
	bool GrandHero;
	bool PartySystem;
	bool Brotherhood;
	bool PartySearch;
	bool ChatLog;
	bool GM_Manager;
	bool PerosnalStoreZt;
	bool PandoraEvent;
	bool AntiCheatPlus;
	bool SpotReturn;
    bool ComboCustom;
	bool NpcBuffer;
	bool BMQuest;
	bool LoraBattle;
	bool Smithy;
	bool Monster;
	bool ItemSmokeEffect;
	bool GrandDinamicExp;
	bool PartySave;
	bool DisableMasterTree;
	bool OfflineMode;
	bool Marriage;
	bool MonsterAttackLife;
	bool bRankItem;
	bool RestoreOffMode;
	bool MapQuest;
	bool bTeamVsTeam2;
	bool bAchievements;
	bool PremiumZt;
	bool AccSecurity;
	bool CraftQuestSystem;
	bool PickUpItemInfo;
	bool ReferralSystem;
	//--
	bool FixVieweMonster;
	bool CustomMapTeleport;
	bool CustomCameraMove;
	bool CustomMiniMapZt;
	LICENSE_DATA()
	{
		ZeroMemory(this->Login, sizeof(this->Login));
		ZeroMemory(this->Password, sizeof(this->Password));
		ZeroMemory(this->mac, sizeof(this->mac));
		ZeroMemory(this->ip, sizeof(this->ip));
		this->hwid					= 0;
		this->Credit				= 0;
		this->Baned					= false;
		this->Rage					= false;
		this->WinQuest				= false;
		this->BloodHound			= false;
		this->MonsterQuest			= false;
		this->TvTEvent				= false;
		this->GrandHero				= false;
		this->PartySystem			= false;
		this->Brotherhood			= false;
		this->PartySearch			= false;
		this->ChatLog				= false;
		this->GM_Manager			= false;
		this->PerosnalStoreZt		= false;
		this->PandoraEvent			= false;
		this->AntiCheatPlus			= false;
		this->ComboCustom			= false;
		this->NpcBuffer				= false;
		this->BMQuest				= false;
		this->LoraBattle			= false;
		this->Smithy				= false;
		this->Monster				= false;
		this->ItemSmokeEffect		= false;
		this->GrandDinamicExp       = false;
		this->PartySave				= false;
		this->DisableMasterTree		= false;
		this->OfflineMode			= false;
		this->Marriage				= false;
		this->MonsterAttackLife		= false;
		this->bRankItem				= false;
		this->RestoreOffMode		= false;
		this->MapQuest				= false;
		this->bTeamVsTeam2			= false;
		this->bAchievements			= false;
		this->PremiumZt				= false;
		this->AccSecurity			= false;
		this->CraftQuestSystem		= false;
		this->PickUpItemInfo		= false;
		this->ReferralSystem		= false;
		// --
		this->FixVieweMonster		= false;
		this->CustomMapTeleport		= false;
		this->CustomCameraMove		= false;
		this->CustomMiniMapZt		= false;
	}
};

struct CUSTOM_CONFIG
{
	unsigned char MaxPartyUser;
	bool PersonalEnable;
	char PersonalBonus;
	bool Gens;
	char PersonalCredit;
	CUSTOM_CONFIG()
	{
		this->MaxPartyUser = 5;
		this->PersonalEnable = false;
		this->PersonalBonus = false;
		this->Gens = false;
		this->PersonalCredit = false;
	}
};

struct PMSG_LICENSE_DATA
{
	PBMSG_HEAD2 h;
	int LicenseUser;	
	int LicenseCustom;
	LICENSE_DATA base;
	CUSTOM_CONFIG config;
};
// ----------------------------------------------------------------------------------------------

class CZtLicense
{
public:
		  CZtLicense();
		 ~CZtLicense();

	void Init();
	void Load();
//#if(!ZTLICENSE_SERVER)
	void AddList();
	void CheckLicense();
//#endif
	void GCLicenseUser(int aIndex);
	void GDLicenseUser();
	bool CheckUser(int NeedUser);
	char* GetDecText(char* EncodeChar);
	void SelectLicense(int UserID);

	bool m_WaitLicense;

	bool m_Enable;
	int ActiveUser;
	bool Exit;
	int	 ExitTime;
	bool NewVersion;
	bool DrawVersion;
	char VersionNum[50];
	char VersionDate[50];
	unsigned char TextXoR[3];
	
	LICENSE_DATA user;
//#if(!ZTLICENSE_SERVER)
	LICENSE_DATA List[TOTAL_CLIENT];
//#endif

	char* GetLicenseName();

	void CustomManager();

	void SetCustom(int ListID);
	int GetCustom();

	int m_MultiWarehouseType;

	int m_SetCustom;

	bool CheckTime(int UserID, int Year, int Month, int Day);
};

extern CZtLicense g_ZtLicense;