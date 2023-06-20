#include "StdAfx.h"
#include "MaxPower.h"
#include "user.h"
#include "ZtFunction.h"

cMaxPower gMaxPower;

void cMaxPower::Load()
{

	//CheckFile(MaxPower_Dir);

	this->Enable = GetPrivateProfileInt("ZtTeam","Enable",0,MaxPower_Dir);

	//-> DK
	this->MaxDamageDK = GetPrivateProfileInt("ZtTeam","MaxDamageDK",0,MaxPower_Dir);
	this->MaxDefenceDK = GetPrivateProfileInt("ZtTeam","MaxDefenceDK",0,MaxPower_Dir);
	this->MaxIgnoreDefenceRateDK = GetPrivateProfileInt("ZtTeam","MaxIgnoreDefenceRateDK",0,MaxPower_Dir);
	this->MaxCriticalDamageRateDK = GetPrivateProfileInt("ZtTeam","MaxCriticalDamageRateDK",0,MaxPower_Dir);
	this->MaxExellentDamageRateDK = GetPrivateProfileInt("ZtTeam","MaxExellentDamageRateDK",0,MaxPower_Dir);
	this->MaxDoubleDamageRateDK = GetPrivateProfileInt("ZtTeam","MaxDoubleDamageRateDK",0,MaxPower_Dir);
	this->MaxAbsordDamageRateDK = GetPrivateProfileInt("ZtTeam","MaxAbsordDamageRateDK",0,MaxPower_Dir);
	this->MaxReflectDamageRateDK = GetPrivateProfileInt("ZtTeam","MaxReflectDamageRateDK",0,MaxPower_Dir);
	this->MaxWizardDamageDK = GetPrivateProfileInt("ZtTeam","MaxWizardDamageDK",0,MaxPower_Dir);
	this->MaxLifeDK = GetPrivateProfileInt("ZtTeam","MaxLifeDK",0,MaxPower_Dir);
	this->MaxSdDK = GetPrivateProfileInt("ZtTeam","MaxSdDK",0,MaxPower_Dir);

	//-> DW
	this->MaxDamageDW = GetPrivateProfileInt("ZtTeam","MaxDamageDW",0,MaxPower_Dir);
	this->MaxDefenceDW = GetPrivateProfileInt("ZtTeam","MaxDefenceDW",0,MaxPower_Dir);
	this->MaxIgnoreDefenceRateDW = GetPrivateProfileInt("ZtTeam","MaxIgnoreDefenceRateDW",0,MaxPower_Dir);
	this->MaxCriticalDamageRateDW = GetPrivateProfileInt("ZtTeam","MaxCriticalDamageRateDW",0,MaxPower_Dir);
	this->MaxExellentDamageRateDW = GetPrivateProfileInt("ZtTeam","MaxExellentDamageRateDW",0,MaxPower_Dir);
	this->MaxDoubleDamageRateDW = GetPrivateProfileInt("ZtTeam","MaxDoubleDamageRateDW",0,MaxPower_Dir);
	this->MaxAbsordDamageRateDW = GetPrivateProfileInt("ZtTeam","MaxAbsordDamageRateDW",0,MaxPower_Dir);
	this->MaxReflectDamageRateDW = GetPrivateProfileInt("ZtTeam","MaxReflectDamageRateDW",0,MaxPower_Dir);
	this->MaxWizardDamageDW = GetPrivateProfileInt("ZtTeam","MaxWizardDamageDW",0,MaxPower_Dir);
	this->MaxLifeDW = GetPrivateProfileInt("ZtTeam","MaxLifeDW",0,MaxPower_Dir);
	this->MaxSdDW = GetPrivateProfileInt("ZtTeam","MaxSdDW",0,MaxPower_Dir);

	//-> Elf
	this->MaxDamageElf = GetPrivateProfileInt("ZtTeam","MaxDamageElf",0,MaxPower_Dir);
	this->MaxDefenceElf = GetPrivateProfileInt("ZtTeam","MaxDefenceElf",0,MaxPower_Dir);
	this->MaxIgnoreDefenceRateElf = GetPrivateProfileInt("ZtTeam","MaxIgnoreDefenceRateElf",0,MaxPower_Dir);
	this->MaxCriticalDamageRateElf = GetPrivateProfileInt("ZtTeam","MaxCriticalDamageRateElf",0,MaxPower_Dir);
	this->MaxExellentDamageRateElf = GetPrivateProfileInt("ZtTeam","MaxExellentDamageRateElf",0,MaxPower_Dir);
	this->MaxDoubleDamageRateElf = GetPrivateProfileInt("ZtTeam","MaxDoubleDamageRateElf",0,MaxPower_Dir);
	this->MaxAbsordDamageRateElf = GetPrivateProfileInt("ZtTeam","MaxAbsordDamageRateElf",0,MaxPower_Dir);
	this->MaxReflectDamageRateElf = GetPrivateProfileInt("ZtTeam","MaxReflectDamageRateElf",0,MaxPower_Dir);
	this->MaxWizardDamageElf = GetPrivateProfileInt("ZtTeam","MaxWizardDamageElf",0,MaxPower_Dir);
	this->MaxLifeElf = GetPrivateProfileInt("ZtTeam","MaxLifeElf",0,MaxPower_Dir);
	this->MaxSdElf = GetPrivateProfileInt("ZtTeam","MaxSdElf",0,MaxPower_Dir);

	//-> MG
	this->MaxDamageMG = GetPrivateProfileInt("ZtTeam","MaxDamageMG",0,MaxPower_Dir);
	this->MaxDefenceMG = GetPrivateProfileInt("ZtTeam","MaxDefenceMG",0,MaxPower_Dir);
	this->MaxIgnoreDefenceRateMG = GetPrivateProfileInt("ZtTeam","MaxIgnoreDefenceRateMG",0,MaxPower_Dir);
	this->MaxCriticalDamageRateMG = GetPrivateProfileInt("ZtTeam","MaxCriticalDamageRateMG",0,MaxPower_Dir);
	this->MaxExellentDamageRateMG = GetPrivateProfileInt("ZtTeam","MaxExellentDamageRateMG",0,MaxPower_Dir);
	this->MaxDoubleDamageRateMG = GetPrivateProfileInt("ZtTeam","MaxDoubleDamageRateMG",0,MaxPower_Dir);
	this->MaxAbsordDamageRateMG = GetPrivateProfileInt("ZtTeam","MaxAbsordDamageRateMG",0,MaxPower_Dir);
	this->MaxReflectDamageRateMG = GetPrivateProfileInt("ZtTeam","MaxReflectDamageRateMG",0,MaxPower_Dir);
	this->MaxWizardDamageMG = GetPrivateProfileInt("ZtTeam","MaxWizardDamageMG",0,MaxPower_Dir);
	this->MaxLifeMG = GetPrivateProfileInt("ZtTeam","MaxLifeMG",0,MaxPower_Dir);
	this->MaxSdMG = GetPrivateProfileInt("ZtTeam","MaxSdMG",0,MaxPower_Dir);

	//-> DL
	this->MaxDamageDL = GetPrivateProfileInt("ZtTeam","MaxDamageDL",0,MaxPower_Dir);
	this->MaxDefenceDL = GetPrivateProfileInt("ZtTeam","MaxDefenceDL",0,MaxPower_Dir);
	this->MaxIgnoreDefenceRateDL = GetPrivateProfileInt("ZtTeam","MaxIgnoreDefenceRateDL",0,MaxPower_Dir);
	this->MaxCriticalDamageRateDL = GetPrivateProfileInt("ZtTeam","MaxCriticalDamageRateDL",0,MaxPower_Dir);
	this->MaxExellentDamageRateDL = GetPrivateProfileInt("ZtTeam","MaxExellentDamageRateDL",0,MaxPower_Dir);
	this->MaxDoubleDamageRateDL = GetPrivateProfileInt("ZtTeam","MaxDoubleDamageRateDL",0,MaxPower_Dir);
	this->MaxAbsordDamageRateDL = GetPrivateProfileInt("ZtTeam","MaxAbsordDamageRateDL",0,MaxPower_Dir);
	this->MaxReflectDamageRateDL = GetPrivateProfileInt("ZtTeam","MaxReflectDamageRateDL",0,MaxPower_Dir);
	this->MaxWizardDamageDL = GetPrivateProfileInt("ZtTeam","MaxWizardDamageDL",0,MaxPower_Dir);
	this->MaxLifeDL = GetPrivateProfileInt("ZtTeam","MaxLifeDL",0,MaxPower_Dir);
	this->MaxSdDL = GetPrivateProfileInt("ZtTeam","MaxSdDL",0,MaxPower_Dir);

	//-> SUM
	this->MaxDamageSUM = GetPrivateProfileInt("ZtTeam","MaxDamageSUM",0,MaxPower_Dir);
	this->MaxDefenceSUM = GetPrivateProfileInt("ZtTeam","MaxDefenceSUM",0,MaxPower_Dir);
	this->MaxIgnoreDefenceRateSUM = GetPrivateProfileInt("ZtTeam","MaxIgnoreDefenceRateSUM",0,MaxPower_Dir);
	this->MaxCriticalDamageRateSUM = GetPrivateProfileInt("ZtTeam","MaxCriticalDamageRateSUM",0,MaxPower_Dir);
	this->MaxExellentDamageRateSUM = GetPrivateProfileInt("ZtTeam","MaxExellentDamageRateSUM",0,MaxPower_Dir);
	this->MaxDoubleDamageRateSUM = GetPrivateProfileInt("ZtTeam","MaxDoubleDamageRateSUM",0,MaxPower_Dir);
	this->MaxAbsordDamageRateSUM = GetPrivateProfileInt("ZtTeam","MaxAbsordDamageRateSUM",0,MaxPower_Dir);
	this->MaxReflectDamageRateSUM = GetPrivateProfileInt("ZtTeam","MaxReflectDamageRateSUM",0,MaxPower_Dir);
	this->MaxWizardDamageSUM = GetPrivateProfileInt("ZtTeam","MaxWizardDamageSUM",0,MaxPower_Dir);
	this->MaxLifeSUM = GetPrivateProfileInt("ZtTeam","MaxLifeSUM",0,MaxPower_Dir);
	this->MaxSdSUM = GetPrivateProfileInt("ZtTeam","MaxSdSUM",0,MaxPower_Dir);

	//-> RF
	this->MaxDamageRF = GetPrivateProfileInt("ZtTeam","MaxDamageRF",0,MaxPower_Dir);
	this->MaxDefenceRF = GetPrivateProfileInt("ZtTeam","MaxDefenceRF",0,MaxPower_Dir);
	this->MaxIgnoreDefenceRateRF = GetPrivateProfileInt("ZtTeam","MaxIgnoreDefenceRateRF",0,MaxPower_Dir);
	this->MaxCriticalDamageRateRF = GetPrivateProfileInt("ZtTeam","MaxCriticalDamageRateRF",0,MaxPower_Dir);
	this->MaxExellentDamageRateRF = GetPrivateProfileInt("ZtTeam","MaxExellentDamageRateRF",0,MaxPower_Dir);
	this->MaxDoubleDamageRateRF = GetPrivateProfileInt("ZtTeam","MaxDoubleDamageRateRF",0,MaxPower_Dir);
	this->MaxAbsordDamageRateRF = GetPrivateProfileInt("ZtTeam","MaxAbsordDamageRateRF",0,MaxPower_Dir);
	this->MaxReflectDamageRateRF = GetPrivateProfileInt("ZtTeam","MaxReflectDamageRateRF",0,MaxPower_Dir);
	this->MaxWizardDamageRF = GetPrivateProfileInt("ZtTeam","MaxWizardDamageRF",0,MaxPower_Dir);
	this->MaxLifeRF = GetPrivateProfileInt("ZtTeam","MaxLifeRF",0,MaxPower_Dir);
	this->MaxSdRF = GetPrivateProfileInt("ZtTeam","MaxSdRF",0,MaxPower_Dir);
}

