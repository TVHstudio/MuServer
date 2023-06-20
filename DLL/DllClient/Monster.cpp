#include "stdafx.h"
#include "Monster.h"
#include "TMemory.h"
#include "Console.h"
#include "Import.h"
#include "Defines.h"
#include "Object.h"
#include "ReadScript.h"
#include "ZtFunction.h"
#include "Configs.h"
#include "User.h"
// ----------------------------------------------------------------------------------------------

Monster gMonster;
// ----------------------------------------------------------------------------------------------

#if(DEBUG_MONSTER_LOAD)
Monster::Monster(){};
Monster::~Monster(){};
#endif

void Monster::Load()
{
	//return;

	#if(DEBUG_MONSTER_LOAD)

	ZeroMemory(this->lpNpcName, sizeof(this->lpNpcName));
	ZeroMemory(this->Data,sizeof(Data));
	// ----
	this->ReadList("Data\\ZtTeam\\Monster.ini");
	
	// ----
	//SetRange((LPVOID)0x005852EC, 0xa4, ASM::NOP);
	//SetOp((LPVOID)0x005852EC, (LPVOID)CraftMasterView, ASM::JMP);
	// ----
	SetOp((LPVOID)0x0061FE3F, (LPVOID)Monster::LoadMonsterBMD, ASM::CALL);
	SetOp((LPVOID)0x0061FEEA, (LPVOID)Monster::LoadMonsterTexture, ASM::CALL);
	//Limit kill
	SetByte((LPVOID)(0x00559B82 + 3),0xFF);
	SetByte((LPVOID)(0x00559B82 + 4),0xFF);
	// ----

	SetOp((LPVOID)0x004E199D, (LPVOID)Monster::ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x00587049, (LPVOID)Monster::ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x00590CCC, (LPVOID)Monster::ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x005BBEE6, (LPVOID)Monster::ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x0064229D, (LPVOID)Monster::ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x00642D51, (LPVOID)Monster::ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x00643229, (LPVOID)Monster::ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x0065EA86, (LPVOID)Monster::ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x00911903, (LPVOID)Monster::ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x0091191D, (LPVOID)Monster::ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x00911937, (LPVOID)Monster::ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x00911951, (LPVOID)Monster::ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x0091196B, (LPVOID)Monster::ShowMonster, ASM::CALL);
	// ----
	SetOp((LPVOID)0x0058101A, (LPVOID)Monster::SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x0058105B, (LPVOID)Monster::SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x0058109C, (LPVOID)Monster::SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x005810DD, (LPVOID)Monster::SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x0058111E, (LPVOID)Monster::SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x0058115F, (LPVOID)Monster::SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x005811A0, (LPVOID)Monster::SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x005811E1, (LPVOID)Monster::SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x00581222, (LPVOID)Monster::SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x00581263, (LPVOID)Monster::SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x005812A8, (LPVOID)Monster::SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x005812ED, (LPVOID)Monster::SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x0058132E, (LPVOID)Monster::SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x0058136F, (LPVOID)Monster::SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x005813B4, (LPVOID)Monster::SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x005813F9, (LPVOID)Monster::SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x00586859, (LPVOID)Monster::SetMainAttribute, ASM::CALL);

	this->m_AttackCount = 0;

	#else

	ZeroMemory(this->lpNpcName, sizeof(this->lpNpcName));
	ZeroMemory(this->Data,sizeof(Data));
	// ----
	this->ReadList("Data\\ZtTeam\\Monster.ini");
	
	// ----
	//SetRange((LPVOID)0x005852EC, 0xa4, ASM::NOP);
	//SetOp((LPVOID)0x005852EC, (LPVOID)CraftMasterView, ASM::JMP);
	// ----
	SetOp((LPVOID)0x0061FE3F, (LPVOID)this->LoadMonsterBMD, ASM::CALL);
	SetOp((LPVOID)0x0061FEEA, (LPVOID)this->LoadMonsterTexture, ASM::CALL);
	//Limit kill
	SetByte((LPVOID)(0x00559B82 + 3),0xFF);
	SetByte((LPVOID)(0x00559B82 + 4),0xFF);
	// ----
	SetOp((LPVOID)0x004E199D, (LPVOID)this->ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x00587049, (LPVOID)this->ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x00590CCC, (LPVOID)this->ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x005BBEE6, (LPVOID)this->ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x0064229D, (LPVOID)this->ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x00642D51, (LPVOID)this->ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x00643229, (LPVOID)this->ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x0065EA86, (LPVOID)this->ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x00911903, (LPVOID)this->ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x0091191D, (LPVOID)this->ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x00911937, (LPVOID)this->ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x00911951, (LPVOID)this->ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x0091196B, (LPVOID)this->ShowMonster, ASM::CALL);
	// ----
	SetOp((LPVOID)0x0058101A, (LPVOID)this->SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x0058105B, (LPVOID)this->SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x0058109C, (LPVOID)this->SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x005810DD, (LPVOID)this->SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x0058111E, (LPVOID)this->SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x0058115F, (LPVOID)this->SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x005811A0, (LPVOID)this->SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x005811E1, (LPVOID)this->SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x00581222, (LPVOID)this->SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x00581263, (LPVOID)this->SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x005812A8, (LPVOID)this->SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x005812ED, (LPVOID)this->SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x0058132E, (LPVOID)this->SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x0058136F, (LPVOID)this->SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x005813B4, (LPVOID)this->SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x005813F9, (LPVOID)this->SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x00586859, (LPVOID)this->SetMainAttribute, ASM::CALL);

	this->m_AttackCount = 0;

	#endif
}
// ----------------------------------------------------------------------------------------------

