#include "StdAfx.h"
#include "user.h"
#include "ComboCustom.h"
#include "GameMain.h"
#include "ZtLicense.h"

#if(DEV_COMBO_CUSTOM==TRUE)

ComboCustom g_ComboCustom;

ComboCustom::ComboCustom()
{
	this->Init();
}

ComboCustom::~ComboCustom()
{
	// ----
}

void ComboCustom::Init()
{
	this->Enable = 0;

	this->DWComboEnable = 0;
	this->DWComboSkill_1 = 0;
	this->DWComboSkill_2 = 0;
	this->DWComboSkill_3 = 0;

	this->AEComboEnable = 0;
	this->AEComboSkill_1 = 0;
	this->AEComboSkill_2 = 0;
	this->AEComboSkill_3 = 0;

	this->SUMComboEnable = 0;
	this->SUMComboSkill_1 = 0;
	this->SUMComboSkill_2 = 0;
	this->SUMComboSkill_3 = 0;

	this->MGComboEnable = 0;
	this->MGComboSkill_1 = 0;
	this->MGComboSkill_2 = 0;
	this->MGComboSkill_3 = 0;

	this->DLComboEnable = 0;
	this->DLComboSkill_1 = 0;
	this->DLComboSkill_2 = 0;
	this->DLComboSkill_3 = 0;

	this->RFComboEnable = 0;
	this->RFComboSkill_1 = 0;
	this->RFComboSkill_2 = 0;
	this->RFComboSkill_3 = 0;

	// ----

	this->Master_DWComboSkill_1 = 0;
	this->Master_DWComboSkill_2 = 0;
	this->Master_DWComboSkill_3 = 0;

	this->Master_AEComboSkill_1 = 0;
	this->Master_AEComboSkill_2 = 0;
	this->Master_AEComboSkill_3 = 0;

	this->Master_SUMComboSkill_1 = 0;
	this->Master_SUMComboSkill_2 = 0;
	this->Master_SUMComboSkill_3 = 0;

	this->Master_MGComboSkill_1 = 0;
	this->Master_MGComboSkill_2 = 0;
	this->Master_MGComboSkill_3 = 0;

	this->Master_DLComboSkill_1 = 0;
	this->Master_DLComboSkill_2 = 0;
	this->Master_DLComboSkill_3 = 0;

	this->Master_RFComboSkill_1 = 0;
	this->Master_RFComboSkill_2 = 0;
	this->Master_RFComboSkill_3 = 0;
}

void ComboCustom::Load()
{
	this->Init();

	if(!g_ZtLicense.user.ComboCustom)
	{
		return;
	}

	this->Read(gDirPath.GetNewPath("ZtData\\ComboCustom.ini"));
}