void cMaxPower::Main(int aIndex)
{
	if(!this->Enable) return;

	LPOBJ lpObj = &gObj[aIndex];

	switch(lpObj->Class)
	{
	case CLASS_WIZARD:
		{
			this->DW(aIndex);
		}
		break;
	case CLASS_KNIGHT:
		{
			this->DK(aIndex);
		}
		break;
	case CLASS_ELF:
		{
			this->Elf(aIndex);
		}
		break;
	case CLASS_MAGUMSA:
		{
			this->MG(aIndex);
		}
		break;
	case CLASS_DARKLORD:
		{
			this->DL(aIndex);
		}
		break;
	case CLASS_SUMMONER:
		{
			this->SUM(aIndex);
		}
		break;
	case CLASS_MONK:
		{
			this->RF(aIndex);
		}
		break;
	}
}

void cMaxPower::DK(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];

	if(this->MaxDamageDK != -1)
	{
		if(lpObj->m_AttackDamageMaxRight > this->MaxDamageDK || lpObj->m_AttackDamageMaxLeft > this->MaxDamageDK)
		{
			lpObj->m_AttackDamageMinRight = this->MaxDamageDK;
			lpObj->m_AttackDamageMaxRight = this->MaxDamageDK;
			lpObj->m_AttackDamageMinLeft = this->MaxDamageDK;
			lpObj->m_AttackDamageMaxLeft = this->MaxDamageDK;
		}
	}

	if(this->MaxDefenceDK != -1)
	{
		if(lpObj->m_Defense > this->MaxDefenceDK)
		{
			lpObj->m_Defense = this->MaxDefenceDK;
		}
	}

	if(this->MaxIgnoreDefenceRateDK != -1)
	{
		if(lpObj->SetOpIgnoreDefense > this->MaxIgnoreDefenceRateDK)
		{
			lpObj->SetOpIgnoreDefense = this->MaxIgnoreDefenceRateDK;
		}
	}

	if(this->MaxCriticalDamageRateDK != -1)
	{
		if(lpObj->m_CriticalDamage > this->MaxCriticalDamageRateDK)
		{
			lpObj->m_CriticalDamage = this->MaxCriticalDamageRateDK;
		}
	}

	if(this->MaxExellentDamageRateDK != -1)
	{
		if(lpObj->m_ExcelentDamage > this->MaxExellentDamageRateDK)
		{
			lpObj->m_ExcelentDamage = this->MaxExellentDamageRateDK;
		}
	}

	if(this->MaxDoubleDamageRateDK != -1)
	{
		if(lpObj->SetOpDoubleDamage > this->MaxDoubleDamageRateDK)
		{
			lpObj->SetOpDoubleDamage = this->MaxDoubleDamageRateDK;
		}
	}

	if(this->MaxAbsordDamageRateDK != -1)
	{
		if(lpObj->DamageMinus > this->MaxAbsordDamageRateDK)
		{
			lpObj->DamageMinus = this->MaxAbsordDamageRateDK;
		}
	}

	if(this->MaxReflectDamageRateDK != -1)
	{
		if(lpObj->DamageReflect > this->MaxReflectDamageRateDK)
		{
			lpObj->DamageReflect = this->MaxReflectDamageRateDK;
		}
	}

	if(this->MaxWizardDamageDK != -1)
	{
		if(lpObj->m_MagicDamageMax > this->MaxWizardDamageDK)
		{
			lpObj->m_MagicDamageMax = this->MaxWizardDamageDK;
			lpObj->m_MagicDamageMin = this->MaxWizardDamageDK;
		}
	}

	if(this->MaxLifeDK != -1)
	{
		if( lpObj->Life > this->MaxLifeDK)
		{
			lpObj->Life = this->MaxLifeDK;
		}
	}

	if(this->MaxSdDK != -1)
	{
		if( lpObj->iShield > this->MaxSdDK)
		{
			lpObj->iShield = this->MaxSdDK;
		}
	}
}

