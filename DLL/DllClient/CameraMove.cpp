#include "stdafx.h"
#include "Import.h"
#include "Object.h"
#include "Protocol.h"
#include "Interface.h"
#include "CameraMove.h"
#include "TMemory.h"
#include "Camera.h"
#include "Controller.h"
#include "Console.h"

#if(CUSTOM_CAMERA_MOVE)

CCameraMove g_CameraMove;

CCameraMove::CCameraMove()
{
	this->Init();

	Hook();//
}

CCameraMove::~CCameraMove()
{
}

void CCameraMove::Init()
{
	this->m_CameraMoveKey = 0;
	
	this->m_TempCursorX = 0;

	this->m_TempCursorY = 0;
}

void CCameraMove::Load()
{

	this->Init();

	this->Hook();
}

#define pMoveCharacterCamera	((float*(__cdecl*)(float *const a1, float *const a2, float **a3)) 0x4D66C0)

float *__cdecl MoveCharacterCameraEx(float *const a1, float *const a2, float **a3)
{
	if(pPlayerState == 5)
	{
		*(float*)0x87933D0 -= 10.0;
		*(float*)0x87933D4 -= 10.0;

		*(float*)0x87933E0 -= 10.0;
		*(float*)0x87933E4 -= 10.0;
	}

	return pMoveCharacterCamera(a1, a2, a3);
}


static DWORD dwMoveCameraJMP = 0x004D8A0B;
static DWORD dwMoveCameraX = 0x0087933DC;
static DWORD dwMoveCameraY = 0x0087933E0;
static DWORD dwMoveCameraZ = 0x0087933E4;

static DWORD dwMoveCameraEBP = 0;

__declspec(naked) void MoveCameraCordAsm()
{
	if(g_CameraMove.m_CameraMoveKey == 1)
	{
		_asm
		{
			MOV dwMoveCameraEBP, EBP

			FLD DWORD PTR SS:[EBP-0x5C]
			FADD DWORD PTR SS:[EBP-0x9C]
			FSTP DWORD PTR DS:[0x0087933E4]         ; FLOAT 1015.000

			MOV EBP, dwMoveCameraEBP

			JMP dwMoveCameraJMP
		}
	}
	else
	{
		_asm
		{
			MOV dwMoveCameraEBP, EBP

			FLD DWORD PTR SS:[EBP-0x64]
			FADD DWORD PTR SS:[EBP-0xA4]
			FSTP DWORD PTR DS:[0x0087933DC]         ; FLOAT 19057.11
			FLD DWORD PTR SS:[EBP-0x60]
			FADD DWORD PTR SS:[EBP-0xA0]
			FSTP DWORD PTR DS:[0x0087933E0]         ; FLOAT 11842.89
			FLD DWORD PTR SS:[EBP-0x5C]
			FADD DWORD PTR SS:[EBP-0x9C]
			FSTP DWORD PTR DS:[0x0087933E4]         ; FLOAT 1015.000

			MOV EBP, dwMoveCameraEBP

			JMP dwMoveCameraJMP
	}
	}
}

void CCameraMove::Hook()
{
	SetOp((LPVOID)0x005DBFE3, this->CreateFrustrum2D, ASM::CALL);

	//SetOp((LPVOID)0x004045E8, (LPVOID)MoveCharacterCameraEx, ASM::CALL);
	//SetOp((LPVOID)0x004D6A54, (LPVOID)MoveCharacterCameraEx, ASM::CALL);

	SetRange((LPVOID)0x004D89DE, 45, ASM::NOP);
	SetOp((LPVOID)0x004D89DE, (LPVOID)MoveCameraCordAsm, ASM::JMP);
	
}

void CCameraMove::Move()
{
	if(this->m_CameraMoveKey == 0 || pPlayerState != 5)
	{
		return;
	}
	
	float StartY = 264.0 + 7.0;

	float StartX = 512.0 + 50.0;

	if(gInterface.IsWorkZone(StartX, StartY, StartX + 128, StartY + 128))
	{		
		*(float*)0x87933DC = (float)(pCursorX - StartX) * 2 * 100;

		*(float*)0x87933E0 = (float)(pCursorY - StartY) * 2 * 100;

		return;
	}	

	//return;	//DEBUG

	float iCameraMoveX = 0;

	float iCameraMoveY = 0;

	float iCameraMoveSpeedX = 0;

	float iCameraMoveSpeedY = 0;

	if(pCursorX > 320)
	{
		iCameraMoveSpeedX =  pCursorX - 320;

		iCameraMoveX = iCameraMoveSpeedX;		//+=
	}

	if(pCursorX < 320)
	{
		iCameraMoveSpeedX = 320 - pCursorX;

		iCameraMoveX = -iCameraMoveSpeedX;		// -	//+=
	}

	if(pCursorY > 240)
	{
		iCameraMoveSpeedY = pCursorY - 240;

		 iCameraMoveY = -iCameraMoveSpeedY;	// -	//+=
	}

	if(pCursorY < 240)
	{
		iCameraMoveSpeedY = 240 - pCursorY;

		 iCameraMoveY = iCameraMoveSpeedY;	//+=
	}

	gConsole.Output(cGREY, "[CURSOR] (X:%d,Y:%d) [MOVE] (X:%f,Y:%f)", 
		pCursorX, pCursorY, iCameraMoveX, iCameraMoveY);

   *(float*)0x87933DC += iCameraMoveX - 48.5f;

   *(float*)0x87933E0 += iCameraMoveY - 48.5f;

   //*(float*)0x87933DC += iCameraMoveX;

   //*(float*)0x87933E0 += iCameraMoveY;
}