void Monster::ReadList(char * File)
{
	int Token;
	// ----
	SMDFile = fopen(File, "r");
	// ----
	if (!SMDFile)
	{
		MessageBoxError("%s - file nor found", File);
		ExitProcess(0);
		return;
	}
	// ----
	this->Count = 0;
	// ----
	while(true)
	{
		Token = GetToken();
		// ----
		if( Token == END || !strcmp(TokenString, "end") )
		{
			break;
		}
		// ----
		if( this->Count >= MAX_MONSTER)
		{
			break;
		}
		// ----
		this->Data[this->Count].ID		= TokenNumber;
		// ----
		GetToken();
		this->Data[this->Count].Type	= TokenNumber;
		// ----
		GetToken();
		memcpy(this->Data[this->Count].Name, TokenString, sizeof(this->Data[this->Count].Name));
		// ----
		GetToken();
		memcpy(this->Data[this->Count].Dir, TokenString, sizeof(this->Data[this->Count].Dir));
		// ----
		GetToken();
		memcpy(this->Data[this->Count].Folder, TokenString, sizeof(this->Data[this->Count].Folder));
		// ----
		GetToken();
		memcpy(this->Data[this->Count].BMDFile, TokenString, sizeof(this->Data[this->Count].BMDFile));
		// ----
		GetToken();
		this->Data[this->Count].Size	= TokenNumber;
		// ----
		this->Count++;
	} 
	fclose(SMDFile);	
#ifdef _GRAND_SYSTEM_
	
	this->Data[this->Count].ID		= 586;
	this->Data[this->Count].Type	= 0;
	memcpy(this->Data[this->Count].Name, "Hero City", sizeof(this->Data[this->Count].Name));
	memcpy(this->Data[this->Count].Dir, "Data\\Monster\\", sizeof(this->Data[this->Count].Dir));
	memcpy(this->Data[this->Count].Folder, "\\Monster\\", sizeof(this->Data[this->Count].Folder));
	memcpy(this->Data[this->Count].BMDFile, "Monster166", sizeof(this->Data[this->Count].BMDFile));
	this->Data[this->Count].Size	= 1.3;
	this->Count++;

	this->Data[this->Count].ID		= 587;
	this->Data[this->Count].Type	= 1;
	memcpy(this->Data[this->Count].Name, "Aidos", sizeof(this->Data[this->Count].Name));
	memcpy(this->Data[this->Count].Dir, "Data\\Monster\\", sizeof(this->Data[this->Count].Dir));
	memcpy(this->Data[this->Count].Folder, "Monster\\", sizeof(this->Data[this->Count].Folder));
	memcpy(this->Data[this->Count].BMDFile, "Monster176", sizeof(this->Data[this->Count].BMDFile));
	this->Data[this->Count].Size	= 1.3;
	this->Count++; 

	this->Data[this->Count].ID		= 588;
	this->Data[this->Count].Type	= 1;
	memcpy(this->Data[this->Count].Name, "ZveroLom", sizeof(this->Data[this->Count].Name));
	memcpy(this->Data[this->Count].Dir, "Data\\Monster\\", sizeof(this->Data[this->Count].Dir));
	memcpy(this->Data[this->Count].Folder, "Monster\\", sizeof(this->Data[this->Count].Folder));
	memcpy(this->Data[this->Count].BMDFile, "monster178", sizeof(this->Data[this->Count].BMDFile));
	this->Data[this->Count].Size	= 1.3;
	this->Count++;

	this->Data[this->Count].ID		= 589;
	this->Data[this->Count].Type	= 1;
	memcpy(this->Data[this->Count].Name, "StriKozel", sizeof(this->Data[this->Count].Name));
	memcpy(this->Data[this->Count].Dir, "Data\\Monster\\", sizeof(this->Data[this->Count].Dir));
	memcpy(this->Data[this->Count].Folder, "Monster\\", sizeof(this->Data[this->Count].Folder));
	memcpy(this->Data[this->Count].BMDFile, "Monster215", sizeof(this->Data[this->Count].BMDFile));
	this->Data[this->Count].Size	= 1.3;
	this->Count++;

	this->Data[this->Count].ID		= 590;
	this->Data[this->Count].Type	= 1;
	memcpy(this->Data[this->Count].Name, "Brokin", sizeof(this->Data[this->Count].Name));
	memcpy(this->Data[this->Count].Dir, "Data\\Monster\\", sizeof(this->Data[this->Count].Dir));
	memcpy(this->Data[this->Count].Folder, "Monster\\", sizeof(this->Data[this->Count].Folder));
	memcpy(this->Data[this->Count].BMDFile, "Monster213", sizeof(this->Data[this->Count].BMDFile));
	this->Data[this->Count].Size	= 1.5;
	this->Count++;

	this->Data[this->Count].ID		= 591;
	this->Data[this->Count].Type	= 1;
	memcpy(this->Data[this->Count].Name, "Varol", sizeof(this->Data[this->Count].Name));
	memcpy(this->Data[this->Count].Dir, "Data\\Monster\\", sizeof(this->Data[this->Count].Dir));
	memcpy(this->Data[this->Count].Folder, "Monster\\", sizeof(this->Data[this->Count].Folder));
	memcpy(this->Data[this->Count].BMDFile, "monster169", sizeof(this->Data[this->Count].BMDFile));
	this->Data[this->Count].Size	= 1.5;
	this->Count++;

	this->Data[this->Count].ID		= 592;
	this->Data[this->Count].Type	= 1;
	memcpy(this->Data[this->Count].Name, "Ishak", sizeof(this->Data[this->Count].Name));
	memcpy(this->Data[this->Count].Dir, "Data\\Monster\\", sizeof(this->Data[this->Count].Dir));
	memcpy(this->Data[this->Count].Folder, "Monster\\", sizeof(this->Data[this->Count].Folder));
	memcpy(this->Data[this->Count].BMDFile, "Monster167", sizeof(this->Data[this->Count].BMDFile));
	this->Data[this->Count].Size	= 1.3;
	this->Count++;

	this->Data[this->Count].ID		= 593;
	this->Data[this->Count].Type	= 1;
	memcpy(this->Data[this->Count].Name, "Hero Boss", sizeof(this->Data[this->Count].Name));
	memcpy(this->Data[this->Count].Dir, "Data\\Monster\\", sizeof(this->Data[this->Count].Dir));
	memcpy(this->Data[this->Count].Folder, "Monster\\", sizeof(this->Data[this->Count].Folder));
	memcpy(this->Data[this->Count].BMDFile, "Monster171", sizeof(this->Data[this->Count].BMDFile));
	this->Data[this->Count].Size	= 1.5;
	this->Count++;
	
#endif
}
// ----------------------------------------------------------------------------------------------