void cMaxPower::DW(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];

	if(this->MaxDamageDW != -1)
	{
		if(lpObj->m_AttackDamageMaxRight > this->MaxDamageDW || lpObj->m_AttackDamageMaxLeft > this->MaxDamageDW)
		{
			lpObj->m_AttackDamageMinRight = this->MaxDamageDW;
			lpObj->m_AttackDamageMaxRight = this->MaxDamageDW;
			lpObj->m_AttackDamageMinLeft = this->MaxDamageDW;
			lpObj->m_AttackDamageMaxLeft = this->MaxDamageDW;
		}
	}

	if(this->MaxDefenceDW != -1)
	{
		if(lpObj->m_Defense > this->MaxDefenceDW)
		{
			lpObj->m_Defense = this->MaxDefenceDW;
		}
	}

	if(this->MaxIgnoreDefenceRateDW != -1)
	{
		if(lpObj->SetOpIgnoreDefense > this->MaxIgnoreDefenceRateDW)
		{
			lpObj->SetOpIgnoreDefense = this->MaxIgnoreDefenceRateDW;
		}
	}

	if(this->MaxCriticalDamageRateDW != -1)
	{
		if(lpObj->m_CriticalDamage > this->MaxCriticalDamageRateDW)
		{
			lpObj->m_CriticalDamage = this->MaxCriticalDamageRateDW;
		}
	}

	if(this->MaxExellentDamageRateDW != -1)
	{
		if(lpObj->m_ExcelentDamage > this->MaxExellentDamageRateDW)
		{
			lpObj->m_ExcelentDamage = this->MaxExellentDamageRateDW;
		}
	}

	if(this->MaxDoubleDamageRateDW != -1)
	{
		if(lpObj->SetOpDoubleDamage > this->MaxDoubleDamageRateDW)
		{
			lpObj->SetOpDoubleDamage = this->MaxDoubleDamageRateDW;
		}
	}

	if(this->MaxAbsordDamageRateDW != -1)
	{
		if(lpObj->DamageMinus > this->MaxAbsordDamageRateDW)
		{
			lpObj->DamageMinus = this->MaxAbsordDamageRateDW;
		}
	}

	if(this->MaxReflectDamageRateDW != -1)
	{
		if(lpObj->DamageReflect > this->MaxReflectDamageRateDW)
		{
			lpObj->DamageReflect = this->MaxReflectDamageRateDW;
		}
	}

	if(this->MaxWizardDamageDW != -1)
	{
		if(lpObj->m_MagicDamageMax > this->MaxWizardDamageDW)
		{
			lpObj->m_MagicDamageMax = this->MaxWizardDamageDW;
			lpObj->m_MagicDamageMin = this->MaxWizardDamageDW;
		}
	}

	if(this->MaxLifeDW != -1)
	{
		if( lpObj->Life > this->MaxLifeDW)
		{
			lpObj->Life = this->MaxLifeDW;
		}
	}

	if(this->MaxSdDW != -1)
	{
		if( lpObj->iShield > this->MaxSdDW)
		{
			lpObj->iShield = this->MaxSdDW;
		}
	}
}

