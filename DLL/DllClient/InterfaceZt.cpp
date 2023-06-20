#include "stdafx.h"
#include "InterfaceZt.h"
#include "Defines.h"
#include "TMemory.h"
#include "Configs.h"

__declspec(naked) void AGPositionZt()
{
	static float AGPositionW = 61.0f;
	static float AGPositionH = 8.0f;
	static float AGPositionX = 383.0f;
	static float AGPositionY = 431.0f;
	static DWORD AGPosition_buff = 0x008102AD-0x150;
	_asm
	{	
	FLD DWORD PTR DS:[AGPositionW]
	FSTP DWORD PTR SS:[EBP-0x18]
	FLD DWORD PTR DS:[AGPositionH]
	FSTP DWORD PTR SS:[EBP-0x14]
	FLD DWORD PTR DS:[AGPositionX]
	FSTP DWORD PTR SS:[EBP-0x10]
	FLD DWORD PTR DS:[AGPositionY]
	FSTP DWORD PTR SS:[EBP-0x0C]
	jmp [AGPosition_buff]
	}
}
__declspec(naked) void SDPositionZt()
{
	static float SDPositionW = 61.0f;
	static float SDPositionH = 8.0f;
	static float SDPositionX = 196.0f;
	static float SDPositionY = 431.0f;
	static DWORD SDPosition_buff = 0x0081057D-0x150;
	_asm
	{	
	FLD DWORD PTR DS:[SDPositionW]
	FSTP DWORD PTR SS:[EBP-0x20]
	FLD DWORD PTR DS:[SDPositionH]
	FSTP DWORD PTR SS:[EBP-0x1C]
	FLD DWORD PTR DS:[SDPositionX]
	FSTP DWORD PTR SS:[EBP-0x10]
	FLD DWORD PTR DS:[SDPositionY]
	FSTP DWORD PTR SS:[EBP-0x0C] 
	jmp [SDPosition_buff]
	}
}
__declspec(naked) void MANAPositionZt()
{
	static float MANAPositionW = 52.0f;
	static float MANAPositionX = 448.0f;
	static float MANAPositionH = 54.0f;
	static float MANAPositionY = 415.0f;
	static DWORD MANAPosition_buff = 0x0080FE80;
	_asm
	{	
	FLD DWORD PTR DS:[MANAPositionW]
	FSTP DWORD PTR SS:[EBP-0x20]
	FLD DWORD PTR DS:[MANAPositionX]
	FSTP DWORD PTR SS:[EBP-0x0C]
	FLD DWORD PTR DS:[MANAPositionH]
	FSTP DWORD PTR SS:[EBP-0x1C]
	FLD DWORD PTR DS:[MANAPositionY]
	FSTP DWORD PTR SS:[EBP-0x8]
	jmp [MANAPosition_buff]
	}
}

//#define pDrawCircle				((void(__cdecl*)(DWORD ModelID, float Arg2, float Arg3, float Arg4, float Arg5, float Arg6, float Arg7, float Arg8, float Arg9, bool Arg10, bool Arg11, float Arg12)) 0x637C60)
void __cdecl pDrawCircleMana(DWORD ModelID, float Arg2, float Arg3, float Arg4, float Arg5, float Arg6, float Arg7, float Arg8, float Arg9, bool Arg10, bool Arg11, float Arg12)
{
	
}

__declspec(naked) void HPPositionZt()
{
	static float HPPositionW = 51.0f;
	static float HPPositionX = 135.0f;
	static float HPPositionH = 52.0f;
	static float HPPositionY = 414.0f;
	static DWORD HPPosition_buff = 0x0080FD7C-0x150;
	_asm
	{             
	FLD DWORD PTR DS:[HPPositionW]
	FSTP DWORD PTR SS:[EBP-0x20]
	FLD DWORD PTR DS:[HPPositionX]
	FSTP DWORD PTR SS:[EBP-0x0C]
	FLD DWORD PTR DS:[HPPositionH]
	FSTP DWORD PTR SS:[EBP-0x1C]
	FLD DWORD PTR DS:[HPPositionY]
	FSTP DWORD PTR SS:[EBP-0x8]
	jmp [HPPosition_buff]
	}
}

