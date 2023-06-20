#include "StdAfx.h"
#include "ZtLicense.h"
#include "VMProtectSDK.h"
#include "wininet.h"
#include "logproc.h"
#include "DSProtocol.h"
#include "DBSockMng.h"
#include "GameMain.h"
#include "PersonalShopZt.h"
#include "ZtLicenseClient.h"
#include "UserConfig.h"

CZtLicense g_ZtLicense;

CZtLicense::CZtLicense()
{
	VMBEGIN
	this->Init();
	VMEND
}

CZtLicense::~CZtLicense()
{
}

void CZtLicense::Init()
{
	VMBEGIN
	this->m_Enable = true;
	this->ActiveUser = -1;
	this->Exit = false;
	this->ExitTime = 0;
	this->NewVersion = false;
	this->DrawVersion = false;
	this->m_WaitLicense = false;
	ZeroMemory(this->VersionNum,sizeof(this->VersionNum));
	ZeroMemory(this->VersionDate,sizeof(this->VersionDate));
	this->TextXoR[0] = 0x03;
	this->TextXoR[1] = 0x05;
	this->TextXoR[2] = 0x08;
	#if(CUSTOM_VALUE_MENU)
	this->m_MultiWarehouseType = 0;
	#endif
	VMEND
	this->m_SetCustom = 0;
}

void CZtLicense::Load()
{
	VMBEGIN
	this->Init();

	if(!this->m_Enable)
	{
		return;
	}

#if(ZTLICENSE_SERVER)
	g_ZtLicenseClient.Start();

	int i = 0;

	while(!g_ZtLicense.m_WaitLicense)
	{
		if(i == 10)
		{
			ExitProcess(0);
		}
		i++;
		Sleep(1000);
	}
#else

	this->AddList();

	this->CheckLicense();

	this->CustomManager();

	this->SetCustom(0);
	
#endif
	

	VMEND
}