void cMaxPower::Elf(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];

	if(this->MaxDamageElf != -1)
	{
		if(lpObj->m_AttackDamageMaxRight > this->MaxDamageElf || lpObj->m_AttackDamageMaxLeft > this->MaxDamageElf)
		{
			lpObj->m_AttackDamageMinRight = this->MaxDamageElf;
			lpObj->m_AttackDamageMaxRight = this->MaxDamageElf;
			lpObj->m_AttackDamageMinLeft = this->MaxDamageElf;
			lpObj->m_AttackDamageMaxLeft = this->MaxDamageElf;
		}
	}

	if(this->MaxDefenceElf != -1)
	{
		if(lpObj->m_Defense > this->MaxDefenceElf)
		{
			lpObj->m_Defense = this->MaxDefenceElf;
		}
	}

	if(this->MaxIgnoreDefenceRateElf != -1)
	{
		if(lpObj->SetOpIgnoreDefense > this->MaxIgnoreDefenceRateElf)
		{
			lpObj->SetOpIgnoreDefense = this->MaxIgnoreDefenceRateElf;
		}
	}

	if(this->MaxCriticalDamageRateElf != -1)
	{
		if(lpObj->m_CriticalDamage > this->MaxCriticalDamageRateElf)
		{
			lpObj->m_CriticalDamage = this->MaxCriticalDamageRateElf;
		}
	}

	if(this->MaxExellentDamageRateElf != -1)
	{
		if(lpObj->m_ExcelentDamage > this->MaxExellentDamageRateElf)
		{
			lpObj->m_ExcelentDamage = this->MaxExellentDamageRateElf;
		}
	}

	if(this->MaxDoubleDamageRateElf != -1)
	{
		if(lpObj->SetOpDoubleDamage > this->MaxDoubleDamageRateElf)
		{
			lpObj->SetOpDoubleDamage = this->MaxDoubleDamageRateElf;
		}
	}

	if(this->MaxAbsordDamageRateElf != -1)
	{
		if(lpObj->DamageMinus > this->MaxAbsordDamageRateElf)
		{
			lpObj->DamageMinus = this->MaxAbsordDamageRateElf;
		}
	}

	if(this->MaxReflectDamageRateElf != -1)
	{
		if(lpObj->DamageReflect > this->MaxReflectDamageRateElf)
		{
			lpObj->DamageReflect = this->MaxReflectDamageRateElf;
		}
	}

	if(this->MaxWizardDamageElf != -1)
	{
		if(lpObj->m_MagicDamageMax > this->MaxWizardDamageElf)
		{
			lpObj->m_MagicDamageMax = this->MaxWizardDamageElf;
			lpObj->m_MagicDamageMin = this->MaxWizardDamageElf;
		}
	}

	if(this->MaxLifeElf != -1)
	{
		if( lpObj->Life > this->MaxLifeElf)
		{
			lpObj->Life = this->MaxLifeElf;
		}
	}

	if(this->MaxSdElf != -1)
	{
		if( lpObj->iShield > this->MaxSdElf)
		{
			lpObj->iShield = this->MaxSdElf;
		}
	}
}

