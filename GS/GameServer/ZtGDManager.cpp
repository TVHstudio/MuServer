#include "StdAfx.h"
#include "user.h"
#include "ZtGDManager.h"
#include "PartySearch.h"
#include "DBSockMng.h"
#include "BufferSystem.h"
#include "ZtLicense.h"
#include "MonsterQuest.h"
#include "SystemOfRage.h"
#include "ObjCalCharacter.h"
#include "ZtUser.h"
#include "OfflineMode.h"
#include "Achievements.h"
#include "BuffManager.h"
#include "ZtWinQuestSystem.h"

CZtGDManager g_ZtGDManager;

CZtGDManager::CZtGDManager()
{
}

CZtGDManager::~CZtGDManager()
{
}

void CZtGDManager::Protocol(BYTE protoNum, BYTE *aRecv)
{
	switch(protoNum)
	{
	case 0x00:
		this->DG_PartySearchLoad((PMSG_ANS_PARTYSEARCH_LOAD *)aRecv);
		break;
	case 0x02:
		this->DG_ZtBuffLoad((PMSG_ANS_ZTBUFF_LOAD *)aRecv);
		break;
	case 0x04:
		this->DG_BMQuestLoad((PMSG_ANS_BMQUEST_LOAD *)aRecv);
		break;
	case 0x06:
		this->DG_MonsterQuestLoad((PMSG_ANS_MONSTERQUEST_LOAD *)aRecv);
		break;
	case 0x08:
		this->DG_RageSystemLoad((PMSG_ANS_RAGESYSTEM_LOAD *)aRecv);
		break;
	case 0x0A:
		this->DG_CreateonBankLoad((PMSG_ANS_CREATEON_LOAD *)aRecv);
		break;
	case 0x0C:
#if(SYSTEM_ACHIEVEMENTS)
		g_Achievements.DGPlayerLoad((PMSG_DGANS_ACH_LOAD*)aRecv);
#endif
		break;
	case 0x0D:
		this->DG_VoteBuffLoad((PMSG_ANS_VOTEBUFF_LOAD *)aRecv);
		break;
#if(CUSTOM_ZT_QUEST_SYSTEM==TRUE)
	case 0x13:
		this->DG_ZtQuestSystemLoad((PMSG_ANS_ZtQuestSystem_LOAD *)aRecv);
		break;
#endif
	}
}
// -------------------------------------------------------------------------------

void CZtGDManager::DB_Start()
{
	//PMSG_REQ_SERVERINFO_ZT pMsg;
	//pMsg.h.set((LPBYTE)&pMsg, 0xEA, 0x08, sizeof(pMsg));
	//cDBSMng.Send((char*)&pMsg, pMsg.h.size);
	
	if(g_ZtLicense.user.RestoreOffMode)
	{
		g_OfflineMode.GDReqAllPlayer();
	}
}
// -------------------------------------------------------------------------------

