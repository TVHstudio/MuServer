#include "StdAfx.h"
#include "JewelsBank.h"
#include "user.h"
#include "Message.h"
#include "Functions.h"
#include "DSProtocol.h"
#include "ZtUser.h"
#include "ZtLicense.h"
#include "ZtFunction.h"
#include "ZtText.h"

JewelsBank gJewelsBank;

void JewelsBank::Load()
{
	this->Enable = GetPrivateProfileInt("ZtTeam","Enable",0,JEWELSBANK_DIR); 
#ifdef PRIVATE_MODULE
#if _CONFLICT_
	if(g_ZtLicense.CheckUser(eZtUB::Local3) || g_ZtLicense.CheckUser(SILVER1) || g_ZtLicense.CheckUser(SILVER2) || g_ZtLicense.CheckUser(eZtUB::drynea))
	{
		this->ZtChaosTeen = GetPrivateProfileInt("ZtTeam","ZtChaosTeen",0,JEWELSBANK_DIR);
		this->ZtChaosTwenty = GetPrivateProfileInt("ZtTeam","ZtChaosTwenty",0,JEWELSBANK_DIR);
		this->ZtChaosThirty = GetPrivateProfileInt("ZtTeam","ZtChaosThirty",0,JEWELSBANK_DIR);
		this->ZtChaosForty = GetPrivateProfileInt("ZtTeam","ZtChaosForty",0,JEWELSBANK_DIR);
		this->ZtChaosFifty = GetPrivateProfileInt("ZtTeam","ZtChaosFifty",0,JEWELSBANK_DIR);
		this->ZtChaosHundred = GetPrivateProfileInt("ZtTeam","ZtChaosHundred",0,JEWELSBANK_DIR);

		this->ZtBlessTeen = GetPrivateProfileInt("ZtTeam","ZtBlessTeen",0,JEWELSBANK_DIR);
		this->ZtBlessTwenty = GetPrivateProfileInt("ZtTeam","ZtBlessTwenty",0,JEWELSBANK_DIR);
		this->ZtBlessThirty = GetPrivateProfileInt("ZtTeam","ZtBlessThirty",0,JEWELSBANK_DIR);
		this->ZtBlessForty = GetPrivateProfileInt("ZtTeam","ZtBlessForty",0,JEWELSBANK_DIR);
		this->ZtBlessFifty = GetPrivateProfileInt("ZtTeam","ZtBlessFifty",0,JEWELSBANK_DIR);
		this->ZtBlessHundred = GetPrivateProfileInt("ZtTeam","ZtBlessHundred",0,JEWELSBANK_DIR);

		this->ZtSoulTeen = GetPrivateProfileInt("ZtTeam","ZtSoulTeen",0,JEWELSBANK_DIR);
		this->ZtSoulTwenty = GetPrivateProfileInt("ZtTeam","ZtSoulTwenty",0,JEWELSBANK_DIR);
		this->ZtSoulThirty = GetPrivateProfileInt("ZtTeam","ZtSoulThirty",0,JEWELSBANK_DIR);
		this->ZtSoulForty = GetPrivateProfileInt("ZtTeam","ZtSoulForty",0,JEWELSBANK_DIR);
		this->ZtSoulFifty = GetPrivateProfileInt("ZtTeam","ZtSoulFifty",0,JEWELSBANK_DIR);
		this->ZtSoulHundred = GetPrivateProfileInt("ZtTeam","ZtSoulHundred",0,JEWELSBANK_DIR);

		this->ZtLifeTeen = GetPrivateProfileInt("ZtTeam","ZtLifeTeen",0,JEWELSBANK_DIR);
		this->ZtLifeTwenty = GetPrivateProfileInt("ZtTeam","ZtLifeTwenty",0,JEWELSBANK_DIR);
		this->ZtLifeThirty = GetPrivateProfileInt("ZtTeam","ZtLifeThirty",0,JEWELSBANK_DIR);
		this->ZtLifeForty = GetPrivateProfileInt("ZtTeam","ZtLifeForty",0,JEWELSBANK_DIR);
		this->ZtLifeFifty = GetPrivateProfileInt("ZtTeam","ZtLifeFifty",0,JEWELSBANK_DIR);
		this->ZtLifeHundred = GetPrivateProfileInt("ZtTeam","ZtLifeHundred",0,JEWELSBANK_DIR);

		this->ZtCreateonTeen = GetPrivateProfileInt("ZtTeam","ZtCreateonTeen",0,JEWELSBANK_DIR);
		this->ZtCreateonTwenty = GetPrivateProfileInt("ZtTeam","ZtCreateonTwenty",0,JEWELSBANK_DIR);
		this->ZtCreateonThirty = GetPrivateProfileInt("ZtTeam","ZtCreateonThirty",0,JEWELSBANK_DIR);
		this->ZtCreateonForty = GetPrivateProfileInt("ZtTeam","ZtCreateonForty",0,JEWELSBANK_DIR);
		this->ZtCreateonFifty = GetPrivateProfileInt("ZtTeam","ZtCreateonFifty",0,JEWELSBANK_DIR);
		this->ZtCreateonHundred = GetPrivateProfileInt("ZtTeam","ZtCreateonHundred",0,JEWELSBANK_DIR);

	/**/
		this->ZtGuardianTeen = GetPrivateProfileInt("ZtTeam","ZtGuardianTeen",0,JEWELSBANK_DIR);
		this->ZtGuardianTwenty = GetPrivateProfileInt("ZtTeam","ZtGuardianTwenty",0,JEWELSBANK_DIR);
		this->ZtGuardianThirty = GetPrivateProfileInt("ZtTeam","ZtGuardianThirty",0,JEWELSBANK_DIR);
		this->ZtGuardianForty = GetPrivateProfileInt("ZtTeam","ZtGuardianForty",0,JEWELSBANK_DIR);
		this->ZtGuardianFifty = GetPrivateProfileInt("ZtTeam","ZtGuardianFifty",0,JEWELSBANK_DIR);
		this->ZtGuardianHundred = GetPrivateProfileInt("ZtTeam","ZtGuardianHundred",0,JEWELSBANK_DIR);

		this->ZtHarmonyTeen = GetPrivateProfileInt("ZtTeam","ZtHarmonyTeen",0,JEWELSBANK_DIR);
		this->ZtHarmonyTwenty = GetPrivateProfileInt("ZtTeam","ZtHarmonyTwenty",0,JEWELSBANK_DIR);
		this->ZtHarmonyThirty = GetPrivateProfileInt("ZtTeam","ZtHarmonyThirty",0,JEWELSBANK_DIR);
		this->ZtHarmonyForty = GetPrivateProfileInt("ZtTeam","ZtHarmonyForty",0,JEWELSBANK_DIR);
		this->ZtHarmonyFifty = GetPrivateProfileInt("ZtTeam","ZtHarmonyFifty",0,JEWELSBANK_DIR);
		this->ZtHarmonyHundred = GetPrivateProfileInt("ZtTeam","ZtHarmonyHundred",0,JEWELSBANK_DIR);

		this->ZtLowStoneTeen = GetPrivateProfileInt("ZtTeam","ZtLowStoneTeen",0,JEWELSBANK_DIR);
		this->ZtLowStoneTwenty = GetPrivateProfileInt("ZtTeam","ZtLowStoneTwenty",0,JEWELSBANK_DIR);
		this->ZtLowStoneThirty = GetPrivateProfileInt("ZtTeam","ZtLowStoneThirty",0,JEWELSBANK_DIR);
		this->ZtLowStoneForty = GetPrivateProfileInt("ZtTeam","ZtLowStoneForty",0,JEWELSBANK_DIR);
		this->ZtLowStoneFifty = GetPrivateProfileInt("ZtTeam","ZtLowStoneFifty",0,JEWELSBANK_DIR);
		this->ZtLowStoneHundred = GetPrivateProfileInt("ZtTeam","ZtLowStoneHundred",0,JEWELSBANK_DIR);

		this->ZtHighStoneTeen = GetPrivateProfileInt("ZtTeam","ZtHighStoneTeen",0,JEWELSBANK_DIR);
		this->ZtHighStoneTwenty = GetPrivateProfileInt("ZtTeam","ZtHighStoneTwenty",0,JEWELSBANK_DIR);
		this->ZtHighStoneThirty = GetPrivateProfileInt("ZtTeam","ZtHighStoneThirty",0,JEWELSBANK_DIR);
		this->ZtHighStoneForty = GetPrivateProfileInt("ZtTeam","ZtHighStoneForty",0,JEWELSBANK_DIR);
		this->ZtHighStoneFifty = GetPrivateProfileInt("ZtTeam","ZtHighStoneFifty",0,JEWELSBANK_DIR);
		this->ZtHighStoneHundred = GetPrivateProfileInt("ZtTeam","ZtHighStoneHundred",0,JEWELSBANK_DIR);

		this->ZtGemStoneTeen = GetPrivateProfileInt("ZtTeam","ZtGemStoneTeen",0,JEWELSBANK_DIR);
		this->ZtGemStoneTwenty = GetPrivateProfileInt("ZtTeam","ZtGemStoneTwenty",0,JEWELSBANK_DIR);
		this->ZtGemStoneThirty = GetPrivateProfileInt("ZtTeam","ZtGemStoneThirty",0,JEWELSBANK_DIR);
		this->ZtGemStoneForty = GetPrivateProfileInt("ZtTeam","ZtGemStoneForty",0,JEWELSBANK_DIR);
		this->ZtGemStoneFifty = GetPrivateProfileInt("ZtTeam","ZtGemStoneFifty",0,JEWELSBANK_DIR);
		this->ZtGemStoneHundred = GetPrivateProfileInt("ZtTeam","ZtGemStoneHundred",0,JEWELSBANK_DIR);
	/**/
	}
#endif
#endif
}

