#include "stdafx.h"
#include "Object.h"
#include "Cape.h"
#include "Defines.h"
#include "Interface.h"
#include "TMemory.h"
#include "Item.h"
#include "NewParty.h"
#include "Console.h"

#if(DEV_CAPE)

CCapeAnimation gCapeAnimation;

DWORD CapeEffectPointer;
DWORD CapeEffectBuff;

CCapeAnimation::CCapeAnimation()
{
}

CCapeAnimation::~CCapeAnimation()
{
}

__declspec(naked) void RemoveDarklordHair()
{
	static DWORD Address1 = 0x00574755;
	static DWORD Address2 = 0x005748FF;
	static DWORD dwClassDL = 0;

	//_asm
	//{
	//	Mov Eax, Dword Ptr Ss : [Ebp + 0x8]
	//	Movzx Edx, Byte Ptr Ds : [Eax + 0x13]
	//	And Edx, 0x7
	//	Cmp Edx, 0x4
	//	Jne EXIT
	//	Push 0xC0000205
	//	Jmp Address1
	//	EXIT:
	//	Jmp Address2
	//}

	_asm
	{
		MOV CapeEffectBuff, EAX
		Mov Eax, Dword Ptr Ss : [Ebp + 0x8]
		Movzx Edx, Byte Ptr Ds : [Eax + 0x13]
		And Edx, 0x7
		Cmp Edx, 0x4
		MOV dwClassDL, EDX
		mov EAX, CapeEffectBuff
	}

	if(dwClassDL == 4)
	{
		_asm
		{
			Push 0xC0000205
			Jmp Address1
		}
	}

	_asm
	{
		JMP Address2
	}
}

__declspec(naked) void CapeD() //allow play
{
	static DWORD Address1 = 0x00574683;
	static DWORD Address2 = 0x0057468F;

	_asm
	{
		Mov CapeEffectBuff, Ecx
		MOV DWORD PTR SS:[EBP-0x2D8],4
		MOV EAX,DWORD PTR SS:[EBP+0x8]
		MOVSX ECX,WORD PTR DS:[EAX+0x208]
		mov CapeEffectPointer,ecx
		mov ecx, CapeEffectBuff
	}

	if(CapeEffectPointer == ITEM2(12,40) || gCapeAnimation.IsCape(CapeEffectPointer, true))
	{
		_asm{jmp Address1}
	}
	else
	{
		_asm{jmp Address2}
	}	
}

__declspec(naked) void CapeA() // 0x7759 //-> 03 Main
{
	static DWORD Address1 = 0x00574F29;
	static DWORD Address2 = 0x005750C5;

	_asm
	{
		Mov CapeEffectBuff, ecx
		MOV EAX,DWORD PTR SS:[EBP+0x8]
		MOVSX ECX,WORD PTR DS:[EAX+0x208]
		Mov CapeEffectPointer,ecx
		Mov ecx, CapeEffectBuff
	}

	if(CapeEffectPointer == ITEM2(12,40) || gCapeAnimation.IsCape(CapeEffectPointer, true))
	{
		_asm{Jmp Address1}
	}
	else
	{
		_asm{Jmp Address2}
	}
}

__declspec(naked) void CapeB() //7758
{
	static DWORD Address1 = 0x00574915;
	static DWORD Address2 = 0x00574A6A;

	_asm
	{
		mov CapeEffectBuff, ecx
		MOV EAX,DWORD PTR SS:[EBP+0x8]
		MOVSX ECX,WORD PTR DS:[EAX+0x208]
		mov CapeEffectPointer,ecx
		mov ecx, CapeEffectBuff
	}

	if(CapeEffectPointer == ITEM2(12,40) || gCapeAnimation.IsCape(CapeEffectPointer, true))
	{
		_asm{Jmp Address1}
	}
	else
	{
		_asm{Jmp Address2}
	}	
}

