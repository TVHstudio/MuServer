#include "stdafx.h"
#include "ZtLicense.h"
#include "Monster.h"
#include "ItemSmokeEffect.h"
#include "Configs.h"
#include "PartySearch.h"
#include "PersonalShopZt.h"
#include "Smithy.h"
#include "TMemory.h"
#include "Interface.h"
#include "VisualFix.h"
#include "User.h"
#include "DonateShop.h"
#include "AddPoints.h"
#include "Console.h"
#include "WingEffect.h"
#include "MiniMenu.h"
#include "Controller.h"
#include "ChatExpanded.h"
#include "ItemSetOption.h"
#include "AccountSecurity.h"
#include "Interface.h"
#include "BuffIcon.h"
#include "ZtMenuV3.h"
#include "StatsAdvance.h"
#include "PetZt.h"
#include "InterfaceZt.h"
#include "MapTeleport.h"
#include "CameraMove.h"
#include "ObjectViewe.h"
#include "MiniMapZt.h"
// ----------------------------------------------------------------------------------------------

#if(ZT_LICENSE==TRUE)

CZtLicense g_ZtLicense;
// ----------------------------------------------------------------------------------------------

static DWORD InterfaceBuffer;

Naked(_00811D69)
{
	_asm
	{
		MOV InterfaceBuffer, EDX
	}

	if(g_ZtLicense.CheckUser(eZtUB::Chebuk))
	{
		if(InterfaceBuffer)
		{
			if(gInterface.CheckWindowZt(ztWinCheckOffAfk))
			{
				gInterface.CloseWindowZt(ztWinCheckOffAfk);
			}
			else
			{
				gInterface.OpenWindowZt(ztWinCheckOffAfk);
			}
		}
	}
	else if(g_ZtLicense.CheckUser(eZtUB::Berlin))
	{
		if(InterfaceBuffer)
		{
			if(gInterface.CheckWindowZt(ztWinDonate))
			{
				gInterface.CloseWindowZt(ztWinDonate);
			}
			else
			{
				gInterface.OpenWindowZt(ztWinDonate);
			}
		}
	}
	else if(g_ZtLicense.m_ZtMenuV2 || g_ZtLicense.m_Achievements)
	{
		if(InterfaceBuffer)
		{
			if(gInterface.CheckWindowZt(ObjWindowsZt::ztWinMiniMenu))//need add check cash shop
			{
				gInterface.CloseWindowZt(ObjWindowsZt::ztWinMiniMenu);
			}
			else
			{
				gInterface.OpenWindowZt(ObjWindowsZt::ztWinMiniMenu);
			}
		}
		else if(gInterface.m_bCashShopOpen)
		{
			gInterface.m_bCashShopOpen = false;
			
			if(g_ZtLicense.CheckUser(eZtUB::Artem) || g_ZtLicense.CheckUser(eZtUB::Artem2))
			{
				if(gObjUser.InSafeZone() && !gInterface.CheckWindow(Shop))
				{
					g_DonateShop.CG_CashSend();
				}
			}
			else
			{
				_asm
				{
					MOV InterfaceBuffer,  0x00811D6F
					JMP InterfaceBuffer
				}
			}
		}
	}
	else
	{
		if(gObjUser.InSafeZone() && !gInterface.CheckWindow(Shop))
		{
			g_DonateShop.CG_CashSend();
		}
	}

	_asm
	{
		MOV InterfaceBuffer,  0x00811F40
		JMP InterfaceBuffer
	}
}

Naked(_007D3C16)
{
	if(g_ZtLicense.CheckUser(eZtUB::Chebuk))
	{
		if(gInterface.CheckWindowZt(ztWinCheckOffAfk))
		{
			gInterface.CloseWindowZt(ztWinCheckOffAfk);
		}
		else
		{
			gInterface.OpenWindowZt(ztWinCheckOffAfk);
		}
	}
	else if(g_ZtLicense.CheckUser(eZtUB::Berlin))
	{
		if(InterfaceBuffer)
		{
			if(gInterface.CheckWindowZt(ztWinDonate))
			{
				gInterface.CloseWindowZt(ztWinDonate);
			}
			else
			{
				gInterface.OpenWindowZt(ztWinDonate);
			}
		}
	}
	else if( g_ZtLicense.m_ZtMenuV2 || g_ZtLicense.m_Achievements )
	{
		if(gInterface.CheckWindowZt(ztWinMiniMenu))
		{
			gInterface.CloseWindowZt(ztWinMiniMenu);
		}
		else
		{
			gInterface.OpenWindowZt(ztWinMiniMenu);
		}
	}
	else 
	{
		if(gObjUser.InSafeZone() && !gInterface.CheckWindow(Shop))
		{
			g_DonateShop.CG_CashSend();
		}
	}

	_asm
	{
		MOV InterfaceBuffer,  0x007D3DF5
		JMP InterfaceBuffer
	}
}

