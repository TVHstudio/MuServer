#pragma once

#include "StdAfx.h"
#include "Protocol.h"

#if(ENABLE_CAMERA_PARTY)

#define DEBUG_CAMERA_PARTY	1

struct PMSG_REQ_PARTY_MEMBER
{
	PBMSG_HEAD2 h;
	int Result;
	int PartyNumber;
};

struct PMSG_ANS_PARTY_MEMBER
{
	PBMSG_HEAD2 h;
	int Result;
	int MapX;
	int MapY;
};

class CCameraParty
{
public:
	CCameraParty();
	~CCameraParty();

	void Load();
	void Move(int aIndex);
	BOOL CheckViewport(int aIndex, int x, int y);
	void CGReqPartyMember(PMSG_REQ_PARTY_MEMBER* lpMsg, int aIndex);
	void GCPartyMemberSend(int aIndex, int aTargetIndex);

	bool m_Active;

};

extern CCameraParty g_CameraParty;

#endif