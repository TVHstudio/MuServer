#pragma once
// ----------------------------------------------------------------------------------------------

#include "Defines.h"
#include "Import.h"
// ----------------------------------------------------------------------------------------------

#define INTERFACE_DEBUG		0
#define MAX_WINDOW_ZT		100
#define MAX_BG_WIDTH		230
// ----------------------------------------------------------------------------------------------


enum ObjectID
{
	eTIME = 1,
	eRageSystem,
	eRageTable,
	eRageClose,
	eRagePointTable,
	eRageIcon1,
	eRageIcon2,
	eRageIcon3,
	eRageIcon4,
	eRageIcon5,
	eRageIcon6,
	eRageIcon7,
	eRageIcon8,
	eRageIcon9,
	eRageIcon10,
	eRageIcon11,
	eRageIcon12,
	eRageIcon13,
	eRageIcon14,
	eRageIcon15,
	eRageIcon16,
	eRageIcon17,
	eRageIcon18,
	eRageIcon19,
	eRageIcon20,
	eRageIcon21,
	eRageIcon22,
	eRageIcon23,
	eRageIcon24,
	eRageIcon25,
	eRageIcon26,
	eRageIcon27,
	eRageIcon28,
	eRageIcon29,
	eRageIcon30,
	eRageIcon31,
	eRageIcon32,
	eRageIcon33,
	eRageIcon34,
	eRageIcon35,
	eRageTeleport,
	eRagePet,
	eRageReset,
	eJewelsBank,
	//---
	eRESET_DIV,
	// ----
	eMQUEST_MAIN,
	eMQUEST_TITLE,
	eMQUEST_FRAME,
	eMQUEST_FOOTER,
	eMQUEST_DIV,
	eMQUEST_CLOSE,
	eMQUEST_INFOBG,
	eMQUEST_INFOBG2,
	eMQUEST_MONEYBG,
	eMQUEST_FINISH,
	eMQUEST_COUNT,
	// ----
	ePT_SEARCH_USER_MAIN,
	ePT_SEARCH_USER_TITLE,
	ePT_SEARCH_USER_FRAME,
	ePT_SEARCH_USER_FOOTER,
	ePT_SEARCH_USER_DIV,
	ePT_SEARCH_USER_CLOSE,
	ePT_SEARCH_USER_FINISH,
	ePT_SEARCH_USER_L,
	ePT_SEARCH_USER_R,
	ePT_SEARCH_USER_INFO,
	ePT_SEARCH_USER_INFOBG,
	ePT_SEARCH_USER_PAGEUP1,
	ePT_SEARCH_USER_PAGEUP2,
	ePT_SEARCH_USER_PAGEUP3,
	ePT_SEARCH_USER_PAGEUP4,
	ePT_SEARCH_USER_PAGEUP5,
	ePT_SEARCH_USER_PAGEUP6,
	ePT_SEARCH_USER_PAGEUP7,
	ePT_SEARCH_USER_PAGEUP8,
	ePT_SEARCH_USER_PAGEUP9,
	ePT_SEARCH_USER_PAGEUP10,
	// --
	ePT_SEARCH_MASTER_MAIN,
	ePT_SEARCH_MASTER_TITLE,
	ePT_SEARCH_MASTER_FRAME,
	ePT_SEARCH_MASTER_FOOTER,
	ePT_SEARCH_MASTER_DIV,
	ePT_SEARCH_MASTER_CLOSE,
	ePT_SEARCH_MASTER_FINISH,
	ePT_SEARCH_MASTER_LINE,
	ePT_SEARCH_MASTER_POINT,
	ePT_SEARCH_MASTER_PAGEUP,
	ePT_SEARCH_MASTER_PAGEDN,
	ePT_SEARCH_MASTER_CHECK1,
	ePT_SEARCH_MASTER_CHECK2,
	ePT_SEARCH_MASTER_CHECK3,
	ePT_SEARCH_MASTER_CHECK4,
	ePT_SEARCH_MASTER_CHECK5,
	ePT_SEARCH_MASTER_CHECK6,
	ePT_SEARCH_MASTER_CHECK7,
	ePT_SEARCH_MASTER_CHECK8,
	ePT_SEARCH_MASTER_CHECK9,
	// --
	ePT_PERSONAL_SEARCH_MAIN,
	ePT_PERSONAL_SEARCH_TITLE,
	ePT_PERSONAL_SEARCH_FRAME,
	ePT_PERSONAL_SEARCH_FOOTER,
	ePT_PERSONAL_SEARCH_DIV,
	ePT_PERSONAL_SEARCH_CLOSE,
	ePT_PERSONAL_SEARCH_L,
	ePT_PERSONAL_SEARCH_R,
	ePT_PERSONAL_SEARCH_INFO,
	ePT_PERSONAL_SEARCH_INFOBG,
	ePT_PERSONAL_SEARCH_PAGEUP1,
	ePT_PERSONAL_SEARCH_PAGEUP2,
	ePT_PERSONAL_SEARCH_PAGEUP3,
	ePT_PERSONAL_SEARCH_PAGEUP4,
	ePT_PERSONAL_SEARCH_PAGEUP5,
	ePT_PERSONAL_SEARCH_PAGEUP6,
	ePT_PERSONAL_SEARCH_PAGEUP7,
	ePT_PERSONAL_SEARCH_PAGEUP8,
	ePT_PERSONAL_SEARCH_PAGEUP9,
	ePT_PERSONAL_SEARCH_PAGEUP10,
	// --
	ePS_PRICE_MAIN,
	ePS_PRICE_TITLE,
	ePS_PRICE_FRAME,
	ePS_PRICE_FOOTER,
	ePS_PRICE_DIV,

	ePS_PRICE_ZEN,
	ePS_PRICE_BONUS,
	ePS_PRICE_BLESS,
	ePS_PRICE_SOUL,
	ePS_PRICE_CHAOS,
	ePS_PRICE_LIFE,
	//#if(DEV_PERSONAL_CREDIT)
	ePS_PRICE_CREDIT,
	//#endif
	ePS_PRICE_OK,
	ePS_PRICE_CLOSE,
	// --
#if(CUSTOM_NEWS==TRUE)
	eNEWS_MAIN,
	eNEWS_TITLE,
	eNEWS_FRAME,
	eNEWS_FOOTER,
	eNEWS_DIV,
	eNEWS_INFOBG,
	eNEWS_CLOSE,
	eNEWS_BACK,
#endif
	// --
	eNPC_BUFF_MAIN,
	eNPC_BUFF_TITLE,
	eNPC_BUFF_FRAME,
	eNPC_BUFF_FOOTER,
	eNPC_BUFF_DIV,
	eNPC_BUFF_CLOSE,
	eNPC_BUFF_LINE,
	eNPC_BUFF_BT1,
	eNPC_BUFF_BT2,
	eNPC_BUFF_BT3,
	eNPC_BUFF_BT4,
	eNPC_BUFF_BT5,
	eNPC_BUFF_BT6,
	eNPC_BUFF_BT7,

	eSMITHY_MAIN,
	eSMITHY_TITLE,
	eSMITHY_FRAME,
	eSMITHY_FOOTER,
	eSMITHY_DIV,
	eSMITHY_DIV2,
	eSMITHY_INFOBG,
	eSMITHY_CLOSE,
	eSMITHY_BACK,
	eSMITHY_TEXT,
	eSMITHY_TEXT2,
	eSMITHY_TEXT3,
	eSMITHY_TEXT4,
	eSMITHY_TEXT5,
	eSMITHY_TEXT6,
	eSMITHY_TEXT7,
	eSMITHY_TEXT8,
	eSMITHY_TEXT9,
	eSMITHY_TEXT10,
	eSMITHY_L,
	eSMITHY_R,
	eSMITHY_INFOBG2,
	eSMITHY_INFOBG3,
	eSMITHY_LINE,
	eSMITHY_POINT,
	eSMITHY_CHECK0,
	eSMITHY_CHECK1,
	eSMITHY_CHECK2,
	eSMITHY_CHECK3,
	eSMITHY_CHECK4,
	eSMITHY_CHECK5,
	eSMITHY_CHECK6,
	eSMITHY_PAGEUP,
	eSMITHY_PAGEDN,
	eSMITHY_PAGEUP2,
	eSMITHY_PAGEDN2,
	eSMITHY_BT1,
	eSMITHY_BT2,

	eSMITHY_CHECKWIN_MAIN,
	eSMITHY_CHECKWIN_TITLE,
	eSMITHY_CHECKWIN_FRAME,
	eSMITHY_CHECKWIN_FOOTER,
	eSMITHY_CHECKWIN_DIV,
	eSMITHY_CHECKWIN_OK,
	eSMITHY_CHECKWIN_CLOSE,
	eSMITHY_CHECKWIN_POINT,
	eSMITHY_CHECKWIN_CHECK,
	eSMITHY_CHECKWIN_LINE,
	eSMITHY_CHECKWIN_LINE2,

