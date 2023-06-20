#include "StdAfx.h"
#include "ZtWebManager.h"
#include "user.h"
#include "ZtUser.h"
#include "DBSockMng.h"

CZtWebManager g_ZtWebManager;

void CZtWebManager::Protocol(BYTE protoNum, BYTE *aRecv)
{
	switch(protoNum)
	{
	case 0x00:
		this->GameShopUpdate((GAMESHOP_WEB_UPDATE*)aRecv);
		break;
	case 0x01:
		this->CreditsUpdate((CREDIT_WEB_UPDATE*)aRecv);
		break;
	}
}

void CZtWebManager::GameShopUpdate(GAMESHOP_WEB_UPDATE* lpMsg)
{
	int aIndex = -1;

	for(int n = OBJ_STARTUSERINDZT; n < OBJMAX; n++)
	{
		if(gObj[n].Connected == PLAYER_PLAYING)
		{
			if(gObj[n].AccountID[0] == lpMsg->AccountID[0])
			{
				if(strcmp(&gObj[n].AccountID[0] , lpMsg->AccountID) == 0)
				{
					aIndex = n;
					break;
				}
			}
		}
	}

	if(aIndex == -1)
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];
	lpUser->GameShop.WCoinC = lpMsg->WCoinC;
	lpUser->GameShop.WCoinP = lpMsg->WCoinP;
	lpUser->GameShop.GoblinPoint = lpMsg->GoblinPoint;

	ZtUserDataSend(aIndex);
}

void CZtWebManager::CreditsUpdate(CREDIT_WEB_UPDATE* lpMsg)
{
	int aIndex = -1;

	for(int n = OBJ_STARTUSERINDZT; n < OBJMAX; n++)
	{
		if(gObj[n].Connected == PLAYER_PLAYING)
		{
			if(gObj[n].AccountID[0] == lpMsg->AccountID[0])
			{
				if(strcmp(&gObj[n].AccountID[0] , lpMsg->AccountID) == 0)
				{
					aIndex = n;
					break;
				}
			}
		}
	}

	if(aIndex == -1)
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];
	lpUser->ZtCred = lpMsg->Credit;

	ZtUserDataSend(aIndex);
}