void JewelsBank::sendchaosbank(int aIndex, int Count)
{
	if(!this->Enable) return;
	if(gObjGetItemCountInInventory(aIndex,ITEMGET(12,15),0) < Count)
	{
		MsgNormal(aIndex,g_ZtText.GetText(147),Count);
		return;
	}
	gObjDeleteItemsCount(aIndex,ITEMGET(12,15),0,Count);
	LPOBJ lpObj = &gObj[aIndex];
	lpObj->ChaosBank += Count;
	ZtUserDataSend(aIndex);
	MsgNormal(aIndex,g_ZtText.GetText(148),Count);
}

void JewelsBank::sendblessbank(int aIndex, int Count)
{
	if(!this->Enable) return;
	if(gObjGetItemCountInInventory(aIndex,ITEMGET(14,13),0) < Count)
	{
		MsgNormal(aIndex,g_ZtText.GetText(149),Count);
		return;
	}
	gObjDeleteItemsCount(aIndex,ITEMGET(14,13),0,Count);
	LPOBJ lpObj = &gObj[aIndex];
	lpObj->BlessBank += Count;
	ZtUserDataSend(aIndex);
	MsgNormal(aIndex,g_ZtText.GetText(150),Count);
}

void JewelsBank::sendsoulbank(int aIndex, int Count)
{
	if(!this->Enable) return;
	if(gObjGetItemCountInInventory(aIndex,ITEMGET(14,14),0) < Count)
	{
		MsgNormal(aIndex,g_ZtText.GetText(151),Count);
		return;
	}
	gObjDeleteItemsCount(aIndex,ITEMGET(14,14),0,Count);
	LPOBJ lpObj = &gObj[aIndex];
	lpObj->SoulBank += Count;
	ZtUserDataSend(aIndex);
	MsgNormal(aIndex,g_ZtText.GetText(152),Count);
}

