#include "StdAfx.h"
#include "protocol.h"
#include "MapTeleport.h"
#include "user.h"
#include "GameMain.h"
#include "..\\include\\ReadScript.h"
#include "logproc.h"
#include "ZtUser.h"
#include "ZtLicense.h"

#if(CUSTOM_MAP_TELEPORT)

CMapTeleport g_MapTeleport;

CMapTeleport::CMapTeleport()
{
	this->m_LoadedCount = 0;
}

CMapTeleport::~CMapTeleport()
{
}

void CMapTeleport::Load()
{
	if(!g_ZtLicense.user.CustomMapTeleport)
	{
		return;
	}

	this->m_LoadedCount = 0;

	this->Read(gDirPath.GetNewPath("ZtData\\MapTeleport.dat"));
}

void CMapTeleport::Read(char* File)
{
	SMDFile = fopen(File, "r");

	if(SMDFile == NULL)
	{
		LogAdd(lMsg.Get(MSGGET(1, 198)), File);

		return;
	}

	int Token;

	int type = -1;

	while(true)
	{
	    Token = GetToken();

        if(Token == END)
		{
            break;
		}

		type = (int)TokenNumber;

		while(true)
		{
			if(type == 0)
			{
				Token = GetToken();

				if(strcmp("end", TokenString) == 0)
				{
					break;
				}

				this->m_Data[this->m_LoadedCount].MapNumber = TokenNumber;
					
				Token = GetToken();
				this->m_Data[this->m_LoadedCount].MapX1 = TokenNumber;
				
				Token = GetToken();
				this->m_Data[this->m_LoadedCount].MapY1 = TokenNumber;
				
				Token = GetToken();
				this->m_Data[this->m_LoadedCount].MapX2 = TokenNumber;
				
				Token = GetToken();
				this->m_Data[this->m_LoadedCount].MapY2 = TokenNumber;
				
				Token = GetToken();
				this->m_Data[this->m_LoadedCount].MinLevel = TokenNumber;
				
				Token = GetToken();
				this->m_Data[this->m_LoadedCount].MaxLevel = TokenNumber;
				
				Token = GetToken();
				this->m_Data[this->m_LoadedCount].MinReset = TokenNumber;
				
				Token = GetToken();
				this->m_Data[this->m_LoadedCount].MaxReset = TokenNumber;
				
				Token = GetToken();
				this->m_Data[this->m_LoadedCount].MinGrand = TokenNumber;
				
				Token = GetToken();
				this->m_Data[this->m_LoadedCount].MaxGrand = TokenNumber;
				
				Token = GetToken();
				this->m_Data[this->m_LoadedCount].PriceZen = TokenNumber;
				
				Token = GetToken();
				this->m_Data[this->m_LoadedCount].PriceWcoin = TokenNumber;
				
				Token = GetToken();
				this->m_Data[this->m_LoadedCount].PriceCredit = TokenNumber;
				
				Token = GetToken();
				this->m_Data[this->m_LoadedCount].NeedMaster = TokenNumber;
				
				Token = GetToken();
				this->m_Data[this->m_LoadedCount].NeedPK = TokenNumber;
				
				Token = GetToken();
				this->m_Data[this->m_LoadedCount].NeedGuild = TokenNumber;
				
				Token = GetToken();
				this->m_Data[this->m_LoadedCount].EmptyInvintory = TokenNumber;

				Token = GetToken();
				this->m_Data[this->m_LoadedCount].Premium = TokenNumber;

				this->m_LoadedCount++;

				if(this->m_LoadedCount >= MAX_MAPTELEPORT)
				{
					break;
				}
			}
		}
    }

	fclose(SMDFile);
}