void ComboCustom::Read(char* File)
{
	this->Enable = GetPrivateProfileInt("ZtTeam","Enable",0,File);

	this->DWComboEnable = GetPrivateProfileInt("ZtTeam","DWComboEnable",0,File);
	this->DWComboSkill_1 = GetPrivateProfileInt("ZtTeam","DWComboSkill_1",0,File);
	this->DWComboSkill_2 = GetPrivateProfileInt("ZtTeam","DWComboSkill_2",0,File);
	this->DWComboSkill_3 = GetPrivateProfileInt("ZtTeam","DWComboSkill_3",0,File);

	this->AEComboEnable = GetPrivateProfileInt("ZtTeam","AEComboEnable",0,File);
	this->AEComboSkill_1 = GetPrivateProfileInt("ZtTeam","AEComboSkill_1",0,File);
	this->AEComboSkill_2 = GetPrivateProfileInt("ZtTeam","AEComboSkill_2",0,File);
	this->AEComboSkill_3 = GetPrivateProfileInt("ZtTeam","AEComboSkill_3",0,File);

	this->SUMComboEnable = GetPrivateProfileInt("ZtTeam","SUMComboEnable",0,File);
	this->SUMComboSkill_1 = GetPrivateProfileInt("ZtTeam","SUMComboSkill_1",0,File);
	this->SUMComboSkill_2 = GetPrivateProfileInt("ZtTeam","SUMComboSkill_2",0,File);
	this->SUMComboSkill_3 = GetPrivateProfileInt("ZtTeam","SUMComboSkill_3",0,File);

	this->MGComboEnable = GetPrivateProfileInt("ZtTeam","MGComboEnable",0,File);
	this->MGComboSkill_1 = GetPrivateProfileInt("ZtTeam","MGComboSkill_1",0,File);
	this->MGComboSkill_2 = GetPrivateProfileInt("ZtTeam","MGComboSkill_2",0,File);
	this->MGComboSkill_3 = GetPrivateProfileInt("ZtTeam","MGComboSkill_3",0,File);

	this->DLComboEnable = GetPrivateProfileInt("ZtTeam","DLComboEnable",0,File);
	this->DLComboSkill_1 = GetPrivateProfileInt("ZtTeam","DLComboSkill_1",0,File);
	this->DLComboSkill_2 = GetPrivateProfileInt("ZtTeam","DLComboSkill_2",0,File);
	this->DLComboSkill_3 = GetPrivateProfileInt("ZtTeam","DLComboSkill_3",0,File);

	this->RFComboEnable = GetPrivateProfileInt("ZtTeam","RFComboEnable",0,File);
	this->RFComboSkill_1 = GetPrivateProfileInt("ZtTeam","RFComboSkill_1",0,File);
	this->RFComboSkill_2 = GetPrivateProfileInt("ZtTeam","RFComboSkill_2",0,File);
	this->RFComboSkill_3 = GetPrivateProfileInt("ZtTeam","RFComboSkill_3",0,File);

	// ----

	this->Master_DWComboSkill_1 = GetPrivateProfileInt("ZtTeam","Master_DWComboSkill_1",0,File);
	this->Master_DWComboSkill_2 = GetPrivateProfileInt("ZtTeam","Master_DWComboSkill_2",0,File);
	this->Master_DWComboSkill_3 = GetPrivateProfileInt("ZtTeam","Master_DWComboSkill_3",0,File);

	this->Master_AEComboSkill_1 = GetPrivateProfileInt("ZtTeam","Master_AEComboSkill_1",0,File);
	this->Master_AEComboSkill_2 = GetPrivateProfileInt("ZtTeam","Master_AEComboSkill_2",0,File);
	this->Master_AEComboSkill_3 = GetPrivateProfileInt("ZtTeam","Master_AEComboSkill_3",0,File);

	this->Master_SUMComboSkill_1 = GetPrivateProfileInt("ZtTeam","Master_SUMComboSkill_1",0,File);
	this->Master_SUMComboSkill_2 = GetPrivateProfileInt("ZtTeam","Master_SUMComboSkill_2",0,File);
	this->Master_SUMComboSkill_3 = GetPrivateProfileInt("ZtTeam","Master_SUMComboSkill_3",0,File);

	this->Master_MGComboSkill_1 = GetPrivateProfileInt("ZtTeam","Master_MGComboSkill_1",0,File);
	this->Master_MGComboSkill_2 = GetPrivateProfileInt("ZtTeam","Master_MGComboSkill_2",0,File);
	this->Master_MGComboSkill_3 = GetPrivateProfileInt("ZtTeam","Master_MGComboSkill_3",0,File);

	this->Master_DLComboSkill_1 = GetPrivateProfileInt("ZtTeam","Master_DLComboSkill_1",0,File);
	this->Master_DLComboSkill_2 = GetPrivateProfileInt("ZtTeam","Master_DLComboSkill_2",0,File);
	this->Master_DLComboSkill_3 = GetPrivateProfileInt("ZtTeam","Master_DLComboSkill_3",0,File);

	this->Master_RFComboSkill_1 = GetPrivateProfileInt("ZtTeam","Master_RFComboSkill_1",0,File);
	this->Master_RFComboSkill_2 = GetPrivateProfileInt("ZtTeam","Master_RFComboSkill_2",0,File);
	this->Master_RFComboSkill_3 = GetPrivateProfileInt("ZtTeam","Master_RFComboSkill_3",0,File);
}

