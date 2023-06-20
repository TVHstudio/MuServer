#include "stdafx.h"
#include "Inter3.h"
#include "Defines.h"
#include "TMemory.h"
#include "Import.h"
#include "Interface.h"
#include "Object.h"
#include "User.h"

#if(DEV_INTERFASE_SEASON3)

__declspec(naked) void AGPosition()
{
	static float AGPositionW = 13.0f;
	static float AGPositionH = 39.0f;
	static float AGPositionX = 552.0f;
	static float AGPositionY = 435.0f;
	static DWORD AGPosition_buff = 0x0081015D;
	_asm
	{
		FLD DWORD PTR DS : [AGPositionW]
		FSTP DWORD PTR SS : [EBP - 0x18]
		FLD DWORD PTR DS : [AGPositionH]
		FSTP DWORD PTR SS : [EBP - 0x14]
		FLD DWORD PTR DS : [AGPositionX]
		FSTP DWORD PTR SS : [EBP - 0x10]
		FLD DWORD PTR DS : [AGPositionY]
		FSTP DWORD PTR SS : [EBP - 0x0C]
		jmp[AGPosition_buff]
	}
}
__declspec(naked) void SDPosition()
{
	static float SDPositionW = 14.0f;
	static float SDPositionH = 39.0f;
	static float SDPositionX = 73.0f;
	static float SDPositionY = 435.0f;
	static DWORD SDPosition_buff = 0x0081042D;
	_asm
	{
		FLD DWORD PTR DS : [SDPositionW]
		FSTP DWORD PTR SS : [EBP - 0x20]
		FLD DWORD PTR DS : [SDPositionH]
		FSTP DWORD PTR SS : [EBP - 0x1C]
		FLD DWORD PTR DS : [SDPositionX]
		FSTP DWORD PTR SS : [EBP - 0x10]
		FLD DWORD PTR DS : [SDPositionY]
		FSTP DWORD PTR SS : [EBP - 0x0C]
		jmp[SDPosition_buff]
	}
}
__declspec(naked) void MANAPosition()
{
	static float MANAPositionW = 52.0f;
	static float MANAPositionX = 489.0f;
	static float MANAPositionH = 48.0f;
	static float MANAPositionY = 429.0f;
	static DWORD MANAPosition_buff = 0x0080FE80;
	_asm
	{
		FLD DWORD PTR DS : [MANAPositionW]
		FSTP DWORD PTR SS : [EBP - 0x20]
		FLD DWORD PTR DS : [MANAPositionX]
		FSTP DWORD PTR SS : [EBP - 0x0C]
		FLD DWORD PTR DS : [MANAPositionH]
		FSTP DWORD PTR SS : [EBP - 0x1C]
		FLD DWORD PTR DS : [MANAPositionY]
		FSTP DWORD PTR SS : [EBP - 0x8]
		jmp[MANAPosition_buff]
	}
}
__declspec(naked) void HPPosition()
{
	static float HPPositionW = 52.0f;
	static float HPPositionX = 98.0f;
	static float HPPositionH = 48.0f;
	static float HPPositionY = 429.0f;
	static DWORD HPPosition_buff = 0x0080FC2C;
	_asm
	{
		FLD DWORD PTR DS : [HPPositionW]
		FSTP DWORD PTR SS : [EBP - 0x20]
		FLD DWORD PTR DS : [HPPositionX]
		FSTP DWORD PTR SS : [EBP - 0x0C]
		FLD DWORD PTR DS : [HPPositionH]
		FSTP DWORD PTR SS : [EBP - 0x1C]
		FLD DWORD PTR DS : [HPPositionY]
		FSTP DWORD PTR SS : [EBP - 0x8]
		jmp[HPPosition_buff]
	}
}

