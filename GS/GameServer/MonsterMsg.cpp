#include "StdAfx.h"
#include "MonsterMsg.h"
#include "GameMain.h"
#include "..\\include\\ReadScript.h"
#include "logproc.h"
#include "Message.h"
#include "ZtLicense.h"
#include "ZtFunction.h"

CMonsterMsg g_MonsterMsg;

CMonsterMsg::CMonsterMsg()
{
	this->Init();
}

CMonsterMsg::~CMonsterMsg()
{
}

void CMonsterMsg::Init()
{
	this->m_Data.clear();
}

void CMonsterMsg::Load()
{
#if(LICENSE_UKRAINE)
	this->Init();
	this->Read(gDirPath.GetNewPath("ZtData\\MonsterMessage.dat"));
	return;
#endif

	if(!g_ZtLicense.CheckUser(eZtUB::Local)			&&
	   !g_ZtLicense.CheckUser(eZtUB::Gredy)			&& 
	   !g_ZtLicense.CheckUser(eZtUB::Gredy2)		&&
	   !g_ZtLicense.CheckUser(eZtUB::GredyLocal)	&&
	   !g_ZtLicense.CheckUser(eZtUB::SILVER1)		&&
	   !g_ZtLicense.CheckUser(eZtUB::SILVER2)		&&
	   !g_ZtLicense.CheckUser(eZtUB::MU2Play)		&&
	   !g_ZtLicense.CheckUser(eZtUB::SILVER_Local)  &&
	   !g_ZtLicense.CheckUser(eZtUB::Artem)			&&
	   !g_ZtLicense.CheckUser(eZtUB::Artem2)		&&
	   !g_ZtLicense.CheckUser(eZtUB::Escalate)		&&
	   !g_ZtLicense.CheckUser(eZtUB::ArcMu)			&&
	   !g_ZtLicense.CheckUser(eZtUB::MedoniAndrei)  &&
	   !g_ZtLicense.CheckUser(eZtUB::mu4you)		&&
	   !g_ZtLicense.CheckUser(eZtUB::eternalmu)		&&
	   !g_ZtLicense.CheckUser(eZtUB::NSGames))
	{
		if(!g_ZtLicense.GetCustom())
		{
			return;
		}
	}

	this->Init();
	this->Read(gDirPath.GetNewPath("ZtData\\MonsterMsg.dat"));
}

void CMonsterMsg::Read(char* filename)
{
	SMDFile = fopen(filename, "r");

	if( SMDFile == NULL )
	{
		LogAdd(lMsg.Get(MSGGET(1, 198)), filename);
		return;
	}

	while(true)
	{
		SMDToken Token = GetToken();

		if( Token == END )
		{
			break;
		}

		MOB_MSG_DATA List;

		List.iClass			= TokenNumber;

		GetToken();
		strncpy(List.szMsg, TokenString, 100);

		this->m_Data.push_back(List);
	}

	fclose(SMDFile);
}

void CMonsterMsg::ReadEx(char* filename)
{
	SMDFile = fopen(filename, "r");

	if( SMDFile == NULL )
	{
		LogAdd(lMsg.Get(MSGGET(1, 198)), filename);
		return;
	}

	while(true)
	{
		SMDToken Token = GetToken();

		if( Token == END )
		{
			break;
		}

		MOB_MSG_DATA List;

		List.iClass			= TokenNumber;

		memset(List.szMsg, 0, sizeof(List.szMsg));

		this->m_Data.push_back(List);
	}

	fclose(SMDFile);
}