void JewelsBank::sendlifebank(int aIndex, int Count)
{
	if(!this->Enable) return;
#ifdef PRIVATE_MODULE
	if(g_ZtLicense.CheckUser(eZtUB::Vadim))
	{
		if(gObjGetItemCountInInventory(aIndex,ITEMGET(14,187),0) < Count)
		{
			MsgNormal(aIndex,"[JewelsBank] Need %d JoR",Count);
			return;
		}
		gObjDeleteItemsCount(aIndex,ITEMGET(14,187),0,Count);
		LPOBJ lpObj = &gObj[aIndex];
		lpObj->LifeBank += Count;
		ZtUserDataSend(aIndex);

		MsgNormal(aIndex,"[JewelsBank] Send %d JoR",Count);
	}
	else
	{
		if(gObjGetItemCountInInventory(aIndex,ITEMGET(14,16),0) < Count)
		{
			MsgNormal(aIndex,g_ZtText.GetText(153),Count);
			return;
		}
		gObjDeleteItemsCount(aIndex,ITEMGET(14,16),0,Count);
		LPOBJ lpObj = &gObj[aIndex];
		lpObj->LifeBank += Count;
		ZtUserDataSend(aIndex);

		MsgNormal(aIndex,g_ZtText.GetText(154),Count);
	}
#else
	if(gObjGetItemCountInInventory(aIndex,ITEMGET(14,16),0) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Need %d Life",Count);
		return;
	}
	gObjDeleteItemsCount(aIndex,ITEMGET(14,16),0,Count);
	LPOBJ lpObj = &gObj[aIndex];
	lpObj->LifeBank += Count;
	ZtUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Send %d Life",Count);
#endif
}

void JewelsBank::sendcreateonbank(int aIndex, int Count)
{
	if(!this->Enable) return;

	if(gObjGetItemCountInInventory(aIndex,ITEMGET(14,22),0) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Need %d Createon",Count);
		return;
	}
	gObjDeleteItemsCount(aIndex,ITEMGET(14,22),0,Count);
	LPOBJ lpObj = &gObj[aIndex];
	lpObj->CreateonBank += Count;
	ZtUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Send %d Createon",Count);
}

//-----------------------------------------------------

void JewelsBank::recvchaosbank(int aIndex, int Count)
{
	if(!this->Enable) return;
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->ChaosBank < Count)
	{
		MsgNormal(aIndex,g_ZtText.GetText(155),Count);
		return;
	}

	//if(CheckInventoryEmptySpace(lpObj,4,2) == false )
	if(ExCheckInventoryEmptySpace(aIndex) < Count)
	{
		MsgNormal(aIndex,g_ZtText.GetText(156),Count);
		return;
	}
	lpObj->ChaosBank -= Count;
	for(int i=0;i<Count;i++)
	{
		ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(12,15),0,0,0,0,0,aIndex,0,0);
	}
	ZtUserDataSend(aIndex);
	MsgNormal(aIndex,g_ZtText.GetText(157),Count);
}

void JewelsBank::recvblessbank(int aIndex, int Count)
{
	if(!this->Enable) return;
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->BlessBank < Count)
	{
		MsgNormal(aIndex,g_ZtText.GetText(158),Count);
		return;
	}
	if(ExCheckInventoryEmptySpace(aIndex) < Count)
	{
		MsgNormal(aIndex,g_ZtText.GetText(156),Count);
		return;
	}
	lpObj->BlessBank -= Count;
	for(int i=0;i<Count;i++)
	{
		ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(14,13),0,0,0,0,0,aIndex,0,0);
	}
	ZtUserDataSend(aIndex);
	MsgNormal(aIndex,g_ZtText.GetText(159),Count);
}

void JewelsBank::recvsoulbank(int aIndex, int Count)
{
	if(!this->Enable) return;
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->SoulBank < Count)
	{
		MsgNormal(aIndex,g_ZtText.GetText(160),Count);
		return;
	}
	if(ExCheckInventoryEmptySpace(aIndex) < Count)
	{
		MsgNormal(aIndex,g_ZtText.GetText(156),Count);
		return;
	}
	lpObj->SoulBank -= Count;
	for(int i=0;i<Count;i++)
	{
		ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(14,14),0,0,0,0,0,aIndex,0,0);
	}
	ZtUserDataSend(aIndex);
	MsgNormal(aIndex,g_ZtText.GetText(161),Count);
}

void JewelsBank::recvlifebank(int aIndex, int Count)
{
	if(!this->Enable) return;

#ifdef PRIVATE_MODULE
	if(g_ZtLicense.CheckUser(eZtUB::Vadim))
	{
		LPOBJ lpObj = &gObj[aIndex];
		if(lpObj->LifeBank < Count)
		{
			MsgNormal(aIndex,"[JewelsBank] No %d JoR",Count);
			return;
		}
		if(ExCheckInventoryEmptySpace(aIndex) < Count)
		{
			MsgNormal(aIndex,g_ZtText.GetText(156),Count);
			return;
		}
		lpObj->LifeBank -= Count;
		for(int i=0;i<Count;i++)
		{
			ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(14,187),0,0,0,0,0,aIndex,0,0);
		}
		ZtUserDataSend(aIndex);

		MsgNormal(aIndex,"[JewelsBank] Recv %d JoR",Count);
	}
	else
	{
		LPOBJ lpObj = &gObj[aIndex];
		if(lpObj->LifeBank < Count)
		{
			MsgNormal(aIndex,g_ZtText.GetText(162),Count);
			return;
		}
		if(ExCheckInventoryEmptySpace(aIndex) < Count)
		{
			MsgNormal(aIndex,g_ZtText.GetText(156),Count);
			return;
		}
		lpObj->LifeBank -= Count;
		for(int i=0;i<Count;i++)
		{
			ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(14,16),0,0,0,0,0,aIndex,0,0);
		}
		ZtUserDataSend(aIndex);

		MsgNormal(aIndex,g_ZtText.GetText(163),Count);
	}