int ComboCustom::Main(int aIndex, int skillnumber)
{
	if(!this->Enable)
	{
		return -2;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(g_ZtLicense.CheckUser(eZtUB::NSGames))
	{
		if(!lpObj->ChangeUP3rd)
		{
			return -2;
		}
	}

	switch(lpObj->Class)
	{
	case CLASS_WIZARD:
		{
			return this->DarkWizard(skillnumber);
		}
		break;
	case CLASS_KNIGHT:
		{
			//return this->DarkKnight(skillnumber);
			return -2;
		}
		break;
	case CLASS_ELF:
		{
			return this->Elf(skillnumber);
		}
		break;
	case CLASS_MAGUMSA:
		{
			return this->MagicGladiator(skillnumber);
		}
		break;
	case CLASS_DARKLORD:
		{
			return this->DarkLord(skillnumber);
		}
		break;
	case CLASS_SUMMONER:
		{
			return this->Summoner(skillnumber);
		}
		break;
	case CLASS_MONK:
		{
			return this->RageFighter(skillnumber);
		}
		break;
	}
}

int ComboCustom::DarkWizard(int skillnumber)
{
	if(!this->DWComboEnable)
	{
		return -1;
	}

	if(skillnumber == this->DWComboSkill_1)
	{
		return 0;
	}
	else if(skillnumber == this->DWComboSkill_2)
	{
		return 1;
	}
	else if(skillnumber == this->DWComboSkill_3)
	{
		return 1;
	}

	if(skillnumber == this->Master_DWComboSkill_1)
	{
		return 0;
	}
	else if(skillnumber == this->Master_DWComboSkill_2)
	{
		return 1;
	}
	else if(skillnumber == this->Master_DWComboSkill_3)
	{
		return 1;
	}

	return -1;
}

int ComboCustom::Elf(int skillnumber)
{
	if(!this->AEComboEnable)
	{
		return -1;
	}

	if(skillnumber == this->AEComboSkill_1)
	{
		return 0;
	}
	else if(skillnumber == this->AEComboSkill_2)
	{
		return 1;
	}
	else if(skillnumber == this->AEComboSkill_3)
	{
		return 1;
	}

	if(skillnumber == this->Master_AEComboSkill_1)
	{
		return 0;
	}
	else if(skillnumber == this->Master_AEComboSkill_2)
	{
		return 1;
	}
	else if(skillnumber == this->Master_AEComboSkill_3)
	{
		return 1;
	}

	return -1;
}

int ComboCustom::Summoner(int skillnumber)
{
	if(!this->SUMComboEnable)
	{
		return -1;
	}

	if(skillnumber == this->SUMComboSkill_1)
	{
		return 0;
	}
	else if(skillnumber == this->SUMComboSkill_2)
	{
		return 1;
	}
	else if(skillnumber == this->SUMComboSkill_3)
	{
		return 1;
	}

	if(skillnumber == this->Master_SUMComboSkill_1)
	{
		return 0;
	}
	else if(skillnumber == this->Master_SUMComboSkill_2)
	{
		return 1;
	}
	else if(skillnumber == this->Master_SUMComboSkill_3)
	{
		return 1;
	}

	return -1;
}

int ComboCustom::MagicGladiator(int skillnumber)
{
	if(!this->MGComboEnable)
	{
		return -1;
	}

	if(skillnumber == this->MGComboSkill_1)
	{
		return 0;
	}
	else if(skillnumber == this->MGComboSkill_2)
	{
		return 1;
	}
	else if(skillnumber == this->MGComboSkill_3)
	{
		return 1;
	}

	if(skillnumber == this->Master_MGComboSkill_1)
	{
		return 0;
	}
	else if(skillnumber == this->Master_MGComboSkill_2)
	{
		return 1;
	}
	else if(skillnumber == this->Master_MGComboSkill_3)
	{
		return 1;
	}

	return -1;
}

int ComboCustom::DarkLord(int skillnumber)
{
	if(!this->DLComboEnable)
	{
		return -1;
	}

	if(skillnumber == this->DLComboSkill_1)
	{
		return 0;
	}
	else if(skillnumber == this->DLComboSkill_2)
	{
		return 1;
	}
	else if(skillnumber == this->DLComboSkill_3)
	{
		return 1;
	}

	if(skillnumber == this->Master_DLComboSkill_1)
	{
		return 0;
	}
	else if(skillnumber == this->Master_DLComboSkill_2)
	{
		return 1;
	}
	else if(skillnumber == this->Master_DLComboSkill_3)
	{
		return 1;
	}

	return -1;
}

int ComboCustom::RageFighter(int skillnumber)
{
	if(!this->RFComboEnable)
	{
		return -1;
	}

	if(skillnumber == this->RFComboSkill_1)
	{
		return 0;
	}
	else if(skillnumber == this->RFComboSkill_2)
	{
		return 1;
	}
	else if(skillnumber == this->RFComboSkill_3)
	{
		return 1;
	}

	if(skillnumber == this->Master_RFComboSkill_1)
	{
		return 0;
	}
	else if(skillnumber == this->Master_RFComboSkill_2)
	{
		return 1;
	}
	else if(skillnumber == this->Master_RFComboSkill_3)
	{
		return 1;
	}

	return -1;
}

#endif