#if(!ZTLICENSE_SERVER)
void CZtLicense::AddList()
{
	if(!this->m_Enable)
	{
		return;
	}

	for(int i = 0; i < TOTAL_CLIENT; i++)
	{
		ZeroMemory(this->List[i].Login, sizeof(this->List[i].Login));
		ZeroMemory(this->List[i].Password, sizeof(this->List[i].Password));
		this->List[i].hwid				= 0;
		this->List[i].mac[0]		= NULL;
		this->List[i].Credit				= 0;
		this->List[i].Baned					= false;
		this->List[i].Rage					= false;
		this->List[i].WinQuest				= false;
		this->List[i].BloodHound			= false;
		this->List[i].MonsterQuest			= false;
		this->List[i].TvTEvent				= false;
		this->List[i].GrandHero				= false;
		this->List[i].PartySystem			= false;
		this->List[i].Brotherhood			= false;
		this->List[i].PartySearch			= false;
		this->List[i].ChatLog				= false;
		this->List[i].GM_Manager			= false;
		this->List[i].PerosnalStoreZt		= false;
		this->List[i].PandoraEvent			= false;
		this->List[i].AntiCheatPlus			= false;
		this->List[i].ComboCustom			= false;
		this->List[i].NpcBuffer				= false;
		this->List[i].BMQuest				= false;
		this->List[i].LoraBattle			= false;
		this->List[i].Smithy				= false;
		this->List[i].Monster				= false;
		this->List[i].ItemSmokeEffect		= false;
		this->List[i].GrandDinamicExp       = false;
		this->List[i].PartySave				= false;
		this->List[i].DisableMasterTree		= false;
		this->List[i].OfflineMode			= false;
		this->List[i].Marriage				= false;
		this->List[i].bRankItem				= false;
		this->List[i].RestoreOffMode		= false;
		this->List[i].MapQuest				= false;
		this->List[i].bTeamVsTeam2          = false;
		this->List[i].bAchievements			= false;
		this->List[i].PremiumZt				= false;
		this->List[i].AccSecurity			= false;
		this->List[i].CraftQuestSystem		= false;
		this->List[i].PickUpItemInfo		= false;
		this->List[i].ReferralSystem		= false;
	}

	//strcpy(this->List[eZtUB::Local].Login,			"Local");
	//this->List[eZtUB::Local].hwid					= 1456940273;	// 1456940273;
	//strcpy(this->List[eZtUB::Local].mac,			"60-A4-4C-2B-45-03");
	//this->List[eZtUB::Local].Rage					= true;
	//this->List[eZtUB::Local].BloodHound				= true;
	//this->List[eZtUB::Local].MonsterQuest			= true;
	//this->List[eZtUB::Local].TvTEvent				= true;
	//this->List[eZtUB::Local].GrandHero				= true;
	//this->List[eZtUB::Local].PartySystem			= true;
	//this->List[eZtUB::Local].Brotherhood			= true;
	//this->List[eZtUB::Local].PartySearch			= true;
	//this->List[eZtUB::Local].ChatLog				= true;
	//this->List[eZtUB::Local].GM_Manager				= true;
	//this->List[eZtUB::Local].PerosnalStoreZt		= true;
	//this->List[eZtUB::Local].PandoraEvent			= true;
	//this->List[eZtUB::Local].AntiCheatPlus			= true;
	//this->List[eZtUB::Local].ComboCustom			= true;
	//this->List[eZtUB::Local].NpcBuffer				= true;
	//this->List[eZtUB::Local].BMQuest				= true;
	//this->List[eZtUB::Local].LoraBattle				= true;
	//this->List[eZtUB::Local].Smithy					= true;
	//this->List[eZtUB::Local].Monster				= true;
	//this->List[eZtUB::Local].ItemSmokeEffect		= true;
	//this->List[eZtUB::Local].GrandDinamicExp		= true;
	//this->List[eZtUB::Local].OfflineMode			= true;
	//this->List[eZtUB::Local].PartySave				= true;
	//this->List[eZtUB::Local].Marriage				= true;
	//this->List[eZtUB::Local].RestoreOffMode			= true;
	//this->List[eZtUB::Local].bTeamVsTeam2			= true;
	//this->List[eZtUB::Local].bAchievements			= true;
	//this->List[eZtUB::Local].PremiumZt				= true;
	//this->List[eZtUB::Local].AccSecurity			= true;
	// ----
	strcpy(this->List[eZtUB::drynea].Login,			"drynea");
	this->List[eZtUB::drynea].hwid				= 1922075450;
	this->List[eZtUB::drynea].Rage					= true;
	this->List[eZtUB::drynea].TvTEvent				= true;
	this->List[eZtUB::drynea].Monster				= true;
	this->List[eZtUB::drynea].ItemSmokeEffect		= true;
	// ----
	strcpy(this->List[eZtUB::t34].Login,			"t34");
	this->List[eZtUB::t34].hwid					= 1352569343;
	// ----
	strcpy(this->List[eZtUB::ztgames].Login,		"ztgames");
	this->List[eZtUB::ztgames].hwid				= 183346987;
	this->List[eZtUB::ztgames].Rage					= true;
	// ----
	strcpy(this->List[eZtUB::Gints].Login,			"Gints");
	this->List[eZtUB::Gints].hwid					= 524162253;//524162253;
	this->List[eZtUB::Gints].Rage					= true;
	this->List[eZtUB::Gints].PartySystem			= true;
	this->List[eZtUB::Gints].MonsterQuest			= true;
	this->List[eZtUB::Gints].AntiCheatPlus			= true;
	this->List[eZtUB::Gints].ComboCustom			= true;
	this->List[eZtUB::Gints].Brotherhood			= true;
	this->List[eZtUB::Gints].NpcBuffer				= true;
	this->List[eZtUB::Gints].Monster				= true;
	this->List[eZtUB::Gints].ItemSmokeEffect		= true;
	// ----
	strcpy(this->List[eZtUB::SaneaMD].Login,		"SaneaMD");
	this->List[eZtUB::SaneaMD].hwid				= 807882591;//3859230483;
	this->List[eZtUB::SaneaMD].Rage					= true;
	// ----
	strcpy(this->List[eZtUB::MarksSevcuks].Login,	"MarksSevcuks");
	this->List[eZtUB::MarksSevcuks].hwid			= 3760116472;
	// ----
	strcpy(this->List[eZtUB::SILVER1].Login,		"SILVER1");
	this->List[eZtUB::SILVER1].hwid					= 146198119; // 3237505581;	146198119|00-0C-29-10-D9-81
	strcpy(this->List[eZtUB::SILVER1].mac,			"00-0C-29-10-D9-81");
	this->List[eZtUB::SILVER1].Rage					= true;
	this->List[eZtUB::SILVER1].TvTEvent				= true;
	this->List[eZtUB::SILVER1].Brotherhood			= true;
	this->List[eZtUB::SILVER1].PartySearch			= true;
	this->List[eZtUB::SILVER1].PartySystem			= true;
	this->List[eZtUB::SILVER1].ChatLog				= true;
	this->List[eZtUB::SILVER1].GM_Manager			= true;
	this->List[eZtUB::SILVER1].PerosnalStoreZt		= true;
	this->List[eZtUB::SILVER1].PartySave			= true;
	this->List[eZtUB::SILVER1].Smithy				= true;
	this->List[eZtUB::SILVER1].OfflineMode			= true;
	this->List[eZtUB::SILVER1].bRankItem			= true;
	this->List[eZtUB::SILVER1].bAchievements		= true;
	this->List[eZtUB::SILVER1].bTeamVsTeam2			= true;
	this->List[eZtUB::SILVER1].GrandDinamicExp		= true;
	this->List[eZtUB::SILVER1].RestoreOffMode		= true;
	this->List[eZtUB::SILVER1].PremiumZt			= true;
	// ----
	strcpy(this->List[eZtUB::SILVER2].Login,		"SILVER2");
	//this->List[eZtUB::SILVER2].hwid					= 2502590384;	
	this->List[eZtUB::SILVER2].hwid					= 15006453;	
	strcpy(this->List[eZtUB::SILVER2].mac,		"00-0C-29-58-01-0E");
	this->List[eZtUB::SILVER2].Rage					= true;
	this->List[eZtUB::SILVER2].TvTEvent				= true;
	this->List[eZtUB::SILVER2].Brotherhood			= true;
	this->List[eZtUB::SILVER2].PartySearch			= true;
	this->List[eZtUB::SILVER2].PartySystem			= true;
	this->List[eZtUB::SILVER2].ChatLog				= true;
	this->List[eZtUB::SILVER2].GM_Manager			= true;
	this->List[eZtUB::SILVER2].PerosnalStoreZt		= true;
	this->List[eZtUB::SILVER2].PartySave			= true;
	this->List[eZtUB::SILVER2].Smithy				= true;
	this->List[eZtUB::SILVER2].OfflineMode			= true;
	this->List[eZtUB::SILVER2].bRankItem			= true;
	this->List[eZtUB::SILVER2].bAchievements		= true;
	this->List[eZtUB::SILVER2].bTeamVsTeam2			= true;
	this->List[eZtUB::SILVER2].GrandDinamicExp		= true;
	this->List[eZtUB::SILVER2].RestoreOffMode		= true;
	this->List[eZtUB::SILVER2].PremiumZt			= true;
	// ----
	strcpy(this->List[eZtUB::Vadim].Login,			"Vadim");
	this->List[eZtUB::Vadim].hwid					= 99415930;
	this->List[eZtUB::Vadim].Rage					= true;
	// ----
	strcpy(this->List[eZtUB::DavitRazmadze].Login, "DavitRazmadze");
	this->List[eZtUB::DavitRazmadze].hwid			= 1080008721;//2494879713;
	strcpy(this->List[eZtUB::thinnakorn].mac,		"84-60-09-A6-10-19");
	this->List[eZtUB::DavitRazmadze].ItemSmokeEffect		= true;
	this->List[eZtUB::DavitRazmadze].Monster		= true;
	this->List[eZtUB::DavitRazmadze].AntiCheatPlus		= true;
	this->List[eZtUB::DavitRazmadze].TvTEvent		= true;
	this->List[eZtUB::DavitRazmadze].bAchievements		= true;
	// ----
	strcpy(this->List[eZtUB::lemiks].Login,			"lemiks");
	this->List[eZtUB::lemiks].hwid				= 3029767103;
	this->List[eZtUB::lemiks].GrandHero				= true;
	this->List[eZtUB::lemiks].Brotherhood			= true;
	this->List[eZtUB::lemiks].Monster				= true;
	this->List[eZtUB::lemiks].ItemSmokeEffect		= true;
	this->List[eZtUB::lemiks].MonsterAttackLife		= true;
	this->List[eZtUB::lemiks].GrandDinamicExp		= true;
	// ----
	strcpy(this->List[eZtUB::spoke].Login,			"spoke");
	this->List[eZtUB::spoke].hwid					= 2461314075;
	this->List[eZtUB::spoke].Monster				= true;
	// ----
	strcpy(this->List[eZtUB::Daboy_1].Login,		"Daboy_1");
	this->List[eZtUB::Daboy_1].hwid				= 1081550485;
	// ----
	strcpy(this->List[eZtUB::Daboy_2].Login,		"Daboy_2");
	this->List[eZtUB::Daboy_2].hwid				= 3102437392;
	// ----
	strcpy(this->List[eZtUB::Encode].Login,			"Encode");
	this->List[eZtUB::Encode].hwid				= 2664824880;
	// ----
	strcpy(this->List[eZtUB::Pavel].Login,			"Pavel");
	this->List[eZtUB::Pavel].hwid					= 1745027016;
	// ----
	strcpy(this->List[eZtUB::PrideMu].Login,		"PrideMu");
	this->List[eZtUB::PrideMu].hwid				= 1;	//136373629
	//List[eZtUB::PrideMu].Rage						= true;
	//List[eZtUB::PrideMu].MonsterQuest				= true;
	//List[eZtUB::PrideMu].TvTEvent					= true;
	//List[eZtUB::PrideMu].GrandHero				= true;
	this->List[eZtUB::PrideMu].Monster				= true;
	this->List[eZtUB::PrideMu].ItemSmokeEffect		= true;
	// ----
	strcpy(this->List[eZtUB::Cherkashin].Login,		"Cherkashin");
	this->List[eZtUB::Cherkashin].hwid			= 3422826830;
	this->List[eZtUB::Cherkashin].Monster			= true;
	// ----
	strcpy(this->List[eZtUB::Semushkin].Login,		"Semushkin");
	this->List[eZtUB::Semushkin].hwid				= 2149325968;
	// ----
	strcpy(this->List[eZtUB::Gints_2].Login,		"Gints_2");
	this->List[eZtUB::Gints_2].hwid				= 2556587903;
	this->List[eZtUB::Gints_2].Rage					= true;
	this->List[eZtUB::Gints_2].GrandHero			= true;
	this->List[eZtUB::Gints_2].PartySystem			= true;
	this->List[eZtUB::Gints_2].MonsterQuest			= true;
	this->List[eZtUB::Gints_2].AntiCheatPlus		= true;
	this->List[eZtUB::Gints_2].ComboCustom			= true;
	this->List[eZtUB::Gints_2].Brotherhood			= true;
	this->List[eZtUB::Gints_2].NpcBuffer			= true;
	this->List[eZtUB::Gints_2].Monster				= true;
	this->List[eZtUB::Gints_2].ItemSmokeEffect		= true;
	// ----
	strcpy(this->List[eZtUB::zerocool].Login,		"zerocool");
	this->List[eZtUB::zerocool].hwid				= 3358746164;
	// ----
	strcpy(this->List[eZtUB::Vadim_2].Login,		"Vadim_2");
	this->List[eZtUB::Vadim_2].hwid				= 1684392689;
	// ----
	strcpy(this->List[eZtUB::ulasevich].Login,		"ulasevich");	// твои модули
	this->List[eZtUB::ulasevich].hwid				= 471417973;// 3632441894;
	strcpy(this->List[eZtUB::Artem].mac,			"00-25-22-C2-E0-AF");
	this->List[eZtUB::ulasevich].BloodHound			= true;
	this->List[eZtUB::ulasevich].Rage				= true;
	this->List[eZtUB::ulasevich].MonsterQuest		= true;
	this->List[eZtUB::ulasevich].Brotherhood		= true;
	this->List[eZtUB::ulasevich].AntiCheatPlus		= true;
	this->List[eZtUB::ulasevich].BMQuest			= true;
	this->List[eZtUB::ulasevich].PandoraEvent		= true;
	this->List[eZtUB::ulasevich].bRankItem			= true;
	this->List[eZtUB::ulasevich].PremiumZt			= true;
	this->List[eZtUB::ulasevich].Smithy				= true;
	this->List[eZtUB::ulasevich].OfflineMode		= true;
	this->List[eZtUB::ulasevich].PerosnalStoreZt	= true;
	this->List[eZtUB::ulasevich].GM_Manager			= true;		//активировать менеджер гмов для твое?лицензии 
	this->List[eZtUB::ulasevich].RestoreOffMode		= true;
	this->List[eZtUB::ulasevich].DisableMasterTree	= true;
	this->List[eZtUB::ulasevich].bAchievements		= true;
	this->List[eZtUB::ulasevich].Monster			= true;
	//сеичас подключи?пето?чт?по сложне?
	//сначал?находи?са?ко?меропр?тия
	// ----
	strcpy(this->List[eZtUB::Local2].Login,			"Local2");
	this->List[eZtUB::Local2].hwid					= 3962621275;
	this->List[eZtUB::Local2].Rage					= true;
	this->List[eZtUB::Local2].BloodHound			= true;
	this->List[eZtUB::Local2].MonsterQuest			= true;
	this->List[eZtUB::Local2].TvTEvent				= true;
	this->List[eZtUB::Local2].GrandHero				= true;
	// ----
	strcpy(this->List[eZtUB::DavitRazmadze2].Login, "DavitRazmadze2");
	this->List[eZtUB::DavitRazmadze2].hwid		= 3496675938;
	this->List[eZtUB::DavitRazmadze2].ItemSmokeEffect		= true;
	this->List[eZtUB::DavitRazmadze2].Monster		= true;
	this->List[eZtUB::DavitRazmadze2].AntiCheatPlus		= true;
	this->List[eZtUB::DavitRazmadze2].TvTEvent		= true;
	this->List[eZtUB::DavitRazmadze2].bAchievements		= true;
	// ----
	strcpy(this->List[eZtUB::DavitRazmadze3].Login, "DavitRazmadze3");
	this->List[eZtUB::DavitRazmadze3].hwid		= 2361010737;
	this->List[eZtUB::DavitRazmadze3].ItemSmokeEffect		= true;
	this->List[eZtUB::DavitRazmadze3].Monster		= true;
	this->List[eZtUB::DavitRazmadze3].AntiCheatPlus		= true;
	this->List[eZtUB::DavitRazmadze3].TvTEvent		= true;
	this->List[eZtUB::DavitRazmadze3].bAchievements		= true;
	// ----
	strcpy(this->List[eZtUB::PrideMuLocal].Login,	"PrideMuLocal");
	this->List[eZtUB::PrideMuLocal].hwid			= 102821109;
	this->List[eZtUB::PrideMuLocal].Rage			= true;
	this->List[eZtUB::PrideMuLocal].MonsterQuest	= true;
	this->List[eZtUB::PrideMuLocal].TvTEvent		= true;
	this->List[eZtUB::PrideMuLocal].GrandHero		= true;
	this->List[eZtUB::PrideMuLocal].Monster			= true;
	this->List[eZtUB::PrideMuLocal].ItemSmokeEffect	= true;
	// ----
	strcpy(this->List[eZtUB::lexbzk].Login,			"lexbzk");
	this->List[eZtUB::lexbzk].hwid				= 308214326;
	// ----
	strcpy(this->List[eZtUB::Local3].Login,			"Local3");
	this->List[eZtUB::Local3].hwid				= 1518866620;
	this->List[eZtUB::Local3].Rage					= true;
	this->List[eZtUB::Local3].MonsterQuest			= true;
	this->List[eZtUB::Local3].TvTEvent				= true;
	this->List[eZtUB::Local3].GrandHero				= true;
	// ----
	//strcpy(this->List[eZtUB::DavitRazmadze3].Login, "DavitRazmadze3");
	//this->List[eZtUB::DavitRazmadze3].hwid		= 370104553;
	//this->List[eZtUB::DavitRazmadze3].Monster		= true;
	//this->List[eZtUB::DavitRazmadze3].AntiCheatPlus		= true;
	// ----
	strcpy(this->List[eZtUB::snaker].Login,			"snaker");
	this->List[eZtUB::snaker].hwid				= 4230177721;
	this->List[eZtUB::snaker].Rage					= true;
	this->List[eZtUB::snaker].MonsterQuest			= true;
	this->List[eZtUB::snaker].TvTEvent				= true;
	this->List[eZtUB::snaker].GrandHero				= true;
	this->List[eZtUB::snaker].Monster				= true;
	this->List[eZtUB::snaker].ItemSmokeEffect		= true;
	// ----
	strcpy(this->List[eZtUB::testuser].Login,		"testuser");
	this->List[eZtUB::testuser].hwid				= 3834831223;
	// ----
	strcpy(this->List[eZtUB::Gredy].Login,			"Gredy");
	this->List[eZtUB::Gredy].hwid					= 1009564418;	//1009564418
	this->List[eZtUB::Gredy].TvTEvent				= true;
	this->List[eZtUB::Gredy].PerosnalStoreZt		= true;
	this->List[eZtUB::Gredy].GM_Manager				= true;
	this->List[eZtUB::Gredy].AntiCheatPlus			= true;
	this->List[eZtUB::Gredy].SpotReturn				= true;
	this->List[eZtUB::Gredy].PandoraEvent			= true;
	this->List[eZtUB::Gredy].LoraBattle				= true;
	this->List[eZtUB::Gredy].Smithy					= true;
	this->List[eZtUB::Gredy].GrandDinamicExp		= true;
	//this->List[eZtUB::Gredy].DisableMasterTree		= true;
	this->List[eZtUB::Gredy].Rage					= true;
	this->List[eZtUB::Gredy].OfflineMode			= true;
	this->List[eZtUB::Gredy].Monster				= true;
	this->List[eZtUB::Gredy].Marriage				= true;
	this->List[eZtUB::Gredy].NpcBuffer				= true;
	this->List[eZtUB::Gredy].bRankItem				= true;
	this->List[eZtUB::Gredy].RestoreOffMode			= true;
	this->List[eZtUB::Gredy].PartySave				= true;
	this->List[eZtUB::Gredy].PartySearch			= true;
	this->List[eZtUB::Gredy].GrandHero				= true;
	this->List[eZtUB::Gredy].MonsterQuest			= true;
	this->List[eZtUB::Gredy].MapQuest				= true;
	this->List[eZtUB::Gredy].bAchievements			= true;
	this->List[eZtUB::Gredy].PremiumZt				= true;
	this->List[eZtUB::Gredy].PartySystem			= true;
	this->List[eZtUB::Gredy].bTeamVsTeam2			= true;
	this->List[eZtUB::Gredy].ItemSmokeEffect		= true;
	this->List[eZtUB::Gredy].AccSecurity			= true;
	this->List[eZtUB::Gredy].CraftQuestSystem		= true;
	// ----
	strcpy(this->List[eZtUB::GredyLocal].Login,		"GredyLocal");
	this->List[eZtUB::GredyLocal].hwid				= 443216415;
	this->List[eZtUB::GredyLocal].TvTEvent			= true;
	this->List[eZtUB::GredyLocal].PerosnalStoreZt	= true;
	this->List[eZtUB::GredyLocal].GM_Manager		= true;
	this->List[eZtUB::GredyLocal].AntiCheatPlus		= true;
	this->List[eZtUB::GredyLocal].SpotReturn		= true;
	this->List[eZtUB::GredyLocal].PandoraEvent		= true;
	this->List[eZtUB::GredyLocal].LoraBattle		= true;
	this->List[eZtUB::GredyLocal].Smithy			= true;
	this->List[eZtUB::GredyLocal].GrandDinamicExp	= true;
	//this->List[eZtUB::GredyLocal].DisableMasterTree	= true;
	this->List[eZtUB::GredyLocal].Rage				= true;
	this->List[eZtUB::GredyLocal].OfflineMode		= true;
	this->List[eZtUB::GredyLocal].Monster			= true;
	this->List[eZtUB::GredyLocal].Marriage			= true;
	this->List[eZtUB::GredyLocal].NpcBuffer			= true;
	this->List[eZtUB::GredyLocal].bRankItem			= true;
	this->List[eZtUB::GredyLocal].RestoreOffMode	= true;
	this->List[eZtUB::GredyLocal].PartySave			= true;
	this->List[eZtUB::GredyLocal].PartySearch		= true;
	this->List[eZtUB::GredyLocal].GrandHero			= true;
	this->List[eZtUB::GredyLocal].MonsterQuest		= true;
	this->List[eZtUB::GredyLocal].MapQuest			= true;
	this->List[eZtUB::GredyLocal].bAchievements		= true;
	this->List[eZtUB::GredyLocal].PremiumZt			= true;
	this->List[eZtUB::GredyLocal].PartySystem		= true;
	this->List[eZtUB::GredyLocal].bTeamVsTeam2		= true;
	this->List[eZtUB::GredyLocal].ItemSmokeEffect	= true;
	this->List[eZtUB::GredyLocal].AccSecurity		= true;
	this->List[eZtUB::GredyLocal].CraftQuestSystem	= true;
	// ----
	strcpy(this->List[eZtUB::Gredy2].Login,			"Gredy2");
	this->List[eZtUB::Gredy2].hwid					= 3761286172;	// 1309694294;
	this->List[eZtUB::Gredy2].TvTEvent				= true;
	this->List[eZtUB::Gredy2].PerosnalStoreZt		= true;
	this->List[eZtUB::Gredy2].GM_Manager			= true;
	this->List[eZtUB::Gredy2].AntiCheatPlus			= true;
	this->List[eZtUB::Gredy2].SpotReturn			= true;
	this->List[eZtUB::Gredy2].PandoraEvent			= true;
	this->List[eZtUB::Gredy2].LoraBattle			= true;
	this->List[eZtUB::Gredy2].Smithy				= true;
	this->List[eZtUB::Gredy2].GrandDinamicExp		= true;
	//this->List[eZtUB::Gredy2].DisableMasterTree		= true;
	this->List[eZtUB::Gredy2].Rage					= true;
	this->List[eZtUB::Gredy2].OfflineMode			= true;
	this->List[eZtUB::Gredy2].Monster				= true;
	this->List[eZtUB::Gredy2].Marriage				= true;
	this->List[eZtUB::Gredy2].NpcBuffer				= true;
	this->List[eZtUB::Gredy2].bRankItem				= true;
	this->List[eZtUB::Gredy2].RestoreOffMode		= true;
	this->List[eZtUB::Gredy2].PartySave				= true;
	this->List[eZtUB::Gredy2].PartySearch			= true;
	this->List[eZtUB::Gredy2].GrandHero				= true;
	this->List[eZtUB::Gredy2].MonsterQuest			= true;
	this->List[eZtUB::Gredy2].MapQuest				= true;
	this->List[eZtUB::Gredy2].bAchievements			= true;
	this->List[eZtUB::Gredy2].PremiumZt				= true;
	this->List[eZtUB::Gredy2].PartySystem			= true;
	this->List[eZtUB::Gredy2].bTeamVsTeam2			= true;
	this->List[eZtUB::Gredy2].ItemSmokeEffect		= true;
	this->List[eZtUB::Gredy2].AccSecurity			= true;
	this->List[eZtUB::Gredy2].CraftQuestSystem		= true;
	// ----
	strcpy(this->List[eZtUB::Pavel2].Login,			"Pavel2");
	this->List[eZtUB::Pavel2].hwid					= 2691024834;
	// ----
	strcpy(this->List[eZtUB::ulasevich2].Login,		"ulasevich2");
	this->List[eZtUB::ulasevich2].hwid				= 71422912;
	this->List[eZtUB::ulasevich2].BloodHound		= true;
	this->List[eZtUB::ulasevich2].Rage				= true;
	this->List[eZtUB::ulasevich2].MonsterQuest		= true;
	this->List[eZtUB::ulasevich2].Brotherhood		= true;
	this->List[eZtUB::ulasevich2].AntiCheatPlus		= true;
	this->List[eZtUB::ulasevich2].BMQuest			= true;
	this->List[eZtUB::ulasevich2].PandoraEvent		= true;
	this->List[eZtUB::ulasevich2].bRankItem			= true;
	this->List[eZtUB::ulasevich2].PremiumZt			= true;
	this->List[eZtUB::ulasevich2].Smithy			= true;
	this->List[eZtUB::ulasevich2].OfflineMode		= true;
	this->List[eZtUB::ulasevich2].PerosnalStoreZt	= true;
	this->List[eZtUB::ulasevich2].RestoreOffMode		= true;
	this->List[eZtUB::ulasevich2].DisableMasterTree		= true;
	this->List[eZtUB::ulasevich2].Monster			= true;
	// ----
	//strcpy(this->List[eZtUB::feqan].Login,			"feqan");
	//this->List[eZtUB::feqan].hwid					= 1521036435;
	//this->List[eZtUB::feqan].PartySystem			= true;
	// ----
	strcpy(this->List[eZtUB::Selfmylife].Login,		"Selfmylife");
	this->List[eZtUB::Selfmylife].hwid			= 3296873814;
	// ----
	strcpy(this->List[eZtUB::NoCustom].Login,		"NoCustom");
	this->List[eZtUB::NoCustom].hwid				= 1188528199;
	// ----
	strcpy(this->List[eZtUB::ConflictNoCustom].Login,"ConflictNoCustom");
	this->List[eZtUB::ConflictNoCustom].hwid		= 2492754898;
	this->List[eZtUB::ConflictNoCustom].TvTEvent	= true;
	this->List[eZtUB::ConflictNoCustom].PandoraEvent= true;
	// ----
	strcpy(List[eZtUB::Emanuel].Login,				"Emanuel");
	List[eZtUB::Emanuel].hwid						= 4196649766;
	// ----
	strcpy(this->List[eZtUB::maksim844495].Login,	"maksim844495");
	this->List[eZtUB::maksim844495].hwid			= 136373629;
	this->List[eZtUB::maksim844495].AntiCheatPlus	= true;
	// ----
	strcpy(this->List[eZtUB::SILVER_Local].Login,		"SILVER_Local");
	this->List[eZtUB::SILVER_Local].hwid				= 0;	// 3237505581;
	this->List[eZtUB::SILVER_Local].Rage				= true;
	this->List[eZtUB::SILVER_Local].TvTEvent			= true;
	this->List[eZtUB::SILVER_Local].Brotherhood			= true;
	this->List[eZtUB::SILVER_Local].PartySearch			= true;
	this->List[eZtUB::SILVER_Local].PartySystem			= true;
	this->List[eZtUB::SILVER_Local].ChatLog				= true;
	this->List[eZtUB::SILVER_Local].GM_Manager			= true;
	this->List[eZtUB::SILVER_Local].PerosnalStoreZt		= true;
	this->List[eZtUB::SILVER_Local].PartySave			= true;
	this->List[eZtUB::SILVER_Local].Smithy				= true;
	this->List[eZtUB::SILVER_Local].OfflineMode			= true;
	this->List[eZtUB::SILVER_Local].bAchievements		= true;
	this->List[eZtUB::SILVER_Local].GrandDinamicExp		= true;
	this->List[eZtUB::SILVER_Local].RestoreOffMode		= true;


	// ----
	strcpy(this->List[eZtUB::Matias].Login,				"Matias");
	this->List[eZtUB::Matias].hwid					= 1578038406;
	// ----
	strcpy(this->List[eZtUB::MMProduction].Login,		"MMProduction");
	this->List[eZtUB::MMProduction].hwid				=	NULL;	//	37123;	<<-- License double disable
	
	//strcpy(this->List[eZtUB::absolute].Login,			"absolute");
	//this->List[eZtUB::absolute].hwid					= 2349598538;	//1578038406;
	//strcpy(this->List[eZtUB::absolute].mac,	"00-15-5D-22-70-34");
	//this->List[eZtUB::absolute].PartySearch				= true;
	//this->List[eZtUB::absolute].PartySystem				= true;
	//this->List[eZtUB::absolute].ChatLog					= true;
	//this->List[eZtUB::absolute].GrandHero				= true;
	//this->List[eZtUB::absolute].GM_Manager				= true;
	//this->List[eZtUB::absolute].PerosnalStoreZt			= true;
	//this->List[eZtUB::absolute].AntiCheatPlus			= true;
	////this->List[eZtUB::absolute].Smithy				= true;
	//this->List[eZtUB::absolute].Monster					= true;
	//this->List[eZtUB::absolute].ItemSmokeEffect			= true;
	//this->List[eZtUB::absolute].PartySave				= true;
	//this->List[eZtUB::absolute].OfflineMode				= true;

	strcpy(this->List[eZtUB::DICE].Login,			"DICE");
	this->List[eZtUB::DICE].hwid					= 2730446961;	// 2730446961;	//1578038406;
	strcpy(this->List[eZtUB::DICE].mac,		"0C-8B-FD-E3-98-05");

	strcpy(this->List[eZtUB::Artem].Login,			"Artem");
	this->List[eZtUB::Artem].hwid					= 1111188280;	//	 2529125018;	// |D5-C5-AC-A8-EF-C1 эт??нового хостинга
	strcpy(this->List[eZtUB::Artem].mac,			"D5-C5-AC-A8-EF-C1");
	this->List[eZtUB::Artem].TvTEvent				= true;
	this->List[eZtUB::Artem].PerosnalStoreZt		= true;
	this->List[eZtUB::Artem].GM_Manager				= true;
	this->List[eZtUB::Artem].AntiCheatPlus			= true;
	this->List[eZtUB::Artem].SpotReturn				= true;
	this->List[eZtUB::Artem].PandoraEvent			= true;
	this->List[eZtUB::Artem].LoraBattle				= true;
	this->List[eZtUB::Artem].Smithy					= true;
	this->List[eZtUB::Artem].GrandDinamicExp		= true;
	this->List[eZtUB::Artem].DisableMasterTree		= true;
	this->List[eZtUB::Artem].Rage					= true;
	this->List[eZtUB::Artem].OfflineMode			= true;
	this->List[eZtUB::Artem].Monster				= true;
	this->List[eZtUB::Artem].Marriage				= true;
	this->List[eZtUB::Artem].PartySave				= true;
	this->List[eZtUB::Artem].bTeamVsTeam2			= true;
	this->List[eZtUB::Artem].bRankItem				= true;
	this->List[eZtUB::Artem].MonsterAttackLife		= true;
	this->List[eZtUB::Artem].RestoreOffMode			= true;
	this->List[eZtUB::Artem].PartySearch			= true;
	this->List[eZtUB::Artem].bAchievements			= true;
	this->List[eZtUB::Artem].MonsterQuest			= true;
	this->List[eZtUB::Artem].PremiumZt				= true;
	this->List[eZtUB::Artem].PartySystem			= true;
	this->List[eZtUB::Artem].Marriage				= true;
	this->List[eZtUB::Artem].AccSecurity			= true;
	this->List[eZtUB::Artem].ReferralSystem			= true;
	this->List[eZtUB::Artem].NpcBuffer				= true;

	strcpy(this->List[eZtUB::Artem2].Login,			"Artem2");
	this->List[eZtUB::Artem2].hwid					= 37123;	//37123
	//strcpy(this->List[eZtUB::Artem2].mac,			"FD-50-78-1A-FE-13");
	this->List[eZtUB::Artem2].TvTEvent				= true;
	this->List[eZtUB::Artem2].PerosnalStoreZt		= true;
	this->List[eZtUB::Artem2].GM_Manager			= true;
	this->List[eZtUB::Artem2].AntiCheatPlus			= true;
	this->List[eZtUB::Artem2].SpotReturn			= true;
	this->List[eZtUB::Artem2].PandoraEvent			= true;
	this->List[eZtUB::Artem2].LoraBattle			= true;
	this->List[eZtUB::Artem2].Smithy				= true;
	this->List[eZtUB::Artem2].GrandDinamicExp		= true;
	this->List[eZtUB::Artem2].DisableMasterTree		= true;
	this->List[eZtUB::Artem2].Rage					= true;
	this->List[eZtUB::Artem2].OfflineMode			= true;
	this->List[eZtUB::Artem2].Monster				= true;
	this->List[eZtUB::Artem2].Marriage				= true;
	this->List[eZtUB::Artem2].PartySave				= true;
	this->List[eZtUB::Artem2].bTeamVsTeam2			= true;
	this->List[eZtUB::Artem2].bRankItem				= true;
	this->List[eZtUB::Artem2].MonsterAttackLife		= true;
	this->List[eZtUB::Artem2].RestoreOffMode		= true;
	this->List[eZtUB::Artem2].PartySearch			= true;
	this->List[eZtUB::Artem2].bAchievements			= true;
	this->List[eZtUB::Artem2].MonsterQuest			= true;
	this->List[eZtUB::Artem2].PremiumZt				= true;
	this->List[eZtUB::Artem2].PartySystem			= true;
	this->List[eZtUB::Artem2].Marriage				= true;
	this->List[eZtUB::Artem2].AccSecurity			= true;
	this->List[eZtUB::Artem2].ReferralSystem		= true;
	this->List[eZtUB::Artem2].NpcBuffer				= true;


	strcpy(this->List[eZtUB::MedoniAndrei].Login,	"MedoniAndrei");
	this->List[eZtUB::MedoniAndrei].hwid			= 2630807982;// 2262655649;	//3760173629
	strcpy(this->List[eZtUB::MedoniAndrei].mac,		"A9-40-37-E5-1B-8D");
	this->List[eZtUB::MedoniAndrei].OfflineMode     = true;
	this->List[eZtUB::MedoniAndrei].PerosnalStoreZt	= true;
	this->List[eZtUB::MedoniAndrei].Monster			= true;
	this->List[eZtUB::MedoniAndrei].MonsterAttackLife = true;
	this->List[eZtUB::MedoniAndrei].Brotherhood		= true;
	this->List[eZtUB::MedoniAndrei].AntiCheatPlus	= true;
	this->List[eZtUB::MedoniAndrei].TvTEvent		= true;
	this->List[eZtUB::MedoniAndrei].ItemSmokeEffect	= true;
	//this->List[eZtUB::MedoniAndrei].Rage			= true;
	this->List[eZtUB::MedoniAndrei].bTeamVsTeam2	= true;
	this->List[eZtUB::MedoniAndrei].bRankItem		= true;
	this->List[eZtUB::MedoniAndrei].PremiumZt		= true;
	this->List[eZtUB::MedoniAndrei].AccSecurity		= true;
	this->List[eZtUB::MedoniAndrei].PartySearch		= true;
	this->List[eZtUB::MedoniAndrei].ReferralSystem  = true;
	this->List[eZtUB::MedoniAndrei].GrandDinamicExp = true;
	this->List[eZtUB::MedoniAndrei].PartySave		= true;
	this->List[eZtUB::MedoniAndrei].CraftQuestSystem = true;
	this->List[eZtUB::MedoniAndrei].PickUpItemInfo = true;

	//strcpy(this->List[eZtUB::SirJ].Login,	"SirJ");
	//this->List[eZtUB::SirJ].hwid			= 2349598538;

	strcpy(this->List[eZtUB::Eduardo].Login,	"Eduardo");
	this->List[eZtUB::Eduardo].hwid				= 3489763032;
	this->List[eZtUB::Eduardo].AntiCheatPlus	= true;
	this->List[eZtUB::Eduardo].NpcBuffer		= true;

	strcpy(this->List[eZtUB::bassreflexive].Login,	"bassreflexive");
	this->List[eZtUB::bassreflexive].hwid			= 176480702;// 3825993254;
	this->List[eZtUB::bassreflexive].PerosnalStoreZt	= true;
	this->List[eZtUB::bassreflexive].OfflineMode	= true;
	this->List[eZtUB::bassreflexive].Rage		= true;

	strcpy(this->List[eZtUB::MU2Play].Login,			"MU2Play");
	//this->List[eZtUB::MU2Play].hwid						= 3324969216;	// 3324969216;	//2349598538;
	//strcpy(this->List[eZtUB::MU2Play].mac,				"02-19-5D-22-71-D1");
	this->List[eZtUB::MU2Play].PartySearch				= true;
	this->List[eZtUB::MU2Play].PartySystem				= true;
	this->List[eZtUB::MU2Play].GM_Manager				= true;
	this->List[eZtUB::MU2Play].PerosnalStoreZt			= true;
	this->List[eZtUB::MU2Play].AntiCheatPlus			= true;
	this->List[eZtUB::MU2Play].Rage						= true;
	this->List[eZtUB::MU2Play].Monster					= true;
	this->List[eZtUB::MU2Play].PartySave				= true;
	this->List[eZtUB::MU2Play].OfflineMode				= true;
	this->List[eZtUB::MU2Play].bRankItem				= true;
	this->List[eZtUB::MU2Play].MonsterAttackLife		= true;
	this->List[eZtUB::MU2Play].GrandDinamicExp			= true;
	this->List[eZtUB::MU2Play].RestoreOffMode			= true;
	this->List[eZtUB::MU2Play].bTeamVsTeam2				= true;

	strcpy(this->List[eZtUB::Stone].Login,	"Stone");
	this->List[eZtUB::Stone].hwid			= 2628301467;	//370104553;
	strcpy(this->List[eZtUB::Stone].mac,				"02-00-00-38-40-23");
	this->List[eZtUB::Stone].bTeamVsTeam2				= true;

	strcpy(this->List[eZtUB::Sentinel].Login,			"Sentinel");
	this->List[eZtUB::Sentinel].hwid					= 1521036435;
	this->List[eZtUB::Sentinel].PartySearch				= true;
	this->List[eZtUB::Sentinel].PartySystem				= true;
	this->List[eZtUB::Sentinel].ChatLog					= true;
	this->List[eZtUB::Sentinel].GM_Manager				= true;
	this->List[eZtUB::Sentinel].PerosnalStoreZt			= true;
	this->List[eZtUB::Sentinel].AntiCheatPlus			= true;
	this->List[eZtUB::Sentinel].Rage					= true;
	this->List[eZtUB::Sentinel].Monster					= true;
	this->List[eZtUB::Sentinel].ItemSmokeEffect			= true;
	this->List[eZtUB::Sentinel].PartySave				= true;
	this->List[eZtUB::Sentinel].OfflineMode				= true;
	this->List[eZtUB::Sentinel].bRankItem				= true;
	this->List[eZtUB::Sentinel].MonsterAttackLife		= true;
	this->List[eZtUB::Sentinel].GrandDinamicExp			= true;
	this->List[eZtUB::Sentinel].RestoreOffMode			= true;
	this->List[eZtUB::Sentinel].GrandHero				= true;
	this->List[eZtUB::Sentinel].bTeamVsTeam2			= true;

	strcpy(this->List[eZtUB::Almdar].Login,				"Almdar");
	this->List[eZtUB::Almdar].hwid						= 2764084540;	//2764084540
	this->List[eZtUB::Almdar].AntiCheatPlus				= true;
	this->List[eZtUB::Almdar].PerosnalStoreZt			= true;
	this->List[eZtUB::Almdar].GM_Manager				= true;

	strcpy(this->List[eZtUB::thinnakorn].Login,			"thinnakorn");
	this->List[eZtUB::thinnakorn].hwid					= 2756002743;
	strcpy(this->List[eZtUB::thinnakorn].mac,			"00-0C-29-A1-0B-3E");
	this->List[eZtUB::thinnakorn].AntiCheatPlus			= true;
	this->List[eZtUB::thinnakorn].Rage					= true;
	this->List[eZtUB::thinnakorn].Smithy				= true;
	this->List[eZtUB::thinnakorn].OfflineMode			= true;
	this->List[eZtUB::thinnakorn].ComboCustom			= true;

	strcpy(this->List[eZtUB::EpicMU].Login,				"EpicMU");
	this->List[eZtUB::EpicMU].hwid						= 2633646976;	// 2633646976;// 2633646976;
	strcpy(this->List[eZtUB::EpicMU].mac,				"00-15-5D-00-F1-9E");
	this->List[eZtUB::EpicMU].Rage						= true;
	this->List[eZtUB::EpicMU].PartySystem				= true;
	this->List[eZtUB::EpicMU].PartySearch				= true;
	this->List[eZtUB::EpicMU].ChatLog					= true;
	this->List[eZtUB::EpicMU].GM_Manager				= true;
	this->List[eZtUB::EpicMU].PerosnalStoreZt			= true;
	this->List[eZtUB::EpicMU].AntiCheatPlus				= true;
	this->List[eZtUB::EpicMU].LoraBattle				= true;
	this->List[eZtUB::EpicMU].Monster					= true;
	this->List[eZtUB::EpicMU].ItemSmokeEffect			= true;
	this->List[eZtUB::EpicMU].PartySave					= true;
	//this->List[eZtUB::EpicMU].DisableMasterTree			= true;
	this->List[eZtUB::EpicMU].OfflineMode				= true;
	this->List[eZtUB::EpicMU].MonsterAttackLife			= true;
	this->List[eZtUB::EpicMU].bRankItem					= true;
	this->List[eZtUB::EpicMU].RestoreOffMode			= true;
	this->List[eZtUB::EpicMU].bTeamVsTeam2				= true;
	this->List[eZtUB::EpicMU].bAchievements				= true;
	this->List[eZtUB::EpicMU].MonsterQuest				= true;
	this->List[eZtUB::EpicMU].PremiumZt					= true;
	this->List[eZtUB::EpicMU].BMQuest					= true;
	this->List[eZtUB::EpicMU].Brotherhood				= true;
	this->List[eZtUB::EpicMU].Rage						= true;
	this->List[eZtUB::EpicMU].Marriage					= true;
	this->List[eZtUB::EpicMU].Smithy					= true;

	strcpy(this->List[eZtUB::masonX].Login,				"masonX");
	this->List[eZtUB::masonX].hwid						= 1356980851;
	//strcpy(this->List[eZtUB::masonX].mac,			"DF-FE-FA-BB-AE-58");
	this->List[eZtUB::masonX].PartySystem				= true;
	this->List[eZtUB::masonX].PerosnalStoreZt				= true;
	this->List[eZtUB::masonX].PartySearch				= true;
	this->List[eZtUB::masonX].PremiumZt				= true;

	strcpy(this->List[eZtUB::MatiasLeiva].Login,		"MatiasLeiva");
	this->List[eZtUB::MatiasLeiva].hwid					= 3028269993;
	strcpy(this->List[eZtUB::MatiasLeiva].mac,			"00-50-56-04-83-04");
	
	strcpy(this->List[eZtUB::AlterMU].Login,		"AlterMU");
	this->List[eZtUB::AlterMU].hwid					= 3324969216;
	strcpy(this->List[eZtUB::AlterMU].mac,			"02-27-D6-00-02-0D");
	this->List[eZtUB::AlterMU].PartySystem				= true;
	this->List[eZtUB::AlterMU].PartySearch				= true;
	this->List[eZtUB::AlterMU].ChatLog					= true;
	this->List[eZtUB::AlterMU].GM_Manager				= true;
	this->List[eZtUB::AlterMU].PerosnalStoreZt			= true;
	this->List[eZtUB::AlterMU].AntiCheatPlus			= true;
	this->List[eZtUB::AlterMU].Monster					= true;
	this->List[eZtUB::AlterMU].ItemSmokeEffect			= true;
	this->List[eZtUB::AlterMU].PartySave				= true;
	this->List[eZtUB::AlterMU].DisableMasterTree		= true;
	this->List[eZtUB::AlterMU].OfflineMode				= true;
	this->List[eZtUB::AlterMU].MonsterAttackLife		= true;
	this->List[eZtUB::AlterMU].RestoreOffMode			= true;
	this->List[eZtUB::AlterMU].bAchievements			= true;	
	this->List[eZtUB::AlterMU].GrandHero				= true;	
	this->List[eZtUB::AlterMU].CustomCameraMove			= true;	
	//this->List[eZtUB::AlterMU].CustomMiniMapZt			= true;	
	

	strcpy(this->List[eZtUB::Almdar2].Login,			"Almdar2");
	this->List[eZtUB::Almdar2].hwid						= 2756002743;	//2764084540
	strcpy(this->List[eZtUB::Almdar2].mac,				"74-D4-35-FE-B7-24");
	this->List[eZtUB::Almdar2].AntiCheatPlus			= true;
	this->List[eZtUB::Almdar2].PerosnalStoreZt			= true;
	this->List[eZtUB::Almdar2].GM_Manager				= true;
	//1087360052

	strcpy(this->List[eZtUB::Escalate].Login,			"Escalate");
	this->List[eZtUB::Escalate].hwid					= 3302700294;	//2633646976;
	strcpy(this->List[eZtUB::Escalate].mac,				"02-12-5D-00-45-90");
	this->List[eZtUB::Escalate].PartySearch				= true;
	this->List[eZtUB::Escalate].PartySystem				= true;
	this->List[eZtUB::Escalate].GM_Manager				= true;
	this->List[eZtUB::Escalate].PerosnalStoreZt			= true;
	this->List[eZtUB::Escalate].AntiCheatPlus			= true;
	this->List[eZtUB::Escalate].Rage					= true;
	this->List[eZtUB::Escalate].Monster					= true;
	this->List[eZtUB::Escalate].PartySave				= true;
	this->List[eZtUB::Escalate].OfflineMode				= true;
	this->List[eZtUB::Escalate].bRankItem				= true;
	this->List[eZtUB::Escalate].MonsterAttackLife		= true;
	this->List[eZtUB::Escalate].GrandDinamicExp			= true;
	this->List[eZtUB::Escalate].RestoreOffMode			= true;
	this->List[eZtUB::Escalate].bTeamVsTeam2			= true;
	this->List[eZtUB::Escalate].LoraBattle				= true;	//OK
	//this->List[eZtUB::Escalate].Smithy					= true;	//OK
	this->List[eZtUB::Escalate].ItemSmokeEffect			= true;	//OK
	this->List[eZtUB::Escalate].PandoraEvent			= true;	//OK
	this->List[eZtUB::Escalate].OfflineMode				= true;
	this->List[eZtUB::Escalate].bAchievements			= true;
	this->List[eZtUB::Escalate].AccSecurity				= true;
	this->List[eZtUB::Escalate].PremiumZt				= true;
	this->List[eZtUB::Escalate].ComboCustom				= true;

	strcpy(this->List[eZtUB::RafaelLorenzet].Login,		"RafaelLorenzet");
	this->List[eZtUB::RafaelLorenzet].hwid				= 2282774568;	//2633646976;
	strcpy(this->List[eZtUB::RafaelLorenzet].mac,		"00-15-5D-1E-17-05");

	strcpy(this->List[eZtUB::TGBA_LLC].Login,			"TGBA_LLC");
	this->List[eZtUB::TGBA_LLC].hwid					= 3324969216;	//2633646976;
	strcpy(this->List[eZtUB::TGBA_LLC].mac,				"00-01-5D-D7-04-C1");
	this->List[eZtUB::TGBA_LLC].Monster					= true;
	this->List[eZtUB::TGBA_LLC].bAchievements			= true;
	this->List[eZtUB::TGBA_LLC].MonsterQuest			= true;
	
	strcpy(this->List[eZtUB::RevoMU].Login,				"RevoMU");
	//this->List[eZtUB::RevoMU].hwid						= 1918130772;
	this->List[eZtUB::RevoMU].hwid						= 3324969216;	//3324969216;	// 1918130772;
	strcpy(this->List[eZtUB::RevoMU].mac,				"02-05-5D-CD-04-73");
	this->List[eZtUB::RevoMU].bAchievements				= true;
	this->List[eZtUB::RevoMU].OfflineMode				= true;
	this->List[eZtUB::RevoMU].PerosnalStoreZt			= true;
	this->List[eZtUB::RevoMU].PartySystem				= true;
	this->List[eZtUB::RevoMU].PartySearch				= true;
	this->List[eZtUB::RevoMU].ChatLog					= true;
	this->List[eZtUB::RevoMU].GM_Manager				= true;
	this->List[eZtUB::RevoMU].PartySave					= true;
	this->List[eZtUB::RevoMU].RestoreOffMode			= true;
	this->List[eZtUB::RevoMU].PremiumZt					= true;
	this->List[eZtUB::RevoMU].AccSecurity				= true;
	this->List[eZtUB::RevoMU].MonsterQuest				= true;

	strcpy(this->List[eZtUB::DrXAOS].Login,				"DrXAOS");
	this->List[eZtUB::DrXAOS].hwid						= 2153285885;
	strcpy(this->List[eZtUB::DrXAOS].mac,				"97-67-23-65-5A-0A");

	strcpy(this->List[eZtUB::masonX2].Login,				"masonX");
	this->List[eZtUB::masonX2].hwid						= 473466670;
	strcpy(this->List[eZtUB::masonX2].mac,				"A6-A1-04-8F-7C-F2");
	this->List[eZtUB::masonX2].PartySystem				= true;
	this->List[eZtUB::masonX2].PerosnalStoreZt			= true;
	this->List[eZtUB::masonX2].PartySearch				= true;
	this->List[eZtUB::masonX2].PremiumZt				= true;

	strcpy(this->List[eZtUB::GloryMU].Login,				"GloryMU");
	//this->List[eZtUB::GloryMU].hwid						= 3302700294;
	//strcpy(this->List[eZtUB::GloryMU].mac,			"02-0E-5D-00-3E-4F");
	this->List[eZtUB::GloryMU].GrandHero				= true;
	this->List[eZtUB::GloryMU].PartySystem				= true;
	this->List[eZtUB::GloryMU].PartySearch				= true;
	this->List[eZtUB::GloryMU].ChatLog					= true;
	this->List[eZtUB::GloryMU].GM_Manager				= true;
	this->List[eZtUB::GloryMU].PerosnalStoreZt			= true;
	this->List[eZtUB::GloryMU].ComboCustom				= false;
	this->List[eZtUB::GloryMU].NpcBuffer				= false;
	this->List[eZtUB::GloryMU].LoraBattle				= true;
	this->List[eZtUB::GloryMU].Smithy					= true;
	this->List[eZtUB::GloryMU].Monster					= true;
	this->List[eZtUB::GloryMU].ItemSmokeEffect			= true;
	this->List[eZtUB::GloryMU].GrandDinamicExp			= true;
	this->List[eZtUB::GloryMU].PartySave				= true;
	this->List[eZtUB::GloryMU].DisableMasterTree		= true;
	this->List[eZtUB::GloryMU].OfflineMode				= true;
	this->List[eZtUB::GloryMU].bRankItem				= false;
	this->List[eZtUB::GloryMU].RestoreOffMode			= true;
	this->List[eZtUB::GloryMU].bTeamVsTeam2				= false;
	this->List[eZtUB::GloryMU].bAchievements			= true;
	this->List[eZtUB::GloryMU].PremiumZt				= true;
	this->List[eZtUB::GloryMU].AccSecurity				= true;
	this->List[eZtUB::GloryMU].CraftQuestSystem			= true;
	this->List[eZtUB::GloryMU].PickUpItemInfo			= false;
	this->List[eZtUB::GloryMU].ReferralSystem			= 0;

	strcpy(this->List[eZtUB::MuRelic].Login,				"MuRelic");	//vlad vlad
	this->List[eZtUB::MuRelic].hwid						= 0;
	//strcpy(this->List[eZtUB::MuRelic].mac,			"00-15-5D-06-41-F8");
	this->List[eZtUB::MuRelic].GrandHero				= true;

	strcpy(this->List[eZtUB::ArcMu].Login,				"ArcMu");
	this->List[eZtUB::ArcMu].hwid						= 697983919;
	strcpy(this->List[eZtUB::ArcMu].mac,				"A4-BF-01-23-8E-D3");
	this->List[eZtUB::ArcMu].Rage						= true;
	this->List[eZtUB::ArcMu].Monster					= true;
	this->List[eZtUB::ArcMu].ItemSmokeEffect			= true;
	this->List[eZtUB::ArcMu].MonsterQuest				= true;//
	this->List[eZtUB::ArcMu].GrandHero					= true;
	this->List[eZtUB::ArcMu].TvTEvent					= true;
	this->List[eZtUB::ArcMu].PartySystem				= true;
	this->List[eZtUB::ArcMu].Brotherhood				= false;
	this->List[eZtUB::ArcMu].PartySearch				= true;
	this->List[eZtUB::ArcMu].PerosnalStoreZt			= true;
	this->List[eZtUB::ArcMu].CraftQuestSystem			= true;
	this->List[eZtUB::ArcMu].NpcBuffer					= true;
	this->List[eZtUB::ArcMu].ComboCustom				= false;
	this->List[eZtUB::ArcMu].MonsterAttackLife			= true;
	this->List[eZtUB::ArcMu].PandoraEvent				= true;
	this->List[eZtUB::ArcMu].Smithy						= true;
	this->List[eZtUB::ArcMu].bRankItem					= true;
	this->List[eZtUB::ArcMu].bAchievements				= true;
	this->List[eZtUB::ArcMu].RestoreOffMode				= true;
	this->List[eZtUB::ArcMu].AccSecurity				= true;

#if(LICENSE_ARCMU)
	this->List[eZtUB::ArcMu].bTeamVsTeam2				= true;
	this->List[eZtUB::ArcMu].LoraBattle					= true;
	this->List[eZtUB::ArcMu].GM_Manager					= true;
	this->List[eZtUB::ArcMu].MapQuest					= true;
	this->List[eZtUB::ArcMu].PremiumZt					= true;
	this->List[eZtUB::ArcMu].BloodHound					= true;
	this->List[eZtUB::ArcMu].Brotherhood				= true;
	this->List[eZtUB::ArcMu].Marriage					= true;
	this->List[eZtUB::ArcMu].PartySave					= true;
	this->List[eZtUB::ArcMu].OfflineMode				= true;
#endif

	strcpy(this->List[eZtUB::muheroia].Login,				"muheroia");
	this->List[eZtUB::muheroia].hwid						= 3302700294;
	strcpy(this->List[eZtUB::muheroia].mac,			"02-12-5D-00-45-DF");

	strcpy(this->List[eZtUB::HomeLan].Login,				"HomeLan");
	//this->List[eZtUB::HomeLan].hwid						= 3302700294;
	//strcpy(this->List[eZtUB::HomeLan].mac,			"02-12-5D-00-45-DF");

	strcpy(this->List[eZtUB::ProtectDebug].Login,				"ProtectDebug");
	//this->List[eZtUB::ProtectDebug].hwid						= ProtectDebug;
	//strcpy(this->List[eZtUB::ProtectDebug].mac,			"02-12-5D-00-45-DF");
	this->List[eZtUB::ProtectDebug].OfflineMode				= true;
	this->List[eZtUB::ProtectDebug].RestoreOffMode			= true;
	this->List[eZtUB::ProtectDebug].PerosnalStoreZt			= true;

	strcpy(this->List[eZtUB::UpdateDebug].Login,		"UpdateDebug");
	//this->List[eZtUB::UpdateDebug].hwid					= 0;
	//strcpy(this->List[eZtUB::UpdateDebug].mac,			"60-A4-4C-2B-45-03");
	this->List[eZtUB::UpdateDebug].Credit				= 0;
	this->List[eZtUB::UpdateDebug].Baned				= false;
	this->List[eZtUB::UpdateDebug].Rage					= true;
	this->List[eZtUB::UpdateDebug].WinQuest				= 0;
	this->List[eZtUB::UpdateDebug].BloodHound			= true;
	this->List[eZtUB::UpdateDebug].MonsterQuest			= true;
	this->List[eZtUB::UpdateDebug].TvTEvent				= true;
	this->List[eZtUB::UpdateDebug].GrandHero			= true;
	this->List[eZtUB::UpdateDebug].PartySystem			= true;
	this->List[eZtUB::UpdateDebug].Brotherhood			= true;
	this->List[eZtUB::UpdateDebug].PartySearch			= true;
	this->List[eZtUB::UpdateDebug].ChatLog				= true;
	this->List[eZtUB::UpdateDebug].GM_Manager			= true;
	this->List[eZtUB::UpdateDebug].PerosnalStoreZt		= true;
	this->List[eZtUB::UpdateDebug].PandoraEvent			= true;
	this->List[eZtUB::UpdateDebug].AntiCheatPlus		= true;
	this->List[eZtUB::UpdateDebug].ComboCustom			= true;
	this->List[eZtUB::UpdateDebug].NpcBuffer			= true;
	this->List[eZtUB::UpdateDebug].BMQuest				= true;
	this->List[eZtUB::UpdateDebug].LoraBattle			= true;
	this->List[eZtUB::UpdateDebug].Smithy				= true;
	this->List[eZtUB::UpdateDebug].Monster				= true;
	this->List[eZtUB::UpdateDebug].ItemSmokeEffect		= true;
	this->List[eZtUB::UpdateDebug].GrandDinamicExp      = true;
	this->List[eZtUB::UpdateDebug].PartySave			= true;
	this->List[eZtUB::UpdateDebug].DisableMasterTree	= true;
	this->List[eZtUB::UpdateDebug].OfflineMode			= true;
	this->List[eZtUB::UpdateDebug].Marriage				= true;
	this->List[eZtUB::UpdateDebug].bRankItem			= true;
	this->List[eZtUB::UpdateDebug].RestoreOffMode		= true;
	this->List[eZtUB::UpdateDebug].MapQuest				= true;
	this->List[eZtUB::UpdateDebug].bTeamVsTeam2         = true;
	this->List[eZtUB::UpdateDebug].bAchievements		= true;
	this->List[eZtUB::UpdateDebug].PremiumZt			= true;
	this->List[eZtUB::UpdateDebug].AccSecurity			= true;
	this->List[eZtUB::UpdateDebug].CraftQuestSystem		= true;
	this->List[eZtUB::UpdateDebug].PickUpItemInfo		= true;
	this->List[eZtUB::UpdateDebug].ReferralSystem		= true;
	
	strcpy(this->List[eZtUB::MegaM].Login,		"MegaM");
	this->List[eZtUB::MegaM].hwid					= 3226014109;
	strcpy(this->List[eZtUB::MegaM].mac,			"02-11-5D-00-6B-C4");
	this->List[eZtUB::MegaM].MonsterQuest			= true;
	this->List[eZtUB::MegaM].bTeamVsTeam2			= true;

	strcpy(this->List[eZtUB::mu4you].Login,			"mu4you");
	this->List[eZtUB::mu4you].hwid					= 3302700294;
	strcpy(this->List[eZtUB::mu4you].mac,			"02-0E-5D-00-3E-4F");
	this->List[eZtUB::mu4you].PartySearch			= true;
	this->List[eZtUB::mu4you].PartySystem			= true;
	this->List[eZtUB::mu4you].GM_Manager			= true;
	this->List[eZtUB::mu4you].PerosnalStoreZt		= true;
	this->List[eZtUB::mu4you].AntiCheatPlus			= true;
	this->List[eZtUB::mu4you].Rage					= true;
	this->List[eZtUB::mu4you].Monster				= true;
	this->List[eZtUB::mu4you].PartySave				= true;
	this->List[eZtUB::mu4you].OfflineMode			= true;
	this->List[eZtUB::mu4you].bRankItem				= true;
	this->List[eZtUB::mu4you].MonsterAttackLife		= true;
	this->List[eZtUB::mu4you].GrandDinamicExp		= true;
	this->List[eZtUB::mu4you].RestoreOffMode		= true;
	this->List[eZtUB::mu4you].bTeamVsTeam2			= true;
	this->List[eZtUB::mu4you].LoraBattle			= true;
	this->List[eZtUB::mu4you].ItemSmokeEffect		= true;
	this->List[eZtUB::mu4you].PandoraEvent			= true;
	this->List[eZtUB::mu4you].OfflineMode			= true;
	this->List[eZtUB::mu4you].bAchievements			= true;
	this->List[eZtUB::mu4you].AccSecurity			= true;
	this->List[eZtUB::mu4you].PremiumZt				= true;
	this->List[eZtUB::mu4you].ComboCustom			= true;

	strcpy(this->List[eZtUB::eternalmu].Login,			"eternalmu");
	this->List[eZtUB::eternalmu].hwid					= 3971232786;	//3971232786|00-15-5D-05-62-89
	strcpy(this->List[eZtUB::eternalmu].mac,		"00-15-5D-05-62-89");
	this->List[eZtUB::eternalmu].PartySearch				= true;
	this->List[eZtUB::eternalmu].PartySystem				= true;
	this->List[eZtUB::eternalmu].GM_Manager				= true;
	this->List[eZtUB::eternalmu].PerosnalStoreZt			= true;
	this->List[eZtUB::eternalmu].AntiCheatPlus			= true;
	this->List[eZtUB::eternalmu].Rage					= true;
	this->List[eZtUB::eternalmu].Monster					= true;
	this->List[eZtUB::eternalmu].PartySave				= true;
	this->List[eZtUB::eternalmu].OfflineMode				= true;
	this->List[eZtUB::eternalmu].bRankItem				= true;
	this->List[eZtUB::eternalmu].MonsterAttackLife		= true;
	this->List[eZtUB::eternalmu].GrandDinamicExp			= true;
	this->List[eZtUB::eternalmu].RestoreOffMode			= true;
	this->List[eZtUB::eternalmu].bTeamVsTeam2			= true;
	this->List[eZtUB::eternalmu].LoraBattle				= true;	//OK
	//this->List[eZtUB::eternalmu].Smithy					= true;	//OK
	this->List[eZtUB::eternalmu].ItemSmokeEffect			= true;	//OK
	this->List[eZtUB::eternalmu].PandoraEvent			= true;	//OK
	this->List[eZtUB::eternalmu].OfflineMode				= true;
	this->List[eZtUB::eternalmu].bAchievements			= true;
	this->List[eZtUB::eternalmu].AccSecurity				= true;
	this->List[eZtUB::eternalmu].PremiumZt				= true;
	this->List[eZtUB::eternalmu].ComboCustom				= true;
	this->List[eZtUB::eternalmu].ChatLog				= true;
	this->List[eZtUB::eternalmu].DisableMasterTree			= true;

	this->List[eZtUB::eternalmu].WinQuest			= true;

	strcpy(this->List[eZtUB::WarBorn].Login,			"WarBorn");
	this->List[eZtUB::WarBorn].hwid					= 3971232786;
	strcpy(this->List[eZtUB::WarBorn].mac,			"02-0E-5D-00-3E-58");
	this->List[eZtUB::WarBorn].PartySearch			= true;
	this->List[eZtUB::WarBorn].PartySystem			= true;
	this->List[eZtUB::WarBorn].GM_Manager			= true;
	this->List[eZtUB::WarBorn].PerosnalStoreZt		= true;
	this->List[eZtUB::WarBorn].AntiCheatPlus		= true;
	this->List[eZtUB::WarBorn].Rage					= true;
	this->List[eZtUB::WarBorn].Monster				= true;
	this->List[eZtUB::WarBorn].PartySave			= true;
	this->List[eZtUB::WarBorn].OfflineMode			= true;
	this->List[eZtUB::WarBorn].bRankItem			= true;
	this->List[eZtUB::WarBorn].MonsterAttackLife	= true;
	this->List[eZtUB::WarBorn].GrandDinamicExp		= true;
	this->List[eZtUB::WarBorn].RestoreOffMode		= true;
	this->List[eZtUB::WarBorn].bTeamVsTeam2			= true;
	this->List[eZtUB::WarBorn].LoraBattle			= true;
	this->List[eZtUB::WarBorn].ItemSmokeEffect		= true;
	this->List[eZtUB::WarBorn].PandoraEvent			= true;
	this->List[eZtUB::WarBorn].OfflineMode			= true;
	this->List[eZtUB::WarBorn].bAchievements		= true;
	this->List[eZtUB::WarBorn].AccSecurity			= true;
	this->List[eZtUB::WarBorn].PremiumZt			= true;
	this->List[eZtUB::WarBorn].ComboCustom			= true;

	strcpy(this->List[eZtUB::NSGames].Login,			"NSGames");
	this->List[eZtUB::NSGames].hwid					= 3971232786;
	strcpy(this->List[eZtUB::NSGames].mac,			"00-15-5D-05-84-FA");
	this->List[eZtUB::NSGames].PartySearch			= true;
	this->List[eZtUB::NSGames].PartySystem			= true;
	this->List[eZtUB::NSGames].GM_Manager			= true;
	this->List[eZtUB::NSGames].PerosnalStoreZt		= true;
	this->List[eZtUB::NSGames].AntiCheatPlus			= true;
	this->List[eZtUB::NSGames].Rage					= true;
	this->List[eZtUB::NSGames].Monster				= true;
	this->List[eZtUB::NSGames].PartySave				= true;
	this->List[eZtUB::NSGames].OfflineMode			= true;
	this->List[eZtUB::NSGames].bRankItem				= true;
	this->List[eZtUB::NSGames].MonsterAttackLife		= true;
	this->List[eZtUB::NSGames].GrandDinamicExp		= true;
	this->List[eZtUB::NSGames].RestoreOffMode		= true;
	this->List[eZtUB::NSGames].bTeamVsTeam2			= true;
	this->List[eZtUB::NSGames].LoraBattle			= true;
	this->List[eZtUB::NSGames].ItemSmokeEffect		= true;
	this->List[eZtUB::NSGames].PandoraEvent			= true;
	this->List[eZtUB::NSGames].OfflineMode			= true;
	this->List[eZtUB::NSGames].bAchievements			= true;
	this->List[eZtUB::NSGames].AccSecurity			= true;
	this->List[eZtUB::NSGames].PremiumZt				= true;
	this->List[eZtUB::NSGames].ComboCustom			= true;
	this->List[eZtUB::NSGames].DisableMasterTree			= true;
	this->List[eZtUB::NSGames].NpcBuffer			= true;
	this->List[eZtUB::NSGames].CustomCameraMove		= 1;
	this->List[eZtUB::NSGames].CustomMiniMapZt		= 1;
	this->List[eZtUB::NSGames].CustomMapTeleport	= 1;

	strcpy(this->List[eZtUB::FinalMU].Login,	"FinalMU");
	this->List[eZtUB::FinalMU].WinQuest			= true;

	strcpy(this->List[eZtUB::MUDev].Login,		"MUDev");
	this->List[eZtUB::MUDev].Monster	= 1;
	this->List[eZtUB::MUDev].CustomMiniMapZt	= 1;

	strcpy(this->List[eZtUB::FoxMU].Login,			"FoxMU");
	this->List[eZtUB::FoxMU].hwid					= 1278144493;
	strcpy(this->List[eZtUB::FoxMU].mac,			"00-15-5D-AC-28-10");

	// ----

	strcpy(this->List[eZtUB::MUCustom].Login,		"MUCustom");
	this->List[eZtUB::MUCustom].hwid				= 419191045;
	strcpy(this->List[eZtUB::MUCustom].mac,			"24-4B-FE-7B-09-F9");
	//this->List[eZtUB::MUCustom].FixVieweMonster	= 1;
	//this->List[eZtUB::MUCustom].CustomMapTeleport	= 1;
	this->List[eZtUB::MUCustom].CustomCameraMove	= 1;
	this->List[eZtUB::MUCustom].CustomMiniMapZt	= 1;
	

	strcpy(this->List[eZtUB::Chebuk].Login,			"Chebuk");
	this->List[eZtUB::Chebuk].hwid					= 851719034;
	strcpy(this->List[eZtUB::Chebuk].mac,			"00-15-13-2D-A2-52");	

	strcpy(this->List[eZtUB::Jancis].Login,			"Jancis");
	this->List[eZtUB::Jancis].hwid					= 3693880149;
	strcpy(this->List[eZtUB::Jancis].mac,			"02-00-00-32-8C-B8");	
	this->List[eZtUB::Jancis].CustomMapTeleport		= 1;
	this->List[eZtUB::Jancis].CustomCameraMove		= 1;
	
	strcpy(this->List[eZtUB::Atomic].Login,			"Atomic");
	//this->List[eZtUB::Atomic].hwid					= 3693880149;
	//strcpy(this->List[eZtUB::Atomic].mac,			"02-00-00-32-8C-B8");	

	strcpy(this->List[eZtUB::jammal].Login,			"jammal");
	this->List[eZtUB::jammal].hwid					= 987085549;
	strcpy(this->List[eZtUB::jammal].mac,			"00-50-56-22-01-01");		

	strcpy(this->List[eZtUB::MuPrime].Login,			"MuPrime");
	this->List[eZtUB::MuPrime].hwid					= 2326546573;
	strcpy(this->List[eZtUB::MuPrime].mac,			"F7-10-16-F6-56-9F");		

	strcpy(this->List[eZtUB::Berlin].Login,			"Berlin");
	this->List[eZtUB::Berlin].hwid					= 3226014109;
	strcpy(this->List[eZtUB::Berlin].mac,			"00-15-5D-09-A4-0F");		
	this->List[eZtUB::Berlin].CustomMiniMapZt	= 1;

	strcpy(this->List[eZtUB::Thinnakorn].Login,			"Thinnakorn");
	this->List[eZtUB::Thinnakorn].hwid					= 1392480478;
	strcpy(this->List[eZtUB::Thinnakorn].mac,			"00-0C-29-FF-E9-2E");		

	strcpy(this->List[eZtUB::InfinityMU].Login,			"InfinityMU");
	this->List[eZtUB::InfinityMU].hwid					= 3601014565;
	strcpy(this->List[eZtUB::InfinityMU].mac,			"F7-2D-8E-C4-4B-F4");		

	strcpy(this->List[eZtUB::MuInsane].Login,			"MuInsane");
	
	strcpy(this->List[eZtUB::Jeancarlos].Login,			"Jeancarlos");
	this->List[eZtUB::Jeancarlos].hwid					= 3565722453;
	strcpy(this->List[eZtUB::Jeancarlos].mac,			"00-16-3C-67-3E-05");	

	strcpy(this->List[eZtUB::NoriaMU].Login,			"NoriaMU");
	this->List[eZtUB::NoriaMU].hwid					= 172572549;
	strcpy(this->List[eZtUB::NoriaMU].mac,			"00-50-56-A2-15-26");	

	strcpy(this->List[eZtUB::FlameMu].Login,			"FlameMu");
	this->List[eZtUB::FlameMu].hwid					= 4103493799;
	strcpy(this->List[eZtUB::FlameMu].mac,			"BA-AE-51-32-80-1F");	

	strcpy(this->List[eZtUB::AsteraMU].Login,			"AsteraMU");
	this->List[eZtUB::AsteraMU].hwid					= 4103493799;
	strcpy(this->List[eZtUB::AsteraMU].mac,			"BA-AE-51-32-80-1F");	

	strcpy(this->List[eZtUB::MU_GE].Login,			"MU_GE");
	this->List[eZtUB::MU_GE].hwid					= 2262655649;
	strcpy(this->List[eZtUB::MU_GE].mac,				"A4-89-F2-5D-0D-15");	

	strcpy(this->List[eZtUB::SaksonPavel].Login,			"SaksonPavel");
	//this->List[eZtUB::SaksonPavel].hwid					= 2262655649;
	//strcpy(this->List[eZtUB::SaksonPavel].mac,				"A4-89-F2-5D-0D-15");	
}


