#include "stdafx.h"
//#include "MuLua.h"
#include "Controller.h"
#include "Other.h"
//#include "Interface.h"
//#include "Camera.h"
//#include "ChatExpanded.h"
//#include "NewsBoard.h"
#include "TrayMode.h"
//#include "TDebugLog.h"
#include "Console.h"
#include "Camera.h"
#include "ConnectEx.h"
#include "Interface.h"
#include "JewelsBank.h"
#include "Object.h"
#include "NewHpBar.h"
#include "Graphics.h"
#include "QuestSystem.h"
#include "Configs.h"
#include "AutoParty.h"
#include "EventTimer.h"
#include "Ranking.h"
#include "MonsterQuest.h"
#include "NewParty.h"
#include "PartySearch.h"
#include "PersonalShopZt.h"
#ifdef ACHIEVEMENTS_SYSTEM
#include "AchievementsSystem.h"
#endif // ACHIEVEMENTS_SYSTEM
#include "NewsBoard.h"
#include "BufferSystem.h"
#include "Smithy.h"
#include "ZtLicense.h"
#include "OfflineMode.h"
#include "MiniMap.h"
#include "Marriage.h"
#include "AddPoints.h"
#include "CustomMenu.h"
#include "ResetSystem.h"
#include "DonateShop.h"
#include "DungeonSiege.h"
#include "TeamVsTeam.h"
#include "MiniMenu.h"
#include "Achievements.h"
#include "ZtTeleport.h"
#include "RageSystem.h"
#include "Debug.h"
#include "resource.h"
#include "TMemory.h"
#include "DeBug.h"
#include "PremiumSystemZt.h"
#include "ZtTeleportEvo.h"
#include "PKClear.h"
#include "AccountSecurity.h"
#include "ReferralSystem.h"
#include "ZtWinQuestSystem.h"
#include "Lottery.h"
#include "DataSend.h"
#include "ItemMarket.h"
#include "ZtMenuV3.h"
#include "Settings.h"
#include "MapTeleport.h"
#include "CameraMove.h"

#include "RenderEffect.h"
#include "MiniMapZt.h"
#include "SelectChar.h"
#include "ChatSmile.h"
// ----------------------------------------------------------------------------------------------

Controller	gController;
// ----------------------------------------------------------------------------------------------

void __declspec(naked) iconHook()
{
	static DWORD dwIcon = (DWORD)LoadIcon(gController.Instance, MAKEINTRESOURCE(IDI_ICON2));
	static DWORD dwJmp = 0x004D0E3C;

	_asm
	{
		MOV EAX, dwIcon
		JMP dwJmp
	}
}
// ----------------------------------------------------------------------------------------------

bool Controller::Load()
{
	gController.wMouse = 0x00;

	gController.wKeyBord = 0x00;

#if(CUSTOM_EMULATOR_KEY)
	this->m_AutoMouseLeft = false;
	this->m_AutoMouseRight = false;
#endif
#if(ADD_CTRL_KEY)
	this->CtrlKey = false;
#endif

	if( !this->MouseHook )
	{
		this->MouseHook = SetWindowsHookExA(WH_MOUSE, this->Mouse, gController.Instance, GetCurrentThreadId());
		// ----
		//MessageBox(0,"ERROR 2","MouseHook",0);
		if( !this->MouseHook )
		{
			//MessageBox(0,"ERROR","MouseHook",0);
			//return false;
		}
	}
	// ----
	if( !this->KeyboardHook )
	{
		//this->KeyboardHook = SetWindowsHookEx(WH_KEYBOARD, this->Keyboard, gController.Instance, NULL);
		//this->KeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, this->Keyboard, gController.Instance, NULL);
#if(UPDATE_KB==TRUE)
		this->KeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, this->Keyboard, gController.Instance, NULL);
#else
		this->KeyboardHook = SetWindowsHookExA(WH_KEYBOARD, this->Keyboard, gController.Instance, GetCurrentThreadId());
#endif
		if(!this->KeyboardHook)
		{
			//MessageBox(0,"ERROR","KeyboardHook",0);
			//return false;
		}
	}

	if(!gLoadMUAutoClicker)
	{
		char* pWinTitle = (char*)&gWindowTitle;
		WriteMemory((LPDWORD)(0x004D0E06+3), &pWinTitle, sizeof(DWORD));
	}


	SetRange((LPVOID)0x004D0E2F, 13, ASM::NOP);
	SetOp((LPVOID)0x004D0E2F, iconHook, ASM::CALL);

	ChangeAddress(oWindowsProc, (DWORD)this->WndProc);
	

	#if(ENABLE_LUA)
	this->m_Lua.DoFile("Controller.lua");
	#endif

	return true;
}
// ----------------------------------------------------------------------------------------------