void cMaxPower::MG(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];

	if(this->MaxDamageMG != -1)
	{
		if(lpObj->m_AttackDamageMaxRight > this->MaxDamageMG || lpObj->m_AttackDamageMaxLeft > this->MaxDamageMG)
		{
			lpObj->m_AttackDamageMinRight = this->MaxDamageMG;
			lpObj->m_AttackDamageMaxRight = this->MaxDamageMG;
			lpObj->m_AttackDamageMinLeft = this->MaxDamageMG;
			lpObj->m_AttackDamageMaxLeft = this->MaxDamageMG;
		}
	}

	if(this->MaxDefenceMG != -1)
	{
		if(lpObj->m_Defense > this->MaxDefenceMG)
		{
			lpObj->m_Defense = this->MaxDefenceMG;
		}
	}

	if(this->MaxIgnoreDefenceRateMG != -1)
	{
		if(lpObj->SetOpIgnoreDefense > this->MaxIgnoreDefenceRateMG)
		{
			lpObj->SetOpIgnoreDefense = this->MaxIgnoreDefenceRateMG;
		}
	}

	if(this->MaxCriticalDamageRateMG != -1)
	{
		if(lpObj->m_CriticalDamage > this->MaxCriticalDamageRateMG)
		{
			lpObj->m_CriticalDamage = this->MaxCriticalDamageRateMG;
		}
	}

	if(this->MaxExellentDamageRateMG != -1)
	{
		if(lpObj->m_ExcelentDamage > this->MaxExellentDamageRateMG)
		{
			lpObj->m_ExcelentDamage = this->MaxExellentDamageRateMG;
		}
	}

	if(this->MaxDoubleDamageRateMG != -1)
	{
		if(lpObj->SetOpDoubleDamage > this->MaxDoubleDamageRateMG)
		{
			lpObj->SetOpDoubleDamage = this->MaxDoubleDamageRateMG;
		}
	}

	if(this->MaxAbsordDamageRateMG != -1)
	{
		if(lpObj->DamageMinus > this->MaxAbsordDamageRateMG)
		{
			lpObj->DamageMinus = this->MaxAbsordDamageRateMG;
		}
	}

	if(this->MaxReflectDamageRateMG != -1)
	{
		if(lpObj->DamageReflect > this->MaxReflectDamageRateMG)
		{
			lpObj->DamageReflect = this->MaxReflectDamageRateMG;
		}
	}

	if(this->MaxWizardDamageMG != -1)
	{
		if(lpObj->m_MagicDamageMax > this->MaxWizardDamageMG)
		{
			lpObj->m_MagicDamageMax = this->MaxWizardDamageMG;
			lpObj->m_MagicDamageMin = this->MaxWizardDamageMG;
		}
	}

	if(this->MaxLifeMG != -1)
	{
		if( lpObj->Life > this->MaxLifeMG)
		{
			lpObj->Life = this->MaxLifeMG;
		}
	}

	if(this->MaxSdMG != -1)
	{
		if( lpObj->iShield > this->MaxSdMG)
		{
			lpObj->iShield = this->MaxSdMG;
		}
	}
}

