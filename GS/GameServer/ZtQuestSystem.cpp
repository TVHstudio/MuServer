#include "StdAfx.h"
#include "user.h"
#include "ZtQuestSystem.h"
#include "Functions.h"
#include "Message.h"
//#include "MapClass.h"
#include "DSProtocol.h"
#include "GameMain.h"
#include "logproc.h"
#include "ZtFunction.h"
#include "ZtText.h"

cZtQuest ZtQuestSystem;

void cZtQuest::Loader()
{
	//CheckFile(DIR_ZT_QUEST_SYSTEM);

	this->Enable = GetPrivateProfileInt("Common","Enable",0,DIR_ZT_QUEST_SYSTEM);
	this->NPC = GetPrivateProfileInt("Common","NPC",0,DIR_ZT_QUEST_SYSTEM);

	GetPrivateProfileString("Common", "NameQuest","Quest",this->NameQuest,sizeof(this->NameQuest),DIR_ZT_QUEST_SYSTEM);

	for(int i=0;i<MAX_ZT_QUEST;i++)
	{
		this->Quest[i].Monster	= 0;
		this->Quest[i].Count	= 0;
		this->Quest[i].Procent	= 0;
		this->Quest[i].Reward	= 0;
		this->Quest[i].Gift		= 0;
		this->Quest[i].iLevel	= 0;
		this->Quest[i].Msg1[0]	= NULL;
		this->Quest[i].Msg2[0]	= NULL;
	}

	FILE *file = fopen(DIR_ZT_QUEST_SYSTEM,"r");
	if(file == NULL)
	{
		this->Enable = 0;
		return;
	}

	char Buff[256];
	int Flag = 0;
	this->qNum = 1;	//Fix

	while(!feof(file))
	{
		fgets(Buff,256,file);	
		if(Zt_IsBadFileLine(Buff, Flag))	
			continue;

		if(Flag == 1)
		{
			int n[10];
			char mes[100];
			char mes2[100];

			sscanf(Buff,"%d %d %d %d %d %d \"%[^\"]\" \"%[^\"]\"",&n[0],&n[1],&n[2],&n[3],&n[4],&n[5],&mes,&mes2);

			this->Quest[this->qNum].Monster	= n[0];
			this->Quest[this->qNum].Count		= n[1];
			this->Quest[this->qNum].Procent	= n[2];
			this->Quest[this->qNum].Reward	= n[3];
			this->Quest[this->qNum].Gift		= n[4];
			this->Quest[this->qNum].iLevel	= n[5];
			sprintf(this->Quest[this->qNum].Msg1,"%s",mes);
			sprintf(this->Quest[this->qNum].Msg2,"%s",mes2);

			this->qNum++;
		}
	}
	fclose(file);
}

void cZtQuest::NPCClick(LPOBJ lpNpc, LPOBJ lpObj)
{
	if(!this->Enable)
		return;

	if(lpNpc->Class != this->NPC)
		return;

	if(lpObj->ZtQuestNum == 0) lpObj->ZtQuestNum++;	//Fix

	int Number = lpObj->ZtQuestNum;

	if(Number >= this->qNum)
	{
		MessageChat(lpObj->m_Index,"@[%s]: Finish!",this->NameQuest);
		return;
	}

	if(lpObj->ZtQuestKill == this->Quest[Number].Count)
	{
		this->Pressent(lpObj,this->Quest[Number].Reward,this->Quest[Number].Gift,this->Quest[Number].iLevel);

		lpObj->ZtQuestNum++;
		lpObj->ZtQuestKill = 0;
	}
	else
	{
		//LPMONSTER_ATTRIBUTE lpMA = gMAttr.GetAttr(this->Quest[Number].Monster);
		MessageChat(lpObj->m_Index,g_ZtText.GetText(102),this->NameQuest,Number);	//Fix
		MessageChat(lpObj->m_Index,"@[%s]: %s",this->NameQuest,this->Quest[Number].Msg1);
		MessageChat(lpObj->m_Index,"@[%s]: %s [%d/%d]",
			this->NameQuest,
			this->Quest[Number].Msg2,
			lpObj->ZtQuestKill,
			this->Quest[Number].Count);
	}
}

