#pragma once
// -------------------------------------------------------------------------------
#define USE_ZT700_INTERFACE		1
// -------------------------------------------------------------------------------
#define ENABLE_PROTECT			0	//log add post item
#define ENABLE_CONSOLE			0
#define ENABLE_DEBUG			0
#define ENABLE_AUTOLOGIN		0
#define ENABLE_FILEMEMORY		0
#define ENABLE_TEST				0
#define ENABLE_START_MU			0
#define ENABLE_DEV				0
#define ENABLE_CHECK			0
#define ENABLE_ENCODER			0
#define ENGINE_DEBUGER			0
#define ENABLE_CLIENT_DLL		1
// -------------------------------------------------------------------------------
#define ENABLE_ZTPROTECTOR		0
#define ENABLE_ZTPROTECTOR1		0
#define ENABLE_ZTPROTECTOR2		0
#define ENABLE_RAM_MIN			0
// -------------------------------------------------------------------------------
#define ENABLE_IP_ADDRESS		0
#define TEXT_IP_ADDRESS			"192.168.0.115"	//"190.2.145.164"//"192.168.23.1"//"144.91.69.0"	//"192.168.70.1"//"151.80.198.97"	//"192.168.70.1"	//"213.108.4.70" //"192.168.70.1"	//"192.168.70.1"
// -------------------------------------------------------------------------------
#define DEV_INTERFASE_SEASON3	1
#define DEV_INTERFACE_ZT700		0
// -------------------------------------------------------------------------------
#define INTERFACE_LOGIN_IMG		0	//private
#define THINNAKORN_MAC			0	//private
#define BASSREFLEXIVE			0	//private
#define EPICMU					0
#define LANG_CHINA				0
#define ENABLE_CHANGE			0	//need 1
#define LICENSE_MUEVIL			0
//#define _SERIAL_				"G3qF7QqTS21ilL7b"
// -------------------------------------------------------------------------------
#define WINDOW_TITLE			"MU Online"
// -------------------------------------------------------------------------------
#if(ENABLE_PROTECT)
#define PROTECT
#endif
// -------------------------------------------------------------------------------
#include <Windows.h>
#include <WindowsX.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <stdarg.h>
#include <process.h>
#include <locale.h>
#include <WinBase.h>
#include <tlhelp32.h>
#include <WinSock.h>
#include <gl\GL.h>
#include "glext.h"
#include "..\\Cg\cg.h"
#include "..\\Cg\cgGL.h"
#include "AntiCheat.h"
#include "VMProtectSDK.h"
#include <vector>
// -------------------------------------------------------------------------------
#include "Text.h"
// -------------------------------------------------------------------------------
#pragma comment(lib,"ws2_32.lib") //<- we need this lib for winsock
#pragma comment(lib, "Opengl32.lib")
#pragma comment(lib, "cg.lib")
#pragma comment(lib, "cgGL.lib")
#ifdef PROTECT
#pragma comment(lib, "VMProtectSDK32.lib")
#endif
// -------------------------------------------------------------------------------
#include "..\\lua\\include\\lua.hpp"
#pragma comment(lib, "..\\lua\\lib\\lua52.lib")
// -------------------------------------------------------------------------------
#if(ANTI_CHEAT_DEBUG==TRUE)
#define ztCONSOLE				1
#endif
// -------------------------------------------------------------------------------
#if(ENABLE_CONSOLE)
#define ztCONSOLE				1	//Консол?
#endif
#if(ENABLE_DEBUG)
#define ztDEBUG_CODE			1	//Debug Режи?
#endif
// -------------------------------------------------------------------------------
#define ANTI_CTRL				1
#define OLD_HP_BAR				0
#define NEW_HP_BAR				1
#define FULL_HD					1
#define NEW_GLOW_EFFECT			1
//#define NEW_QUEST_SYSTEM		1
#define ztRECONNECT				1
//#define ztRAGESYSTEM			1	//Систем?ярост? не работает бе?интерфейса
#define AUTO_PARTY				1
//#define _ANTI_HACK_			1
#define _LAUNCHER_				1
#define _ITEM_PRICE_MANAGER_	1
#define HPBAR_UPDATE			1
#define AUTO_LOGIN				1
//#define ADD_NEW_EFFECT_WINGS	1
#define _NEW_MONSTER_			1
#define _PRIVATE_MODULE_		1
#define _COINS_					1
#define PRIVATE_MODULE			1
#define NEW_PARTY_BUFF			1
#define ZT_SPEED_CALC			1
 // -------------------------------------------------------------------------------