void CZtGDManager::DB_Load(int aIndex)
{
	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	if(g_ZtLicense.user.PartySearch)
	{
		this->GD_PartySearchLoad(aIndex);
	}

	if(g_ZtLicense.user.NpcBuffer)
	{
		this->GD_ZtBuffLoad(aIndex);
	}

	if(g_ZtLicense.user.BMQuest)
	{
		this->GD_BMQuestLoad(aIndex);
	}

	if(g_ZtLicense.user.MonsterQuest)
	{
		this->GD_MonsterQuestLoad(aIndex);
	}

	if(g_ZtLicense.user.Rage)
	{
		this->GD_RageSystemLoad(aIndex);
	}

#if(ADD_JEWELBANK_CREATEON)
	if(/*g_ZtLicense.CheckUser(eZtUB::Local) || */g_ZtLicense.CheckUser(SILVER1) || g_ZtLicense.CheckUser(SILVER2) ||
		g_ZtLicense.CheckUser(eZtUB::Gredy) || g_ZtLicense.CheckUser(eZtUB::GredyLocal) || g_ZtLicense.CheckUser(eZtUB::Gredy2) ||
		g_ZtLicense.CheckUser(eZtUB::mu4you) || g_ZtLicense.CheckUser(eZtUB::Escalate) || g_ZtLicense.CheckUser(eZtUB::MedoniAndrei) ||
	    g_ZtLicense.CheckUser(eZtUB::Escalate) || g_ZtLicense.CheckUser(eZtUB::Artem) || g_ZtLicense.CheckUser(eZtUB::Artem2) ||
		g_ZtLicense.CheckUser(eZtUB::eternalmu) || g_ZtLicense.CheckUser(eZtUB::NSGames) || g_ZtLicense.GetCustom())
	{
		this->GD_CreateonBankLoad(aIndex);
	}
#endif
#if(SYSTEM_ACHIEVEMENTS)
	if(g_ZtLicense.user.bAchievements)
	{
		g_Achievements.GDPlayerLoad(aIndex);
	}
#endif

	if(g_ZtLicense.CheckUser(eZtUB::Gredy) || g_ZtLicense.CheckUser(eZtUB::GredyLocal) || g_ZtLicense.CheckUser(eZtUB::Gredy2))
	{
		this->GD_VoteBuffLoad(aIndex);
	}

#if(CUSTOM_ZT_QUEST_SYSTEM==TRUE)
	this->GD_ZtQuestSystemLoad(aIndex);
#endif
}

void CZtGDManager::DB_Save(int aIndex)
{
	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	if(g_ZtLicense.user.PartySearch)
	{
		this->GD_PartySearchSave(aIndex);
	}

	if(g_ZtLicense.user.NpcBuffer)
	{
		this->GD_ZtBuffSave(aIndex);
	}

	if(g_ZtLicense.user.BMQuest)
	{
		this->GD_BMQuestSave(aIndex);
	}

	if(g_ZtLicense.user.MonsterQuest)
	{
		this->GD_MonsterQuestSave(aIndex);
	}

	if(g_ZtLicense.user.Rage)
	{
		this->GD_RageSystemSave(aIndex);
	}

#if(ADD_JEWELBANK_CREATEON)
	if(/*g_ZtLicense.CheckUser(eZtUB::Local) || */g_ZtLicense.CheckUser(SILVER1) || g_ZtLicense.CheckUser(SILVER2) ||
		g_ZtLicense.CheckUser(eZtUB::Gredy) || g_ZtLicense.CheckUser(eZtUB::GredyLocal) || g_ZtLicense.CheckUser(eZtUB::Gredy2) ||
		g_ZtLicense.CheckUser(eZtUB::mu4you) || g_ZtLicense.CheckUser(eZtUB::Escalate) || g_ZtLicense.CheckUser(eZtUB::MedoniAndrei) ||
	    g_ZtLicense.CheckUser(eZtUB::Escalate) || g_ZtLicense.CheckUser(eZtUB::Artem) || g_ZtLicense.CheckUser(eZtUB::Artem2) ||
		g_ZtLicense.CheckUser(eZtUB::eternalmu) || g_ZtLicense.CheckUser(eZtUB::NSGames))
	{
		this->GD_CreateonBankSave(aIndex);
	}
#endif

#if(SYSTEM_ACHIEVEMENTS)
	if(g_ZtLicense.user.bAchievements)
	{
		g_Achievements.GDPlayerSave(aIndex);
	}
#endif

	if(g_ZtLicense.CheckUser(eZtUB::Gredy) || g_ZtLicense.CheckUser(eZtUB::GredyLocal) || g_ZtLicense.CheckUser(eZtUB::Gredy2))
	{
		this->GD_VoteBuffSave(aIndex);
	}

#if(CUSTOM_ZT_QUEST_SYSTEM==TRUE)
	this->GD_ZtQuestSystemSave(aIndex);
#endif
}
// -------------------------------------------------------------------------------