__declspec(naked) void UsingSkillPositionZt()
{
	static float UsingSkillPositionX = 309.8f;
	static float UsingSkillPositionY = 442.5f;
	static float UsingSkillPositionW = 20.0f;
	static float UsingSkillPositionH = 28.0f;
	static DWORD UsingSkillPosition_buff = 0x00813900-0x150;
	_asm
	{
	FLD DWORD PTR DS:[UsingSkillPositionX]
	FSTP DWORD PTR SS:[EBP-0x8]
	FLD DWORD PTR DS:[UsingSkillPositionY]
	FSTP DWORD PTR SS:[EBP-0x4]
	FLD DWORD PTR DS:[UsingSkillPositionW]
	FSTP DWORD PTR SS:[EBP-0x18]
	FLD DWORD PTR DS:[UsingSkillPositionH]
	FSTP DWORD PTR SS:[EBP-0x14]
	jmp [UsingSkillPosition_buff]
	}
}
__declspec(naked) void SkillClickPositionZt()
{
	static float SkillClickPositionX = 310.0f;
	static float SkillClickPositionY = 443.0f;
	static float SkillClickPositionW = 20.0f;
	static float SkillClickPositionH = 27.0f;
	static DWORD SkillClickPosition_buff = 0x00812734-0x150;
	_asm
	{
	FLD DWORD PTR DS:[SkillClickPositionX]
	FSTP DWORD PTR SS:[EBP-0x8]
	FLD DWORD PTR DS:[SkillClickPositionY]
	FSTP DWORD PTR SS:[EBP-0x4]
	FLD DWORD PTR DS:[SkillClickPositionW]
	FSTP DWORD PTR SS:[EBP-0x20]
	FLD DWORD PTR DS:[SkillClickPositionH]
	FSTP DWORD PTR SS:[EBP-0x1C]
	jmp [SkillClickPosition_buff]
	}
}
__declspec(naked) void SkillBarDrawPositionZt()
{
	static float SkillBarDrawPositionX = 222.0f;
	static float SkillBarDrawPositionY = 480.0f;
	static float SkillBarDrawPositionW = 160.0f;
	static float SkillBarDrawPositionH = 38.0f;
	static DWORD SkillBarDrawPosition_buff = 0x00812968-0x150;
	_asm
	{	
	FLD DWORD PTR DS:[SkillBarDrawPositionX]
	FSTP DWORD PTR SS:[EBP-0x8]
	FLD DWORD PTR DS:[SkillBarDrawPositionY]
	FSTP DWORD PTR SS:[EBP-0x4]
	FLD DWORD PTR DS:[SkillBarDrawPositionW]
	FSTP DWORD PTR SS:[EBP-0x20]
	FLD DWORD PTR DS:[SkillBarDrawPositionH]
	FSTP DWORD PTR SS:[EBP-0x1C]
	jmp [SkillBarDrawPosition_buff]
	}
}
__declspec(naked) void SkillSwitchDrawZt()
{
	static float SkillSwitchDrawX = 385.0f;
	static float SkillSwitchDrawY = 380.0f;
	static float SkillSwitchDrawW = 32.0f;
	static float SkillSwitchDrawH = 38.0f;
	static float SkillSwitchDrawMW = 385.0f;
	static DWORD SkillSwitchDraw_buff = 0x008139CA-0x150;
	_asm
	{
		FLD DWORD PTR DS:[SkillSwitchDrawX]
		FSTP DWORD PTR SS:[EBP-0x8]
		FLD DWORD PTR DS:[SkillSwitchDrawY]
		FSTP DWORD PTR SS:[EBP-0x4]	
		FLD DWORD PTR DS:[SkillSwitchDrawW]
		FSTP DWORD PTR SS:[EBP-0x18]
		FLD DWORD PTR DS:[SkillSwitchDrawH]
		FSTP DWORD PTR SS:[EBP-0x14]
		FLD DWORD PTR DS:[SkillSwitchDrawMW]
		FSTP DWORD PTR SS:[EBP-0x24]
		jmp [SkillSwitchDraw_buff]
	}
}
__declspec(naked) void SkillSwitchClickZt()
{
	static float SkillSwitchDrawX = 385.0f;
	static float SkillSwitchDrawY = 380.0f;
	static float SkillSwitchDrawW = 32.0f;
	static float SkillSwitchDrawH = 38.0f;
	static float SkillSwitchDrawMW = 385.0f;
	static DWORD SkillSwitchClick_buff = 0x00812D69-0x150;
	_asm
	{
		FLD DWORD PTR DS:[SkillSwitchDrawX]
		FSTP DWORD PTR SS:[EBP-0x8]
		FLD DWORD PTR DS:[SkillSwitchDrawY]
		FSTP DWORD PTR SS:[EBP-0x4]
		FLD DWORD PTR DS:[SkillSwitchDrawW]
		FSTP DWORD PTR SS:[EBP-0x20]
		FLD DWORD PTR DS:[SkillSwitchDrawH]
		FSTP DWORD PTR SS:[EBP-0x1C]
		FLD DWORD PTR DS:[SkillSwitchDrawMW]
		FSTP DWORD PTR SS:[EBP-0x14]
		jmp [SkillSwitchClick_buff]
	}
}
__declspec(naked) void SkillBarraZt()
{
	static float SkillBarraX = 307.0f;
	static float SkillBarraY = 436.5f;
	static float SkillBarraW = 20.0f;
	static float SkillBarraH = 32.0f;
	static DWORD SkillBarra_buff = 0x0081379A-0x150;
	_asm
	{	
	FLD DWORD PTR DS:[SkillBarraX]
	FSTP DWORD PTR SS:[EBP-0x8]
	FLD DWORD PTR DS:[SkillBarraY]
	FSTP DWORD PTR SS:[EBP-0x4]
	FLD DWORD PTR DS:[SkillBarraW]
	FSTP DWORD PTR SS:[EBP-0x18]
	FLD DWORD PTR DS:[SkillBarraH]
	FSTP DWORD PTR SS:[EBP-0x14]
	jmp [SkillBarra_buff]
	}
}
__declspec(naked) void QPosition1Zt()
{
	static float BarNumberY = 455.0f;
	static DWORD QPosition1_buff = 0x00895A4F-0x150;
	_asm
	{
	FLD DWORD PTR DS:[BarNumberY]
	FSTP DWORD PTR SS:[ESP]
	jmp [QPosition1_buff]
	}
}
__declspec(naked) void QPosition2Zt()
{
	static float QPosition2X = 222.0f;
	static DWORD QPosition2_buff = 0x00895A59-0x150;
	_asm
	{
	FLD DWORD PTR DS:[QPosition2X]
	FSTP DWORD PTR SS:[ESP]
	jmp [QPosition2_buff]
	}
}
__declspec(naked) void QPosition3Zt()
{
	static float BarPotionY = 446.0f;
	static DWORD QPosition3_buff = 0x00895A63-0x150;
	_asm
	{
	FLD DWORD PTR DS:[BarPotionY]
	FSTP DWORD PTR SS:[ESP]
	jmp [QPosition3_buff]
	}
}
__declspec(naked) void QPosition4Zt()
{
	static float QPosition4X = 204.0f;
	static DWORD QPosition4_buff = 0x00895A6D-0x150;
	_asm
	{
	FLD DWORD PTR DS:[QPosition4X]
	FSTP DWORD PTR SS:[ESP]
	jmp [QPosition4_buff]
	}
}
__declspec(naked) void WPosition1Zt()
{
	static float BarNumberY = 455.0f;
	static DWORD WPosition1_buff = 0x00895AC4-0x150;
	_asm
	{
	FLD DWORD PTR DS:[BarNumberY]
	FSTP DWORD PTR SS:[ESP]
	jmp [WPosition1_buff]
	}
}
__declspec(naked) void WPosition2Zt()
{
	static float WPosition2X = 249.0f;
	static DWORD WPosition2_buff = 0x00895ACE-0x150;
	_asm
	{
	FLD DWORD PTR DS:[WPosition2X]
	FSTP DWORD PTR SS:[ESP]
	jmp [WPosition2_buff]
	}
}
__declspec(naked) void WPosition3Zt()
{
	static float BarPotionY = 446.0f;
	static DWORD WPosition3_buff = 0x00895AD8-0x150;
	_asm
	{
	FLD DWORD PTR DS:[BarPotionY]
	FSTP DWORD PTR SS:[ESP]
	jmp [WPosition3_buff]
	}
}
__declspec(naked) void WPosition4Zt()
{
	static float WPosition4X = 231.0f;
	static DWORD WPosition4_buff = 0x00895AE2-0x150;
	_asm
	{
	FLD DWORD PTR DS:[WPosition4X]
	FSTP DWORD PTR SS:[ESP]
	jmp [WPosition4_buff]
	}
}
__declspec(naked) void EPosition1Zt()
{
	static float BarNumberY = 455.0f;
	static DWORD EPosition1_buff = 0x00895B39-0x150;
	_asm
	{
	FLD DWORD PTR DS:[BarNumberY]
	FSTP DWORD PTR SS:[ESP]
	jmp [EPosition1_buff]
	}
}
__declspec(naked) void EPosition2Zt()
{
	static float EPosition2X = 275.0f;
	static DWORD EPosition2_buff = 0x00895B43-0x150;
	_asm
	{
	FLD DWORD PTR DS:[EPosition2X]
	FSTP DWORD PTR SS:[ESP]
	jmp [EPosition2_buff]
	}
}
__declspec(naked) void EPosition3Zt()
{
	static float BarPotionY = 446.0f;
	static DWORD EPosition3_buff = 0x00895B4D-0x150;
	_asm
	{
	FLD DWORD PTR DS:[BarPotionY]
	FSTP DWORD PTR SS:[ESP]
	jmp [EPosition3_buff]
	}
}
__declspec(naked) void EPosition4Zt()
{
	static float EPosition4X = 257.0f;
	static DWORD EPosition4_buff = 0x00895B57-0x150;
	_asm
	{
	FLD DWORD PTR DS:[EPosition4X]
	FSTP DWORD PTR SS:[ESP]
	jmp [EPosition4_buff]
	}
}
_declspec(naked) void RPosition1Zt()
{
	static float BarNumberY = 455.0f;
	static DWORD EPosition1_buff = 0x00895BAE-0x150;
	_asm
	{
	FLD DWORD PTR DS:[BarNumberY]
	FSTP DWORD PTR SS:[ESP]
	jmp [EPosition1_buff]
	}
}
__declspec(naked) void RPosition2Zt()
{
	static float RPosition2X = 301.0f;
	static DWORD RPosition2_buff = 0x00895BB8-0x150;
	_asm
	{
	FLD DWORD PTR DS:[RPosition2X]
	FSTP DWORD PTR SS:[ESP]
	jmp [RPosition2_buff]
	}
}
__declspec(naked) void RPosition3Zt()
{
	static float BarPotionY = 446.0f;
	static DWORD RPosition3_buff = 0x00895BC2-0x150;
	_asm
	{
	FLD DWORD PTR DS:[BarPotionY]
	FSTP DWORD PTR SS:[ESP]
	jmp [RPosition3_buff]
	}
}
__declspec(naked) void RPosition4Zt()
{
	static float RPosition4X = 283.0f;
	static DWORD RPosition4_buff = 0x00895BCC-0x150;
	_asm
	{
	FLD DWORD PTR DS:[RPosition4X]
	FSTP DWORD PTR SS:[ESP]
	jmp [RPosition4_buff]
	}
}

