#include "stdafx.h"
#include "Controller.h"
#include "TrayMode.h"
#include "Console.h"
#include "MiniMap.h"
#include "ChatWnd.h"
#include "Protocol.h"
#include "VisualFix.h"
#include "Interface.h"
#include "Item.h"
#include "MakePreviewCharSet.h"
#include "ItemAsm.h"
#include "Camera.h"
#include "RageSystem.h"
#include "User.h"
#include "AntiHack.h"
#include "ConnectEx.h"
#include "SpeedFix.h"
#include "TMemory.h"
#include "Configs.h"
#include "Other.h"
#include "NewHpBar.h"
#include "ChatExpanded.h"
#include "Graphics.h"
#include "QuestSystem.h"
#include "ItemPrice.h"
#include "SocketItem.h"
#include "Monster.h"
#include "DeBug.h"
#include "ItemSmokeEffect.h"
#include "Map.h"
#ifdef _GRAND_SYSTEM_
#include "Bow.h"
#endif
#include "NewPartyBuff.h"
#include "NewParty.h"
#include "Fog.h"
#include "AntiCheat.h"
#include "PartySearch.h"
#include "SecurityScript.h"
#include "PersonalShopZt.h"
#include "AntiCheatPlus.h"
#include "BufferSystem.h"
#include "Smithy.h"
#include "ZtLicense.h"
#include "InfoLog.h"
#include "AddPoints.h"
#include "CustomMenu.h"
#include "DonateShop.h"
#include "ItemRank.h"
#include "FileMemory.h"
#include "ServerInfo.h"
#include "WingEffect.h"
#include "EncDec.h"
#include "MapManager.h"
#include "ZtText.h"
#include "PremiumSystemZt.h"
#include "PKClear.h"
#include "ItemSetOption.h"
#include "ReferralSystem.h"
#include "ZtWinQuestSystem.h"
#include "PickUpItemInfo.h"
#include "Skill.h"
#include "ItemPacket.h"
#include "Effect.h"
#include "CreateEffect.h"
#include "DynamicEffect.h"
#include "Fps.h"
#include "ItemMarket.h"
#include "PetZt.h"
#include "InterfaceZt.h"
#include "Cape.h"
#include "RenderEffect.h"
#include "MapTeleport.h"
#include "MuLua.h"
#include "MiniMapZt.h"
#include "Inter3.h"
#include "SelectChar.h"
#include "PacketManager.h"
#include "giocp.h"
#include "packetsend_hooks.h"
// -------------------------------------------------------------------------------
#if(ENABLE_DUMP_CHECK)
	
#define MAX_DUMP_OFFSETS	3
#define MAX_DUMP_SIZE		32

BYTE btJar [] = { 
255,	037,	000,	032,	064,	000,	000,	000,	000,	000,	000,	
000,	000,	000,	000,	000,	000,	000,	000,	000,	000,	000,	
000,	000,	000,	000,	000,	000,	000,	000,	000,	000
};

bool DumpCheck(HANDLE hProcess) 
{
	//for( int i = 0; i < MAX_PROCESS_DUMP; i++ )
	{
		char aTmpBuffer[MAX_DUMP_SIZE];
		SIZE_T aBytesRead = 0;
		ReadProcessMemory(hProcess, (LPCVOID)0x00E18C1E, (LPVOID)aTmpBuffer, sizeof(aTmpBuffer), &aBytesRead);

		if(memcmp(aTmpBuffer, btJar, MAX_DUMP_SIZE) == 0)
		{
			//this->Write(DAMP_LOG_TEXT, g_ProcessesDumps[i].Name);

			MessageBox(pGameWindow, "DumpCheck", "DumpCheck", ERROR);

			return true;
		}
	}
	return false;
}

void DumpRun() 
{
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(hProcessSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 pe32;
		pe32.dwSize = sizeof(PROCESSENTRY32);

		if(Process32First(hProcessSnap, &pe32))
		{
			do
			{
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
				if(hProcess != NULL)
				{
					if(DumpCheck(hProcess))
					{
					}
				}
			}
			while(Process32Next(hProcessSnap, &pe32));
		}
	}
	CloseHandle(hProcessSnap);
}
#endif
#ifdef _ANTI_HACK_
DWORD WINAPI Timer(LPVOID lpParam)
{
	Sleep(5000);
	while(true)
	{
		if(bAntiHack)
		{
#ifdef ztDEBUG_CODE
			//gConsole.Output(cGREEN,"SystemProcessesScan");
#endif
			SystemProcessesScan();
		}
		
		Sleep(5000);
	}
	return 1;
}
#endif
  // -------------------------------------------------------------------------------