void CZtGDManager::GD_PartySearchLoad(int aIndex)
{
	LPOBJ lpUser = &gObj[aIndex];
	PMSG_REQ_PARTYSEARCH_LOAD pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEA, 0x00, sizeof(pMsg));
	pMsg.aIndex = aIndex;
	pMsg.Name[10] = 0;
	memcpy(pMsg.Name, lpUser->Name, sizeof(pMsg.Name)-1);
	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}

void CZtGDManager::DG_PartySearchLoad(PMSG_ANS_PARTYSEARCH_LOAD *aRecv)
{
	int aIndex = aRecv->aIndex;
	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}
	g_PartySearch.LoadBinary(aIndex,aRecv->btPartySearch);
}

void CZtGDManager::GD_PartySearchSave(int aIndex)
{
	LPOBJ lpUser = &gObj[aIndex];
	PMSG_REQ_PARTYSEARCH_SAVE pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEA, 0x01, sizeof(pMsg));
	pMsg.Name[10] = 0;
	memcpy(pMsg.Name, lpUser->Name, sizeof(pMsg.Name)-1);
	g_PartySearch.SaveBinary(aIndex, pMsg.btPartySearch);
	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}
// --------------------------------------------------------

void CZtGDManager::GD_ZtBuffLoad(int aIndex)
{
	LPOBJ lpUser = &gObj[aIndex];
	PMSG_REQ_ZTBUFF_LOAD pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEA, 0x02, sizeof(pMsg));
	pMsg.aIndex = aIndex;
	pMsg.Name[10] = 0;
	memcpy(pMsg.Name, lpUser->Name, sizeof(pMsg.Name)-1);
	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}

void CZtGDManager::DG_ZtBuffLoad(PMSG_ANS_ZTBUFF_LOAD *aRecv)
{
	if(!aRecv->bResult)
	{
		return;
	}

	int aIndex = aRecv->aIndex;

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	lpUser->ExpBuffTime = aRecv->ExpBuffTime;
	lpUser->DamageBuffTime = aRecv->DamageBuffTime;
	lpUser->DefenceBuffTime = aRecv->DefenceBuffTime;
	lpUser->BattleBuffTime = aRecv->BattleBuffTime;
	lpUser->DropBuffTime = aRecv->DropBuffTime;
	lpUser->DoubleBuffTime = aRecv->DoubleBuffTime;

	g_BufferSystem.UserConnect(aIndex);
}

void CZtGDManager::GD_ZtBuffSave(int aIndex)
{
	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	PMSG_REQ_ZTBUFF_SAVE pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEA, 0x03, sizeof(pMsg));

	LPOBJ lpUser = &gObj[aIndex];

	pMsg.Name[10] = 0;
	memcpy(pMsg.Name, lpUser->Name, sizeof(pMsg.Name)-1);

	pMsg.ExpBuffTime = lpUser->ExpBuffTime;
	pMsg.DamageBuffTime = lpUser->DamageBuffTime;
	pMsg.DefenceBuffTime = lpUser->DefenceBuffTime;
	pMsg.BattleBuffTime = lpUser->BattleBuffTime;
	pMsg.DropBuffTime = lpUser->DropBuffTime;
	pMsg.DoubleBuffTime = lpUser->DoubleBuffTime;

	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}
// -------------------------------------------------------------------------------

void CZtGDManager::GD_BMQuestLoad(int aIndex)
{
	LPOBJ lpUser = &gObj[aIndex];
	PMSG_REQ_BMQUEST_LOAD pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEA, 0x04, sizeof(pMsg));
	pMsg.aIndex = aIndex;
	pMsg.Name[10] = 0;
	memcpy(pMsg.Name, lpUser->Name, sizeof(pMsg.Name)-1);
	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}

