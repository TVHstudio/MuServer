#include "StdAfx.h"
#include "ZtWinQuestSystem.h"
#include "user.h"
#include "GameMain.h"
#include "DSProtocol.h"
#include "ZtFunction.h"
#include "logproc.h"
#include "ZtUser.h"
#include "..\include\ReadScript.h"
#include "gObjMonster.h"
#include "BuffManager.h"
#include "ZtLicense.h"

#if(CUSTOM_ZT_QUEST_SYSTEM==TRUE)
// ----------------------------------------------------------------------------------------------

ZtWinQuestSystem g_ZtWinQuestSystem;
// ----------------------------------------------------------------------------------------------

ZtWinQuestSystem::ZtWinQuestSystem()
{
	this->Init();
}
// ----------------------------------------------------------------------------------------------

ZtWinQuestSystem::~ZtWinQuestSystem()
{
	// ----
}
// ----------------------------------------------------------------------------------------------

void ZtWinQuestSystem::Init()
{
	ZeroMemory(&this->ewdata,sizeof(this->ewdata));

	this->Enable = false;
	this->NPC_Class = 0;
	this->NPC_Map = 0;
	this->NPC_X = 0;
	this->NPC_Y = 0;
	this->iDropLoaded = 0;
}
// ----------------------------------------------------------------------------------------------

void ZtWinQuestSystem::Load()
{
	this->Init();

	if(!g_ZtLicense.user.CraftQuestSystem)
	{
		return;
	}

	this->Read(gDirPath.GetNewPath("ZtData\\ZtWinQuest\\ZtWinQuestSystem.ini"));
	this->ReadQuest(0, gDirPath.GetNewPath("ZtData\\ZtWinQuest\\ZtWinQuestData_1.ini"));
	this->ReadQuest(1, gDirPath.GetNewPath("ZtData\\ZtWinQuest\\ZtWinQuestData_2.ini"));
	this->ReadQuest(2, gDirPath.GetNewPath("ZtData\\ZtWinQuest\\ZtWinQuestData_3.ini"));
	this->ReadDrop(gDirPath.GetNewPath("ZtData\\ZtWinQuest\\ZtWinQuestDrop.ini"));
}
// ----------------------------------------------------------------------------------------------

void ZtWinQuestSystem::Read(char* File)
{
	this->Enable = GetPrivateProfileInt("ZtTeam", "Enable", 0, File);
	this->NPC_Class = GetPrivateProfileInt("ZtTeam", "NPC_Class", 0, File);
	this->NPC_Map = GetPrivateProfileInt("ZtTeam", "NPC_Map", 0, File);
	this->NPC_X = GetPrivateProfileInt("ZtTeam", "NPC_X", 0, File);
	this->NPC_Y = GetPrivateProfileInt("ZtTeam", "NPC_Y", 0, File);
}
// ----------------------------------------------------------------------------------------------

void ZtWinQuestSystem::ReadQuest(int a, char* File)
{
	int Token;

	SMDFile = fopen(File, "r");

	if( SMDFile == NULL )
	{
		MsgBox(lMsg.Get(MSGGET(0, 112)), File);
		return;
	}

	int n = 0;

	while(true) 
	{
		Token = GetToken();

		if( Token == END)
		{
			break;
		}

		if( Token != NUMBER )
		{
			continue;
		}
		
		this->ewdata[a][n].NeedLevel = TokenNumber;

		Token = GetToken();
		this->ewdata[a][n].NeedReset = TokenNumber;

		Token = GetToken();
		this->ewdata[a][n].NeedGrand = TokenNumber;

		Token = GetToken();
		strncpy(this->ewdata[a][n].NameQuest, TokenString, 25);

		for(int m = 0; m < EW_MAX_MISSION; m++)
		{
			Token = GetToken();
			this->ewdata[a][n].MissionType[m]		= TokenNumber;

			Token = GetToken();
			this->ewdata[a][n].MissionID[m]			= TokenNumber;

			Token = GetToken();
			this->ewdata[a][n].MissionIndex[m]		= TokenNumber;

			Token = GetToken();
			this->ewdata[a][n].MissionLevel[m]		= TokenNumber;

			Token = GetToken();
			this->ewdata[a][n].MissionLuck[m]		= TokenNumber;

			Token = GetToken();
			this->ewdata[a][n].MissionOpt[m]		= TokenNumber;

			Token = GetToken();
			this->ewdata[a][n].MissionExl[m]		= TokenNumber;

			Token = GetToken();
			this->ewdata[a][n].MissionProcent[m]	= TokenNumber;

			Token = GetToken();
			this->ewdata[a][n].MissionCount[m]		= TokenNumber;
		}

		for(int r = 0; r < EW_MAX_REWARD; r++)
		{
			Token = GetToken();
			this->ewdata[a][n].RewardType[r]		= TokenNumber;

			Token = GetToken();
			this->ewdata[a][n].RewardItemType[r]	= TokenNumber;

			Token = GetToken();
			this->ewdata[a][n].RewardItemIndex[r]	= TokenNumber;

			Token = GetToken();
			this->ewdata[a][n].RewardItemLevel[r]	= TokenNumber;

			Token = GetToken();
			this->ewdata[a][n].RewardCount[r]		= TokenNumber;
		}

		n++;
	}

	this->iLoaded[a] = n;
	fclose(SMDFile);	
	LogAddTD("[ZtWinQuestSystem][ReadQuestZt] [%d] Item loaded from list", this->iLoaded[a]);
}
// ----------------------------------------------------------------------------------------------

