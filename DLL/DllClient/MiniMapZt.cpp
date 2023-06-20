#include "StdAfx.h"
#include "Protocol.h"
#include "MiniMapZt.h"
#include "Interface.h"
#include "Object.h"
#include "ReadScript.h"

#if(ENABLE_MINIMAP_ZT)

CMiniMapZt g_MiniMapZt;


CMiniMapZt::CMiniMapZt()
{
	this->m_Enable		= 0;
	this->m_Show		= 0;
	this->m_DataCount	= 0;

	memset(this->m_Data, 0, sizeof(this->m_Data));	
}

CMiniMapZt::~CMiniMapZt()
{

}

void CMiniMapZt::Load()
{
	this->m_Config.clear();

	this->m_Show = 1;

	this->Read("Data\\ZtData\\MiniMapZtC.dat");
}

void CMiniMapZt::LoadImg()
{
	pLoadImage("ZtData\\Maps\\PlayerPoint.jpg", zt_PLAYER_POINT, 0x2600, 0x2900, 1, 0);
	pLoadImage("ZtData\\Maps\\null.tga", zt_NULL_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("ZtData\\Maps\\Lorencia.tga", zt_LORENCIA_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("ZtData\\Maps\\Dungeon.tga", zt_DUNGEON_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("ZtData\\Maps\\Devias.tga", zt_DEVIAS_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("ZtData\\Maps\\Noria.tga", zt_NORIA_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("ZtData\\Maps\\Losttower.tga", zt_LOSTTOWER_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("ZtData\\Maps\\Atlans.tga", zt_ATLANS_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("ZtData\\Maps\\Tarkan.tga", zt_Tarkan_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("ZtData\\Maps\\Elbeland.tga", zt_Elbeland_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("ZtData\\Maps\\Icarus.tga", zt_ICARUS_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("ZtData\\Maps\\LandOfTrials.tga", zt_LANDOFTRIALS_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("ZtData\\Maps\\Aida.tga", zt_AIDA_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("ZtData\\Maps\\Crywolf.tga", zt_CRYWOLF_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("ZtData\\Maps\\Kantru.tga", zt_KANTRU_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("ZtData\\Maps\\Kantru3.tga", zt_KANTRU3_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("ZtData\\Maps\\Barracks.tga", zt_BARRACKS_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("ZtData\\Maps\\Calmness.tga", zt_CALMNESS_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("ZtData\\Maps\\Raklion.tga", zt_RAKLION_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("ZtData\\Maps\\Vulcanus.tga", zt_VULCANUS_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("ZtData\\Maps\\Kalrutan.tga", zt_KALRUTAN_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("ZtData\\Maps\\Kalrutan2.tga", zt_KALRUTAN2_MAP, 0x2601, 0x2900, 1, 0);
}

void CMiniMapZt::BindImg()
{
	gInterface.BindObject(eNULL_MAP, zt_NULL_MAP, 128, 128, -1, -1);
	gInterface.BindObject(eLORENCIA_MAP, zt_LORENCIA_MAP, 128, 128, -1, -1);
	gInterface.BindObject(eDUNGEON_MAP, zt_DUNGEON_MAP, 128, 128, -1, -1);
	gInterface.BindObject(eDEVIAS_MAP, zt_DEVIAS_MAP, 128, 128, -1, -1);
	gInterface.BindObject(eNORIA_MAP, zt_NORIA_MAP, 128, 128, -1, -1);
	gInterface.BindObject(eLOSTTOWER_MAP, zt_LOSTTOWER_MAP, 128, 128, -1, -1);
	gInterface.BindObject(eATLANS_MAP, zt_ATLANS_MAP, 128, 128, -1, -1);
	gInterface.BindObject(eTarkan_MAP, zt_Tarkan_MAP, 128, 128, -1, -1);
	gInterface.BindObject(eElbeland_MAP, zt_Elbeland_MAP, 128, 128, -1, -1);
	gInterface.BindObject(eICARUS_MAP, zt_ICARUS_MAP, 128, 128, -1, -1);
	gInterface.BindObject(eLANDOFTRIALS_MAP, zt_LANDOFTRIALS_MAP, 128, 128, -1, -1);
	gInterface.BindObject(eAIDA_MAP, zt_AIDA_MAP, 128, 128, -1, -1);
	gInterface.BindObject(eCRYWOLF_MAP, zt_CRYWOLF_MAP, 128, 128, -1, -1);
	gInterface.BindObject(eKANTRU_MAP, zt_KANTRU_MAP, 128, 128, -1, -1);
	gInterface.BindObject(eKANTRU3_MAP, zt_KANTRU3_MAP, 128, 128, -1, -1);
	gInterface.BindObject(eBARRACKS_MAP, zt_BARRACKS_MAP, 128, 128, -1, -1);
	gInterface.BindObject(eCALMNESS_MAP, zt_CALMNESS_MAP, 128, 128, -1, -1);
	gInterface.BindObject(eRAKLION_MAP, zt_RAKLION_MAP, 128, 128, -1, -1);
	gInterface.BindObject(eVULCANUS_MAP, zt_VULCANUS_MAP, 128, 128, -1, -1);
	gInterface.BindObject(eKALRUTAN_MAP, zt_KALRUTAN_MAP, 128, 128, -1, -1);
	gInterface.BindObject(eKALRUTAN2_MAP, zt_KALRUTAN2_MAP, 128, 128, -1, -1);
}

void CMiniMapZt::Read(char*filename)
{
	SMDToken Token;

	SMDFile = fopen(filename, "r");

	if(!SMDFile)
	{
		//MsgBox("[MINI MAP] %s file not found", filename);
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

				list.Type = TokenNumber;

				Token = GetToken();
				list.Red = TokenNumber;

				Token = GetToken();
				list.Green = TokenNumber;

				Token = GetToken();
				list.Blue = TokenNumber;

				Token = GetToken();
				list.Alfa = TokenNumber;

				Token = GetToken();
				list.Size = TokenNumber;

				this->m_Config.push_back(list);
			}
		}	
	}

	fclose(SMDFile);
	//LogAdd("%s file load!", filename);
}

void CMiniMapZt::Run()
{

}

void CMiniMapZt::DrawMain()
{
	if(!this->m_Enable)
	{
		return;
	}

	if(!this->m_Show)
	{
		return;
	}

	if(!this->DrawCheck())
	{
		return;
	}

	float MainWidth = 138.0;
	float MainHeight = 265.0;
	float StartY = 264.0 + 7.0;
	float StartX = 512.0;

	gInterface.RightMiniInfoY -= 128;

	switch(pMapNumber)
	{
		case 0:		gInterface.DrawGUI(eLORENCIA_MAP, StartX, StartY + 30);		break;	//Lorencia
		case 1:		gInterface.DrawGUI(eDUNGEON_MAP, StartX, StartY + 30);		break;	//Dungeon
		case 2:		gInterface.DrawGUI(eDEVIAS_MAP, StartX, StartY + 30);		break;  //Devias
		case 3:		gInterface.DrawGUI(eNORIA_MAP, StartX, StartY + 30);		break;  //Noria
		case 4:		gInterface.DrawGUI(eLOSTTOWER_MAP, StartX, StartY + 30);	break;  //LostTower
		case 7:		gInterface.DrawGUI(eATLANS_MAP, StartX, StartY + 30);		break;  //Atlans
		case 8:		gInterface.DrawGUI(eTarkan_MAP, StartX, StartY + 30);		break;  //Tarkan
		case 10:	gInterface.DrawGUI(eICARUS_MAP, StartX, StartY + 30);		break;	//Icarus
		case 31:    gInterface.DrawGUI(eLANDOFTRIALS_MAP, StartX, StartY + 30);	break;	//Land of Trials
		case 33:    gInterface.DrawGUI(eAIDA_MAP, StartX, StartY + 30);			break;	//Aida
		case 34:    gInterface.DrawGUI(eCRYWOLF_MAP, StartX, StartY + 30);		break;	//Crywolf Fortress
		case 37:    gInterface.DrawGUI(eKANTRU_MAP, StartX, StartY + 30);		break;	//Kantru
		case 38:    gInterface.DrawGUI(eKANTRU3_MAP, StartX, StartY + 30);		break;	//Kantru
		case 41:	gInterface.DrawGUI(eBARRACKS_MAP, StartX, StartY + 30);		break;  //Barracks
		case 51:    gInterface.DrawGUI(eElbeland_MAP, StartX, StartY + 30);		break;	//Elbeland
		case 56:    gInterface.DrawGUI(eCALMNESS_MAP, StartX, StartY + 30);		break;	//Swamp of Calmness
		case 57:    gInterface.DrawGUI(eRAKLION_MAP, StartX, StartY + 30);		break;	//Raklion
		case 63:    gInterface.DrawGUI(eVULCANUS_MAP, StartX, StartY + 30);		break;	//Vulcanus
		case 80:    gInterface.DrawGUI(eKALRUTAN_MAP, StartX, StartY + 30);		break;	//Kalrutan
		case 81:    gInterface.DrawGUI(eKALRUTAN2_MAP, StartX, StartY + 30);	break;	//Kalrutan 2
		default:	return;
	}

	lpViewObj lpViewPlayer = &*(ObjectPreview*)oUserPreviewStruct;

	float flInfoX = (float)(StartX - 1 + lpViewPlayer->MapPosX / 2);

	float flInfoY = (float)(294 - 1 + (255 - lpViewPlayer->MapPosY) / 2);

	pDrawColorButton(0x7880, flInfoX, flInfoY, this->m_Config[0].Size, this->m_Config[0].Size, 0, 0, Color4f(this->m_Config[0].Red, this->m_Config[0].Green, this->m_Config[0].Blue, this->m_Config[0].Alfa));	

	for(int i = 0; i < this->m_DataCount; i++)
	{
		MINIMAP_MONSTER * pData = &this->m_Data[i];

		flInfoX = (float)(StartX - 1 + pData->MapX / 2);

		flInfoY = (float)(298 - 1 + (255 - pData->MapY) / 2);

		if(pData->Type < eMINIMAP_PLAYER || pData->Type > eMINIMAP_BOSS)
		{
			continue;
		}

		DWORD dwColor =	Color4f(this->m_Config[pData->Type].Red, this->m_Config[pData->Type].Green, this->m_Config[pData->Type].Blue, this->m_Config[pData->Type].Alfa);

		DWORD dwSize = this->m_Config[pData->Type].Size;

		switch(pData->Type)
		{
			case eMINIMAP_PLAYER:	pDrawColorButton(0x7880, flInfoX , flInfoY, dwSize, dwSize, 0, 0, dwColor);			break;
			case eMINIMAP_PARTY:	pDrawColorButton(0x7880, flInfoX , flInfoY, dwSize, dwSize, 0, 0, dwColor);			break;
			case eMINIMAP_GUILD:	pDrawColorButton(0x7880, flInfoX , flInfoY, dwSize, dwSize, 0, 0, dwColor);			break;
			case eMINIMAP_ALLIANCE:	pDrawColorButton(0x7880, flInfoX , flInfoY, dwSize, dwSize, 0, 0, dwColor);			break;
			case eMINIMAP_PHONOMAN:	pDrawColorButton(0x7880, flInfoX , flInfoY, dwSize, dwSize, 0, 0, dwColor);			break;
			case eMINIMAP_NPC:		pDrawColorButton(0x7880, flInfoX , flInfoY, dwSize, dwSize, 0, 0, dwColor);			break;
			case eMINIMAP_MONSTER:	pDrawColorButton(0x7880, flInfoX , flInfoY, dwSize, dwSize, 0, 0, dwColor);			break;
			case eMINIMAP_BOSS:		pDrawColorButton(0x7880, flInfoX , flInfoY, dwSize, dwSize, 0, 0, dwColor);			break;
		}
	}
}

bool CMiniMapZt::DrawCheck()
{
	if (gInterface.MiniMapCheck() || gInterface.CombinedChecks())
	{
		return false;
	}

	return true;
}

void CMiniMapZt::CGMapRecv(LPBYTE lpMsg)
{
	
	//this->m_DataCount = lpCount->DataCount;

	int iDataSize = 7;

	this->m_DataCount = MAKE_NUMBERW(lpMsg[5], lpMsg[6]);

	for(int i = 0; i < this->m_DataCount; i++)
	{
		
		if(i >= MINIMAP_MAX)	//MINIMAP_MAX
		{
			break;
		}

		MINIMAP_MONSTER Info;

		memcpy(&Info, &lpMsg[iDataSize], sizeof(Info));

		this->m_Data[i].Type = Info.Type;
		this->m_Data[i].MapX = Info.MapX; 
		this->m_Data[i].MapY = Info.MapY; 

		iDataSize += sizeof(Info);
	}
	

}


#endif