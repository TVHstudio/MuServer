#include "StdAfx.h"
#include "Protocol.h"
#include "ObjectViewe.h"
#include "ZtLicense.h"

#if(FIX_OBJECT_VIEWE)
/*
		#if(FIX_OBJECT_VIEWE)
		g_ObjectViewe.GCIndexLive(aIndex, usernumber, gObj[usernumber].Type, gObj[usernumber].Live);
		#endif
*/

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

void CObjectViewe::GCIndexLive(int UserIndex, int ObjectIndex, WORD ObjectType, BYTE ObjectLive)
{
	
	if(!this->m_Active)
	{
		return;
	}
	

	if(!OBJMAX_RANGE(UserIndex))
	{
		return;
	}

	if(!ObjectLive)
	{
		//MsgOutput(UserIndex, "[GCIndexLive]: %d %d %d", ObjectIndex, ObjectType, ObjectLive);

		PMSG_OBJECT_LIVE pMsg;
		pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xE9, sizeof(pMsg));
		pMsg.ObjectIndex = ObjectIndex;
		pMsg.ObjectType = ObjectType;
		pMsg.ObjectLive = ObjectLive;
		DataSend(UserIndex, (LPBYTE)&pMsg, sizeof(pMsg));
	}
}


#endif