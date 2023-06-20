#include "StdAfx.h"
#include "user.h"
#include "Message.h"
#include "Reset.h"
#include "Functions.h"
#include "LogProc.h"
#include "Configs.h"
#include "GrandReset.h"
#include "SystemOfRage.h"
#include "MoveCommand.h"
#include "ZtLicense.h"
#include "ZtFunction.h"
#include "ZtUser.h"
#include "ObjCalCharacter.h"
#include "GameMain.h"
#include "BuffManager.h"
#include "Achievements.h"
#include "ZtText.h"

cGrandReset gGrandReset;

void cGrandReset::Load()
{
	//CheckFile(GrandReset_DIR);
	this->EnableGrandResetSystem = GetPrivateProfileInt("GrandReset","Enable",0,GrandReset_DIR);	
	this->MaxGrandRes = GetPrivateProfileInt("GrandReset","Max.GrandRes",100,GrandReset_DIR);
	this->ZenForm = GetPrivateProfileInt("GrandReset","ZenForm",0,GrandReset_DIR);
	this->NeedZen = GetPrivateProfileInt("GrandReset","Need.Zen",0,GrandReset_DIR);
	this->NeedRes = GetPrivateProfileInt("GrandReset","Need.Res",0,GrandReset_DIR);
	this->NeedLevel = GetPrivateProfileInt("GrandReset","Need.Level",0,GrandReset_DIR);
	this->AddForm = GetPrivateProfileInt("GrandReset","Add.Form",0,GrandReset_DIR);
	this->AddPointsDW = GetPrivateProfileInt("GrandReset","Add.PointsDW",0,GrandReset_DIR);
	this->AddPointsDK = GetPrivateProfileInt("GrandReset","Add.PointsDK",0,GrandReset_DIR);
	this->AddPointsELF = GetPrivateProfileInt("GrandReset","Add.PointsELF",0,GrandReset_DIR);
	this->AddPointsSUM = GetPrivateProfileInt("GrandReset","Add.PointsSUM",0,GrandReset_DIR);
	this->AddPointsMG = GetPrivateProfileInt("GrandReset","Add.PointsMG",0,GrandReset_DIR);
	this->AddPointsDL = GetPrivateProfileInt("GrandReset","Add.PointsDL",0,GrandReset_DIR);
	this->AddPointsRF = GetPrivateProfileInt("GrandReset","Add.PointsRF",0,GrandReset_DIR);
	this->NeedEmptyInv = GetPrivateProfileInt("GrandReset","Need.EmptyInv",1,GrandReset_DIR);

	this->AddCredits = GetPrivateProfileInt("GrandReset","AddCredits",0,GrandReset_DIR);
	this->AddWcoinC = GetPrivateProfileInt("GrandReset","AddWcoinC",0,GrandReset_DIR);
	this->AddWcoinP = GetPrivateProfileInt("GrandReset","AddWcoinP",0,GrandReset_DIR);
	this->AddGoblinPoint = GetPrivateProfileInt("GrandReset","AddGoblinPoint",0,GrandReset_DIR);

	 GetPrivateProfileString("GrandReset", "cmd","/grandreset",this->CommandGrandReset,100,GrandReset_DIR);

	 this->m_NpcClass = GetPrivateProfileInt("GrandReset", "NpcClass", 0, GrandReset_DIR);
	 this->m_NpcMap = GetPrivateProfileInt("GrandReset", "NpcMap", 0, GrandReset_DIR);
	 this->m_NpcX = GetPrivateProfileInt("GrandReset", "NpcX", 0, GrandReset_DIR);
	 this->m_NpcY = GetPrivateProfileInt("GrandReset", "NpcY", 0, GrandReset_DIR);

	 this->m_iMapForGrand = GetPrivateProfileInt("GrandReset", "MapForGrand", 0, GrandReset_DIR);

//#ifdef PRIVATE_MODULE
//	if(g_ZtLicense.CheckUser(eZtUB::drynea))
//	{
//		this->AddWcoin = GetPrivateProfileInt("GrandReset","AddWcoin",0,GrandReset_DIR);
//	}
//#endif

	

#if(ADD_GRAND_EXP)
	 this->EnableGrandDinamic = g_ZtLicense.user.GrandDinamicExp;

	this->DataExp.clear();

	FILE * file = fopen(GrandReset_DIR,"r");
	if(file == NULL)
	{
		MessageBoxA(0,GrandReset_DIR,"LOAD FILE ERROR",0);
		ExitProcess(0);
	}
	char Buff[256];
	int Flag = 0;
	while(!feof(file))
	{
		fgets(Buff,256,file);
		if(Zt_IsBadFileLine(Buff, Flag)) continue;
		if(Flag == 1)
		{
			int n[3];
			sscanf(Buff, "%d %d %d", &n[0], &n[1], &n[2]);
			GrandResetEXP list;
			list.GrandReset = n[0];
			list.TypeExp	= n[1];
			list.MinusExp	= n[2];
			this->DataExp.push_back(list);
		}

		//if(g_ZtLicense.CheckUser(eZtUB::Local) || g_ZtLicense.CheckUser(eZtUB::Artem) || g_ZtLicense.CheckUser(eZtUB::Artem2))
		{
			if(Flag == 2)
			{
				GRANDSYSTEM_REWARD_DATA list;
				sscanf(Buff, "%d %d %d %d %d %d %d %d %d %d %d %d",&list.ResetNum,&list.WcoinC,&list.Credit,&list.EnableItem,&list.Type,&list.Index,&list.Level,&list.Skill,&list.Luck,&list.Opt,&list.Exl,&list.Anc);
				this->m_reward.push_back(list);
			}
			#if(ENABLE_GRAND_NEEDITEM)
			if(Flag == 3)
			{
				RESET_NEEDITEM_DATA list;
				sscanf(Buff, "%d %d %d %d %d %d %d %d %d %d", &list.ResetNum,&list.Type,&list.Index,&list.Level,&list.Skill,&list.Luck,&list.Opt,&list.Exl,&list.Anc,&list.Count);
				this->m_needitem.push_back(list);
			}
			#endif
		}
	}
	fclose(file);
#endif
}