#else
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->LifeBank < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] No %d Life",Count);
		return;
	}
	if(ExCheckInventoryEmptySpace(aIndex) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Inventory %d",Count);
		return;
	}
	lpObj->LifeBank -= Count;
	for(int i=0;i<Count;i++)
	{
		ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(14,16),0,0,0,0,0,aIndex,0,0);
	}
	ZtUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Recv %d Life",Count);
#endif
}

void JewelsBank::recvcreateonbank(int aIndex, int Count)
{
	if(!this->Enable) return;

	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->CreateonBank < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] No %d Createon",Count);
		return;
	}
	if(ExCheckInventoryEmptySpace(aIndex) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Inventory %d",Count);
		return;
	}
	lpObj->CreateonBank -= Count;
	for(int i=0;i<Count;i++)
	{
		ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(14,22),0,0,0,0,0,aIndex,0,0);
	}
	ZtUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Recv %d Createon",Count);

}

#ifdef PRIVATE_MODULE
#if _CONFLICT_
void JewelsBank::exchaos(int aIndex, int Count)
{
	if(g_ZtLicense.CheckUser(eZtUB::Local3) || g_ZtLicense.CheckUser(SILVER1) || g_ZtLicense.CheckUser(SILVER2) || g_ZtLicense.CheckUser(eZtUB::drynea))
	{
		if(!this->Enable) return;
		LPOBJ lpObj = &gObj[aIndex];
		if(lpObj->ChaosBank < Count)
		{
			MsgNormal(aIndex,"[JewelsBank] No %d Chaos",Count);
			return;
		}

		if (Count == 10)
		{
			lpObj->ChaosBank -= Count;
			lpObj->ZtCred += ZtChaosTeen;
			CountExChaos = ZtChaosTeen;
		}
		else if (Count == 20)
		{
			lpObj->ChaosBank -= Count;
			lpObj->ZtCred += ZtChaosTwenty;
			CountExChaos = ZtChaosTwenty;
		}
		else if (Count == 30)
		{
			lpObj->ChaosBank -= Count;
			lpObj->ZtCred += ZtChaosThirty;
			CountExChaos = ZtChaosThirty;
		}
		else if (Count == 40)
		{
			lpObj->ChaosBank -= Count;
			lpObj->ZtCred += ZtChaosForty;
			CountExChaos = ZtChaosForty;
		}
		else if (Count == 50)
		{
			lpObj->ChaosBank -= Count;
			lpObj->ZtCred += ZtChaosFifty;
			CountExChaos = ZtChaosFifty;
		}
		else if (Count == 100)
		{
			lpObj->ChaosBank -= Count;
			lpObj->ZtCred += ZtChaosHundred;
			CountExChaos = ZtChaosHundred;
		}
		else
		{
			MsgNormal(aIndex,"[JewelsBank] Exchange Only 10 20 30 40 50 100");
			return;
		}
		
		/*int ZtChaosForty;
	int ZtChaosFifty;
	int ZtChaosHundred;*/

		ZtUserDataSend(aIndex);
		MsgNormal(aIndex,"[JewelsBank] Exchange %d Jewel of Chaos Added %d Credits" ,Count, CountExChaos);
	}
}

void JewelsBank::exbless(int aIndex, int Count)
{
	if(g_ZtLicense.CheckUser(eZtUB::Local3) || g_ZtLicense.CheckUser(SILVER1) || g_ZtLicense.CheckUser(SILVER2) || g_ZtLicense.CheckUser(eZtUB::drynea))
	{
		if(!this->Enable) return;
		LPOBJ lpObj = &gObj[aIndex];
		if(lpObj->BlessBank < Count)
		{
			MsgNormal(aIndex,"[JewelsBank] No %d Bless",Count);
			return;
		}
		if (Count == 10)
		{
			lpObj->BlessBank -= Count;
			lpObj->ZtCred += ZtBlessTeen;
			CountExBless = ZtBlessTeen;
		}
		else if (Count == 20)
		{
			lpObj->BlessBank -= Count;
			lpObj->ZtCred += ZtBlessTwenty;
			CountExBless = ZtBlessTwenty;
		}
		else if (Count == 30)
		{
			lpObj->BlessBank -= Count;
			lpObj->ZtCred += ZtBlessThirty;
			CountExBless = ZtBlessThirty;
		}		
		else if (Count == 40)
		{
			lpObj->BlessBank -= Count;
			lpObj->ZtCred += ZtBlessForty;
			CountExBless = ZtBlessForty;
		}
		else if (Count == 50)
		{
			lpObj->BlessBank -= Count;
			lpObj->ZtCred += ZtBlessFifty;
			CountExBless = ZtBlessFifty;
		}
		else if (Count == 100)
		{
			lpObj->BlessBank -= Count;
			lpObj->ZtCred += ZtBlessHundred;
			CountExBless = ZtBlessHundred;
		}
		else{
			MsgNormal(aIndex,"[JewelsBank] Exchange Only 10 20 30 40 50 100");
			return;
		}

		ZtUserDataSend(aIndex);
		MsgNormal(aIndex,"[JewelsBank] Exchange %d Jewel of Bless Added %d Credits" ,Count, CountExBless);
	}
}