void cMaxPower::DL(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];

	if(this->MaxDamageDL != -1)
	{
		if(lpObj->m_AttackDamageMaxRight > this->MaxDamageDL || lpObj->m_AttackDamageMaxLeft > this->MaxDamageDL)
		{
			lpObj->m_AttackDamageMinRight = this->MaxDamageDL;
			lpObj->m_AttackDamageMaxRight = this->MaxDamageDL;
			lpObj->m_AttackDamageMinLeft = this->MaxDamageDL;
			lpObj->m_AttackDamageMaxLeft = this->MaxDamageDL;
		}
	}

	if(this->MaxDefenceDL != -1)
	{
		if(lpObj->m_Defense > this->MaxDefenceDL)
		{
			lpObj->m_Defense = this->MaxDefenceDL;
		}
	}

	if(this->MaxIgnoreDefenceRateDL != -1)
	{
		if(lpObj->SetOpIgnoreDefense > this->MaxIgnoreDefenceRateDL)
		{
			lpObj->SetOpIgnoreDefense = this->MaxIgnoreDefenceRateDL;
		}
	}

	if(this->MaxCriticalDamageRateDL != -1)
	{
		if(lpObj->m_CriticalDamage > this->MaxCriticalDamageRateDL)
		{
			lpObj->m_CriticalDamage = this->MaxCriticalDamageRateDL;
		}
	}

	if(this->MaxExellentDamageRateDL != -1)
	{
		if(lpObj->m_ExcelentDamage > this->MaxExellentDamageRateDL)
		{
			lpObj->m_ExcelentDamage = this->MaxExellentDamageRateDL;
		}
	}

	if(this->MaxDoubleDamageRateDL != -1)
	{
		if(lpObj->SetOpDoubleDamage > this->MaxDoubleDamageRateDL)
		{
			lpObj->SetOpDoubleDamage = this->MaxDoubleDamageRateDL;
		}
	}

	if(this->MaxAbsordDamageRateDL != -1)
	{
		if(lpObj->DamageMinus > this->MaxAbsordDamageRateDL)
		{
			lpObj->DamageMinus = this->MaxAbsordDamageRateDL;
		}
	}

	if(this->MaxReflectDamageRateDL != -1)
	{
		if(lpObj->DamageReflect > this->MaxReflectDamageRateDL)
		{
			lpObj->DamageReflect = this->MaxReflectDamageRateDL;
		}
	}

	if(this->MaxWizardDamageDL != -1)
	{
		if(lpObj->m_MagicDamageMax > this->MaxWizardDamageDL)
		{
			lpObj->m_MagicDamageMax = this->MaxWizardDamageDL;
			lpObj->m_MagicDamageMin = this->MaxWizardDamageDL;
		}
	}

	if(this->MaxLifeDL != -1)
	{
		if( lpObj->Life > this->MaxLifeDL)
		{
			lpObj->Life = this->MaxLifeDL;
		}
	}

	if(this->MaxSdDL != -1)
	{
		if( lpObj->iShield > this->MaxSdDL)
		{
			lpObj->iShield = this->MaxSdDL;
		}
	}
}