__declspec(naked) void AGNumberPositionZt()
{
	static float AGNumberPositionX = 35.0f;
	static DWORD AGNumberPosition_buff = 0x0081037F-0x150;
	_asm
	{
	FADD DWORD PTR DS:[AGNumberPositionX]
	FSTP DWORD PTR SS:[EBP-0x154]
	FLD DWORD PTR SS:[EBP-0x154]
	jmp [AGNumberPosition_buff]
	}
}

__declspec(naked) void SDNumberPositionZt()
{
	static float SDNumberPositionX = 35.0f;
	static DWORD SDNumberPosition_buff = 0x0081064F-0x150;
	_asm
	{
	FADD DWORD PTR DS:[SDNumberPositionX]
	FSTP DWORD PTR SS:[EBP-0x154]
	FLD DWORD PTR SS:[EBP-0x154]
	jmp [SDNumberPosition_buff]
	}
}

__declspec(naked) void HPNumberPositionZt()
{
	static float HPNumberPositionX = 30.0f;
	static DWORD HPNumberPosition_buff = 0x0080FF1E-0x150;
	_asm
	{
	FADD DWORD PTR DS:[HPNumberPositionX]
	FSTP DWORD PTR SS:[EBP-0x19C]
	FLD DWORD PTR SS:[EBP-0x19C]
	jmp [HPNumberPosition_buff]
	}
}