void CZtGDManager::DG_BMQuestLoad(PMSG_ANS_BMQUEST_LOAD *aRecv)
{
	if(!aRecv->bResult)
	{
		return;
	}

	int aIndex = aRecv->aIndex;

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	lpUser->BMQuest_num = aRecv->BMQuest_num;
	lpUser->BMQuest_kill = aRecv->BMQuest_kill;
	lpUser->BMQuest_start = aRecv->BMQuest_start;
	lpUser->BMDamageReflect = aRecv->BMDamageReflect;
	lpUser->BMDamage = aRecv->BMDamage;
	lpUser->BMDefense = aRecv->BMDefense;
	lpUser->BMCriticalDamage = aRecv->BMCriticalDamage;
	lpUser->BMExcelentDamage = aRecv->BMExcelentDamage;
	lpUser->BMLife = aRecv->BMLife;
}

void CZtGDManager::GD_BMQuestSave(int aIndex)
{
	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	PMSG_REQ_BMQUEST_SAVE pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEA, 0x05, sizeof(pMsg));

	LPOBJ lpUser = &gObj[aIndex];

	pMsg.Name[10] = 0;
	memcpy(pMsg.Name, lpUser->Name, sizeof(pMsg.Name)-1);

	pMsg.BMQuest_num = lpUser->BMQuest_num;
	pMsg.BMQuest_kill = lpUser->BMQuest_kill;
	pMsg.BMQuest_start = lpUser->BMQuest_start;
	pMsg.BMDamageReflect = lpUser->BMDamageReflect;
	pMsg.BMDamage = lpUser->BMDamage;
	pMsg.BMDefense = lpUser->BMDefense;
	pMsg.BMCriticalDamage = lpUser->BMCriticalDamage;
	pMsg.BMExcelentDamage = lpUser->BMExcelentDamage;
	pMsg.BMLife = lpUser->BMLife;

	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}
// -------------------------------------------------------------------------------

void CZtGDManager::GD_MonsterQuestLoad(int aIndex)
{
	LPOBJ lpUser = &gObj[aIndex];
	PMSG_REQ_MONSTERQUEST_LOAD pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEA, 0x06, sizeof(pMsg));
	pMsg.aIndex = aIndex;
	pMsg.Name[10] = 0;
	memcpy(pMsg.Name, lpUser->Name, sizeof(pMsg.Name)-1);
	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}

void CZtGDManager::DG_MonsterQuestLoad(PMSG_ANS_MONSTERQUEST_LOAD *aRecv)
{
	if(!aRecv->bResult)
	{
		return;
	}

	int aIndex = aRecv->aIndex;

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	lpUser->m_MonsterQuest.QuestNumber = aRecv->QuestNum;
	lpUser->m_MonsterQuest.KillCount[0] = aRecv->QuestKill_1;
	lpUser->m_MonsterQuest.KillCount[1] = aRecv->QuestKill_2;
	lpUser->m_MonsterQuest.KillCount[2] = aRecv->QuestKill_3;
	lpUser->m_MonsterQuest.KillCount[3] = aRecv->QuestKill_4;
	lpUser->m_MonsterQuest.KillCount[4] = aRecv->QuestKill_5;

	gMonsterQuest.GCConnectUser(aIndex);
}

void CZtGDManager::GD_MonsterQuestSave(int aIndex)
{
	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	PMSG_REQ_MONSTERQUEST_SAVE pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEA, 0x07, sizeof(pMsg));

	LPOBJ lpUser = &gObj[aIndex];

	pMsg.Name[10] = 0;
	memcpy(pMsg.Name, lpUser->Name, sizeof(pMsg.Name)-1);

	pMsg.QuestNum = lpUser->m_MonsterQuest.QuestNumber;
	pMsg.QuestKill_1 = lpUser->m_MonsterQuest.KillCount[0];
	pMsg.QuestKill_2 = lpUser->m_MonsterQuest.KillCount[1];
	pMsg.QuestKill_3 = lpUser->m_MonsterQuest.KillCount[2];
	pMsg.QuestKill_4 = lpUser->m_MonsterQuest.KillCount[3];
	pMsg.QuestKill_5 = lpUser->m_MonsterQuest.KillCount[4];

	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}