	eSMITHY_ITEM_BG,
	// --
	eCHECKWIN_MAIN,
	eCHECKWIN_TITLE,
	eCHECKWIN_FRAME,
	eCHECKWIN_FOOTER,
	eCHECKWIN_DIV,
	eCHECKWIN_OK,
	eCHECKWIN_CLOSE,
	eCHECKWIN_POINT,
	eCHECKWIN_CHECK,
	eCHECKWIN_LINE,
	eCHECKWIN_LINE2,

	eOFFMODE_INFOLINE1,
	eOFFMODE_POINT1,
	eOFFMODE_CHECK1,
	eOFFMODE_LINE1,
	eOFFMODE_POINT2,
	eOFFMODE_CHECK2,
	eOFFMODE_LINE2,
	eOFFMODE_POINT3,
	eOFFMODE_CHECK3,
	eOFFMODE_LINE3,
	eOFFMODE_POINT4,
	eOFFMODE_CHECK4,
	eOFFMODE_LINE4,
	#if(ADD_OFFMODE_TIMER)
	eOFFMODE_POINT5,
	eOFFMODE_PAGEUP,
	eOFFMODE_PAGEDN,
	#endif
	// --
	eMARRIAGE_MAIN,
	eMARRIAGE_TITLE,
	eMARRIAGE_FRAME,
	eMARRIAGE_FOOTER,
	eMARRIAGE_DIV,
	eMARRIAGE_OK,
	eMARRIAGE_CLOSE,
	eMARRIAGE_IMG,
	// ---
	eADDPOINT_MAIN,
	eADDPOINT_TITLE,
	eADDPOINT_FRAME,
	eADDPOINT_FOOTER,
	eADDPOINT_DIV,
	eADDPOINT_OK,
	eADDPOINT_CLOSE,
	eADDPOINT_INFOBG,
	eADDPOINT_INFOBG1,
	eADDPOINT_INFOBG2,
	eADDPOINT_INFOBG3,
	eADDPOINT_INFOBG4,
	eADDPOINT_INFOBG5,
	eADDPOINT_POINTUP,
	eADDPOINT_RESET,
	eADDPOINT_TABLE,
	eADDPOINT_TABLE2,
	eADDPOINT_TABLE3,

	eADDPOINTRESET_MAIN,
	eADDPOINTRESET_TITLE,
	eADDPOINTRESET_FRAME,
	eADDPOINTRESET_FOOTER,
	eADDPOINTRESET_DIV,
	eADDPOINTRESET_INFOBG,
	eADDPOINTRESET_CLOSE,
	eADDPOINTRESET_OK,

	eADDPOINTRESET_POINT1,
	eADDPOINTRESET_CHECK1,
	eADDPOINTRESET_LINE1,
	eADDPOINTRESET_POINT2,
	eADDPOINTRESET_CHECK2,
	eADDPOINTRESET_LINE2,
	// --

	eCUSTOM_MENU_MAIN,
	eCUSTOM_MENU_TITLE,
	eCUSTOM_MENU_FRAME,
	eCUSTOM_MENU_FOOTER,
	eCUSTOM_MENU_DIV,
	eCUSTOM_MENU_CLOSE,
	eCUSTOM_MENU_CHANGE_CLASS,
	eCUSTOM_MENU_RESET,
	eCUSTOM_MENU_GRANDRESET,
	eCUSTOM_MENU_PREMIUM,
	eCUSTOM_MENU_TELEPORT,
	eCUSTOM_MENU_ACCSECURITY,

	eCHANGECLASS_MAIN,
	eCHANGECLASS_TITLE,
	eCHANGECLASS_FRAME,
	eCHANGECLASS_FOOTER,
	eCHANGECLASS_DIV,
	eCHANGECLASS_CLOSE,
	eCHANGECLASS_DK,
	eCHANGECLASS_DW,
	eCHANGECLASS_AE,
	eCHANGECLASS_SU,
	eCHANGECLASS_MG,
	eCHANGECLASS_DL,
	eCHANGECLASS_RF,
	eCHANGECLASS_POINT1,
	eCHANGECLASS_CHECK1,
	eCHANGECLASS_LINE1,
	eCHANGECLASS_POINT2,
	eCHANGECLASS_CHECK2,
	eCHANGECLASS_LINE2,
	// ----
	eRESETSYSTEM_MAIN,
	eRESETSYSTEM_TITLE,
	eRESETSYSTEM_FRAME,
	eRESETSYSTEM_FOOTER,
	eRESETSYSTEM_DIV,
	eRESETSYSTEM_CLOSE,
	eRESETSYSTEM_INFOBG,
	eRESETSYSTEM_INFOBG2,
	eRESETSYSTEM_INFOBG3,
	eRESETSYSTEM_MONEYBG,
	eRESETSYSTEM_FINISH,
	eRESETSYSTEM_COUNT,
	eRESETSYSTEM_TEXT,
	// --
	eGRANDSYSTEM_MAIN,
	eGRANDSYSTEM_TITLE,
	eGRANDSYSTEM_FRAME,
	eGRANDSYSTEM_FOOTER,
	eGRANDSYSTEM_DIV,
	eGRANDSYSTEM_CLOSE,
	eGRANDSYSTEM_INFOBG,
	eGRANDSYSTEM_INFOBG2,
	eGRANDSYSTEM_INFOBG3,
	eGRANDSYSTEM_MONEYBG,
	eGRANDSYSTEM_FINISH,
	eGRANDSYSTEM_COUNT,
	eGRANDSYSTEM_TEXT,
	// ----
	eDONATE_LEFT,
	eDONATE_RIGHT,
	eDONATE_INFOBG1,
	eDONATE_INFOBG2,
	// ----
	ePT_DUNGEON_SIEGE_MAIN,
	ePT_DUNGEON_SIEGE_TITLE,
	ePT_DUNGEON_SIEGE_FRAME,
	ePT_DUNGEON_SIEGE_FOOTER,
	ePT_DUNGEON_SIEGE_DIV,
	ePT_DUNGEON_SIEGE_DIV2,
	ePT_DUNGEON_SIEGE_REG,
	ePT_DUNGEON_SIEGE_OK,

	ePT_DUNGEON_SIEGE_NAME,
	ePT_DUNGEON_SIEGE_NAME2,

	ePT_DUNGEON_SIEGE_GUILD1,
	ePT_DUNGEON_SIEGE_GUILD2,
	ePT_DUNGEON_SIEGE_GUILD3,
	ePT_DUNGEON_SIEGE_GUILD4,
	ePT_DUNGEON_SIEGE_GUILD5,
	ePT_DUNGEON_SIEGE_GUILD6,
	ePT_DUNGEON_SIEGE_GUILD7,
	ePT_DUNGEON_SIEGE_GUILD8,
	ePT_DUNGEON_SIEGE_GUILD9,
	ePT_DUNGEON_SIEGE_GUILD10,
	ePT_DUNGEON_SIEGE_NAMEOWNER,
	ePT_DUNGEON_SIEGE_DIVOWNER,
	ePT_DUNGEON_SIEGE_GUILDOWNER,

	eTEAMVSTEAM_MAIN,
	eTEAMVSTEAM_TITLE,
	eTEAMVSTEAM_FRAME,
	eTEAMVSTEAM_FOOTER,
	eTEAMVSTEAM_DIV,
	eTEAMVSTEAM_INFOBG,
	eTEAMVSTEAM_CLOSE,
	eTEAMVSTEAM_OK,
	eLORA_BATTLE_SCORE,

	eTEAMVSTEAM_STATISTIC_MAIN,
	eTEAMVSTEAM_STATISTIC_TITLE,
	eTEAMVSTEAM_STATISTIC_FRAME,
	eTEAMVSTEAM_STATISTIC_FOOTER,
	eTEAMVSTEAM_STATISTIC_DIV,
	eTEAMVSTEAM_STATISTIC_FINISH,
	eTEAMVSTEAM_STATISTIC_LINE,