DWORD WINAPI ExTimer(LPVOID lpParam)
{
	Sleep(1000);

	while(true)
	{
		if(gObjUser.Premium > 0)
		{
			gObjUser.Premium--;
		}

		#if(CUSTOM_EMULATOR_KEY)

		gController.ThreadhMouseAutoKey();

		#endif



		Sleep(1000);
	}
	return 1;
}
  // -------------------------------------------------------------------------------

void (*ProcLibrary)(void);


bool GetFalse(int a1)
{
	return true;
}

void LoadDll()
{
	HMODULE hLibrary = LoadLibrary("Effect.dll");

	if(hLibrary)
	{
		ProcLibrary = (void (*)(void))GetProcAddress(hLibrary, "ikennylee");

		if(ProcLibrary)
		{
			ProcLibrary();
		}
		else
		{
			MessageBox(0, "GetProc Error Effect.dll", "GetProc Error", ERROR);
		}
	}
	else
	{
		MessageBox(0, "Load Error Effect.dll", "Load Error", ERROR);
	}
}

void InitLoginTheme()
{
	HMODULE hModule = LoadLibraryA("logintheme.dll");

	void (*EntryProc)(char*) = ((void(*)(char*))GetProcAddress(hModule, "EntryProc"));

	if (EntryProc)
	{
  //choose one
  //EntryProc("EX700");
  //0x008C497D
		EntryProc("SS2");

		/*
		SetByte((LPBYTE)0x0057F0FC, 0xE9);
		SetByte((LPBYTE)0x0057F0FD, 0x4A);
		SetByte((LPBYTE)0x0057F0FE, 0x01);
		SetByte((LPBYTE)0x0057F0FF, 0x00);
		SetByte((LPBYTE)0x0057F100, 0x00);
		SetByte((LPBYTE)0x0057F101, 0x90);

		SetByte((LPBYTE)0x00503834, 0xEB);
		*/

	}
}

