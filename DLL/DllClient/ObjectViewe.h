#pragma once

#if(FIX_OBJECT_VIEWE)

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

#define OBJECTVIEWE_MAX			400

#define OBJECTVIEWE_RANGE(x)	(((x)<FALSE)?FALSE:((x)>=OBJECTVIEWE_MAX)?FALSE:TRUE)

struct PMSG_OBJECT_LIVE
{
	PBMSG_HEAD2 h;
	int ObjectIndex;
	WORD ObjectType;
	BYTE ObjectLive;
};

class CObjectViewe
{
public:
		CObjectViewe();
		~CObjectViewe();

	void Load();

	void ClearLive(int ObjectIndex);

	int CheckLive(int ObjectIndex);
	
	void GCIndexLive(PMSG_OBJECT_LIVE* lpMsg);

	bool m_Active;

};

extern CObjectViewe g_ObjectViewe;


#endif