void JewelsBank::exsoul(int aIndex, int Count)
{
	if(g_ZtLicense.CheckUser(eZtUB::Local3) || g_ZtLicense.CheckUser(SILVER1) || g_ZtLicense.CheckUser(SILVER2) || g_ZtLicense.CheckUser(eZtUB::drynea))
	{
	if(!this->Enable) return;
		LPOBJ lpObj = &gObj[aIndex];
		if(lpObj->SoulBank < Count)
		{
			MsgNormal(aIndex,"[JewelsBank] No %d Soul",Count);
			return;
		}
		
		if (Count == 10)
		{
			lpObj->SoulBank -= Count;
			lpObj->ZtCred += ZtSoulTeen;
			CountExSoul = ZtSoulTeen;
		}
		else if (Count == 20)
		{
			lpObj->SoulBank -= Count;
			lpObj->ZtCred += ZtSoulTwenty;
			CountExSoul = ZtSoulTwenty;
		}
		else if (Count == 30)
		{
			lpObj->SoulBank -= Count;
			lpObj->ZtCred += ZtSoulThirty;
			CountExSoul = ZtSoulThirty;
		}
		else if (Count == 40)
		{
			lpObj->SoulBank -= Count;
			lpObj->ZtCred += ZtSoulForty;
			CountExSoul = ZtSoulForty;
		}
		else if (Count == 50)
		{
			lpObj->SoulBank -= Count;
			lpObj->ZtCred += ZtSoulFifty;
			CountExSoul = ZtSoulFifty;
		}
		else if (Count == 100)
		{
			lpObj->SoulBank -= Count;
			lpObj->ZtCred += ZtSoulHundred;
			CountExSoul = ZtSoulHundred;
		}
		else{
			MsgNormal(aIndex,"[JewelsBank] Exchange Only 10 20 30 40 50 100");
			return;
		}
		
		
		ZtUserDataSend(aIndex);
		MsgNormal(aIndex,"[JewelsBank] Exchange %d Jewel of Soul Added %d Credits" ,Count, CountExSoul);
	}
}

void JewelsBank::exlife(int aIndex, int Count)
{
	if(g_ZtLicense.CheckUser(eZtUB::Local3) || g_ZtLicense.CheckUser(SILVER1) || g_ZtLicense.CheckUser(SILVER2) || g_ZtLicense.CheckUser(eZtUB::drynea))
	{
		if(!this->Enable) return;
		LPOBJ lpObj = &gObj[aIndex];
		if(lpObj->LifeBank < Count)
		{
			MsgNormal(aIndex,"[JewelsBank] No %d Life",Count);
			return;
		}
		if (Count == 10)
			{
				lpObj->LifeBank -= Count;
				lpObj->ZtCred += ZtLifeTeen;
				CountExLife = ZtLifeTeen;
			}
			else if (Count == 20)
			{
				lpObj->LifeBank -= Count;
				lpObj->ZtCred += ZtLifeTwenty;
				CountExLife = ZtLifeTwenty;
			}
			else if (Count == 30)
			{
				lpObj->LifeBank -= Count;
				lpObj->ZtCred += ZtLifeThirty;
				CountExLife = ZtLifeThirty;
			}
		else if (Count == 40)
		{
			lpObj->LifeBank -= Count;
			lpObj->ZtCred += ZtLifeForty;
			CountExLife = ZtLifeForty;
		}
		else if (Count == 50)
		{
			lpObj->LifeBank -= Count;
			lpObj->ZtCred += ZtLifeFifty;
			CountExLife = ZtLifeFifty;
		}
		else if (Count == 100)
		{
			lpObj->LifeBank -= Count;
			lpObj->ZtCred += ZtLifeHundred;
			CountExLife = ZtLifeHundred;
		}
		else{
				MsgNormal(aIndex,"[JewelsBank] Exchange Only 10 20 30 40 50 100");
				return;
			}

		ZtUserDataSend(aIndex);

		MsgNormal(aIndex,"[JewelsBank] Exchange %d Jewel of Life Added %d Credits " ,Count, CountExLife);
	}
}

void JewelsBank::excreateon(int aIndex, int Count)
{
	if(g_ZtLicense.CheckUser(eZtUB::Local3) || g_ZtLicense.CheckUser(SILVER1) || g_ZtLicense.CheckUser(SILVER2) || g_ZtLicense.CheckUser(eZtUB::drynea))
	{
		if(!this->Enable) return;
		LPOBJ lpObj = &gObj[aIndex];
		if(lpObj->CreateonBank < Count)
		{
			MsgNormal(aIndex,"[JewelsBank] No %d Createon",Count);
			return;
		}
		if (Count == 10)
			{
				lpObj->CreateonBank -= Count;
				lpObj->ZtCred += ZtCreateonTeen;
				CountExCreateon = ZtCreateonTeen;
			}
			else if (Count == 20)
			{
				lpObj->CreateonBank -= Count;
				lpObj->ZtCred += ZtCreateonTwenty;
				CountExCreateon = ZtCreateonTwenty;
			}
			else if (Count == 30)
			{
				lpObj->CreateonBank -= Count;
				lpObj->ZtCred += ZtCreateonThirty;
				CountExCreateon = ZtCreateonThirty;
			}
		else if (Count == 40)
		{
			lpObj->CreateonBank -= Count;
			lpObj->ZtCred += ZtCreateonForty;
			CountExCreateon = ZtCreateonForty;
		}
		else if (Count == 50)
		{
			lpObj->CreateonBank -= Count;
			lpObj->ZtCred += ZtCreateonFifty;
			CountExCreateon = ZtCreateonFifty;
		}
		else if (Count == 100)
		{
			lpObj->CreateonBank -= Count;
			lpObj->ZtCred += ZtCreateonHundred;
			CountExCreateon = ZtCreateonHundred;
		}
		else{
				MsgNormal(aIndex,"[JewelsBank] Exchange Only 10 20 30 40 50 100");
				return;
			}

		ZtUserDataSend(aIndex);

		MsgNormal(aIndex,"[JewelsBank] Exchange %d Jewel of Createon Added %d Credits " ,Count, CountExCreateon);
	}
}