void ZtWinQuestSystem::ReadDrop(char* File)
{
	SMDFile = fopen(File, "r");

	if( SMDFile == NULL )
	{
		LogAdd(lMsg.Get(MSGGET(1, 198)), File);
		return;
	}

	while(true)
	{
		SMDToken Token = GetToken();

		if( Token == END )
		{
			break;
		}

		this->m_Drop[this->iDropLoaded].iAct				= TokenNumber;

		GetToken();
		this->m_Drop[this->iDropLoaded].iNeedQuest			= TokenNumber;

		GetToken();
		this->m_Drop[this->iDropLoaded].ItemType			= TokenNumber;

		GetToken();
		this->m_Drop[this->iDropLoaded].ItemIndex			= TokenNumber;

		GetToken();
		this->m_Drop[this->iDropLoaded].ItemMinLevel		= TokenNumber;

		GetToken();
		this->m_Drop[this->iDropLoaded].ItemMaxLevel		= TokenNumber;

		GetToken();
		this->m_Drop[this->iDropLoaded].ItemMaxOption		= TokenNumber;

		GetToken();
		this->m_Drop[this->iDropLoaded].ItemLuck			= TokenNumber;

		GetToken();
		this->m_Drop[this->iDropLoaded].ItemSkill			= TokenNumber;

		GetToken();
		this->m_Drop[this->iDropLoaded].ItemExcellent		= TokenNumber;

		GetToken();
		this->m_Drop[this->iDropLoaded].ItemDur				= TokenNumber;

		GetToken();
		this->m_Drop[this->iDropLoaded].ItemDropRate		= TokenNumber;

		GetToken();
		this->m_Drop[this->iDropLoaded].MonsterMinLevel		= TokenNumber;

		GetToken();
		this->m_Drop[this->iDropLoaded].MonsterMaxLevel		= TokenNumber;

		GetToken();
		this->m_Drop[this->iDropLoaded].MonsterMap			= TokenNumber;
	}
	// ----
	fclose(SMDFile);
	LogAddTD("[ZtWinQuestSystem][ReadDrop] [%d] Item loaded from list", this->iDropLoaded);
}
// ----------------------------------------------------------------------------------------------

bool ZtWinQuestSystem::Dialog(int aIndex, int aNpcIndex)
{
	if(!this->Enable)
	{
 		return false;
	}

	if(!gObjIsConnectedZt(aIndex))
	{
		return false;
	}

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpNpc = &gObj[aNpcIndex];

	if(		lpNpc->Class		== this->NPC_Class 
		&&	lpNpc->MapNumber	== this->NPC_Map
		&&	lpNpc->X			== this->NPC_X
		&&	lpNpc->Y			== this->NPC_Y )
	{

		this->GC_OpenWindow(aIndex);
		return true;
	}
	// ----
	return false;
}
// ----------------------------------------------------------------------------------------------