LRESULT Controller::Mouse(int Code, WPARAM wParam, LPARAM lParam)
{
	if(GetForegroundWindow() != pGameWindow)
	{
		return CallNextHookEx(gController.MouseHook, Code, wParam, lParam);
	}

	gController.wMouse = wParam;

	MOUSEHOOKSTRUCTEX * Mouse	= (MOUSEHOOKSTRUCTEX*)lParam;
	if(gWINQUEST) gQuestSystem.MouseRun();

	gCamera.Run(Mouse, wParam);

	#if(DEV_PLAYERSHOP)
	g_ItemMarket.Mouse(Mouse, wParam);
	#endif
	
	switch(wParam)
	{
	case WM_LBUTTONUP:
	case WM_LBUTTONDOWN:
		{
			if(gMONSTER_QUEST_SYSTEM)
			{
				gMonsterQuest.EventCloseMainTable(wParam);
				gMonsterQuest.EventFinishMainTable(wParam);
			}
#if _NEW_PARTY_SYSTEM_ == TRUE
			//if(gPARTY_SYSTEM){
				g_Party.MouseController(wParam);
				g_Party.MouseControllerD(wParam);
				g_Party.MouseControllerPage(wParam);
				g_Party.MouseControllerLeader(wParam);
			//}
#endif
#if(CUSTOM_PARTY_SEARCH==TRUE)
			g_PartySearch.Button(wParam);
#endif
#if(CUSTOM_PERONAL_ZT==TRUE)
			g_PersonalShopZt.Button(wParam);
			g_PersonalShopZt.ButtonPrice(wParam);
#endif
#if(CUSTOM_NEWS==TRUE)
			g_NewsBoard.EventNewsWindow_Main(wParam);
#endif
#if(CUSTOM_NPC_BUFFER==TRUE)
			g_BufferSystem.ButtonEvent(wParam);
#endif
#if(CUSTOM_SMITHY == TRUE)
			g_Smithy.Button(wParam);
#endif
#if(OFFLINE_MODE==TRUE)
			g_OfflineMode.Click(wParam);
#endif
#if(CUSTOM_MARRIAGE)
			g_Marriage.Button(wParam);
#endif
#if(CUSTOM_ADD_POINTS==TRUE)
			g_AddPoints.Button(wParam);
#endif
#if(CUSTOM_MENU)
			g_CustomMenu.Button(wParam);
#endif
#if(CUSTOM_RESETSYSTEM)
			g_ResetSystem.Button(wParam);
#endif
#if(DONATE_SHOP==TRUE)
			g_DonateShop.ButtonClick(wParam);
#endif
#if(EVENT_DUNGEON_SIEGE)
			g_DungeonSiege.Button(wParam);
#endif
#if(EVENT_TEAM_VS_TEAM)
			g_TeamVsTeam.Button(wParam);
#endif
#if(CUSTOM_MINIMENU==TRUE)
			g_MiniMenu.Botton(wParam);
#endif
#if(SYSTEM_ACHIEVEMENTS)
			g_Achievements.Button(wParam);
#endif
#if(CUSTOM_ZT_TELEPORT==TRUE)
			g_ZtTeleport.Button(wParam);
#endif
#if(CUSTOM_ZT_TELEPORT_EVO==TRUE)
			g_ZtTeleportEvo.Button(wParam);
#endif
#if(CUSTOM_PREMIUM_SYSTEM==TRUE)
			g_PremiumSystemZt.Button(wParam);
#endif
			gRageSystem.Button(wParam);
#if(CUSTOM_PKCLEAR_NPC==TRUE)
			g_PKClear.EventButton(wParam);
#endif
#if(CUSTOM_ACCOUNT_SECURITY)
			g_AccountSecurity.ButtonMain(wParam);
#endif
#if(CUSTOM_REFERAL_SYSTEM)
			g_ReferralSystem.Button(wParam);
#endif
#if(CUSTOM_ZT_QUEST_SYSTEM==TRUE)
			g_ZtWinQuestSystem.Button(wParam);
#endif
			gInterface.EventAutoHPClick(wParam);
			gInterface.EventWarehouseUI(wParam);
			gInterface.EventOffTrade(wParam);
#if(CUSTOM_LOTTERY)
			g_Lottery.Button(wParam);
#endif
			#if(DEV_INTERFASE_SEASON3)
			if(gInterfaceVersion == eINTERFACE_SEASON3)
			{
				gInterface.EventMenuButton(wParam);
			}
			#endif
			#if(DEV_GUILDBANK)
			gInterface.EventGuildBank(wParam);
			#endif
			#if(INTERFACE_JEWELBANK)
			gJewelsBank.Button(wParam);
			#endif
			#if(DEV_PLAYERSHOP)
			//g_ItemMarket.Button(wParam);
			#endif
			#if(DEV_ZTMENU_V3)
			g_ZtMenuV3.CursorButton(wParam);
			#endif
			#if(CUSTOM_WIN_SETTINGS==TRUE)
			g_Settings.Button(wParam);
			#endif
			#if(DEV_INTERFACE_ZT700)
			gInterface.EventMenuButton(wParam);
			#endif
			#if(USERPANEL)
			gInterface.EventUsersPanel(wParam);
			#endif
			gInterface.EventMenuButtonZt(wParam);
			#if(CUSTOM_MAP_TELEPORT)
			g_MapTeleport.MouseTeleportEx(wParam);
			#endif		
			#if(CUSTOM_VALUE_MENU)
			gInterface.ControllerValueMenu(wParam);
			gInterface.ControllerGuildValueMenu(wParam);
			#endif		
			#if(ENABLE_MULTI_CHAR)
			gInterface.EventSelectChar(wParam);
			#endif
			#if(ENABLE_MARKET_BUTTON)
			gInterface.EventMarketButton(wParam);
			#endif
			#if(ENABLE_CHAT_SMILE)
			g_ChatSmile.ControllerSmile(wParam);
			#endif
		}
		break;
	case WM_MOUSEWHEEL:
		{

		}
		break;
	case WM_MBUTTONDOWN:
		{

		}
		break;
	case WM_MBUTTONUP:
		{

		}
		break;
	case WM_MOUSEMOVE:
		{

		}
		break;
	}

	return CallNextHookEx(gController.MouseHook, Code, wParam, lParam);
}
// ----------------------------------------------------------------------------------------------

