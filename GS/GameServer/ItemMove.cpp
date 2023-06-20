#include "StdAfx.h"
#include "ZtLicense.h"
#include "..\\include\\ReadScript.h"
#include "logproc.h"
#include "ItemMove.h"

#if(CUSTOM_ITEM_MOVE)

CItemMove g_ItemMove;

CItemMove::CItemMove()
{

}

CItemMove::~CItemMove()
{

}

void CItemMove::Init()
{
	this->m_Data.clear();
}

void CItemMove::Load()
{
	this->Init();
	this->Read(ITEM_MOVE_PATH);
}

void CItemMove::Read(char* FileName)
{
	SMDFile = fopen(FileName, "r");

	if(SMDFile == NULL)
	{
		LogAdd(lMsg.Get(MSGGET(1, 198)), FileName);
		return;
	}

	SMDToken Token;

	int iType = -1;

	while(true)
	{
		Token = GetToken();

        if(Token == END)
		{
            break;
		}

		//iType = (int)TokenNumber;

		//if(iType != 0)
		//{
		//	break;
		//}

		//while(true)
		{
			//if(iType == 0)
			{
				//Token = GetToken();

				if(!strcmp("end", TokenString))
				{
					break;
				}

				ITEM_MOVE_DATA lpData;

				lpData.Type = TokenNumber;

				Token = GetToken();
				lpData.Index = TokenNumber;

				Token = GetToken();
				lpData.AllowDrop = TokenNumber;

				Token = GetToken();
				lpData.AllowSell = TokenNumber;

				Token = GetToken();
				lpData.AllowTrade = TokenNumber;

				Token = GetToken();
				lpData.AllowVault = TokenNumber;

				this->m_Data.push_back(lpData);
			}
		}
	}

	fclose(SMDFile);

	LogAdd("%s file load!", FileName);
}

bool CItemMove::CheckDrop(int ItemType)
{
	for(int i = 0; i < this->m_Data.size(); i++)
	{
		ITEM_MOVE_DATA * lpData = &this->m_Data[i];

		if(ItemType == ITEMGET(lpData->Type,lpData->Index) && lpData->AllowDrop == 0)
		{
			return true;
		}
	}

	return false;
}

bool CItemMove::CheckSell(int ItemType)
{
	for(int i = 0; i < this->m_Data.size(); i++)
	{
		ITEM_MOVE_DATA * lpData = &this->m_Data[i];

		if(ItemType == ITEMGET(lpData->Type,lpData->Index) && lpData->AllowSell == 0)
		{
			return true;
		}
	}

	return false;
}

bool CItemMove::CheckTrade(int ItemType)
{
	for(int i = 0; i < this->m_Data.size(); i++)
	{
		ITEM_MOVE_DATA * lpData = &this->m_Data[i];

		if(ItemType == ITEMGET(lpData->Type,lpData->Index) && lpData->AllowTrade == 0)
		{
			return true;
		}
	}

	return false;
}

bool CItemMove::CheckVault(int ItemType)
{
	for(int i = 0; i < this->m_Data.size(); i++)
	{
		ITEM_MOVE_DATA * lpData = &this->m_Data[i];

		if(ItemType == ITEMGET(lpData->Type,lpData->Index) && lpData->AllowVault == 0)
		{
			return true;
		}
	}

	return false;
}


#endif