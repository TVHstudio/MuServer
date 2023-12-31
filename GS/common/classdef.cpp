//GameServer 1.00.77 JPN - Completed
#include "stdafx.h"
#include "classdef.h"
#include "..\GameServer\user.h"
#ifdef HP_CONFIG
#include "..\GameServer\ZtLicense.h"
#include "..\GameServer\Configs.h"
#endif

classdef::classdef()
{
	this->m_BabubBanJiCreate = FALSE;
}

classdef::~classdef()
{
	return;
}

void classdef::Init()
{
	this->SetCharacter( CLASS_WIZARD, 18, 18, 15, 30, 60.0, 60.0, 1.0, 2.0, 2.0, 2.0, 0);
	this->SetCharacter( CLASS_KNIGHT, 28, 20, 25, 10, 110.0, 20.0, 2.0, 0.5, 3.0, 1.0, 0);
	this->SetCharacter( CLASS_ELF, 22, 25, 20, 15, 80.0, 30.0, 1.0, 1.5, 2.0, 1.5, 0);
	this->SetCharacter( CLASS_MAGUMSA, 26, 26, 26, 26, 110.0, 60.0, 1.0, 1.0, 2.0, 2.0, 0);
	this->SetCharacter( CLASS_DARKLORD, 26, 20, 20, 15, 90.0, 40.0, 1.5, 1.0, 2.0, 1.5, 25);
	this->SetCharacter( CLASS_SUMMONER, 21, 21, 18, 23, 70.0, 40.0, 1.0, 1.5, 2.0, 1.5, 0);
	this->SetCharacter(CLASS_MONK, 32, 27, 25, 20, 100.0f, 40.0f, 1.3f, 1.0f, 2.0f, 1.3f, 0);
}

void classdef::SetCharacter(int Class, int Str, int Dex, int Vit, int Energy, float Life, float Mana, float LevelLife, float LevelMana, float VitalityToLife, float EnergyToMana, int Leadership)
{
#ifdef HP_CONFIG	
	if(g_ZtLicense.CheckUser(eZtUB::PrideMuLocal) || g_ZtLicense.CheckUser(eZtUB::PrideMu))
	{
		switch (Class)
		{
			case CLASS_WIZARD:
				this->DefClass[Class].LevelLife = (float)ZtConfig.PrideMu.LevelLifeSM / 10.0;
				this->DefClass[Class].VitalityToLife = (float)ZtConfig.PrideMu.VitalityToLifeSM / 10.0;
				break;
			case CLASS_KNIGHT:
				this->DefClass[Class].LevelLife = (float)ZtConfig.PrideMu.LevelLifeDK / 10.0;
				this->DefClass[Class].VitalityToLife = (float)ZtConfig.PrideMu.VitalityToLifeDK / 10.0;
				break;
			case CLASS_ELF:
				this->DefClass[Class].LevelLife = (float)ZtConfig.PrideMu.LevelLifeELF / 10.0;
				this->DefClass[Class].VitalityToLife = (float)ZtConfig.PrideMu.VitalityToLifeELF / 10.0;
				break;
			case CLASS_MAGUMSA:
				this->DefClass[Class].LevelLife = (float)ZtConfig.PrideMu.LevelLifeMG / 10.0;
				this->DefClass[Class].VitalityToLife = (float)ZtConfig.PrideMu.VitalityToLifeMG / 10.0;
				break;
			case CLASS_DARKLORD:
				this->DefClass[Class].LevelLife = (float)ZtConfig.PrideMu.LevelLifeDL / 10.0;
				this->DefClass[Class].VitalityToLife = (float)ZtConfig.PrideMu.VitalityToLifeDL / 10.0;
				break;
			case CLASS_SUMMONER:
				this->DefClass[Class].LevelLife = (float)ZtConfig.PrideMu.LevelLifeSUM / 10.0;
				this->DefClass[Class].VitalityToLife = (float)ZtConfig.PrideMu.VitalityToLifeSUM / 10.0;
				break;
			case CLASS_MONK:
				this->DefClass[Class].LevelLife = (float)ZtConfig.PrideMu.LevelLifeRF / 10.0;
				this->DefClass[Class].VitalityToLife = (float)ZtConfig.PrideMu.VitalityToLifeRF / 10.0;
				break;
		}
	}
#endif

	this->DefClass[Class].Experience = 0;

	this->DefClass[Class].Strength = Str;
	this->DefClass[Class].Dexterity = Dex;
	this->DefClass[Class].Vitality = Vit;
	this->DefClass[Class].Energy = Energy;

	this->DefClass[Class].Life = Life;
	this->DefClass[Class].MaxLife = Life;
#ifdef HP_CONFIG	
	if(g_ZtLicense.CheckUser(eZtUB::PrideMuLocal) || g_ZtLicense.CheckUser(eZtUB::PrideMu))
	{
	}
	else
	{
		this->DefClass[Class].LevelLife = LevelLife;
	}
#else
	this->DefClass[Class].LevelLife = LevelLife;
#endif
	this->DefClass[Class].Mana = Mana;
	this->DefClass[Class].MaxMana = Mana;
	this->DefClass[Class].LevelMana = LevelMana;

#ifdef HP_CONFIG	
	if(g_ZtLicense.CheckUser(eZtUB::PrideMuLocal) || g_ZtLicense.CheckUser(eZtUB::PrideMu) )
	{
	}
	else
	{
		this->DefClass[Class].VitalityToLife = VitalityToLife;
	}
#else
	this->DefClass[Class].VitalityToLife = VitalityToLife;
#endif

	this->DefClass[Class].EnergyToMana = EnergyToMana;

	this->DefClass[Class].Leadership = Leadership;

	this->SetEquipment(Class);

}

