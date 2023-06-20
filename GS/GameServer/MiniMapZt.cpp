#include "StdAfx.h"
#include "..\\include\\prodef.h"
#include "user.h"
#include "MiniMapZt.h"
#include "TUnion.h"
#include "GameMain.h"
#include "..\\include\\ReadScript.h"
#include "logproc.h"
#include "ZtLicense.h"

#if(ENABLE_MINIMAP_ZT)

CMiniMapZt g_MiniMapZt;

CMiniMapZt::CMiniMapZt()
{
	this->m_Data.clear();
}

CMiniMapZt::~CMiniMapZt()
{
}

void CMiniMapZt::Load()
{
	this->m_Data.clear();

	this->Read(gDirPath.GetNewPath("ZtData\\MiniMapZt.dat"));
}

void CMiniMapZt::Read(char*filename)
{
	SMDToken Token;

	SMDFile = fopen(filename, "r");

	if(!SMDFile)
	{
		MsgBox("[MINI MAP] %s file not found", filename);
		return;
	}

	int iType = -1;

	while(true)
	{
		Token = GetToken();

		if(Token == END)
		{
			break;
		}

		iType = TokenNumber;

		while(true)
		{
			if(iType == 0)
			{
				Token = GetToken();

				if(strcmp("end", TokenString) == 0)
				{
					break;
				}

				this->m_Enable = (short)TokenNumber;
			}
			else if(iType == 1)
			{
				Token = GetToken();

				if(strcmp("end", TokenString) == 0)
				{
					break;
				}

				MINIMAP_DATA list;

				list.Map = TokenNumber;

				Token = GetToken();
				list.Player = TokenNumber;

				Token = GetToken();
				list.Party = TokenNumber;

				Token = GetToken();
				list.Guild = TokenNumber;

				Token = GetToken();
				list.Alliance = TokenNumber;

				Token = GetToken();
				list.Phonoman = TokenNumber;

				Token = GetToken();
				list.NPC = TokenNumber;

				Token = GetToken();
				list.Monster = TokenNumber;

				Token = GetToken();
				list.Boss = TokenNumber;

				this->m_Data.push_back(list);
			}
		}	
	}

	fclose(SMDFile);
	LogAdd("%s file load!", filename);
}

void CMiniMapZt::Run()
{
	if(!this->m_Enable)
	{
		return;
	}

	for(int n = OBJ_STARTUSERINDZT; n < OBJMAX; n++)
	{
		this->GCMapSend(n);
	}	
}

void CMiniMapZt::GCMapSend(int aIndex)
{
	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}

	if(lpUser->OffExp)
	{
		return;
	}

	if(lpUser->OffTrade)
	{
		return;
	}

#if(OFFLINE_MODE == TRUE)
	if(lpUser->m_OfflineMode)
	{
		return;
	}
#endif

	MINIMAP_DATA * pData = this->GetData(lpUser->MapNumber);

	if(!pData)
	{
		return;
	}

	BYTE byTempData[8192];

	memset(byTempData, 0, sizeof(byTempData));	

	int iTempSize = 7;

	int iTempCount = 0;

	for(int n = 0; n < OBJMAX; n++)
	{
		LPOBJ lpTemp = &gObj[n];

		if(lpTemp->Connected < PLAYER_PLAYING)
		{
			continue;
		}

		if(lpUser->MapNumber != lpTemp->MapNumber)
		{
			continue;
		}

		if(lpUser->m_Index == lpTemp->m_Index)
		{
			continue;
		}

		// ----

		BYTE btType = eMINIMAP_NONE;

		if(pData->Player)
		{
			if(lpTemp->Type == OBJ_USER)
			{
				btType = eMINIMAP_PLAYER;
			}
		}

		if(pData->Phonoman)
		{
			if(lpTemp->m_PK_Level >= 6)
			{
				btType = eMINIMAP_PHONOMAN;
			}
		}

		_GUILD_INFO_STRUCT * lpGuildUser = lpUser->lpGuild;
		_GUILD_INFO_STRUCT * lpGuildTemp = lpTemp->lpGuild;

		if(lpGuildUser && lpGuildTemp)
		{
			if(pData->Guild)
			{
				if(!strcmp(lpGuildUser->Name, lpGuildTemp->Name))
				{
					btType = eMINIMAP_GUILD;
				}
			}


			TUnionInfo * pUnionUser = UnionManager.SearchUnion(lpGuildUser->iGuildUnion);
			TUnionInfo * pUnionTemp = UnionManager.SearchUnion(lpGuildTemp->iGuildUnion);

			if(pData->Alliance)
			{
				if(pUnionUser && pUnionTemp)
				{
					if(!strcmp(pUnionUser->m_szMasterGuild, pUnionTemp->m_szMasterGuild))
					{
						btType = eMINIMAP_ALLIANCE;
					}
				}
			}
		}

		if(pData->Party)
		{
			if(lpUser->PartyNumber == lpTemp->PartyNumber)
			{
				btType = eMINIMAP_PARTY;
			}
		}

		if(pData->NPC)
		{
			if(lpTemp->Type == OBJ_NPC)
			{
				btType = eMINIMAP_NPC;
			}
		}

		if(pData->Monster)
		{
			if(lpTemp->Type == OBJ_MONSTER)
			{
				btType = eMINIMAP_MONSTER;
			}
		}

		if(pData->Boss)
		{
			if(lpTemp->Type == OBJ_MONSTER)
			{
				if(lpTemp->MaxLife >= 100000)
				{
					btType = eMINIMAP_BOSS;
				}
			}
		}

		MINIMAP_MONSTER Info;
		Info.Type = btType;
		Info.MapX = lpTemp->X;
		Info.MapY = lpTemp->Y;

		// ----

		memcpy(&byTempData[iTempSize], &Info, sizeof(Info));

		iTempSize += sizeof(Info);

		iTempCount++;

		if(iTempCount >= MINIMAP_MAX)
		{
			break;
		}
	}

	if(iTempCount > 0)
	{
		
		byTempData[0] = 0xC2;
		byTempData[1] = SET_NUMBERH(iTempSize);
		byTempData[2] = SET_NUMBERL(iTempSize);
		byTempData[3] = 0xFA;
		byTempData[4] = 0xED;
		byTempData[5] = SET_NUMBERH(iTempCount);
		byTempData[6] = SET_NUMBERL(iTempCount);
		

		//PMSG_MINIMAPZT pMsg;
		//pMsg.h.set((LPBYTE)&pMsg, 0xFA, 0xED, sizeof(iTempSize));
		//pMsg.DataCount = iTempCount;
		//memcpy(&byTempData[0], &pMsg, sizeof(pMsg));

		DataSend(aIndex, byTempData, iTempSize);
	}

}

MINIMAP_DATA* CMiniMapZt::GetData(int MapNum)
{
	for(int i = 0; i < this->m_Data.size(); i++)
	{
		if(this->m_Data[i].Map == MapNum)
		{
			return &this->m_Data[i];
		}
	}

	return false;
}

#endif