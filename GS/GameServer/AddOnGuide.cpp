#include "StdAfx.h"
#include "ItemGetNotice.h"
#include "GameMain.h"
#include "Achievements.h"


#define ITEM_GET_NOTICE		1

//===GameMain.cpp -> ReadCommonServerInfo()123123

#if(ITEM_GET_NOTICE)
	g_ItemGetNotice.Read();
	
#endif

//=== Protocol.cpp -> CGItemGetRequest

//#if(SYSTEM_ACHIEVEMENTS)
//	g_Achievements.PickUp(aIndex, lpItem->m_Type, lpItem->m_Level, lpItem->m_NewOption, lpItem->m_SetOption, lpItem->m_Durability); //<<===== Find Is
//#endif

#if(ITEM_GET_NOTICE)
			g_ItemGetNotice.ItemGetNotice(lpItem, aIndex);
#endif
		