void CZtLicense::CheckLicense()
{
#if(ZTLICENSE_SELECT)
	//this->SelectLicense(eZtUB::ulasevich);
	//this->SelectLicense(eZtUB::Gredy);	
	//this->SelectLicense(eZtUB::MuPrime);
	//this->SelectLicense(eZtUB::Thinnakorn);
	//this->SelectLicense(eZtUB::Berlin);	//48 14
	//this->SelectLicense(eZtUB::MUCustom);
	//this->SelectLicense(eZtUB::InfinityMU);
	//this->SelectLicense(eZtUB::MUDev);
	//this->SelectLicense(eZtUB::Berlin);
	//this->SelectLicense(eZtUB::AsteraMU);
	//this->SelectLicense(eZtUB::SaksonPavel);
	this->SelectLicense(eZtUB::AlterMU);
	//this->SelectLicense(eZtUB::Gredy);
	
	return;
#endif

#if(THINNAKORN_MAC)
	strcpy(this->user.Login,		"AllCustom");
	strcpy(this->user.Password,		"");                                                                                                                                                                                                                                                                                                    
	this->user.hwid					= 0;
	this->user.mac[0]				= NULL;
	this->user.Credit				= 0;
	this->user.Baned				= true;
	this->user.Rage					= true;
	this->user.WinQuest				= false;
	this->user.BloodHound			= true;
	this->user.MonsterQuest			= true;
	this->user.TvTEvent				= true;
	this->user.GrandHero			= true;
	this->user.PartySystem			= true;
	this->user.Brotherhood			= true;
	this->user.PartySearch			= true;
	this->user.ChatLog				= true;
	this->user.GM_Manager			= true;
	this->user.PerosnalStoreZt		= true;
	this->user.PandoraEvent			= true;
	this->user.AntiCheatPlus		= true;
	this->user.ComboCustom			= true;
	this->user.NpcBuffer			= true;
	this->user.BMQuest				= true;
	this->user.LoraBattle			= true;
	this->user.Smithy				= true;
	this->user.Monster				= true;
	this->user.ItemSmokeEffect		= true;
	this->user.GrandDinamicExp      = true;
	this->user.PartySave			= true;
	this->user.DisableMasterTree	= true;
	this->user.OfflineMode			= true;
	this->user.Marriage				= true;
	this->user.bRankItem			= true;
	this->user.RestoreOffMode		= true;
	this->user.MapQuest				= true;
	this->user.bTeamVsTeam2         = true;
	this->user.bAchievements		= true;

	return;
#endif

#if(LICENSE_EVOMU)
	this->ActiveUser = eZtUB::Gredy;
	memcpy(&this->user, &this->List[this->ActiveUser], sizeof(g_ZtLicense.user));
	return;
#endif


	VMBEGIN

	bool Result = false; 

	unsigned char MACData[6];
	UUID uuid;
	UuidCreateSequential(&uuid);

	for(int i = 2; i < 8; i++)
	{
		MACData[i-2] = uuid.Data4[i];
	}

	char szMac[18];
	sprintf(szMac, "%02X-%02X-%02X-%02X-%02X-%02X", MACData[0], MACData[1], MACData[2], MACData[3], MACData[4], MACData[5]);

	for(int i = 0; i < TOTAL_CLIENT; i++)
	{
		if(this->List[i].mac[0] != NULL)
		{
			if(!strcmp(this->List[i].mac, szMac))
			{
				if(this->List[i].Baned)
				{
					ExitProcess(0);
				}
				this->ActiveUser = i;
				Result = true;
				break;
			}
		}
	}

	if(Result == false)
	{
		unsigned long HDDKEY;
		GetVolumeInformationA(this->GetDecText(DISK_DIR),0,0,&HDDKEY,0,0,0,0); 

		for(int i = 0; i < TOTAL_CLIENT; i++)
		{
			if(HDDKEY == this->List[i].hwid)
			{
				if(this->List[i].Baned)
				{
					ExitProcess(0);
				}
				this->ActiveUser = i;
				Result = true;
				break;
			}
		}
	}

	/*
	if(!this->CheckTime(NoriaMU, 2020, 8, 17))
	{
		Result = false;
	}
	*/

	if(!Result)
	{
		ExitProcess(0);
		return;
	}

	memcpy(&this->user, &this->List[this->ActiveUser], sizeof(g_ZtLicense.user));
	VMEND
}
#endif

