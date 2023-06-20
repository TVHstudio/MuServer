#include "StdAfx.h"
#include "user.h"
#include "PlayerConnect.h"
#include "Reset.h"
#include "Message.h"
#include "Configs.h"
#include "ZtLicense.h"
#ifdef _UPDATE8_
#include "ShowOnline.h"
#endif
#include "ConnectZt.h"
#include "ZtText.h"

void ExPlayerConnectSystem(int aIndex)
{	
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->MapNumber == 10){
	
	}

#ifdef TWO_IP_CONNECT_OFF
	if(g_ZtLicense.CheckUser(eZtUB::ulasevich) || g_ZtLicense.CheckUser(eZtUB::Local) || g_ZtLicense.CheckUser(eZtUB::ulasevich2))
	{
		int CountIpAddress;
		CountIpAddress = 0;
		for ( int n = OBJ_STARTUSERINDZT ; n < OBJMAX ; n++)
		{
				if ( gObj[n].Type == OBJ_USER && gObj[n].Connected == PLAYER_PLAYING )
				{
					if (lpObj->m_Index == gObj[n].m_Index)
					{
						continue;
					}
						if(!strcmp(lpObj->Ip_addr, gObj[n].Ip_addr))
						{
							CountIpAddress++;
								
						}
						
				}
		}
		if(CountIpAddress >= 2)
		{
			g_ConnectZt.SendClose(aIndex, NORM_DC);
			return;
		}
			
	}
#endif

	if(g_ZtLicense.CheckUser(eZtUB::ulasevich) || g_ZtLicense.CheckUser(eZtUB::Local3) || g_ZtLicense.CheckUser(eZtUB::ulasevich2))
	{
		if(ZtConfig.PlayerConnect.ShowNameAll == 1)
		{
			MessageSendAllEx(ZtConfig.PlayerConnect.ShowNameColor,"[System]", "%s Online" , lpObj->Name);
		}
		if ( CheckAuthorityCondition(98, lpObj) == true) //season4 changed
		{
			if(ZtConfig.PlayerConnect.ShowGMAll == 1)
			{
				MessaageAllGlobal("[%s]:Online", lpObj->Name);
			}
		}
	}
	if(!ZtConfig.PlayerConnect.EnablePlayerConnectSystem)
		return;

#ifdef _UPDATE8_
	if(ZtConfig.PlayerConnect.ShowOnline)	MsgNormal(aIndex, g_ZtText.GetText(2), getShowOnline());
#endif
	if(ZtConfig.PlayerConnect.ShowReset) MsgNormal(aIndex, g_ZtText.GetText(0), lpObj->Reset);
	if(ZtConfig.PlayerConnect.ShowGReset) MsgNormal(aIndex, g_ZtText.GetText(1), lpObj->GReset);
}