#define _GRAND_SYSTEM_
#define NEWWINGS6
#define PREM_TYPE
#define EXCLUSIVE_AMYLET
#define VIEW_MONSTER
#define CUSTOM_PARTY_SEARCH		TRUE
#define SECURITY_SCRIPT			FALSE
#define CUSTOM_PERONAL_ZT		TRUE
// -------------------------------------------------------------------------------
#define DLL_ZT_ANTI_CHEAT		TRUE
// -------------------------------------------------------------------------------
#define _SPEED_FIX_				TRUE
// -------------------------------------------------------------------------------
//#define ACHIEVEMENTS_SYSTEM
#define CUSTOM_NEWS				TRUE
#define CUSTOM_NEWS				TRUE
#define ANTI_CHEAT_PLUS			TRUE
#define CUSTOM_NPC_BUFFER		TRUE
// -------------------------------------------------------------------------------
#define SPEED_BUG_FIX			0	// <== need recode ZtGames normal code
// -------------------------------------------------------------------------------
#define CONNECT_IP_ENCRYPT		0
// -------------------------------------------------------------------------------
#define JEWEL_OF_PVP			1
#define CUSTOM_SMITHY			1
#define ZT_LICENSE				TRUE
#define OFFLINE_MODE			1
#define ADD_OFFMODE_PICKUP		1
// -------------------------------------------------------------------------------
#define FIX_MINIMAP				1
#define CUSTOM_MARRIAGE			1	// Свадьб?
#define CUSTOM_ZT_CHAT			1
#define ADD_JEWELBANK_CREATEON	1
#define CUSTOM_ADD_POINTS		1
#define ADD_ADD_POINT			1	// ?
#define ADD_ADD_RESETPOINT		1
#define CUSTOM_MENU				1
#define ADD_PARTY_LEADER		1
#define CUSTOM_RESETSYSTEM		1
#define DONATE_SHOP				TRUE
// -------------------------------------------------------------------------------
#define EVENT_DUNGEON_SIEGE		1
#define CUSTOM_ITEM_RANK		TRUE
#define FIX_GUILD_CRASH			1
#define CUSTOM_SERVER_TIME		1
#define ANTI_CHEAT_PLUS_CRC		0
#define EVENT_TEAM_VS_TEAM		1
#define TEAM_VS_TEAM_INFO		1
#define CUSTOM_SOUND			1
#define CUSTOM_NEW_MAP			1
// -------------------------------------------------------------------------------
#define SYSTEM_ACHIEVEMENTS		1
#define CUSTOM_MINIMENU			1
#define CUSTOM_SERVERINFO		1
// -------------------------------------------------------------------------------
// 04.09.2017
// -------------------------------------------------------------------------------
#define CUSTOM_ZT_TELEPORT		TRUE
#define CUSTOM_WINGSEFFECT		1
#define CUSTOM_AUTOCTRL			1
#define CUSTOM_WIN_SETTINGS		1
#define CUSTOM_PLAYERTITLE		0
#define FIX_AGM_REQVALLIANCE	TRUE
// -------------------------------------------------------------------------------
#define CUSTOM_NEW_MAP			1
#define CUSTOM_MAP_MANAGER		0	//Disable not work
#define CUSTOM_ZTTEXT			1
#define CUSTOM_PREMIUM_SYSTEM	1
#define CUSTOM_ZT_TELEPORT_EVO	TRUE
#define CUSTOM_PKCLEAR_NPC		TRUE
#define CUSTOM_ACCOUNT_SECURITY	TRUE
// -------------------------------------------------------------------------------
#define CUSTOM_REFERAL_SYSTEM	1
#define ENABLE_ITEMSETOPTION	1
#define ENABLE_CHATCOLOR		1
#define CUSTOM_POSTITEM			1
#define CUSTOM_MINIMAP			1
#define CUSTOM_AUTOHP			1
#define USER_BUFF_ICON_ZT		1
#define CUSTOM_BUFF_INFO		1
#define CUSTOM_ZT_QUEST_SYSTEM	1		// [-] Оконная квес?систем?
// --------------------------------
#define RF_NEW_GLOV				0	//ОТКЛЮЧАЕ?ГРАН?ХИРО ИТЕМ
#define GLOV1					0x610	//620
#define GLOV2					0x611	//621
#define GLOV3					0x612	//620
#define GLOV4					0x613	//621
// -------------------------------------------------------------------------------
// 23.06.2018
// -------------------------------------------------------------------------------
#define CUSTOM_PICKUP_ITEM_INFO	1
#define FIX_CORD_ITEM_TEXT		1
#define CUSTOM_MINIMAP_PARTY	1
// -------------------------------------------------------------------------------
#define CUSTOM_EMULATOR_KEY		1
#define CUSTOM_MUHELPER_INV		1
#define CUSTOM_LOTTERY			0	//...
#define DEV_USERSHOP			0
// itemPos
#define ADD_CTRL_KEY			1
#define FIX_MONSTER_HP			1
#define DEV_GUILDBANK			1
#define DEV_STORAGE				1
// -------------------------------------------------------------------------------
#define INTERFACE_JEWELBANK		1
// -------------------------------------------------------------------------------
#define DEV_EFFECT				0
#define DEV_EFFECT2				0
#define DEV_FPS					1
#define DEV_SKILL				0
// -------------------------------------------------------------------------------
#define CUSTOM_DINAMIC_EFFECT	1
// -------------------------------------------------------------------------------
#define DEBUG_FPS				0
// -------------------------------------------------------------------------------
// -> New Dev
#define DEV_ZTMENU_V3			1
#define DEV_STATS_ADVANCE		1
#define DEV_PLAYERINFO			0
#define DEV_DAMAGE_TABLE		1
#define ADD_OFFMODE_TIMER		1
// -------------------------------vv------------------------------------------------
#define NEXT_INTERFACE_MANAGER	1
#define ENABLE_PETZT			1
#define USERPANEL				0	///
// -------------------------------------------------------------------------------
#define ENABLE_AGMASTER			1
#define DEV_CAPE				0
#define ENABLE_DAMAGEROT		1
/* АГ?0x0078F41E - прие??клан */
// -------------------------------------------------------------------------------
//	01.12.2019 next dev
// -------------------------------------------------------------------------------
#define CUSTOM_MODEL_EFFECT		0
#define CUSTOM_MAP_TELEPORT		1
#define CUSTOM_VALUE_MENU		1
#define FIX_VIEWE_MONSTER		0	//void __usercall MoveHero(int a1@<esi>)
#define CUSTOM_CAMERA_MOVE		1	//
#define ENABLE_NEW_EFFECT		0
#define FIX_OBJECT_VIEWE		0
// -------------------------------------------------------------------------------
#define ENABLE_LUA				0
#define ENABLE_RENDER_EFFECT	0
// -------------------------------------------------------------------------------
#define MANGOL_DEV				0
#define	DEV_VALERIY_CHIBUK		1
// -------------------------------------------------------------------------------
#define ENABLR_DEN_DEV			0
// -------------------------------------------------------------------------------
#define ENABLE_MINIMAP_ZT		1
// -------------------------------------------------------------------------------
#define DEV_SELECT_SERVER		1
#define DEV_SELECT_CHARACTER	0
// ----------------------------------------------------------------------------------------------
#define ENABLE_ENCDEC_EVOMU		0
// ----------------------------------------------------------------------------------------------
#define ENABLE_MULTI_CHAR		0
#define ENABLE_DUMP_CHECK		0
// ----------------------------------------------------------------------------------------------
#define DEV_PACKET_ITEM			0
#define DEV_ITEM_LEVEL			0
// ----------------------------------------------------------------------------------------------
#define DEV_MAX_BUFF_32			0
#define ENABLE_CHARACTER_ACTION	0

#define ENABLE_BUFFICON_HD		1
#define ENABLE_VERSION_ME		1
// ----------------------------------------------------------------------------------------------
#define ENABLE_GRAND_NEEDITEM	1
//28.05.2020
#define ENABLE_PACK_MANAGER		0
#define MOVE_ITEM				0
#define DEBUG_MONSTER_LOAD		0
#define ENABLE_MARKET_BUTTON	1
// ----------------------------------------------------------------------------------------------
#define ENABLE_INDEV_SOCKET		0
#define ENABLE_INDEV_NETWORK	0
// ----------------------------------------------------------------------------------------------
#define ENABLE_CHAT_SMILE		1
#define DISABLE_C_INFO			0
#define ENABLE_UTEXT_COLOR		0
#define ENABLE_CUSTOMFONTZT		1