bool CZtLicense::CheckUser(int NeedUser)
{
	if(this->ActiveUser == NeedUser)
	{
		return true;
	}
	return false;
}

void CZtLicense::GCLicenseUser(int aIndex)
{
	VMBEGIN
	PMSG_LICENSE_DATA rSend;
	rSend.h.set((LPBYTE)&rSend, 0xFB, 17, sizeof(rSend));
	rSend.LicenseUser = this->ActiveUser;
	rSend.LicenseCustom = this->m_SetCustom;
	memcpy(&rSend.base, &this->user, sizeof(g_ZtLicense.user));
	rSend.config.MaxPartyUser = g_MaxPartyMember;
	rSend.config.PersonalEnable = g_PersonalShopZt.Enable;
	rSend.config.PersonalBonus = g_PersonalShopZt.BonusPrice;
	rSend.config.PersonalCredit = g_PersonalShopZt.CreditPrice;
	DataSend(aIndex,(LPBYTE)&rSend,sizeof(rSend));
	g_UserConfig.GC_SettingsSend(aIndex);
	VMEND
}
// ----------------------------------------------------------------------------------------------

void CZtLicense::GDLicenseUser()
{
	VMBEGIN
	PMSG_LICENSE_DATA rSend;
	rSend.h.set((LPBYTE)&rSend, 0xE3, 0x00, sizeof(rSend));
	rSend.LicenseUser = this->ActiveUser;
	rSend.LicenseCustom = this->m_SetCustom;
	rSend.base = this->user;
	rSend.config.Gens = gGENS;
	cDBSMng.Send((char*)&rSend, sizeof(rSend));
	VMEND
}