	eACHIEVEMENTS_MAIN,
	eACHIEVEMENTS_PROGRESS_BG,
	eACHIEVEMENTS_MISSION_1,
	eACHIEVEMENTS_MISSION_2,
	eACHIEVEMENTS_MISSION_3,
	eACHIEVEMENTS_MISSION_4,
	eACHIEVEMENTS_MISSION_5,
	eACHIEVEMENTS_MISSION_6,
	eACHIEVEMENTS_MISSION_7,
	eACHIEVEMENTS_MISSION_8,
	eACHIEVEMENTS_MISSION_9,
	eACHIEVEMENTS_MISSION_10,
	eACHIEVEMENTS_MISSION_11,
	eACHIEVEMENTS_MISSION_12,
	eACHIEVEMENTS_MISSION_13,
	eACHIEVEMENTS_MISSION_14,
	eACHIEVEMENTS_MISSION_15,
	eACHIEVEMENTS_MISSION_16,
	eACHIEVEMENTS_MISSION_17,
	eACHIEVEMENTS_MISSION_18,
	eACHIEVEMENTS_MISSION_19,
	eACHIEVEMENTS_MISSION_20,
	eACHIEVEMENTS_MISSION_21,
	eACHIEVEMENTS_MISSION_22,
	eACHIEVEMENTS_MISSION_23,
	eACHIEVEMENTS_MISSION_24,
	eACHIEVEMENTS_MISSION_25,
	eACHIEVEMENTS_MISSION_26,
	eACHIEVEMENTS_MISSION_27,
	eACHIEVEMENTS_MISSION_28,
	eACHIEVEMENTS_MISSION_29,
	eACHIEVEMENTS_MISSION_30,
	eACHIEVEMENTS_MISSION_31,
	eACHIEVEMENTS_MISSION_32,
	eACHIEVEMENTS_MISSION_33,
	eACHIEVEMENTS_MISSION_34,
	eACHIEVEMENTS_MISSION_35,
	eACHIEVEMENTS_MISSION_36,
	eACHIEVEMENTS_MISSION_37,
	eACHIEVEMENTS_MISSION_38,
	eACHIEVEMENTS_MISSION_39,
	eACHIEVEMENTS_MISSION_40,
	eACHIEVEMENTS_MISSION_41,
	eACHIEVEMENTS_MISSION_42,
	eACHIEVEMENTS_MISSION_43,
	eACHIEVEMENTS_MISSION_44,
	eACHIEVEMENTS_MISSION_45,
	eACHIEVEMENTS_MISSION_46,
	eACHIEVEMENTS_MISSION_47,
	eACHIEVEMENTS_MISSION_48,
	eACHIEVEMENTS_MISSION_49,
	eACHIEVEMENTS_MISSION_50,

	eACHIEVEMENTS_PANEL,
	eACHIEVEMENTS_DAMAGE,
	eACHIEVEMENTS_DEFENCE,
	eACHIEVEMENTS_LIFE,
	eACHIEVEMENTS_EXELENT,
	eACHIEVEMENTS_CRITICAL,

	eMINIMENU_MAIN,
	eMINIMENU_TITLE,
	eMINIMENU_FRAME,
	eMINIMENU_FOOTER,
	eMINIMENU_LINE,
	eMINIMENU_ARROW_L,
	eMINIMENU_ARROW_R,
	eMINIMENU_BT1,
	eMINIMENU_BT2,
	eMINIMENU_BT3,
	eMINIMENU_BT4,
	eMINIMENU_BT5,
	eMINIMENU_BT6,
	eMINIMENU_BT7,
	eMINIMENU_BT8,
	eMINIMENU_BT9,

	eMINIMENU_BT10,
	eMINIMENU_BT11,
	eMINIMENU_BT12,
	eMINIMENU_BT13,
	eMINIMENU_BT14,
	eMINIMENU_BT15,
	eMINIMENU_BT16,
	eMINIMENU_BT17,
	eMINIMENU_BT18,
	eMINIMENU_BT19,
	eMINIMENU_BT20,
	eMINIMENU_BT21,
	eMINIMENU_BT22,
	eMINIMENU_BT23,

	eSETTINGS_MAIN,
	eSETTINGS_TITLE,
	eSETTINGS_FRAME,
	eSETTINGS_FOOTER,
	eSETTINGS_DIV,
	eSETTINGS_INFOBG,
	eSETTINGS_CLOSE,
	eSETTINGS_FINISH,
	eSETTINGS_LINE1,
	eSETTINGS_POINT1,
	eSETTINGS_CHECK1,
	eSETTINGS_LINE2,
	eSETTINGS_POINT2,
	eSETTINGS_CHECK2,
	eSETTINGS_LINE3,
	eSETTINGS_POINT3,
	eSETTINGS_CHECK3,
	eSETTINGS_LINE4,
	eSETTINGS_POINT4,
	eSETTINGS_CHECK4,
	eSETTINGS_LINE5,
	eSETTINGS_POINT5,
	eSETTINGS_CHECK5,
	eSETTINGS_LINE6,
	eSETTINGS_POINT6,
	eSETTINGS_CHECK6,
	// --
	eTELEPORT_MAIN,
	eTELEPORT_TITLE,
	eTELEPORT_FRAME,
	eTELEPORT_FOOTER,
	eTELEPORT_DIV,
	eTELEPORT_CLOSE,
	eTELEPORT_LINE,
	eTELEPORT_POINT,

	eTELEPORT_BT1,
	eTELEPORT_BT2,
	eTELEPORT_BT3,
	eTELEPORT_BT4,
	eTELEPORT_BT5,
	eTELEPORT_BT6,
	eTELEPORT_BT7,
	eTELEPORT_BT8,
	eTELEPORT_BT9,
	eTELEPORT_BT10,

	eTELEPORT_BT_CANCELE,
	eTELEPORT_PAGEUP1,
	eTELEPORT_PAGEUP2,
	eTELEPORT_PAGEUP3,
	eTELEPORT_PAGEUP4,
	eTELEPORT_PAGEUP5,
	eTELEPORT_PAGEUP6,
	eTELEPORT_PAGEUP7,
	eTELEPORT_PAGEUP8,
	eTELEPORT_PAGEUP9,
	eTELEPORT_PAGEUP10,
	eTELEPORT_MAPNAME,
	eTELEPORT_INFOBG,

	eRAGERESET_MAIN,
	eRAGERESET_TITLE,
	eRAGERESET_FRAME,
	eRAGERESET_FOOTER,
	eRAGERESET_DIV,
	eRAGERESET_INFOBG,
	eRAGERESET_CLOSE,
	eRAGERESET_OK,
	eRAGERESET_POINT1,
	eRAGERESET_CHECK1,
	eRAGERESET_LINE1,
	eRAGERESET_POINT2,
	eRAGERESET_CHECK2,
	eRAGERESET_LINE2,

	eDONATE_CHECKWIN_MAIN,
	eDONATE_CHECKWIN_TITLE,
	eDONATE_CHECKWIN_FRAME,
	eDONATE_CHECKWIN_FOOTER,
	eDONATE_CHECKWIN_DIV,
	eDONATE_CHECKWIN_OK,
	eDONATE_CHECKWIN_CLOSE,
	eDONATE_CHECKWIN_POINT,
	eDONATE_CHECKWIN_CHECK,
	eDONATE_CHECKWIN_LINE,
	eDONATE_CHECKWIN_LINE2,

	ePREMIUM_MAIN,
	ePREMIUM_TITLE,
	ePREMIUM_FRAME,
	ePREMIUM_FOOTER,
	ePREMIUM_DIV,
	ePREMIUM_INFOBG,
	ePREMIUM_MONEYBG,
	ePREMIUM_CLOSE,
	ePREMIUM_FINISH,
	ePREMIUM_LINE1,
	ePREMIUM_LINE2,
	ePREMIUM_LINE3,
	ePREMIUM_LINE4,
	ePREMIUM_POINT1,
	ePREMIUM_POINT2,
	ePREMIUM_POINT3,
	ePREMIUM_POINT4,
	ePREMIUM_CHECK1,
	ePREMIUM_CHECK2,
	ePREMIUM_CHECK3,
	ePREMIUM_CHECK4,
	ePREMIUM_CHECK5,
	ePREMIUM_PAGEUP,
	ePREMIUM_PAGEDN,

	ePKCLEAR_MAIN,
	ePKCLEAR_TITLE,
	ePKCLEAR_FRAME,
	ePKCLEAR_FOOTER,
	ePKCLEAR_DIV,
	ePKCLEAR_OK,
	ePKCLEAR_CLOSE,

	eACC_WARNGNG_MAIN,
	eACC_WARNGNG_TITLE,
	eACC_WARNGNG_FRAME,
	eACC_WARNGNG_FOOTER,
	eACC_WARNGNG_OK,
	eACC_WARNGNG_CLOSE,

	eACC_MENU_MAIN,
	eACC_MENU_TITLE,
	eACC_MENU_FRAME,
	eACC_MENU_FOOTER,
	eACC_MENU_DIV1,
	eACC_MENU_DIV2,
	eACC_MENU_CLOSE,
	eACC_MENU_PCSETTING,
	eACC_MENU_OPTION,
	eACC_MENU_INFOBG1,