__declspec(naked) void HPNumberPosition2Zt()
{
	static float HPNumberPositionY = 450.0f;
	static DWORD HPNumberPosition2_buff = 0x0080FF0F-0x150;
	_asm
	{	
	FLD DWORD PTR DS:[HPNumberPositionY]
	FSTP DWORD PTR SS:[ESP]
	FLD DWORD PTR SS:[EBP-0xC]
	jmp [HPNumberPosition2_buff]
	}
}

__declspec(naked) void MANANumberPositionZt()
{
	static float MANANumberPositionX = 25.0f;
	static DWORD MANANumberPosition_buff = 0x008100B1-0x150;
	_asm
	{
	FADD DWORD PTR DS:[MANANumberPositionX]
	FSTP DWORD PTR SS:[EBP-0x1AC]
	FLD DWORD PTR SS:[EBP-0x1AC]
	jmp [MANANumberPosition_buff]
	}
}
//EXP
__declspec(naked) void EXP1Zt()
{
	static float EXP1 = 92.0f;
	static DWORD EXP1_buff = 0x008113E4-0x150;
	_asm
	{
	FLD DWORD PTR DS:[EXP1]
	FSTP QWORD PTR SS:[EBP-0x10]
	jmp [EXP1_buff]
	}
}

__declspec(naked) void EXP2Zt()
{
	static float EXP2 = 92.0f;
	static DWORD EXP2_buff = 0x0081152E-0x150;
	_asm
	{
	FLD DWORD PTR DS:[EXP2]
	FSTP QWORD PTR SS:[EBP-0x10]
	jmp [EXP2_buff]
	}
}