void cZtQuest::MonsterKill(LPOBJ lpObj, LPOBJ lpTargetObj)	//lpTargetObj - ��?��?������?
{
	if(!this->Enable)
		return;

	int Number = lpTargetObj->ZtQuestNum;

#ifdef DEBUG_CODE
	LogAddC(2,"[ZtQuest]: %d",Number);
#endif

	if(Number == 0 || Number >= this->qNum) return;

	if(lpObj->Class == this->Quest[Number].Monster)
	{
		if(this->Quest[Number].Count == lpTargetObj->ZtQuestKill)
		{
			return;
		}

		//srand(time(NULL));
		int iRate = rand()%100;

		if(this->Quest[Number].Procent > iRate)
		{
			lpTargetObj->ZtQuestKill++;
			MessageChat(lpTargetObj->m_Index,"@[%s]: %s [%d/%d]",
				this->NameQuest,
				this->Quest[Number].Msg2,
				lpTargetObj->ZtQuestKill,
				this->Quest[Number].Count);

			if(this->Quest[Number].Count == lpTargetObj->ZtQuestKill)
			{
				MessageChat(lpTargetObj->m_Index,g_ZtText.GetText(103),this->NameQuest);
			}
		}
	}
}

void cZtQuest::Pressent(LPOBJ lpObj, int Present, int Gifts,int Level)
{
	//1- Zen, 2 - FreePoints, 3 - Items, 4 - ZtCred, 5 - Wcoin
	if(Present == 1)	//Zen
	{
		MapC[lpObj->MapNumber].MoneyItemDrop((int)Gifts, lpObj->X, lpObj->Y);
	}
	else if(Present == 2)
	{
		MessageChat(lpObj->m_Index,g_ZtText.GetText(104),this->NameQuest,Gifts);
		lpObj->ZtFreePoints += Gifts;
		lpObj->LevelUpPoint += Gifts;
		GCLevelUpMsgSend(lpObj->m_Index, 0);
	}
	else if(Present == 3)
	{
		ItemSerialCreateSend(lpObj->m_Index,(BYTE)lpObj->MapNumber,(BYTE)lpObj->X,(BYTE)lpObj->Y,Gifts,(BYTE)Level,0,0,0,0,lpObj->m_Index,0,0);
	}
	else if(Present == 4)
	{
		MessageChat(lpObj->m_Index,g_ZtText.GetText(105),this->NameQuest,Gifts);
		lpObj->ZtCred += Gifts;
	}
	else if(Present == 5)
	{
		MessageChat(lpObj->m_Index,g_ZtText.GetText(106),this->NameQuest,Gifts);
		lpObj->GameShop.WCoinC += Gifts;
		gGameShop.GDSaveUserInfo(lpObj->m_Index);
	}
	else if(Present == 6)
	{
		MessageChat(lpObj->m_Index,g_ZtText.GetText(107),this->NameQuest,Gifts);
		lpObj->GameShop.WCoinP += Gifts;
		gGameShop.GDSaveUserInfo(lpObj->m_Index);
	}
	else if(Present == 7)
	{
		MessageChat(lpObj->m_Index,g_ZtText.GetText(108),this->NameQuest,Gifts);
		lpObj->GameShop.GoblinPoint += Gifts;
		gGameShop.GDSaveUserInfo(lpObj->m_Index);
	}
	else if(Present == 8)
	{
		MessageChat(lpObj->m_Index,"@[%s]: NSPoint %d!",this->NameQuest,Gifts);
		lpObj->PCPoint += Gifts;
	}
	ZtFireCracker(lpObj->m_Index, lpObj->X, lpObj->Y);
}