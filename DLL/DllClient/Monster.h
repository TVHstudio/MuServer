#pragma once

#include "stdafx.h"
#include "Object.h"
#include "Protocol.h"
// ----------------------------------------------------------------------------------------------

/*
.text:00661C70 ; void __cdecl ReceiveNotice(unsigned char *)

.text:00662080 ; void __cdecl ReceiveMovePosition(unsigned char *)
.text:006621B0 ; int __cdecl ReceiveTeleport(unsigned char *, int)

.text:00662AB0 ; void __cdecl ReceiveChangePlayer(unsigned char *)
.text:00663360 ; void __cdecl ReceiveCreatePlayerViewport(unsigned char *, int)
.text:00663A40 ; void __cdecl ReceiveCreateTransformViewport(unsigned char *)
.text:00663EF0 ; void __cdecl AppearMonster(struct CHARACTER *)
.text:00664590 ; void __cdecl ReceiveCreateMonsterViewport(unsigned char *)
.text:00664A50 ; void __cdecl ReceiveCreateSummonViewport(unsigned char *)
.text:00664DF0 ; void __cdecl ReceiveDeleteCharacterViewport(unsigned char *)

.text:00665040 ; void __cdecl ProcessDamageCastle(struct PRECEIVE_ATTACK *)
.text:006654D0 ; void __cdecl ReceiveAttackDamage(unsigned char *)
.text:00665DA0 ; void __cdecl ReceiveAction(unsigned char *, int)
.text:00666800 ; void __cdecl ReceiveSkillStatus(unsigned char *)
.text:00666A10 ; void __cdecl ReceiveMagicFinish(unsigned char *)
.text:00666FD0 ; void __cdecl SetPlayerBow(struct CHARACTER *)
.text:006671A0 ; void __cdecl SetPlayerHighBow(class CHARACTER *)
.text:00667340 ; int __cdecl ReceiveMonsterSkill(unsigned char *, int, int)
.text:0066BE10 ; void __cdecl ReceiveSkillCount(unsigned char *)
.text:0066C5D0 ; void __cdecl FallingStartCharacter(class CHARACTER *, class OBJECT *)
.text:0066C8E0 ; void __cdecl ReceiveDie(unsigned char *, int)
.text:0066CB90 ; void __cdecl ReceiveCreateItemViewport(unsigned char *)
.text:0066CCB0 ; void __cdecl ReceiveDeleteItemViewport(unsigned char *)

*/

// ----------------------------------------------------------------------------------------------

/*
	.text:006674A0 ; int __cdecl ReceiveMagic(unsigned char *, int, int)
	.text:0066A430 ; int __cdecl ReceiveMagicContinue(unsigned char *, int, int)
	.text:00666A10 ; void __cdecl ReceiveMagicFinish(unsigned char *)
	.text:0066BC00 ; void __cdecl ReceiveMagicPosition(unsigned char *, int)

	void __cdecl ReceiveMagicPosition(unsigned char *, int)
*/

// ----------------------------------------------------------------------------------------------

#define MAX_MONSTER		1024
#define MONSTER_MODEL	644
// ----------------------------------------------------------------------------------------------

#define pLoadMonsterBMD			((void(__cdecl*)(signed int a1, char* a2, char* a3, signed int a4)) 0x614D10)
#define pLoadMonsterTexture		((void(__cdecl*)(int a1, char* a2, int a3, signed int a4)) 0x614710)
#define pShowMonster			((double(__cdecl*)(int a1, int a2, int a3, int a4)) 0x580FC0)
#define pVieweObject			((int(__cdecl*)(int a1, signed int a2, unsigned __int8 a3, unsigned __int8 a4, float a5)) 0x57EEC0)
#define pLoadMonsterID			((int(__cdecl*)(signed int a1)) 0x61FDE0)
// ----------------------------------------------------------------------------------------------

struct Monster_DATA
{
	WORD ID;
	BYTE Type;
	char Name[25];
	char Dir[50];
	char Folder[50];
	char BMDFile[50];
	float Size;
};
// ----------------------------------------------------------------------------------------------

struct npcName_DATA  //-> Complete (size: 27)
{
	WORD	ObjectID;
	char	Name[25];
};
// ----------------------------------------------------------------------------------------------
/*
struct PMSG_REQ_REVIEWE_ZT
{
	PBMSG_HEAD2 h;
	int TargetAttackIndex;
};
*/
// ----------------------------------------------------------------------------------------------


class Monster
{
public:
	#if(DEBUG_MONSTER_LOAD)
   Monster();
   virtual ~Monster();
   #endif

	void			Load();
	void			ReadList(char * File);
	void			ReadName(char* File);
	// ----
	static void		LoadMonsterBMD(signed int ModelID, char* a2, char* a3, signed int a4);
	static void		LoadMonsterTexture(signed int ModelID, char* a2, int a3, int a4);
	static void		ShowMonster(int MonsterID, int a2, int a3, int a4);
	static void		SetMainAttribute(int ObjectPointer, int MonsterID);
	// ----
	char*			GetMonsterName(int MOBID);
	// ----
	void			FixMonsterVieweBug();
	void			FixViewe();
	void			GCIndexLive();
	
	// ----
	int				m_AttackCount;

	npcName_DATA	name_data[MAX_MONSTER];
	int				iLoadedName;
//private:
	NpcNameList		lpNpcName[MAX_MONSTER];
	Monster_DATA	Data[MAX_MONSTER];
	int				Count;
	// ----
}; extern Monster gMonster;
// ----------------------------------------------------------------------------------------------