__declspec(naked) void EXP3Zt()
{
	static float EXP3 = 92.0f;
	static DWORD EXP3_buff = 0x008116F5-0x150;
	_asm
	{
	FLD DWORD PTR DS:[EXP3]
	FSTP QWORD PTR SS:[EBP-0x10]
	jmp [EXP3_buff]
	}
}

__declspec(naked) void EXP4Zt()
{
	static float EXP4 = 92.0f;
	static DWORD EXP4_buff = 0x008117FE-0x150;
	_asm
	{
	FLD DWORD PTR DS:[EXP4]
	FSTP QWORD PTR SS:[EBP-0x10]
	jmp [EXP4_buff]
	}
}

//EXP MASTER
__declspec(naked) void EXPMASTER1Zt()
{
	static float EXPMASTER1 = 92.0f;
	static DWORD EXPMASTER1_buff = 0x00810B4D-0x150;
	_asm
	{
	FLD DWORD PTR DS:[EXPMASTER1]
	FSTP QWORD PTR SS:[EBP-0x10]
	jmp [EXPMASTER1_buff]
	}
}

__declspec(naked) void EXPMASTER2Zt()
{
	static float EXPMASTER2 = 92.0f;
	static DWORD EXPMASTER2_buff = 0x00810C91-0x150;
	_asm
	{
	FLD DWORD PTR DS:[EXPMASTER2]
	FSTP QWORD PTR SS:[EBP-0x10]
	jmp [EXPMASTER2_buff]
	}
}

__declspec(naked) void EXPMASTER3Zt()
{
	static float EXPMASTER3 = 92.0f;
	static DWORD EXPMASTER3_buff = 0x00810E58-0x150;
	_asm
	{
	FLD DWORD PTR DS:[EXPMASTER3]
	FSTP QWORD PTR SS:[EBP-0x10]
	jmp [EXPMASTER3_buff]
	}
}

__declspec(naked) void EXPMASTER4Zt()
{
	static float EXPMASTER4 = 92.0f;
	static DWORD EXPMASTER4_buff = 0x00810F55-0x150;
	_asm
	{
	FLD DWORD PTR DS:[EXPMASTER4]
	FSTP QWORD PTR SS:[EBP-0x10]
	jmp [EXPMASTER4_buff]
	}
}