void ZtWinQuestSystem::GC_MainInfo(int aIndex)
{
	LPOBJ lpUser = &gObj[aIndex];

	int n = 0;

	GC_MainPacket pReq;
	pReq.h.set((LPBYTE)&pReq, 0xFA, 0xCC, sizeof(pReq));

	for(int a = 0; a < EW_MAX_ACT; a++)
	{
		bool sb_accept = true;
		bool sb_done = true;

		bool sb_level = true;
		bool sb_reset = true;
		bool sb_grand = true;

		bool b_mission[EW_MAX_MISSION];

		for(int i = 0; i < EW_MAX_MISSION; i++)
		{
			b_mission[i] = true;
		}

		n = lpUser->ZtWQuestNum[a];

		if(n >= this->iLoaded[a])
		{
			pReq.ztQuest[a].b_End = true;
		}
		else
		{
			pReq.ztQuest[a].b_End = false;
		}
		// -> user send
		strncpy(pReq.ztQuest[a].NameQuest, this->ewdata[a][n].NameQuest, 25);
		pReq.ztQuest[a].Start = lpUser->ZtWQuestStart[a];
		pReq.ztQuest[a].Number = lpUser->ZtWQuestNum[a];
		for(int m = 0; m < EW_MAX_MISSION; m++)
		{
			if(this->ewdata[a][n].MissionType[m] == Searching)
			{
				pReq.ztQuest[a].Count[m] = this->SearchItem(aIndex, a, m);
			}
			else
			{
				if(lpUser->ZtWQuestCount[a][m] > this->ewdata[a][n].MissionCount[m])
				{
					lpUser->ZtWQuestCount[a][m] = this->ewdata[a][n].MissionCount[m];
				}

				pReq.ztQuest[a].Count[m] = lpUser->ZtWQuestCount[a][m];
			}
		}	
		// -> need send
		if(this->ewdata[a][n].NeedLevel > lpUser->Level)
		{
			sb_level = false;
		}
		pReq.ztQuest[a].NeedLevel = this->ewdata[a][n].NeedLevel;
		if(this->ewdata[a][n].NeedReset > lpUser->Reset)
		{
			sb_reset = false;
		}
		pReq.ztQuest[a].NeedReset = this->ewdata[a][n].NeedReset;
		if(this->ewdata[a][n].NeedGrand > lpUser->GReset)
		{
			sb_grand = false;
		}
		pReq.ztQuest[a].NeedGrand = this->ewdata[a][n].NeedGrand;
		// -> mission send
		for(int m = 0; m < EW_MAX_MISSION; m++)
		{
			if(this->ewdata[a][n].MissionType[m] == Hunting || this->ewdata[a][n].MissionType[m] == Droping)
			{
				if(this->ewdata[a][n].MissionCount[m] > lpUser->ZtWQuestCount[a][m])
				{
					b_mission[m] = false;
					sb_done = false;
				}
			}
			else if(this->ewdata[a][n].MissionType[m] == Searching)
			{
				if(!this->SearchItem(aIndex, a, m))
				{
					b_mission[m] = false;
					sb_done = false;
				}
			}
			pReq.ztQuest[a].b_Mission[m] = b_mission[m];

			pReq.ztQuest[a].MissionType[m] = this->ewdata[a][n].MissionType[m];
			pReq.ztQuest[a].MissionID[m] = this->ewdata[a][n].MissionID[m];
			pReq.ztQuest[a].MissionIndex[m] = this->ewdata[a][n].MissionIndex[m];
			pReq.ztQuest[a].MissionLevel[m] = this->ewdata[a][n].MissionLevel[m];
			pReq.ztQuest[a].MissionLuck[m] = this->ewdata[a][n].MissionLuck[m];
			pReq.ztQuest[a].MissionOpt[m] = this->ewdata[a][n].MissionOpt[m];
			pReq.ztQuest[a].MissionExl[m] = this->ewdata[a][n].MissionExl[m];
			pReq.ztQuest[a].MissionCount[m] = this->ewdata[a][n].MissionCount[m];
			pReq.ztQuest[a].MissionProcent[m] = this->ewdata[a][n].MissionProcent[m];
		}
		// -> reward send
		for(int r = 0; r < EW_MAX_REWARD; r++)
		{
			pReq.ztQuest[a].RewardType[r] = this->ewdata[a][n].RewardType[r];
			pReq.ztQuest[a].RewardCount[r] = this->ewdata[a][n].RewardCount[r];
			pReq.ztQuest[a].RewardItemType[r] = this->ewdata[a][n].RewardItemType[r];
			pReq.ztQuest[a].RewardItemIndex[r] = this->ewdata[a][n].RewardItemIndex[r];
			pReq.ztQuest[a].RewardItemLevel[r] = this->ewdata[a][n].RewardItemLevel[r];
		}
		if(lpUser->ZtWQuestStart[a] == FALSE)
		{
			if( sb_level == false || sb_reset == false || sb_grand == false )
			{
				 sb_accept = false;
			}
		}

		pReq.ztQuest[a].b_done = sb_done;
		pReq.ztQuest[a].b_accept = sb_accept;

		pReq.ztQuest[a].b_Level = sb_level;
		pReq.ztQuest[a].b_Reset = sb_reset;
		pReq.ztQuest[a].b_Grand = sb_grand;
	}

	DataSend(aIndex, (LPBYTE)&pReq, sizeof(pReq));
}
// ----------------------------------------------------------------------------------------------