char* CZtLicense::GetDecText(char* EncodeChar)
{
	int len = strlen(EncodeChar);	
	char* Line = new char[len+1];
	for(int i = 0; i < len; i++)
	{
		Line[i] = char(EncodeChar[i] ^ this->TextXoR[i % 3]);
	}
	Line[len] = 0;
	return Line;
}

void CZtLicense::SelectLicense(int UserID)
{
	this->ActiveUser = UserID;
	memcpy(&this->user, &this->List[UserID], sizeof(this->user));
	return;
}

char* CZtLicense::GetLicenseName()
{
	if(this->ActiveUser == -1)
	{
		return "Unknown";
	}

	return this->user.Login;
}

void CZtLicense::CustomManager()
{
	#if(CUSTOM_VALUE_MENU)
	if(/*g_ZtLicense.CheckUser(eZtUB::NSGames) || */g_ZtLicense.CheckUser(eZtUB::Artem) || g_ZtLicense.CheckUser(eZtUB::Artem2) ||
	   g_ZtLicense.CheckUser(eZtUB::Gredy)	 ||  g_ZtLicense.CheckUser(eZtUB::Gredy2) || g_ZtLicense.CheckUser(eZtUB::GredyLocal) || 
	   g_ZtLicense.CheckUser(eZtUB::WarBorn))
	{
		this->m_MultiWarehouseType = 1;
	}
	#endif
}