__declspec(naked) void CapeE() //main allow
{
	static DWORD Address1 = 0x005760C2;
	static DWORD Address2 = 0x00576014;

	_asm
	{
		Mov CapeEffectBuff, ecx
		MOV EAX,DWORD PTR SS:[EBP+0x8]
		MOVSX ECX,WORD PTR DS:[EAX+0x208]
		Mov CapeEffectPointer,Ecx
		Mov Ecx, CapeEffectBuff
	}

	if(CapeEffectPointer == 0x1CBB|| CapeEffectPointer == 0x1D15 || CapeEffectPointer == 0x1EB1 || gCapeAnimation.IsCape(CapeEffectPointer, true))
	{
		_asm{jmp Address1}
	}
	else
	{
		_asm{jmp Address2}
	}	
}

__declspec(naked) void HideCape()
{
	static DWORD Address1 = 0x005FAD7D;
	static DWORD Address2 = 0x005FAE90;

	_asm
	{
		Mov Ecx, dword ptr ss : [ebp +0x10]
		Mov Dword ptr ss : [ebp +0x10], Ecx
		Mov CapeEffectPointer, Ecx
	}

	if (CapeEffectPointer == ITEM2(12,40) || gCapeAnimation.IsCape(CapeEffectPointer, true))
	{
		_asm{jmp Address1}
	}
	else
	{
		_asm{jmp Address2}
	}
}

__declspec(naked) void AllowMGCape() //?
{
	static DWORD Address1 = 0x00574D4C;
	static DWORD Address2 = 0x00574DAC;

	_asm
	{
		Mov CapeEffectBuff,Ecx
		Mov Eax,Dword Ptr Ss : [Ebp + 0x8]
		MOVZX ECX,BYTE Ptr Ds : [Eax + 0x13]
		Mov CapeEffectPointer,Ecx
		Mov Ecx, CapeEffectBuff
	}

	if (CapeEffectPointer == 3)
	{
		_asm{jmp Address1}
	}
	else
	{
		_asm{jmp Address2}
	}	
}

__declspec(naked) void CapeInventoryPos()
{
	static DWORD dwItem;

	//_asm
	//{
	//	Mov Ecx,DWORD PTR SS:[EBP+0x8]
	//	Mov dwItem,Ecx
	//	CMP dwItem,ITEM2(12,40)
	//	Je Exit	
	//	CMP dwItem,ITEM2(12,184)
	//	Je Exit
	//	CMP dwItem,ITEM2(12,194)
	//	Je Exit
	//	Exit:
	//	Mov Ecx,0x005CAFD2
	//	Jmp Ecx
	//}

	_asm
	{
		Mov Ecx,DWORD PTR SS:[EBP+0x8]
		Mov dwItem,Ecx
	}

	if(dwItem == ITEM2(12,40) || gCapeAnimation.IsCape(dwItem, true))
	{

		//gConsole.Output(cGREY,"CapeInventoryPos: %d", dwItem);
	}

	_asm
	{
		Mov Ecx,0x005CAFD2
		Jmp Ecx
	}
}

void CCapeAnimation::LoadIMG()
{
	//pLoadImage("ZtTeam\\Wings4\\darklordwing4de.tga", iCapeLvl4DL, GL_LINEAR, GL_REPEAT, GL_TRUE, 0);
	//pLoadImage("ZtTeam\\Wings4\\darklordwing4dd.tga", iCapeLvl4DL2, GL_LINEAR, GL_REPEAT, GL_TRUE, 0);
	//pLoadImage("ZtTeam\\Wings4\\darklordwing4df.tga", ITEM2(12,184), GL_LINEAR, GL_REPEAT, GL_TRUE, 0);
}

void CCapeAnimation::Model()
{
	pLoadModel(ITEM2(12,184), "Data\\ZtTeam\\Wings4\\", "Wings184", -1); // Wing51.bmd		- Lord Emperor
}

void CCapeAnimation::Texture()
{
	pLoadTexture(ITEM2(12,184), "ZtTeam\\Wings4\\", GL_REPEAT, GL_LINEAR, GL_TRUE); // Wing51.bmd		- Lord Emperor
	pLoadImage("ZtTeam\\Wings4\\darklordwing4de.tga", iCapeLvl4DL, GL_LINEAR, GL_REPEAT, GL_TRUE, 0);
	pLoadImage("ZtTeam\\Wings4\\darklordwing4dd.tga", iCapeLvl4DL2, GL_LINEAR, GL_REPEAT, GL_TRUE, 0);
}