void cMaxPower::SUM(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];

	if(this->MaxDamageSUM != -1)
	{
		if(lpObj->m_AttackDamageMaxRight > this->MaxDamageSUM || lpObj->m_AttackDamageMaxLeft > this->MaxDamageSUM)
		{
			lpObj->m_AttackDamageMinRight = this->MaxDamageSUM;
			lpObj->m_AttackDamageMaxRight = this->MaxDamageSUM;
			lpObj->m_AttackDamageMinLeft = this->MaxDamageSUM;
			lpObj->m_AttackDamageMaxLeft = this->MaxDamageSUM;
		}
	}

	if(this->MaxDefenceSUM != -1)
	{
		if(lpObj->m_Defense > this->MaxDefenceSUM)
		{
			lpObj->m_Defense = this->MaxDefenceSUM;
		}
	}

	if(this->MaxIgnoreDefenceRateSUM != -1)
	{
		if(lpObj->SetOpIgnoreDefense > this->MaxIgnoreDefenceRateSUM)
		{
			lpObj->SetOpIgnoreDefense = this->MaxIgnoreDefenceRateSUM;
		}
	}

	if(this->MaxCriticalDamageRateSUM != -1)
	{
		if(lpObj->m_CriticalDamage > this->MaxCriticalDamageRateSUM)
		{
			lpObj->m_CriticalDamage = this->MaxCriticalDamageRateSUM;
		}
	}

	if(this->MaxExellentDamageRateSUM != -1)
	{
		if(lpObj->m_ExcelentDamage > this->MaxExellentDamageRateSUM)
		{
			lpObj->m_ExcelentDamage = this->MaxExellentDamageRateSUM;
		}
	}

	if(this->MaxDoubleDamageRateSUM != -1)
	{
		if(lpObj->SetOpDoubleDamage > this->MaxDoubleDamageRateSUM)
		{
			lpObj->SetOpDoubleDamage = this->MaxDoubleDamageRateSUM;
		}
	}

	if(this->MaxAbsordDamageRateSUM != -1)
	{
		if(lpObj->DamageMinus > this->MaxAbsordDamageRateSUM)
		{
			lpObj->DamageMinus = this->MaxAbsordDamageRateSUM;
		}
	}

	if(this->MaxReflectDamageRateSUM != -1)
	{
		if(lpObj->DamageReflect > this->MaxReflectDamageRateSUM)
		{
			lpObj->DamageReflect = this->MaxReflectDamageRateSUM;
		}
	}

	if(this->MaxWizardDamageSUM != -1)
	{
		if(lpObj->m_MagicDamageMax > this->MaxWizardDamageSUM)
		{
			lpObj->m_MagicDamageMax = this->MaxWizardDamageSUM;
			lpObj->m_MagicDamageMin = this->MaxWizardDamageSUM;
		}
	}

	if(this->MaxLifeSUM != -1)
	{
		if( lpObj->Life > this->MaxLifeSUM)
		{
			lpObj->Life = this->MaxLifeSUM;
		}
	}

	if(this->MaxSdSUM != -1)
	{
		if( lpObj->iShield > this->MaxSdSUM)
		{
			lpObj->iShield = this->MaxSdSUM;
		}
	}
}

