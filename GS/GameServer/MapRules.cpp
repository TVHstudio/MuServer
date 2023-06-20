#include "StdAfx.h"
#include "MapRules.h"


#include "user.h"

#if(ENABLE_MAPRULES)

CMapRules g_MapRules;

void CMapRules::Load()
{
	this->m_Data.clear();
}

void CMapRules::Run()
{
	for(int aIndex = OBJ_STARTUSERINDZT; aIndex < OBJMAX; aIndex++)
	{
		if(!this->GetResult(aIndex))
		{
			// -> TELEPORT
		}
	}
}

bool CMapRules::GetResult(int aIndex)
{
	// -> CHECK index

	LPOBJ lpUser = &gObj[aIndex];

	for(int i = 0; i < this->m_Data.size(); i++)
	{
		if(this->m_Data[i].MapNumber != lpUser->MapNumber)
		{
			continue;
		}

		if(lpUser->GReset < this->m_Data[i].GrandNumber)
		{
			// -> MESSAGE

			return false;
		}

		if(lpUser->Reset < this->m_Data[i].ResetNumber)
		{
			// -> MESSAGE

			return false;
		}

		return true;

	}

	return true;
}

#endif