__declspec(naked) void SDScaleZt()
{
	static DWORD SDScale_buff = 0x008105F9-0x150;
	static double Alto = 16.0f;
	static double Ancho = 64.0f;
	_asm
	{
	FMUL DWORD PTR SS:[EBP-0x1C]
	FDIV QWORD PTR DS:[Alto]
	FSTP DWORD PTR SS:[EBP-0x148]
	FLD DWORD PTR SS:[EBP-0x148]
	PUSH ECX
	FSTP DWORD PTR SS:[ESP]
	FLD DWORD PTR SS:[EBP-0x20]
	FDIV QWORD PTR DS:[Ancho]
	FSTP DWORD PTR SS:[EBP-0x14C]
	FLD DWORD PTR SS:[EBP-0x14C]
	PUSH ECX
	FSTP DWORD PTR SS:[ESP]
	FLD DWORD PTR SS:[EBP-0x8]
	FMUL DWORD PTR SS:[EBP-0x1C]
	FDIV QWORD PTR DS:[Alto]
	FSTP DWORD PTR SS:[EBP-0x150]
	FLD DWORD PTR SS:[EBP-0x150]
	jmp [SDScale_buff]
	}
}

__declspec(naked) void AGScaleZt()
{
	static DWORD AGScale_buff = 0x00810329-0x150;
	static double Alto = 16.0f;
	static double Ancho = 64.0f;
	_asm
	{
	FMUL DWORD PTR SS:[EBP-0x14]
	FDIV QWORD PTR DS:[Alto]
	FSTP DWORD PTR SS:[EBP-0x148]
	FLD DWORD PTR SS:[EBP-0x148]
	PUSH ECX
	FSTP DWORD PTR SS:[ESP]
	FLD DWORD PTR SS:[EBP-0x18]
	FDIV QWORD PTR DS:[Ancho]
	FSTP DWORD PTR SS:[EBP-0x14C]
	FLD DWORD PTR SS:[EBP-0x14C]
	PUSH ECX
	FSTP DWORD PTR SS:[ESP]
	FLD DWORD PTR SS:[EBP-0x8]
	FMUL DWORD PTR SS:[EBP-0x14]
	FDIV QWORD PTR DS:[Alto]
	FSTP DWORD PTR SS:[EBP-0x150]
	FLD DWORD PTR SS:[EBP-0x150]
	jmp [AGScale_buff]
	}
}

void HookDrawTooltip(int X, int Y, LPCSTR Text)
{
	//glColor4f(1.0, 1.0, 1.0, 1.0);
	//pGLSwitchBlend();
	//pDrawToolTip(X,Y,Text);
	//pDrawBarForm(X,Y,50,10,1.0,1);
	//gInterface.DrawBarFormNew(X,Y,50,10,0.0,0.0,0.0,0.0);
	
}