void cGrandReset::ExGrandResetSystemFunciton(int aIndex)
{
	if(!this->EnableGrandResetSystem)
		return;

	LPOBJ lpObj = &gObj[aIndex];

	if ( (GetTickCount() - lpObj->MySelfDefenseTime ) < 60000)
	{
		GCServerMsgStringSend(lMsg.Get(MSGGET(4, 109)), lpObj->m_Index, 1);
		GCCloseMsgSend(aIndex,-1); //Season 2.5 add-on
		return;
	}

	if(lpObj->SkillRecallParty_Time != 0)
	{
		return;
	}

	if(lpObj->MapNumber != this->m_iMapForGrand)
	{
		MsgNormal(aIndex,g_ZtText.GetText(12));
		return;
	}

	if(gMoveCommand.CheckInterfaceToMove(lpObj) == 0)
	{
		GCServerMsgStringSend(g_ZtText.GetText(13),lpObj->m_Index,1);
		return;
	}

	//Проверка на максимальное количество ресето?
	if(lpObj->GReset >= this->MaxGrandRes)
	{
		MsgNormal(aIndex,g_ZtText.GetText(14),this->MaxGrandRes);
		return;
	}
	
	//Проверка на Ресе?
	if(this->NeedRes > lpObj->Reset)
	{
		MsgNormal(aIndex,g_ZtText.GetText(15),this->NeedRes);
		return;
	}
	//Проверка на уровен?
	if(this->NeedLevel > lpObj->Level)
	{
		MsgNormal(aIndex,g_ZtText.GetText(16),this->NeedLevel);
		return;
	}
	int ZenMoney = 0;
	//Проверка на зе?
	switch(this->ZenForm)
	{
		case 1: ZenMoney = this->NeedZen * ( lpObj->GReset + 1 ); break;
		case 2: ZenMoney = this->NeedZen; break;
	}
	
	if(this->ZenForm != 0)
	{
		if(lpObj->Money < ZenMoney)
		{
			MsgNormal(aIndex,g_ZtText.GetText(17),ZenMoney);
			return;
		}
	}
	//Проверка на пустой инвентар?
	if(this->NeedEmptyInv)
	{
		if(lpObj->pInventory[0].m_Type != -1 || lpObj->pInventory[1].m_Type != -1 || lpObj->pInventory[2].m_Type != -1 ||
		   lpObj->pInventory[3].m_Type != -1 || lpObj->pInventory[4].m_Type != -1 || lpObj->pInventory[5].m_Type != -1 ||
		   lpObj->pInventory[6].m_Type != -1 || lpObj->pInventory[7].m_Type != -1 || lpObj->pInventory[8].m_Type != -1 ||
		   lpObj->pInventory[9].m_Type != -1 || lpObj->pInventory[10].m_Type != -1|| lpObj->pInventory[11].m_Type != -1)
		{
			MsgNormal(aIndex,g_ZtText.GetText(18));
			return;
		}
	}
	/////////////////////
	//Выполнение Гран?ресета//
	/////////////////////
	lpObj->Money -= ZenMoney;
	lpObj->Level = 1;
	lpObj->Experience = 0;
	lpObj->NextExp = 100;
	if(this->AddForm == 2 || this->AddForm == 3)
	{
		lpObj->Strength = 25;
		lpObj->Dexterity = 25;
		lpObj->Vitality = 25;
		lpObj->Energy = 25;
		if(lpObj->Class == 4)
		{
			lpObj->Leadership = 25;
		}
	}
	//Поинта за гран?ресе?
	if(this->AddForm == 1 || this->AddForm == 2)
	{
		switch (lpObj->Class)
		{
			case 0: lpObj->LevelUpPoint = ( lpObj->GReset + 1 ) * this->AddPointsDW ;  break;
			case 1: lpObj->LevelUpPoint = ( lpObj->GReset + 1 ) * this->AddPointsDK ;  break;
			case 2: lpObj->LevelUpPoint = ( lpObj->GReset + 1 ) * this->AddPointsELF ; break;
			case 3: lpObj->LevelUpPoint = ( lpObj->GReset + 1 ) * this->AddPointsMG ;  break;
			case 4: lpObj->LevelUpPoint = ( lpObj->GReset + 1 ) * this->AddPointsDL ;  break;
			case 5: lpObj->LevelUpPoint = ( lpObj->GReset + 1 ) * this->AddPointsSUM ; break;
			case 6: lpObj->LevelUpPoint = ( lpObj->GReset + 1 ) * this->AddPointsRF ; break;
		}
	}
	if(this->AddForm == 3)
	{
		lpObj->LevelUpPoint = 0;
	}
	else
	{
		lpObj->LevelUpPoint += lpObj->ZtFreePoints;
	}
	
	lpObj->Reset = 0;
	lpObj->GReset += 1;

	if(this->AddCredits > 0)
	{
		if(g_ZtLicense.CheckUser(eZtUB::NSGames))
		{
			lpObj->PCPoint += this->AddCredits;	
		}
		else
		{
			lpObj->ZtCred += this->AddCredits;		
		}
		ZtUserDataSend(aIndex);
	}
	if(this->AddWcoinC > 0)
	{
		lpObj->GameShop.WCoinC += this->AddWcoinC;
	}
	if(this->AddWcoinP > 0)
	{
		lpObj->GameShop.WCoinP += this->AddWcoinP;
	}
	if(this->AddGoblinPoint > 0)
	{
		lpObj->GameShop.GoblinPoint += this->AddGoblinPoint;
	}

	if(this->AddWcoinC > 0 || this->AddWcoinP > 0 || this->AddGoblinPoint > 0)
	{
		gGameShop.GDSaveUserInfo(aIndex);
	}	

	ZtFireCracker(aIndex, lpObj->X, lpObj->Y);
	//gObjCloseSet(aIndex, 1);

	lpObj->Life = DCInfo.DefClass[lpObj->Class].Life + (lpObj->Level + lpObj->MLevel - 1) * DCInfo.DefClass[lpObj->Class].LevelLife  + ((lpObj->Vitality - DCInfo.DefClass[lpObj->Class].Vitality ) * DCInfo.DefClass[lpObj->Class].VitalityToLife);
	lpObj->Mana = DCInfo.DefClass[lpObj->Class].Mana + (lpObj->Level + lpObj->MLevel - 1) * DCInfo.DefClass[lpObj->Class].LevelMana  + ((lpObj->Energy - DCInfo.DefClass[lpObj->Class].Energy ) * DCInfo.DefClass[lpObj->Class].EnergyToMana);

	lpObj->MaxLife = DCInfo.DefClass[lpObj->Class].Life + (lpObj->Level + lpObj->MLevel - 1) * DCInfo.DefClass[lpObj->Class].LevelLife  + ((lpObj->Vitality - DCInfo.DefClass[lpObj->Class].Vitality ) * DCInfo.DefClass[lpObj->Class].VitalityToLife);
	lpObj->MaxMana = DCInfo.DefClass[lpObj->Class].Mana + (lpObj->Level + lpObj->MLevel - 1) * DCInfo.DefClass[lpObj->Class].LevelMana  + ((lpObj->Energy - DCInfo.DefClass[lpObj->Class].Energy ) * DCInfo.DefClass[lpObj->Class].EnergyToMana);

	lpObj->VitalityToLife = DCInfo.DefClass[lpObj->Class].VitalityToLife;
	lpObj->EnergyToMana = DCInfo.DefClass[lpObj->Class].EnergyToMana;

	::gObjSetBP(aIndex);
	lpObj->BP = lpObj->MaxBP / 2;
	::gObjCalcMaxLifePower(aIndex);

	GCReFillSend(aIndex, (int)lpObj->MaxLife + lpObj->AddLife, 0xFE, 0, lpObj->iMaxShield + lpObj->iAddShield);
	//gObjSetBP(aIndex);
	GCManaSend(aIndex,(int)lpObj->MaxMana + lpObj->AddMana, 0xFE, 0, lpObj->MaxBP + lpObj->AddBP);
	gObjCalCharacter(aIndex);

	ResetSystemGC_CharUpdate(lpObj);

	GCMoneySend(aIndex, lpObj->Money);

#if(CUSTOM_NOOBBUFF)
	if(ZtConfig.CommonServer.bNoobBuffEnable)
	{
		if(gObjSearchActiveEffect(lpObj,AT_NOOB_BUFF) == TRUE)
		{
			gObjRemoveBuffEffect(lpObj,AT_NOOB_BUFF);
		}
	}
#endif

#if(SYSTEM_ACHIEVEMENTS)
	g_Achievements.GrandResetUp(aIndex);
#endif

	LogAddTD("[GrandResetSystem] Accaunt: %s , Name: %s , GrandReset: %d",lpObj->AccountID, lpObj->Name,lpObj->GReset);
}