__declspec(naked) void UsingSkillPosition()
{
	static float UsingSkillPositionX = 311.0f;
	static float UsingSkillPositionY = 448.0f;
	static float UsingSkillPositionW = 20.0f;
	static float UsingSkillPositionH = 28.0f;
	static DWORD UsingSkillPosition_buff = 0x008137B0;
	_asm
	{
		FLD DWORD PTR DS : [UsingSkillPositionX]
		FSTP DWORD PTR SS : [EBP - 0x8]
		FLD DWORD PTR DS : [UsingSkillPositionY]
		FSTP DWORD PTR SS : [EBP - 0x4]
		FLD DWORD PTR DS : [UsingSkillPositionW]
		FSTP DWORD PTR SS : [EBP - 0x18]
		FLD DWORD PTR DS : [UsingSkillPositionH]
		FSTP DWORD PTR SS : [EBP - 0x14]
		jmp[UsingSkillPosition_buff]
	}
}
__declspec(naked) void SkillClickPosition()
{
	static float SkillClickPositionX = 310.0f;
	static float SkillClickPositionY = 431.0f;
	static float SkillClickPositionW = 32.0f;
	static float SkillClickPositionH = 38.0f;
	static DWORD SkillClickPosition_buff = 0x008125E4;
	_asm
	{
		FLD DWORD PTR DS : [SkillClickPositionX]
		FSTP DWORD PTR SS : [EBP - 0x8]
		FLD DWORD PTR DS : [SkillClickPositionY]
		FSTP DWORD PTR SS : [EBP - 0x4]
		FLD DWORD PTR DS : [SkillClickPositionW]
		FSTP DWORD PTR SS : [EBP - 0x20]
		FLD DWORD PTR DS : [SkillClickPositionH]
		FSTP DWORD PTR SS : [EBP - 0x1C]
		jmp[SkillClickPosition_buff]
	}
}
__declspec(naked) void SkillBarDrawPosition()
{
	static float SkillBarDrawPositionX = 222.0f;
	static float SkillBarDrawPositionY = 480.0f;
	static float SkillBarDrawPositionW = 160.0f;
	static float SkillBarDrawPositionH = 38.0f;
	static DWORD SkillBarDrawPosition_buff = 0x00812818;
	_asm
	{
		FLD DWORD PTR DS : [SkillBarDrawPositionX]
		FSTP DWORD PTR SS : [EBP - 0x8]
		FLD DWORD PTR DS : [SkillBarDrawPositionY]
		FSTP DWORD PTR SS : [EBP - 0x4]
		FLD DWORD PTR DS : [SkillBarDrawPositionW]
		FSTP DWORD PTR SS : [EBP - 0x20]
		FLD DWORD PTR DS : [SkillBarDrawPositionH]
		FSTP DWORD PTR SS : [EBP - 0x1C]
		jmp[SkillBarDrawPosition_buff]
	}
}
__declspec(naked) void SkillSwitchDraw()
{
	static float SkillSwitchDrawX = 385.0f;
	static float SkillSwitchDrawY = 380.0f;
	static float SkillSwitchDrawW = 32.0f;
	static float SkillSwitchDrawH = 38.0f;
	static float SkillSwitchDrawMW = 385.0f;
	static DWORD SkillSwitchDraw_buff = 0x0081387A;
	_asm
	{
		FLD DWORD PTR DS : [SkillSwitchDrawX]
		FSTP DWORD PTR SS : [EBP - 0x8]
		FLD DWORD PTR DS : [SkillSwitchDrawY]
		FSTP DWORD PTR SS : [EBP - 0x4]
		FLD DWORD PTR DS : [SkillSwitchDrawW]
		FSTP DWORD PTR SS : [EBP - 0x18]
		FLD DWORD PTR DS : [SkillSwitchDrawH]
		FSTP DWORD PTR SS : [EBP - 0x14]
		FLD DWORD PTR DS : [SkillSwitchDrawMW]
		FSTP DWORD PTR SS : [EBP - 0x24]
		jmp[SkillSwitchDraw_buff]
	}
}
__declspec(naked) void SkillSwitchClick()
{
	static float SkillSwitchDrawX = 385.0f;
	static float SkillSwitchDrawY = 380.0f;
	static float SkillSwitchDrawW = 32.0f;
	static float SkillSwitchDrawH = 38.0f;
	static float SkillSwitchDrawMW = 385.0f;
	static DWORD SkillSwitchClick_buff = 0x00812C19;
	_asm
	{
		FLD DWORD PTR DS : [SkillSwitchDrawX]
		FSTP DWORD PTR SS : [EBP - 0x8]
		FLD DWORD PTR DS : [SkillSwitchDrawY]
		FSTP DWORD PTR SS : [EBP - 0x4]
		FLD DWORD PTR DS : [SkillSwitchDrawW]
		FSTP DWORD PTR SS : [EBP - 0x20]
		FLD DWORD PTR DS : [SkillSwitchDrawH]
		FSTP DWORD PTR SS : [EBP - 0x1C]
		FLD DWORD PTR DS : [SkillSwitchDrawMW]
		FSTP DWORD PTR SS : [EBP - 0x14]
		jmp[SkillSwitchClick_buff]
	}
}
__declspec(naked) void QPosition1()
{
	static float BarNumberY = 445.0f;
	static DWORD QPosition1_buff = 0x008958FF;
	_asm
	{
		FLD DWORD PTR DS : [BarNumberY]
		FSTP DWORD PTR SS : [ESP]
		jmp[QPosition1_buff]
	}
}
__declspec(naked) void QPosition2()
{
	static float QPosition2X = 227.0f;
	static DWORD QPosition2_buff = 0x00895909;
	_asm
	{
		FLD DWORD PTR DS : [QPosition2X]
		FSTP DWORD PTR SS : [ESP]
		jmp[QPosition2_buff]
	}
}
__declspec(naked) void QPosition3()
{
	static float BarPotionY = 453.0f;
	static DWORD QPosition3_buff = 0x00895913;
	_asm
	{
		FLD DWORD PTR DS : [BarPotionY]
		FSTP DWORD PTR SS : [ESP]
		jmp[QPosition3_buff]
	}
}
__declspec(naked) void QPosition4()
{
	static float QPosition4X = 210.0f;
	static DWORD QPosition4_buff = 0x0089591D;
	_asm
	{
		FLD DWORD PTR DS : [QPosition4X]
		FSTP DWORD PTR SS : [ESP]
		jmp[QPosition4_buff]
	}
}
__declspec(naked) void WPosition1()
{
	static float BarNumberY = 445.0f;
	static DWORD WPosition1_buff = 0x00895974;
	_asm
	{
		FLD DWORD PTR DS : [BarNumberY]
		FSTP DWORD PTR SS : [ESP]
		jmp[WPosition1_buff]
	}
}
__declspec(naked) void WPosition2()
{
	static float WPosition2X = 257.0f;
	static DWORD WPosition2_buff = 0x0089597E;
	_asm
	{
		FLD DWORD PTR DS : [WPosition2X]
		FSTP DWORD PTR SS : [ESP]
		jmp[WPosition2_buff]
	}
}
__declspec(naked) void WPosition3()
{
	static float BarPotionY = 453.0f;
	static DWORD WPosition3_buff = 0x00895988;
	_asm
	{
		FLD DWORD PTR DS : [BarPotionY]
		FSTP DWORD PTR SS : [ESP]
		jmp[WPosition3_buff]
	}
}
__declspec(naked) void WPosition4()
{
	static float WPosition4X = 240.0f;
	static DWORD WPosition4_buff = 0x00895992;
	_asm
	{
		FLD DWORD PTR DS : [WPosition4X]
		FSTP DWORD PTR SS : [ESP]
		jmp[WPosition4_buff]
	}
}
__declspec(naked) void EPosition1()
{
	static float BarNumberY = 445.0f;
	static DWORD EPosition1_buff = 0x008959E9;
	_asm
	{
		FLD DWORD PTR DS : [BarNumberY]
		FSTP DWORD PTR SS : [ESP]
		jmp[EPosition1_buff]
	}
}
__declspec(naked) void EPosition2()
{
	static float EPosition2X = 287.0f;
	static DWORD EPosition2_buff = 0x008959F3;
	_asm
	{
		FLD DWORD PTR DS : [EPosition2X]
		FSTP DWORD PTR SS : [ESP]
		jmp[EPosition2_buff]
	}
}
__declspec(naked) void EPosition3()
{
	static float BarPotionY = 453.0f;
	static DWORD EPosition3_buff = 0x008959FD;
	_asm
	{
		FLD DWORD PTR DS : [BarPotionY]
		FSTP DWORD PTR SS : [ESP]
		jmp[EPosition3_buff]
	}
}
__declspec(naked) void EPosition4()
{
	static float EPosition4X = 270.0f;
	static DWORD EPosition4_buff = 0x00895A07;
	_asm
	{
		FLD DWORD PTR DS : [EPosition4X]
		FSTP DWORD PTR SS : [ESP]
		jmp[EPosition4_buff]
	}
}
__declspec(naked) void NopRShortKey()
{
	static DWORD RButtonAddress = 0x00895ABC;
	_asm {jmp RButtonAddress}
}
__declspec(naked) void HPNumberPosition()
{
	static float HPNumberPositionX = 45.0f;
	static DWORD HPNumberPosition_buff = 0x0080FDCE;
	_asm
	{
		FADD DWORD PTR DS : [HPNumberPositionX]
		FSTP DWORD PTR SS : [EBP - 0x19C]
		FLD DWORD PTR SS : [EBP - 0x19C]
		jmp[HPNumberPosition_buff]
	}
}
__declspec(naked) void MasterButton()
{
	static DWORD MasterButtonAddress1 = 0x0077EBD0;
	_asm
	{
		jmp[MasterButtonAddress1]
	}
}
__declspec(naked) void HelperAll()
{
	static DWORD HelperStopAddress1 = 0x007D2764;
	_asm
	{
		jmp[HelperStopAddress1]
	}
}