void ZtWinQuestSystem::GC_OpenWindow(int aIndex)
{
	if(!gObjIsConnectedZt(aIndex))
	{
		return;
	}

	this->GC_MainInfo(aIndex);
}
// ----------------------------------------------------------------------------------------------

void ZtWinQuestSystem::GC_MiniInfo(int aIndex)
{
	LPOBJ lpUser = &gObj[aIndex];

	GC_ZtWinMiniInfo pReq = { 0 };
	pReq.h.set((LPBYTE)&pReq, 0xFA, 0xCD, sizeof(pReq));

	int n = 0;

	for(int a = 0; a < EW_MAX_ACT; a++)
	{
		n = lpUser->ZtWQuestNum[a];
		strncpy(pReq.ztQuest[a].NameQuest, this->ewdata[a][n].NameQuest, 25);
		pReq.ztQuest[a].Start = lpUser->ZtWQuestStart[a];

		for(int m = 0; m < EW_MAX_MISSION; m++)
		{
			if(this->ewdata[a][n].MissionType[m] == Hunting || this->ewdata[a][n].MissionType[m] == Droping)
			{
				pReq.ztQuest[a].ZtWQuestCount[m] = lpUser->ZtWQuestCount[a][m];
			}
			else if(this->ewdata[a][n].MissionType[m] == Searching)
			{
				pReq.ztQuest[a].ZtWQuestCount[m] = this->SearchItem(aIndex, a, m);
			}

			pReq.ztQuest[a].MissionType[m] = this->ewdata[a][n].MissionType[m];
			pReq.ztQuest[a].MissionID[m] = this->ewdata[a][n].MissionID[m];
			pReq.ztQuest[a].MissionIndex[m] = this->ewdata[a][n].MissionIndex[m];
			pReq.ztQuest[a].MissionLevel[m] = this->ewdata[a][n].MissionLevel[m];
			pReq.ztQuest[a].MissionLuck[m] = this->ewdata[a][n].MissionLuck[m];
			pReq.ztQuest[a].MissionOpt[m] = this->ewdata[a][n].MissionOpt[m];
			pReq.ztQuest[a].MissionExl[m] = this->ewdata[a][n].MissionExl[m];
			pReq.ztQuest[a].MissionCount[m] = this->ewdata[a][n].MissionCount[m];
		}
	}

	DataSend(aIndex, (LPBYTE)&pReq, sizeof(pReq));
}
// ----------------------------------------------------------------------------------------------

void ZtWinQuestSystem::GC_MiniInfoZt(int aIndex, int a, int m)
{
	if(!gObjIsConnectedZt(aIndex))
	{
		return;
	}

	GC_ZtWinMiniInfoExt ztSend = { 0 };
	ztSend.h.set((LPBYTE)&ztSend, 0xFB, 0xC3, sizeof(ztSend));

	ztSend.a = a;
	ztSend.m = m;

	DataSend(aIndex, (LPBYTE)&ztSend, ztSend.h.size);
}
// ----------------------------------------------------------------------------------------------

void ZtWinQuestSystem::CG_AcceptQuest(int aIndex, CG_Accept_Done* aRecv)
{
	if(!gObjIsConnectedZt(aIndex))
	{
		return;
	}	

	if(aRecv->Result != 0 && aRecv->Result != 1 && aRecv->Result != 2)
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	int a = aRecv->Result;
	int n = lpUser->ZtWQuestNum[a];

	if(!lpUser->ZtWQuestStart[a])
	{
		if( this->ewdata[a][n].NeedLevel > lpUser->Level		||
			this->ewdata[a][n].NeedReset > lpUser->Reset		||
			this->ewdata[a][n].NeedGrand > lpUser->GReset )
		{
			LogAddC(2, "[ZtWinQuestSystem] Error CG_AcceptQuest Result");
			return;
		}
		lpUser->ZtWQuestStart[a] = true;
		this->GC_Start(aIndex, a, true);
	}
	else
	{
		this->RewardQuest(aIndex, a);
	}
}
// ----------------------------------------------------------------------------------------------