#if(ADD_GRAND_EXP)
int cGrandReset::DinamicExp(int aIndex, int Experience)
{
	int Result = Experience;

	if(!this->EnableGrandResetSystem)
	{
		return Result;
	}

	if(!this->EnableGrandDinamic)
	{
		return Result;
	}

	if(OBJMAX_RANGE(aIndex) == 0)
	{
		return Result;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return Result;
	}

	for(int i = 0; i < this->DataExp.size(); i++)
	{
		GrandResetEXP list = this->DataExp[i];

		if(lpUser->GReset == list.GrandReset)
		{
			if(list.TypeExp == false)
			{
				Result = Experience - list.MinusExp;

				if(Result < 1)
				{
					Result = 1;
				}
			}
			else
			{
				Result = list.MinusExp;
			}

			break;
		}
	}

	return Result;
}
#endif

void cGrandReset::CGGrandMenu(int aIndex)
{
	if( !g_ZtLicense.CheckUser(eZtUB::Local) && 
		!g_ZtLicense.CheckUser(eZtUB::Gredy) &&
		!g_ZtLicense.CheckUser(eZtUB::Gredy2) && 
		!g_ZtLicense.CheckUser(eZtUB::GredyLocal)&&
		!g_ZtLicense.CheckUser(eZtUB::GloryMU) &&
		!g_ZtLicense.CheckUser(eZtUB::MedoniAndrei) &&
		!g_ZtLicense.CheckUser(eZtUB::mu4you) && 
		!g_ZtLicense.CheckUser(eZtUB::Escalate) &&
		!g_ZtLicense.CheckUser(eZtUB::eternalmu) &&
		!g_ZtLicense.CheckUser(eZtUB::NSGames) &&
		!g_ZtLicense.CheckUser(eZtUB::MUCustom) &&
		!g_ZtLicense.CheckUser(eZtUB::AsteraMU))
	{
		return;
	}

	this->GCDialogInfo(aIndex);
}

