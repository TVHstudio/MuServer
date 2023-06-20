#include "stdafx.h"
#include "Camera.h"
#include "Other.h"
#include "TMemory.h"
//#include "TDebugLog.h"
#include "Interface.h"
#include "User.h"
#include "Interface.h"
#include "Console.h"
#include "Import.h"
#include "CameraMove.h"
#include "ZtLicense.h"

float TenFix;

// ----------------------------------------------------------------------------------------------

Camera	gCamera;
// ----------------------------------------------------------------------------------------------

//Camera::Camera()
//{
//
//}
// ----------------------------------------------------------------------------------------------

Camera::~Camera()
{

}
// ----------------------------------------------------------------------------------------------

void Camera::Load()
{
	#if(ENABLE_DAMAGEROT)
	g_Damage.Load();
	#endif
	#if(CUSTOM_CAMERA_MOVE)
	//g_CameraMove.Load();
	#endif

}

Camera::Camera()
{
	this->Default.Zoom		= *(float*)oCam_Zoom;
	this->Default.RotationY	= *(float*)oCam_RotY;
	this->Default.RotationZ	= *(float*)oCam_RotZDef;
	this->Default.PositionZ	= *(float*)oCam_PosZ;
	this->Default.ClipX		= *(double*)oCam_ClipX;
	this->Default.ClipY		= *(float*)oCam_ClipY;
	this->Default.ClipZ		= *(double*)oCam_ClipZ;
	this->Default.ClipX2	= *(double*)oCam_ClipX2;
	this->Default.ClipY2	= *(float*)oCam_ClipY2;
	this->Default.ClipZ2	= *(float*)oCam_ClipZ2;
	this->Default.ClipGL	= *(float*)oCam_ClipGL;
	// ----
	this->InMove			= 0;
	this->IsActive			= 0;
	this->RotateMode		= 2;
	this->ZoomPercent		= 0.0;
	this->TempCursorX		= 0;
	this->TempCursorY		= 0;
	// ----
	this->ZoomPercent		= this->Default.Zoom / ((float)ZOOM_MAX / 100.0f);
}

void Camera::Init()
{
	if( pPlayerState != GameProcess )
	{
		return;
	}
	// ----

	//SetFloat((LPVOID)oCam_Zoom,		35.0f);
	//SetFloat((LPVOID)oCam_RotY,		-48.5f);
	//SetFloat((LPVOID)oCam_RotZ,		-45.0f);
	//SetFloat((LPVOID)oCam_PosZ,		150.0f);

	SetFloat((LPVOID)oCam_Zoom,		this->Default.Zoom);
	SetFloat((LPVOID)oCam_RotY,		this->Default.RotationY);
	SetFloat((LPVOID)oCam_RotZ,		this->Default.RotationZ);
	SetFloat((LPVOID)oCam_PosZ,		this->Default.PositionZ);
#if(FULL_HD==1)
	SetDouble((LPVOID)oCam_ClipX,	this->Default.ClipX + 500); 
	SetFloat((LPVOID)oCam_ClipGL,	this->Default.ClipGL + 200);
#else
	SetDouble((LPVOID)oCam_ClipX,	this->Default.ClipX);
	SetFloat((LPVOID)oCam_ClipGL,	this->Default.ClipGL);
#endif
	SetFloat((LPVOID)oCam_ClipY,	this->Default.ClipY);
	SetDouble((LPVOID)oCam_ClipZ,	this->Default.ClipZ);
	SetDouble((LPVOID)oCam_ClipX2,	this->Default.ClipX2);
	SetFloat((LPVOID)oCam_ClipY2,	this->Default.ClipY2);
	SetFloat((LPVOID)oCam_ClipZ2,	this->Default.ClipZ2);


	// ----
	this->ZoomPercent = *(float*)oCam_Zoom / ((float)ZOOM_MAX / 100.0f);

	TenFix = this->ZoomPercent;
}
// ----------------------------------------------------------------------------------------------

void Camera::Switch()
{
	if( pPlayerState != GameProcess )
	{
		return;
	}
	// ----
	this->IsActive = !this->IsActive;
}
// ----------------------------------------------------------------------------------------------

