#include "stdafx.h"
#include "MiniMenu.h"
#include "Interface.h"
#include "Console.h"
#include "DonateShop.h"
#include "PartySearch.h"
#include "User.h"
#include "Protocol.h"
#include "PersonalShopZt.h"
#include "Achievements.h"
#include "Configs.h"
#include "Ranking.h"
#include "EventTimer.h"
#include "AutoParty.h"
#include "ZtLicense.h"
#include "NewParty.h"
#include "Settings.h"
#include "Camera.h"
#include "Configs.h"
#include "JewelsBank.h"
#include "QuestSystem.h"
#include "DataSend.h"
#include "ReferralSystem.h"
#include "ZtText.h"
#include "ZtMenuV3.h"
#include "PremiumSystemZt.h"

#if(DEV_ZTMENU_V3)

CZtMenuV3 g_ZtMenuV3;

CZtMenuV3::CZtMenuV3()
{
	this->Init();
}

CZtMenuV3::~CZtMenuV3()
{
}

void CZtMenuV3::Init()
{
	this->m_Enable = false;
	this->m_Version = ZTMENU_NUMBER::eVERSION_NO;
}

void CZtMenuV3::LoadIMG()
{
	gInterface.LoadImages("ZtData\\Interface\\newui_btn_mini.tga", zt_ZTMENU3_BUTTON_01, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Interface\\server_menu_b_all.tga", zt_ZTMENU3_BUTTON_02, 0x2601, 0x2900, 1);

	gInterface.LoadImages("ZtData\\Interface\\MenuV3\\menu.tga", zt_ZTMENU3_BUTTON_03, 0x2601, 0x2900, 1);
	
}

void CZtMenuV3::Bind()
{
	//gInterface.BindObject(eZTMENU3_MENU, 0x7BAC, 168, 18, -1, -1);

	gInterface.BindObject(eZTMENU3_MAIN, 0x7A5A, 222, 435, -1, -1);	//230
	gInterface.BindObject(eZTMENU3_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eZTMENU3_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eZTMENU3_FOOTER, 0x7A59, 230, 50, -1, -1);

	gInterface.BindObject(eZTMENU3_BUTTON_01, zt_ZTMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eZTMENU3_BUTTON_02, zt_ZTMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eZTMENU3_BUTTON_03, zt_ZTMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eZTMENU3_BUTTON_04, zt_ZTMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eZTMENU3_BUTTON_05, zt_ZTMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eZTMENU3_BUTTON_06, zt_ZTMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eZTMENU3_BUTTON_07, zt_ZTMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eZTMENU3_BUTTON_08, zt_ZTMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eZTMENU3_BUTTON_09, zt_ZTMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eZTMENU3_BUTTON_10, zt_ZTMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eZTMENU3_BUTTON_11, zt_ZTMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eZTMENU3_BUTTON_12, zt_ZTMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eZTMENU3_BUTTON_13, zt_ZTMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eZTMENU3_BUTTON_14, zt_ZTMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eZTMENU3_BUTTON_15, zt_ZTMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eZTMENU3_BUTTON_16, zt_ZTMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eZTMENU3_BUTTON_17, zt_ZTMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eZTMENU3_BUTTON_18, zt_ZTMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eZTMENU3_BUTTON_19, zt_ZTMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eZTMENU3_BUTTON_20, zt_ZTMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eZTMENU3_BUTTON_21, zt_ZTMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eZTMENU3_BUTTON_22, zt_ZTMENU3_BUTTON_01, 108, 24, -1, -1);

	gInterface.BindObject(eZTMENU3_BUTTON_CHEBUK, 0x7A5E, 108, 29, -1, -1);
}

void CZtMenuV3::Load(ZTMENU_NUMBER Number)
{
	this->m_Enable = true;
	this->m_Version = Number;

	if(this->m_Version == ZTMENU_NUMBER::eVERSION_NS)
	{
		#if(ENABLE_VERSION_ME)
		float StartX = 492;
		float StartY = 365;
		gInterface.BindObject(eZTMENU3_MENU, zt_ZTMENU3_BUTTON_03, 48, 14, StartX, StartY);
		#else
		//gInterface.BindObject(eZTMENU3_MENU, 0x7BAC, 168, 18, -1, -1);
		//gInterface.BindObject(eZTMENU3_MENU, 0x7A5E, 108, 29, -1, -1);
		gInterface.BindObject(eZTMENU3_MENU, zt_ZTMENU3_BUTTON_03, 48, 14, -1, -1);
		#endif
	}
	else if(this->m_Version == ZTMENU_NUMBER::eVERSION_ET)
	{
		gInterface.BindObject(eZTMENU3_MENU, zt_ZTMENU3_BUTTON_02, 53, 27, -1, -1);
	}	
	else if(this->m_Version == ZTMENU_NUMBER::eVERSION_WB)
	{
		// ----
	}	
	else if(this->m_Version == ZTMENU_NUMBER::eVERSION_CHEBUK)
	{
		gInterface.BindObject(eZTMENU3_MENU, 0x7A5E, 108, 29, -1, -1);
	}	
	//eZTMENU3_MENU
}

void CZtMenuV3::DrawMain()
{
	if(!this->m_Enable)
	{
		return;
	}

	if(pPlayerState != GameProcess)
	{
		return;
	}

	if(gInterface.CheckWindow(ObjWindow::CashShop)  || 
	   gInterface.CheckWindow(ObjWindow::FullMap)   || 
	   gInterface.CheckWindow(ObjWindow::SkillTree) || 
	   gInterface.CheckWindow(ObjWindow::MoveList))
	{
		return;
	}

	#if(ENABLE_VERSION_ME)
	if(gInterface.IsWorkZone(eZTMENU3_MENU))
	{
		pSetCursorFocus = true;
	}
	#endif

	if(this->m_Version == ZTMENU_NUMBER::eVERSION_NS)
	{
		this->DrawMenu();
		this->DrawWindow();
		//this->DrawWindowChebuk();
		//this->DrawMenuChebuk();
	}
	else if(this->m_Version == ZTMENU_NUMBER::eVERSION_ET)
	{
//		#if(USERPANEL)
//        gInterface.DrawUsersPanel();
//		#endif
		this->DrawWindow2();
#if(ENABLR_DEN_DEV)
		this->DrawMenu2();
#endif

	}	
	else if(this->m_Version == ZTMENU_NUMBER::eVERSION_WB)
	{
		// ----
	}	
	else if(this->m_Version == ZTMENU_NUMBER::eVERSION_CHEBUK)
	{
		this->DrawWindowChebuk();
		this->DrawMenuChebuk();
	}	
}

void CZtMenuV3::DrawMenu()
{
	if(gInterface.CheckWindow(ObjWindow::CommandWindow))
	{
		return;
	}

	if(gEventTimer.Show)
	{
		return;
	}

	if(gRanking.Show)
	{
		return;
	}

	float StartY = 16.0;
	float StartX = 10;
	DWORD dwColor = eGray100;

	StartX = 3;
	StartY += 65;

	gInterface.DrawGUI(eZTMENU3_MENU, StartX , StartY);

	if(gInterface.IsWorkZone(eZTMENU3_MENU))
	{
		if(gInterface.Data[eZTMENU3_MENU].OnClick)
		{
			dwColor = eGray150;
		}

		gInterface.DrawColoredGUI(eZTMENU3_MENU, gInterface.Data[eZTMENU3_MENU].X, gInterface.Data[eZTMENU3_MENU].Y, dwColor);
	}

	/*
	if(gInterface.IsWorkZone(eZTMENU3_MENU))
	{
		gInterface.DrawFormat(eWhite, StartX, StartY + 10, 168, 3, "Menu");
	}
	else
	{
		gInterface.DrawFormat(eWhite, StartX, StartY + 10, 168, 3, "Menu");
	}
	*/


	//debug
	//gInterface.DrawFormat(eBlack, pCursorX, pCursorY, 100, 3, "%d - %d, ", pCursorX, pCursorY);
}

void CZtMenuV3::DrawMenuChebuk()
{
	if(!gInterface.CheckWindow(ObjWindow::CommandWindow))
	{
		return;
	}

	float StartX			= 492;
	float StartY			= 365;

	//gInterface.DrawFormat(eYellow, pCursorX, pCursorY, 100, 3, "%d - %d, ", pCursorX, pCursorY);

	gInterface.DrawGUI(eZTMENU3_MENU, StartX , StartY);

	if(gInterface.IsWorkZone(eZTMENU3_MENU))
	{
		gInterface.DrawFormat(eYellow, StartX, StartY + 10, 108, 3, "Menu");
		//gInterface.DrawFormat(eYellow, StartX, StartY + 3, 168, 3, "Menu");
		gInterface.DrawColoredGUI(eZTMENU3_MENU, StartX, StartY, eGray100);
	}
	else
	{
		//gInterface.DrawFormat(eAncient, StartX, StartY + 3, 168, 3, "Menu");
		gInterface.DrawFormat(eYellow, StartX, StartY + 10, 108, 3, "Menu");
	}


}

void CZtMenuV3::DrawWindow()
{
	if(!gInterface.CheckWindowZt(ObjWindowsZt::ztWinMenuV3))
	{
		return;
	}

	pSetCursorFocus = true;

	float StartY = 18.0;
	float StartX = 0;

	#if(DEV_VALERIY_CHIBUK)
	if(g_ZtLicense.CheckUser(eZtUB::Chebuk))
	{
			pDrawGUI(0x7A5A, StartX, StartY, 190, 420);
		///	gInterface.BindObject(eSMITHY_MAIN, 0x7A5A, 222, 303 + 18, -1, -1);
	}
	else
	{
		pDrawColorButton(0x7880, StartX, StartY, 190, 420, NULL, NULL, Color4f(33, 19, 10, 255));
	}
	#else
	//pDrawColorButton(0x7880, StartX, StartY, 190, 420, NULL, NULL, Color4f(0, 0, 0, 150));
	pDrawColorButton(0x7880, StartX, StartY, 190, 420, NULL, NULL, Color4f(33, 19, 10, 255));
	#endif
	

	float flDrawX = StartX + 42.5;
	float flDrawY = StartY + 20;

	// ====
	/*
	flDrawY = this->DrawButon("New button 1", eZTMENU3_BUTTON_01, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 2", eZTMENU3_BUTTON_02, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 3", eZTMENU3_BUTTON_03, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 4", eZTMENU3_BUTTON_04, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 5", eZTMENU3_BUTTON_05, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 6", eZTMENU3_BUTTON_06, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 7", eZTMENU3_BUTTON_07, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 8", eZTMENU3_BUTTON_08, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 9", eZTMENU3_BUTTON_09, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 10", eZTMENU3_BUTTON_10, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 11", eZTMENU3_BUTTON_11, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 12", eZTMENU3_BUTTON_12, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 13", eZTMENU3_BUTTON_13, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 14", eZTMENU3_BUTTON_14, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 15", eZTMENU3_BUTTON_15, flDrawX, flDrawY);
	*/
	// ====

	// =====================================================================

	if(g_ZtLicense.CheckUser(eZtUB::NSGames))
	{
		flDrawY = this->DrawButton("Vote for Server", eZTMENU3_BUTTON_20, flDrawX, flDrawY);

		flDrawY = this->DrawButton("Donate Shop", eZTMENU3_BUTTON_21, flDrawX, flDrawY);
	}

	if(g_ZtLicense.CheckUser(eZtUB::GloryMU))
	{
		flDrawY = this->DrawButton("Buy Credits", eZTMENU3_BUTTON_20, flDrawX, flDrawY);

		flDrawY = this->DrawButton("Donate Shop", eZTMENU3_BUTTON_21, flDrawX, flDrawY);
	}

	//flDrawY = this->DrawButton(g_ZtText.GetText(183), eZTMENU3_BUTTON_01, flDrawX, flDrawY);

	if(g_ZtLicense.m_Achievements)
	{
		flDrawY = this->DrawButton("Achievements", eZTMENU3_BUTTON_02, flDrawX, flDrawY);

		flDrawY = this->DrawButton("Power", eZTMENU3_BUTTON_03, flDrawX, flDrawY);
	}

	if(g_ZtLicense.user.AccSecurity)
	{
		if(g_ZtLicense.CheckUser(eZtUB::Gredy) || g_ZtLicense.CheckUser(eZtUB::GredyLocal) || g_ZtLicense.CheckUser(eZtUB::Gredy2))
		{
		}
		else
		{
			flDrawY = this->DrawButton("Account Security", eZTMENU3_BUTTON_18, flDrawX, flDrawY);
		}
	}

	if(g_ZtLicense.user.PremiumZt)
	{
		flDrawY = this->DrawButton("Premium System", eZTMENU3_BUTTON_19, flDrawX, flDrawY);
	}

	flDrawY = this->DrawButton("Options", eZTMENU3_BUTTON_04, flDrawX, flDrawY);

	flDrawY = this->DrawButton("3D Camera [Reset]", eZTMENU3_BUTTON_05, flDrawX, flDrawY);

	flDrawY = this->DrawButton("Jewels Bank", eZTMENU3_BUTTON_06, flDrawX, flDrawY);

	if(gRAGESYSTEM)
	{
		flDrawY = this->DrawButton("Rage System", eZTMENU3_BUTTON_07, flDrawX, flDrawY);
	}

	if(gWINQUEST)
	{
		flDrawY = this->DrawButton("Quest", eZTMENU3_BUTTON_08, flDrawX, flDrawY);
		flDrawY = this->DrawButton("Quest Options", eZTMENU3_BUTTON_09, flDrawX, flDrawY);
	}

	flDrawY = this->DrawButton("Offline Attack", eZTMENU3_BUTTON_10, flDrawX, flDrawY);

	if(gRanking.Active)
	{
		flDrawY = this->DrawButton("Top 100 Player", eZTMENU3_BUTTON_11, flDrawX, flDrawY);
	}

	if(gEventTimer.Active)
	{
		flDrawY = this->DrawButton("Events Timer", eZTMENU3_BUTTON_12, flDrawX, flDrawY);
	}

	#if(CUSTOM_PARTY_SEARCH==TRUE)
	if(g_PartySearch.Active)
	{
		flDrawY = this->DrawButton("Auto Party", eZTMENU3_BUTTON_13, flDrawX, flDrawY);
	}
	#endif

	if(g_PartySearch.Active)
	{
		flDrawY = this->DrawButton("Party Search List", eZTMENU3_BUTTON_14, flDrawX, flDrawY);
	}
	else
	{
		if(gAutoParty.Active)
		{
			flDrawY = this->DrawButton("Auto Party List", eZTMENU3_BUTTON_15, flDrawX, flDrawY);
		}
	}

	if(g_ZtLicense.user.Smithy == true)
	{
		flDrawY = this->DrawButton("Smithy", eZTMENU3_BUTTON_16, flDrawX, flDrawY);
	}

	if(g_ZtLicense.CheckUser(eZtUB::Local) || g_ZtLicense.CheckUser(eZtUB::Gredy) || 
		g_ZtLicense.CheckUser(eZtUB::GredyLocal) || g_ZtLicense.CheckUser(eZtUB::Gredy2) || 
		THINNAKORN_MAC == 1 || g_ZtLicense.CheckUser(eZtUB::MedoniAndrei))
	{
		flDrawY = this->DrawButton("Custom", eZTMENU3_BUTTON_17, flDrawX, flDrawY);
	}
}


void CZtMenuV3::DrawWindowChebuk()
{
	if(!gInterface.CheckWindowZt(ObjWindowsZt::ztWinMenuV3))
	{
		return;
	}

	pSetCursorFocus = true;

	float StartY = 18.0;
	float StartX = 0;

	#if(DEV_VALERIY_CHIBUK)
	if(g_ZtLicense.CheckUser(eZtUB::Chebuk))
	{
			pDrawGUI(0x7A5A, StartX, StartY, 190, 420);
		///	gInterface.BindObject(eSMITHY_MAIN, 0x7A5A, 222, 303 + 18, -1, -1);
	}
	else
	{
		pDrawColorButton(0x7880, StartX, StartY, 190, 420, NULL, NULL, Color4f(33, 19, 10, 255));
	}
	#else
	//pDrawColorButton(0x7880, StartX, StartY, 190, 420, NULL, NULL, Color4f(0, 0, 0, 150));
	pDrawColorButton(0x7880, StartX, StartY, 190, 420, NULL, NULL, Color4f(33, 19, 10, 255));
	#endif
	

	float flDrawX = StartX + 42.5;
	float flDrawY = StartY + 20;

	// ====
	/*
	flDrawY = this->DrawButon("New button 1", eZTMENU3_BUTTON_01, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 2", eZTMENU3_BUTTON_02, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 3", eZTMENU3_BUTTON_03, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 4", eZTMENU3_BUTTON_04, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 5", eZTMENU3_BUTTON_05, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 6", eZTMENU3_BUTTON_06, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 7", eZTMENU3_BUTTON_07, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 8", eZTMENU3_BUTTON_08, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 9", eZTMENU3_BUTTON_09, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 10", eZTMENU3_BUTTON_10, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 11", eZTMENU3_BUTTON_11, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 12", eZTMENU3_BUTTON_12, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 13", eZTMENU3_BUTTON_13, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 14", eZTMENU3_BUTTON_14, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 15", eZTMENU3_BUTTON_15, flDrawX, flDrawY);
	*/
	// ====

	// =====================================================================

	if(g_ZtLicense.CheckUser(eZtUB::NSGames))
	{
		flDrawY = this->DrawButton("Vote for Server", eZTMENU3_BUTTON_20, flDrawX, flDrawY);

		flDrawY = this->DrawButton("Donate Shop", eZTMENU3_BUTTON_21, flDrawX, flDrawY);
	}

	if(g_ZtLicense.CheckUser(eZtUB::GloryMU))
	{
		flDrawY = this->DrawButton("Buy Credits", eZTMENU3_BUTTON_20, flDrawX, flDrawY);

		flDrawY = this->DrawButton("Donate Shop", eZTMENU3_BUTTON_21, flDrawX, flDrawY);
	}

	//flDrawY = this->DrawButton(g_ZtText.GetText(183), eZTMENU3_BUTTON_01, flDrawX, flDrawY);

	if(g_ZtLicense.m_Achievements)
	{
		flDrawY = this->DrawButton("Achievements", eZTMENU3_BUTTON_02, flDrawX, flDrawY);

		flDrawY = this->DrawButton("Power", eZTMENU3_BUTTON_03, flDrawX, flDrawY);
	}

	if(g_ZtLicense.user.AccSecurity)
	{
		if(g_ZtLicense.CheckUser(eZtUB::Gredy) || g_ZtLicense.CheckUser(eZtUB::GredyLocal) || g_ZtLicense.CheckUser(eZtUB::Gredy2))
		{
		}
		else
		{
			flDrawY = this->DrawButton("Account Security", eZTMENU3_BUTTON_18, flDrawX, flDrawY);
		}
	}

	if(g_ZtLicense.user.PremiumZt)
	{
		flDrawY = this->DrawButton("Premium System", eZTMENU3_BUTTON_19, flDrawX, flDrawY);
	}

	flDrawY = this->DrawButton("Options", eZTMENU3_BUTTON_04, flDrawX, flDrawY);

	flDrawY = this->DrawButton("3D Camera [Reset]", eZTMENU3_BUTTON_05, flDrawX, flDrawY);

	flDrawY = this->DrawButton("Jewels Bank", eZTMENU3_BUTTON_06, flDrawX, flDrawY);

	if(gRAGESYSTEM)
	{
		flDrawY = this->DrawButton("Rage System", eZTMENU3_BUTTON_07, flDrawX, flDrawY);
	}

	if(gWINQUEST)
	{
		flDrawY = this->DrawButton("Quest", eZTMENU3_BUTTON_08, flDrawX, flDrawY);
		flDrawY = this->DrawButton("Quest Options", eZTMENU3_BUTTON_09, flDrawX, flDrawY);
	}

	flDrawY = this->DrawButton("Offline Attack", eZTMENU3_BUTTON_10, flDrawX, flDrawY);

	if(gRanking.Active)
	{
		flDrawY = this->DrawButton("Top 100 Player", eZTMENU3_BUTTON_11, flDrawX, flDrawY);
	}

	if(gEventTimer.Active)
	{
		flDrawY = this->DrawButton("Events Timer", eZTMENU3_BUTTON_12, flDrawX, flDrawY);
	}

	#if(CUSTOM_PARTY_SEARCH==TRUE)
	if(g_PartySearch.Active)
	{
		flDrawY = this->DrawButton("Auto Party", eZTMENU3_BUTTON_13, flDrawX, flDrawY);
	}
	#endif

	if(g_PartySearch.Active)
	{
		flDrawY = this->DrawButton("Party Search List", eZTMENU3_BUTTON_14, flDrawX, flDrawY);
	}
	else
	{
		if(gAutoParty.Active)
		{
			flDrawY = this->DrawButton("Auto Party List", eZTMENU3_BUTTON_15, flDrawX, flDrawY);
		}
	}

	if(g_ZtLicense.user.Smithy == true)
	{
		flDrawY = this->DrawButton("Smithy", eZTMENU3_BUTTON_16, flDrawX, flDrawY);
	}

	if(g_ZtLicense.CheckUser(eZtUB::Local) || g_ZtLicense.CheckUser(eZtUB::Gredy) || 
		g_ZtLicense.CheckUser(eZtUB::GredyLocal) || g_ZtLicense.CheckUser(eZtUB::Gredy2) || 
		THINNAKORN_MAC == 1 || g_ZtLicense.CheckUser(eZtUB::MedoniAndrei))
	{
		flDrawY = this->DrawButton("Custom", eZTMENU3_BUTTON_17, flDrawX, flDrawY);
	}
}


float CZtMenuV3::DrawButton(char* Text, int ID, float X, float Y)
{
	float flResult = 0;
	float flButtonX = X;
	float flButtonY = Y;
	DWORD dwColor = eGray100;

	gInterface.DrawGUI(ID, flButtonX, flButtonY);

	if(gInterface.IsWorkZone(ID))
	{
		if(gInterface.Data[ID].OnClick)
		{
			dwColor = eGray150;
		}

		gInterface.DrawColoredGUI(ID, gInterface.Data[ID].X, gInterface.Data[ID].Y, dwColor);

		gInterface.DrawFormat(eYellow, flButtonX, flButtonY + 7, 108, 3, Text);
	}
	else
	{
		gInterface.DrawFormat(eWhite, flButtonX, flButtonY + 7, 108, 3, Text);
	}

	flResult = Y + gInterface.Data[ID].Height + 1.5;

#if(ENABLR_DEN_DEV)
	if(g_ZtLicense.CheckUser(eZtUB::eternalmu))
	{
		flResult -= 0.5;
	}
#endif

	return flResult;
}

void CZtMenuV3::CursorButton(DWORD Event)
{
	if(pPlayerState != GameProcess)
	{
		return;
	}

	if(gInterface.CheckWindow(ObjWindow::CashShop)  || 
	   gInterface.CheckWindow(ObjWindow::FullMap)   || 
	   gInterface.CheckWindow(ObjWindow::SkillTree) || 
	   gInterface.CheckWindow(ObjWindow::MoveList))
	{
		return;
	}

	//if(gInterface.Data[eZTMENU3_MENU].X == -1 || gInterface.Data[eZTMENU3_MENU].Y == -1)
	//{
	//	return;
	//}

	if(gInterface.IsWorkZone(eZTMENU3_MENU))
	{
		pSetCursorFocus = true;
	}


	if(gInterface.CheckWindowZt(ObjWindowsZt::ztWinMenuV3))
	{
		if(gInterface.ButtonZt(Event, eZTMENU3_MENU, false))
		{
			gInterface.CloseWindowZt(ObjWindowsZt::ztWinMenuV3);
			return;
		}
	}
	else
	{
		if(gInterface.ButtonZt(Event, eZTMENU3_MENU, false))
		{
			gInterface.CloseWindow(ObjWindow::CommandWindow);
			#if(ENABLE_VERSION_ME)
			gInterface.CloseWindowsZtAll();
			#endif
			gInterface.OpenWindowZt(ObjWindowsZt::ztWinMenuV3);
			return;
		}
	}

	if(!gInterface.CheckWindowZt(ObjWindowsZt::ztWinMenuV3))
	{
		return;
	}

	if(g_ZtLicense.CheckUser(eZtUB::NSGames))
	{
		if(gInterface.Button(Event, ObjWindowsZt::ztWinMenuV3, eZTMENU3_BUTTON_20,  false))
		{
			gInterface.CloseWindowZt(ObjWindowsZt::ztWinMenuV3);

			ShellExecute(NULL, "open", "https://mu.mmotop.ru/servers/32190", NULL, NULL, SW_MAXIMIZE);		
		}

		if(gInterface.Button(Event, ObjWindowsZt::ztWinMenuV3, eZTMENU3_BUTTON_21,  false))
		{
			gInterface.CloseWindowZt(ObjWindowsZt::ztWinMenuV3);

			#if(DONATE_SHOP==TRUE)
			if(!gInterface.CheckWindow(Shop))
			{
				g_DonateShop.CG_CashSend();
			}
			#endif
		}
	}

	if(g_ZtLicense.CheckUser(eZtUB::eternalmu))
	{
		if(gInterface.Button(Event, ObjWindowsZt::ztWinMenuV3, eZTMENU3_BUTTON_20,  false))
		{
			gInterface.CloseWindowZt(ObjWindowsZt::ztWinMenuV3);

			ShellExecute(NULL, "open", "https://mu.mmotop.ru/servers/32083", NULL, NULL, SW_MAXIMIZE);		
		}

		if(gInterface.Button(Event, ObjWindowsZt::ztWinMenuV3, eZTMENU3_BUTTON_21,  false))
		{
			gInterface.CloseWindowZt(ObjWindowsZt::ztWinMenuV3);

			#if(DONATE_SHOP==TRUE)
			if(!gInterface.CheckWindow(Shop))
			{
				g_DonateShop.CG_CashSend();
			}
			#endif
		}

	}

	if(g_ZtLicense.CheckUser(eZtUB::GloryMU))
	{
		if(gInterface.Button(Event, ObjWindowsZt::ztWinMenuV3, eZTMENU3_BUTTON_20,  false))
		{
			gInterface.CloseWindowZt(ObjWindowsZt::ztWinMenuV3);

			ShellExecute(NULL, "open", "http://glorymu.org/cabinet/pay", NULL, NULL, SW_MAXIMIZE);		
		}

		if(gInterface.Button(Event, ObjWindowsZt::ztWinMenuV3, eZTMENU3_BUTTON_21,  false))
		{
			gInterface.CloseWindowZt(ObjWindowsZt::ztWinMenuV3);

			#if(DONATE_SHOP==TRUE)
			if(!gInterface.CheckWindow(Shop))
			{
				g_DonateShop.CG_CashSend();
			}
			#endif
		}
	}

#if(ENABLE_DONATE_BUTTON==TRUE)
	if( gInterface.ButtonZt(Event, eZTMENU3_BUTTON_01, false ) )
	{
		lpViewObj lpViewPlayer = &*(ObjectPreview*)oUserPreviewStruct;

		if(lpViewPlayer->InSafeZone)
		{
			gInterface.CloseWindowZt(ObjWindowsZt::ztWinMenuV3);

			gInterface.m_bCashShopOpen = true;
		}
		return;
	}
#endif

#if(SYSTEM_ACHIEVEMENTS)
	if(gInterface.ButtonZt(Event, eZTMENU3_BUTTON_02, false))
	{
		g_Achievements.CGWindowOpen();

		gInterface.CloseWindowZt(ObjWindowsZt::ztWinMenuV3);
	}

	if(gInterface.ButtonZt(Event, eZTMENU3_BUTTON_03, false))
	{
		gInterface.CloseWindowZt(ObjWindowsZt::ztWinMenuV3);	

		if(gInterface.CheckWindowZt(ztWinAchievementsPower))
		{
			gInterface.CloseWindowZt(ztWinAchievementsPower);
		}
		else
		{
			gInterface.OpenWindowZt(ztWinAchievementsPower);
		}
	}
#endif

	if(g_ZtLicense.user.AccSecurity)
	{
		if(g_ZtLicense.CheckUser(eZtUB::Gredy) || g_ZtLicense.CheckUser(eZtUB::GredyLocal) || g_ZtLicense.CheckUser(eZtUB::Gredy2))
		{
		}
		else
		{
			if(gInterface.Button(Event, ObjWindowsZt::ztWinMenuV3, eZTMENU3_BUTTON_18, false))
			{
				gInterface.CloseWindowZt(ObjWindowsZt::ztWinMenuV3);

				gInterface.OpenWindowZt(ObjWindowsZt::ztWinAccWarning);
			}
		}
	}

	if(g_ZtLicense.user.PremiumZt)
	{
		if(g_ZtLicense.CheckUser(eZtUB::Gredy) || g_ZtLicense.CheckUser(eZtUB::GredyLocal) || g_ZtLicense.CheckUser(eZtUB::Gredy2) || g_ZtLicense.CheckUser(eZtUB::MedoniAndrei))
		{
		}
		else
		{
			if(gInterface.Button(Event, ObjWindowsZt::ztWinMenuV3, eZTMENU3_BUTTON_19, false))
			{
				gInterface.CloseWindowZt(ObjWindowsZt::ztWinMenuV3);

				//gInterface.OpenWindowZt(ObjWindowsZt::ztWinPremium);
				g_PremiumSystemZt.CG_SendOpenWindows();
			}
		}
	}

	if( gInterface.Button(Event, ObjWindowsZt::ztWinMenuV3, eZTMENU3_BUTTON_04, false ) )
	{
		gInterface.CloseWindowZt(ObjWindowsZt::ztWinMenuV3);

		gInterface.OpenWindowZt(ztWinSettings);
	}

	if(gInterface.Button(Event, ObjWindowsZt::ztWinMenuV3, eZTMENU3_BUTTON_05, false))
	{
		gInterface.CloseWindowZt(ObjWindowsZt::ztWinMenuV3);

		gCamera.Init();
	}

	if(gInterface.Button(Event, ObjWindowsZt::ztWinMenuV3, eZTMENU3_BUTTON_06, false))
	{
		gInterface.CloseWindowZt(ObjWindowsZt::ztWinMenuV3);

		gJewelsBank.Active = !gJewelsBank.Active;
	}

	if(gRAGESYSTEM)
	{
		if(gInterface.Button(Event, ObjWindowsZt::ztWinMenuV3, eZTMENU3_BUTTON_07, false))
		{
			gInterface.CloseWindowZt(ObjWindowsZt::ztWinMenuV3);

			gInterface.Data[eRageTable].OnShow = !gInterface.Data[eRageTable].OnShow;
		}
	}

	if(gWINQUEST)
	{
		if(gInterface.Button(Event, ObjWindowsZt::ztWinMenuV3, eZTMENU3_BUTTON_08, false))
		{
			gInterface.CloseWindowZt(ObjWindowsZt::ztWinMenuV3);

			gQuestSystem.Switcher(0);
		}
		if(gInterface.Button(Event, ObjWindowsZt::ztWinMenuV3, eZTMENU3_BUTTON_09, false))
		{
			gInterface.CloseWindowZt(ObjWindowsZt::ztWinMenuV3);

			gQuestSystem.Switcher(1);
		}
	}

	if(gInterface.Button(Event, ObjWindowsZt::ztWinMenuV3, eZTMENU3_BUTTON_10, false))
	{
		gInterface.CloseWindowZt(ObjWindowsZt::ztWinMenuV3);

		if(g_ZtLicense.user.OfflineMode)
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
		else
		{
			gDataSend.SendOfflineAttack();
		}
	}
	if(gRanking.Active)
	{
		if(gInterface.Button(Event, ObjWindowsZt::ztWinMenuV3, eZTMENU3_BUTTON_11, false))
		{
			gInterface.CloseWindowZt(ObjWindowsZt::ztWinMenuV3);

			gRanking.Show = !gRanking.Show;
		}
	}

	if(gEventTimer.Active)
	{
		if(gInterface.Button(Event, ObjWindowsZt::ztWinMenuV3, eZTMENU3_BUTTON_12, false))
		{
			gInterface.CloseWindowZt(ObjWindowsZt::ztWinMenuV3);

			gEventTimer.Show = !gEventTimer.Show;
		}
	}

	#if(CUSTOM_PARTY_SEARCH==TRUE)
	if(g_PartySearch.Active)
	{
		if(gInterface.Button(Event, ObjWindowsZt::ztWinMenuV3, eZTMENU3_BUTTON_13, false))
		{
			gInterface.CloseWindowZt(ObjWindowsZt::ztWinMenuV3);

			if(!gInterface.CheckWindowZt(ztWinPTSearchMaster) && !gInterface.CheckWindowZt(ztWinPTSearchUser))
			{
				gInterface.OpenWindowZt(ztWinPTSearchMaster);
			}
			else if(gInterface.CheckWindowZt(ztWinPTSearchMaster))
			{
				gInterface.CloseWindowZt(ztWinPTSearchMaster);
			}
		}
	}
	#endif

	if(g_PartySearch.Active)
	{
		if(gInterface.Button(Event, ObjWindowsZt::ztWinMenuV3, eZTMENU3_BUTTON_14, false))
		{
			gInterface.CloseWindowZt(ObjWindowsZt::ztWinMenuV3);

			if(!gInterface.CheckWindowZt(ztWinPTSearchMaster) && !gInterface.CheckWindowZt(ztWinPTSearchUser))
			{
				g_PartySearch.CG_SendOpenUserList();
			}
			else if(gInterface.CheckWindowZt(ztWinPTSearchUser))
			{
				gInterface.CloseWindowZt(ztWinPTSearchUser);
			}
		}
	}
	else
	{
		if(gAutoParty.Active)
		{
			if(gInterface.Button(Event, ObjWindowsZt::ztWinMenuV3, eZTMENU3_BUTTON_15,  false))
			{
				gInterface.CloseWindowZt(ObjWindowsZt::ztWinMenuV3);
				gDataSend.SendOpenAutoPartyList();
			}
		}
	}

	if(g_ZtLicense.user.Smithy == true)
	{
		if(gInterface.Button(Event, ObjWindowsZt::ztWinMenuV3, eZTMENU3_BUTTON_16,  false))
		{
			gInterface.CloseWindowZt(ObjWindowsZt::ztWinMenuV3);
			if(!gInterface.CheckWindowZt(ztWinSmithy))
			{
				gInterface.OpenWindowZt(ztWinSmithy);
			}
		}
	}

	if(g_ZtLicense.CheckUser(eZtUB::Local) || g_ZtLicense.CheckUser(eZtUB::Gredy) || g_ZtLicense.CheckUser(eZtUB::GredyLocal) || g_ZtLicense.CheckUser(eZtUB::Gredy2) || 
		THINNAKORN_MAC == 1 || g_ZtLicense.CheckUser(eZtUB::MedoniAndrei) )
	{
		if(gInterface.Button(Event, ObjWindowsZt::ztWinMenuV3, eZTMENU3_BUTTON_17,  false))
		{
			gInterface.CloseWindowZt(ObjWindowsZt::ztWinMenuV3);
			if(!gInterface.CheckWindowZt(ztWinCustomMenu))
			{
				gInterface.OpenWindowZt(ztWinCustomMenu);
			}
			else
			{
				gInterface.CloseWindowZt(ztWinCustomMenu);
			}
		}
	}
}

void CZtMenuV3::DrawMenu2()
{
	//if(    gInterface.CheckWindow(Party)
	//	|| gInterface.CheckWindow(Guild)
	//	|| gInterface.CheckWindow(Trade)
	//	|| gInterface.CheckWindow(Warehouse)
	//	|| gInterface.CheckWindow(ChaosBox)
	//	|| gInterface.CheckWindow(CommandWindow)
	//	|| gInterface.CheckWindow(PetInfo)
	//	|| gInterface.CheckWindow(Shop)
	//	|| gInterface.CheckWindow(Inventory)
	//	|| gInterface.CheckWindow(Store)
	//	|| gInterface.CheckWindow(OtherStore)
	//	|| gInterface.CheckWindow(Character)
	//	|| gInterface.CheckWindow(FastMenu)
	//	|| gInterface.CheckWindow(SkillTree)
	//	|| gInterface.CheckWindow(NPC_Titus)
	//	|| gInterface.CheckWindow(CashShop)
	//	|| gInterface.CheckWindow(FullMap)
	//	|| gInterface.CheckWindow(NPC_Dialog)
	//	|| gInterface.CheckWindow(GensInfo)
	//	|| gInterface.CheckWindow(NPC_Julia)
	//	|| gInterface.CheckWindow(ExpandInventory)
	//	|| gInterface.CheckWindow(ExpandWarehouse) 
	//	|| gInterface.CheckWindow(Helper) 
	//	|| gInterface.CheckWindow(Quest) 
	//	|| gInterface.CheckWindow(QuestDevin) 
	//	|| gInterface.CheckWindow(DevilSquery) 
	//	|| gInterface.CheckWindow(GuardNPC) 
	//	|| gInterface.CheckWindow(VorotaCS) 
	//	|| gInterface.CheckWindow(Rena) 
	//	|| gInterface.CheckWindow(LuckyCoins)
	//	|| gInterface.CheckWindow(Titus)
	//	|| gInterface.CheckWindow(BloodCastle) )
	//{
	//	return;
	//}

	//if( gInterface.CheckWindowZt(ztWinRanking)		  ||
	//	gInterface.CheckWindowZt(ztWinPersonalPrice) )
	//{
	//	return;
	//}

	float StartY = 379;
	float StartX = 0;//MAX_WIN_WIDTH - 100;
	//float StartY = 0;
	//float StartX = MAX_WIN_WIDTH - 125;

	gInterface.DrawGUI(eZTMENU3_MENU, StartX , StartY);

	if(gInterface.IsWorkZone(eZTMENU3_MENU))
	{
		pSetCursorFocus = true;
		
		DWORD dwColor = eGray100;

		if(gInterface.Data[eZTMENU3_MENU].OnClick)
		{
			dwColor = eGray150;
		}

		gInterface.DrawColoredGUI(eZTMENU3_MENU, gInterface.Data[eZTMENU3_MENU].X, gInterface.Data[eZTMENU3_MENU].Y, dwColor);
	}

	//if(gInterface.IsWorkZone(eZTMENU3_MENU))
	//{
	//	gInterface.DrawFormat(eWhite, StartX, StartY + 3, 168, 3, "Eternal");
	//	gInterface.DrawFormat(eYellow, StartX, StartY + 13, 168, 3, "Menu");
	//}
	//else
	//{
	//	gInterface.DrawFormat(eWhite, StartX, StartY + 3, 168, 3, "Eternal");
	//	gInterface.DrawFormat(eAncient, StartX, StartY + 13, 168, 3, "Menu");
	//}
}

void CZtMenuV3::DrawWindow2()
{
	if(!gInterface.CheckWindowZt(ObjWindowsZt::ztWinMenuV3))
	{
		return;
	}

	pSetCursorFocus = true;

	float StartY = 0;
	float StartX = MAX_WIN_WIDTH - 225;

	gInterface.DrawWindow(eZTMENU3_MAIN, eZTMENU3_TITLE, eZTMENU3_FRAME, eZTMENU3_FOOTER, 21, StartX, StartY, "Menu");
	//pDrawColorButton(0x7880, StartX, StartY, 190, 430, NULL, NULL, Color4f(0, 0, 0, 255));

	float flDrawX = StartX + 42.5 + 15;	//42.5;
	float flDrawY = StartY + 20 + 20;

	#if(ENABLR_DEN_DEV)
	if(g_ZtLicense.CheckUser(eZtUB::eternalmu))
	{
		flDrawY -= 15;
	}
#endif

	// =====================================================================

	if(g_ZtLicense.CheckUser(eZtUB::NSGames))
	{
		flDrawY = this->DrawButton("Vote for Server", eZTMENU3_BUTTON_20, flDrawX, flDrawY);

		flDrawY = this->DrawButton("Donate Shop", eZTMENU3_BUTTON_21, flDrawX, flDrawY);
	}

	if(g_ZtLicense.CheckUser(eZtUB::eternalmu))
	{
		flDrawY = this->DrawButton("Vote for Server", eZTMENU3_BUTTON_20, flDrawX, flDrawY);

		flDrawY = this->DrawButton("Donate Shop", eZTMENU3_BUTTON_21, flDrawX, flDrawY);
	}

	if(g_ZtLicense.CheckUser(eZtUB::GloryMU))
	{
		flDrawY = this->DrawButton("Buy Credits", eZTMENU3_BUTTON_20, flDrawX, flDrawY);

		flDrawY = this->DrawButton("Donate Shop", eZTMENU3_BUTTON_21, flDrawX, flDrawY);
	}


	if(g_ZtLicense.m_Achievements)
	{
		flDrawY = this->DrawButton("Achievements", eZTMENU3_BUTTON_02, flDrawX, flDrawY);

		flDrawY = this->DrawButton("Power", eZTMENU3_BUTTON_03, flDrawX, flDrawY);
	}

	if(g_ZtLicense.user.AccSecurity)
	{
		if(g_ZtLicense.CheckUser(eZtUB::Gredy) || g_ZtLicense.CheckUser(eZtUB::GredyLocal) || g_ZtLicense.CheckUser(eZtUB::Gredy2))
		{
		}
		else
		{
			flDrawY = this->DrawButton("Account Security", eZTMENU3_BUTTON_18, flDrawX, flDrawY);
		}
	}

	if(g_ZtLicense.user.PremiumZt)
	{
		flDrawY = this->DrawButton("Premium System", eZTMENU3_BUTTON_19, flDrawX, flDrawY);
	}

	flDrawY = this->DrawButton("Options", eZTMENU3_BUTTON_04, flDrawX, flDrawY);

	flDrawY = this->DrawButton("3D Camera [Reset]", eZTMENU3_BUTTON_05, flDrawX, flDrawY);

	flDrawY = this->DrawButton("Jewels Bank", eZTMENU3_BUTTON_06, flDrawX, flDrawY);

	if(gRAGESYSTEM)
	{
		flDrawY = this->DrawButton("Rage System", eZTMENU3_BUTTON_07, flDrawX, flDrawY);
	}

	if(gWINQUEST)
	{
		flDrawY = this->DrawButton("Quest", eZTMENU3_BUTTON_08, flDrawX, flDrawY);
		flDrawY = this->DrawButton("Quest Options", eZTMENU3_BUTTON_09, flDrawX, flDrawY);
	}

	flDrawY = this->DrawButton("Offline Attack", eZTMENU3_BUTTON_10, flDrawX, flDrawY);

	if(gRanking.Active)
	{
		flDrawY = this->DrawButton("Top 100 Player", eZTMENU3_BUTTON_11, flDrawX, flDrawY);
	}

	if(gEventTimer.Active)
	{
		flDrawY = this->DrawButton("Events Timer", eZTMENU3_BUTTON_12, flDrawX, flDrawY);
	}

	#if(CUSTOM_PARTY_SEARCH==TRUE)
	if(g_PartySearch.Active)
	{
		flDrawY = this->DrawButton("Auto Party", eZTMENU3_BUTTON_13, flDrawX, flDrawY);
	}
	#endif

	if(g_PartySearch.Active)
	{
		flDrawY = this->DrawButton("Party Search List", eZTMENU3_BUTTON_14, flDrawX, flDrawY);
	}
	else
	{
		if(gAutoParty.Active)
		{
			flDrawY = this->DrawButton("Auto Party List", eZTMENU3_BUTTON_15, flDrawX, flDrawY);
		}
	}

	if(g_ZtLicense.user.Smithy == true)
	{
		flDrawY = this->DrawButton("Smithy", eZTMENU3_BUTTON_16, flDrawX, flDrawY);
	}

	if(g_ZtLicense.CheckUser(eZtUB::Local) || g_ZtLicense.CheckUser(eZtUB::Gredy) || 
		g_ZtLicense.CheckUser(eZtUB::GredyLocal) || g_ZtLicense.CheckUser(eZtUB::Gredy2) || 
		THINNAKORN_MAC == 1 || g_ZtLicense.CheckUser(eZtUB::MedoniAndrei))
	{
		flDrawY = this->DrawButton("Custom", eZTMENU3_BUTTON_17, flDrawX, flDrawY);
	}
}

#endif