// -------------------------------------------------------------------------------

void CZtGDManager::GD_RageSystemLoad(int aIndex)
{
	LPOBJ lpUser = &gObj[aIndex];
	PMSG_REQ_RAGESYSTEM_LOAD pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEA, 0x08, sizeof(pMsg));
	pMsg.aIndex = aIndex;

	pMsg.AccountID[10] = 0;
	memcpy(pMsg.AccountID, lpUser->AccountID, sizeof(pMsg.AccountID)-1);

	pMsg.Name[10] = 0;
	memcpy(pMsg.Name, lpUser->Name, sizeof(pMsg.Name)-1);

	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}

void CZtGDManager::DG_RageSystemLoad(PMSG_ANS_RAGESYSTEM_LOAD *aRecv)
{
	int aIndex = aRecv->aIndex;

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	if(!aRecv->bResult)
	{
		return;
	}

	//gSystemOfRage.NewDBLoad(aIndex,aRecv->btRage);

	gSystemOfRage.rUser[aIndex].LoadInfo = 1;

	gSystemOfRage.rUser[aIndex].rLevel = aRecv->rLevel;
	gSystemOfRage.rUser[aIndex].rPoints = aRecv->rPoints;
	gSystemOfRage.rUser[aIndex].rExperience = aRecv->rExperience;
	gSystemOfRage.rUser[aIndex].Damage = aRecv->Damage;
	gSystemOfRage.rUser[aIndex].FreePoints = aRecv->FreePoints;
	gSystemOfRage.rUser[aIndex].SummonPet = aRecv->SummonPet;
	gSystemOfRage.rUser[aIndex].WingsDamagePlus = aRecv->WingsDamagePlus;
	gSystemOfRage.rUser[aIndex].FinalMana = aRecv->FinalMana;
	gSystemOfRage.rUser[aIndex].IgnoreDefence = aRecv->IgnoreDefence;
	gSystemOfRage.rUser[aIndex].ResetLevel = aRecv->ResetLevel;
	gSystemOfRage.rUser[aIndex].Teleport = aRecv->Teleport;
	gSystemOfRage.rUser[aIndex].CriticalDamageRate = aRecv->CriticalDamageRate;
	gSystemOfRage.rUser[aIndex].AbsordDamage = aRecv->AbsordDamage;
	gSystemOfRage.rUser[aIndex].PetDamageBonus = aRecv->PetDamageBonus;
	gSystemOfRage.rUser[aIndex].FinalLife = aRecv->FinalLife;
	gSystemOfRage.rUser[aIndex].Strength = aRecv->Strength;
	gSystemOfRage.rUser[aIndex].DefenceRate = aRecv->DefenceRate;
	gSystemOfRage.rUser[aIndex].FireDamage = aRecv->FireDamage;
	gSystemOfRage.rUser[aIndex].Energy = aRecv->Energy;
	gSystemOfRage.rUser[aIndex].Agility = aRecv->Agility;
	gSystemOfRage.rUser[aIndex].DoubleDamage = aRecv->DoubleDamage;
	gSystemOfRage.rUser[aIndex].FinalSD = aRecv->FinalSD;
	gSystemOfRage.rUser[aIndex].FinalDefence = aRecv->FinalDefence;
	gSystemOfRage.rUser[aIndex].ZenDrop = aRecv->ZenDrop;
	gSystemOfRage.rUser[aIndex].GuildBonus = aRecv->GuildBonus;
	gSystemOfRage.rUser[aIndex].ReflectDamage = aRecv->ReflectDamage;
	gSystemOfRage.rUser[aIndex].ExellentDamageRate = aRecv->ExellentDamageRate;
	gSystemOfRage.rUser[aIndex].PvPBonusPlus = aRecv->PvPBonusPlus;
	gSystemOfRage.rUser[aIndex].MinDefence = aRecv->MinDefence;
	gSystemOfRage.rUser[aIndex].Experience = aRecv->Experience;
	gSystemOfRage.rUser[aIndex].StartSD = aRecv->StartSD;
	gSystemOfRage.rUser[aIndex].PartyBonus = aRecv->PartyBonus;
	gSystemOfRage.rUser[aIndex].IceDamage = aRecv->IceDamage;
	gSystemOfRage.rUser[aIndex].DistanceAttack = aRecv->DistanceAttack;
	gSystemOfRage.rUser[aIndex].AttackRate = aRecv->AttackRate;
	gSystemOfRage.rUser[aIndex].WeaponBonus = aRecv->WeaponBonus;
	gSystemOfRage.rUser[aIndex].ExellentDamage = aRecv->ExellentDamage;
	gSystemOfRage.rUser[aIndex].CriticalDamage = aRecv->CriticalDamage;

	gSystemOfRage.ConfigSend(aIndex);
	gSystemOfRage.SendUser(aIndex);
	gObjCalCharacter(aIndex);
}