void cGrandReset::GCDialogInfo(int aIndex)
{
	PMSG_GRAND_DIALOG pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xA1, sizeof(pMsg));
	pMsg.Result = 1;

	if(!this->EnableGrandResetSystem)
		return;

	LPOBJ lpObj = &gObj[aIndex];

	if ( (GetTickCount() - lpObj->MySelfDefenseTime ) < 60000)
	{
		GCServerMsgStringSend(lMsg.Get(MSGGET(4, 109)), lpObj->m_Index, 1);
		GCCloseMsgSend(aIndex,-1); //Season 2.5 add-on
		return;
	}

	if(lpObj->SkillRecallParty_Time != 0)
	{
		return;
	}

	if(gMoveCommand.CheckInterfaceToMove(lpObj) == 0)
	{
		GCServerMsgStringSend("[GReset]: Interface Disable",lpObj->m_Index,1);
		return;
	}

	//Проверка на максимальное количество ресето?
	pMsg.GrandNum = lpObj->GReset;
	pMsg.GrandMax = this->MaxGrandRes;

	if(lpObj->GReset >= this->MaxGrandRes)
	{
		//MsgNormal(aIndex,"[GReset]: Max Grand Reset %d",this->MaxGrandRes);
		pMsg.Result = 0;
	}
	
	//Проверка на Ресе?
	pMsg.NeedReset = this->NeedRes;

	if(this->NeedRes > lpObj->Reset)
	{
		//MsgNormal(aIndex,"[GReset]: You need above %d Reset to GReset",this->NeedLevel);
		pMsg.Result = 0;
	}

	//Проверка на уровен?
	pMsg.NeedLevel = this->NeedLevel;

	if(this->NeedLevel > lpObj->Level)
	{
		//MsgNormal(aIndex,"[GReset]: You need above %d Level to GReset",this->NeedLevel);
		pMsg.Result = 0;
	}
	int ZenMoney = 0;

	//Проверка на зе?
	switch(this->ZenForm)
	{
		case 1: ZenMoney = this->NeedZen * ( lpObj->GReset + 1 ); break;
		case 2: ZenMoney = this->NeedZen; break;
	}
	
	pMsg.NeedMoney = ZenMoney;

	if(this->ZenForm != 0)
	{
		if(lpObj->Money < ZenMoney)
		{
			//MsgNormal(aIndex,"[GReset]: You need above %d Zen to GReset",ZenMoney);
			pMsg.Result = 0;
		}
	}

	//Проверка на пустой инвентар?
	if(this->NeedEmptyInv)
	{
		if(lpObj->pInventory[0].m_Type != -1 || lpObj->pInventory[1].m_Type != -1 || lpObj->pInventory[2].m_Type != -1 ||
		   lpObj->pInventory[3].m_Type != -1 || lpObj->pInventory[4].m_Type != -1 || lpObj->pInventory[5].m_Type != -1 ||
		   lpObj->pInventory[6].m_Type != -1 || lpObj->pInventory[7].m_Type != -1 || lpObj->pInventory[8].m_Type != -1 ||
		   lpObj->pInventory[9].m_Type != -1 || lpObj->pInventory[10].m_Type != -1|| lpObj->pInventory[11].m_Type != -1)
		{
			MsgNormal(aIndex,"[GReset]: You need Empty Inventory to GReset");
			pMsg.Result = 0;
			return;
		}
	}

	//Поинта за гран?ресе?
	pMsg.RewardPoint = 0;

	if(this->AddForm == 1 || this->AddForm == 2)
	{
		switch (lpObj->Class)
		{
		case 0: pMsg.RewardPoint = ( lpObj->GReset + 1 ) * this->AddPointsDW;  break;
		case 1: pMsg.RewardPoint = ( lpObj->GReset + 1 ) * this->AddPointsDK;  break;
		case 2: pMsg.RewardPoint = ( lpObj->GReset + 1 ) * this->AddPointsELF; break;
		case 3: pMsg.RewardPoint = ( lpObj->GReset + 1 ) * this->AddPointsMG;  break;
		case 4: pMsg.RewardPoint = ( lpObj->GReset + 1 ) * this->AddPointsDL;  break;
		case 5: pMsg.RewardPoint = ( lpObj->GReset + 1 ) * this->AddPointsSUM; break;
		case 6: pMsg.RewardPoint = ( lpObj->GReset + 1 ) * this->AddPointsRF;  break;
		}
	}

	//if(this->AddForm == 3)
	//{
	//	lpObj->LevelUpPoint = 0;
	//}
	//else
	//{
	//	lpObj->LevelUpPoint += lpObj->ZtFreePoints;
	//}

	//if(this->AddCredits>0)
	//{
	//	lpObj->ZtCred += AddCredits;
	//}

	pMsg.RewardWCoin = this->AddWcoinC;

	//if(this->AddWcoinC > 0)
	//{
	//	lpObj->GameShop.WCoinC += this->AddWcoinC;
	//}
	//if(this->AddWcoinP > 0)
	//{
	//	lpObj->GameShop.WCoinP += this->AddWcoinP;
	//}
	//if(this->AddGoblinPoint > 0)
	//{
	//	lpObj->GameShop.GoblinPoint += this->AddGoblinPoint;
	//}
	#if(ENABLE_GRAND_CREDIT)
	if(this->AddCredits>0)
	{
		pMsg.RewardCredit = this->AddCredits;
	}
	#endif

	#if(ENABLE_GRAND_NEEDITEM)
	// Need Item
	pMsg.AddEnableItem = false;
	pMsg.AddItem = -1;
	pMsg.AddItemLevel = 0;
	pMsg.AddItemSkill = 0;
	pMsg.AddItemLuck = 0;
	pMsg.AddItemOpt = 0;
	pMsg.AddItemExl = 0;
	pMsg.AddItemAnc = 0;
	pMsg.AddItemCount = 0;

	for(int i = 0; i < this->m_needitem.size(); i++)
	{
		RESET_NEEDITEM_DATA & nitem = this->m_needitem[i];
		if(nitem.ResetNum == (lpObj->GReset + 1))
		{
			pMsg.AddEnableItem = true;
			pMsg.AddItem = ITEMGET(nitem.Type, nitem.Index);
			pMsg.AddItemLevel = nitem.Level;
			pMsg.AddItemSkill = nitem.Skill;
			pMsg.AddItemLuck = nitem.Luck;
			pMsg.AddItemOpt = nitem.Opt;
			pMsg.AddItemExl = nitem.Exl;
			pMsg.AddItemAnc = nitem.Anc;
			pMsg.AddItemCount = nitem.Count;

			if(!this->SearchItem(aIndex, nitem.Type, nitem.Index, nitem.Level, nitem.Skill, nitem.Luck, nitem.Opt, nitem.Exl, nitem.Anc, nitem.Count, false))
			{
				pMsg.Result = false;
			}

			break;
		}
	}
	#endif

	if(g_ZtLicense.CheckUser(eZtUB::Local) || g_ZtLicense.CheckUser(eZtUB::Artem) || g_ZtLicense.CheckUser(eZtUB::Artem2))
	{
		//reward Item
		for(int i = 0; i < this->m_reward.size(); i++)
		{
			GRANDSYSTEM_REWARD_DATA & ritem = this->m_reward[i];
			if(ritem.ResetNum == (lpObj->GReset + 1))
			{
				if(ritem.WcoinC > 0)
				{
					pMsg.RewardWCoin = ritem.WcoinC;
				}
				if(ritem.Credit > 0)
				{
					pMsg.RewardCredit = ritem.Credit;
				}
			}
		}
	}

	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}