void __declspec(naked) GuildAllieReqv()
{
	static DWORD __jmpTRUE = 0x0078F4AD;
	static DWORD __jmpFALSE = 0x0078F42A;
	static DWORD _UserGuildStatus = 0;

	_asm
	{
		MOV _UserGuildStatus, ECX
	}

	if(_UserGuildStatus == 0x80 || _UserGuildStatus == 0x40)
	{
		_asm
		{
			JMP __jmpTRUE;
		}
	}

	_asm
	{
		JMP __jmpFALSE;
	}
}

CZtLicense::CZtLicense()
{
	//VMBEGIN
	this->Init();
	//VMEND
}
// ----------------------------------------------------------------------------------------------

CZtLicense::~CZtLicense()
{
}
// ----------------------------------------------------------------------------------------------

void CZtLicense::Init()
{
	//VMBEGIN
	this->Enable = true;

	this->TEXTXoR[0] = 0x03;
	this->TEXTXoR[1] = 0x05;
	this->TEXTXoR[2] = 0x08;

	this->URLXoR[0] = 0xA9;
	this->URLXoR[1] = 0xB3;
	this->URLXoR[2] = 0x18;

	this->ActiveUser = -1;

	this->m_Achievements = false;
	this->m_ZtMenuV2 = false;
	this->m_MultiWarehouseType = 0;
	//VMEND
}
// ----------------------------------------------------------------------------------------------

void CZtLicense::Load()
{
	//VMBEGIN
	this->Init();
	//VMEND

}
// ----------------------------------------------------------------------------------------------

void CZtLicense::GCLicenseUser(PMSG_LICENSE_DATA* aRecv)
{
	//VMBEGIN
	this->ActiveUser = aRecv->LicenseUser;
	this->m_SetCustom = aRecv->LicenseCustom;

	this->user.Rage = aRecv->base.Rage;
	this->user.WinQuest = aRecv->base.WinQuest;
	this->user.BloodHound = aRecv->base.BloodHound;
 	this->user.MonsterQuest = aRecv->base.MonsterQuest;
	this->user.TvTEvent = aRecv->base.TvTEvent;
	this->user.GrandHero = aRecv->base.GrandHero;
	this->user.PartySystem = aRecv->base.PartySystem;
	this->user.Brotherhood = aRecv->base.Brotherhood;
	this->user.PartySearch = aRecv->base.PartySearch;
	this->user.ChatLog = aRecv->base.ChatLog;
	this->user.GM_Manager = aRecv->base.GM_Manager;
	this->user.PerosnalStoreZt = aRecv->base.PerosnalStoreZt;
	this->user.PandoraEvent = aRecv->base.PandoraEvent;
	this->user.AntiCheatPlus = aRecv->base.AntiCheatPlus;
	this->user.SpotReturn = aRecv->base.SpotReturn;
	this->user.ComboCustom = aRecv->base.ComboCustom;
	this->user.NpcBuffer = aRecv->base.NpcBuffer;
	this->user.BMQuest = aRecv->base.BMQuest;
	this->user.LoraBattle = aRecv->base.LoraBattle;
	this->user.Smithy = aRecv->base.Smithy;
	this->user.Monster = aRecv->base.Monster;
	this->user.ItemSmokeEffect = aRecv->base.ItemSmokeEffect;
	this->user.GrandDinamicExp = aRecv->base.GrandDinamicExp;
	this->user.PartySave = aRecv->base.PartySave;
	this->user.DisableMasterTree = aRecv->base.DisableMasterTree;
	this->user.OfflineMode = aRecv->base.OfflineMode;
	this->user.bAchievements = aRecv->base.bAchievements;
	this->user.PremiumZt = aRecv->base.PremiumZt;
	this->user.AccSecurity = aRecv->base.AccSecurity;
	this->user.CraftQuestSystem = aRecv->base.CraftQuestSystem;
	this->user.PickUpItemInfo = aRecv->base.PickUpItemInfo;
	this->user.ReferralSystem = aRecv->base.ReferralSystem;

	this->user.FixVieweMonster		= aRecv->base.FixVieweMonster;
	this->user.CustomMapTeleport	= aRecv->base.CustomMapTeleport;
	this->user.CustomCameraMove		= aRecv->base.CustomCameraMove;
	this->user.CustomMiniMapZt		= aRecv->base.CustomMiniMapZt;

	this->config.MaxPartyUser = aRecv->config.MaxPartyUser;
	this->config.PersonalEnable = aRecv->config.PersonalEnable;
	this->config.PersonalBonus = aRecv->config.PersonalBonus;
	this->config.PersonalCredit = aRecv->config.PersonalCredit;

	this->CustomManager();

	if(this->m_SetCustom)
	{
		this->SetCustom(0);
	}
	//VMEND
}
// ----------------------------------------------------------------------------------------------

