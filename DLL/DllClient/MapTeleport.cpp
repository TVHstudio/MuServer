#include "StdAfx.h"
#include "Protocol.h"
#include "MapTeleport.h"
#include "Interface.h"
#include "TMemory.h"
#include "Object.h"
#include "ReadScript.h"
#include "ZtLicense.h"

#if(CUSTOM_MAP_TELEPORT)

CMapTeleport g_MapTeleport;

CMapTeleport::CMapTeleport()
{
	this->Init();
}

CMapTeleport::~CMapTeleport()
{
}

void CMapTeleport::Init()
{
	this->m_LoadedCount = 0;

	memset(this->m_Data, 0, sizeof(this->m_Data));

	memset(&this->m_User, 0, sizeof(this->m_User));
}

void CMapTeleport::Load()
{

	this->Init();

	this->Read("Data\\ZtData\\MapTeleport.dat");

	this->BindTeleportEx();

	this->Hook();
}

void CMapTeleport::Hook()
{
	SetRange((LPVOID)0x007D34B0, 0x1E, ASM::NOP);

	SetRange((LPVOID)0x007D3B2D, 0x1E, ASM::NOP);

	SetRange((LPVOID)0x0086868E, 0x10, ASM::NOP);

	SetOp((LPVOID)0x007D34B0, (LPVOID)this->KeyboardTeleportEx, ASM::CALL);

	SetOp((LPVOID)0x007D3B2D, (LPVOID)this->KeyboardTeleportEx, ASM::CALL);

	SetOp((LPVOID)0x0086868E, (LPVOID)this->KeyboardTeleportEx, ASM::CALL);
}