void cMaxPower::RF(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];

	if(this->MaxDamageRF != -1)
	{
		if(lpObj->m_AttackDamageMaxRight > this->MaxDamageRF || lpObj->m_AttackDamageMaxLeft > this->MaxDamageRF)
		{
			lpObj->m_AttackDamageMinRight = this->MaxDamageRF;
			lpObj->m_AttackDamageMaxRight = this->MaxDamageRF;
			lpObj->m_AttackDamageMinLeft = this->MaxDamageRF;
			lpObj->m_AttackDamageMaxLeft = this->MaxDamageRF;
		}
	}

	if(this->MaxDefenceRF != -1)
	{
		if(lpObj->m_Defense > this->MaxDefenceRF)
		{
			lpObj->m_Defense = this->MaxDefenceRF;
		}
	}

	if(this->MaxIgnoreDefenceRateRF != -1)
	{
		if(lpObj->SetOpIgnoreDefense > this->MaxIgnoreDefenceRateRF)
		{
			lpObj->SetOpIgnoreDefense = this->MaxIgnoreDefenceRateRF;
		}
	}

	if(this->MaxCriticalDamageRateRF != -1)
	{
		if(lpObj->m_CriticalDamage > this->MaxCriticalDamageRateRF)
		{
			lpObj->m_CriticalDamage = this->MaxCriticalDamageRateRF;
		}
	}

	if(this->MaxExellentDamageRateRF != -1)
	{
		if(lpObj->m_ExcelentDamage > this->MaxExellentDamageRateRF)
		{
			lpObj->m_ExcelentDamage = this->MaxExellentDamageRateRF;
		}
	}

	if(this->MaxDoubleDamageRateRF != -1)
	{
		if(lpObj->SetOpDoubleDamage > this->MaxDoubleDamageRateRF)
		{
			lpObj->SetOpDoubleDamage = this->MaxDoubleDamageRateRF;
		}
	}

	if(this->MaxAbsordDamageRateRF != -1)
	{
		if(lpObj->DamageMinus > this->MaxAbsordDamageRateRF)
		{
			lpObj->DamageMinus = this->MaxAbsordDamageRateRF;
		}
	}

	if(this->MaxReflectDamageRateRF != -1)
	{
		if(lpObj->DamageReflect > this->MaxReflectDamageRateRF)
		{
			lpObj->DamageReflect = this->MaxReflectDamageRateRF;
		}
	}

	if(this->MaxWizardDamageRF != -1)
	{
		if(lpObj->m_MagicDamageMax > this->MaxWizardDamageRF)
		{
			lpObj->m_MagicDamageMax = this->MaxWizardDamageRF;
			lpObj->m_MagicDamageMin = this->MaxWizardDamageRF;
		}
	}

	if(this->MaxLifeRF != -1)
	{
		if( lpObj->Life > this->MaxLifeRF)
		{
			lpObj->Life = this->MaxLifeRF;
		}
	}

	if(this->MaxSdRF != -1)
	{
		if( lpObj->iShield > this->MaxSdRF)
		{
			lpObj->iShield = this->MaxSdRF;
		}
	}
}