bool IsMasterClass(BYTE Class)
{
	return false;
}

void CZtLicense::CustomManager()
{
	if(this->user.Monster)
	{ 
		gMonster.Load();
	}
	if(this->user.ItemSmokeEffect)
	{
		gItemSmokeEffect.Load();
	}
	if(this->user.MonsterQuest)
	{
		gMONSTER_QUEST_SYSTEM = true;
	}
	if(this->user.PartySystem)
	{
		gPARTY_SYSTEM = true;
	}
	if(this->user.PartySearch)
	{
		g_PartySearch.Active = true;
	}
	if(this->user.Smithy)
	{
		this->user.Smithy = true;
	}
	if(this->user.Rage)
	{
		gRAGESYSTEM = true;
	}
	if(this->user.WinQuest)
	{
		gWINQUEST = true;
	}
	if(this->user.PerosnalStoreZt && this->config.PersonalEnable)
	{
		g_PersonalShopZt.Load();
		g_PersonalShopZt.iPERSONAL_BONUS = this->config.PersonalBonus;
		g_PersonalShopZt.iPERSONAL_CREDIT = this->config.PersonalCredit;
	}

	g_Smithy.License = this->user.Smithy;

	this->m_Achievements = this->user.bAchievements;

	if(this->user.AccSecurity)
	{
		g_AccountSecurity.m_bEnable = true;
	}

	// ----

	#if(FIX_OBJECT_VIEWE)
	if(g_ZtLicense.user.FixVieweMonster)
	{
		g_ObjectViewe.Load();
	}
	#endif

	#if(CUSTOM_MAP_TELEPORT)
	if(g_ZtLicense.user.CustomMapTeleport)
	{
		g_MapTeleport.Load();
	}
	#endif

	#if(CUSTOM_CAMERA_MOVE)
	if(g_ZtLicense.user.CustomCameraMove)
	{
		g_CameraMove.Load();
	}
	#endif


	#if(ENABLE_MINIMAP_ZT)
	if(g_ZtLicense.user.CustomMiniMapZt)
	{
		g_MiniMapZt.Load();
	}
	
	#endif
	// ----

	//Master Skill Button Disable
	//if(this->user.DisableMasterTree)
	if(!gInterfaceMasterSkill)
	{
		SetRange((LPVOID)0x00784B77, 5, ASM::NOP);
		SetOp((LPVOID)0x00784F79, (LPVOID)IsMasterClass, ASM::CALL);	//  CALL 005878E0		//Master Button Disable
		SetOp((LPVOID)0x007D3916, (LPVOID)IsMasterClass, ASM::CALL);	//  CALL 005878E0		//Master A Key Disable
	}

	g_MaxPartyMember = this->config.MaxPartyUser;

	if( g_ZtLicense.CheckUser(eZtUB::SILVER1) ||
	    g_ZtLicense.CheckUser(eZtUB::SILVER2) )
	{
		gVisualFix.GCVisualInit();
		//SetRange((LPVOID)0x007D3C1C, 5, ASM::NOP);	
		//SetOp((LPVOID)0x007D3C1C, _007D3C16, ASM::JMP);
		////SetRange((LPVOID)0x00811D6F, 5, ASM::NOP);	
		////SetOp((LPVOID)0x00811D6F, _00811D69, ASM::JMP);
		//SetRange((LPVOID)0x00811D69, 6, ASM::NOP);	
		//SetOp((LPVOID)0x00811D69, _00811D69, ASM::JMP);
		SetRange((LPVOID)0x00811D89, 7, ASM::NOP);
		SetRange((LPVOID)0x00811EC5, 5, ASM::NOP);//
		g_AddPoints.Load();

		gChatExpanded.LoadChatZt();
	}

#if(CUSTOM_ADD_POINTS==TRUE)
	if( g_ZtLicense.CheckUser(eZtUB::Gredy) ||
		g_ZtLicense.CheckUser(eZtUB::Gredy2) || 
		g_ZtLicense.CheckUser(eZtUB::GredyLocal) )
	{
		g_AddPoints.Load();
		//SetRange((LPVOID)0x005528DE, 23, ASM::NOP);	//dark lord horse spotikaeca pt damaga reflecta
	}
#endif
	if(g_ZtLicense.CheckUser(eZtUB::Stone))
	{
		SetRange((LPVOID)0x005528D7, 2, ASM::NOP);	//ne kto ne spotikaeca ot damaga i reflecta

		//Credit Shop
		SetRange((LPVOID)0x007D3C1C, 5, ASM::NOP);	
		SetOp((LPVOID)0x007D3C1C, _007D3C16, ASM::JMP);
		SetRange((LPVOID)0x00811D6F, 5, ASM::NOP);	
		SetOp((LPVOID)0x00811D6F, _00811D69, ASM::JMP);
	}
	else if(g_ZtLicense.CheckUser(eZtUB::Stone) || g_ZtLicense.CheckUser(eZtUB::Almdar))
	{
		SetRange((LPVOID)0x005528D7, 2, ASM::NOP);	//ne sko ne spotikaeca ot damaga i reflecta
	}
	else if(g_ZtLicense.CheckUser(eZtUB::Artem) || g_ZtLicense.CheckUser(eZtUB::Artem2))
	{
		//Credit Shop
		SetRange((LPVOID)0x007D3C1C, 5, ASM::NOP);	
		SetOp((LPVOID)0x007D3C1C, _007D3C16, ASM::JMP);
		SetRange((LPVOID)0x00811D6F, 5, ASM::NOP);	
		SetOp((LPVOID)0x00811D6F, _00811D69, ASM::JMP);

		g_AddPoints.Load();

		#if(USER_BUFF_ICON_ZT==TRUE)
		g_BuffIcon.Load();
		#endif
	}
	else if(g_ZtLicense.CheckUser(eZtUB::MU2Play))
	{
		g_AddPoints.Load();
	}
	else if(g_ZtLicense.CheckUser(eZtUB::EpicMU))
	{
		//-> Siege minimap fix
		SetRange((PVOID)0x006505FB, 4, ASM::NOP);
		//-> Fix BC Master Disable
		SetByte((LPVOID)(0x008742AC+3), 0x07);
		SetByte((LPVOID)(0x00874C04+6), 0x07);
		SetRange((LPVOID)(0x00874EBF), 5, ASM::NOP);
		//-> Fix DS Master Disable
		SetByte((LPVOID)(0x00877D8C+3), 0x06);
		SetByte((LPVOID)(0x00878754+6), 0x06);
		SetRange((LPVOID)(0x00878A0F), 5, ASM::NOP);
		SetRange((LPVOID)0x005F7AEA, 27, ASM::NOP);		//Fix Item Pol
		SetByte((LPVOID)(0x005CD192), 0xEB);			//Fix Inventory Pos
		SetRange((LPVOID)0x005528D7, 2, ASM::NOP);		//ne sko ne spotikaeca ot damaga i reflecta

		this->m_ZtMenuV2 = true;

		g_AddPoints.Load();
	}

#if(THINNAKORN_MAC)
	g_AddPoints.Load();

	SetByte((LPVOID)(0x00405B7A+2), 0x91);	//Character delete 400 level
#endif

	if( g_ZtLicense.CheckUser(eZtUB::SILVER1) ||
	    g_ZtLicense.CheckUser(eZtUB::SILVER2) ||
		THINNAKORN_MAC == 1)
	{
		this->m_Achievements = true;
	}

	if( g_ZtLicense.CheckUser(eZtUB::DavitRazmadze) || g_ZtLicense.CheckUser(eZtUB::DavitRazmadze2) || g_ZtLicense.CheckUser(eZtUB::DavitRazmadze3) ||
		g_ZtLicense.CheckUser(eZtUB::MedoniAndrei))
	{
		this->m_ZtMenuV2 = true;
	}

	if(g_ZtLicense.CheckUser(eZtUB::Escalate))
	{
		g_AddPoints.Load();

		//SetRange((LPVOID)0x007D3C1C, 5, ASM::NOP);	
		//SetOp((LPVOID)0x007D3C1C, _007D3C16, ASM::JMP);
		//SetRange((LPVOID)0x00811D69, 6, ASM::NOP);	
		//SetOp((LPVOID)0x00811D69, _00811D69, ASM::JMP);
	}

	if(g_ZtLicense.CheckUser(eZtUB::eternalmu))
	{
		g_AddPoints.Load();
	}

#if(FIX_AGM_REQVALLIANCE==TRUE)
	if(g_ZtLicense.CheckUser(eZtUB::Gredy)		|| 
	   g_ZtLicense.CheckUser(eZtUB::Gredy2)		|| 
	   g_ZtLicense.CheckUser(eZtUB::GredyLocal) || 
	   g_ZtLicense.CheckUser(eZtUB::mu4you)		||
	   g_ZtLicense.CheckUser(eZtUB::NSGames))
	{
		SetOp((LPVOID)0x0078F41E, (LPVOID)GuildAllieReqv, ASM::JMP);	//  CALL 005878E0
		SetRange((LPVOID)0x007E519C, 6, ASM::NOP);	// -> Disable Check ItemAddOption Wings
		//SetRange((LPVOID)0x006D80F0, 2, ASM::NOP);	// -> Fix File Scream Target Block
		//SetByte((LPVOID)(0x006F0B06 + 2), 0xE0);	// -> Fix File Scream Target Block
		//SetByte((LPVOID)(0x006F0B06 + 3), 0x7B);	// -> Fix File Scream Target Block
		SetByte((LPVOID)(0x006F0B51 + 0), 0xE9);
		SetByte((LPVOID)(0x006F0B51 + 1), 0xB4);
		SetByte((LPVOID)(0x006F0B51 + 2), 0x02);
		SetByte((LPVOID)(0x006F0B51 + 3), 0x00);
		SetByte((LPVOID)(0x006F0B51 + 4), 0x00);

		gChatExpanded.LoadChatZt();

		SetByte((LPVOID)0x005C8B42, 0xEB);	//Rena trade
		SetByte((LPVOID)0x005C8881, 0xEB);	//Rena store

		//gInterface.m_ActiveAutoHP = true;

		#if(USER_BUFF_ICON_ZT==TRUE)
		g_BuffIcon.Load();
		#endif
	}
#endif

	if(g_ZtLicense.CheckUser(eZtUB::RevoMU))
	{
		this->m_ZtMenuV2 = true;
		g_AddPoints.Load();
		SetRange((LPVOID)0x005528D7, 2, ASM::NOP);	//ne kto ne spotikaeca ot damaga i reflecta
		SetRange((PVOID)0x006505FB, 4, ASM::NOP);	//-> Siege minimap fix

		gChatExpanded.LoadChatZt();
	}
#if(ENABLE_CHATCOLOR)
	//gChatExpanded.LoadChatZt();
#endif
	// ----
	#if(ENABLE_ITEMSETOPTION)
	if( g_ZtLicense.CheckUser(eZtUB::Gredy) || 
		g_ZtLicense.CheckUser(eZtUB::Gredy2) || 
		g_ZtLicense.CheckUser(eZtUB::GredyLocal) ||
		g_ZtLicense.CheckUser(eZtUB::masonX) || g_ZtLicense.CheckUser(eZtUB::masonX2)||
		g_ZtLicense.CheckUser(eZtUB::ulasevich) || g_ZtLicense.CheckUser(eZtUB::ulasevich2) ||
		g_ZtLicense.CheckUser(eZtUB::Escalate) || g_ZtLicense.CheckUser(eZtUB::mu4you) ||
		g_ZtLicense.CheckUser(eZtUB::eternalmu) || g_ZtLicense.CheckUser(eZtUB::NSGames))
	{
		g_ItemSetOption.Load();
	}
	#endif
	// ----
	if(g_ZtLicense.CheckUser(eZtUB::masonX) || g_ZtLicense.CheckUser(eZtUB::masonX2))
	{
		g_AddPoints.Load();
	}
	// ----
	if(g_ZtLicense.CheckUser(eZtUB::GloryMU))
	{
		//this->m_ZtMenuV2 = true;

		//SetRange((LPVOID)0x005F7AEA, 27, ASM::NOP);		//Fix Item Pol
		//SetByte((LPVOID)(0x005CD192), 0xEB);		 	//Fix Inventory Pos

		SetRange((LPVOID)0x005528D7, 2, ASM::NOP);		//ne kto ne spotikaeca ot damaga i reflecta	
		SetRange((PVOID)0x006505FB, 4, ASM::NOP);		//-> Siege minimap fix		

		g_AddPoints.Load();
		gChatExpanded.LoadChatZt();
		g_ItemSetOption.Load();
		#if(USER_BUFF_ICON_ZT==TRUE)
		g_BuffIcon.Load();
		#endif

		//this->DisableMasterEvent();
	}
	// ----
	if(g_ZtLicense.CheckUser(eZtUB::ArcMu))
	{
		g_AddPoints.Load();
		#if(USER_BUFF_ICON_ZT==TRUE)
		g_BuffIcon.Load();
		#endif
	}

	if(g_ZtLicense.CheckUser(eZtUB::MedoniAndrei))
	{
		g_AddPoints.Load();
	}

	if(g_ZtLicense.CheckUser(eZtUB::mu4you))
	{
		g_AddPoints.Load();
		#if(USER_BUFF_ICON_ZT==TRUE)
		g_BuffIcon.Load();
		#endif
		gChatExpanded.LoadChatZt();

		SetRange((LPVOID)0x0095DE51, 2, ASM::NOP);	//MUHelper Inventory 1
		SetByte((LPVOID)(0x0095CE90), 0xEB);		//MUHelper Inventory 2

		SetRange((PVOID)0x006505FB, 4, ASM::NOP);		//-> Siege minimap fix	

		gVisualFix.GCVisualInit();
	}

	if(g_ZtLicense.CheckUser(eZtUB::eternalmu))
	{
		#if(USER_BUFF_ICON_ZT==TRUE)
		g_BuffIcon.Load();
		#endif
		#if(DEV_ZTMENU_V3)
		g_ZtMenuV3.Load(ZTMENU_NUMBER::eVERSION_CHEBUK);
		#endif
	}

	if(g_ZtLicense.CheckUser(eZtUB::WarBorn))
	{
		#if(USER_BUFF_ICON_ZT==TRUE)
		g_BuffIcon.Load();
		#endif

	}

	if(g_ZtLicense.CheckUser(eZtUB::NSGames))	//поис?всех мест гд?подключения есть по этой лицензии
	{
		g_AddPoints.Load();
		#if(USER_BUFF_ICON_ZT==TRUE)
		g_BuffIcon.Load();
		#endif
		gChatExpanded.LoadChatZt();

		SetRange((LPVOID)0x0095DE51, 2, ASM::NOP);	//MUHelper Inventory 1
		SetByte((LPVOID)(0x0095CE90), 0xEB);		//MUHelper Inventory 2

		SetRange((PVOID)0x006505FB, 4, ASM::NOP);		//-> Siege minimap fix	

		gVisualFix.GCVisualInit();

		#if(DEV_ZTMENU_V3)
		g_ZtMenuV3.Load(ZTMENU_NUMBER::eVERSION_NS);
		#endif

		#if(DEV_STATS_ADVANCE)
		g_StatsAdvance.Load();
		#endif

		//InitInterZt();

		//char szSerial[17];
		//memset(szSerial, 0, sizeof(szSerial));
		//sprintf(szSerial, "01332jcEX48mxL3b");
		//WriteMemory((PDWORD)SERIAL_MAIN, szSerial, sizeof(szSerial));
	}

	if(g_ZtLicense.CheckUser(eZtUB::MuPrime))
	{

		#if(MANGOL_DEV)
		SetByte((LPVOID)0x007D280C, 0xEB);
		SetByte((LPVOID)0x007D3FCF, 0xEB);
		#endif
	}


	#if(DEV_ZTMENU_V3)
	if(g_ZtLicense.CheckUser(eZtUB::Chebuk))
	{
		SetRange((LPVOID)0x007D3C1C, 5, ASM::NOP);	
		SetOp((LPVOID)0x007D3C1C, _007D3C16, ASM::JMP);
		SetRange((LPVOID)0x00811D6F, 5, ASM::NOP);	
		SetOp((LPVOID)0x00811D6F, _00811D69, ASM::JMP);

		g_ZtMenuV3.Load(ZTMENU_NUMBER::eVERSION_CHEBUK);

		this->user.PremiumZt = false;
		this->user.Smithy = false;
		
	}
	#endif

#if(CUSTOM_POSTITEM)
	gInterface.LoadItemPost();
#endif

#if(LICENSE_MUEVIL)
	SetRange((LPVOID)0x0095DE51, 2, ASM::NOP);	//MUHelper Inventory 1
	SetByte((LPVOID)(0x0095CE90), 0xEB);		//MUHelper Inventory 2
#endif



	if( g_ZtLicense.m_ZtMenuV2 || g_ZtLicense.m_Achievements )
	{
		#if(DEV_ZTMENU_V3)
		if(!g_ZtMenuV3.m_Enable)
		{
			SetRange((LPVOID)0x007D3C1C, 5, ASM::NOP);	
			SetOp((LPVOID)0x007D3C1C, _007D3C16, ASM::JMP);
			SetRange((LPVOID)0x00811D69, 6, ASM::NOP);	
			SetOp((LPVOID)0x00811D69, _00811D69, ASM::JMP);
		}
		#endif
	}

	if(g_ZtLicense.CheckUser(eZtUB::ulasevich) || g_ZtLicense.CheckUser(eZtUB::ulasevich2))
	{
		#if(USER_BUFF_ICON_ZT==TRUE)
		g_BuffIcon.Load();
		#endif	

		gChatExpanded.LoadChatZt();

		g_AddPoints.Load();

		SetRange((LPVOID)0x007E519C, 6, ASM::NOP);	// -> Disable Check ItemAddOption Wings

		SetRange((LPVOID)0x005528DE, 23, ASM::NOP);	// dark lord horse spotikaeca pt damaga reflecta

		//Fix File Scream Target Block
		SetByte((LPVOID)(0x006F0B51 + 0), 0xE9);
		SetByte((LPVOID)(0x006F0B51 + 1), 0xB4);
		SetByte((LPVOID)(0x006F0B51 + 2), 0x02);
		SetByte((LPVOID)(0x006F0B51 + 3), 0x00);
		SetByte((LPVOID)(0x006F0B51 + 4), 0x00);
	}

	// ------------------------------------
	if(g_ZtLicense.CheckUser(eZtUB::Local))
	{
		g_AddPoints.Load();
		#if(USER_BUFF_ICON_ZT==TRUE)
		g_BuffIcon.Load();
		#endif
		gChatExpanded.LoadChatZt();
		SetRange((LPVOID)0x0095DE51, 2, ASM::NOP);	//	MUHelper Inventory 1
		SetByte((LPVOID)(0x0095CE90), 0xEB);		//	MUHelper Inventory 2
		SetRange((PVOID)0x006505FB, 4, ASM::NOP);	//  Siege minimap fix	
		gVisualFix.GCVisualInit();
		#if(DEV_STATS_ADVANCE)
		g_StatsAdvance.Load();
		#endif
	}
	// ------------------------------------

	#if(ENABLE_AGMASTER)
	if(g_ZtLicense.CheckUser(eZtUB::MUDev))
	{
		SetOp((LPVOID)0x0078F41E, (LPVOID)GuildAllieReqv, ASM::JMP);
		//char __stdcall sub_78FA80(int a1) -> Alliance recv
		//0078F649 -> alli send
		//0078F774 -> alli send

		/*----------------------------
			=>	GUILD MASTER
		  ----------------------------
			00474200  CMP ECX,80
			00475161  CMP ECX,80
			00475AC6  CMP ECX,80
			00475CAA  CMP ECX,80
			00476699  CMP ECX,80
			00477821  CMP ECX,80
			004779E2  CMP ECX,80
			005967BE  CMP ECX,80
			005993AE  CMP ECX,80
			00640312  CMP ECX,80
			0078F41E  CMP ECX,80
			0078F63D  CMP ECX,80
			0078F7FE  CMP ECX,80
			0078FAAD  CMP ECX,80
			0078FE71  CMP ECX,80
			007CA923  CMP ECX,80
			007CAA00  CMP ECX,80
			007CAC70  CMP ECX,80
			00958D6B  CMP ECX,80
			00958DE9  CMP ECX,80
			00A35DBC  CMP ECX,80
			00A40BC4  CMP ECX,80
			00A412B4  CMP ECX,80
			00A42CE6  CMP ECX,80
			00AB5D5A  CMP ECX,80
			00AB5E2F  CMP ECX,80
			00B6883A  CMP ECX,80
			00C3EB31  CMP ECX,80
		   ----------------------------*/
	}
	#endif

	#if(CUSTOM_VALUE_MENU)
	if(/*g_ZtLicense.CheckUser(eZtUB::NSGames) ||*/ g_ZtLicense.CheckUser(eZtUB::Artem) || g_ZtLicense.CheckUser(eZtUB::Artem2) ||
	   g_ZtLicense.CheckUser(eZtUB::Gredy)	 ||  g_ZtLicense.CheckUser(eZtUB::Gredy2) || g_ZtLicense.CheckUser(eZtUB::GredyLocal) || 
	   g_ZtLicense.CheckUser(eZtUB::WarBorn))
	{
		this->m_MultiWarehouseType = 1;
	}
	#endif

	if(g_ZtLicense.CheckUser(eZtUB::Thinnakorn))
	{
		/*LoadLibrary("vcorp.dll");*/
	}


}
// ----------------------------------------------------------------------------------------------