void Camera::Run(MOUSEHOOKSTRUCTEX * Mouse, WPARAM wParam)
{


	if( pMapNumber == 30 || pMapNumber == 62 )
	{
		this->IsActive = false;
		this->Init();
	}
	// ----
	switch(wParam)
	{
	case WM_MOUSEWHEEL:
		{
			if( !this->IsActive
				|| gInterface.CheckWindow(MoveList) 
				)
			{
				return;
			}
			// ----
			if( (int)Mouse->mouseData > 0 )
			{
				if( *(float*)oCam_Zoom < ZOOM_MAX )
				{
					SetFloat((LPVOID)oCam_Zoom,	*(float*)oCam_Zoom + ZOOM_INTER);
				}
				else
				{
					SetFloat((LPVOID)oCam_Zoom,	(float)ZOOM_MAX);
				}
			}
			else if( (int)Mouse->mouseData < 0 )
			{
				if( *(float*)oCam_Zoom > ZOOM_MIN )
				{
					SetFloat((LPVOID)oCam_Zoom,	*(float*)oCam_Zoom - ZOOM_INTER);
				}
				else
				{
					SetFloat((LPVOID)oCam_Zoom,	(float)ZOOM_MIN);
				}
			}
			// ----
			this->ZoomPercent = *(float*)oCam_Zoom / ((float)ZOOM_MAX / 100.0f);
			// ----
			//gConsole.Output(cGREEN,"%f %f",this->ZoomPercent,*(float*)oCam_Zoom);
			//if(*(float*)oCam_Zoom >= 50)
			{


			SetDouble((LPVOID)oCam_ClipX, PERCF(PERCF(this->Default.ClipX, 500), this->ZoomPercent));
			SetFloat((LPVOID)oCam_ClipY, PERCF(PERCF(this->Default.ClipY, 285), this->ZoomPercent));
			SetDouble((LPVOID)oCam_ClipZ, PERCF(PERCF(this->Default.ClipZ, -395), this->ZoomPercent));
			SetDouble((LPVOID)oCam_ClipX2, PERCF(PERCF(this->Default.ClipX2,235), this->ZoomPercent));
			SetFloat((LPVOID)oCam_ClipY2, PERCF(PERCF(this->Default.ClipY2,195), this->ZoomPercent));
			SetFloat((LPVOID)oCam_ClipZ2, PERCF(PERCF(this->Default.ClipZ2, -4000), this->ZoomPercent));
			SetFloat((LPVOID)oCam_ClipGL, PERCF(PERCF(this->Default.ClipGL, 250), this->ZoomPercent));



			//SetDouble((LPVOID)oCam_ClipX, PERCF(PERCF(this->Default.ClipX, 1000), this->ZoomPercent));
			//SetFloat((LPVOID)oCam_ClipY, PERCF(PERCF(this->Default.ClipY, 500), this->ZoomPercent));

			////SetDouble((LPVOID)oCam_ClipZ, PERCF(PERCF(this->Default.ClipZ, -395), this->ZoomPercent));
			////SetDouble((LPVOID)oCam_ClipX2, PERCF(PERCF(this->Default.ClipX2,235), this->ZoomPercent));
			////SetFloat((LPVOID)oCam_ClipY2, PERCF(PERCF(this->Default.ClipY2,195), this->ZoomPercent));
			////SetFloat((LPVOID)oCam_ClipZ2, PERCF(PERCF(this->Default.ClipZ2, -4000), this->ZoomPercent));
			////SetFloat((LPVOID)oCam_ClipGL, PERCF(PERCF(this->Default.ClipGL, 250), this->ZoomPercent));
			}
		}
		break;
		// --
	case WM_MBUTTONDOWN:
		{
			this->InMove = true;
		}
		break;
		// --
	case WM_MBUTTONUP:
		{
			this->InMove = false;
		}
		break;
	}

	#if(CUSTOM_CAMERA_MOVE)
	if(g_ZtLicense.user.CustomCameraMove)
	{
		g_CameraMove.Mouse(wParam, Mouse);
	}
	return;
	#endif

	this->Rotate();
}
// ----------------------------------------------------------------------------------------------

void Camera::Rotate()
{
	if( !this->IsActive )
	{
		return;
	}
	// ----																				  
	if( this->RotateMode == 1 ) //-> Auto rotation
	{
		if( gObjUser.m_CursorX <= 150 )
		{
			SetFloat((LPVOID)oCam_RotZ,	*(float*)oCam_RotZ - ROTATION_SENS);
		}
		else if( gObjUser.m_CursorX >= 500 )
		{
			SetFloat((LPVOID)oCam_RotZ,	*(float*)oCam_RotZ + ROTATION_SENS);
		}
	}
	else if( this->RotateMode == 2 && this->InMove ) //-> Manual rotation
	{
		if( this->TempCursorX < gObjUser.m_CursorX )
		{
			SetFloat((LPVOID)oCam_RotZ,	*(float*)oCam_RotZ + ROTATION_SENS);
		}
		else if( this->TempCursorX > gObjUser.m_CursorX )
		{
			SetFloat((LPVOID)oCam_RotZ,	*(float*)oCam_RotZ - ROTATION_SENS);
		}
		// ----
		this->TempCursorX = gObjUser.m_CursorX;
	}
}
// ----------------------------------------------------------------------------------------------

// ------------------------------ //
//		    Damage Rot			  //
// ------------------------------ //

#if(ENABLE_DAMAGEROT)

CDamage g_Damage;

void CDamage::DamageRot(float& X,float& Y,float D)
{
	float CamRotX = *(float*)0x087933D8;

	const float Rad = 0.01745329;
	
	float sinTh = sin(Rad * CamRotX);

	float cosTh = cos(Rad * CamRotX);

	X += D / 0.7071067 * cosTh / 2;

	Y -= D / 0.7071067 * sinTh / 2;
}

void CDamage::Load()
{
	const DWORD DamgRotCall_Offset	= 0x00637657;

	const DWORD DamgRotPatch_Offset	= 0x0063764C;

	char Hook[] = { 0x8D ,0x45 ,0xC8 ,0x8D ,0x4D ,0xC4 ,0xFF ,0x75 ,0x18 ,0x50 ,0x51 ,0xE8 ,0xB4 ,0x7A ,0x9C ,0xFF ,0x83 ,0xC4 ,0x08 ,0xE9 ,0xC9 ,0xFE ,0xFF ,0xFF };

	memcpy((LPVOID)DamgRotPatch_Offset, Hook, sizeof(Hook));

	SetOp((LPVOID)DamgRotCall_Offset, this->DamageRot, ASM::CALL);
}

#endif