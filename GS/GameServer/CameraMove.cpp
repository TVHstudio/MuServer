#include "StdAfx.h"
#include "..\\include\\prodef.h"
#include "giocp.h"
#include "user.h"
#include "CameraMove.h"
#include "ZtLicense.h"

#if(CUSTOM_CAMERA_MOVE)

CCameraMove g_CameraMove;

CCameraMove::CCameraMove()
{
	this->Init();
}

CCameraMove::~CCameraMove()
{
}

void CCameraMove::Init()
{
}

void CCameraMove::Load()
{
	this->Init();

	if(g_ZtLicense.user.CustomCameraMove)
	{
		return;
	}

}

void CCameraMove::CGReqViewe(PMSG_REQ_CAMERAMOVE_VIEWE* lpMsg, int aIndex)
{
	if(!g_ZtLicense.user.CustomCameraMove)
	{
		return;
	}

	if(!lpMsg->Result)
	{
		return;
	}

	int iActive = lpMsg->Active;

	int iX = lpMsg->X;

	int iY = lpMsg->Y;

	LPOBJ lpUser = &gObj[aIndex];

	//// =====

	////gObjViewportClose(lpUser);
	////gObjViewportListProtocolDestroy(lpUser);

	//	gObjViewportListProtocolDestroy(&gObj[aIndex]); //season4 add-on

	//	//GCTeleportSend(&gObj[aIndex],gt,mapNumber,gObj[aIndex].X,gObj[aIndex].Y,gObj[aIndex].Dir);
	//	
	//	gObjViewportListProtocolCreate(&gObj[aIndex]); //season4 add-on

	//	gObjClearViewport(&gObj[aIndex]);

	//					//	gObjViewportListDestroy(aIndex);
	//					//}
	//					//for (int  n=0;n<OBJMAX;n++)
	//					//{
	//					//	gObjViewportListCreate(n);
	//					//}
	//					//for (int n=0;n<OBJMAX;n++)
	//					//{
	//					//	gObjViewportListProtocol(n);	return;

	//// =====

	lpUser->m_CamMove = iActive;
	lpUser->m_CamX = iX;
	lpUser->m_CamY = iY;

	//this->GCAnsViewe(aIndex);
}

void CCameraMove::GCAnsViewe(int aIndex)
{
	LPOBJ lpUser = &gObj[aIndex];

	//gObjClearViewport(lpUser);
	//gObjViewportListCreate(lpUser->m_Index);
	//gObjViewportListProtocolCreate(lpUser);
}

BOOL CCameraMove::CheckViewport(int aIndex, int x, int y)
{
	LPOBJ lpUser = &gObj[aIndex];

	int iCamViewe = 20;
	int iCamX = lpUser->m_CamX;
	int iCamY = lpUser->m_CamY;

	if(x < iCamX - iCamViewe  || x > iCamX + iCamViewe || y < iCamY - iCamViewe || y > iCamY + iCamViewe)
	{
		return false;
	}

	return true;
}

#endif