	eACC_OPTION_MAIN,
	eACC_OPTION_TITLE,
	eACC_OPTION_FRAME,
	eACC_OPTION_FOOTER,
	eACC_OPTION_OK,
	eACC_OPTION_CLOSE,
	eACC_OPTION_LINE1,
	eACC_OPTION_POINT1,
	eACC_OPTION_CHECK1,
	eACC_OPTION_LINE2,
	eACC_OPTION_POINT2,
	eACC_OPTION_CHECK2,
	eACC_OPTION_LINE3,
	eACC_OPTION_POINT3,
	eACC_OPTION_CHECK3,
	eACC_OPTION_LINE4,
	eACC_OPTION_POINT4,
	eACC_OPTION_CHECK4,	
	eACC_OPTION_LINE5,
	eACC_OPTION_POINT5,
	eACC_OPTION_CHECK5,	
	eACC_OPTION_LINE6,
	eACC_OPTION_POINT6,
	eACC_OPTION_CHECK6,
	eACC_OPTION_ACCOPTION,
	eACC_OPTION_INFOBG1,
	eACC_OPTION_DIV1,
	eACC_OPTION_DIV2,

	eACC_PC_MAIN,
	eACC_PC_TITLE,
	eACC_PC_FRAME,
	eACC_PC_FOOTER,
	eACC_PC_OK,
	eACC_PC_CLOSE,
	eACC_PC_INFOBG1,
	eACC_PC_LINE1,
	eACC_PC_POINT1,
	eACC_PC_CHECK1,
	eACC_PC_LINE2,
	eACC_PC_POINT2,
	eACC_PC_CHECK2,
	eACC_PC_DIV1,

	eACC_MESSAGE_MAIN,
	eACC_MESSAGE_TITLE,
	eACC_MESSAGE_FRAME,
	eACC_MESSAGE_FOOTER,
	eACC_MESSAGE_CLOSE,

	eACC_NUMBER_MAIN,
	eACC_NUMBER_TITLE,
	eACC_NUMBER_FRAME,
	eACC_NUMBER_FOOTER,
	eACC_NUMBER_OK,
	eACC_NUMBER_CLOSE,
	eACC_NUMBER_INFOBG1,

	eREFERRAL_BORDER,
	eREFERRAL_ICON,

	eREFERRAL_MENU_MAIN,
	eREFERRAL_MENU_TITLE,
	eREFERRAL_MENU_FRAME,
	eREFERRAL_MENU_FOOTER,
	eREFERRAL_MENU_DIV1,
	eREFERRAL_MENU_CLOSE,
	eREFERRAL_MENU_REWARD,
	eREFERRAL_MENU_REFERRAL,

	eREFERRAL_MAIN,
	eREFERRAL_TITLE,
	eREFERRAL_FRAME,
	eREFERRAL_FOOTER,
	eREFERRAL_DIV1,
	eREFERRAL_CLOSE,
	eREFERRAL_L,
	eREFERRAL_R,
	eREFERRAL_INFOBG,
	eREFERRAL_PAGEUP1,
	eREFERRAL_PAGEUP2,
	eREFERRAL_PAGEUP3,
	eREFERRAL_PAGEUP4,
	eREFERRAL_PAGEUP5,
	eREFERRAL_PAGEUP6,
	eREFERRAL_PAGEUP7,
	eREFERRAL_PAGEUP8,
	eREFERRAL_PAGEUP9,
	eREFERRAL_PAGEUP10,
	eREFERRAL_BT1,
	eREFERRAL_BT2,
	eREFERRAL_BT3,
	eREFERRAL_BT4,
	eREFERRAL_BT5,
	eREFERRAL_BT6,
	eREFERRAL_BT7,
	eREFERRAL_BT8,
	eREFERRAL_BT9,
	eREFERRAL_BT10,
	eREFERRAL_LINE1,
	eREFERRAL_LINE2,

	eREFERRAL2_MAIN,
	eREFERRAL2_TITLE,
	eREFERRAL2_FRAME,
	eREFERRAL2_FOOTER,
	eREFERRAL2_DIV1,
	eREFERRAL2_CLOSE,
	eREFERRAL2_PAGEUP1,
	eREFERRAL2_BT1,
	eREFERRAL2_LINE1,
	eREFERRAL2_LINE2,

	ePLAYER_POINT_1,
	ePLAYER_POINT_2,
	ePLAYER_POINT_3,
	ePLAYER_POINT_4,
	ePLAYER_POINT_5,
	ePLAYER_POINT_6,
	ePLAYER_POINT_7,
	ePLAYER_POINT_8,
	ePLAYER_POINT_9,
	ePLAYER_POINT_10,
	eNULL_MAP,
	eLORENCIA_MAP,
	eDUNGEON_MAP,
	eDEVIAS_MAP,
	eNORIA_MAP,
	eLOSTTOWER_MAP,
	eATLANS_MAP,
	eTarkan_MAP,
	eElbeland_MAP,
	eICARUS_MAP,
	eLANDOFTRIALS_MAP,
	eAIDA_MAP,
	eCRYWOLF_MAP,
	eKANTRU_MAP,
	eKANTRU3_MAP,
	eBARRACKS_MAP,
	eCALMNESS_MAP,
	eRAKLION_MAP,
	eVULCANUS_MAP,
	eKALRUTAN_MAP,
	eKALRUTAN2_MAP,
	//
	eAUTO_HP_ON,
	eAUTO_HP_OFF,
	// --
	eWIN_QUEST_MAIN,
	eWIN_QUEST_TITLE,
	eWIN_QUEST_FRAME,
	eWIN_QUEST_FOOTER,
	eWIN_QUEST_DIV,
	eWIN_QUEST_CLOSE,
	eWIN_QUEST_TAB,
	eWIN_QUEST_TAB1,
	eWIN_QUEST_TAB2,
	eWIN_QUEST_TAB3,
	eWIN_QUEST_FINISH,
	eWIN_QUEST_COUNT1,
	eWIN_QUEST_COUNT2,
	eWIN_QUEST_COUNT3,
	eWIN_QUEST_INFOBG,
	eWIN_QUEST_INFOBG2,
	eWIN_QUEST_INFOBG3,
	eWIN_QUEST_LINE1,
	eWIN_QUEST_POINT1,
	eWIN_QUEST_INFO,
	// --
	eWAREHOUSE,
	eWAREHOUSE1,
	eOFFTRADE,
	eOFFTRADE_LINE1,
	eOFFTRADE_POINT1,
	eOFFTRADE_CHECK1,
	// --
	eLOTTERY_MAIN,
	eLOTTERY_TITLE,
	eLOTTERY_FRAME,
	eLOTTERY_FOOTER,
	eLOTTERY_PLAY,
	eLOTTERY_CLOSE,
	eLOTTERY_MONEYBG,
	eLOTTERY_INFOBG1,
	eLOTTERY_LINE1,
	eLOTTERY_POINT1,

	eLOTTERY_POINT,
	eLOTTERY_PAGEUP,
	eLOTTERY_PAGEDN,
	eLOTTERY_DIV,

	eLOTTERY_SPIN,

	eUSERSHOP_BT1,

	eGUILD_BANK_BT1,

#if(DEV_INTERFASE_SEASON3)
	eSkillBox,
	eDragonLeft,
	eDragonRight,
	eCharacter,
	eInventory,
	eParty,
	eFriend,
	eFastMenu,
#endif

	eJEWELBANK_MAIN,
	eJEWELBANK_TITLE,
	eJEWELBANK_FRAME,
	eJEWELBANK_FOOTER,
	eJEWELBANK_POINT,
	eJEWELBANK_LINE,
	eJEWELBANK_DIV,
	eJEWELBANK_PAGEUP1,
	eJEWELBANK_PAGEUP2,
	eJEWELBANK_PAGEUP3,
	eJEWELBANK_PAGEUP4,
	eJEWELBANK_PAGEUP5,
	eJEWELBANK_PAGEUP6,
	eJEWELBANK_PAGEUP7,
	eJEWELBANK_PAGEUP8,
	eJEWELBANK_PAGEUP9,
	eJEWELBANK_PAGEUP10,
	eJEWELBANK_PAGEUP11,
	eJEWELBANK_PAGEDN1,
	eJEWELBANK_PAGEDN2,
	eJEWELBANK_PAGEDN3,
	eJEWELBANK_PAGEDN4,
	eJEWELBANK_PAGEDN5,
	eJEWELBANK_PAGEDN6,
	eJEWELBANK_PAGEDN7,
	eJEWELBANK_PAGEDN8,
	eJEWELBANK_PAGEDN9,
	eJEWELBANK_PAGEDN10,
	eJEWELBANK_PAGEDN11,