void ZtWinQuestSystem::GC_Start(int aIndex, int a, int s)
{
	GC_ZtWinStart pReq = { 0 };
	pReq.h.set((LPBYTE)&pReq, 0xFB, 0xC4, sizeof(pReq));
	pReq.Act = a;
	pReq.Start = s;
	DataSend(aIndex, (LPBYTE)&pReq, pReq.h.size);

}
// ----------------------------------------------------------------------------------------------

bool ZtWinQuestSystem::MonsterKiller(int aIndexMonster, int aIndexUser)
{
	bool Result = false;

	if(!this->Enable)
	{
 		return Result;
	}

	LPOBJ lpUser = &gObj[aIndexUser];
	LPOBJ lpMonster = &gObj[aIndexMonster];

	int n = 0;

	for(int a = 0; a < EW_MAX_ACT; a++)
	{
		n = lpUser->ZtWQuestNum[a];

		if(lpUser->ZtWQuestStart[a] == TRUE)
		{
			for(int m = 0; m < EW_MAX_MISSION; m++)
			{
				// -> Monsterr Mission
				if(this->ewdata[a][n].MissionType[m] == Hunting)
				{
					if(this->ewdata[a][n].MissionCount[m] > lpUser->ZtWQuestCount[a][m])
					{
						if( this->ewdata[a][n].MissionLuck[m] == lpMonster->MapNumber ||  this->ewdata[a][n].MissionLuck[m] == -1 )
						{
							if(this->ewdata[a][n].MissionID[m] == lpMonster->Class)	// Охот?на монастро?по классу
							{
								lpUser->ZtWQuestCount[a][m]++;
								this->GC_MiniInfoZt(aIndexUser, a, m);
							}
							else if(this->ewdata[a][n].MissionID[m] == -1)	// Охот?на монастро?по уровню
							{
								if(lpMonster->Level >= this->ewdata[a][n].MissionOpt[m] && lpMonster->Level <= this->ewdata[a][n].MissionExl[m])
								{
									lpUser->ZtWQuestCount[a][m]++;
									this->GC_MiniInfoZt(aIndexUser, a, m);
								}
							}
						}
					}
				}
				// -> Drop Mission
				if( this->ewdata[a][n].MissionType[m] == Droping )
				{
					if( this->ewdata[a][n].MissionCount[m] > lpUser->ZtWQuestCount[a][m] )
					{
						if( this->ewdata[a][n].MissionLuck[m] == lpMonster->MapNumber ||  this->ewdata[a][n].MissionLuck[m] == -1 )
						{
							if(lpMonster->Level >= this->ewdata[a][n].MissionOpt[m] && lpMonster->Level <= this->ewdata[a][n].MissionExl[m])
							{
								if ( (rand()%100) < this->ewdata[a][n].MissionProcent[m] )
								{
									int ItemType = ITEMGET(this->ewdata[a][n].MissionID[m], this->ewdata[a][n].MissionIndex[m]);
									ItemSerialCreateSend(aIndexUser,lpMonster->MapNumber,lpMonster->X,lpMonster->Y,ItemType,0,0,0,0,0,aIndexUser,0,0);
									Result = true;
								}
							}
						}
					}
				}
			}
		}
	}

#if(EW_NEW_DROP==TRUE)
	if(this->NewDrop(aIndexUser, aIndexMonster))
	{
		Result = true;
	}
#endif

	return Result;
}
// ----------------------------------------------------------------------------------------------

int ZtWinQuestSystem::PickUpItem(int aIndex, int ItemType)
{
	if(!this->Enable)
	{
 		return 0;
	}

	int n = 0;
	LPOBJ lpUser = &gObj[aIndex];

	for(int a = 0; a < EW_MAX_ACT; a++)
	{
		n = lpUser->ZtWQuestNum[a];

		if(lpUser->ZtWQuestStart[a] == TRUE)
		{
			for(int m = 0; m < EW_MAX_MISSION; m++)
			{
				if( this->ewdata[a][n].MissionType[m] == Droping && 
					ITEMGET(this->ewdata[a][n].MissionID[m], this->ewdata[a][n].MissionIndex[m]) == ItemType )
				{
					if(this->ewdata[a][n].MissionCount[m] > lpUser->ZtWQuestCount[a][m])
					{
						lpUser->ZtWQuestCount[a][m]++;
						this->GC_MiniInfoZt(aIndex, a, m);
						return 1;
					}
					else if(lpUser->ZtWQuestCount[a][m] >= this->ewdata[a][n].MissionCount[m])
					{
						return 2;
					}
				}
			}
		}
	}

	return 0;
}
// ----------------------------------------------------------------------------------------------