void JewelsBank::exGuardian(int aIndex, int Count)
{
	if( !g_ZtLicense.CheckUser(eZtUB::Local3)  && 
		!g_ZtLicense.CheckUser(eZtUB::SILVER1) &&
		!g_ZtLicense.CheckUser(eZtUB::SILVER2) && 
		!g_ZtLicense.CheckUser(eZtUB::drynea) )
	{
		return;
	}

	if(!this->Enable) return;

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->GuardianBank < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] No %d Guardian",Count);
		return;
	}

	int CountJewels = 0;

	if (Count == 10)
	{
		lpObj->GuardianBank -= Count;
		lpObj->ZtCred += this->ZtGuardianTeen;
		CountJewels = this->ZtGuardianTeen;
	}
	else if (Count == 20)
	{
		lpObj->GuardianBank -= Count;
		lpObj->ZtCred += this->ZtGuardianTwenty;
		CountJewels = this->ZtGuardianTwenty;
	}
	else if (Count == 30)
	{
		lpObj->GuardianBank -= Count;
		lpObj->ZtCred += this->ZtGuardianThirty;
		CountJewels = this->ZtGuardianThirty;
	}
	else if (Count == 40)
	{
		lpObj->GuardianBank -= Count;
		lpObj->ZtCred += this->ZtGuardianForty;
		CountJewels = this->ZtGuardianForty;
	}
	else if (Count == 50)
	{
		lpObj->GuardianBank -= Count;
		lpObj->ZtCred += this->ZtGuardianFifty;
		CountJewels = this->ZtGuardianFifty;
	}
	else if (Count == 100)
	{
		lpObj->GuardianBank -= Count;
		lpObj->ZtCred += this->ZtGuardianHundred;
		CountJewels = this->ZtGuardianHundred;
	}
	else
	{
		MsgNormal(aIndex,"[JewelsBank] Exchange Only 10 20 30 40 50 100");
		return;
	}

	ZtUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Exchange %d Jewel of Guardian Added %d Credits " ,Count, CountJewels);
}

void JewelsBank::exHarmony(int aIndex, int Count)
{
	if( !g_ZtLicense.CheckUser(eZtUB::Local3)  && 
		!g_ZtLicense.CheckUser(eZtUB::SILVER1) &&
		!g_ZtLicense.CheckUser(eZtUB::SILVER2) && 
		!g_ZtLicense.CheckUser(eZtUB::drynea) )
	{
		return;
	}

	if(!this->Enable) return;

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->HarmonyBank < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] No %d Harmony",Count);
		return;
	}

	int CountJewels = 0;

	if (Count == 10)
	{
		lpObj->HarmonyBank -= Count;
		lpObj->ZtCred += this->ZtHarmonyTeen;
		CountJewels = this->ZtHarmonyTeen;
	}
	else if (Count == 20)
	{
		lpObj->HarmonyBank -= Count;
		lpObj->ZtCred += this->ZtHarmonyTwenty;
		CountJewels = this->ZtHarmonyTwenty;
	}
	else if (Count == 30)
	{
		lpObj->HarmonyBank -= Count;
		lpObj->ZtCred += this->ZtHarmonyThirty;
		CountJewels = this->ZtHarmonyThirty;
	}
	else if (Count == 40)
	{
		lpObj->HarmonyBank -= Count;
		lpObj->ZtCred += this->ZtHarmonyForty;
		CountJewels = this->ZtHarmonyForty;
	}
	else if (Count == 50)
	{
		lpObj->HarmonyBank -= Count;
		lpObj->ZtCred += this->ZtHarmonyFifty;
		CountJewels = this->ZtHarmonyFifty;
	}
	else if (Count == 100)
	{
		lpObj->HarmonyBank -= Count;
		lpObj->ZtCred += this->ZtHarmonyHundred;
		CountJewels = this->ZtHarmonyHundred;
	}
	else
	{
		MsgNormal(aIndex,"[JewelsBank] Exchange Only 10 20 30 40 50 100");
		return;
	}

	ZtUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Exchange %d Jewel of Harmony Added %d Credits " ,Count, CountJewels);
}

void JewelsBank::exLowStone(int aIndex, int Count)
{
	if( !g_ZtLicense.CheckUser(eZtUB::Local3)  && 
		!g_ZtLicense.CheckUser(eZtUB::SILVER1) &&
		!g_ZtLicense.CheckUser(eZtUB::SILVER2) && 
		!g_ZtLicense.CheckUser(eZtUB::drynea) )
	{
		return;
	}

	if(!this->Enable) return;

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->LowStoneBank < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] No %d LowStone",Count);
		return;
	}

	int CountJewels = 0;

	if (Count == 10)
	{
		lpObj->LowStoneBank -= Count;
		lpObj->ZtCred += this->ZtLowStoneTeen;
		CountJewels = this->ZtLowStoneTeen;
	}
	else if (Count == 20)
	{
		lpObj->LowStoneBank -= Count;
		lpObj->ZtCred += this->ZtLowStoneTwenty;
		CountJewels = this->ZtLowStoneTwenty;
	}
	else if (Count == 30)
	{
		lpObj->LowStoneBank -= Count;
		lpObj->ZtCred += this->ZtLowStoneThirty;
		CountJewels = this->ZtLowStoneThirty;
	}
	else if (Count == 40)
	{
		lpObj->LowStoneBank -= Count;
		lpObj->ZtCred += this->ZtLowStoneForty;
		CountJewels = this->ZtLowStoneForty;
	}
	else if (Count == 50)
	{
		lpObj->LowStoneBank -= Count;
		lpObj->ZtCred += this->ZtLowStoneFifty;
		CountJewels = this->ZtLowStoneFifty;
	}
	else if (Count == 100)
	{
		lpObj->LowStoneBank -= Count;
		lpObj->ZtCred += this->ZtLowStoneHundred;
		CountJewels = this->ZtLowStoneHundred;
	}
	else
	{
		MsgNormal(aIndex,"[JewelsBank] Exchange Only 10 20 30 40 50 100");
		return;
	}

	ZtUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Exchange %d Jewel of LowStone Added %d Credits " ,Count, CountJewels);
}