void cGrandReset::CGGrandStart(int aIndex)
{
	if(!this->EnableGrandResetSystem)
		return;

	LPOBJ lpObj = &gObj[aIndex];

	if ( (GetTickCount() - lpObj->MySelfDefenseTime ) < 60000)
	{
		GCServerMsgStringSend(lMsg.Get(MSGGET(4, 109)), lpObj->m_Index, 1);
		GCCloseMsgSend(aIndex,-1); //Season 2.5 add-on
		return;
	}

	if(lpObj->SkillRecallParty_Time != 0)
	{
		return;
	}

	if(gMoveCommand.CheckInterfaceToMove(lpObj) == 0)
	{
		GCServerMsgStringSend("[GReset]: Interface Disable",lpObj->m_Index,1);
		return;
	}

	//Проверка на максимальное количество ресето?
	if(lpObj->GReset >= this->MaxGrandRes)
	{
		MsgNormal(aIndex,"[GReset]: Max Grand Reset %d",this->MaxGrandRes);
		return;
	}
	
	//Проверка на Ресе?
	if(this->NeedRes > lpObj->Reset)
	{
		MsgNormal(aIndex,"[GReset]: You need above %d Reset to GReset",this->NeedRes);
		return;
	}
	//Проверка на уровен?
	if(this->NeedLevel > lpObj->Level)
	{
		MsgNormal(aIndex,"[GReset]: You need above %d Level to GReset",this->NeedLevel);
		return;
	}
	int ZenMoney = 0;
	//Проверка на зе?
	switch(this->ZenForm)
	{
		case 1: ZenMoney = this->NeedZen * ( lpObj->GReset + 1 ); break;
		case 2: ZenMoney = this->NeedZen; break;
	}
	
	if(this->ZenForm != 0)
	{
		if(lpObj->Money < ZenMoney)
		{
			MsgNormal(aIndex,"[GReset]: You need above %d Zen to GReset",ZenMoney);
			return;
		}
	}
	//Проверка на пустой инвентар?
	if(this->NeedEmptyInv)
	{
		if(lpObj->pInventory[0].m_Type != -1 || lpObj->pInventory[1].m_Type != -1 || lpObj->pInventory[2].m_Type != -1 ||
		   lpObj->pInventory[3].m_Type != -1 || lpObj->pInventory[4].m_Type != -1 || lpObj->pInventory[5].m_Type != -1 ||
		   lpObj->pInventory[6].m_Type != -1 || lpObj->pInventory[7].m_Type != -1 || lpObj->pInventory[8].m_Type != -1 ||
		   lpObj->pInventory[9].m_Type != -1 || lpObj->pInventory[10].m_Type != -1|| lpObj->pInventory[11].m_Type != -1)
		{
			MsgNormal(aIndex,"[GReset]: You need Empty Inventory to GReset");
			return;
		}
	}

	#if(ENABLE_GRAND_NEEDITEM)
	// Need Item
	for(int i = 0; i < this->m_needitem.size(); i++)
	{
		RESET_NEEDITEM_DATA & nitem = this->m_needitem[i];
		if(nitem.ResetNum == (lpObj->GReset + 1))
		{
			if(!this->SearchItem(aIndex, nitem.Type, nitem.Index, nitem.Level, nitem.Skill, nitem.Luck, nitem.Opt, nitem.Exl, nitem.Anc, nitem.Count, true))
			{
				MsgNormal(aIndex,"[GReset]: Need Grand Reset Items");
				return;
			}
			break;
		}
	}
	#endif

	/////////////////////
	//Выполнение Гран?ресета//
	/////////////////////
	lpObj->Money -= ZenMoney;
	lpObj->Level = 1;
	lpObj->Experience = 0;
	lpObj->NextExp = 100;
	if(this->AddForm == 2 || this->AddForm == 3)
	{
		lpObj->Strength = 25;
		lpObj->Dexterity = 25;
		lpObj->Vitality = 25;
		lpObj->Energy = 25;
		if(lpObj->Class == 4)
		{
			lpObj->Leadership = 25;
		}
	}
	//Поинта за гран?ресе?
	if(this->AddForm == 1 || this->AddForm == 2)
	{
		switch (lpObj->Class)
		{
			case 0: lpObj->LevelUpPoint = ( lpObj->GReset + 1 ) * this->AddPointsDW ;  break;
			case 1: lpObj->LevelUpPoint = ( lpObj->GReset + 1 ) * this->AddPointsDK ;  break;
			case 2: lpObj->LevelUpPoint = ( lpObj->GReset + 1 ) * this->AddPointsELF ; break;
			case 3: lpObj->LevelUpPoint = ( lpObj->GReset + 1 ) * this->AddPointsMG ;  break;
			case 4: lpObj->LevelUpPoint = ( lpObj->GReset + 1 ) * this->AddPointsDL ;  break;
			case 5: lpObj->LevelUpPoint = ( lpObj->GReset + 1 ) * this->AddPointsSUM ; break;
			case 6: lpObj->LevelUpPoint = ( lpObj->GReset + 1 ) * this->AddPointsRF ; break;
		}
	}
	if(this->AddForm == 3)
	{
		lpObj->LevelUpPoint = 0;
	}
	else
	{
		lpObj->LevelUpPoint += lpObj->ZtFreePoints;
	}
	
	lpObj->Reset = 0;
	lpObj->GReset += 1;

	if(this->AddCredits > 0)
	{
		if(g_ZtLicense.CheckUser(eZtUB::NSGames))
		{
			lpObj->PCPoint += this->AddCredits;	
		}
		else
		{
			lpObj->ZtCred += this->AddCredits;		
		}
	}

	if(this->AddWcoinC > 0)
	{
		lpObj->GameShop.WCoinC += this->AddWcoinC;
	}
	if(this->AddWcoinP > 0)
	{
		lpObj->GameShop.WCoinP += this->AddWcoinP;
	}
	if(this->AddGoblinPoint > 0)
	{
		lpObj->GameShop.GoblinPoint += this->AddGoblinPoint;
	}

	if(this->AddWcoinC > 0 || this->AddWcoinP > 0 || this->AddGoblinPoint > 0)
	{
		gGameShop.GDSaveUserInfo(aIndex);
	}	

	if(g_ZtLicense.CheckUser(eZtUB::Local) || g_ZtLicense.CheckUser(eZtUB::Artem) || g_ZtLicense.CheckUser(eZtUB::Artem2))
	{
		//reward Item
		for(int i = 0; i < this->m_reward.size(); i++)
		{
			GRANDSYSTEM_REWARD_DATA & ritem = this->m_reward[i];
			if(ritem.ResetNum == (lpObj->GReset + 1))
			{
				if(ritem.WcoinC > 0)
				{
					lpObj->GameShop.WCoinC += ritem.WcoinC;
					gGameShop.GDSaveUserInfo(lpObj->m_Index);
				}
				if(ritem.Credit > 0)
				{
					lpObj->ZtCred += ritem.Credit;
					ZtUserDataSend(aIndex);
				}
				if(ritem.EnableItem)
				{
					ItemSerialCreateSend(aIndex,lpObj->MapNumber,lpObj->X,lpObj->Y,ITEMGET(ritem.Type, ritem.Index),ritem.Level,0,ritem.Skill,ritem.Luck,ritem.Opt,aIndex,ritem.Exl,ritem.Anc);
				}
				break;
			}
		}
	}


	ZtFireCracker(aIndex, lpObj->X, lpObj->Y);
	//gObjCloseSet(aIndex, 1);

	lpObj->Life = DCInfo.DefClass[lpObj->Class].Life + (lpObj->Level + lpObj->MLevel - 1) * DCInfo.DefClass[lpObj->Class].LevelLife  + ((lpObj->Vitality - DCInfo.DefClass[lpObj->Class].Vitality ) * DCInfo.DefClass[lpObj->Class].VitalityToLife);
	lpObj->Mana = DCInfo.DefClass[lpObj->Class].Mana + (lpObj->Level + lpObj->MLevel - 1) * DCInfo.DefClass[lpObj->Class].LevelMana  + ((lpObj->Energy - DCInfo.DefClass[lpObj->Class].Energy ) * DCInfo.DefClass[lpObj->Class].EnergyToMana);

	lpObj->MaxLife = DCInfo.DefClass[lpObj->Class].Life + (lpObj->Level + lpObj->MLevel - 1) * DCInfo.DefClass[lpObj->Class].LevelLife  + ((lpObj->Vitality - DCInfo.DefClass[lpObj->Class].Vitality ) * DCInfo.DefClass[lpObj->Class].VitalityToLife);
	lpObj->MaxMana = DCInfo.DefClass[lpObj->Class].Mana + (lpObj->Level + lpObj->MLevel - 1) * DCInfo.DefClass[lpObj->Class].LevelMana  + ((lpObj->Energy - DCInfo.DefClass[lpObj->Class].Energy ) * DCInfo.DefClass[lpObj->Class].EnergyToMana);

	lpObj->VitalityToLife = DCInfo.DefClass[lpObj->Class].VitalityToLife;
	lpObj->EnergyToMana = DCInfo.DefClass[lpObj->Class].EnergyToMana;

	::gObjSetBP(aIndex);
	lpObj->BP = lpObj->MaxBP / 2;
	::gObjCalcMaxLifePower(aIndex);

	GCReFillSend(aIndex, (int)lpObj->MaxLife + lpObj->AddLife, 0xFE, 0, lpObj->iMaxShield + lpObj->iAddShield);
	//gObjSetBP(aIndex);
	GCManaSend(aIndex,(int)lpObj->MaxMana + lpObj->AddMana, 0xFE, 0, lpObj->MaxBP + lpObj->AddBP);
	gObjCalCharacter(aIndex);

	ResetSystemGC_CharUpdate(lpObj);

	GCMoneySend(aIndex, lpObj->Money);

#if(CUSTOM_NOOBBUFF)
	if(ZtConfig.CommonServer.bNoobBuffEnable)
	{
		if(gObjSearchActiveEffect(lpObj,AT_NOOB_BUFF) == TRUE)
		{
			gObjRemoveBuffEffect(lpObj,AT_NOOB_BUFF);
		}
	}
#endif

#if(SYSTEM_ACHIEVEMENTS)
	g_Achievements.GrandResetUp(aIndex);
#endif

	LogAddTD("[GrandResetSystem] Accaunt: %s , Name: %s , GrandReset: %d",lpObj->AccountID, lpObj->Name,lpObj->GReset);
}