void DrawCoord()
{
	
	//lpCharObj lpObj = (lpCharObj)oUserObjectStruct;

	lpViewObj lpViewPlayer		= &*(ObjectPreview*)oUserPreviewStruct;

	if (pPlayerState == 5)
	{
		glColor3f(1.0f, 1.0f, 1.0f);

		//pDrawInterfaceNumBer(23, 460, 123, 1);
		//pDrawInterfaceNumBer(46, 460, 123, 1);

		pDrawBar(23, 460, lpViewPlayer->MapPosX, 1);
		pDrawBar(46, 460, lpViewPlayer->MapPosY, 1);
	}
}

void DrawZtperience(int Model, float X, float Y, float Whith, float High, float CritX, float CritY, float standartWhith, float standartHight, char a10, char a11, float a12)
{
	//X = 221.0f;
	//Y = 435.9f;
	//Whith = 198.0f;
	//High = 4.0f;

	/*if(Whith > 198.0f)
	{
		Whith = 198.0f;
	}*/

	//pDrawGUFULL(Model, X, Y, Whith, High, CritX, CritY, standartWhith, standartHight, a10, a11, a12);
}

//EXP
__declspec(naked) void EXP1()
{
   static double Ancho = 221.0f;
   static double Alto = 435.9f;
   static double AnchoTex = 198.0f;
   static double AltoTex = 4.0f;
   static DWORD EXP1_buff = 0x008112B8;	// 0x00811408;
   _asm
   {
   FLD QWORD PTR DS:[Ancho]
   FSTP QWORD PTR SS:[EBP-0x10]
   FLD QWORD PTR DS:[Alto]
   FSTP QWORD PTR SS:[EBP-0x8]
   FLD DWORD PTR SS:[EBP-0x1B0]
   FMUL QWORD PTR DS:[AnchoTex]
   FSTP QWORD PTR SS:[EBP-0x28]
   FLD QWORD PTR DS:[AltoTex]
   FSTP QWORD PTR SS:[EBP-0x20]
   jmp [EXP1_buff]
   }
}

__declspec(naked) void EXP2()
{
   static double Ancho = 221.0f;
   static double Alto = 435.9f;
   static double AnchoTex = 198.0f;
   static double AltoTex = 4.0f;
   static DWORD EXP2_buff = 0x00811402;	// 0x00811552;
   _asm
   {
   FLD QWORD PTR DS:[Ancho]
   FSTP QWORD PTR SS:[EBP-0x10]
   FLD QWORD PTR DS:[Alto]
   FSTP QWORD PTR SS:[EBP-0x8]
   FLD DWORD PTR SS:[EBP-0x1C4]
   FMUL QWORD PTR DS:[AnchoTex]
   FSTP QWORD PTR SS:[EBP-0x28]
   FLD QWORD PTR DS:[AltoTex]
   FSTP QWORD PTR SS:[EBP-0x20]
   jmp [EXP2_buff]
   }
}

__declspec(naked) void EXP3()
{
   static double Ancho = 221.0f;
   static double Alto = 435.9f;
   static double AnchoTex = 198.0f;
   static double AltoTex = 4.0f;
   static DWORD EXP3_buff = 0x008115C9;	//0x00811719;
   _asm
   {
   FLD QWORD PTR DS:[Ancho]
   FSTP QWORD PTR SS:[EBP-0x10]
   FLD QWORD PTR DS:[Alto]
   FSTP QWORD PTR SS:[EBP-0x8]
   FLD DWORD PTR SS:[EBP-0x1B0]
   FMUL QWORD PTR DS:[AnchoTex]
   FSTP QWORD PTR SS:[EBP-0x28]
   FLD QWORD PTR DS:[AltoTex]
   FSTP QWORD PTR SS:[EBP-0x20]
   jmp [EXP3_buff]
   }
}