void Monster::ReadName(char* File)
{
	int Token;
	// ----
	SMDFile = fopen(File, "r");
	// ----
	if( SMDFile == 0 )
	{
		//MsgBox(lMsg.Get(MSGGET(0, 112)), File);
		return;
	}

	this->iLoadedName = 0;

	while(true) 
	{
		Token = GetToken();

		if( Token == END || !strcmp(TokenString, "end") )
		{
			return;
		}

		this->name_data[this->iLoadedName].ObjectID = TokenNumber;

		Token = GetToken();
		int nomer = TokenNumber;

		Token = GetToken();
		memcpy(this->name_data[this->iLoadedName].Name, TokenString, 25);

		//gConsole.Output(cGREY, "%d %s",this->iLoadedName, this->name_data[this->iLoadedName].Name);

		this->iLoadedName++;
	}

	fclose(SMDFile);	
	// ----
};

void Monster::LoadMonsterBMD(signed int ModelID, char* a2, char* a3, signed int a4)
{
	int MonsterID = ModelID - MONSTER_MODEL;
	// ----
	for(int i=0;i<gMonster.Count;i++)
	{
		if(MonsterID == gMonster.Data[i].ID)
		{
			pLoadMonsterBMD(ModelID, gMonster.Data[i].Dir, gMonster.Data[i].BMDFile, -1);
			return;
		}
	}
	// ----
	pLoadMonsterBMD(ModelID, a2, a3, a4);
}
// ----------------------------------------------------------------------------------------------