bool cGrandReset::NpcDialog(int aIndex, int aNpcIndex)
{
	if( !g_ZtLicense.CheckUser(eZtUB::Local) && 
		!g_ZtLicense.CheckUser(eZtUB::EpicMU) && 
		!g_ZtLicense.CheckUser(eZtUB::RevoMU) &&
		!g_ZtLicense.CheckUser(eZtUB::GloryMU) &&
		!g_ZtLicense.CheckUser(eZtUB::MedoniAndrei) &&
		!g_ZtLicense.CheckUser(eZtUB::Artem) && 
		!g_ZtLicense.CheckUser(eZtUB::Artem2) &&
		!g_ZtLicense.CheckUser(eZtUB::mu4you) &&
		!g_ZtLicense.CheckUser(eZtUB::Escalate) &&
		!g_ZtLicense.CheckUser(eZtUB::eternalmu) &&
		!g_ZtLicense.CheckUser(eZtUB::NSGames) &&
		!g_ZtLicense.CheckUser(eZtUB::MUCustom) &&
		!g_ZtLicense.CheckUser(eZtUB::AsteraMU))
	{
		if(!g_ZtLicense.GetCustom())
		{
			return false;
		}
	}

	if(!OBJMAX_RANGE(aIndex) && !OBJMAX_RANGE(aNpcIndex))
	{
		return false;
	}

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpNpc = &gObj[aNpcIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return false;
	}

	if( lpNpc->Class		== this->m_NpcClass  &&
		lpNpc->MapNumber	== this->m_NpcMap &&
		lpNpc->X			== this->m_NpcX   &&
	    lpNpc->Y			== this->m_NpcY )
	{
		this->GCDialogInfo(aIndex);
		return true;
	}

	return false;
}