bool CZtLicense::CheckUser(int NeedUser)
{
	//VMBEGIN
	if(this->ActiveUser == NeedUser)
	{
		return true;
	}
	return false;
	//VMEND
}
// ----------------------------------------------------------------------------------------------

char* CZtLicense::GetDecText(char* EncodeChar)
{
	//VMBEGIN
	int len = strlen(EncodeChar);	
	char* Line = new char[len+1];
	for(int i = 0; i < len; i++)
	{
		Line[i] = char(EncodeChar[i] ^ this->TEXTXoR[i % 3]);
	}
	Line[len] = 0;
	return Line;
	//VMEND
}
// ----------------------------------------------------------------------------------------------

void CZtLicense::GCAttackEnable(PMSG_GC_ATTACK* lpMsg)
{

}

void CZtLicense::GCAttackDisable()
{

}

void CZtLicense::GC_UserConfigRecv(PMSG_USERCONFIG * lpMsg)
{
	gInterface.m_ActiveAutoHP = false;
	gInterface.m_AutoHP = false;

	memcpy(&g_ZtLicense.m_EvoConfig, &lpMsg->EvoConfig, sizeof(g_ZtLicense.m_EvoConfig));

	if(g_ZtLicense.CheckUser(eZtUB::Gredy) || g_ZtLicense.CheckUser(eZtUB::Gredy2) || g_ZtLicense.CheckUser(eZtUB::GredyLocal))
	{
		gInterface.m_ActiveAutoHP = g_ZtLicense.m_EvoConfig.HPAutoClicker;
	}
}