bool ZtWinQuestSystem::SearchItem(int aIndex, int a, int m)
{
	LPOBJ lpUser = &gObj[aIndex];

	int n = lpUser->ZtWQuestNum[a];

	short iType = ITEMGET(this->ewdata[a][n].MissionID[m], this->ewdata[a][n].MissionIndex[m]);
	short iLevel = this->ewdata[a][n].MissionLevel[m];
	short iLuck = this->ewdata[a][n].MissionLuck[m];
	short iOpt =  this->ewdata[a][n].MissionOpt[m];
	short iExl = this->ewdata[a][n].MissionExl[m];

	for (int i = INVETORY_WEAR_SIZE; i < INVENTORY_SIZE; i++)
	{
		if( lpUser->pInventory[i].m_Type == iType && 
			lpUser->pInventory[i].m_Level >= iLevel &&
			CheckOptionItem(lpUser->pInventory[i].m_Option2, iLuck, FALSE) &&
			CheckOptionItem(lpUser->pInventory[i].m_Option3, iOpt, FALSE) &&
			CheckOptionItem(lpUser->pInventory[i].m_NewOption, iExl, FALSE) )
		{
			return true;
		}
	}

	return false;
}
// ----------------------------------------------------------------------------------------------

void ZtWinQuestSystem::DeleteItem(int aIndex, int a, int m)
{
	LPOBJ lpUser = &gObj[aIndex];

	int n = lpUser->ZtWQuestNum[a];

	short iType = ITEMGET(this->ewdata[a][n].MissionID[m], this->ewdata[a][n].MissionIndex[m]);
	short iLevel = this->ewdata[a][n].MissionLevel[m];
	short iLuck = this->ewdata[a][n].MissionLuck[m];
	short iOpt =  this->ewdata[a][n].MissionOpt[m];
	short iExl = this->ewdata[a][n].MissionExl[m];

	for (int i = INVETORY_WEAR_SIZE; i < INVENTORY_SIZE; i++)
	{
		if( lpUser->pInventory[i].m_Type == iType && 
			lpUser->pInventory[i].m_Level >= iLevel &&
			CheckOptionItem(lpUser->pInventory[i].m_Option2, iLuck, FALSE) &&
			CheckOptionItem(lpUser->pInventory[i].m_Option3, iOpt, FALSE) &&
			CheckOptionItem(lpUser->pInventory[i].m_NewOption, iExl, FALSE) )
		{
			gObjInventoryDeleteItem(aIndex, i);
			GCInventoryItemDeleteSend(aIndex, i, 1);
		}
	}
}
// ----------------------------------------------------------------------------------------------

bool ZtWinQuestSystem::CheckMission(int aIndex, int a)
{
	LPOBJ lpUser = &gObj[aIndex];

	int n = lpUser->ZtWQuestNum[a];

	for(int m = 0; m < EW_MAX_MISSION; m++)
	{
		if(this->ewdata[a][n].MissionType[m] == Hunting || this->ewdata[a][n].MissionType[m] == Droping)
		{
			if(this->ewdata[a][n].MissionCount[m] > lpUser->ZtWQuestCount[a][m])
			{
				return false;
			}
		}
		else if(this->ewdata[a][n].MissionType[m] == Searching)
		{
			if(!this->SearchItem(aIndex, a, m))
			{
				return false;
			}
		}
	}

	return true;
}
// ----------------------------------------------------------------------------------------------

void ZtWinQuestSystem::UserConnect(int aIndex)
{
	LPOBJ lpUser = &gObj[aIndex];

	this->GC_MiniInfo(aIndex);

	for(int a = 0; a < EW_MAX_ACT; a++)
	{
		if(lpUser->ZtWQuestNum[a] >= 0 && lpUser->ZtWQuestStart[a] == true)
		{
			return;
		}
	}
}
// ----------------------------------------------------------------------------------------------