bool CCapeAnimation::IsCape(WORD ItemID, bool Preview)
{
	if( Preview )
	{
		ItemID -= ITEM_INTER;
	}
	if( ItemID >= ITEM(12, 184) && ItemID <= ITEM(12, 184) )
	{
		return true;
	}
	return false;
}

bool CCapeAnimation::ResetPetPreview(int ItemId)
{
	if(gCapeAnimation.IsCape(ItemId, false))
	{
		gConsole.Output(cGREY,"ResetPetPreview: return true");
		return true;
	}

	gConsole.Output(cGREEN,"ResetPetPreview: return false");
	return false;
}

void CCapeAnimation::DrawViewPort(DWORD ObjectPointer, DWORD ObjectModel, DWORD a3)
{
	lpViewObj Object = &*(ObjectPreview*)(ObjectPointer);
	
	switch(Object->WingsSlot)
	{
	case ITEM2(12,40):
		SetDword((LPVOID)(0x0057491A + 1), iDLRedwing02);
		SetDword((LPVOID)(0x0057491F + 1), iDLRedwing02);

		SetDword((LPVOID)(0x00574F2E + 1), iDLRedwing03);
		SetDword((LPVOID)(0x00574F33 + 1), iDLRedwing03);

		SetDword((LPVOID)(0x00574FFC + 1), iDLRedwing03);
		SetDword((LPVOID)(0x00575001 + 1), iDLRedwing03);

		gConsole.Output(cGREY,"DrawViewPort: %d", Object->WingsSlot);
		break;
	case ITEM2(12, 184):
		SetDword((LPVOID)(0x0057491A + 1), iCapeLvl4DL);
		SetDword((LPVOID)(0x0057491F + 1), iCapeLvl4DL);

		SetDword((LPVOID)(0x00574F2E + 1), iCapeLvl4DL2);
		SetDword((LPVOID)(0x00574F33 + 1), iCapeLvl4DL2);

		SetDword((LPVOID)(0x00574FFC + 1), iCapeLvl4DL2);
		SetDword((LPVOID)(0x00575001 + 1), iCapeLvl4DL2);

		gConsole.Output(cGREY,"DrawViewPort: %d", Object->WingsSlot);
		break;
	}

	gConsole.Output(cGREEN,"DrawViewPort");

	pDrawViewPort(ObjectPointer, ObjectModel,  a3);
}

void CCapeAnimation::RefreshCapeUnEquip(ObjectItem * lpItem)
{

	if(gCapeAnimation.IsCape(lpItem->ItemID, true))
	{
		gConsole.Output(cGREY,"RefreshCapeUnEquip: pRefreshViewport");
		pRefreshViewport(oUserPreviewStruct, oUserPreviewStruct + 776, 0);
	}
	
	gConsole.Output(cGREEN,"RefreshCapeUnEquip: pRefreshCape1");
	pRefreshCape1(lpItem);
}