void classdef::SetEquipment(int Class)
{
	int def_type=0;
	int right_type=0;
	int n;

	for (n=0;n<MAX_PLAYER_EQUIPMENT+1;n++)
	{
		this->DefClass[Class].Equipment[n].Clear();
	}

	switch (Class)
	{
		case CLASS_KNIGHT:
			def_type = ItemGetNumberMake(1, 0);
			break;

		case CLASS_ELF:
			def_type = ItemGetNumberMake(4, 0);
			right_type = ItemGetNumberMake(4, 15);
			break;

		case CLASS_DARKLORD:
			def_type = ItemGetNumberMake(6, 0);
			right_type = ItemGetNumberMake(0, 1);
			break;

		case CLASS_MAGUMSA:
			def_type = ItemGetNumberMake(6, 0);
			right_type = ItemGetNumberMake(0, 1);
			break;

		case CLASS_SUMMONER:
			def_type = ItemGetNumberMake(1, 0);
		break;

		case CLASS_MONK:
			def_type = ItemGetNumberMake(1, 0);
			break;
	}

	if ( Class != 0 )
	{
		if ( Class == CLASS_DARKLORD )
		{
			this->DefClass[Class].Equipment[0].m_Level = 0;
			this->DefClass[Class].Equipment[1].m_Level = 0;
			this->DefClass[Class].Equipment[0].Convert(right_type, 0,0,0,0,0,0,NULL, 0xFF, 0, CURRENT_DB_VERSION);
			this->DefClass[Class].Equipment[1].Convert(def_type, 0,0,0,0,0,0,NULL, 0xFF, 0, CURRENT_DB_VERSION);
		}
		else if ( Class == CLASS_ELF || Class == CLASS_MAGUMSA )
		{
			this->DefClass[Class].Equipment[0].m_Level = 0;
			this->DefClass[Class].Equipment[1].m_Level = 0;
			this->DefClass[Class].Equipment[0].Convert(right_type, 0,0,0,0,0,0,NULL, 0xFF, 0, CURRENT_DB_VERSION);
			this->DefClass[Class].Equipment[1].Convert(def_type, 0,0,0,0,0,0,NULL, 0xFF, 0, CURRENT_DB_VERSION);
		}
		else if( Class == CLASS_SUMMONER )
		{
			DefClass[Class].Equipment[0].m_Level = 0;
			DefClass[Class].Equipment[0].Convert(def_type, 0,0,0,0,0,0,NULL, 0xFF, 0, CURRENT_DB_VERSION);
		}
		else
		{
			this->DefClass[Class].Equipment[0].m_Level = 0;
			this->DefClass[Class].Equipment[0].Convert(def_type, 0,0,0,0,0,0,NULL, 0xFF, 0, CURRENT_DB_VERSION);
		}
	}

	if ( this->m_BabubBanJiCreate == TRUE )
	{
		def_type = ItemGetNumberMake(13, 20);
		this->DefClass[Class].Equipment[12].m_Level = 1;
		this->DefClass[Class].Equipment[12].Convert(def_type, 0,0,0,0,0,0,NULL, 0xFF, 0, CURRENT_DB_VERSION);
		
		def_type = ItemGetNumberMake(13, 20);
		this->DefClass[Class].Equipment[13].m_Level = 2;
		this->DefClass[Class].Equipment[13].Convert(def_type, 0,0,0,0,0,0,NULL, 0xFF, 0, CURRENT_DB_VERSION);
	}

}

int classdef::GetDefPoint(int char_class)
{
	if ( char_class < 0 || char_class > MAX_TYPE_PLAYER-1 )
	{
		return 0;
	}

	return this->DefClass[char_class].Strength + this->DefClass[char_class].Dexterity + this->DefClass[char_class].Vitality + this->DefClass[char_class].Energy + this->DefClass[char_class].Leadership;
}

void classdef::SetMabubBanjiOption(BOOL Flag)
{
	this->m_BabubBanJiCreate=Flag;
}