#if(UPDATE_KB==TRUE)
LRESULT Controller::Keyboard(int Code, WPARAM wParam, LPARAM lParam)
{
	if( (Code == HC_ACTION) && (wParam == WM_KEYDOWN) && (GetForegroundWindow() == pGameWindow) )
	{
		KBDLLHOOKSTRUCT Hook = *((KBDLLHOOKSTRUCT*)lParam);
		// ----
		gController.wKeyBord = Hook.vkCode;

		if(gWINQUEST) gQuestSystem.Keyboard(Hook.vkCode);

		switch(Hook.vkCode)
		//switch(Hook.vkCode)
		{
		case VK_ESCAPE:
			{
				gJewelsBank.Active = false;
				gAutoParty.Show = false;
				//gInterface.Data[eTIME].OnShow = false;
				gEventTimer.Show = false;
				gInterface.Data[eRageTable].OnShow = false;
				gRanking.Show = false;
				gInterface.
			}
			break;

		case VK_F6:
			{
				//if( GetForegroundWindow() == pGameWindow )
				//{
				//	gChatExpanded.Switch();
				//}
//#ifdef ztDEBUG_CODE
//				gConsole.Output(2,"%d",win);
//#endif
//				gInterface.OpenWindow(win);
//				win++;
			}
			break;
			// --
		case VK_F7:
			{
				gMonsterQuest.DrawInfoTable = !gMonsterQuest.DrawInfoTable;
			}
			break;
			// --

		case VK_F12:
			{
				if( gTrayMode.TempWindowProc == NULL )
				{
					gTrayMode.TempWindowProc = SetWindowLongA(pGameWindow, GWL_WNDPROC, (long)gController.Window);
				}
				gTrayMode.SwitchState();
			}
			break;
		case VK_PRIOR:
			{
				gCamera.Init();
			}
			break;
		case VK_NEXT:
			{
				gCamera.Switch();
			}
			break;
		case 0x59:	//Y
			{
				if(!gInterface.CheckWindow(ObjWindow::ChatWindow))
				{
					if(gJewelsBank.Active)
					{
						gJewelsBank.Active = false;
					}
					else
					{
						gJewelsBank.Active = true;
					}
				}
			}
			break;
		case 0x4F:	//O
			{
				if(g_ZtLicense.ActiveUser == ulasevich){
				
				}
				else{
					if(!gInterface.CheckWindow(ObjWindow::ChatWindow))
					{
						if(g_bGlowGraphic)
							g_bGlowGraphic = false;
						else
							g_bGlowGraphic = true;
					}
				}
			}
			break;
		case 0x38:	//8
			{
				if(g_ZtLicense.ActiveUser == ulasevich){
					if(!gInterface.CheckWindow(ObjWindow::ChatWindow))
					{
						if(g_bGlowGraphic)
							g_bGlowGraphic = false;
						else
							g_bGlowGraphic = true;
					}
				}
				else{
					
				}
			}
			break;
		case VK_F9:
			{
				if(iMonsterHPBar == 0)
				{
					iMonsterHPBar++;
				}
				else if(iMonsterHPBar == 1)
				{
					iMonsterHPBar++;
				}
				else
				{
					iMonsterHPBar = 0;
				}

			}
			break;
		case VK_F10:
			{

				if(iUserHpBar == 0)
				{
					iUserHpBar = 1;
				}
				else
				{
					iUserHpBar = 0;
				}

			}
			break;
		case VK_F11:
			{
				if(iPartyHpBar == 0)
				{
					iPartyHpBar = 1;
				}
				else
				{
					iPartyHpBar = 0;
				}

#ifdef ztDEBUG_CODE
				//gConsole.Output(2,"%d",iPartyHpBar);
#endif
			}
			break;
		}

#if(CUSTOM_PERONAL_ZT==TRUE)
		g_PersonalShopZt.Key(Hook.vkCode);
#endif

	} 

	return CallNextHookEx(gController.KeyboardHook, Code, wParam, lParam);
}
// ----------------------------------------------------------------------------------------------
#else
LRESULT Controller::Keyboard(int Code, WPARAM wParam, LPARAM lParam)
{
	if(((lParam >> 31) & 1) && (Code == HC_ACTION))
	{
		#if(CUSTOM_CAMERA_MOVE)
		if(g_ZtLicense.user.CustomCameraMove)
		{
			g_CameraMove.KeyBoard(wParam);
		}
		#endif
	}

	if( ((lParam >> 31) & 1) && (Code == HC_ACTION) )
	{
#if(CUSTOM_AUTOCTRL)
		if(wParam == VK_CONTROL && gInterface.m_bAutoCtrl)
		{
			gInterface.m_bAutoCtrl = false;
		}
#endif

		#if(ENABLE_CHARACTER_ACTION)
		if(GetForegroundWindow() == pGameWindow && pPlayerState == SwitchCharacter)
		{
			gSelectChar.KeyboardProcces(wParam);

			return CallNextHookEx(gController.KeyboardHook, Code, wParam, lParam);
		}
		#endif

		if(GetForegroundWindow() != pGameWindow || pPlayerState != GameProcess)
		{
			//gController.wKeyBord = 0x00;

			return CallNextHookEx(gController.KeyboardHook, Code, wParam, lParam);
		}

		KBDLLHOOKSTRUCT Hook = *((KBDLLHOOKSTRUCT*)lParam);

		gController.wKeyBord = wParam;

		#if(CUSTOM_CAMERA_MOVE)
		//g_CameraMove.KeyBoard(wParam);
		#endif



		if(gWINQUEST) gQuestSystem.Keyboard(wParam);

		#if(ADD_CTRL_KEY)

		if(((lParam>>31)&1))
		{
			switch(wParam)
			{
			case VK_CONTROL: 
				{
					if(gController.CtrlKey == true)
					{
						gController.CtrlKey = false;
						gController.CGCtrlKey();
					}
				}
				break;
			}
		}
		else
		{
			switch(wParam)
			{
			case VK_CONTROL:
				{
					if(gController.CtrlKey == false)
					{
						gController.CtrlKey = true;
						gController.CGCtrlKey();
					}
				}
				break;
			}
		}

		#endif

		switch(wParam)
		{
		case VK_ESCAPE:
			{
				//gJewelsBank.Active = false;
				//gAutoParty.Show = false;
				//gEventTimer.Show = false;
				//gInterface.Data[eRageTable].OnShow = false;
				//gRanking.Show = false;
#ifdef ACHIEVEMENTS_SYSTEM
				gAchievementsSystem.Show = false;
#endif
			}
			break;

		case VK_F6:
			{
				//DeBugCrashWarehouse();
			}
			break;
			// --
		case VK_F7:
			{
				gMonsterQuest.DrawInfoTable = !gMonsterQuest.DrawInfoTable;
			}
			break;
			// --
#if(CUSTOM_NEWS == TRUE)
		case VK_F8:
		{
			if( GetForegroundWindow() == pGameWindow )
			{
				if( gInterface.CheckWindowZt(ztWinNews) )
				{
					gInterface.CloseWindowZt(ztWinNews);
				}
				else
				{
					g_NewsBoard.ReqOpenMain();
				}
			}
		}
		break;
#endif
		case VK_F12:
			{
				//if( gTrayMode.TempWindowProc == NULL )
				//{
				//	gTrayMode.TempWindowProc = SetWindowLongA(pGameWindow, GWL_WNDPROC, (long)gController.Window);
				//}
				gTrayMode.SwitchState();
			}
			break;
		case VK_PRIOR:
			{
				gCamera.Init();
			}
			break;
		case VK_NEXT:
			{
				gCamera.Switch();
			}
			break;
		case 0x59:	//Y
			{
				if(!gInterface.CheckWindow(ObjWindow::ChatWindow) && !gInterface.CheckWindow(ObjWindow::Trade))
				{
					if(gJewelsBank.Active)
					{
						gJewelsBank.Active = false;
					}
					else
					{
						gJewelsBank.Active = true;
					}
				}
			}
			break;
		case 0x4F:	//O
			{
				if(!g_ZtLicense.CheckUser(eZtUB::ulasevich))
				{
					if(!gInterface.CheckWindow(ObjWindow::ChatWindow))
					{
						g_bGlowGraphic = !g_bGlowGraphic;
					}				
				}
			}
			break;
		case 0x38:	//8
			{
				if(g_ZtLicense.CheckUser(eZtUB::ulasevich))
				{
					if(!gInterface.CheckWindow(ObjWindow::ChatWindow))
					{
						g_bGlowGraphic = !g_bGlowGraphic;
					}
				}
			}
			break;
		//case 0x4A:	//J
		case 0x4:	//J
			{
				if(!gInterface.CheckWindow(ObjWindow::ChatWindow))
				{
					if(gInterface.CheckWindowZt(ztWinPremium))
					{
						gInterface.CloseWindowZt(ztWinPremium);
					}
					else
					{
						g_PremiumSystemZt.CG_SendOpenWindows();
					}
				}
			}
			break;
		case VK_F9:
			{
				if(iMonsterHPBar == 0)
				{
					iMonsterHPBar++;
				}
				else if(iMonsterHPBar == 1)
				{
					iMonsterHPBar++;
				}
				else
				{
					iMonsterHPBar = 0;
				}
			}
			break;
		case VK_F10:
			{
				if(iUserHpBar == 0)
				{
					iUserHpBar = 1;
				}
				else
				{
					iUserHpBar = 0;
				}
			}
			break;
		case VK_F11:
			{
				if(iPartyHpBar == 0)
				{
					iPartyHpBar = 1;
				}
				else
				{
					iPartyHpBar = 0;
				}
			}
			break;
		case VK_F5:
			{
				if(g_Smithy.License)
				{
					gInterface.OpenWindowZt(ztWinSmithy);
				}
			}
			break;
		case VK_TAB:
			{
				if(pPlayerState == GameProcess && pMapNumber == 30)
				{
					g_MiniMap.Show = !g_MiniMap.Show;
				}
			}
			break;
#ifdef ACHIEVEMENTS_SYSTEM
			case VK_OEM_3: //'`~' for US
			{
				if(gAchievementsSystem.Show)
				{
					gAchievementsSystem.Show = false;
				}
				else
				{
					gAchievementsSystem.Show = true;
				}
			}
			break;
#endif
#if(CUSTOM_AUTOCTRL)
		case VK_MENU:
			{
				if(THINNAKORN_MAC == 1)
				{
					if(gInterface.m_bAutoCtrl)
					{
						gInterface.m_bAutoCtrl = false;
						keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
					}
					else
					{
						gInterface.m_bAutoCtrl = true;
						keybd_event(VK_CONTROL, 0, 0, 0);
					}
				}
#endif
			}
			break;
		case VK_END:
			{
				gMiniMap = !gMiniMap;
				gDataSend.SendConfig();
			}
			break;
#if(CUSTOM_EMULATOR_KEY)
		case 0xBD:
			{
				if(gAutoMouseKey && !gInterface.CheckWindow(ObjWindow::ChatWindow))
				{
					gController.m_AutoMouseLeft = !gController.m_AutoMouseLeft;

					if(gController.m_AutoMouseLeft)
					{
						mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					}
					else
					{
						mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
					}
				}
			}
			break;
		case 0xBB:
			{
				if(gAutoMouseKey && !gInterface.CheckWindow(ObjWindow::ChatWindow))
				{
					gController.m_AutoMouseRight = !gController.m_AutoMouseRight;

					if(gController.m_AutoMouseRight)
					{
						mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
					}
					else
					{
						mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
					}
				}
			}
			break;
#endif
		case VK_SHIFT:
			{
				if(!gInterface.CheckWindow(ObjWindow::ChatWindow))
				{
					if(g_ZtLicense.user.CustomMiniMapZt)
					{
						g_MiniMapZt.m_Show = !g_MiniMapZt.m_Show;
					}
					else
					{
						gMiniMap = !gMiniMap;
					}
				}
			}
			break;

		case VK_PAUSE:
			gDamageTable = !gDamageTable;
			break;
		case VK_NUMPAD0:
			{
				#if(CUSTOM_MAP_TELEPORT)
				//g_MapTeleport.KeyboardTeleportEx();
				#endif	
			}
			break;
		case VK_NUMPAD1:
			{
				#if(ENABLE_LUA)
				gController.m_Lua.Generic_Call("LuaScript", "i");
				#endif
			}
			break;
		case VK_SPACE:
			{

			}
			break;

		}

	gConsole.Output(cGREEN, "[VK] : 0x%02X", wParam);

#if(CUSTOM_PERONAL_ZT==TRUE)
	g_PersonalShopZt.Key(wParam);
#endif
#if(CUSTOM_ADD_POINTS==TRUE)
	g_AddPoints.Keybord(wParam);
#endif
#if(CUSTOM_ACCOUNT_SECURITY)
	g_AccountSecurity.KeyboardPC(wParam);
#endif

#if(CUSTOM_MENU)
	if(wParam == VK_F11)
	{
		gInterface.OpenWindowZt(ztWinCustomMenu);
	}
#endif
	}

	if(GetForegroundWindow() == pGameWindow && pPlayerState == GameProcess)
	{
		if(Code == HC_ACTION)
		{
			if(((lParam >> 31) & 1))
			{
				#if(DEV_PLAYERSHOP)
				g_ItemMarket.Keyboard(wParam);
				#endif
			}
		}
	}

	return CallNextHookEx(gController.KeyboardHook, Code, wParam, lParam);
}
// ----------------------------------------------------------------------------------------------
#endif
LRESULT Controller::Window(HWND Window, DWORD Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
	case TRAYMODE_ICON_MESSAGE:
		{
			switch(lParam)
			{
			case WM_LBUTTONDBLCLK:
				{
					gTrayMode.SwitchState();
				}
				break;
			}
		}
		break;
	}
	// ----
	return CallWindowProc((WNDPROC)gTrayMode.TempWindowProc, Window, Message, wParam, lParam);
}
// ----------------------------------------------------------------------------------------------