void CMonsterMsg::RegenMessage(int aIndex)
{
#if(LICENSE_UKRAINE)
	return;
#endif
	if(!g_ZtLicense.CheckUser(eZtUB::Local)			&&
	   !g_ZtLicense.CheckUser(eZtUB::Gredy)			&& 
	   !g_ZtLicense.CheckUser(eZtUB::Gredy2)		&&
	   !g_ZtLicense.CheckUser(eZtUB::GredyLocal)	&&
	   !g_ZtLicense.CheckUser(eZtUB::SILVER1)		&&
	   !g_ZtLicense.CheckUser(eZtUB::SILVER2)		&&
	   !g_ZtLicense.CheckUser(eZtUB::MU2Play)		&&
	   !g_ZtLicense.CheckUser(eZtUB::SILVER_Local)  &&
	   !g_ZtLicense.CheckUser(eZtUB::Artem)			&& 
	   !g_ZtLicense.CheckUser(eZtUB::Artem2)		&&
	   !g_ZtLicense.CheckUser(eZtUB::Escalate)		&&
	   !g_ZtLicense.CheckUser(eZtUB::ArcMu)			&&
	   !g_ZtLicense.CheckUser(eZtUB::MedoniAndrei)	&&
	   !g_ZtLicense.CheckUser(eZtUB::mu4you)		&&
	   !g_ZtLicense.CheckUser(eZtUB::eternalmu)		&&
	   !g_ZtLicense.CheckUser(eZtUB::NSGames))
	{
		if(!g_ZtLicense.GetCustom())
		{
			return;
		}
	}

	if(!OBJMON_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpMonster = &gObj[aIndex];

	for(int i = 0; i < this->m_Data.size(); i++)
	{
		MOB_MSG_DATA & Mob = this->m_Data[i];
		if(Mob.iClass == lpMonster->Class)
		{
			AllSendServerMsg(Mob.szMsg);
			return;
		}
	}
}

void CMonsterMsg::DieMessage(int aIndex, int aTargetIndex)
{
#if(LICENSE_UKRAINE)
	if(!OBJMAX_RANGE(aIndex) || !OBJMAX_RANGE(aTargetIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpMonster = &gObj[aTargetIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}

	int iMapNumber = lpMonster->MapNumber;

	if(!MAX_MAP_RANGE(iMapNumber)) 
	{
		return;
	}

	for(int i = 0; i < this->m_Data.size(); i++)
	{
		MOB_MSG_DATA & Mob = this->m_Data[i];
		if(Mob.iClass == lpMonster->Class)
		{
			LPMONSTER_ATTRIBUTE lpMonsterAttr = gMAttr.GetAttr(lpMonster->Class);
			char szMsg[128];
			sprintf(szMsg,"%s defeated by %s in %s", lpMonsterAttr->m_Name, lpUser->Name, ztMapName(iMapNumber));
			AllSendServerMsg(szMsg);
			return;
		}
	}
#else
	if(!g_ZtLicense.CheckUser(eZtUB::Local)			&&
	   !g_ZtLicense.CheckUser(eZtUB::Gredy)			&& 
	   !g_ZtLicense.CheckUser(eZtUB::Gredy2)		&&
	   !g_ZtLicense.CheckUser(eZtUB::GredyLocal)	&&
	   !g_ZtLicense.CheckUser(eZtUB::SILVER1)		&&
	   !g_ZtLicense.CheckUser(eZtUB::SILVER2)		&&
	   !g_ZtLicense.CheckUser(eZtUB::MU2Play)		&&
	   !g_ZtLicense.CheckUser(eZtUB::SILVER_Local)  &&
	   !g_ZtLicense.CheckUser(eZtUB::Artem)			&&
	   !g_ZtLicense.CheckUser(eZtUB::Artem2)		&&
	   !g_ZtLicense.CheckUser(eZtUB::Escalate)		&&
	   !g_ZtLicense.CheckUser(eZtUB::ArcMu)			&&
	   !g_ZtLicense.CheckUser(eZtUB::MedoniAndrei)	&&
	   !g_ZtLicense.CheckUser(eZtUB::mu4you)		&&
	   !g_ZtLicense.CheckUser(eZtUB::eternalmu)		&&
	   !g_ZtLicense.CheckUser(eZtUB::NSGames))
	{
		if(!g_ZtLicense.GetCustom())
		{
			return;
		}
	}

	if(!OBJMAX_RANGE(aIndex) || !OBJMAX_RANGE(aTargetIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpMonster = &gObj[aTargetIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}

	int iMapNumber = lpMonster->MapNumber;

	if(!MAX_MAP_RANGE(iMapNumber)) 
	{
		return;
	}

	for(int i = 0; i < this->m_Data.size(); i++)
	{
		MOB_MSG_DATA & Mob = this->m_Data[i];
		if(Mob.iClass == lpMonster->Class)
		{
			LPMONSTER_ATTRIBUTE lpMonsterAttr = gMAttr.GetAttr(lpMonster->Class);
			char szMsg[128];
			sprintf(szMsg,"%s defeated by %s in %s", lpMonsterAttr->m_Name, lpUser->Name, ztMapName(iMapNumber));
			AllSendServerMsg(szMsg);
			return;
		}
	}
#endif
}