void JewelsBank::exHighStone(int aIndex, int Count)
{
	if( !g_ZtLicense.CheckUser(eZtUB::Local3)  && 
		!g_ZtLicense.CheckUser(eZtUB::SILVER1) &&
		!g_ZtLicense.CheckUser(eZtUB::SILVER2) && 
		!g_ZtLicense.CheckUser(eZtUB::drynea) )
	{
		return;
	}

	if(!this->Enable) return;

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->HighStoneBank < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] No %d HighStone",Count);
		return;
	}

	int CountJewels = 0;

	if (Count == 10)
	{
		lpObj->HighStoneBank -= Count;
		lpObj->ZtCred += this->ZtHighStoneTeen;
		CountJewels = this->ZtHighStoneTeen;
	}
	else if (Count == 20)
	{
		lpObj->HighStoneBank -= Count;
		lpObj->ZtCred += this->ZtHighStoneTwenty;
		CountJewels = this->ZtHighStoneTwenty;
	}
	else if (Count == 30)
	{
		lpObj->HighStoneBank -= Count;
		lpObj->ZtCred += this->ZtHighStoneThirty;
		CountJewels = this->ZtHighStoneThirty;
	}
	else if (Count == 40)
	{
		lpObj->HighStoneBank -= Count;
		lpObj->ZtCred += this->ZtHighStoneForty;
		CountJewels = this->ZtHighStoneForty;
	}
	else if (Count == 50)
	{
		lpObj->HighStoneBank -= Count;
		lpObj->ZtCred += this->ZtHighStoneFifty;
		CountJewels = this->ZtHighStoneFifty;
	}
	else if (Count == 100)
	{
		lpObj->HighStoneBank -= Count;
		lpObj->ZtCred += this->ZtHighStoneHundred;
		CountJewels = this->ZtHighStoneHundred;
	}
	else
	{
		MsgNormal(aIndex,"[JewelsBank] Exchange Only 10 20 30 40 50 100");
		return;
	}

	ZtUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Exchange %d Jewel of HighStone Added %d Credits " ,Count, CountJewels);
}

void JewelsBank::exGemStone(int aIndex, int Count)
{
	if( !g_ZtLicense.CheckUser(eZtUB::Local3)  && 
		!g_ZtLicense.CheckUser(eZtUB::SILVER1) &&
		!g_ZtLicense.CheckUser(eZtUB::SILVER2) && 
		!g_ZtLicense.CheckUser(eZtUB::drynea) )
	{
		return;
	}

	if(!this->Enable) return;

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->GemStoneBank < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] No %d GemStone",Count);
		return;
	}

	int CountJewels = 0;

	if (Count == 10)
	{
		lpObj->GemStoneBank -= Count;
		lpObj->ZtCred += this->ZtGemStoneTeen;
		CountJewels = this->ZtGemStoneTeen;
	}
	else if (Count == 20)
	{
		lpObj->GemStoneBank -= Count;
		lpObj->ZtCred += this->ZtGemStoneTwenty;
		CountJewels = this->ZtGemStoneTwenty;
	}
	else if (Count == 30)
	{
		lpObj->GemStoneBank -= Count;
		lpObj->ZtCred += this->ZtGemStoneThirty;
		CountJewels = this->ZtGemStoneThirty;
	}
	else if (Count == 40)
	{
		lpObj->GemStoneBank -= Count;
		lpObj->ZtCred += this->ZtGemStoneForty;
		CountJewels = this->ZtGemStoneForty;
	}
	else if (Count == 50)
	{
		lpObj->GemStoneBank -= Count;
		lpObj->ZtCred += this->ZtGemStoneFifty;
		CountJewels = this->ZtGemStoneFifty;
	}
	else if (Count == 100)
	{
		lpObj->GemStoneBank -= Count;
		lpObj->ZtCred += this->ZtGemStoneHundred;
		CountJewels = this->ZtGemStoneHundred;
	}
	else
	{
		MsgNormal(aIndex,"[JewelsBank] Exchange Only 10 20 30 40 50 100");
		return;
	}

	ZtUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Exchange %d Jewel of GemStone Added %d Credits " ,Count, CountJewels);
}


#endif
#endif

void JewelsBank::sendzen(int aIndex, int Count)
{
	LPOBJ lpUser = &gObj[aIndex];
	unsigned int M = 1000000 * Count;
	if(M > lpUser->Money) return;
	lpUser->Money -= M;
	lpUser->Zen += Count;
	GCMoneySend(aIndex,lpUser->Money);
	ZtUserDataSend(aIndex);
}

void JewelsBank::recvzen(int aIndex, int Count)
{
	LPOBJ lpUser = &gObj[aIndex];
	int M = 1000000;
	unsigned long long totalzen = M + lpUser->Money;
	if(totalzen > MAX_ZEN) return;
	if(Count > lpUser->Zen) return;
	lpUser->Money += M;
	lpUser->Zen -= Count;
	GCMoneySend(aIndex,lpUser->Money);
	ZtUserDataSend(aIndex);
}

void JewelsBank::sendGuardianBank(int aIndex, int Count)
{
	if(gObjGetItemCountInInventory(aIndex,ITEMGET(14,31),0) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Need %d Guardian",Count);
		return;
	}
	gObjDeleteItemsCount(aIndex,ITEMGET(14,31),0,Count);
	LPOBJ lpObj = &gObj[aIndex];
	lpObj->GuardianBank += Count;
	ZtUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Send %d Guardian",Count);
}

void JewelsBank::sendHarmonyBank(int aIndex, int Count)
{
	if(gObjGetItemCountInInventory(aIndex,ITEMGET(14,42),0) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Need %d Harmony",Count);
		return;
	}
	gObjDeleteItemsCount(aIndex,ITEMGET(14,42),0,Count);
	LPOBJ lpObj = &gObj[aIndex];
	lpObj->HarmonyBank += Count;
	ZtUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Send %d Harmony",Count);
}