void CameraPositionAddEx()
{
	*(float*)0x87933DC = 18200;

	*(float*)0x87933E0 = 12800;
}

void CCameraMove::Mouse(WPARAM wParam, MOUSEHOOKSTRUCTEX* HookStruct)
{
	switch(wParam)
	{
		case WM_MOUSEMOVE:
			this->Move();
			break;
		case WM_MBUTTONDOWN:
			{
				if(this->m_CameraMoveKey == 0)
				{
					this->m_TempCursorX = pCursorX;

					this->m_TempCursorY = pCursorY;
				}

				this->m_CameraMoveKey = 1;

				//SetRange((LPVOID)0x004D89E7, 6, ASM::NOP);

				//SetRange((LPVOID)0x004D89F6, 6, ASM::NOP);

				//SetOp((LPVOID)0x004D89F6, CameraPositionAddEx, ASM::CALL);

				//*(float*)0x87933DC = 18200;

				//*(float*)0x87933E0 = 12800;

				g_CameraMove.CGReqViewe(TRUE);
			}
			break;
		case WM_MBUTTONUP:
			{
				this->m_CameraMoveKey = 0;

				//BYTE btPatch1[] = { 0xD9, 0x1D, 0xDC, 0x33, 0x79, 0x08 };

				//BYTE btPatch2[] = { 0xD9, 0x1D, 0xE0, 0x33, 0x79, 0x08 };

				//WriteMemory((LPVOID)0x004D89E7, btPatch1, sizeof(btPatch1));

				//WriteMemory((LPVOID)0x004D89F6, btPatch2, sizeof(btPatch2));

				g_CameraMove.CGReqViewe(FALSE);
			}
			break;
	}
}

void CCameraMove::KeyBoard(DWORD KeyID)
{
	/*
	if(!this->m_CameraMoveKey)
	{
		return;
	}
	*/

	int iCameraMoveX = 0;

	int iCameraMoveY = 0;

	if(KeyID == VK_DOWN)
	{
		iCameraMoveY += CAMERAMOVE_ADD;
	}
	else if(KeyID == VK_UP)
	{
		iCameraMoveY += -CAMERAMOVE_ADD;
	}
	else if(KeyID == VK_RIGHT)
	{
		iCameraMoveX += CAMERAMOVE_ADD;
	}
	else if(KeyID == VK_LEFT)
	{
		iCameraMoveX += -CAMERAMOVE_ADD;
	}
	else
	{
		return;
	}

   *(float*)0x87933DC += iCameraMoveX;

   *(float*)0x87933E0 += iCameraMoveY;

   // ----

	int iMapPosX = *(float*)0x87933DC / 100;

	int iMapPosY = *(float*)0x87933E0 / 100;

	float flFrustrumX[4];

	float flFrustrumY[4];

	memset(flFrustrumX, 0, sizeof(flFrustrumX));

	memset(flFrustrumY, 0, sizeof(flFrustrumY));

	flFrustrumX[0] = iMapPosX + 102;

	flFrustrumX[1] = iMapPosX - 12;

	flFrustrumX[2] = iMapPosX - 77;

	flFrustrumX[3] = iMapPosX + 12;

	flFrustrumY[0] = iMapPosY + 50;

	flFrustrumY[1] = iMapPosY - 157;

	flFrustrumY[2] = iMapPosY - 8;

	flFrustrumY[3] = iMapPosY + 128;

	memcpy((LPVOID)0x82C64B8, flFrustrumX, sizeof(flFrustrumX));

	memcpy((LPVOID)0x82C64A8, flFrustrumY, sizeof(flFrustrumY));

}