void ZtWinQuestSystem::RewardQuest(int aIndex, int Act)
{
	if(!gObjIsConnectedZt(aIndex))
	{
		return;
	}	

	LPOBJ lpUser = &gObj[aIndex];

	int a = Act;

	if(!this->CheckMission(aIndex, a))
	{
		LogAddC(2, "[ZtWinQuestSystem] RewardQuest ERROR");
		return;
	}
	
	int n = lpUser->ZtWQuestNum[a];
	int UserMap = lpUser->MapNumber;
	int UserX = lpUser->X;
	int UserY = lpUser->Y;

	int rType = 0;
	int rItemType = 0;
	int rItemIndex = 0;
	int rItemLevel = 0;
	int rCount = 0;

	for(int m = 0; m < EW_MAX_MISSION; m++)
	{
		lpUser->ZtWQuestCount[a][m] = 0;
		if(this->ewdata[a][n].MissionType[m] == Searching)
		{
			this->DeleteItem(aIndex, a, m);
		}
	}

	for(int r = 0; r < EW_MAX_REWARD; r++)
	{
		rType = this->ewdata[a][n].RewardType[r];
		rItemType = this->ewdata[a][n].RewardItemType[r];
		rItemIndex = this->ewdata[a][n].RewardItemIndex[r];
		rItemLevel = this->ewdata[a][n].RewardItemLevel[r];
		rCount = this->ewdata[a][n].RewardCount[r];

		if(rType == ewZen)
		{	
			if(!MAX_MAP_RANGE(UserMap))
			{
				return;
			}
			MapC[UserMap].MoneyItemDrop(rCount, UserX, UserY);
		}
		if(rType == ewFreePoint)
		{
			lpUser->ZtFreePoints += rCount;
			lpUser->LevelUpPoint += rCount;
			//g_ZtUser.UpdateCharInfo(aIndex);
			ZtUserDataSend(aIndex);
		}
		if(rType == ewItem)
		{
			for(int d = 0; d < rCount; d++ )
			{
				ItemSerialCreateSend(aIndex, UserMap, UserX, UserY, ITEMGET(rItemType, rItemIndex), rItemLevel, 0, 0, 0, 0, lpUser->m_Index, 0, 0);
			}
		}
		if(rType == ewBonus)
		{


			lpUser->GameShop.WCoinC += rCount;
			gGameShop.GDSaveUserInfo(lpUser->m_Index);

			//g_ZtUser.UpdateCharInfo(aIndex);
			ZtUserDataSend(aIndex);
		}
		if(rType == ewBuff)
		{
			int idBuffer = AT_NPC_BUFF_EXP;
			lpUser->ExpBuffTime = rCount;

			if(rItemType == 1)
			{
				idBuffer = AT_NPC_BUFF_EXP;
				lpUser->ExpBuffTime = rCount;
			}
			if(rItemType == 2)
			{
				idBuffer = AT_NPC_BUFF_DAMAGE;
				lpUser->DamageBuffTime = rCount;
			}
			if(rItemType == 3)
			{
				idBuffer = AT_NPC_BUFF_DEFENCE;
				lpUser->DefenceBuffTime = rCount;
			}
			if(rItemType == 4)
			{
				idBuffer = AT_NPC_BUFF_EXL_CRIT;
				lpUser->BattleBuffTime = rCount;
			}
			if(rItemType == 5)
			{
				idBuffer = AT_NPC_BUFF_DROP;
				lpUser->DropBuffTime = rCount;
			}
			if(rItemType == 6)
			{
				idBuffer = AT_NPC_BUFF_DOUBLE;
				lpUser->DoubleBuffTime = rCount;
			}

			gObjApplyBuffEffectDuration(lpUser, idBuffer, 0, 0, 0, 0, rCount);
		}
	}

	lpUser->ZtWQuestNum[a]++;
	lpUser->ZtWQuestStart[a] = false;
	this->GC_MainInfo(aIndex);
}
// ----------------------------------------------------------------------------------------------