void Monster::LoadMonsterTexture(signed int ModelID, char* a2, int a3, int a4)
{
	int MonsterID = ModelID - MONSTER_MODEL;
	// ----
	for(int i=0;i<gMonster.Count;i++)
	{
		if(MonsterID == gMonster.Data[i].ID)
		{
			pLoadMonsterTexture(ModelID, gMonster.Data[i].Folder, a3, a4);
			return;
		}
	}
	// ----
	pLoadMonsterTexture(ModelID, a2, a3, a4);
}
// ----------------------------------------------------------------------------------------------

void Monster::ShowMonster(int MonsterID, int a2, int a3, int a4)
{
	//__try
	//{
		for(int i=0;i<gMonster.Count;i++)
		{
			if(MonsterID == gMonster.Data[i].ID)
			{
				pLoadMonsterID(MonsterID);
				// ----
				DWORD ObjectStruct  = pVieweObject(a4, MonsterID + MONSTER_MODEL, a2, a3, 0.0);
				// -----
				lpViewObj Object	= &*(ObjectPreview*)ObjectStruct;
				// ----
				memcpy(Object->Name, gMonster.Data[i].Name, sizeof(gMonster.Data[i].Name));
				// ----
				if(gMonster.Data[i].Type == 0)
				{
					*(BYTE*)(ObjectStruct + 800) = emNPC;
				}
				else
				{
					*(BYTE*)(ObjectStruct + 800) = emMonster;
				}
				// ----
				*(float *)(ObjectStruct + 872) = gMonster.Data[i].Size;			
				// ----
				Object->ID = MonsterID;
				*(BYTE*)(ObjectStruct + 798) = 0;
				Object->Unknown128 = *(DWORD*)0x879343C;
				return;
			}	
		}
		// ----
		pShowMonster(MonsterID, a2, a3, a4);
	//}__except(EXCEPTION_EXECUTE_HANDLER)
	//{
	//}

		
}
// ----------------------------------------------------------------------------------------------