	eZTMENU3_MENU,
	eZTMENU3_MAIN,
	eZTMENU3_TITLE,
	eZTMENU3_FRAME,
	eZTMENU3_FOOTER,
	eZTMENU3_BUTTON_01,
	eZTMENU3_BUTTON_02,
	eZTMENU3_BUTTON_03,
	eZTMENU3_BUTTON_04,
	eZTMENU3_BUTTON_05,
	eZTMENU3_BUTTON_06,
	eZTMENU3_BUTTON_07,
	eZTMENU3_BUTTON_08,
	eZTMENU3_BUTTON_09,
	eZTMENU3_BUTTON_10,
	eZTMENU3_BUTTON_11,
	eZTMENU3_BUTTON_12,
	eZTMENU3_BUTTON_13,
	eZTMENU3_BUTTON_14,
	eZTMENU3_BUTTON_15,
	eZTMENU3_BUTTON_16,
	eZTMENU3_BUTTON_17,
	eZTMENU3_BUTTON_18,
	eZTMENU3_BUTTON_19,
	eZTMENU3_BUTTON_20,
	eZTMENU3_BUTTON_21,
	eZTMENU3_BUTTON_22,
	eZTMENU3_BUTTON_CHEBUK,
	
	eITEM_MARKET_BG,
	eITEM_MARKET_BUY0,
	eITEM_MARKET_BUY1,
	eITEM_MARKET_BUY2,
	eITEM_MARKET_CHECK,
	eITEM_MARKET_L,
	eITEM_MARKET_R,
	eITEM_MARKET_PAGE0,
	eITEM_MARKET_PAGE1,
	eITEM_MARKET_PAGE2,
	eITEM_MARKET_PAGE3,
	eITEM_MARKET_PAGE4,
	eITEM_MARKET_PAGE5,

	eADVANCE_STAT_INFO,

	#if(DEV_INTERFACE_ZT700)
	eMainEx700,
	eShop1,
	eShop2,
	eCharacter1,
	eCharacter2,
	eInventory1,
	eInventory2,
	eQuest1,
	eQuest2,
	eCommunity1,
	eCommunity2,
	eSystem1,
	eSystem2,	
	#endif

	#if(USERPANEL)
	eUSERSPANELBG,
	eUSERSPANEL_BUTTON,
	#endif

	//Ex700
	eMainEx700,
	eShop1,
	eShop2,
	eCharacter1,
	eCharacter2,
	eInventory1,
	eInventory2,
	eQuest1,
	eQuest2,
	eCommunity1,
	eCommunity2,
	eSystem1,
	eSystem2,

	#if(CUSTOM_MAP_TELEPORT)

	eMAPTELEPORT_MAIN,
	eMAPTELEPORT_TEST,

	eMAPTELEPORT_POINT1,
	eMAPTELEPORT_POINT2,
	eMAPTELEPORT_POINT3,
	eMAPTELEPORT_POINT4,
	eMAPTELEPORT_POINT5,
	eMAPTELEPORT_POINT6,
	eMAPTELEPORT_POINT7,
	eMAPTELEPORT_POINT8,
	eMAPTELEPORT_POINT9,
	eMAPTELEPORT_POINT10,

	eMAPTELEPORT_POINT11,
	eMAPTELEPORT_POINT12,
	eMAPTELEPORT_POINT13,
	eMAPTELEPORT_POINT14,
	eMAPTELEPORT_POINT15,
	eMAPTELEPORT_POINT16,
	eMAPTELEPORT_POINT17,
	eMAPTELEPORT_POINT18,
	eMAPTELEPORT_POINT19,
	eMAPTELEPORT_POINT20,

	eMAPTELEPORT_POINT21,
	eMAPTELEPORT_POINT22,
	eMAPTELEPORT_POINT23,
	eMAPTELEPORT_POINT24,
	eMAPTELEPORT_POINT25,
	eMAPTELEPORT_POINT26,
	eMAPTELEPORT_POINT27,
	eMAPTELEPORT_POINT28,
	eMAPTELEPORT_POINT29,
	eMAPTELEPORT_POINT30,

	eMAPTELEPORT_POINT31,
	eMAPTELEPORT_POINT32,
	eMAPTELEPORT_POINT33,
	eMAPTELEPORT_POINT34,
	eMAPTELEPORT_POINT35,
	eMAPTELEPORT_POINT36,
	eMAPTELEPORT_POINT37,
	eMAPTELEPORT_POINT38,
	eMAPTELEPORT_POINT39,
	eMAPTELEPORT_POINT40,

	#endif

	eVALUEMENU_MAIN,
	eVALUEMENU_TITLE,
	eVALUEMENU_FRAME,
	eVALUEMENU_FOOTER,
	eVALUEMENU_OK,
	eVALUEMENU_CLOSE,
	eVALUEMENU_VALUE1,
	eVALUEMENU_VALUE2,
	eVALUEMENU_VALUE3,
	eVALUEMENU_VALUE4,
	eVALUEMENU_VALUE5,

	eSPOT_POIN_1,
	eSPOT_POIN_2,
	eSPOT_POIN_3,
	eSPOT_POIN_4,
	eSPOT_POIN_5,
	eSPOT_POIN_6,
	eSPOT_POIN_7,
	eSPOT_POIN_8,
	eSPOT_POIN_9,
	eSPOT_POIN_10,

	#if(ENABLE_MULTI_CHAR)
	eSELECTCHAR_LEFT,
	eSELECTCHAR_RIGHT,
	#endif

	eMARKET_MAIN,
	eMARKET_TITLE, 
	eMARKET_FRAME,
	eMARKET_FOOTER,
	eMARKET_DIV,
	eMARKET_OK,
	eMARKET_CLOSE,
	eMARKET_INFOBG,
	eMARKET_INFOBG2,
	eMARKET_INFOBG3,
	eMARKET_SCROLL,
	eMARKET_BUY,

	eMARKET_PRICE_MAIN,
	eMARKET_PRICE_TITLE, 
	eMARKET_PRICE_FRAME,
	eMARKET_PRICE_FOOTER,
	eMARKET_PRICE_OK,
	eMARKET_PRICE_CLOSE,
	eMARKET_PRICE_INFOBG,
	eMARKET_PRICE_CHECK1,
	eMARKET_PRICE_CHECK2,
	eMARKET_PRICE_CHECK3,
	eMARKET_PRICE_POINT, 
	eMARKET_PRICE_LINE,

	eMARKET_FILTER_MAIN,
	eMARKET_FILTER_TITLE, 
	eMARKET_FILTER_FRAME,
	eMARKET_FILTER_FOOTER,
	eMARKET_FILTER_POINT, 
	eMARKET_FILTER_PAGEUP, 
	eMARKET_FILTER_PAGEDN, 
	eMARKET_FILTER_LINE,
	eMARKET_FILTER_CHECK1,
	eMARKET_FILTER_CHECK2,
	eMARKET_FILTER_CHECK3,
	eMARKET_FILTER_CHECK4,
	eMARKET_FILTER_CHECK5,
	eMARKET_FILTER_CHECK6,
	eMARKET_FILTER_NAME,
	eMARKET_FILTER_CAATEGORY,
	eMARKET_FILTER_DIV,

	eMARKET_ITEM_MAIN,
	eMARKET_ITEM_TITLE,
	eMARKET_ITEM_FRAME,
	eMARKET_ITEM_FOOTER,
	eMARKET_ITEM_BG,
	eMARKET_ITEM_OK,
	eMARKET_ITEM_CLOSE,

	eMARKET_L,
	eMARKET_R,

	eMARKET_BUTTON,
	eCHAT_SMILE_BUTTON

};
// ----------------------------------------------------------------------------------------------

enum eLoadWeZenImage
{
	eImgSkillOn1 = 0x7A4C,
	eImgSkillOn2 = 0x7A4D,
	eImgSkillOn3 = 0x7A4F,	//0x7A4E,
	eImgSkillOff1 = 0x7A52,
	eImgSkillOff2 = 0x7A53,
	eImgSkillOff3 = 0x7A55,	//0x7A4F,
	//eImgSkillOff4 = 0x7A55,

};
// ----------------------------------------------------------------------------------------------