bool CMapTeleport::GetCheck(int aIndex, int SelectNumber)
{
	if(!OBJMAX_RANGE(aIndex))
	{
		return false;
	}

	if(SelectNumber < 0 || SelectNumber >= MAX_MAPTELEPORT)
	{
		return false;
	}

	LPOBJ lpUser = &gObj[aIndex];

	MAPTELEPORT_DATA * pSelectData = &this->m_Data[SelectNumber];

	if(pSelectData->MinLevel > lpUser->Level || lpUser->Level > pSelectData->MaxLevel )
	{
		return false;
	}

	if(pSelectData->MinReset > lpUser->Reset || lpUser->Reset > pSelectData->MaxReset )
	{
		return false;
	}

	if(pSelectData->MinGrand > lpUser->GReset || lpUser->GReset > pSelectData->MaxGrand )
	{
		return false;
	}

	if(pSelectData->PriceZen > lpUser->Money)
	{
		return false;
	}

	if(pSelectData->PriceWcoin > lpUser->GameShop.WCoinC)
	{
		return false;
	}

	if(pSelectData->PriceCredit > lpUser->ZtCred)
	{
		return false;
	}

	if(pSelectData->NeedMaster)
	{
		if(!lpUser->ChangeUP3rd)
		{
			return false;
		}
	}

	if(!pSelectData->NeedPK)
	{
		if(lpUser->m_PK_Level >= 6)
		{
			return false;
		}
	}

	if(pSelectData->NeedGuild)
	{
		if(lpUser->GuildNumber < 1)
		{
			return false;
		}
	}

	if(pSelectData->EmptyInvintory)
	{
		for(int n = 0; n < INVENTORY_SIZE; n++)
		{
			if(lpUser->pInventory[n].IsItem() == TRUE)
			{
				return false;
			}
		}
	}

	if(pSelectData->Premium > 0 && lpUser->PremiumTime == 0)
	{
		return false;
	}

	// ----

	if(pSelectData->PriceZen)
	{
		lpUser->Money -= pSelectData->PriceZen;
		GCMoneySend(aIndex, lpUser->Money);
	}

	if(pSelectData->PriceWcoin)
	{
		lpUser->GameShop.WCoinC -= pSelectData->PriceWcoin;
		ZtUserDataSend(aIndex);
	}

	if(pSelectData->PriceCredit)
	{
		lpUser->ZtCred -= pSelectData->PriceCredit;
		ZtUserDataSend(aIndex);
	}

	// ----

	return true;
}


void CMapTeleport::CGReqData(PMSG_REQ_MAPTELEPORT_DATA* lpMsg, int aIndex)
{
	if(!lpMsg->Result)
	{
		return;
	}

	this->GCAnsData(aIndex);
}

void CMapTeleport::GCAnsData(int aIndex)
{
	LPOBJ lpUser = &gObj[aIndex];

	PMSG_ANS_MAPTELEPORT_DATA pMsg;

	pMsg.h.set((LPBYTE)&pMsg, 0xFA, 0xE1, sizeof(pMsg));

	pMsg.User.Level = lpUser->Level;

	pMsg.User.Reset = lpUser->Reset;

	pMsg.User.Grand = lpUser->GReset;

	pMsg.User.Zen = lpUser->Money;

	pMsg.User.WCoin = lpUser->GameShop.WCoinC;

	pMsg.User.Credit = lpUser->ZtCred;

	pMsg.User.Master = lpUser->ChangeUP3rd;

	pMsg.User.PKLevel = lpUser->m_PK_Level;

	pMsg.User.Guild = lpUser->GuildNumber;

	pMsg.User.Invintory = 0;

	for(int n = 0; n < INVENTORY_SIZE; n++)
	{
		if(lpUser->pInventory[n].IsItem() == TRUE)
		{
			pMsg.User.Invintory = 1;
		}
	}
	
	pMsg.User.Premium = lpUser->PremiumTime;

	DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));
}

void CMapTeleport::CGReqSelect(PMSG_REQ_MAPTELEPORT_SELECT* lpMsg, int aIndex)
{
	if(!lpMsg->Result)
	{
		return;
	}

	if(gObj[aIndex].Connected < 3)
	{
		return;
	}

	int iSelectNumber = lpMsg->SelectNumber;



	if(!this->GetCheck(aIndex, iSelectNumber))
	{
		this->GCAnsSelect(aIndex, 0);

		return;
	}

	short sMapX = 0;

	short sMapY = 0;

	MAPTELEPORT_DATA * pData = &this->m_Data[iSelectNumber];

	if(!gMSetBase.GetBoxPosition(pData->MapNumber, pData->MapX1, pData->MapY1, pData->MapX2, pData->MapY2, sMapX, sMapY))
	{
		//this->GCAnsSelect(aIndex, 0);

		//return;

		sMapX = pData->MapX1;

		sMapY = pData->MapY1;
	}

	this->GCAnsSelect(aIndex, 1);
	
	gObjTeleport(aIndex, pData->MapNumber, sMapX, sMapY);
}

void CMapTeleport::GCAnsSelect(int aIndex, int Result)
{
	PMSG_ANS_MAPTELEPORT_SELECT pMsg;

	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xE2, sizeof(pMsg));

	pMsg.Result = Result;

	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}

#endif