__declspec(naked) void EXP4()
{
   static double Ancho = 221.0f;
   static double Alto = 435.9f;
   static double AnchoTex = 198.0f;
   static double AltoTex = 4.0f;
   static DWORD EXP4_buff = 0x008116CF;	// 0x0081181F;
   _asm
   {
   FLD QWORD PTR DS:[Ancho]
   FSTP QWORD PTR SS:[EBP-0x10]
   FLD QWORD PTR DS:[Alto]
   FSTP QWORD PTR SS:[EBP-0x8]
   FLD QWORD PTR DS:[AnchoTex]
   FSTP QWORD PTR SS:[EBP-0x28]
   FLD QWORD PTR DS:[AltoTex]
   FSTP QWORD PTR SS:[EBP-0x20]
   FLD QWORD PTR SS:[EBP-0x20]
   jmp [EXP4_buff]
   }
}

__declspec(naked) void EXP5()
{
   static double Ancho = 221.0f;
   static double Alto = 435.9f;
   static double AnchoTex = 198.0f;
   static double AltoTex = 4.0f;
   static DWORD EXP5_buff = 0x008110DF;	// 0x0081181F;
   _asm
   {
   FLD QWORD PTR DS:[Ancho]
   FSTP QWORD PTR SS:[EBP-0x10]
   FLD QWORD PTR DS:[Alto]
   FSTP QWORD PTR SS:[EBP-0x8]
   FLD QWORD PTR DS:[AnchoTex]
   FSTP QWORD PTR SS:[EBP-0x28]
   FLD QWORD PTR DS:[AltoTex]
   FSTP QWORD PTR SS:[EBP-0x20]
   FLD QWORD PTR SS:[EBP-0x20]
   jmp [EXP5_buff]
   }
}

//EXP MASTER
__declspec(naked) void EXPMASTER1()
{
   static double Ancho = 221.0f;
   static double Alto = 435.9f;
   static double AnchoTex = 198.0f;
   static double AltoTex = 4.0f;
   static DWORD EXPMASTER1_buff = 0x00810A1E;// 0x00810B6E;
   _asm
   {
   FLD QWORD PTR DS:[Ancho]
   FSTP QWORD PTR SS:[EBP-0x10]
   FLD QWORD PTR DS:[Alto]
   FSTP QWORD PTR SS:[EBP-0x8]
   FLD QWORD PTR SS:[EBP-0x58]
   FMUL QWORD PTR DS:[AnchoTex]
   FSTP QWORD PTR SS:[EBP-0x28]
   FLD QWORD PTR DS:[AltoTex]
   FSTP QWORD PTR SS:[EBP-0x20]
   jmp [EXPMASTER1_buff]
   }
}

__declspec(naked) void EXPMASTER2()
{
   static double Ancho = 221.0f;
   static double Alto = 435.9f;
   static double AnchoTex = 198.0f;
   static double AltoTex = 4.0f;
   static DWORD EXPMASTER2_buff = 0x00810B65;	// 0x00810CB5;
   _asm
   {
   FLD QWORD PTR DS:[Ancho]
   FSTP QWORD PTR SS:[EBP-0x10]
   FLD QWORD PTR DS:[Alto]
   FSTP QWORD PTR SS:[EBP-0x8]
   FLD QWORD PTR SS:[EBP-0x88]
   FMUL QWORD PTR DS:[AnchoTex]
   FSTP QWORD PTR SS:[EBP-0x28]
   FLD QWORD PTR DS:[AltoTex]
   FSTP QWORD PTR SS:[EBP-0x20]
   jmp [EXPMASTER2_buff]
   }
}

__declspec(naked) void EXPMASTER3()
{
   static double Ancho = 221.0f;
   static double Alto = 435.9f;
   static double AnchoTex = 198.0f;
   static double AltoTex = 4.0f;
   static DWORD EXPMASTER3_buff = 0x00810D29;	// 0x00810E79;
   _asm
   {
   FLD QWORD PTR DS:[Ancho]
   FSTP QWORD PTR SS:[EBP-0x10]
   FLD QWORD PTR DS:[Alto]
   FSTP QWORD PTR SS:[EBP-0x8]
   FLD QWORD PTR SS:[EBP-0x58]
   FMUL QWORD PTR DS:[AnchoTex]
   FSTP QWORD PTR SS:[EBP-0x28]
   FLD QWORD PTR DS:[AltoTex]
   FSTP QWORD PTR SS:[EBP-0x20]
   jmp [EXPMASTER3_buff]
   }
}

__declspec(naked) void EXPMASTER4()
{
   static double Ancho = 221.0f;
   static double Alto = 435.9f;
   static double AnchoTex = 198.0f;
   static double AltoTex = 4.0f;
   static DWORD EXPMASTER4_buff = 0x00810E26;	// 0x00810F73;
   _asm
   {
   FLD QWORD PTR DS:[Ancho]
   FSTP QWORD PTR SS:[EBP-0x10]
   FLD QWORD PTR DS:[Alto]
   FSTP QWORD PTR SS:[EBP-0x8]
   FLD QWORD PTR DS:[AnchoTex]
   FSTP QWORD PTR SS:[EBP-0x28]
   FLD QWORD PTR DS:[AltoTex]
   FSTP QWORD PTR SS:[EBP-0x20]
   jmp [EXPMASTER4_buff]
   }
}