extern "C" __declspec(dllexport)void ExInit()
{
	DWORD OldProtect;
	// ----
	if(VirtualProtect(LPVOID(0x401000),0xD21FFF,PAGE_EXECUTE_READWRITE,&OldProtect))
	{

		//Init Interface Ex700
		InitInterZt();

#if(ENABLE_DEBUG)
		DeBugLoad();
#endif
#if(ENABLE_ENCODER)
		g_EncDec.Load();
#endif

#ifdef PROTECT
	if( VMProtectIsDebuggerPresent(TRUE) != 0 )
	{
		MessageBox(0, "Protect system found debugger, process will be closed", "ExCheatGuard", ERROR);
		ExitProcess(0);
	}
#endif
#if(ENABLE_EXPROTECTOR1)
	if(!LoadLibrary("wz_up.dll"))
	{
		MessageBox(0, "Protect", "Protect Client Error", ERROR);
		ExitProcess(0);
	}

	//HMODULE hLibrary = LoadLibrary("Effect.dll");

#endif
#if(ENABLE_EXPROTECTOR2)
	if(!LoadLibrary("Protect.dll"))
	{
		MessageBox(0, "Protect", "Protect Client Error", ERROR);
		ExitProcess(0);
	}

	//HMODULE hLibrary = LoadLibrary("Effect.dll");

#endif
#if(MANGOL_DEV)
	//LoadLibrary("Clicker.dll");

	if(!LoadLibrary("Clicker.dll"))
	{
		MessageBox(0, "Clicker", "Clicker Client Error", ERROR);
		ExitProcess(0);
	}
#endif
	//gConfig.Configs();

#ifdef _LAUNCHER_
	if(gConfig.LauncherActive == 1)
	{
		char **	Command	= 0;
		CommandLineToArg(GetCommandLine(), &Command);
		if( strcmp(gConfig.LauncherParameters, Command[1]) )
		{
			MessageBox(0, "Please start game from Launcher", "Start Error", ERROR);
			ExitProcess(0);
		}
	}
#endif
							
#if(ANTI_CHEAT_PLUS==TRUE)
	g_AntiCheatPlus.Load();
#endif

#if(ANTI_CHEAT==TRUE) 
#endif
#if(DLL_ZT_ANTI_CHEAT==TRUE)
#endif
	// ----
	
	LoadLibrary("ttlci.dll");

#if(THINNAKORN_MAC)
	LoadLibrary("vcorp.dll");
	LoadLibrary("EliteBlock.dll");
#endif
	// ----
	gController.Load();
	gStart.Load();

	gTrayMode.Load();

//#if(!ENABLE_INDEV_NETWORK)
	gProtocol.Load();
//#endif



	gInterface.Load();
	gCamera.Load();
#if(exCHATWND)
	ChatWndHooks();
#endif
	initEffectSkil();
	gVisualFix.InitVisualFix();


	gItem.Load();

	InitItemAsm();
#if(exPRIVIEWESET)
	gMakePreviewCharSet.Load();
#endif
//#ifdef ztRAGESYSTEM
	gRageSystem.Load();
//#endif
	gObjUser.Load();
#if(ztRECONNECT)
	gConnectEx.Load();
#endif
#if(_SPEED_FIX_==TRUE)
	InitAttackSpeed();
#endif
//#if(v103K)
	g_MiniMap.Load();
//#endif
#ifdef NEW_HP_BAR
	gViewePortInfo.InitNewHpBar();
#endif
	gChatExpanded.Load();
#if(NEW_GLOW_EFFECT)
	if(gGlowEffect)
	{
		gGraphics.Load();
	}
#endif
#ifdef _ITEM_PRICE_MANAGER_
	gItemPrice.Load();
#endif
	gSocketItem.Load();
#ifdef _NEW_MONSTER_
	//gMonster.Load();
#endif
#ifdef ztDEBUG_CODE
	//DeBug_Init();
#endif
#if NEW_PARTY_BUFF == TRUE
	g_NewPartyBuff.Load();
#endif
//#if _NEW_PARTY_SYSTEM_ == TRUE
	{
		g_Party.Load();
	}
//#endif
#if(CUSTOM_PARTY_SEARCH==TRUE)
		g_PartySearch.Load();
#endif
//#if(CUSTOM_PERONAL_ZT==TRUE)
		g_PersonalShopZt.Init();
//#endif
#if(CUSTOM_NPC_BUFFER==TRUE)
		g_BufferSystem.Load();
#endif
#if(CUSTOM_SMITHY == TRUE)
		g_Smithy.Load();
#endif
#if(CUSTOM_ZT_CHAT==TRUE)
		g_InfoLog.Load();
#endif
#if(CUSTOM_MENU)
		g_CustomMenu.Load();
#endif
#if(CUSTOM_ITEM_RANK==TRUE)
		g_ItemRank.Load();
#endif
#ifdef _ANTI_HACK_
	CloseHandle(CreateThread(NULL,0,Timer,NULL,0,NULL));
#endif
	CloseHandle(CreateThread(NULL,0,ExTimer,NULL,0,NULL));

#if(ENABLE_FILEMEMORY)
	FileMemoryLoad();
#endif

#if(CUSTOM_NEW_MAP)
	g_Map.Load();
#endif
//#if(BASSREFLEXIVE)
	g_ServerInfo.Load();
//#endif
#if(CUSTOM_WINGSEFFECT)
	g_WingEffect.Load();
#endif
#if(ENABLE_CHANGE)
	g_Text.Load();
#endif
#if(CUSTOM_MAP_MANAGER)
	g_MapManager.Load();
#endif
#if(CUSTOM_ZTTEXT)
	g_ZtText.Load();
#endif
#if(CUSTOM_PREMIUM_SYSTEM==TRUE)
	g_PremiumSystemZt.Load();
#endif
#if(CUSTOM_PKCLEAR_NPC==TRUE)
	g_PKClear.Load();
#endif
#if(CUSTOM_REFERAL_SYSTEM)
	g_ReferralSystem.Load();
#endif

	gMonster.ReadName(".\\Data\\Local\\Eng\\Npcname(eng).txt");

#if(CUSTOM_ZT_QUEST_SYSTEM==TRUE)
	g_ZtWinQuestSystem.Load();
#endif	
#if(CUSTOM_PICKUP_ITEM_INFO)
	g_PickUpItemInfo.Load();
#endif
#if(DEV_SKILL)
	g_Skill.Load();
#endif
#if(DEV_PACKET_ITEM)
	g_ItemPacket.Load();
#endif

#if(DEBUG_FPS)
	g_Fps.Load();
#endif

#if(ENABLE_TEST)
	//-> Fix BC Master Disable
	//SetByte((LPVOID)(0x008742AC+3), 0x07);
	//SetByte((LPVOID)(0x00874C04+6), 0x07);
	//SetRange((LPVOID)(0x00874EBF), 5, ASM::NOP);
#endif

#if(ENABLE_TEST)
			//SetRange((LPVOID)0x0080F6AE, 5, ASM::NOP);	//user bar
			//SetByte((LPVOID)(0x004D9746+3), 0xE0);		//gl draw 480px

			//SetByte((LPVOID)(0x0080F683), 0xE9);	//disable userbar
			//SetByte((LPVOID)(0x0080F683+1), 0x97);
			//SetByte((LPVOID)(0x0080F683+2), 0x00);
			//SetByte((LPVOID)(0x0080F683+3), 0x00);
			//SetByte((LPVOID)(0x0080F683+4), 0x00);

	

			//004D9746
	//0080F6AE
	//420220 - bitmap load
	//6363D0 - gl vieweport
			//004D9746 - 1b0
#endif
#if(DEV_EFFECT)
	gEffect.Load();
#endif
#if(DEV_EFFECT2)
	gCreateEffect.Load();
#endif

#if(ENABLE_RENDER_EFFECT)
	g_RenderEffect.Load();
#endif

		//#if(ENABLE_ITEMSETOPTION)
		//g_ItemSetOption.Load();
		//#endif
		//007E1B7F
		//SHL EDX,9 <<
		//SAR ECX,7 >>
		//007E1B75
		//C1 E1 04

		//007E1B75 nop
		//SetRange((LPVOID)0x007E1B75, 3, ASM::NOP);
		//SetRange((LPVOID)0x007E519C, 6, ASM::NOP);	//ItemAddOption in Wings

	
		//SetRange((LPVOID)0x007E5188, 20, ASM::NOP);	// ItemAddOption in Wings

		//007E5195 -> CALL CHECK WINGS

		//SetOp((LPVOID)0x007E3FC0, GetFalse, ASM::CALL);
		//SetOp((LPVOID)0x007E4766, GetFalse, ASM::CALL);
		//SetOp((LPVOID)0x007E5195, GetFalse, ASM::CALL);

	
	

		//skill
		//006D81CC
		// 006D80F0 - nop 2 

		#if(ENABLE_CHECK)
		//Credit Shop
		//SetRange((LPVOID)0x007D3C1C, 5, ASM::NOP);	
		//SetOp((LPVOID)0x007D3C1C, _007D3C16, ASM::JMP);
		//SetRange((LPVOID)0x00811D6F, 5, ASM::NOP);	
		//SetOp((LPVOID)0x00811D6F, _00811D69, ASM::JMP);
		//SetOp((LPVOID)0x007D3C1C, (LPVOID)0x00811F40, ASM::JMP);	// disable key X
		 SetOp((LPVOID)0x007D3C16, (LPVOID)0x007D3DF5, ASM::JMP);	// disable key X
		 
		//SetRange((LPVOID)0x00784B77, 5, ASM::NOP);
		#endif
		#if(DEV_PLAYERSHOP)
		g_ItemMarket.Load();
		#endif
		#if(ENABLE_PETZT)
		g_PetZt.Load();
		#endif
		#if(DEV_CAPE)
		gCapeAnimation.Load();
		#endif
		#if(CUSTOM_MODEL_EFFECT)
		g_ModelEffect.Load();
		#endif
		//#if(CUSTOM_MAP_TELEPORT)
		//if(g_ZtLicense.user.CustomMapTeleport)
		//{
		//	g_MapTeleport.Load();
		//}
		//#endif

		#if(ENABLE_CHARACTER_ACTION)
		gSelectChar.Load();
		#endif

		if(gLoadVcorpDll)
		{
			LoadLibrary("vcorp.dll");
		}

		if(gLoadMUAutoClicker)
		{
			LoadLibrary("MUAutoClicker.dll");
		}

		//LoadLibrary("logintheme.dll");
		//InitLoginTheme();
		#if(DEV_SELECT_CHARACTER)
		SCharacterS3();
		#endif



		#if(ENABLE_CLIENT_DLL)
		LoadLibraryA("ClientEx.dll");
		#endif

#if(ENABLE_INDEV_SOCKET)
		gPacketManager.LoadEncryptionKey("Data\\Enc1.dat");

		gPacketManager.LoadDecryptionKey("Data\\Dec2.dat");

		gPacketManager.Init();
#endif

		#if(ENABLE_INDEV_NETWORK)
		NetworkLoad();
		//SetOp((LPVOID)PROTOCOL_CORE_HOOK, (LPVOID)ProtocolCoreASM, ASM::JMP);
		#endif
	}
	else
	{
		
	}
}