enum MaiObjID
{
	zt_RANKING_MAIN = 0x9C46,
	zt_DONATE_LEFT = 0x9C47,
	zt_DONATE_RIGHT = 0x9C48,
	zt_PT_SEARCH_TITLE = 0x9C49,
	zt_PEROSNAL_SEATCH_TITLE,
	zt_NEWS_TITLE,
	zt_SMITHY_TEXT,
	zt_MARRIAGE,
	zt_ADDPOINT_BOX,
	zt_ADDPOINT_FRAME,
	zt_PM_FLAGNEW_LEADER,
	zt_LORA_BATTLE_SCORE,
	eImgID_ACHIEVEMENTS_MAIN,
	eImgID_ACHIEVEMENTS_PROGRESS_BG,
	eImgID_ACHIEVEMENTS_PROGRESS_LINE,
	eImgID_ACHIEVEMENTS_MISSION_1,
	eImgID_ACHIEVEMENTS_MISSION_2,
	eImgID_ACHIEVEMENTS_MISSION_3,
	eImgID_ACHIEVEMENTS_MISSION_4,
	eImgID_ACHIEVEMENTS_MISSION_5,
	eImgID_ACHIEVEMENTS_MISSION_6,
	eImgID_ACHIEVEMENTS_MISSION_7,
	eImgID_ACHIEVEMENTS_MISSION_8,
	eImgID_ACHIEVEMENTS_MISSION_9,
	eImgID_ACHIEVEMENTS_MISSION_10,
	eImgID_ACHIEVEMENTS_MISSION_11,
	eImgID_ACHIEVEMENTS_MISSION_12,
	eImgID_ACHIEVEMENTS_MISSION_13,
	eImgID_ACHIEVEMENTS_MISSION_14,
	eImgID_ACHIEVEMENTS_MISSION_15,
	eImgID_ACHIEVEMENTS_MISSION_16,
	eImgID_ACHIEVEMENTS_MISSION_17,
	eImgID_ACHIEVEMENTS_MISSION_18,
	eImgID_ACHIEVEMENTS_MISSION_19,
	eImgID_ACHIEVEMENTS_MISSION_20,
	eImgID_ACHIEVEMENTS_MISSION_21,
	eImgID_ACHIEVEMENTS_MISSION_22,
	eImgID_ACHIEVEMENTS_MISSION_23,
	eImgID_ACHIEVEMENTS_MISSION_24,
	eImgID_ACHIEVEMENTS_MISSION_25,
	eImgID_ACHIEVEMENTS_MISSION_26,
	eImgID_ACHIEVEMENTS_MISSION_27,
	eImgID_ACHIEVEMENTS_MISSION_28,
	eImgID_ACHIEVEMENTS_MISSION_29,
	eImgID_ACHIEVEMENTS_MISSION_30,
	eImgID_ACHIEVEMENTS_MISSION_31,
	eImgID_ACHIEVEMENTS_MISSION_32,
	eImgID_ACHIEVEMENTS_MISSION_33,
	eImgID_ACHIEVEMENTS_MISSION_34,
	eImgID_ACHIEVEMENTS_MISSION_35,
	eImgID_ACHIEVEMENTS_MISSION_36,
	eImgID_ACHIEVEMENTS_MISSION_37,
	eImgID_ACHIEVEMENTS_MISSION_38,
	eImgID_ACHIEVEMENTS_MISSION_39,
	eImgID_ACHIEVEMENTS_MISSION_40,
	eImgID_ACHIEVEMENTS_MISSION_41,
	eImgID_ACHIEVEMENTS_MISSION_42,
	eImgID_ACHIEVEMENTS_MISSION_43,
	eImgID_ACHIEVEMENTS_MISSION_44,
	eImgID_ACHIEVEMENTS_MISSION_45,
	eImgID_ACHIEVEMENTS_MISSION_46,
	eImgID_ACHIEVEMENTS_MISSION_47,
	eImgID_ACHIEVEMENTS_MISSION_48,
	eImgID_ACHIEVEMENTS_MISSION_49,
	eImgID_ACHIEVEMENTS_MISSION_50,
	eImgID_ACHIEVEMENTS_PANEL,
	eImgID_ACHIEVEMENTS_DAMAGE,
	eImgID_ACHIEVEMENTS_DEFENCE,
	eImgID_ACHIEVEMENTS_LIFE,
	eImgID_ACHIEVEMENTS_EXELENT,
	eImgID_ACHIEVEMENTS_CRITICAL,
	zt_ZTTELEPORT_TITLE,
	zt_PLAYERTITLE_A,
	zt_BORDER_REFFERAL,
	zt_ICON_REFFERAL,
	zt_SMITHY_ITEM,
	zt_AUTOHP_ON,
	zt_AUTOHP_OFF,
	zt_PLAYER_POINT,
	zt_NULL_MAP,
	zt_LORENCIA_MAP,
	zt_DUNGEON_MAP,
	zt_DEVIAS_MAP,
	zt_NORIA_MAP,
	zt_LOSTTOWER_MAP,
	zt_ATLANS_MAP,
	zt_Tarkan_MAP,
	zt_Elbeland_MAP,
	zt_ICARUS_MAP,
	zt_LANDOFTRIALS_MAP,
	zt_AIDA_MAP,
	zt_CRYWOLF_MAP,
	zt_KANTRU_MAP,
	zt_KANTRU3_MAP,
	zt_BARRACKS_MAP,
	zt_CALMNESS_MAP,
	zt_RAKLION_MAP,
	zt_VULCANUS_MAP,
	zt_KALRUTAN_MAP,
	zt_KALRUTAN2_MAP,
	zt_INFO_2,
	zt_TEXT_BOX3,
	zt_WAREHOUSE,
	zt_WAREHOUSE1,

	zt_LOTTERY_SPIN,
	zt_LOTTERY_CLOSE,
	zt_LOTTERY_MAIN,

	zt_ITEM_MARKET_BG,
	zt_ITEM_MARKET_BUY0,
	zt_ITEM_MARKET_BUY1,
	zt_ITEM_MARKET_BUY2,
	zt_ITEM_MARKET_PAGE0,
	zt_ITEM_MARKET_PAGE1,
	zt_ITEM_MARKET_PAGE2,
	zt_ITEM_MARKET_PAGE3,
	zt_ITEM_MARKET_PAGE4,
	zt_ITEM_MARKET_PAGE5,

#if(DEV_INTERFASE_SEASON3)
	iNewSkillBox,
	iDragonLeft,
	iDragonRight,
	iNewParty,
	iNewCharacter,
	iNewInventory,
	iNewWinpush,
	iNewFastMenu,
#endif
	zt_ZTMENU3_BUTTON_01,
	zt_ZTMENU3_BUTTON_02,
	zt_ZTMENU3_BUTTON_03,
	#if(USERPANEL)
	zt_USERSPANELBG,
	zt_USERSPANEL_BUTTON,
	#endif
	#if(CUSTOM_MAP_TELEPORT)
	zt_MAPTELEPORT_MAIN,
	zt_MAPTELEPORT_TEST,
	//eTELEPORT_TITLE,
	//eTELEPORT_FRAME,
	//eINVENTORY_FOOTER,
	//eINVENTORY_BORDER,
	//eINVENTORY_ITEMBOX,
	//eINVENTORY_USEBOX,
	#endif
	#if(ENABLE_RENDER_EFFECT)
	TEXTURE_FLARERED,
	TEXTURE_FLARE01,
	TEXTURE_FIRE02,
	TEXTURE_SHINY04,
	#endif
	#if(ENABLE_CHAT_SMILE)
	zt_CHAT_SMILE_ICON,
	zt_CHAT_SMILE_BUTTON,
	zt_CHAT_SMILE_BGLINE,
	#endif
};
// ----------------------------------------------------------------------------------------------

struct ItemBmdStruct
{
    char Name[30];
/*+30*/ BYTE TwoHand;
/*+31*/ BYTE gap01;
/*+32*/ BYTE ItemLvl;
/*+33*/ BYTE gap02;
/*+34*/ BYTE Slot;
/*+35*/ BYTE gap03;
/*+36*/ BYTE Skill;
/*+37*/ BYTE gap04;
/*+38*/ BYTE ItemWidth;
/*+39*/ BYTE ItemHeight;
/*+40*/ BYTE MinDmg;
/*+41*/ BYTE MaxDmg;
/*+42*/ BYTE gap05;
/*+43*/ BYTE Defence;
/*+44*/ BYTE gap06;
/*+45*/ BYTE Speed;
/*+46*/ BYTE gap07;
/*+47*/ BYTE Dur;
/*+48*/ BYTE MagicDur;
/*+49*/ BYTE MagicPwr;
/*+50*/ BYTE ReqStr;
/*+51*/ BYTE ReqStrValue;
/*+52*/ BYTE ReqAgi;
/*+53*/ BYTE ReqAgiValue;
/*+54*/ BYTE ReqEne;
/*+55*/ BYTE ReqEneValue;
/*+56*/ BYTE ReqVit;
/*+57*/ BYTE ReqVitValue;
/*+58*/ BYTE ReqCmd; //ReqCmd = ReqCmd+(ReqCmdValue*256)
/*+59*/ BYTE ReqCmdValue;
/*+60*/ BYTE ReqLvl;
/*+60*/ byte gap08[3];
/*+63*/ unsigned int Money;
/*+67*/ BYTE Type;
/*+68*/ BYTE DW;
/*+69*/ BYTE DK;
/*+70*/ BYTE ELF;
/*+71*/ BYTE MG;
/*+72*/ BYTE DL;
/*+73*/ BYTE Sum;
/*+74*/ BYTE RF;
    BYTE Resists[8];
};
// ----------------------------------------------------------------------------------------------