void CZtGDManager::GD_RageSystemSave(int aIndex)
{
	if(!gSystemOfRage.rUser[aIndex].LoadInfo)
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];
	PMSG_REQ_RAGESYSTEM_SAVE pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEA, 0x09, sizeof(pMsg));

	pMsg.Name[10] = 0;
	memcpy(pMsg.Name, lpUser->Name, sizeof(pMsg.Name)-1);
	pMsg.AccountID[10] = 0;
	memcpy(pMsg.AccountID, lpUser->AccountID, sizeof(pMsg.AccountID)-1);

	//gSystemOfRage.NewDBSave(aIndex, pMsg.btRage);

	pMsg.rLevel = gSystemOfRage.rUser[aIndex].rLevel;
	pMsg.rPoints = gSystemOfRage.rUser[aIndex].rPoints;
	pMsg.rExperience = gSystemOfRage.rUser[aIndex].rExperience;
	pMsg.Damage = gSystemOfRage.rUser[aIndex].Damage;
	pMsg.FreePoints = gSystemOfRage.rUser[aIndex].FreePoints;
	pMsg.SummonPet = gSystemOfRage.rUser[aIndex].SummonPet;
	pMsg.WingsDamagePlus = gSystemOfRage.rUser[aIndex].WingsDamagePlus;
	pMsg.FinalMana = gSystemOfRage.rUser[aIndex].FinalMana;
	pMsg.IgnoreDefence = gSystemOfRage.rUser[aIndex].IgnoreDefence;
	pMsg.ResetLevel = gSystemOfRage.rUser[aIndex].ResetLevel;
	pMsg.Teleport = gSystemOfRage.rUser[aIndex].Teleport;
	pMsg.CriticalDamageRate = gSystemOfRage.rUser[aIndex].CriticalDamageRate;
	pMsg.AbsordDamage = gSystemOfRage.rUser[aIndex].AbsordDamage;
	pMsg.PetDamageBonus = gSystemOfRage.rUser[aIndex].PetDamageBonus;
	pMsg.FinalLife = gSystemOfRage.rUser[aIndex].FinalLife;
	pMsg.Strength = gSystemOfRage.rUser[aIndex].Strength;
	pMsg.DefenceRate = gSystemOfRage.rUser[aIndex].DefenceRate;
	pMsg.FireDamage = gSystemOfRage.rUser[aIndex].FireDamage;
	pMsg.Energy = gSystemOfRage.rUser[aIndex].Energy;
	pMsg.Agility = gSystemOfRage.rUser[aIndex].Agility;
	pMsg.DoubleDamage = gSystemOfRage.rUser[aIndex].DoubleDamage;
	pMsg.FinalSD = gSystemOfRage.rUser[aIndex].FinalSD;
	pMsg.FinalDefence = gSystemOfRage.rUser[aIndex].FinalDefence;
	pMsg.ZenDrop = gSystemOfRage.rUser[aIndex].ZenDrop;
	pMsg.GuildBonus = gSystemOfRage.rUser[aIndex].GuildBonus;
	pMsg.ReflectDamage = gSystemOfRage.rUser[aIndex].ReflectDamage;
	pMsg.ExellentDamageRate = gSystemOfRage.rUser[aIndex].ExellentDamageRate;
	pMsg.PvPBonusPlus = gSystemOfRage.rUser[aIndex].PvPBonusPlus;
	pMsg.MinDefence = gSystemOfRage.rUser[aIndex].MinDefence;
	pMsg.Experience = gSystemOfRage.rUser[aIndex].Experience;
	pMsg.StartSD = gSystemOfRage.rUser[aIndex].StartSD;
	pMsg.PartyBonus = gSystemOfRage.rUser[aIndex].PartyBonus;
	pMsg.IceDamage = gSystemOfRage.rUser[aIndex].IceDamage;
	pMsg.DistanceAttack = gSystemOfRage.rUser[aIndex].DistanceAttack;
	pMsg.AttackRate = gSystemOfRage.rUser[aIndex].AttackRate;
	pMsg.WeaponBonus = gSystemOfRage.rUser[aIndex].WeaponBonus;
	pMsg.ExellentDamage = gSystemOfRage.rUser[aIndex].ExellentDamage;
	pMsg.CriticalDamage = gSystemOfRage.rUser[aIndex].CriticalDamage;

	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}
