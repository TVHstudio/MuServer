#include "StdAfx.h"
#include "MonsterZt.h"
#include "GameMain.h"
#include "..\\include\\ReadScript.h"
#include "logproc.h"
#include "ZtLicense.h"
// ----------------------------------------------------------------------------------------------

#if(CUSTOM_MONSTER_ZT==TRUE)
// ----------------------------------------------------------------------------------------------

MonsterZt g_MonsterZt;
// ----------------------------------------------------------------------------------------------

MonsterZt::MonsterZt()
{
}
// ----------------------------------------------------------------------------------------------

MonsterZt::~MonsterZt()
{
}
// ----------------------------------------------------------------------------------------------

void MonsterZt::Init()
{
	ZeroMemory(this->mobdata,sizeof(this->mobdata));

	this->mobLoaded = 0;
}
// ----------------------------------------------------------------------------------------------

void MonsterZt::Load()
{
	this->Init();

	if(!g_ZtLicense.user.MonsterAttackLife)
	{
		return;
	}
	
	this->Read(gDirPath.GetNewPath("ZtData\\MonsterZt.ini"));
}
// ----------------------------------------------------------------------------------------------

void MonsterZt::Read(char* File)
{
	SMDFile = fopen(File, "r");

	if( SMDFile == NULL )
	{
		LogAdd(lMsg.Get(MSGGET(1, 198)), File);
		return;
	}

	int Token;
	int type = -1;

	while ( true )
	{
	    Token = GetToken();

        if( Token == END )
		{
            break;
		}

		type = (int)TokenNumber;

		while ( true )
		{
			if ( type == 0 )
			{
				Token = GetToken();

				if ( strcmp("end", TokenString) == 0 )
				{
					break;
				}

				this->mobdata[this->mobLoaded].id = TokenNumber;

				Token = GetToken();
				this->mobdata[this->mobLoaded].map = TokenNumber;

				Token = GetToken();
				this->mobdata[this->mobLoaded].AttackDiv = TokenNumber;

				this->mobLoaded++;
			}    
		}
    }

	fclose(SMDFile);
	return;
}
// ----------------------------------------------------------------------------------------------

void MonsterZt::AttackMonster(int aUserIndex, int aMonsterIndex, int& AttackDamage)
{
	if(!g_ZtLicense.user.MonsterAttackLife)
	{
		return;
	}

	if(!OBJMAX_RANGE(aUserIndex) || !OBJMAX_RANGE(aMonsterIndex))
	{
		return;
	}

	if(!gObjIsConnectedZt(aUserIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aUserIndex];
	LPOBJ lpMonster = &gObj[aMonsterIndex];

	if(lpMonster->Type != OBJ_NPC && lpMonster->Type != OBJ_MONSTER)
	{
		return;
	}

	for(int i = 0; i < this->mobLoaded; i++)
	{
		if(this->mobdata[i].map == -1 || this->mobdata[i].map == lpMonster->MapNumber)
		{
			if(this->mobdata[i].id == lpMonster->Class)
			{
				if(this->mobdata[i].AttackDiv > 0)
				{
					AttackDamage = ( lpUser->MaxLife + lpUser->AddLife ) / this->mobdata[i].AttackDiv;
					return;
				}			
			}
		}
	}
}
// ----------------------------------------------------------------------------------------------
#endif