__declspec(naked) void EXPMASTER5()
{
   static double Ancho = 221.0f;
   static double Alto = 435.9f;
   static double AnchoTex = 198.0f;
   static double AltoTex = 4.0f;
   static DWORD EXPMASTER5_buff = 0x00810853;	// 0x00810F73;
   _asm
   {
   FLD QWORD PTR DS:[Ancho]
   FSTP QWORD PTR SS:[EBP-0x10]
   FLD QWORD PTR DS:[Alto]
   FSTP QWORD PTR SS:[EBP-0x8]
   FLD QWORD PTR DS:[AnchoTex]
   FSTP QWORD PTR SS:[EBP-0x28]
   FLD QWORD PTR DS:[AltoTex]
   FSTP QWORD PTR SS:[EBP-0x20]
   jmp [EXPMASTER5_buff]
   }
}

void InitInterZtp()
{
	////EXP
 //  	SetRange((LPVOID)0x0081128E, 5, ASM::NOP);			//0x008113DE
 //  	SetOp((LPVOID)0x0081128E, (LPVOID)EXP1, ASM::JMP);	//0x008113DE

 //  	SetRange((LPVOID)0x008113D8, 5, ASM::NOP);			//0x00811528
 //  	SetOp((LPVOID)0x008113D8, (LPVOID)EXP2, ASM::JMP);	//0x00811528

 //  	SetRange((LPVOID)0x0081159F, 5, ASM::NOP);			//0x008116EF
 //  	SetOp((LPVOID)0x0081159F, (LPVOID)EXP3, ASM::JMP);	//0x008116EF

 //  	SetRange((LPVOID)0x008116A8, 5, ASM::NOP);			//0x008117F8
 //  	SetOp((LPVOID)0x008116A8, (LPVOID)EXP4, ASM::JMP);	//0x008117F8

 //  	SetRange((LPVOID)0x008110B5, 5, ASM::NOP);			//
 //  	SetOp((LPVOID)0x008110B5, (LPVOID)EXP5, ASM::JMP);	//

	//////EXPMASTER
 //  	SetRange((LPVOID)0x008109F7, 5, ASM::NOP);
 //   SetOp((LPVOID)0x008109F7, (LPVOID)EXPMASTER1, ASM::JMP);

 //  	SetRange((LPVOID)0x00810B3B, 5, ASM::NOP);
 //  	SetOp((LPVOID)0x00810B3B, (LPVOID)EXPMASTER2, ASM::JMP);

 //  	SetRange((LPVOID)0x00810D02, 5, ASM::NOP);
 //  	SetOp((LPVOID)0x00810D02, (LPVOID)EXPMASTER3, ASM::JMP);

 //  	SetRange((LPVOID)0x00810DFF, 5, ASM::NOP);
 //  	SetOp((LPVOID)0x00810DFF, (LPVOID)EXPMASTER4, ASM::JMP);

 //  	SetRange((LPVOID)0x0081082C, 5, ASM::NOP);
 //  	SetOp((LPVOID)0x0081082C, (LPVOID)EXPMASTER5, ASM::JMP);	

	//Posicion Numero Exp
	SetDouble((PVOID)(0x0D46188), 425);	//OK
	SetDouble((PVOID)(0x0D46180), 431);	//OK

	//810700 0081082C
//
	//SetOp((LPVOID)0x007D2473, (LPVOID)DrawZtperience, ASM::CALL);//????

	SetOp((LPVOID)0x00811156, (LPVOID)DrawZtperience, ASM::CALL);
	SetOp((LPVOID)0x0081132F, (LPVOID)DrawZtperience, ASM::CALL);
	SetOp((LPVOID)0x00811479, (LPVOID)DrawZtperience, ASM::CALL);
	SetOp((LPVOID)0x00811510, (LPVOID)DrawZtperience, ASM::CALL);
	SetOp((LPVOID)0x00811640, (LPVOID)DrawZtperience, ASM::CALL);

	SetOp((LPVOID)0x008108CA, (LPVOID)DrawZtperience, ASM::CALL);
	SetOp((LPVOID)0x00810A95, (LPVOID)DrawZtperience, ASM::CALL);
	SetOp((LPVOID)0x00810BDC, (LPVOID)DrawZtperience, ASM::CALL);
	SetOp((LPVOID)0x00810C73, (LPVOID)DrawZtperience, ASM::CALL);
	SetOp((LPVOID)0x00810DA0, (LPVOID)DrawZtperience, ASM::CALL);

	//0080F715 nop - exl line func
	//SetRange((LPVOID)0x0080F715, 5, ASM::NOP);
}