// -------------------------------------------------------------------------------

void CZtGDManager::GD_CreateonBankLoad(int aIndex)
{
	LPOBJ lpUser = &gObj[aIndex];
	PMSG_REQ_CREATEON_LOAD pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEA, 0x0A, sizeof(pMsg));
	pMsg.aIndex = aIndex;

	pMsg.szName[10] = 0;
	memcpy(pMsg.szName, lpUser->Name, sizeof(pMsg.szName)-1);

	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}

void CZtGDManager::DG_CreateonBankLoad(PMSG_ANS_CREATEON_LOAD *aRecv)
{
	int aIndex = aRecv->aIndex;

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	lpUser->CreateonBank = aRecv->iCreateon;

	lpUser->GuardianBank = aRecv->iGuardian;
	lpUser->HarmonyBank = aRecv->iHarmony;
	lpUser->LowStoneBank = aRecv->iLowStone;
	lpUser->HighStoneBank = aRecv->iHighStone;
	lpUser->GemStoneBank = aRecv->iGemStone;
	//

	ZtUserDataSend(aIndex);
}

void CZtGDManager::GD_CreateonBankSave(int aIndex)
{
	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	PMSG_REQ_CREATEON_SAVE pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEA, 0x0B, sizeof(pMsg));

	pMsg.szName[10] = 0;
	memcpy(pMsg.szName, lpUser->Name, sizeof(pMsg.szName)-1);

	pMsg.iCreateon = lpUser->CreateonBank;

	pMsg.iGuardian = lpUser->GuardianBank;
	pMsg.iHarmony = lpUser->HarmonyBank;
	pMsg.iLowStone = lpUser->LowStoneBank;
	pMsg.iHighStone = lpUser->HighStoneBank;
	pMsg.iGemStone = lpUser->GemStoneBank;

	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}
// -------------------------------------------------------------------------------

void CZtGDManager::GD_OfflineAfk(int aIndex, BYTE ConnectType, BYTE OfflineType)
{
	if(!g_ZtLicense.CheckUser(bassreflexive))
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	PMSG_REQ_OFFLINE_AFK pMsg = { 0 };
	pMsg.h.set((LPBYTE)&pMsg, 0xEA, 0x0F, sizeof(pMsg));
	pMsg.Name[10] = 0;
	memcpy(pMsg.Name, gObj[aIndex].Name, sizeof(pMsg.Name)-1);
	pMsg.ConnectType = ConnectType;
	pMsg.OfflineType = OfflineType;
	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}
// -------------------------------------------------------------------------------

