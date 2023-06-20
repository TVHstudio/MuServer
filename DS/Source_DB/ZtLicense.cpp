#include "StdAfx.h"
#include "ZtLicense.h"
// ----------------------------------------------------------------------------------------------

#if(ZT_LICENSE==TRUE)

CZtLicense g_ZtLicense;
// ----------------------------------------------------------------------------------------------

CZtLicense::CZtLicense()
{
	this->Init();
}
// ----------------------------------------------------------------------------------------------

CZtLicense::~CZtLicense()
{
}
// ----------------------------------------------------------------------------------------------

void CZtLicense::Init()
{
	this->Enable = true;

	this->TEXTXoR[0] = 0x03;
	this->TEXTXoR[1] = 0x05;
	this->TEXTXoR[2] = 0x08;

	this->URLXoR[0] = 0xA9;
	this->URLXoR[1] = 0xB3;
	this->URLXoR[2] = 0x18;

	this->ActiveUser = -1;
}
// ----------------------------------------------------------------------------------------------

void CZtLicense::Load()
{
	this->Init();
}
// ----------------------------------------------------------------------------------------------

void CZtLicense::GDLicenseUser(PMSG_LICENSE_DATA* aRecv)
{
	this->ActiveUser = aRecv->LicenseUser;
	this->m_SetCustom = aRecv->LicenseCustom;
	memcpy(&this->user,&aRecv->base,sizeof(this->user));
	memcpy(&this->config,&aRecv->config,sizeof(this->config));
}
// ----------------------------------------------------------------------------------------------

bool CZtLicense::CheckUser(int NeedUser)
{
	if(this->ActiveUser == NeedUser)
	{
		return true;
	}
	return false;
}
// ----------------------------------------------------------------------------------------------

char* CZtLicense::GetDecText(char* EncodeChar)
{
	int len = strlen(EncodeChar);	
	char* Line = new char[len+1];
	for(int i = 0; i < len; i++)
	{
		Line[i] = char(EncodeChar[i] ^ this->TEXTXoR[i % 3]);
	}
	Line[len] = 0;
	return Line;
}
// ----------------------------------------------------------------------------------------------

#endif