#include "StdAfx.h"
#include "..\\include\ReadScript.h"
#include "GameMain.h"
#include "PetZt.h"
#include "logproc.h"
#include "ZtLicense.h"

#if(ENABLE_PETZT)

CPetZt g_PetZt;

CPetZt::CPetZt()
{
	this->Init();
}

CPetZt::~CPetZt()
{
}

void CPetZt::Init()
{
	this->m_Enable = 0;
	this->m_PetCount = 0;
	this->m_ImmortalCount = 0;

	for(int i = 0; i < MAX_PETZT_COUNT; i++)
	{
		this->m_Data[i].Active = false;	
		this->m_Data[i].ItemType = -1;	
		this->m_Data[i].ItemIndex = -1;	
		
		for(int n = 0; n < MAX_PETZT_OPTION; n++)
		{
			this->m_Data[i].Option[n].Type = 0;
			this->m_Data[i].Option[n].Value = 0;		
		}
	}

	for(int i = 0; i < MAX_PETZT_COUNT; i++)
	{
		this->m_Immoirtal[i].Active = false;	
		this->m_Immoirtal[i].ItemType = -1;	
		this->m_Immoirtal[i].ItemIndex = -1;	
	}
}

void CPetZt::Load()
{
	this->Init();
	this->Read(gDirPath.GetNewPath("ZtData\\PetZt.dat"));
	
}


void CPetZt::Read(char* filename)
{
	SMDFile = fopen(filename, "r");

	if(SMDFile == NULL)
	{
		LogAdd(lMsg.Get(MSGGET(1, 198)), filename);
		return;
	}

	SMDToken Token;

	int iType = -1;
	int iMaxType = 1;

	if(g_ZtLicense.CheckUser(eZtUB::SILVER1) || g_ZtLicense.CheckUser(eZtUB::SILVER2))
	{
		iMaxType = 2;
	}

	while(true)
	{
		Token = GetToken();

        if(Token == END)
		{
            break;
		}

		iType = (int)TokenNumber;

		if(iType < 0 || iType > iMaxType)
		{
			break;
		}

		while(true)
		{
			if(iType == 0)
			{
				Token = GetToken();

				if(!strcmp("end", TokenString))
				{
					break;
				}

				this->m_Enable = (int)1;
			}
			else if(iType == 1)
			{
				Token = GetToken();

				if(!strcmp("end", TokenString))
				{
					break;
				}

				if(this->m_PetCount >= MAX_PETZT_COUNT)
				{
					break;
				}

				this->m_Data[this->m_PetCount].Active = true;

				this->m_Data[this->m_PetCount].ItemType = TokenNumber;

				Token = GetToken();
				this->m_Data[this->m_PetCount].ItemIndex = TokenNumber;

				for(int i = 0; i < MAX_PETZT_OPTION; i++)
				{
					Token = GetToken();
					this->m_Data[this->m_PetCount].Option[i].Type = TokenNumber;

					Token = GetToken();
					this->m_Data[this->m_PetCount].Option[i].Value = TokenNumber;
				}

				this->m_PetCount++;
			}
			else if(iType == 2)
			{
				Token = GetToken();

				if(!strcmp("end", TokenString))
				{
					break;
				}

				if(this->m_ImmortalCount >= MAX_PETZT_COUNT)
				{
					break;
				}

				this->m_Data[this->m_ImmortalCount].Active = true;

				this->m_Data[this->m_ImmortalCount].ItemType = TokenNumber;

				Token = GetToken();
				this->m_Data[this->m_ImmortalCount].ItemIndex = TokenNumber;

				this->m_ImmortalCount++;
			}
		}
	}

	fclose(SMDFile);

	LogAdd("%s file load!", filename);
}

bool CPetZt::IsPet(int ItemID)
{
	if(!this->m_Enable)
	{
		return false;
	}	

	for(int i = 0; i < this->m_PetCount; i++)
	{
		if(ITEMGET(this->m_Data[i].ItemType, this->m_Data[i].ItemIndex) == ItemID)
		{
			return true;
		}
	}

	return false;
}

bool CPetZt::IsPetImmortal(int ItemID)
{
	if(!this->m_Enable)
	{
		return false;
	}	

	for(int i = 0; i < this->m_ImmortalCount; i++)
	{
		if(this->m_Immoirtal[i].Active)
		{
			if(ITEMGET(this->m_Data[i].ItemType, this->m_Data[i].ItemIndex) == ItemID)
			{
				return true;
			}
		}
	}

	return false;
}