enum ObjWindow // -> Season 6.3
{
	FriendList		= 1,
	MoveList		= 2,
	Party			= 3,
	Quest			= 4,//
	QuestDevin		= 5,//
	Guild			= 6,
	Trade			= 7,
	Warehouse		= 8,
	ChaosBox		= 9,
	CommandWindow	= 10,
	PetInfo			= 11,
	Shop			= 12,
	Inventory		= 13,
	Store			= 14,
	OtherStore		= 15,
	Character		= 16,
	DevilSquery		= 19,//
	BloodCastle		= 20,//
	GuildMaster		= 21,
	GuardNPC		= 24,//
	VorotaCS		= 25,//
	ChatWindow		= 33,
	FastMenu		= 34,
	Options			= 35,
	Help			= 36,
	FastDial		= 39,
	SkillTree		= 57,
	Rena			= 59,//
	LuckyCoins		= 60,//?
	LuckCoinsNPC	= 61,
	Titus			= 62,//
	NPC_Titus		= 63,
	CashShop		= 65,
	ElfQuest		= 68,
	FullMap			= 72,
	NPC_Dialog		= 73,
	GensInfo		= 74,
	NPC_Julia		= 75,
	ExpandInventory	= 77,
	ExpandWarehouse	= 78, 
	Helper			= 79,
};
// ----------------------------------------------------------------------------------------------

enum ObjWindowsZt
{
	ztWinNews			= 1,
	ztWinReset			= 2,
	ztWinGrandReset		= 3,
	ztWinRanking		= 4,
	ztWinDonate			= 5,
	ztWinPremium		= 6,
	ztWinMiniMenu		= 7,
	ztWinSettings		= 8,
	ztWinPTSearchMaster	= 9,
	ztWinPTSearchUser	= 10,
	ztWinPersonalSearch	= 12,
	ztWinPersonalPrice	= 13,
	ztWinNPCBuffer,
	ztWinSmithy,
	ztWinSmithyCheck,
	ztWinCheckOffAfk,
	ztWinMarriage,
	ztWinAddPoints,
	ztWinAddResetPoint,
	ztWinCustomMenu,
	ztWinCustomMenuChangeClass,
	ztWinDungeonSiege,
	ztWinTeamVsTeam,
	ztWinTeamVsTeamStatistic,
	ztWinAchievements,
	ztWinAchievementsPower,
	ztWinTeleport,
	ztWinTeleportEvo,
	ztWinResetRage,
	ztWinDonateCheck,
	ztWinPKClear,
	ztWinAccWarning,
	ztWinAccMenu,
	ztWinAccOption,
	ztWinAccPC,
	ztWinAccMessage,
	ztWinAccNumber,
	ztWinReferralMenu,
	ztWinReferralSystem,
	ztWinReferralSystem2,
	ztWinQuest,
	ztWinLottery,
	ztWinItemMarket,
	ztWinItemMarketPrice,
	ztWinMenuV3,
	ztWinStatsAdvance,
	ztWinMapTeleport,
	ztWinValueMenu,
	ztWinGuildValueMenu,
	ztWinWarehouseUserMenu,
	ztWinWarehouseGuildMenu,
	ztWinCernage,

};
// ----------------------------------------------------------------------------------------------

enum ColorMacro
{
	eShinyGreen		= Color4f(172, 255, 56, 255),
	eGold			= Color4f(255, 189, 25, 255),
	eWhite			= Color4f(255, 255, 255, 255),
	eWhite180		= Color4f(255, 255, 255, 180),
	eOrange			= Color4f(255, 105, 25, 255),
	eGray100		= Color4f(50, 50, 50, 100),
	eGray150		= Color4f(50, 50, 50, 150),
	eGray			= Color4f(50, 50, 50, 255),
	eBlowPink		= Color4f(220, 20, 60, 255),
	eRed			= Color4f(225, 0, 0, 255),
	eExcellent		= Color4f(0, 225, 139, 255),
	eAncient		= Color4f(36, 242, 252, 255),
	eSocket			= Color4f(153, 102, 204, 255),
	eBlue			= Color4f(0, 100, 200, 255),	//Color4f(0, 100, 200, 255)
	eYellow			= Color4f(255, 255, 0, 255),
	eBrown			= Color4f(69, 39, 18, 255),
	eBlack			= Color4f(0, 0, 0, 255),	
};
// ----------------------------------------------------------------------------------------------

struct InterfaceObject
{
	DWORD	ModelID;
	float	Width;
	float	Height;
	float	X;
	float	Y;
	float	MaxX;
	float	MaxY;
	DWORD	EventTick;
	bool	OnClick;
	bool	OnShow;
	BYTE	Attribute;

	void Open()
	{
		this->OnShow = true; 
		//pSetCursorFocus = true;
	}

	void Open(int Value)
	{
		this->OnShow = true; 
		//this->OpenedValue = Value;
	}

	void Close(int Value)
	{
		//this->OpenedValue = Value;
		this->OnShow = false; 
	}

	void Close()
	{
		this->OnShow = false; 
		pSetCursorFocus = false;
	}

	void Clear()
	{
		this->Width = 0;
		this->Height = 0;
		this->X = 0;
		this->Y = 0;
		this->MaxX = 0;
		this->MaxY = 0;
		this->OnClick = 0;
		this->OnShow = 0;
		//this->State = 0;
		//this->Type = 0;
	}
};
// ----------------------------------------------------------------------------------------------

class Pos2D
{
public:
    Pos2D(float x= 0.0f, float y = 0.0f)
    {
		this->X = x;
		this->Y = y;
    }
    float X;
    float Y;

public:
    void Set(float x, float y)
    {
		this->X = x;
		this->Y = y;
    }
};
// ----------------------------------------------------------------------------------------------

class Vec3D
{
public:
    Vec3D(float x = 0.0f, float y = 0.0f, float z = 0.0f)
    {
		this->X = x;
		this->Y = y;
		this->Z = z;
    }
    float X;
    float Y;
    float Z;

public:
   void SetVertexCoord(Vec3D *Pos, Vec3D *a2)
    {
		this->X = a2->Y * Pos->Y + a2->Z * Pos->Z + Pos->X * a2->X;
		this->Y = a2[1].Y * Pos->X + a2[1].Z * Pos->Y + a2[2].X * Pos->Z;
		this->Z = a2[2].Z * Pos->X + a2[3].X * Pos->Y + a2[3].Y * Pos->Z;
    }

    void SetVertex(Vec3D *lpVertex)
    {
		float PosZ = this->Z * 0.01745329238474369f;
		float v3 = sin(PosZ);
		float v4 = cos(PosZ);
		float PosY = this->Y * 0.01745329238474369f;
		float v6 = sin(PosY);
		float v7 = cos(PosY);
		float PosX = this->X * 0.01745329238474369f;
		float v9 = sin(PosX);
		float v10 = cos(PosX);

		lpVertex->X = v7 * v4;
		lpVertex[1].Y = v7 * v3;
		lpVertex[2].Z = -v6;

		lpVertex->Y = v9 * v6 * v4 + -v3 * v10;
		lpVertex[1].Z = v9 * v6 * v3 + v10 * v4;
		lpVertex[3].X = v9 * v7;

		lpVertex->Z = v10 * v6 * v4 + -v9 * -v3;
		lpVertex[2].X = v10 * v6 * v3 + -v9 * v4;
		lpVertex[3].Y = v10 * v7;

		lpVertex[1].X = 0.0;
		lpVertex[2].Y = 0.0;
		lpVertex[3].Z = 0.0;
    }

    void Set(float R, float G, float B)
    {
		this->X = R;
		this->Y = G;
		this->Z = B;
    }

    Vec3D * Get()
    {
		return this;
    }
};
// ----------------------------------------------------------------------------------------------

typedef struct
{
	/* +0*/  unsigned char  identsize;          // size of ID field that follows 18 byte header (0 usually)
	/* +1*/  unsigned char  colourmaptype;      // type of colour map 0=none, 1=has palette
	/* +2*/  unsigned char  imagetype;          // type of image 0=none,1=indexed,2=rgb,3=grey,+8=rle packed
	/* +3*/  short colourmapstart;     // first colour map entry in palette
	/* +5*/  short colourmaplength;    // number of colours in palette
	/* +7*/  unsigned char  colourmapbits;      // number of bits per palette entry 15,16,24,32
	/* +8*/  short xstart;             // image x origin
	/* +10*/	short ystart;             // image y origin
	/* +12*/	short width;              // image width in pixels
	/* +14*/	short height;             // image height in pixels
	/* +16*/	unsigned char  bits;               // image bits per pixel 8,16,24,32
	/* +17*/	unsigned char  descriptor;         // image descriptor bits (vh flip bits)
	/* +18*/	unsigned char *data;
} TGA_HEADER;
// ----------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------