void Monster::SetMainAttribute(int ObjectPointer, int MonsterID)
{
	lpViewObj Object	= &*(ObjectPreview*)ObjectPointer;
	int MapClass		= pMapNumber - 9;	//ebp-4
	// ----
	if( MapClass > 0 && MapClass <= 8 && MonsterID >= 84 && MonsterID <= 143 )
	{
		Object->Unknown130				= 0;
		*(float*)(ObjectPointer + 872)	+= (double)(MapClass / 3) * 0.05;
	}
	// ----
	if( !Object )
	{
		return;
	}
	// ----

	for( int i = 0; i < MAX_MONSTER; i++ )
	{
		gMonster.lpNpcName[i] = *(NpcNameList*)(oNpcName + sizeof(NpcNameList) * i);
		// ----
		if( MonsterID == gMonster.lpNpcName[i].ObjectID )
		{
			memcpy(Object->Name, gMonster.lpNpcName[i].Name, sizeof(gMonster.lpNpcName[i].Name)-1);
			break;
		}
		else if( MonsterID == 579 )
		{
			memcpy(Object->Name, "David", sizeof("David"));
		}
		else if( MonsterID == 0 )
		{
			memcpy(Object->Name, "Bull Fighter", sizeof("Bull Fighter"));
		}
		else if ( MonsterID == 561 )
		{
			memcpy(Object->Name, "Medusa (Boss)", sizeof("Medusa (Boss)"));
		}
	}
	// ----
	Object->ID = MonsterID;
	*(BYTE*)(ObjectPointer + 798) = 0;
	Object->Unknown128 = *(DWORD*)0x879343C;
	// ----
	if( MonsterID == 200 )	//-> Soccerball
	{
		*(BYTE*)(ObjectPointer + 800) = emMonster;
	}
	else
	{
		if( MonsterID < 260 )
		{
			if( MonsterID <= 200 )
			{
				if( MonsterID < 150 )
				{
					if( MonsterID <= 110 )
					{
						if( MonsterID < 100 )
						{
							*(BYTE*)(ObjectPointer + 800)	= emMonster;
						}
						else
						{
							*(BYTE*)(ObjectPointer + 800)	= emNone;
						}
					}
					else
					{
						*(BYTE*)(ObjectPointer + 800) = emMonster;
					}
				}
				else
				{
					*(BYTE*)(ObjectPointer + 800)	= emMonster;
				}
			}
			else
			{
				*(BYTE*)(ObjectPointer + 800) = emNPC;
			}
		}
		else
		{
			*(BYTE*)(ObjectPointer + 800) = emMonster;
		}
	}
	// ----
	switch(MonsterID)
	{
		//-> 칸투르 npc
	case 367:	//-> Gateway Machine
	case 368:	//-> Elpis
		//-> 조화의 보석 관련 npc
	case 369:	//-> Osbourne
	case 370:	//-> Jerridon
		//-> 화이트엔젤 이벤트 아이템 지급 NPC 추가
	case 371:	//-> Leo the Helper
		//-> 카오스카드 담당
	case 375:	//-> Chaos Card Master
		//-> 공성전 신규 물약 NPC
	case 376:	//-> Pamela the Supplier
	case 377:	//-> Angela the Supplier
		//-> 설날 복주머니 이름
	case 379:	//-> Natasha the Firecracker Merchant
		//-> 신규 이벤트맵
	case 380:	//-> Stone Statue
	case 381:	//-> MU Allies General
	case 382:	//-> Illusion Sorcerer Elder
	case 383:	//-> Alliance Sacred Item Storage
	case 384:	//-> Illusion Castle Sacred Item Storage
	case 385:	//-> Mirage
		//-> 3차 체인지업
	case 406:	//-> Apostle Devin
	case 407:	//-> Werewolf Quarel
	case 408:	//-> Gatekeeper
		//-> 추석(2007)이벤트
	case 414:	//-> Helper Ellen
		//-> 엘베란드  NPC
	case 415:	//-> Silvia
	case 416:	//-> Rhea
	case 417:	//-> Marce
		//-> 벚꽃이벤트 npc 추가	
	case 450:	//-> Cherry Blossom Spirit
		//-> 소켓 시스템 NPC
	case 452:	//-> Seed Master
	case 453:	//-> Seed Researcher
		//-> 체험서버용 NPC 추가	
	case 464:	//-> Re-Initialization Helper
		//-> 크리스마스이벤트 NPC 추가(국내 적용 추가)
	case 465:	//-> Santa Claus
	case 467:	//-> Snowman
	case 468:	//-> Dasher
	case 469:	//-> Kermit
	case 470:	//-> Little Santa
	case 471:	//-> Cupid
	case 472:	//-> Prancer
	case 473:	//-> Donner
	case 474:	//-> Vixen
	case 475:	//-> Blitzen
		//-> 상용화 7주년 이벤트 NPC 추가
	case 478:	//-> Delgado
		//-> PK필드 몬스터 NPC 추가
	case 479:	//-> Doorkeeper Titus
		//-> 겜블 NPC 추가
	case 492:	//-> Moss
		//-> 일반 몬스터 NPC
	case 522:	//-> Jerint the Assistant
		//-> 도플갱어 몬스터 NPC
	case 540:	//-> Lugard
	case 541:	//-> Interim Reward Chest
	case 542:	//-> Final Reward Chest
		//-> 겐스 NPC
	case 543:	//-> Gens Duprian Steward
	case 544:	//-> Gens Vanert Steward
		//-> 로랜시장 NPC 추가
	case 545:	//-> Christine the General Goods Merchant
	case 546:	//-> Jeweler Raul
	case 547:	//-> Market Union Member Julia
		//-> 스켈레톤변신반지용 변신스켈레톤 추가
	case 566:	//-> Mercenary Guild Manager Tercia
	case 567:	//-> Priestess Veina
	case 568:	//-> Wandering Merchant Zyro
		//-> 칼루탄 NPC 추가 2010-06-30 홍승욱
	case 577:	//-> Leina the General Goods Merchant
	case 578:	//-> Weapons Merchant Bolo
		//-> 럭키아이템 NPC 추가 2010-09-01 이기수	
	case 579:	//-> David
		{
			*(BYTE*)(ObjectPointer + 800) = emNPC;
		}
		break;
	}
	// ----
	if( MonsterID >= 480 && MonsterID <= 491 )	//-> PK필드 몬스터
	{
		*(BYTE*)(ObjectPointer + 800) = emMonster;
	}
	// ----
	if( MonsterID == 451 )	//-> Cherry Blossom Tree
	{
		*(BYTE*)(ObjectPointer + 800) = emNone;
	}
	// ----
	//*(float *)(ObjectPointer + 872) = 0.5;
	//Object->m_Model.Scale = 0.5;
}
// ----------------------------------------------------------------------------------------------