LRESULT Controller::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_CLOSE:
		{
			if( gCheckCloseWindow == true	&&
				pPlayerState == GameProcess && 
				gConnectEx.m_ConnectState != ConnectExType::OnForceDisconnect)
			{
				if(MessageBox(hwnd, "Close the game window?", WINDOW_TITLE, MB_OKCANCEL|MB_ICONWARNING) == IDOK)	
				{					
					ExitProcess(0);
				}
				else
				{
					return 0;
				}
			}
			else
			{
				ExitProcess(0);
			}
		}
		break;

	case TRAYMODE_ICON_MESSAGE:
		{
			switch(lParam)
			{
			case WM_LBUTTONDBLCLK:
				{
					gTrayMode.SwitchState();
				}
				break;
			}
		}
		break;
	}

	return (LRESULT)pWindowsProc(hwnd, uMsg, wParam, lParam);
}
// ----------------------------------------------------------------------------------------------

#if(CUSTOM_EMULATOR_KEY)

void Controller::ThreadhMouseAutoKey()
{
	if(GetForegroundWindow() != pGameWindow || pPlayerState != GameProcess)
	{
		if(gController.m_AutoMouseLeft)
		{
			gController.m_AutoMouseLeft = false;
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}

		if(gController.m_AutoMouseRight)
		{
			gController.m_AutoMouseRight = false;
			mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
		}
	}
}
// ----------------------------------------------------------------------------------------------

#endif

#if(ADD_CTRL_KEY)
void Controller::CGCtrlKey()
{
	PMSG_CONTROLLER_CTRL pRequest;
	pRequest.h.set((LPBYTE)&pRequest, 0xFB, 0xD3, sizeof(pRequest));
	pRequest.CtrlKey = this->CtrlKey;
	gProtocol.DataSend((LPBYTE)&pRequest, pRequest.h.size);
}
// ----------------------------------------------------------------------------------------------
#endif