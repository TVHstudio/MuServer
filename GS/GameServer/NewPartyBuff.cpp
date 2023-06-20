#include "StdAfx.h"
#include "NewPartyBuff.h"
#include "user.h"
#include "..\common\winutil.h"
#include "GameServer.h"
#include "GameMain.h"
#include "logproc.h"
#include "ZtLicense.h"

#ifdef _ZT_DEV_BUFF_PT_

struct PMSG_BUFFLIST_SEND_PARTY
{
	PBMSG_HEAD h;				
	char szName[11];			
	char btBuffCount;			
	BYTE iBuffList[32];	
};

void GCDisplayBuffeffectPartyMember(int aIndex)
{
	//if(g_ZtLicense.CheckUser(eZtUB::PrideMuLocal) || g_ZtLicense.CheckUser(eZtUB::drynea) || g_ZtLicense.CheckUser(eZtUB::PrideMu) || g_ZtLicense.CheckUser(eZtUB::Local3) || g_ZtLicense.CheckUser(eZtUB::Local) || g_ZtLicense.CheckUser(eZtUB::feqan))
	if(g_ZtLicense.user.PartySystem || g_ZtLicense.CheckUser(eZtUB::MedoniAndrei))
	{
			
	int nDestUserIndex;
	signed int i;
	signed int nBuffCnt;
	int nPartyIndex;
	signed int nTotalBuffCount;
	PMSG_BUFFLIST_SEND_PARTY pMsg;

	if ( aIndex < 0 || aIndex > OBJMAX-1)
	{
		return;
	}

	if ( gObj[aIndex].Connected < PLAYER_PLAYING )
	{
		return;
	}

	if ( gObjIsConnected(aIndex) && gObj[aIndex].PartyNumber >= 0 )
	{
		ZeroMemory(&pMsg,sizeof(pMsg));
		//PHeadSetB((LPBYTE)&pMsg, 0x2E, 175);
		PHeadSetB((LPBYTE)&pMsg, 0x2E, sizeof(pMsg));
		//LogAddC(2, "PMSG_BUFFLIST_SEND_PARTY: %d", sizeof(pMsg));
		
		nTotalBuffCount = gObj[aIndex].m_btViewStateCount;
		pMsg.btBuffCount = gObj[aIndex].m_btViewStateCount;

	    memcpy(pMsg.szName, gObj[aIndex].Name, 10);
		nPartyIndex = gObj[aIndex].PartyNumber;
		if ( nTotalBuffCount >= 0 )
		{
			if ( nTotalBuffCount > 32 )
			{
				nTotalBuffCount = 32;
				pMsg.btBuffCount = 32;
			}
			for ( nBuffCnt = 0; nBuffCnt < nTotalBuffCount; nBuffCnt++ )
			{
				pMsg.iBuffList[nBuffCnt] = gObj[aIndex].m_BuffEffectState[nBuffCnt].btBuffIndex;
			}
			for ( i = 0; i < MAX_USER_IN_PARTY; ++i )
			{
				nDestUserIndex = gParty.m_PartyS[nPartyIndex].Number[i];
				if ( gObjIsConnected(nDestUserIndex) )
				{
					DataSend(nDestUserIndex, (LPBYTE)&pMsg, pMsg.h.size);
				}
		
			}
		}
	}
	}
}

#endif