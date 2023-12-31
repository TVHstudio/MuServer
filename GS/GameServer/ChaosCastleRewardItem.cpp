#include "StdAfx.h"
#include "ChaosCastleRewardItem.h"
#include "ZtFunction.h"
#include "Functions.h"
#include "DSProtocol.h"
#include "ZtLicense.h"

CChaosCastleRewardItem gChaosCastleRewardItem;

void CChaosCastleRewardItem::Load()
{
	if(!g_ZtLicense.CheckUser(Local) && 
	   !g_ZtLicense.CheckUser(MedoniAndrei))
	{
		this->Enable = 0;
		return;
	}

	this->Enable = GetPrivateProfileInt("ZtTeam","Enable",0,CC_REWARD_ITEM_DIR);

	for (int j = 0; j < MAX_CHAOSCASTLE_LEVEL; j++)
	{
		for(int i=0;i<MAX_CC_REWARD_ITEM;i++)
		{
			this->Reward[i][j].Type		= 0;
			this->Reward[i][j].Index	= 0;
			this->Reward[i][j].Level	= 0;
			this->Reward[i][j].Skill	= 0;
			this->Reward[i][j].Luck		= 0;
			this->Reward[i][j].Opt		= 0;
			this->Reward[i][j].Exl		= 0;
			this->Reward[i][j].Anc		= 0;
		}
	}

	FILE *file = fopen(CC_REWARD_ITEM_DIR,"r");

	if(file == NULL)
	{
		this->Enable = 0;
		return;
	}

	char Buff[256];
	int Flag = 0;

	for (int j = 0; j < MAX_CHAOSCASTLE_LEVEL; j++)
	{
		this->Count[j] = 0;
	}
	
	while(!feof(file))
	{
		fgets(Buff,256,file);	

		if(Zt_IsBadFileLine(Buff, Flag))	
			continue;

		for(int j = 0; j < MAX_CHAOSCASTLE_LEVEL; j++)
		{
			if(Flag == (j+1))
			{
				int n[8];

				sscanf(Buff," %d %d %d %d %d %d %d %d %d",&n[0],&n[1],&n[2],&n[3],&n[4],&n[5],&n[6],&n[7]);

				this->Reward[this->Count[j]][j].Type	= n[0];
				this->Reward[this->Count[j]][j].Index	= n[1];
				this->Reward[this->Count[j]][j].Level	= n[2];
				this->Reward[this->Count[j]][j].Skill	= n[3];
				this->Reward[this->Count[j]][j].Luck	= n[4];
				this->Reward[this->Count[j]][j].Opt		= n[5];
				this->Reward[this->Count[j]][j].Exl		= n[6];
				this->Reward[this->Count[j]][j].Anc		= n[7];

				this->Count[j]++;

				if(this->Count[j]>=MAX_CC_REWARD_ITEM)
				{
					break;
				}
			}
		}
	}

	fclose(file);
}

bool CChaosCastleRewardItem::Main(int aIndex, int ChaosCastleIndex)
{
	
	if(!this->Enable)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];
	
	for(int j = 0; j < MAX_CHAOSCASTLE_LEVEL; j++)
	{
		if(ChaosCastleIndex == j)
		{
			if(this->Count[j] == 0)
			{
				return false;
			}

			int itemId = rand()%this->Count[j];

			ItemSerialCreateSend(aIndex,lpObj->MapNumber,lpObj->X,lpObj->Y,ITEMGET(this->Reward[itemId][j].Type,this->Reward[itemId][j].Index),this->Reward[itemId][j].Level,0,this->Reward[itemId][j].Skill,this->Reward[itemId][j].Luck,this->Reward[itemId][j].Opt,aIndex,this->Reward[itemId][j].Exl,this->Reward[itemId][j].Anc);

			return true;	
		}
	}

	return false;
}