PETZT_DATA* CPetZt::GetPetData(int ItemID)
{
	if(!this->m_Enable)
	{
		return false;
	}	

	for(int i = 0; i < this->m_PetCount; i++)
	{
		if(ITEMGET(this->m_Data[i].ItemType, this->m_Data[i].ItemIndex) == ItemID)
		{
			return &this->m_Data[i];
		}
	}

	return NULL;
}

bool CPetZt::PetLife(int aIndex)
{
	if(!this->m_Enable)
	{
		return false;
	}	

	if(!OBJMAX_RANGE(aIndex))
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->Type != OBJ_USER)
	{
		return false;
	}

	if(!lpObj->pInventory[8].IsItem())
	{
		return false;
	}

	CItem * Item = &lpObj->pInventory[8];

	if(this->IsPet(Item->m_Type) && Item->m_Durability > 0.0f)
	{
		return true;
	}

	return false;
}

void CPetZt::Calc(int aIndex)
{
	if(!this->m_Enable)
	{
		return;
	}	

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	if(!this->PetLife(aIndex))
	{
		return;
	}

	LPOBJ lpObj = &gObj[aIndex];

	PETZT_DATA* pPetData = this->GetPetData(lpObj->pInventory[8].m_Type);

	if(!pPetData)
	{
		return;
	}

	for(int i = 0; i < MAX_PETZT_OPTION; i++)
	{
		switch(pPetData->Option[i].Type)
		{
		case ePET_DAMAGE:
			lpObj->m_AttackDamageMinRight += pPetData->Option[i].Value;
			lpObj->m_AttackDamageMaxRight += pPetData->Option[i].Value;
			lpObj->m_AttackDamageMinLeft += pPetData->Option[i].Value;
			lpObj->m_AttackDamageMaxLeft += pPetData->Option[i].Value;
			break;
		case ePET_DEFENCE:
			lpObj->m_Defense += pPetData->Option[i].Value;
			break;
		case ePET_IGNOREDEFENCE:
			lpObj->SetOpIgnoreDefense += pPetData->Option[i].Value;
			break;
		case ePET_CRITICALDAMAGE:
			lpObj->m_CriticalDamage += pPetData->Option[i].Value;
			break;
		case ePET_EXELLENTDAMAGEe:
			lpObj->m_ExcelentDamage += pPetData->Option[i].Value;
			break;
		case ePET_DOUBLEDAMAGE:
			lpObj->SetOpDoubleDamage += pPetData->Option[i].Value;
			break;
		case ePET_DECRISEDAMAGE:
			lpObj->DamageMinus += pPetData->Option[i].Value;
			break;
		case ePET_REFLECTDAMAGE:
			lpObj->DamageReflect += pPetData->Option[i].Value;
			break;
		case ePET_SD:
			lpObj->iAddShield += pPetData->Option[i].Value;
			break;
		case ePET_LIFE:
			lpObj->AddLife += pPetData->Option[i].Value;
			break;
		case ePET_MAGICDAMAGE:
			lpObj->m_MagicDamageMin += pPetData->Option[i].Value;
			lpObj->m_MagicDamageMax += pPetData->Option[i].Value;
			break;
		}
	}
}

void CPetZt::Exp(int aIndex, __int64 & exp)
{
	if(!this->m_Enable)
	{
		return;
	}	

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	if(!this->PetLife(aIndex))
	{
		return;
	}

	LPOBJ lpObj = &gObj[aIndex];

	PETZT_DATA* pPetData = this->GetPetData(lpObj->pInventory[8].m_Type);

	if(!pPetData)
	{
		return;
	}

	for(int i = 0; i < MAX_PETZT_OPTION; i++)
	{
		switch(pPetData->Option[i].Type)
		{
		case ePET_EXPERIENCE:
			exp += ( exp * pPetData->Option[i].Value ) / 100;
			break;
		}
	}
}

void CPetZt::Zen(int aIndex, float & money)
{
	if(!this->m_Enable)
	{
		return;
	}	

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	if(!this->PetLife(aIndex))
	{
		return;
	}

	LPOBJ lpObj = &gObj[aIndex];

	PETZT_DATA* pPetData = this->GetPetData(lpObj->pInventory[8].m_Type);

	if(!pPetData)
	{
		return;
	}

	for(int i = 0; i < MAX_PETZT_OPTION; i++)
	{
		switch(pPetData->Option[i].Type)
		{
		case ePET_ZENMONEY:
			money += ( money * pPetData->Option[i].Value ) / 100;
			break;
		}
	}
}

#endif