void CMapTeleport::Read(char* File)
{
	SMDFile = fopen(File, "r");

	if(SMDFile == NULL)
	{
		//	LogAdd(lMsg.Get(MSGGET(1, 198)), File);

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

				memcpy(this->m_Data[this->m_LoadedCount].MapName, TokenString, 20);

				Token = GetToken();
				this->m_Data[this->m_LoadedCount].PointX = TokenNumber;

				Token = GetToken();
				this->m_Data[this->m_LoadedCount].PointY = TokenNumber;

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

void CMapTeleport::LoadTeleportEx()
{
	pLoadImage("ZtData\\Teleport\\contentmu500.tga", zt_MAPTELEPORT_MAIN, 0x2601, 0x2900, 1, 0);

	//pLoadImage("ZtData\\Teleport\\contentmap.jpg", zt_MAPTELEPORT_TEST, 0x2601, 0x2900, 1, 0);
}

void CMapTeleport::BindTeleportEx()
{
	gInterface.BindObject(eMAPTELEPORT_MAIN, zt_MAPTELEPORT_MAIN, 500, 375, -1, -1);

	//gInterface.BindObject(eMAPTELEPORT_TEST, zt_MAPTELEPORT_TEST, 640, 440, -1, -1);

	for(int i = 0; i < this->m_LoadedCount; i++)
	{
		gInterface.BindObject(eMAPTELEPORT_POINT1 + i, 0x7B68, 10, 10, this->m_Data[i].PointX, this->m_Data[i].PointY);
	}
}

void CMapTeleport::DrawTeleportEx()
{
	if(pPlayerState != GameProcess)
	{
		return;
	}

	if(!gInterface.CheckWindowZt(ztWinMapTeleport))
	{
		return;
	}

	pSetCursorFocus = true;

	int iResultID = -1;

	DWORD dwColor = eExcellent;

	float StartY = 75;
	float StartX = 150;

	if(g_ZtLicense.CheckUser(NSGames))
	{
		StartY = 40;
		StartX = 75;
		gInterface.DrawGUI(eMAPTELEPORT_MAIN, StartX, StartY);
	}
	else
	{
		gInterface.DrawIMG(eMAPTELEPORT_MAIN, StartX, StartY, 1.5, 1.0);
	
	}



	for(int i = 0; i < this->m_LoadedCount; i++)
	{
		int iPoint = eMAPTELEPORT_POINT1 + i;

		gInterface.DrawGUI(iPoint);

		gInterface.DrawToolTip(this->m_Data[i].PointX + 12, this->m_Data[i].PointY + 2, this->m_Data[i].MapName);	
	}

	for(int i = 0; i < this->m_LoadedCount; i++)
	{
		if(gInterface.IsWorkZone(eMAPTELEPORT_POINT1 + i))
		{
			gInterface.DrawColoredGUI(eMAPTELEPORT_POINT1 + i, dwColor);

			iResultID = i;

			break;
		}
	}

	if(iResultID >= 0 && iResultID < MAX_MAPTELEPORT)
	{
		this->DrawInfo(iResultID, this->m_Data[iResultID].PointX - 77, this->m_Data[iResultID].PointY + 2, 75 , 125);
	}

	//debug
	//gInterface.DrawFormat(eBlack, pCursorX, pCursorY, 100, 3, "%d - %d, ", pCursorX, pCursorY);
}

void CMapTeleport::DrawInfo(int ID, float StartX, float StartY, float Width, float Hight)
{
	MAPTELEPORT_DATA * pData = &this->m_Data[ID];

	MAPTELEPORT_USER * pUser = &this->m_User;

	DWORD dwColor = eWhite;

	int iX = StartX;

	int iY = StartY;

	int iWidth = Width;

	int iHight = this->GetCountLine(pData) * 10;

	pDrawColorButton(0x7A66, iX, iY, iWidth, iHight, 0, 0, Color4f(0, 0, 0, 200));

	// -- INFO

	iY = gInterface.DrawFormat(eYellow, iX, iY, Width, 3, pData->MapName);

	dwColor = this->GetColor(pUser->Level, pData->MinLevel, pData->MaxLevel);

	iY = gInterface.DrawFormat(dwColor, iX, iY, Width, 3, "Level: %d - %d (%d)", pData->MinLevel, pData->MaxLevel, pUser->Level);

	dwColor = this->GetColor(pUser->Reset, pData->MinReset, pData->MaxReset);

	iY = gInterface.DrawFormat(dwColor, iX, iY, Width, 3, "Reset: %d - %d (%d)", pData->MinReset, pData->MaxReset, pUser->Reset);

	dwColor = this->GetColor(pUser->Grand, pData->MinGrand, pData->MaxGrand);

	iY = gInterface.DrawFormat(dwColor, iX, iY, Width, 3, "Grand: %d - %d (%d)", pData->MinGrand, pData->MaxGrand, pUser->Grand);

	// -- PRICE

	if(pData->PriceZen > 0)
	{
		dwColor = this->GetColor(pUser->Zen, pData->PriceZen);

		iY = gInterface.DrawFormat(dwColor, iX, iY, Width, 3, "Money: %d (%d)", pData->PriceZen, pUser->Zen);
	}

	if(pData->PriceWcoin > 0)
	{
		dwColor = this->GetColor(pUser->WCoin, pData->PriceWcoin);

		iY = gInterface.DrawFormat(dwColor, iX, iY, Width, 3, "WCoin: %d (%d)", pData->PriceWcoin, pUser->WCoin);
	}

	if(pData->PriceCredit > 0)
	{
		dwColor = this->GetColor(pUser->Credit, pData->PriceCredit);

		iY = gInterface.DrawFormat(dwColor, iX, iY, Width, 3, "Credit: %d (%d)", pData->PriceCredit, pUser->Credit);
	}

	// -- NEED

	if(pData->NeedMaster)
	{
		dwColor = this->GetColor(pUser->Master, pData->NeedMaster);

		iY = gInterface.DrawFormat(dwColor, iX, iY, Width, 3, "Class: Master");
	}

	if(!pData->NeedPK)
	{
		dwColor = eExcellent;

		if(pUser->PKLevel >= 6)
		{
			dwColor = eRed;
		}

		iY = gInterface.DrawFormat(dwColor, iX, iY, Width, 3, "PK Status: Normal", pUser->PKLevel);
	}

	if(pData->NeedGuild)
	{
		dwColor = this->GetColor(pUser->Guild, pData->NeedGuild);

		iY = gInterface.DrawFormat(dwColor, iX, iY, Width, 3, "Guild: Need");
	}

	if(pData->EmptyInvintory)
	{
		dwColor = this->GetColor(pUser->Invintory, pData->EmptyInvintory);

		iY = gInterface.DrawFormat(dwColor, iX, iY, Width, 3, "Empty Invintory: Need");
	}

	if(pData->Premium)
	{
		dwColor = this->GetColor(pUser->Premium, pData->Premium);

		iY = gInterface.DrawFormat(dwColor, iX, iY, Width, 3, "Premium: Need");
	}

	// -- ITEM

	/*
	//iY += 10;
	gInterface.DrawItem(iX, iY, 10, 10, ITEMGET(12, 15), SET_ITEMOPT_LEVEL(0), 0, 0, 0);

	iX += 10;
	gInterface.DrawItem(iX, iY, 10, 10, ITEMGET(14, 13), SET_ITEMOPT_LEVEL(0), 0, 0, 0);

	iX += 10;
	gInterface.DrawItem(iX, iY, 10, 10, ITEMGET(14, 14), SET_ITEMOPT_LEVEL(0), 0, 0, 0);

	iX += 10;
	gInterface.DrawItem(iX, iY, 10, 10, ITEMGET(14, 16), SET_ITEMOPT_LEVEL(0), 0, 0, 0);

	iX += 10;
	gInterface.DrawItem(iX, iY, 10, 10, ITEMGET(14, 22), SET_ITEMOPT_LEVEL(0), 0, 0, 0);
	*/

	//	pDrawColorButton(0x7A66, iX, iY, Width, Hight, 0, 0, Color4f(0, 0, 0, 150));
}

DWORD CMapTeleport::GetColor(int Number, int Min)
{
	DWORD dwColor = eWhite;

	if(Number >= Min)
	{
		dwColor = eExcellent;
	}
	else
	{
		dwColor = eRed;
	}
	
	return dwColor;
}

DWORD CMapTeleport::GetColor(int Number, int Min, int Max)
{
	DWORD dwColor = eWhite;

	if(Number >= Min && Number <= Max)
	{
		dwColor = eExcellent;
	}
	else
	{
		dwColor = eRed;
	}
	
	return dwColor;
}

int CMapTeleport::GetCountLine(MAPTELEPORT_DATA* lpData)
{
	int iCount = 0;

	iCount++;

	iCount++;

	iCount++;

	iCount++;

	// -- PRICE

	if(lpData->PriceZen > 0)
	{
		iCount++;
	}

	if(lpData->PriceWcoin > 0)
	{
		iCount++;
	}

	if(lpData->PriceCredit > 0)
	{
		iCount++;	
	}

	// -- NEED

	if(lpData->NeedMaster)
	{
		iCount++;
	}

	if(lpData->NeedPK)
	{
		iCount++;
	}

	if(lpData->NeedGuild)
	{
		iCount++;
	}

	if(lpData->EmptyInvintory)
	{
		iCount++;
	}

	if(lpData->Premium)
	{
		iCount++;
	}

	return iCount;
}

void CMapTeleport::MouseTeleportEx(DWORD Event)
{
	if(pPlayerState != GameProcess)
	{
		return;
	}

	if(!gInterface.CheckWindowZt(ztWinMapTeleport))
	{
		return;
	}

	for(int i = 0; i < this->m_LoadedCount; i++)
	{
		if(gInterface.IsWorkZone(eMAPTELEPORT_POINT1 + i))
		{
			g_MapTeleport.CGReqSelect(i);

			break;
		}
	}
}

void CMapTeleport::KeyboardTeleportEx()
{
	if(pPlayerState != GameProcess)
	{
		return;
	}

	if(gInterface.CheckWindowZt(ztWinMapTeleport))
	{
		gInterface.CloseWindowZt(ztWinMapTeleport);
	}
	else if(!gInterface.CheckWindowZt(ztWinMapTeleport))
	{
		g_MapTeleport.CGReqData();
	}
}

void CMapTeleport::CGReqData()
{
	PMSG_REQ_MAPTELEPORT_DATA pMsg;

	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xE1, sizeof(pMsg));

	pMsg.Result = 1;

	gProtocol.DataSend((LPBYTE)&pMsg, pMsg.h.size);
}

void CMapTeleport::GCAnsData(PMSG_ANS_MAPTELEPORT_DATA* lpMsg)
{
	this->m_User.Level = lpMsg->User.Level;

	this->m_User.Reset = lpMsg->User.Reset;

	this->m_User.Grand = lpMsg->User.Grand;

	this->m_User.Zen = lpMsg->User.Zen;

	this->m_User.WCoin = lpMsg->User.WCoin;

	this->m_User.Credit = lpMsg->User.Credit;

	this->m_User.Master = lpMsg->User.Master;

	this->m_User.PKLevel = lpMsg->User.PKLevel;

	this->m_User.Guild = lpMsg->User.Guild;

	this->m_User.Invintory = lpMsg->User.Invintory;

	this->m_User.Premium = lpMsg->User.Premium;

	gInterface.OpenWindowZt(ztWinMapTeleport);
}

void CMapTeleport::CGReqSelect(int SelectNumber)
{
	PMSG_REQ_MAPTELEPORT_SELECT pMsg;

	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xE2, sizeof(pMsg));

	pMsg.Result = 1;

	pMsg.SelectNumber = SelectNumber;

	gProtocol.DataSend((LPBYTE)&pMsg, pMsg.h.size);
}

void CMapTeleport::GCAnsSelect(PMSG_ANS_MAPTELEPORT_SELECT* lpMsg)
{
	if(!lpMsg->Result)
	{
		return;
	}

	gInterface.CloseWindowZt(ztWinMapTeleport);
}

#endif