#if(ENABLE_RAM_MIN)
void RamOptimization(LPVOID lpThreadParameter) 
{ 
	HANDLE hCurrentProcess = NULL;

	while(TRUE) 
	{ 
		Sleep(5000);

		hCurrentProcess = GetCurrentProcess();

		SetProcessWorkingSetSize(hCurrentProcess, 0xFFFFFFFF, 0xFFFFFFFF); 

		SetThreadPriority(hCurrentProcess, THREAD_BASE_PRIORITY_MAX); 
	} 
}
#endif

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch(dwReason)
	{
	case DLL_PROCESS_ATTACH:
		{
		#if(ENABLE_INDEV_NETWORK)
		//HookPacketSend();
		#endif
#if(ENABLE_RAM_MIN)
			CreateThread (0, 0, (LPTHREAD_START_ROUTINE)RamOptimization, 0, 0 , 0);
#endif

#if(ZT_LICENSE==TRUE)
			g_ZtLicense.Load();
#endif
			gController.Instance = hModule;
#if(ztCONSOLE)
			gConsole.InitCore();
#endif
			gConfig.LoadGame();
//#if(NEW_QUEST_SYSTEM)
			gQuestSystem.LoadGame();
//#endif
			if (gFogEffect)
			{
				g_Fog.Load();
			}

#if(SECURITY_SCRIPT==TRUE)


//	if(!strcmp(a1,"Data\\World1\\EncTerrain1.map"))
	{
	//	Packed = true;
	}

	//if(Packed==true)
	{
		//g_SecurityScript.ReadScript("Data\\World1\\EncTerrain1.obj");
		//g_SecurityScript.WriteScript("Data\\World1\\EncTerrain1.obj");
	}

	//Result = sub_5D6E50(a1);

	//if(Packed==true)
	{
		//g_SecurityScript.WriteScript(a1);
	}

			//g_SecurityScript.Test();
#endif

		//MULua * TempLua = new MULua(false);
		//TempLua->DoFile(Pasth.GetPath("\\Scripts\\Misc\\ExpCalc.lua"));
		//TempLua->Generic_Call("SetExpTable_Normal", "i>d", n, &exp);
			//g_Log.Add("[NORMAL EXP] [LEVEL %d] [EXP %I64d]", n, gLevelExperience[n]);
		//}

		//delete TempLua;

		#if(ENABLE_DUMP_CHECK)
		DumpRun();
		#endif

		}
		break;
	case DLL_THREAD_ATTACH:
		break;

	case DLL_THREAD_DETACH:
		break;
		
	case DLL_PROCESS_DETACH:
		{
			gConfig.SaveGame();
//#if(NEW_QUEST_SYSTEM)
			gQuestSystem.SaveGame();
//#endif
			if (gFogEffect)
			{
				g_Fog.End();
			}
#if(SECURITY_SCRIPT==TRUE)

	{
		//g_SecurityScript.WriteScript("Data\\World1\\EncTerrain1.obj");
	}

#endif
	//ExitProcess(0);
		}
		break;
	case WM_CLOSE:
		//ExitProcess(0);
		break;
	}
	return true;
}
  // -------------------------------------------------------------------------------

