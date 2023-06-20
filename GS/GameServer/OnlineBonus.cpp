#include "StdAfx.h"
#include "user.h"
#include "OnlineBonus.h"
#include "DSProtocol.h"
#include "Message.h"
#include "ZtUser.h"
#include "ZtFunction.h"
#include "ZtText.h"

OnlineBonus gOnlineBonus;

void OnlineBonus::Load()
{
	//CheckFile(ONLINEBONUS_DIR);

	this->Enable = GetPrivateProfileInt("ZtTeam","Enable",0,ONLINEBONUS_DIR); 

	this->WCoinCActive = GetPrivateProfileInt("ZtTeam","WCoinCActive",0,ONLINEBONUS_DIR);
	this->WCoinCTime = GetPrivateProfileInt("ZtTeam","WCoinCTime",0,ONLINEBONUS_DIR) * 60;
	this->WCoinCBonus = GetPrivateProfileInt("ZtTeam","WCoinCBonus",0,ONLINEBONUS_DIR);

	this->WCoinPActive = GetPrivateProfileInt("ZtTeam","WCoinPActive",0,ONLINEBONUS_DIR);
	this->WCoinPTime = GetPrivateProfileInt("ZtTeam","WCoinPTime",0,ONLINEBONUS_DIR) * 60;
	this->WCoinPBonus = GetPrivateProfileInt("ZtTeam","WCoinPBonus",0,ONLINEBONUS_DIR);

	this->GoblinActive = GetPrivateProfileInt("ZtTeam","GoblinActive",0,ONLINEBONUS_DIR);
	this->GoblinTime = GetPrivateProfileInt("ZtTeam","GoblinTime",0,ONLINEBONUS_DIR) * 60;
	this->GoblinBonus = GetPrivateProfileInt("ZtTeam","GoblinBonus",0,ONLINEBONUS_DIR);

	this->ZtCredActive = GetPrivateProfileInt("ZtTeam","ZtCredActive",0,ONLINEBONUS_DIR);
	this->ZtCredTime = GetPrivateProfileInt("ZtTeam","ZtCredTime",0,ONLINEBONUS_DIR) * 60;
	this->ZtCredBonus = GetPrivateProfileInt("ZtTeam","ZtCredBonus",0,ONLINEBONUS_DIR);

#if(LICENSE_UKRAINE)
	this->AutoExpActive = GetPrivateProfileInt("ZtTeam","AutoExpActive",0,ONLINEBONUS_DIR);
	this->AutoExpTimeSec = GetPrivateProfileInt("ZtTeam","AutoExpTimeSec",0,ONLINEBONUS_DIR);
	this->AutoExpBonus = GetPrivateProfileInt("ZtTeam","AutoExpBonus",0,ONLINEBONUS_DIR);
	this->AutoExpMaxLvl = GetPrivateProfileInt("ZtTeam","AutoExpMaxLvl",0,ONLINEBONUS_DIR);
#endif
}

void OnlineBonus::TickTime(int aIndex)
{
	if(!this->Enable) return;

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->OffExp > 0 || lpObj->OffTrade > 0)
	{
		return;
	}

	if(lpObj->m_OfflineMode)
	{
		return;
	}

	if(this->WCoinCActive)
	{
		lpObj->WCoinCTick++;
		if(lpObj->WCoinCTick >= this->WCoinCTime)
		{
			lpObj->WCoinCTick = 0;
			lpObj->GameShop.WCoinC += this->WCoinCBonus;
			gGameShop.GDSaveUserInfo(aIndex);
			MessageChat(aIndex, g_ZtText.GetText(88), this->WCoinCBonus);
		}
	}

	if(this->WCoinPActive)
	{
		lpObj->WCoinPTick++;
		if(lpObj->WCoinPTick >= this->WCoinPTime)
		{
			lpObj->WCoinPTick = 0;
			lpObj->GameShop.WCoinP += this->WCoinPBonus;
			gGameShop.GDSaveUserInfo(aIndex);
			MessageChat(aIndex, g_ZtText.GetText(89), this->WCoinPBonus);
		}
	}

	if(this->GoblinActive)
	{
		lpObj->GoblinTick++;
		if(lpObj->GoblinTick == this->GoblinTime)
		{
			lpObj->GoblinTick = 0;
			lpObj->GameShop.GoblinPoint += this->GoblinBonus;
			gGameShop.GDSaveUserInfo(aIndex);
			MessageChat(aIndex, g_ZtText.GetText(90), this->GoblinBonus);
		}
	}

	if(this->ZtCredActive)
	{
		lpObj->ZtCredTick++;
		if(lpObj->ZtCredTick >= this->ZtCredTime)
		{
			lpObj->ZtCredTick = 0;
			lpObj->ZtCred += this->ZtCredBonus;
#ifndef FIX_DS_CRASH
			GJSetCharacterInfo(lpObj, lpObj->m_Index, 0);
#endif
			ZtUserDataSend(aIndex);
			MessageChat(aIndex, g_ZtText.GetText(91),this->ZtCredBonus);
		}
	}

	#if(LICENSE_UKRAINE)

	if(this->AutoExpActive)
	{
		if(this->AutoExpMaxLvl >= lpObj->Level)
		{
			lpObj->AutoExpTick++;

			if(lpObj->AutoExpTick >= this->AutoExpTimeSec)
			{
				lpObj->AutoExpTick = 0;

				__int64 addexp = this->AutoExpBonus * lpObj->Level;

				lpObj->Experience += addexp;

				if(gObjLevelUp(lpObj, addexp, 0, 0) == true)
				{
					GCKillPlayerExpSend(lpObj->m_Index, (WORD)-1, addexp, 0, 0);
				}
			}
		}
	}
	
	#endif
}

void OnlineBonus::TickSecond(int aIndex)
{
	if(!this->Enable) return;

	LPOBJ lpObj = &gObj[aIndex];

}