void CZtLicense::DisableMasterEvent()
{
	//-> Fix BC Master Disable
	SetByte((LPVOID)(0x008742AC+3), 0x07);
	SetByte((LPVOID)(0x00874C04+6), 0x07);
	SetRange((LPVOID)(0x00874EBF), 5, ASM::NOP);
	//-> Fix DS Master Disable
	SetByte((LPVOID)(0x00877D8C+3), 0x06);
	SetByte((LPVOID)(0x00878754+6), 0x06);
	SetRange((LPVOID)(0x00878A0F), 5, ASM::NOP);

	SetOp((LPVOID)0x0063DDF2, (LPVOID)IsMasterClass, ASM::CALL);//
	SetOp((LPVOID)0x0063DF89, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x0063E5F2, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x0063EA4C, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x0064A79A, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x0064A85F, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x0064AB3D, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x0064AC02, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x0064CA0C, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	
	SetOp((LPVOID)0x0064CDE9, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x0064CF5F, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x00651674, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x00656E03, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x0077EFD0, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x0077F9A9, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x0077FBC8, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x00782C5A, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x00783032, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	
	SetOp((LPVOID)0x00784F79, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0		//Master Button Disable
	SetOp((LPVOID)0x007D3916, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0		//Master A Key Disable
	SetOp((LPVOID)0x007E4B19, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x007E4B8F, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x0080F8D9, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0

	SetOp((LPVOID)0x00810019, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x008102E9, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x008105CB, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x0081064B, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x00869213, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0

	SetOp((LPVOID)0x0087455B, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x0087862E, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x00878661, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x0095DFAF, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x0095E090, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x0095E1F0, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x00968450, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x009684A6, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x009684EF, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
}

void CZtLicense::SetCustom(int ListID)
{
	this->m_SetCustom = 1;

	if(gInterfaceChat)
	{
		gChatExpanded.LoadChatZt();
	}

	g_AddPoints.Load();

	#if(USER_BUFF_ICON_ZT==TRUE)
	if(gInterfaceBuffIcon)
	{
		g_BuffIcon.Load();
	}
	#endif
		
	gVisualFix.GCVisualInit();

	#if(DEV_STATS_ADVANCE)
	g_StatsAdvance.Load();
	#endif

	SetRange((LPVOID)0x0095DE51, 2, ASM::NOP);	//	MUHelper Inventory 1
	SetByte((LPVOID)(0x0095CE90), 0xEB);		//	MUHelper Inventory 2
	SetRange((PVOID)0x006505FB, 4, ASM::NOP);	//  Siege minimap fix	

	this->m_MultiWarehouseType = 1;
}

int CZtLicense::GetCustom()
{
	return this->m_SetCustom;
}
#endif