void CCapeAnimation::RefreshViewPortItem(int a1)
{
	signed int v1; // ST14_4@1
	int result; // eax@1
	int v6; // [sp+Ch] [bp-14h]@2
	int v7; // [sp+10h] [bp-10h]@1
	int v8; // [sp+14h] [bp-Ch]@2
	BYTE v9; // [sp+1Dh] [bp-3h]@2
	BYTE v10; // [sp+1Eh] [bp-2h]@2
	BYTE v11; // [sp+1Fh] [bp-1h]@2

	v1 = sub_57D9A0(*(BYTE *)(a1 + 4) + (*(BYTE *)(a1 + 3) << 8));
	result = sub_96A4C0(sub_402BC0(), v1);
	v7 = result;

	if (result)
	{
		v6 = result + 776;
		v8 = sub_58AA80(a1 + 5);
		v11 = *(BYTE *)(a1 + 6) & 0xF;
		v10 = *(BYTE *)(a1 + 8) & 0x3F;
		v9 = *(BYTE *)(a1 + 9);

		switch ((signed int)*(BYTE *)(a1 + 6) >> 4)
		{
		case 7:
			if (v8 == 0x1FFF)
			{
				if(gCapeAnimation.IsCape(*(WORD*)(v7 + 520), true))
				{
					sub_558630(v7, v6, 0);
				}

				*(WORD *)(v7 + 520) = -1;

				gConsole.Output(cGREY,"RefreshViewPortItem: -1");
			}
			else
			{
				*(WORD *)(v7 + 520) = v8 + 1171;
				*(BYTE *)(v7 + 522) = 0;

				if(gCapeAnimation.IsCape(*(WORD*)(v7 + 520), true))
				{
					sub_558630(v7, v6, 0);
				}

				gConsole.Output(cGREY,"RefreshViewPortItem: %d", *(WORD *)(v7 + 520));
			}
			break;
		default:
			break;
		}
	}

	((void(*)(int))0x6411A0)(a1);
}

void CCapeAnimation::Load()
{
	this->ReLoad();

	return;

	// ----

	SetRange((LPVOID)0x00574667,20,ASM::NOP);
	SetOp((LPVOID)0x00574667,(LPVOID)CapeD,ASM::JMP);

	SetRange((LPVOID)0x005748FF,10,ASM::NOP);
	SetOp((LPVOID)0x005748FF,(LPVOID)CapeB,ASM::JMP);

	SetRange((LPVOID)0x00574F13,10,ASM::NOP);
	SetOp((LPVOID)0x00574F13,(LPVOID)CapeA,ASM::JMP);

	SetRange((LPVOID)0x00576058,10,ASM::NOP);
	SetOp((LPVOID)0x00576058,(LPVOID)CapeE,ASM::JMP);

	SetRange((LPVOID)0x005FAD70,7,ASM::NOP);
	SetOp((LPVOID)0x005FAD70,(LPVOID)HideCape,ASM::JMP);

	SetRange((LPVOID)0x00574D3D,13,ASM::NOP);
	SetOp((LPVOID)0x00574D3D,(LPVOID)AllowMGCape,ASM::JMP);

	//SetRange((LPVOID)0x005CAFCB,7,ASM::NOP);
	//SetOp((LPVOID)0x005CAFCB,(LPVOID)CapeInventoryPos,ASM::JMP);

	// ----

	SetOp((LPVOID)0x00572346, (LPVOID)0x00572370, ASM::JMP); //Apply
	SetOp((LPVOID)0x0057464E, (LPVOID)0x00574667, ASM::JMP); //Apply
	SetOp((LPVOID)0x00574750, (LPVOID)RemoveDarklordHair, ASM::JMP);

	SetOp((LPVOID)0x00833A97,(LPVOID)this->RefreshCapeUnEquip,ASM::CALL);	//OK

	SetOp((LPVOID)0x0040487D,(LPVOID)this->DrawViewPort,ASM::CALL);
	SetOp((LPVOID)0x0048E56C,(LPVOID)this->DrawViewPort,ASM::CALL);
	SetOp((LPVOID)0x0057D4FF,(LPVOID)this->DrawViewPort,ASM::CALL);
	SetOp((LPVOID)0x0057D513,(LPVOID)this->DrawViewPort,ASM::CALL);

	// ----

	//SetOp((LPVOID)0x00836331,(LPVOID)this->ResetPetPreview,ASM::CALL);
	//SetOp((LPVOID)0x00664117, (LPVOID)this->RefreshViewPortItem, ASM::CALL);
}

void CCapeAnimation::ReLoad()
{
	//SetOp((LPVOID)0x00574915, (LPVOID)0x00574915, ASM::JMP);
	SetRange((LPVOID)0x0057490F, 6, ASM::NOP);
	
	//00574915
	SetOp((LPVOID)0x00574648, (LPVOID)0x00574667, ASM::JMP);


	/*
	0x005746E4
	00574909
	00574F2E
	00574FFC
	00575001
	0057468F
	*/

}

#endif