char* Monster::GetMonsterName(int MOBID)
{
	for( int i = 0; i < MAX_MONSTER; i++ )
	{
		if(MOBID == gMonster.name_data[i].ObjectID)
		{
			return this->name_data[i].Name;
		}
	}
	return NULL;
}
// ----------------------------------------------------------------------------------------------

void Monster::FixMonsterVieweBug()
{
	if(pViewAttackTargetID == -1)
	{
		return;
	}

	if(!gObjUser.GetActiveSkill())
	{
		return;
	}

	lpViewObj lpObj	= &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), pViewAttackTargetID);
	
	if(!lpObj || !lpObj->m_Model.Unknown4)
	{
		return;
	}

	if(lpObj->m_Model.ObjectType != emMonster && lpObj->m_Model.ObjectType != emNPC)
	{
		return;
	}

	//if()
	{

	}

}
// ----------------------------------------------------------------------------------------------

struct PMSG_REQ_REVIEWE_ZT
{
	PBMSG_HEAD2 h;
	int TargetAttackIndex;
	int TargetAttackCount;
};

void CGReqReVieweEx()
{
	PMSG_REQ_REVIEWE_ZT pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xE5, sizeof(pMsg));
	pMsg.TargetAttackIndex = 0;
	pMsg.TargetAttackCount = 0;
	gProtocol.DataSend((LPBYTE)&pMsg, pMsg.h.size);	
}