void InitInter3()
{
	//SetOp((LPVOID)0x007D2473, (LPVOID)DrawZtperience, ASM::CALL);

	SetRange((LPVOID)0x0080F120, 0x4D1, ASM::NOP);//-> Interface -> Draw Button
												  //-
	SetByte((PVOID)(0x0081365F + 3), 0);
	SetByte((PVOID)(0x00811857), 0xEB);
	SetRange((LPVOID)0x00811970, 0xAC, ASM::NOP);
	//-
	SetRange((LPVOID)0x0081013C, 0x24, ASM::NOP);
	SetOp((LPVOID)0x0081013C, (LPVOID)AGPosition, ASM::JMP);
	//-
	SetRange((LPVOID)0x0081040C, 0x24, ASM::NOP);
	SetOp((LPVOID)0x0081040C, (LPVOID)SDPosition, ASM::JMP);
	//-
	SetRange((LPVOID)0x0080FE5F, 0x24, ASM::NOP);
	SetOp((LPVOID)0x0080FE5F, (LPVOID)MANAPosition, ASM::JMP);
	//-
	SetRange((LPVOID)0x0080FC0B, 0x24, ASM::NOP);
	SetOp((LPVOID)0x0080FC0B, (LPVOID)HPPosition, ASM::JMP);
	//-
	SetRange((LPVOID)0x0081378F, 0x24, ASM::NOP);
	SetOp((LPVOID)0x0081378F, (LPVOID)UsingSkillPosition, ASM::JMP);
	//-
	SetRange((LPVOID)0x008125C3, 0x24, ASM::NOP);
	SetOp((LPVOID)0x008125C3, (LPVOID)SkillClickPosition, ASM::JMP);
	//-
	SetRange((LPVOID)0x008127F7, 0x24, ASM::NOP);
	SetOp((LPVOID)0x008127F7, (LPVOID)SkillBarDrawPosition, ASM::JMP);
	//-
	SetRange((LPVOID)0x00813850, 0x2D, ASM::NOP);
	SetOp((LPVOID)0x00813850, (LPVOID)SkillSwitchDraw, ASM::JMP);
	//-
	SetRange((LPVOID)0x00812BEF, 0x2D, ASM::NOP);
	SetOp((LPVOID)0x00812BEF, (LPVOID)SkillSwitchClick, ASM::JMP);
	//-
	SetRange((LPVOID)0x0080FDC2, 0x12, ASM::NOP);
	SetOp((LPVOID)0x0080FDC2, (LPVOID)HPNumberPosition, ASM::JMP);
	//-
	SetRange((LPVOID)0x0077EB47, 0x88, ASM::NOP);
	SetOp((LPVOID)0x0077EB47, (LPVOID)MasterButton, ASM::JMP);
	//-
	//->Q
	SetRange((LPVOID)0x008958F9, 0x9, ASM::NOP);
	SetOp((LPVOID)0x008958F9, (LPVOID)QPosition1, ASM::JMP);
	//-
	SetRange((LPVOID)0x00895903, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895903, (LPVOID)QPosition2, ASM::JMP);
	//-
	SetRange((LPVOID)0x0089590D, 0x9, ASM::NOP);
	SetOp((LPVOID)0x0089590D, (LPVOID)QPosition3, ASM::JMP);
	//-
	SetRange((LPVOID)0x00895917, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895917, (LPVOID)QPosition4, ASM::JMP);
	//->W
	SetRange((LPVOID)0x0089596E, 0x9, ASM::NOP);
	SetOp((LPVOID)0x0089596E, (LPVOID)WPosition1, ASM::JMP);
	//-
	SetRange((LPVOID)0x00895978, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895978, (LPVOID)WPosition2, ASM::JMP);
	//-
	SetRange((LPVOID)0x00895982, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895982, (LPVOID)WPosition3, ASM::JMP);
	//-
	SetRange((LPVOID)0x0089598C, 0x9, ASM::NOP);
	SetOp((LPVOID)0x0089598C, (LPVOID)WPosition4, ASM::JMP);
	//-
	//->E
	SetRange((LPVOID)0x008959E3, 0x9, ASM::NOP);
	SetOp((LPVOID)0x008959E3, (LPVOID)EPosition1, ASM::JMP);
	//-
	SetRange((LPVOID)0x008959ED, 0x9, ASM::NOP);
	SetOp((LPVOID)0x008959ED, (LPVOID)EPosition2, ASM::JMP);
	//-
	SetRange((LPVOID)0x008959F7, 0x9, ASM::NOP);
	SetOp((LPVOID)0x008959F7, (LPVOID)EPosition3, ASM::JMP);
	//-
	SetRange((LPVOID)0x00895A01, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895A01, (LPVOID)EPosition4, ASM::JMP);
	//-
	//->R
	SetRange((LPVOID)0x00895A3D, 0x7E, ASM::NOP);
	SetOp((LPVOID)0x00895A3D, (LPVOID)NopRShortKey, ASM::JMP);

	//SetRange((LPVOID)0x007D2473, 0x2F0, ASM::NOP);
	//SetOp((LPVOID)0x007D2473, (LPVOID)HelperAll, ASM::JMP);

	#if(ENABLE_SEASON3_VERSION)
	InitInterZtp();
	#endif
}

#endif


__declspec(naked) void SelectCharacterMap()
{
	static DWORD SelectCharacterMap_buff = 0x004D6C35;
	_asm
	{
	MOV DWORD PTR DS:[0xE61E18],0x36 //0x4A
	MOV EAX,DWORD PTR DS:[0xE61E18]
	jmp [SelectCharacterMap_buff]
	}
}

__declspec(naked) void SelectCharacterCord()
{
	static float D27B98 = -84.50000f;
	static float D25708 = -45.00000f;
	static float D27B94 = 8898.929687f;
	static float D27B90 = 18513.10938f;
	static float D27B8C = 550.5000f;
	static float D27B88 = -48.50000;
	static DWORD SelectCharacterCord_buff = 0x004D8B57;
	static DWORD SCCordJMP    = 0x004D8B42;
	_asm
	{
	//CMP DWORD PTR DS:[0xE609E8],0x4
	//JNZ SCCordJNZ
	FLD DWORD PTR DS:[D27B98]
	FSTP DWORD PTR DS:[0x87933D0]
	FLDZ
	FSTP DWORD PTR DS:[0x87933D4]
	FLD DWORD PTR DS:[D25708]
	FSTP DWORD PTR DS:[0x87933D8]
	FLD DWORD PTR DS:[D27B94]
	FSTP DWORD PTR DS:[0x87933DC]
	FLD DWORD PTR DS:[D27B90]
	FSTP DWORD PTR DS:[0x87933E0]
	FLD DWORD PTR DS:[D27B8C]
	FSTP DWORD PTR DS:[0x87933E4]
	JMP SCCordJMP
	FLD DWORD PTR DS:[D27B88]
	FSTP DWORD PTR DS:[0x87933D0]
	FLD DWORD PTR DS:[0x87933D0]
	FADD DWORD PTR DS:[0x8787D48]
	FSTP DWORD PTR DS:[0x87933D0]
	MOV EDX,DWORD PTR SS:[EBP-0x68]
	jmp [SelectCharacterCord_buff]
	}
}