void JewelsBank::sendLowStoneBank(int aIndex, int Count)
{
	if(gObjGetItemCountInInventory(aIndex,ITEMGET(14,43),0) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Need %d LowStone",Count);
		return;
	}
	gObjDeleteItemsCount(aIndex,ITEMGET(14,43),0,Count);
	LPOBJ lpObj = &gObj[aIndex];
	lpObj->LowStoneBank += Count;
	ZtUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Send %d LowStone",Count);
}

void JewelsBank::sendHighStoneBank(int aIndex, int Count)
{
	if(gObjGetItemCountInInventory(aIndex,ITEMGET(14,44),0) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Need %d HighStone",Count);
		return;
	}
	gObjDeleteItemsCount(aIndex,ITEMGET(14,44),0,Count);
	LPOBJ lpObj = &gObj[aIndex];
	lpObj->HighStoneBank += Count;
	ZtUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Send %d HighStone",Count);
}

void JewelsBank::sendGemStoneBank(int aIndex, int Count)
{
	if(gObjGetItemCountInInventory(aIndex,ITEMGET(14,41),0) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Need %d GemStoneBank",Count);
		return;
	}
	gObjDeleteItemsCount(aIndex,ITEMGET(14,41),0,Count);
	LPOBJ lpObj = &gObj[aIndex];
	lpObj->GemStoneBank += Count;
	ZtUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Send %d GemStoneBank",Count);
}

 // -> Recv

void JewelsBank::recvGuardianBank(int aIndex, int Count)
{
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->GuardianBank < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] No %d Guardian",Count);
		return;
	}
	if(ExCheckInventoryEmptySpace(aIndex) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Inventory %d",Count);
		return;
	}
	lpObj->GuardianBank -= Count;
	for(int i=0;i<Count;i++)
	{
		ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(14,31),0,0,0,0,0,aIndex,0,0);
	}
	ZtUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Recv %d Guardian",Count);
}

void JewelsBank::recvHarmonyBank(int aIndex, int Count)
{
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->HarmonyBank < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] No %d Harmony",Count);
		return;
	}
	if(ExCheckInventoryEmptySpace(aIndex) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Inventory %d",Count);
		return;
	}
	lpObj->HarmonyBank -= Count;
	for(int i=0;i<Count;i++)
	{
		ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(14,42),0,0,0,0,0,aIndex,0,0);
	}
	ZtUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Recv %d Harmony",Count);
}

void JewelsBank::recvLowStoneBank(int aIndex, int Count)
{
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->LowStoneBank < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] No %d LowStone",Count);
		return;
	}
	if(ExCheckInventoryEmptySpace(aIndex) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Inventory %d",Count);
		return;
	}
	lpObj->LowStoneBank -= Count;
	for(int i=0;i<Count;i++)
	{
		ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(14,43),0,0,0,0,0,aIndex,0,0);
	}
	ZtUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Recv %d LowStone",Count);
}

void JewelsBank::recvHighStoneBank(int aIndex, int Count)
{
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->HighStoneBank < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] No %d HighStone",Count);
		return;
	}
	if(ExCheckInventoryEmptySpace(aIndex) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Inventory %d",Count);
		return;
	}
	lpObj->HighStoneBank -= Count;
	for(int i=0;i<Count;i++)
	{
		ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(14,44),0,0,0,0,0,aIndex,0,0);
	}
	ZtUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Recv %d HighStone",Count);
}

void JewelsBank::recvGemStoneBank(int aIndex, int Count)
{
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->GemStoneBank < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] No %d GemStone",Count);
		return;
	}
	if(ExCheckInventoryEmptySpace(aIndex) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Inventory %d",Count);
		return;
	}
	lpObj->GemStoneBank -= Count;
	for(int i=0;i<Count;i++)
	{
		ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(14,41),0,0,0,0,0,aIndex,0,0);
	}
	ZtUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Recv %d GemStone",Count);
}

void JewelsBank::Packet(int aIndex, PMSG_JEWELBANK* lpMsg)
{
	if(!this->Enable)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	switch(lpMsg->Result)
	{
		case 0:		this->sendzen(aIndex, 1);				break;
		case 1:		this->sendchaosbank(aIndex, 1);			break;
		case 2:		this->sendblessbank(aIndex, 1);			break;
		case 3:		this->sendsoulbank(aIndex, 1);			break;
		case 4:		this->sendlifebank(aIndex, 1);			break;
		case 5:		this->sendcreateonbank(aIndex, 1);		break;
		case 6:		this->sendGuardianBank(aIndex, 1);		break;
		case 7:		this->sendHarmonyBank(aIndex, 1);		break;
		case 8:		this->sendLowStoneBank(aIndex, 1);		break;
		case 9:		this->sendHighStoneBank(aIndex, 1);		break;
		case 10:	this->sendGemStoneBank(aIndex, 1);		break;

		case 11:	this->recvzen(aIndex, 1);				break;
		case 12:	this->recvchaosbank(aIndex, 1);			break;
		case 13:	this->recvblessbank(aIndex, 1);			break;
		case 14:	this->recvsoulbank(aIndex, 1);			break;
		case 15:	this->recvlifebank(aIndex, 1);			break;
		case 16:	this->recvcreateonbank(aIndex, 1);		break;
		case 17:	this->recvGuardianBank(aIndex, 1);		break;
		case 18:	this->recvHarmonyBank(aIndex, 1);		break;
		case 19:	this->recvLowStoneBank(aIndex, 1);		break;
		case 20:	this->recvHighStoneBank(aIndex, 1);		break;
		case 21:	this->recvGemStoneBank(aIndex, 1);		break;
	}
}