void InitInterZt()
{
//#if (!USE_ZT700_INTERFACE)
//	return;
//#endif
	if(gInterfaceVersion == eINTERFACE_ZT700)
	{


   SetRange((LPVOID)(0x0080F270-0x150), 0x4D1, ASM::NOP);//-> Interface -> Draw Button

	SetRange((LPVOID)(0x0080F255-0x150),8,ASM::NOP);
	//-
	
	SetRange((LPVOID)(0x0081028C-0x150), 0x24, ASM::NOP);
	SetOp((LPVOID)(0x0081028C-0x150), (LPVOID)AGPositionZt, ASM::JMP);
	//-
	SetRange((LPVOID)(0x0081055C-0x150), 0x24, ASM::NOP);
	SetOp((LPVOID)(0x0081055C-0x150), (LPVOID)SDPositionZt, ASM::JMP);
	//-
	SetRange((LPVOID)0x0080FE5F, 0x24, ASM::NOP);
	SetOp((LPVOID)0x0080FE5F, (LPVOID)MANAPositionZt, ASM::JMP);
	//-
	SetRange((LPVOID)(0x0080FD5B-0x150), 0x24, ASM::NOP);
	SetOp((LPVOID)(0x0080FD5B-0x150), (LPVOID)HPPositionZt, ASM::JMP);
	//-
	SetRange((LPVOID)(0x008138DF-0x150), 0x24, ASM::NOP);
	SetOp((LPVOID)(0x008138DF-0x150), (LPVOID)UsingSkillPositionZt, ASM::JMP);
	//-
	SetRange((LPVOID)(0x00812713-0x150), 0x24, ASM::NOP);
	SetOp((LPVOID)(0x00812713-0x150), (LPVOID)SkillClickPositionZt, ASM::JMP);
	//-
	SetRange((LPVOID)(0x00812947-0x150), 0x24, ASM::NOP);
	SetOp((LPVOID)(0x00812947-0x150), (LPVOID)SkillBarDrawPositionZt, ASM::JMP);
	//-
	SetRange((LPVOID)(0x008139A0-0x150), 0x2D, ASM::NOP);
	SetOp((LPVOID)(0x008139A0-0x150), (LPVOID)SkillSwitchDrawZt, ASM::JMP);
	//-
	SetRange((LPVOID)(0x00812D3F-0x150), 0x2D, ASM::NOP);
	SetOp((LPVOID)(0x00812D3F-0x150), (LPVOID)SkillSwitchClickZt, ASM::JMP);
	//-
	SetRange((LPVOID)(0x00813779-0x150), 0x24, ASM::NOP);
	SetOp((LPVOID)(0x00813779-0x150), (LPVOID)SkillBarraZt, ASM::JMP);
	//-
	SetRange((LPVOID)(0x00810373-0x150), 0x12, ASM::NOP);
	SetOp((LPVOID)(0x00810373-0x150), (LPVOID)AGNumberPositionZt, ASM::JMP);
	//-
	SetRange((LPVOID)(0x00810643-0x150), 0x12, ASM::NOP);
	SetOp((LPVOID)(0x00810643-0x150), (LPVOID)SDNumberPositionZt, ASM::JMP);
	//-
	SetRange((LPVOID)(0x0080FF12-0x150), 0x12, ASM::NOP);
	SetOp((LPVOID)(0x0080FF12-0x150), (LPVOID)HPNumberPositionZt, ASM::JMP);
	//-
	SetRange((LPVOID)(0x00810B50-0x150), 0x12, ASM::NOP);
	SetOp((LPVOID)(0x00810B50-0x150), (LPVOID)MANANumberPositionZt, ASM::JMP);
	//->Q
	SetRange((LPVOID)(0x00895A49-0x150), 0x9, ASM::NOP);
	SetOp((LPVOID)(0x00895A49-0x150), (LPVOID)QPosition1Zt, ASM::JMP);
	//-
	SetRange((LPVOID)(0x00895A53-0x150), 0x9, ASM::NOP);
	SetOp((LPVOID)(0x00895A53-0x150), (LPVOID)QPosition2Zt, ASM::JMP);
	//-
	SetRange((LPVOID)(0x00895A5D-0x150), 0x9, ASM::NOP);
	SetOp((LPVOID)(0x00895A5D-0x150), (LPVOID)QPosition3Zt, ASM::JMP);
	//-
	SetRange((LPVOID)(0x00895A67-0x150), 0x9, ASM::NOP);
	SetOp((LPVOID)(0x00895A67-0x150), (LPVOID)QPosition4Zt, ASM::JMP);
	//->W
	SetRange((LPVOID)(0x00895ABE-0x150), 0x9, ASM::NOP);
	SetOp((LPVOID)(0x00895ABE-0x150), (LPVOID)WPosition1Zt, ASM::JMP);
	//-
	SetRange((LPVOID)(0x00895AC8-0x150), 0x9, ASM::NOP);
	SetOp((LPVOID)(0x00895AC8-0x150), (LPVOID)WPosition2Zt, ASM::JMP);
	//-
	SetRange((LPVOID)(0x00895AD2-0x150), 0x9, ASM::NOP);
	SetOp((LPVOID)(0x00895AD2-0x150), (LPVOID)WPosition3Zt, ASM::JMP);
	//-
	SetRange((LPVOID)(0x00895ADC-0x150), 0x9, ASM::NOP);
	SetOp((LPVOID)(0x00895ADC-0x150), (LPVOID)WPosition4Zt, ASM::JMP);
	//-
	//->E
	SetRange((LPVOID)(0x00895B33-0x150), 0x9, ASM::NOP);
	SetOp((LPVOID)(0x00895B33-0x150), (LPVOID)EPosition1Zt, ASM::JMP);
	//-
	SetRange((LPVOID)(0x00895B3D-0x150), 0x9, ASM::NOP);
	SetOp((LPVOID)(0x00895B3D-0x150), (LPVOID)EPosition2Zt, ASM::JMP);
	//-
	SetRange((LPVOID)(0x00895B47-0x150), 0x9, ASM::NOP);
	SetOp((LPVOID)(0x00895B47-0x150), (LPVOID)EPosition3Zt, ASM::JMP);
	//-
	SetRange((LPVOID)(0x00895B51-0x150), 0x9, ASM::NOP);
	SetOp((LPVOID)(0x00895B51-0x150), (LPVOID)EPosition4Zt, ASM::JMP);
	//-R
	SetRange((LPVOID)(0x00895BA8-0x150), 0x9, ASM::NOP);
	SetOp((LPVOID)(0x00895BA8-0x150), (LPVOID)RPosition1Zt, ASM::JMP);
	//-
	SetRange((LPVOID)(0x00895BB2-0x150), 0x9, ASM::NOP);
	SetOp((LPVOID)(0x00895BB2-0x150), (LPVOID)RPosition2Zt, ASM::JMP);
	//-
	SetRange((LPVOID)(0x00895BBC-0x150), 0x9, ASM::NOP);
	SetOp((LPVOID)(0x00895BBC-0x150), (LPVOID)RPosition3Zt, ASM::JMP);
	//-
	SetRange((LPVOID)(0x00895BC6-0x150), 0x9, ASM::NOP);
	SetOp((LPVOID)(0x00895BC6-0x150), (LPVOID)RPosition4Zt, ASM::JMP);

	 
//EXP
	SetRange((LPVOID)(0x008113DE-0x150), 0x9, ASM::NOP);
	SetOp((LPVOID)(0x008113DE-0x150), (LPVOID)EXP1Zt, ASM::JMP);
	SetRange((LPVOID)(0x00811528-0x150), 0x9, ASM::NOP);
	SetOp((LPVOID)(0x00811528-0x150), (LPVOID)EXP2Zt, ASM::JMP);
	SetRange((LPVOID)(0x008116EF-0x150), 0x9, ASM::NOP);
	SetOp((LPVOID)(0x008116EF-0x150), (LPVOID)EXP3Zt, ASM::JMP);
	SetRange((LPVOID)(0x008117F8-0x150), 0x9, ASM::NOP);
	SetOp((LPVOID)(0x008117F8-0x150), (LPVOID)EXP4Zt, ASM::JMP);

//EXPMASTER
	SetRange((LPVOID)(0x00810B47-0x150), 0x9, ASM::NOP);
	SetOp((LPVOID)(0x00810B47-0x150), (LPVOID)EXPMASTER1Zt, ASM::JMP);
	SetRange((LPVOID)(0x00810C8B-0x150), 0x9, ASM::NOP);
	SetOp((LPVOID)(0x00810C8B-0x150), (LPVOID)EXPMASTER2Zt, ASM::JMP);
	SetRange((LPVOID)(0x00810E52-0x150), 0x9, ASM::NOP);
	SetOp((LPVOID)(0x00810E52-0x150), (LPVOID)EXPMASTER3Zt, ASM::JMP);
	SetRange((LPVOID)(0x00810F4F-0x150), 0x9, ASM::NOP);
	SetOp((LPVOID)(0x00810F4F-0x150), (LPVOID)EXPMASTER4Zt, ASM::JMP);

//Posicion Numero HPMANAetc
	SetFloat((LPVOID)0x00D4616C, 430);
//Posicion Exp
	SetDouble((LPVOID)0x00D46190, 450);
//Posicion Numero Exp
	SetDouble((LPVOID)0x00D46188, 572);
//Tamaño numeros general (Prueba)
	SetDouble((LPVOID)0x00D27AF8, 0.400000011920929);

	SetRange((LPVOID)(0x008105AF-0x150), 5, ASM::NOP);
	SetCompleteHook(0xE9,0x008105AF-0x150,&SDScaleZt);
	//SetJmp((LPVOID)0x008105AF, SDScale);
	SetRange((LPVOID)(0x008102DF-0x150), 5, ASM::NOP);
	SetCompleteHook(0xE9,0x008102DF-0x150,&AGScaleZt);
	//SetJmp(0x008102DF, AGScale);
	/**/

	SetDword((LPVOID)(0x004D9746+3),480); //viewport height

	//SetDword((LPVOID)(0x005C7281+3),480); //viewport height
	//SetDword((LPVOID)(0x005C72BD+3),480); //viewport height

	//005C6E9E
	//signed int sub_5C6E80()
	//004D9765 -> 004D98CF
	//SetOp((LPVOID)(0x004D9765), (LPVOID)0x004D98CF, ASM::JMP);

	}
}