__declspec(naked) void SelectCharacterCordPJ1()
{
	static float D41DCC = 7900.000f; //8008.000
	static float D41DC8 = 19100.00f; //18885.00
	static float D27AE0 = 90.0000f; //115.0000
	static DWORD SelectCharacterCordPJ1_buff = 0x0063D1E9;
	_asm
	{
	FLD DWORD PTR DS:[D41DCC]
	FSTP DWORD PTR SS:[EBP-0x14]
	FLD DWORD PTR DS:[D41DC8]
	FSTP DWORD PTR SS:[EBP-0x10]
	FLD DWORD PTR DS:[D27AE0]
	FSTP DWORD PTR SS:[EBP-0x18]
	jmp [SelectCharacterCordPJ1_buff]
	}
}

__declspec(naked) void SelectCharacterCordPJ21()
{
	static float D41DCC = 7900.000f; //8008.000
	static float D41DC8 = 19100.00f; //18885.00
	static float D27AE0 = 90.0000f; //115.0000
	static DWORD SelectCharacterCordPJ1_buff = 0x0063D42A;
	_asm
	{
	FLD DWORD PTR DS:[D41DCC]
	FSTP DWORD PTR SS:[EBP-0xC]
	FLD DWORD PTR DS:[D41DC8]
	FSTP DWORD PTR SS:[EBP-0x8]
	FLD DWORD PTR DS:[D27AE0]
	FSTP DWORD PTR SS:[EBP-0x14]
	jmp [SelectCharacterCordPJ1_buff]
	}
}

__declspec(naked) void SelectCharacterCordPJ2()
{
	static float D41DC4 = 7900.000f; //7986.000
	static float D41DC0 = 19300.00f; //19145.00
	static float D254C0 = 75.00000f; //90.00000
	static DWORD SelectCharacterCordPJ2_buff = 0x0063D206;
	_asm
	{
	FLD DWORD PTR DS:[D41DC4]
	FSTP DWORD PTR SS:[EBP-0x14]
	FLD DWORD PTR DS:[D41DC0]
	FSTP DWORD PTR SS:[EBP-0x10]
	FLD DWORD PTR DS:[D254C0]
	FSTP DWORD PTR SS:[EBP-0x18]
	jmp [SelectCharacterCordPJ2_buff]
	}
}

__declspec(naked) void SelectCharacterCordPJ22()
{
	static float D41DC4 = 7900.000f; //7986.000
	static float D41DC0 = 19300.00f; //19145.00
	static float D254C0 = 75.00000f; //90.00000
	static DWORD SelectCharacterCordPJ2_buff = 0x0063D447;
	_asm
	{
	FLD DWORD PTR DS:[D41DC4]
	FSTP DWORD PTR SS:[EBP-0xC]
	FLD DWORD PTR DS:[D41DC0]
	FSTP DWORD PTR SS:[EBP-0x8]
	FLD DWORD PTR DS:[D254C0]
	FSTP DWORD PTR SS:[EBP-0x14]
	jmp [SelectCharacterCordPJ2_buff]
	}
}

__declspec(naked) void SelectCharacterCordPJ3()
{
	static float D41DBC = 8000.000f; //8046.000
	static float D41DB8 = 19450.00f; //19400.00
	static float D2B954 = 45.00000f; //75.00000
	static DWORD SelectCharacterCordPJ3_buff = 0x0063D223;
	_asm
	{
	FLD DWORD PTR DS:[D41DBC]
	FSTP DWORD PTR SS:[EBP-0x14]
	FLD DWORD PTR DS:[D41DB8]
	FSTP DWORD PTR SS:[EBP-0x10]
	FLD DWORD PTR DS:[D2B954]
	FSTP DWORD PTR SS:[EBP-0x18]
	jmp [SelectCharacterCordPJ3_buff]
	}
}

__declspec(naked) void SelectCharacterCordPJ23()
{
	static float D41DBC = 8000.000f; //8046.000
	static float D41DB8 = 19450.00f; //19400.00
	static float D2B954 = 45.00000f; //75.00000
	static DWORD SelectCharacterCordPJ3_buff = 0x0063D464;
	_asm
	{
	FLD DWORD PTR DS:[D41DBC]
	FSTP DWORD PTR SS:[EBP-0xC]
	FLD DWORD PTR DS:[D41DB8]
	FSTP DWORD PTR SS:[EBP-0x8]
	FLD DWORD PTR DS:[D2B954]
	FSTP DWORD PTR SS:[EBP-0x14]
	jmp [SelectCharacterCordPJ3_buff]
	}
}

__declspec(naked) void SelectCharacterCordPJ4()
{
	static float D41DB4 = 8150.00f; //8133.000
	static float D41DB0 = 19550.00f; //19645.00
	static float D2577C = 25.00000f; //60.00000
	static DWORD SelectCharacterCordPJ4_buff = 0x0063D240;
	_asm
	{
	FLD DWORD PTR DS:[D41DB4]
	FSTP DWORD PTR SS:[EBP-0x14]
	FLD DWORD PTR DS:[D41DB0]
	FSTP DWORD PTR SS:[EBP-0x10]
	FLD DWORD PTR DS:[D2577C]
	FSTP DWORD PTR SS:[EBP-0x18]
	jmp [SelectCharacterCordPJ4_buff]
	}
}

