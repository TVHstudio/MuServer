#include "stdafx.h"
#include "Object.h"
#include "Protocol.h"
#include "ObjectViewe.h"
#include "ZtLicense.h"

#if(FIX_OBJECT_VIEWE)

CObjectViewe g_ObjectViewe;


CObjectViewe::CObjectViewe()
{
	this->m_Active = false;
}

CObjectViewe::~CObjectViewe()
{
}

void CObjectViewe::Load()
{
	if(!g_ZtLicense.user.FixVieweMonster)
	{
		this->m_Active = false;

		return;
	}

	this->m_Active = true;
}

void CObjectViewe::ClearLive(int ObjectIndex)
{
	lpViewObj lpObj = &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), ObjectIndex);

	if(!lpObj)
	{
		return;
	}

	//lpObj->Unknown15 = 0;

	//lpObj->m_Model.Unknown4 = 0;

	lpObj->IsLiveObject = 0;
}

int CObjectViewe::CheckLive(int ObjectIndex)
{
	for(int i = 0; i < OBJECTVIEWE_MAX; i++)
	{
		lpViewObj lpObj = &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), i);

		if(!lpObj)
		{
			continue;
		}

		if(!lpObj->m_Model.Unknown4)
		{
			continue;
		}

		if(!lpObj->IsLiveObject)
		{
			continue;
		}

		if(lpObj->aIndex == ObjectIndex)
		{
			return i;
		}
	}

	return -1;
}

void CObjectViewe::GCIndexLive(PMSG_OBJECT_LIVE* lpMsg)
{
	
	if(!this->m_Active)
	{
		return;
	}
	

	if(!lpMsg->ObjectLive)
	{
		int iPreviewIndex = this->CheckLive(lpMsg->ObjectIndex);

		if(OBJECTVIEWE_RANGE(iPreviewIndex))
		{
			this->ClearLive(iPreviewIndex);
		}
	}
}


#endif