void Monster::FixViewe()
{
	/*
	for(int i = 0; i < 400; i++)
	{
		lpViewObj lpObj = &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), i);

		if(!lpObj)
		{
			gConsole.Output(cRED, "[Monster::FixViewe] if(!lpObj) (%d) %d", i, lpObj->aIndex);
		}

		if(!lpObj->Unknown15)
		{
			gConsole.Output(cGREEN, "[Monster::FixViewe] if(!lpObj->Unknown15)(%d) %d", i, lpObj->aIndex);
		}

		if(!lpObj->m_Model.Unknown4)
		{
			gConsole.Output(cGREY, "[Monster::FixViewe] if(!lpObj->m_Model.Unknown4) (%d) %d", i, lpObj->aIndex);
		}

		if(lpObj->IsLiveObject)
		{
			gConsole.Output(cYELLOW, "[Monster::FixViewe] if(lpObj->IsLiveObject) (%d) %d", i, lpObj->aIndex);
		}

		continue;

	}
	*/
}
// ----------------------------------------------------------------------------------------------
//
//int sub_402BC0()
//{
//  return *(DWORD*)0xE7C224;
//}
//
////int __thiscall sub_96A340(int This, signed int a2)
//int sub_96A340(int This, signed int a2)
//{
//  int result; // eax@3
//
//  if ( a2 >= 0 && a2 < 400 )
//    result = *(DWORD *)(This + 8) + 1432 * a2;
//  else
//    result = 0;
//  return result;
//}
//
//char __cdecl sub_6D7F90(int a1, int a2, float a3, char a4, __int16 a5, char a6)
//{
//  void *v6; // esp@1
//  unsigned __int16 v7; // ax@3
//  char result; // al@4
//  float v9; // ST18_4@14
//  char v10; // ST14_1@31
//  char v11; // ST10_1@31
//  char v12; // ST0C_1@31
//  char v13; // ST08_1@31
//  void *v14; // eax@31
//  void *v15; // eax@31
//  void *v16; // eax@31
//  void *v17; // eax@31
//  void *v18; // eax@31
//  int v19; // ST14_4@33
//  void *v20; // eax@33
//  __int16 v21; // ST20_2@38
//  char v22; // ST14_1@38
//  char v23; // ST10_1@38
//  char v24; // ST0C_1@38
//  char v25; // ST08_1@38
//  void *v26; // eax@38
//  void *v27; // eax@38
//  void *v28; // eax@38
//  void *v29; // eax@38
//  void *v30; // eax@38
//  int v31; // ST14_4@40
//  void *v32; // eax@40
//  int j; // [sp+Ch] [bp-1078h]@38
//  char v34; // [sp+18h] [bp-106Ch]@38
//  int k; // [sp+824h] [bp-860h]@31
//  __int16 v36; // [sp+828h] [bp-85Ch]@31
//  int *v37; // [sp+82Ch] [bp-858h]@31
//  char v38; // [sp+830h] [bp-854h]@31
//  char v39; // [sp+103Bh] [bp-49h]@30
//  int v40; // [sp+103Ch] [bp-48h]@9
//  float v41; // [sp+1040h] [bp-44h]@14
//  int v42; // [sp+1044h] [bp-40h]@9
//  float v43; // [sp+1048h] [bp-3Ch]@14
//  float v44; // [sp+104Ch] [bp-38h]@14
//  int i; // [sp+1050h] [bp-34h]@6
//  int v46; // [sp+1054h] [bp-30h]@3
//  char v47; // [sp+105Bh] [bp-29h]@1
//  int v48; // [sp+105Ch] [bp-28h]@1
//  int v49[5]; // [sp+1060h] [bp-24h]@25
//  int v50; // [sp+1074h] [bp-10h]@1
//  int v51; // [sp+1080h] [bp-4h]@31
//
//  v6 = alloca(4208);
//  v50 = *(WORD *)(*(DWORD*)0x8128AC8 + 2 * a1 + 120);
//  v48 = 0;
//  v47 = 0;
//  if ( (unsigned __int8)sub_4DB0E0(*(DWORD*)0xE61E18) && sub_8CAF90() )
//  {
//    v7 = sub_5D6720(*(float *)a2, *(float *)(a2 + 4));
//    v46 = v7;
//    if ( v7 & 0x100 )
//      return 0;
//    v47 = 1;
//  }
//  for ( i = 0; i < 0x190; ++i )
//  {
//    sub_402BC0();
//    v42 = ((int (__stdcall *)(int))sub_96A340)(i);
//    v40 = v42 + 776;
//    if ( *(BYTE *)(v42 + 780) )
//    {
//      if ( *(BYTE *)(v40 + 12) )
//      {
//        if ( v42 != *(DWORD*)0x7BC4F04 && (*(BYTE *)(v42 + 36) != 0) != 1 )
//        {
//          v41 = *(float *)a2 - *(float *)(v40 + 252);
//          v44 = *(float *)(a2 + 4) - *(float *)(v40 + 256);
//          v9 = v41 * v41 + v44 * v44;
//          sub_4E3DB0(v9);
//          v43 = v9;
//          if ( a3 >= (double)v9
//            && (*(BYTE *)(v40 + 24) == 2 || *(BYTE *)(v40 + 24) == 1 && (*(WORD *)(v42 + 126) == a5 || v47)) )
//          {
//            if ( (v50 == 8 || v50 == 9 || v50 == 385 || v50 == 487) && !*(DWORD *)(v42 + 8) )
//              *(BYTE *)(v42 + 43) = 10;
//            v49[v48++] = *(WORD *)(v42 + 126);
//            if ( v48 >= 5 )
//              break;
//          }
//        }
//      }
//    }
//  }
//  if ( v48 <= 0 )
//  {
//    result = 0;
//  }
//  /*
//  else
//  {
//    if ( v50 != 78 && v50 != 0x206 )
//    {
//      if ( v50 != 235 && !sub_512DC0(dword_7BC4F04 + 56, (int)"webzen", 0) )
//      {
//        sub_404B40(&v34);
//        v51 = 1;
//        sub_404B90(&v34, 0xC1, 0xDB);
//        v21 = v50;
//        v22 = v48;
//        v23 = sub_5AB060(&a4);
//        v24 = sub_9CEA70(*(float *)(a2 + 4) / 100.0);
//        v25 = sub_9CEA70(*(float *)a2 / 100.0);
//        v26 = sub_4050D0(&v34, SHIBYTE(v21));
//        v27 = sub_4050D0(v26, v21);
//        v28 = sub_4050D0(v27, v25);
//        v29 = sub_4050D0(v28, v24);
//        v30 = sub_4050D0(v29, v23);
//        sub_4050D0(v30, v22);
//        for ( j = 0; j < v48; ++j )
//        {
//          v31 = v49[j] & 0xFF;
//          v32 = sub_4050D0(&v34, LOWORD(v49[j]) >> 8);
//          sub_4050D0(v32, v31);
//          sub_4050D0(&v34, a6);
//        }
//        sub_404D70(1, 0);
//        v51 = -1;
//        sub_404B60();
//      }
//    }
//    else
//    {
//      v39 = a6;
//      if ( !sub_512DC0(dword_7BC4F04 + 56, (int)"webzen", 0) )
//      {
//        sub_404B40(&v38);
//        v51 = 0;
//        sub_404B90(&v38, 0xC1, 0xDB);
//        v36 = v50;
//        v10 = v48;
//        v11 = sub_5AB060(&v39);
//        v12 = sub_9CEA70(*(float *)(a2 + 4) / 100.0);
//        v13 = sub_9CEA70(*(float *)a2 / 100.0);
//        v14 = sub_4050D0(&v38, SHIBYTE(v36));
//        v15 = sub_4050D0(v14, v36);
//        v16 = sub_4050D0(v15, v13);
//        v17 = sub_4050D0(v16, v12);
//        v18 = sub_4050D0(v17, v11);
//        sub_4050D0(v18, v10);
//        v37 = v49;
//        for ( k = 0; k < v48; ++k )
//        {
//          v19 = v37[k] & 0xFF;
//          v20 = sub_4050D0(&v38, LOWORD(v37[k]) >> 8);
//          sub_4050D0(v20, v19);
//          sub_4050D0(&v38, a6);
//        }
//        sub_404D70(1, 0);
//        v51 = -1;
//        sub_404B60();
//      }
//    }
//    result = 1;
//  }*/
//  return result;
//}
//// ----------------------------------------------------------------------------------------------
//
///*
//void Monster::CGReVieweExRecv(PMSG_REQ_REVIEWE_ZT*lpMsg, int aIndex)
//{
//	
//}
//*/