class Interface
{
public:
	Interface();

	static void NewLogoDraw();
	// ----
	static char __thiscall BankImgHook(char *This, char a2);
	static char __thiscall BankMouse(char *This);
	static void __cdecl BankImg2Hook(int a1, float a2, float a3, float a4, float a5);
	static void __thiscall SetBankTextHook(LPVOID This, int PosX, int PosY, LPCTSTR Text, int nCount, int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin);
	void SetBankHook(bool BankType);
	
	// ----
	void		BindObject(short ObjectID, DWORD ModelID, float Width, float Height, float X, float Y);
	void		Load();
	void		LoadImages(char * Folder, int Code, int Arg3, int Arg4, int Arg5);
	static void	LoadTga();
	// ----
	static void LogoDraw(); 
	static void	Work();
	static bool	AllowGUI();

	bool		CheckWindow(int WindowID);
	void		DrawGUI(short ObjectID);
	void		DrawGUI(short ObjectID, float PosX, float PosY);
	void		DrawColoredGUI(short ObjectID, DWORD Color);
	void		DrawColoredGUIObj(short ObjectID, float X, float Y, DWORD Color);
	int			DrawFormat(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...);
	void		DrawFormatEx(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...);
	int			DrawFormatBG(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...);
	bool		IsWorkZone(float X, float Y, float MaxX, float MaxY);
	bool		IsWorkZoneObj(short ObjectID);

	int			DrawToolTip(int X, int Y, LPCSTR Text, ...);
	int			DrawToolTipEx(int X, int Y, LPCSTR Text, ...);

	void		DrawColorGUI(int MainID, int X, int Y, int Width, int Height, DWORD Color);
	float		DrawRepeatGUI(short MonsterID, float X, float Y, int Count);

	bool		RightWindows();

	int			OpenWindow(int WindowID);
	int			CloseWindow(int WindowID);

	bool		WindowEx[MAX_WINDOW_ZT];
	void		OpenWindowZt(int WindowID);
	void		CloseWindowZt(int WindowID);
	bool		CheckWindowZt(int WindowID);
	bool		CloseWindowsZtAll();
	bool		IsWorkZone(short ObjectID);
	void		DrawColoredGUI(short ObjectID, float X, float Y, DWORD Color);

	void		DrawCheckLine(bool Switch, int Point, int Check, int Line, float X, float Y, int Color, char* Text);
	void		DrawCheckLineZt(bool Switch, int Point, int Check, int Line, float X, float Y, int Color, char* Text);
	void		PartUPandDN(int Point, int PageUp, int PageDn, int Line, float X, float Y, int Color, int Number, char* Text);
	void		PartUPandDNEx(int Point, int PageUp, int PageDn, int Line, float X, float Y, int Color, int Number, char* Text);
	void		DrawGUIY(short ObjectID, float PosX, float PosY, int Type);

	bool		Button(DWORD Event, int WinID, int ButtonID, bool Type);
	bool		ButtonZt(DWORD Event, int ButtonID, bool Type);
	static int	CursorDraw();
	void		KeyBoxEvent(DWORD Event, char* kText, int MaxText);

	void		DrawButtonMini(int id, int X, int Y, int res, char* Text);
	void		DrawPrice(int X, int Y, int iZen, int iChaos, int iBless, int iSoul, int iLife, int iBonus, int iCredit);
	int			DrawFormat_Ex(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...);

	bool		ButtonCord(DWORD Event, float bX, float bY, float bW, float bH, bool& bClick, DWORD& EventTick);
	void		DrawBorder(float X, float Y, float Whith, float High, float bor, DWORD eColor);
	void		DrawButtonBig(int ObjID, bool bActive, float fX, float fY, char* Text);

	void		DrawRightMiniInfoMapQuest();
	void		DrawGUIText(short ObjectID, float PosX, float PosY, char* Text);
	void        CashShopOpen();
#if(CUSTOM_AUTOCTRL)
	void		DrawAutoCtrl();
	bool	    m_bAutoCtrl;
#endif
	void		DrawWindow(int ObjMain, int ObjTitle, int ObjFrame, int ObjFooter, int Repeat, float X, float Y, char* Text);
	void		DrawPage(int ObjL, int ObjR, int Page, int MaxPage, float X, float Y);

	void	DrawItem(float PosX, float PosY, float Width, float Height, int ItemID, int Level, int Excl, int Anc, bool OnMouse);

#if(CUSTOM_POSTITEM)
	void LoadItemPost();
	static void Work2();
	static void DrawChat ( int mode, char* character, char* message );
	static void DrawItemToolTipText ( void * item, int x, int y );

	void * item_post_;
	DWORD last_tickcount_view_;


	void	MapMessageRender();
	void	SetMapMessage(const char* Format, ...);
	void	DrawBarForm(float PosX,float PosY,float Width,float Height,GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
#endif
	
	bool m_ActiveAutoHP;
	bool m_AutoHP;
	int m_AutoHPTick;
	void DrawAutoHPClick();
	void EventAutoHPClick(DWORD Event);

	bool		IsWorkFullZone(float X, float Y, float MaxX, float MaxY);

	void		DrawMiniMap();
	bool		MiniMapCheck();
	bool		CombinedChecks();
	void		DrawGUIZt(short ObjectID, float PosX, float PosY, bool dr);
	short		m_iDrawObjectID;
	// ----
	float		GetResizeX(short ObjectID);
	void		DrawWarehouseUI();
	void		EventWarehouseUI(DWORD Event);
	void		DrawOffTrade();
	void		EventOffTrade(DWORD Event);
	// ----
	#if(CUSTOM_EMULATOR_KEY)
	void        DrawAutoClickMouse();
	#endif
	InterfaceObject Data[MAX_OBJECT];
	float RightMiniInfoY;
	bool m_bCashShopOpen;
	bool m_OffTradeSwitch;

	#if(DEV_INTERFASE_SEASON3)
	void DrawS2Interface();
	void DrawMenuButton();
	void EventMenuButton(DWORD Event);
	#endif

	void		DrawMiniBar(float X, float Y, int Count);

	static void _TC DrawGuildBank(LPVOID This, int PosX, int PosY, LPCTSTR Text, int nCount, int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin);
	void			EventGuildBank(DWORD Event);

	static void _TC DrawWarehouseHook(LPVOID This, int PosX, int PosY, LPCTSTR Text, int nCount, int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin);

	void DrawSizeGUI(short ObjectID, float Width, float High, float PosX, float PosY, float SizeW, float SizeH);

	#if(DEV_PLAYERINFO)
	bool m_EnableDrawTargetInfo;
	void DrawTargetInfo();
	#endif
	#if(DEV_DAMAGE_TABLE)
	bool m_EnableDamageTable;
	void DrawDamageTable();
	#endif
	#if(DEV_INTERFACE_ZT700)
	void DrawInterfaceEx700();
	#endif
	void DrawItemMarket();

	#if(DEV_INTERFACE_ZT700)
	void DrawMenuButton();
	void EventMenuButton(DWORD Event);
	void DrawInterfaceCustom();
	#endif

	void DrawButton(short ObjectID, float PosX, float PosY, float Width, float Height);
	void DrawIMG(short ObjectID, float PosX, float PosY, float Width, float Height);

	#if(USERPANEL)
	void		DrawUsersPanel();
	void		EventUsersPanel(DWORD Event);
	#endif

	bool m_GameDraw;

	void		DrawMenuButtonZt();
	void		EventMenuButtonZt(DWORD Event);
	void DrawInterfaceCustomEx();

	static void 	DrawChatInterface(int a1, float a2, float a3, float a4, float a5);
	static char __thiscall DrawChatMain(int This);

	#if(CUSTOM_VALUE_MENU)
	void BindValueMenu();
	void DrawValueMenu();
	void ControllerValueMenu(DWORD Event);
	// --
	void BindGuildValueMenu();
	void DrawGuildValueMenu();
	void ControllerGuildValueMenu(DWORD Event);
	#endif
	/*
	void DrawWindowCernage();
	*/

	void DrawButtonZt(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY);

	#if(ENABLE_MULTI_CHAR)
	static void SelectChar();
	void EventSelectChar(DWORD Event);
	int m_CharacterPage;
	#endif

	bool		ButtonZtR(DWORD Event, int ButtonID, bool Type);
#if(ENABLE_MARKET_BUTTON)
	void DrawMarketButton();
	void EventMarketButton(DWORD Event);
#endif

	void __fastcall muGetWindowSize(int* vec);
	void LoadGraphics();
};

extern Interface gInterface;