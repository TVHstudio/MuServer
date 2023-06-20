#include "StdAfx.h"
#include "UserConfig.h"
#include "GameMain.h"
#include "ZtLicense.h"
#include "GameMain.h"

CUserConfig g_UserConfig;

CUserConfig::CUserConfig()
{
}

CUserConfig::~CUserConfig()
{
}

void CUserConfig::Load()
{
	if(g_ZtLicense.CheckUser(eZtUB::ulasevich) || g_ZtLicense.CheckUser(eZtUB::ulasevich2))
	{
		this->ReadUsilevich(gDirPath.GetNewPath("ZtData\\User\\Usilevich.ini"));
	}

	if(g_ZtLicense.CheckUser(eZtUB::Gredy) || g_ZtLicense.CheckUser(eZtUB::Gredy2) || g_ZtLicense.CheckUser(eZtUB::GredyLocal))
	{
		this->ReadEvoMU(gDirPath.GetNewPath("ZtData\\User\\EvoMU.ini"));
	}
}

void CUserConfig::CheckNullNumber(int& number)
{
	if(number <= 0)
	{
		number = 1;
	}
}

void CUserConfig::ReadUsilevich(char* filename)
{
	this->m_Usilevich.DarkSideAgility = GetPrivateProfileInt("ZtTeam", "DarkSideAgility", 10, filename);
	this->m_Usilevich.ChainDriveVitality = GetPrivateProfileInt("ZtTeam", "ChainDriveVitality", 8, filename);
	this->m_Usilevich.DragonRoarEnergy = GetPrivateProfileInt("ZtTeam", "DragonRoarEnergy", 10, filename);

	this->CheckNullNumber(this->m_Usilevich.DarkSideAgility);
	this->CheckNullNumber(this->m_Usilevich.ChainDriveVitality);
	this->CheckNullNumber(this->m_Usilevich.DragonRoarEnergy);
}

void CUserConfig::ReadEvoMU(char* filename)
{
	this->m_EvoMU.CSRegTimeNeed = GetPrivateProfileInt("ZtTeam", "CSRegTimeNeed", 40000, filename);
	this->m_EvoMU.CSRegTimeMinus = GetPrivateProfileInt("ZtTeam", "CSRegTimeMinus", 4000, filename);
	this->m_EvoMU.PvpMap400LvlTpActive = GetPrivateProfileInt("ZtTeam", "PvpMap400LvlTpActive", 0, filename);
	this->m_EvoMU.PvpMap400LvlTpMap = GetPrivateProfileInt("ZtTeam", "PvpMap400LvlTpMap", 0, filename);
	this->m_EvoMU.PvpMap400LvlTpX = GetPrivateProfileInt("ZtTeam", "PvpMap400LvlTpX", 0, filename);
	this->m_EvoMU.PvpMap400LvlTpY = GetPrivateProfileInt("ZtTeam", "PvpMap400LvlTpY", 0, filename);
	this->m_EvoMU.HPAutoClicker = GetPrivateProfileInt("ZtTeam", "HPAutoClicker", 0, filename);
}

void CUserConfig::GC_SettingsSend(int aIndex)
{
	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	PMSG_USERCONFIG pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xC0, sizeof(pMsg));
	memcpy(&pMsg.EvoConfig, &this->m_EvoMU, sizeof(pMsg.EvoConfig));
	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}