__declspec(naked) void SelectCharacterCordPJ24()
{
	static float D41DB4 = 8150.00f; //8133.000
	static float D41DB0 = 19550.00f; //19645.00
	static float D2577C = 25.00000f; //60.00000
	static DWORD SelectCharacterCordPJ4_buff = 0x0063D481;
	_asm
	{
	FLD DWORD PTR DS:[D41DB4]
	FSTP DWORD PTR SS:[EBP-0xC]
	FLD DWORD PTR DS:[D41DB0]
	FSTP DWORD PTR SS:[EBP-0x8]
	FLD DWORD PTR DS:[D2577C]
	FSTP DWORD PTR SS:[EBP-0x14]
	jmp [SelectCharacterCordPJ4_buff]
	}
}

__declspec(naked) void SelectCharacterCordPJ5()
{
	static float D41DAC = 8300.000f; //8282.000
	static float D41DA8 = 19600.00f; //19845.00
	static float D27BFC = 0.00000f; //35.00000
	static DWORD SelectCharacterCordPJ5_buff = 0x0063D25D;
	_asm
	{
	FLD DWORD PTR DS:[D41DAC]
	FSTP DWORD PTR SS:[EBP-0x14]
	FLD DWORD PTR DS:[D41DA8]
	FSTP DWORD PTR SS:[EBP-0x10]
	FLD DWORD PTR DS:[D27BFC]
	FSTP DWORD PTR SS:[EBP-0x18]
	jmp [SelectCharacterCordPJ5_buff]
	}
}

__declspec(naked) void SelectCharacterCordPJ25()
{
	static float D41DAC = 8300.000f; //8282.000
	static float D41DA8 = 19600.00f; //19845.00
	static float D27BFC = 0.00000f; //35.00000
	static DWORD SelectCharacterCordPJ5_buff = 0x0063D49E;
	_asm
	{
	FLD DWORD PTR DS:[D41DAC]
	FSTP DWORD PTR SS:[EBP-0xC]
	FLD DWORD PTR DS:[D41DA8]
	FSTP DWORD PTR SS:[EBP-0x8]
	FLD DWORD PTR DS:[D27BFC]
	FSTP DWORD PTR SS:[EBP-0x14]
	jmp [SelectCharacterCordPJ5_buff]
	}
}

// CAOTHU.VN add here to fix mount size
__declspec(naked) void ThuNhoThuCuoi()
{
	static float CAOTHU_VN = 1.00000f;
	static DWORD BACK = 0x50383F;
	_asm
	{
		FLD DWORD PTR DS : [CAOTHU_VN]
		jmp[BACK]
	}
}

void SCharacterS3()
{
	//return;

	SetRange((LPVOID)0x004D6C26, 5, ASM::NOP);
    SetOp((LPVOID)0x004D6C26, (LPVOID)SelectCharacterMap, ASM::JMP);
	
	SetRange((LPVOID)0x004D8AF0, 5, ASM::NOP);//0x004D8AE7
    SetOp((LPVOID)0x004D8AF0, (LPVOID)SelectCharacterCord, ASM::JMP);

//Posicion Personajes

	SetRange((LPVOID)0x0063D1CE, 5, ASM::NOP);
    SetOp((LPVOID)0x0063D1CE, (LPVOID)SelectCharacterCordPJ1, ASM::JMP);
	SetRange((LPVOID)0x0063D40F, 5, ASM::NOP);
    SetOp((LPVOID)0x0063D40F, (LPVOID)SelectCharacterCordPJ21, ASM::JMP);
	
	SetRange((LPVOID)0x0063D1EB, 5, ASM::NOP);
    SetOp((LPVOID)0x0063D1EB, (LPVOID)SelectCharacterCordPJ2, ASM::JMP);
	SetRange((LPVOID)0x0063D42C, 5, ASM::NOP);
    SetOp((LPVOID)0x0063D42C, (LPVOID)SelectCharacterCordPJ22, ASM::JMP);
	
	SetRange((LPVOID)0x0063D208, 5, ASM::NOP);
    SetOp((LPVOID)0x0063D208, (LPVOID)SelectCharacterCordPJ3, ASM::JMP);
	SetRange((LPVOID)0x0063D449, 5, ASM::NOP);
    SetOp((LPVOID)0x0063D449, (LPVOID)SelectCharacterCordPJ23, ASM::JMP);
	
	SetRange((LPVOID)0x0063D225, 5, ASM::NOP);
    SetOp((LPVOID)0x0063D225, (LPVOID)SelectCharacterCordPJ4, ASM::JMP);
	SetRange((LPVOID)0x0063D466, 5, ASM::NOP);
    SetOp((LPVOID)0x0063D466, (LPVOID)SelectCharacterCordPJ24, ASM::JMP);
	
	SetRange((LPVOID)0x0063D242, 5, ASM::NOP);
    SetOp((LPVOID)0x0063D242, (LPVOID)SelectCharacterCordPJ5, ASM::JMP);
	SetRange((LPVOID)0x0063D483, 5, ASM::NOP);
    SetOp((LPVOID)0x0063D483, (LPVOID)SelectCharacterCordPJ25, ASM::JMP);
	SetByte((LPVOID)0x0057F0FC, 0xE9);
    SetByte((LPVOID)0x0057F0FD, 0x4A);
    SetByte((LPVOID)0x0057F0FE, 0x01);
    SetByte((LPVOID)0x0057F0FF, 0x00);
    SetByte((LPVOID)0x0057F100, 0x00);
    SetByte((LPVOID)0x0057F101, 0x90);
	// CAOTHU.VN add here to fix mount size
	SetRange((LPVOID)0x503839, 6, ASM::NOP);
	SetOp((LPVOID)0x503839, (LPVOID)ThuNhoThuCuoi, ASM::JMP);	

}