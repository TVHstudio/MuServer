#pragma once

#if(DEV_CAPE)

/*
	//SetCompleteHook(0xFF,0x0040487D, &this->DrawViewPort);
	//SetCompleteHook(0xFF,0x0048E56C, &this->DrawViewPort);
	//SetCompleteHook(0xFF,0x0057D4FF, &this->DrawViewPort);
	//SetCompleteHook(0xFF,0x0057D513, &this->DrawViewPort);
	//-
	//SetOp((LPVOID)0x664267, RefreshViewPortItem, ASM::CALL);
	//-
	//SetRange((LPVOID)0x00574667,20,ASM::NOP);
	//SetOp((LPVOID)0x00574667,(LPVOID)CapeD,ASM::JMP);
	////-
	//SetRange((LPVOID)0x005748FF,10,ASM::NOP);
	//SetOp((LPVOID)0x005748FF,(LPVOID)CapeB,ASM::JMP);
	////-
	//SetRange((LPVOID)0x00574F13,10,ASM::NOP);
	//SetOp((LPVOID)0x00574F13,(LPVOID)CapeA,ASM::JMP);
	////-
	//SetRange((LPVOID)0x00576058,10,ASM::NOP);
	//SetOp((LPVOID)0x00576058,(LPVOID)CapeE,ASM::JMP);
	////-
	//SetRange((LPVOID)0x005FAD70,7,ASM::NOP);
	//SetOp((LPVOID)0x005FAD70,(LPVOID)HideCape,ASM::JMP);
	////-
	//SetRange((LPVOID)0x00574D3D,13,ASM::NOP);
	//SetOp((LPVOID)0x00574D3D,(LPVOID)AllowMGCape,ASM::JMP);
	//SetOp((LPVOID)0x00836481,ResetPetPreviewEx,ASM::CALL);
	//SetOp((LPVOID)0x00833BE7,(LPVOID)RefreshCapeUnEquip,ASM::CALL);
	////-
	//SetRange((LPVOID)0x005CAFCB,7,ASM::NOP);
	//SetOp((LPVOID)0x005CAFCB,(LPVOID)CapeInventoryPos,ASM::JMP);
*/

/*
	//SetCompleteHook(0xE9, 0x00572346, 0x00572370); //Apply
	//SetCompleteHook(0xE9, 0x0057464E, 0x00574667); //Apply
	//SetCompleteHook(0xE9, 0x00574750, &RemoveDarklordHair);

	//SetCompleteHook(0xFF,0x0040487D, &this->DrawViewPort);
	//SetCompleteHook(0xFF,0x0048E56C, &this->DrawViewPort);
	//SetCompleteHook(0xFF,0x0057D4FF, &this->DrawViewPort);
	//SetCompleteHook(0xFF,0x0057D513, &this->DrawViewPort);

	//SetRange((LPVOID)0x00574667,20,ASM::NOP);
	//SetOp((LPVOID)0x00574667,(LPVOID)CapeD,ASM::JMP);

	//SetRange((LPVOID)0x005748FF,10,ASM::NOP);
	//SetOp((LPVOID)0x005748FF,(LPVOID)CapeB,ASM::JMP);

	//SetRange((LPVOID)0x00574F13,10,ASM::NOP);
	//SetOp((LPVOID)0x00574F13,(LPVOID)CapeA,ASM::JMP);

	//SetRange((LPVOID)0x00576058,10,ASM::NOP);
	//SetOp((LPVOID)0x00576058,(LPVOID)CapeE,ASM::JMP);

	//SetRange((LPVOID)0x005FAD70,7,ASM::NOP);
	//SetOp((LPVOID)0x005FAD70,(LPVOID)HideCape,ASM::JMP);

	//SetRange((LPVOID)0x00574D3D,13,ASM::NOP);
	//SetOp((LPVOID)0x00574D3D,(LPVOID)AllowMGCape,ASM::JMP);

	//SetOp((LPVOID)0x00833A97,(LPVOID)RefreshCapeUnEquip,ASM::CALL);	//OK

	//SetRange((LPVOID)0x005CAFCB,7,ASM::NOP);
	//SetOp((LPVOID)0x005CAFCB,(LPVOID)CapeInventoryPos,ASM::JMP);

	//SetOp((LPVOID)0x0040487D,(LPVOID)this->DrawViewPort,ASM::CALL);
	//SetOp((LPVOID)0x0048E56C,(LPVOID)this->DrawViewPort,ASM::CALL);
	//SetOp((LPVOID)0x0057D4FF,(LPVOID)this->DrawViewPort,ASM::CALL);
	//SetOp((LPVOID)0x0057D513,(LPVOID)this->DrawViewPort,ASM::CALL);

	//SetOp((LPVOID)0x00572346, (LPVOID)0x00572370, ASM::JMP); //Apply
	//SetOp((LPVOID)0x0057464E, (LPVOID)0x00574667, ASM::JMP); //Apply
	//SetOp((LPVOID)0x00574750, (LPVOID)RemoveDarklordHair, ASM::JMP);

	//SetOp((LPVOID)0x00836331,ResetPetPreviewEx,ASM::CALL);
	//SetOp((LPVOID)0x00664117, RefreshViewPortItem, ASM::CALL);
*/

enum InterfaceID
{
	iDLRedwing02  = 0x7758,
	iDLRedwing03  = 0x7759,
	iCapeLvl4DL   = 0x78A5,
	iCapeLvl4DL2  = 0x78A6,
};

#define pDrawViewPort		((int(__cdecl*)(DWORD ObjectPointer, DWORD ModelPointer, int a3)) 0x56F210)
#define pRefreshViewport	((void(__cdecl*)(DWORD a1, DWORD a2, int a3)) 0x558630)
#define pRefreshCape1		((void(__stdcall*)(ObjectItem * lpItem)) 0x00836280)	//OK
#define pObjOnViewport		((int(__cdecl*)(int Object))0x5F61C0)
#define sub_57D9A0			((DWORD(__cdecl*)(DWORD)) 0x57D9A0)
#define sub_96A4C0			((int(__thiscall*)(LPVOID This, signed int a2)) 0x96A4C0)
#define sub_402BC0			((LPVOID(*)())0x402BC0)
#define sub_58AA80			((DWORD(__cdecl*)(DWORD)) 0x58AA80)
#define sub_558630			((void(__cdecl*)(int a1, int a2, int a3)) 0x558630)
#define sub_5012D0			((DWORD(__cdecl*)(DWORD)) 0x5012D0)
#define sub_9253D0			((int(__thiscall*)(LPVOID This,int a1, short a2)) 0x9253D0)//?
#define sub_4DB230			((LPVOID(*)())0x4DB230)
#define sub_501700			((DWORD(__cdecl*)(DWORD, DWORD, DWORD, DWORD, DWORD)) 0x501700)

class CCapeAnimation
{
public:
	CCapeAnimation();
	~CCapeAnimation();

	void ReLoad();
	void Load();
	void LoadIMG();
	void Model();
	void Texture();
	bool IsCape(WORD ItemID, bool Preview);

	static bool ResetPetPreview(int ItemId);
	static void DrawViewPort(DWORD ObjectPointer, DWORD ModelPointer, DWORD a3);
	static void RefreshCapeUnEquip(ObjectItem * lpItem);
	static void RefreshViewPortItem(int a1);
};

extern CCapeAnimation gCapeAnimation;

#endif