int CCameraMove::CreateFrustrum2D(int a1, char a2)
{
	if(pPlayerState == GameProcess)
	{
		#if(CUSTOM_CAMERA_MOVE)
		//g_CameraMove.Move();
		#endif

		if(g_CameraMove.m_CameraMoveKey == 1)
		{
			g_CameraMove.CGReqViewe(TRUE);
		}

		if(g_CameraMove.m_CameraMoveKey == 1)
		{
			
			int Result = 4;

			int iMapPosX = *(float*)0x87933DC / 100;

			int iMapPosY = *(float*)0x87933E0 / 100;

			float flFrustrumX[4];

			float flFrustrumY[4];

			memset(flFrustrumX, 0, sizeof(flFrustrumX));

			memset(flFrustrumY, 0, sizeof(flFrustrumY));

			float flDiv = 0.7;

			flFrustrumX[0] = iMapPosX + ( 102 * flDiv);

			flFrustrumX[1] = iMapPosX - ( 12 * flDiv);

			flFrustrumX[2] = iMapPosX - ( 77 * flDiv);

			flFrustrumX[3] = iMapPosX + ( 12 * flDiv);

			flFrustrumY[0] = iMapPosY + ( 50 * flDiv);

			flFrustrumY[1] = iMapPosY - ( 157 * flDiv);

			flFrustrumY[2] = iMapPosY - ( 8 * flDiv);

			flFrustrumY[3] = iMapPosY + ( 128 * flDiv);

			memcpy((LPVOID)0x82C64B8, flFrustrumX, sizeof(flFrustrumX));

			memcpy((LPVOID)0x82C64A8, flFrustrumY, sizeof(flFrustrumY));

			//WriteMemory((LPVOID)0x82C64B8, flFrustrumX, sizeof(flFrustrumX));
			//
			//WriteMemory((LPVOID)0x82C64A8, flFrustrumY, sizeof(flFrustrumY));

			//int Result = 4;

			//int iMapPosX = *(float*)0x87933DC / 100;

			//int iMapPosY = *(float*)0x87933E0 / 100;

			//float flFrustrumX[4];	

			//float flFrustrumY[4];

			//float flDiv = 0.7;

			//flFrustrumX[0] = (*(float*)0x87933DC / 100) + ( 102 * flDiv);

			//flFrustrumX[1] = (*(float*)0x87933DC / 100) - ( 12 * flDiv);

			//flFrustrumX[2] = (*(float*)0x87933DC / 100) - ( 77 * flDiv);

			//flFrustrumX[3] = (*(float*)0x87933DC / 100) + ( 12 * flDiv);

			//flFrustrumY[0] = (*(float*)0x87933E0 / 100) + ( 50 * flDiv);

			//flFrustrumY[1] = (*(float*)0x87933E0 / 100) - ( 157 * flDiv);

			//flFrustrumY[2] = (*(float*)0x87933E0 / 100) - ( 8 * flDiv);

			//flFrustrumY[3] = (*(float*)0x87933E0 / 100) + ( 128 * flDiv);

			//float flFrustrumX[4];	

			//float flFrustrumY[4];

			//int iMapPosX = 18200 / 100;

			//int iMapPosY = 12800 / 100;			

			//flFrustrumX[0] = iMapPosX + 40;
			//flFrustrumX[1] = iMapPosX - 4;
			//flFrustrumX[2] = iMapPosX - 15;
			//flFrustrumX[3] = iMapPosX + 0;

			//flFrustrumY[0] = iMapPosY + 4;
			//flFrustrumY[1] = iMapPosY - 40;
			//flFrustrumY[2] = iMapPosY - 0;
			//flFrustrumY[3] = iMapPosY + 15;

			//memcpy((LPVOID)0x82C64B8, flFrustrumX, sizeof(flFrustrumX));

			//memcpy((LPVOID)0x82C64A8, flFrustrumY, sizeof(flFrustrumY));

			return Result;
		}
	}

	

	return sub_5DB130(a1, a2);
}

void CCameraMove::CGReqViewe(int ActiveMove)
{
	int iMapPosX = *(float*)0x87933DC / 100;

	int iMapPosY = *(float*)0x87933E0 / 100;

	PMSG_REQ_CAMERAMOVE_VIEWE pMsg;

	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xEA, sizeof(pMsg));

	pMsg.Active = ActiveMove;

	pMsg.X = iMapPosX;

	pMsg.Y = iMapPosY;

	gProtocol.DataSend((LPBYTE)&pMsg, sizeof(pMsg));
}

void CCameraMove::GCAnsViewe(PMSG_ANS_CAMERAMOVE_VIEWE* lpMsg)
{

}

void CCameraMove::DrawMiniMap(float StartX, float StartY)
{
	if(this->m_CameraMoveKey)
	{
		if(gInterface.IsWorkZone(StartX, StartY, StartX + 128, StartY + 128))
		{
			pDrawColorButton(0x7880, pCursorX - 7, pCursorY - 5, 14, 10, 0, 0, Color4f(0, 0, 0, 150));	
		}
	}
}

#endif