bool ZtWinQuestSystem::NewDrop(int aIndexMob, int aIndexUser)
{
	LPOBJ lpUser = &gObj[aIndexUser];
	LPOBJ lpMonster = &gObj[aIndexMob];

	switch(lpMonster->Class)
	{
	case 78:
	case 53:
	case 79:
	case 80:
	case 82:
	case 502:
	case 493:
	case 494:
	case 495:
	case 496:
	case 497:
	case 498:
	case 499:
	case 500:
	case 501:
		{
			return false;
		}
		break;
	}

	for( int i = 0; i < this->iDropLoaded; i++ )
	{
		int a = this->m_Drop[i].iAct;

		if(a < 0 || a >= EW_MAX_ACT)
		{
			continue;
		}

		if(lpUser->ZtWQuestNum[a] >= this->m_Drop[i].iNeedQuest)
		{
			if( lpMonster->Level >= this->m_Drop[i].MonsterMinLevel && lpMonster->Level <= this->m_Drop[i].MonsterMaxLevel )
			{
				if( lpMonster->MapNumber == this->m_Drop[i].MonsterMap || this->m_Drop[i].MonsterMap == -1 )
				{
					if( rand() % 10000 < this->m_Drop[i].ItemDropRate )
					{
						int iLuck	= 0;
						int iSkill	= 0;
						int iOption	= 0;
						int iLevel	= 0;

						// ----
						if( this->m_Drop[i].ItemMaxLevel == this->m_Drop[i].ItemMinLevel )
						{
							iLevel = this->m_Drop[i].ItemMinLevel;
						}
						else
						{
							iLevel = this->m_Drop[i].ItemMinLevel + (rand() % (this->m_Drop[i].ItemMaxLevel - this->m_Drop[i].ItemMinLevel + 1));
						}

						// ----
						if( this->m_Drop[i].ItemLuck == 1 )
						{
							if( rand() % 100 < 50 )
							{
								iLuck = 1;
							}
						}
						// ----
						if( this->m_Drop[i].ItemSkill == 1 )
						{
							if( rand() % 100 < 50 )
							{
								iSkill = 1;
							}
						}
						// ----
						if( this->m_Drop[i].ItemMaxOption != 0 )
						{
							if( rand() % 100 < 50 )
							{
								iOption = rand() % this->m_Drop[i].ItemMaxOption + 1;
							}
						}

						ItemSerialCreateSend(lpUser->m_Index, lpMonster->MapNumber, lpMonster->X, lpMonster->Y, ITEMGET(this->m_Drop[i].ItemType, this->m_Drop[i].ItemIndex), iLevel, this->m_Drop[i].ItemDur, iOption, iLuck, iSkill, gObjMonsterTopHitDamageUser(lpMonster), this->m_Drop[i].ItemExcellent, 0);
					
						return true;
					}
				}
			}
		}
	}

	return false;
}
// ----------------------------------------------------------------------------------------------

void ZtWinQuestSystem::SaveQuest(int aIndex, LPBYTE buf)
{
	return;
	LPOBJ lpUser = &gObj[aIndex];

	int n = 0;
	BYTE Start = 0;
	WORD Number = 0;
	WORD Count = 0;

	for(int a = 0; a < EW_MAX_ACT; a++)
	{
		Start = lpUser->ZtWQuestStart[a];
		buf[n] = Start;
		n++;
		WORD Number = lpUser->ZtWQuestNum[a];
		buf[n] = SET_NUMBERH(Number);
		n++;
		buf[n] = SET_NUMBERL(Number);
		n++;
		for(int m = 0; m < EW_MAX_MISSION; m++)
		{
			Count = lpUser->ZtWQuestCount[a][m];
			buf[n] = SET_NUMBERH(Count);
			n++;
			buf[n] = SET_NUMBERL(Count);
			n++;
		}
	}

#if(EW_DEBUG==TRUE)
	LogAddC(2, "SaveQuest: %d", n);
#endif
}
// ----------------------------------------------------------------------------------------------

void ZtWinQuestSystem::LoadQuest(int aIndex, LPBYTE buf)
{
	return;
	LPOBJ lpUser = &gObj[aIndex];
	int n = 0;

	for(int a = 0; a < EW_MAX_ACT; a++)
	{
		lpUser->ZtWQuestStart[a] = buf[n];
		n++;
		lpUser->ZtWQuestNum[a] = MAKE_NUMBERW(buf[n], buf[n+1]);
		n+=2;
		for(int m = 0; m < EW_MAX_MISSION; m++)
		{
			lpUser->ZtWQuestCount[a][m] = MAKE_NUMBERW(buf[n], buf[n+1]);
			n+=2;
		}
	}

#if(EW_DEBUG==TRUE)
	LogAddC(2, "LoadQuest: %d", n);
#endif
}
// ----------------------------------------------------------------------------------------------
#endif