bool cGrandReset::SearchItem(int aIndex, int Type, int Index, int Level, bool Skill, bool Luck, bool Opt, bool Exl, bool Anc, int count, bool del)
{
	LPOBJ lpUser = &gObj[aIndex];
	int iCount = 0;
	short iType = ITEMGET(Type, Index);

	for (int i = INVETORY_WEAR_SIZE; i < INVENTORY_SIZE; i++)
	{
		if( lpUser->pInventory[i].m_Type == iType && 
			lpUser->pInventory[i].m_Level >= Level &&
			CheckOptionItem(lpUser->pInventory[i].m_Option1, Skill, FALSE) &&
			CheckOptionItem(lpUser->pInventory[i].m_Option2, Luck, FALSE) &&
			CheckOptionItem(lpUser->pInventory[i].m_Option3, Opt, FALSE) &&
			CheckOptionItem(lpUser->pInventory[i].m_NewOption, Exl, FALSE) &&
			CheckOptionItem(lpUser->pInventory[i].m_SetOption, Anc, FALSE) )
		{
			iCount++;
		}
	}

	if(iCount >= count)
	{
		if(del)
		{
			int iDelCount = 0;
			for(int i = INVETORY_WEAR_SIZE; i < INVENTORY_SIZE; i++)
			{
				if( lpUser->pInventory[i].m_Type == iType && 
					lpUser->pInventory[i].m_Level >= Level &&
					CheckOptionItem(lpUser->pInventory[i].m_Option1, Skill, FALSE) &&
					CheckOptionItem(lpUser->pInventory[i].m_Option2, Luck, FALSE) &&
					CheckOptionItem(lpUser->pInventory[i].m_Option3, Opt, FALSE) &&
					CheckOptionItem(lpUser->pInventory[i].m_NewOption, Exl, FALSE) &&
					CheckOptionItem(lpUser->pInventory[i].m_SetOption, Anc, FALSE) )
				{
					gObjInventoryDeleteItem(aIndex, i);
					GCInventoryItemDeleteSend(aIndex, i, 1);
					iDelCount++;
					if(iDelCount == count)
					{
						return true;
					}
				}
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}