#include "StdAfx.h"
#include "GameMain.h"
#include "PartyClass.h"
#include "CameraParty.h"

#if(ENABLE_CAMERA_PARTY)

CCameraParty g_CameraParty;

CCameraParty::CCameraParty()
{
	this->m_Active = false;
}

CCameraParty::~CCameraParty()
{

}

void CCameraParty::Load()
{
	
}

void CCameraParty::Move(int aIndex)
{
	LPOBJ lpUser = &gObj[aIndex];

	int iPartyNumber = lpUser->PartyNumber;

	if(!gParty.IsParty(iPartyNumber))
	{
		return;
	}

	for(int i = 0; i < MAX_USER_IN_PARTY; i++ )
	{
		int aCamIndex = gParty.m_PartyS[iPartyNumber].Number[i];

		if (!gObjIsConnected(aCamIndex))
		{
			continue;
		}

		LPOBJ lpCamUser = &gObj[aCamIndex];

		if(!lpCamUser->m_CameraPartyActive)
		{
			continue;
		}

		if(lpCamUser->m_CameraPartyIndex == aIndex)
		{
			this->GCPartyMemberSend(aCamIndex, aIndex);

			break;

		}
	}
}

BOOL CCameraParty::CheckViewport(int aIndex, int x, int y)
{
	LPOBJ lpUser = &gObj[aIndex];

	int aCamIndex = lpUser->m_CameraPartyIndex;

	if (!OBJMAX_RANGE(aCamIndex))
	{
		return false;
	}

	LPOBJ lpCamUser = &gObj[aCamIndex];

	int iCamViewe = 20;
	int iCamX = lpCamUser->X;
	int iCamY = lpCamUser->Y;

	if(x < iCamX - iCamViewe  || x > iCamX + iCamViewe || y < iCamY - iCamViewe || y > iCamY + iCamViewe)
	{
		return false;
	}

	return true;
}

void CCameraParty::CGReqPartyMember(PMSG_REQ_PARTY_MEMBER* lpMsg, int aIndex)
{
	if (!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}

	if(lpMsg->PartyNumber == -1)
	{
		lpUser->m_CameraPartyActive = false;

		return;
	}

	int usernumber = -1;

	int dbnumber = -1;

	if (!gParty.GetIndexUser(gObj[aIndex].PartyNumber, lpMsg->PartyNumber, usernumber, dbnumber))
	{
		return;
	}

	if(aIndex == usernumber)
	{
		return;
	}

	lpUser->m_CameraPartyActive = true;

	lpUser->m_CameraPartyIndex = usernumber;
}

void CCameraParty::GCPartyMemberSend(int aIndex, int aTargetIndex)
{
	LPOBJ lpTargetObj = &gObj[aTargetIndex];

	PMSG_ANS_PARTY_MEMBER pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xEC, sizeof(pMsg));
	pMsg.Result = 1;
	pMsg.MapX = lpTargetObj->X;
	pMsg.MapY = lpTargetObj->Y;
	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}



#endif