void CZtGDManager::GD_VoteBuffLoad(int aIndex)
{
	LPOBJ lpUser = &gObj[aIndex];
	PMSG_REQ_VOTEBUFF_LOAD pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEA, 0x10, sizeof(pMsg));
	pMsg.aIndex = aIndex;

	pMsg.szName[10] = 0;
	memcpy(pMsg.szName, lpUser->Name, sizeof(pMsg.szName)-1);

	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}

void CZtGDManager::DG_VoteBuffLoad(PMSG_ANS_VOTEBUFF_LOAD *aRecv)
{
	int aIndex = aRecv->aIndex;

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	lpUser->MT_BuffTime = aRecv->MTBuffTime;
	lpUser->QT_BuffTime = aRecv->QTBuffTime;

	if(lpUser->MT_BuffTime > 0)
	{
		gObjApplyBuffEffectDuration(lpUser, AT_MMOTOP_BUFF, 0, 0, 0, 0, lpUser->MT_BuffTime);
	}

	if(lpUser->QT_BuffTime > 0)
	{
		gObjApplyBuffEffectDuration(lpUser, AT_QTOP_BUFF, 0, 0, 0, 0, lpUser->QT_BuffTime);
	}
}

void CZtGDManager::GD_VoteBuffSave(int aIndex)
{
	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	PMSG_REQ_VOTEBUFF_SAVE pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEA, 0x11, sizeof(pMsg));

	pMsg.szName[10] = 0;
	memcpy(pMsg.szName, lpUser->Name, sizeof(pMsg.szName)-1);

	pMsg.MTBuffTime = lpUser->MT_BuffTime;
	pMsg.QTBuffTime = lpUser->QT_BuffTime;

	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}

#if(CUSTOM_ZT_QUEST_SYSTEM)
void CZtGDManager::GD_ZtQuestSystemLoad(int aIndex)
{
	if(!g_ZtWinQuestSystem.Enable)
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];
	PMSG_REQ_ZtQuestSystem_LOAD pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEA, 0x14, sizeof(pMsg));
	pMsg.aIndex = aIndex;
	pMsg.Name[10] = 0;
	memcpy(pMsg.Name, lpUser->Name, sizeof(pMsg.Name)-1);
	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}

void CZtGDManager::DG_ZtQuestSystemLoad(PMSG_ANS_ZtQuestSystem_LOAD *aRecv)
{
	if(!aRecv->bResult)
	{
		return;
	}

	int aIndex = aRecv->aIndex;

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	for(int a = 0; a < EW_MAX_ACT; a++)
	{
		lpUser->ZtWQuestStart[a] = aRecv->ZtWQuestStart[a];
		lpUser->ZtWQuestNum[a] = aRecv->ZtWQuestNum[a];
		for(int m = 0; m < EW_MAX_MISSION; m++)
		{
			lpUser->ZtWQuestCount[a][m] = aRecv->ZtWQuestCount[a][m];
		}
	}

	g_ZtWinQuestSystem.UserConnect(aIndex);
}

void CZtGDManager::GD_ZtQuestSystemSave(int aIndex)
{
	if(!g_ZtWinQuestSystem.Enable)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	PMSG_REQ_ZtQuestSystem_SAVE pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEA, 0x15, sizeof(pMsg));

	LPOBJ lpUser = &gObj[aIndex];

	pMsg.Name[10] = 0;
	memcpy(pMsg.Name, lpUser->Name, sizeof(pMsg.Name)-1);

	for(int a = 0; a < EW_MAX_ACT; a++)
	{
		pMsg.ZtWQuestStart[a] = lpUser->ZtWQuestStart[a];
		pMsg.ZtWQuestNum[a] = lpUser->ZtWQuestNum[a];
		for(int m = 0; m < EW_MAX_MISSION; m++)
		{
			pMsg.ZtWQuestCount[a][m] = lpUser->ZtWQuestCount[a][m];
		}
	}

	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}
#endif
// -------------------------------------------------------------------------------