void CZtLicense::SetCustom(int ListID)
{
	if( !g_ZtLicense.CheckUser(eZtUB::ulasevich) && 
		!g_ZtLicense.CheckUser(eZtUB::ulasevich2) &&
		!g_ZtLicense.CheckUser(eZtUB::DavitRazmadze))
	{
		if(this->ActiveUser < 84)
		{
			return;
		}
	}


	this->m_SetCustom = 1;

	//LICENSE_DATA * pList = &List[ListID]; 

	LICENSE_DATA * pList = &this->user;

	pList->Rage					= true;
	pList->MonsterQuest			= true;
	pList->TvTEvent				= true;
	pList->GrandHero			= true;
	pList->PartySystem			= true;
	pList->PartySearch			= true;
	pList->ChatLog				= true;
	pList->GM_Manager			= true;
	pList->PerosnalStoreZt		= true;
	pList->PandoraEvent			= true;
	pList->AntiCheatPlus		= true;
	pList->ComboCustom			= true;
	pList->NpcBuffer			= true;
	pList->LoraBattle			= true;
	pList->Smithy				= true;
	pList->Monster				= true;
	pList->ItemSmokeEffect		= true;
	pList->GrandDinamicExp      = true;
	pList->PartySave			= true;
	pList->OfflineMode			= true;
	pList->MonsterAttackLife	= true;
	pList->bRankItem			= true;
	pList->RestoreOffMode		= true;
	pList->MapQuest				= true;
	pList->bTeamVsTeam2			= true;
	pList->bAchievements		= true;
	pList->PremiumZt			= true;
	pList->CraftQuestSystem		= true;
	pList->PickUpItemInfo		= true;

	pList->AccSecurity			= true;
	pList->WinQuest				= true;
	pList->Brotherhood			= true;
	pList->Marriage				= true;

	this->m_MultiWarehouseType = 1;

	//

	if(g_ZtLicense.CheckUser(eZtUB::Berlin))
	{
		pList->Smithy = false;
	}

	



	//AccSecurity

	/*
		Config Interface Chat
		Config Interface Buff Icon
		Add Points
		Reset point
		Donate Manager
		Teleport Manager
		NPC PK Clear
		Donate Shop
		Monster Message
		Dungeon Siege
		Carnage Event
		Question Answer
	*/
}

int CZtLicense::GetCustom()
{
	return this->m_SetCustom;
}

bool CZtLicense::CheckTime(int UserID, int Year, int Month, int Day)
{
	if(UserID != this->ActiveUser)
	{
		return true;
	}
	
	SYSTEMTIME t;

	GetLocalTime(&t);

	if(t.wYear >= Year)
	{
		if(t.wMonth >= Month)
		{
			if(t.wDay >= Day)
			{
				return false;
			}
		}
	}

	return true;
}