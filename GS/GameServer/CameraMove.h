#pragma once

#if(CUSTOM_CAMERA_MOVE)


#define CAMERAMOVE_ADD		20

struct PMSG_REQ_CAMERAMOVE_VIEWE
{
	PBMSG_HEAD2 h;
	int Result;
	int Active;
	int X;
	int Y;
};

struct PMSG_ANS_CAMERAMOVE_VIEWE
{
	PBMSG_HEAD2 h;
};

class CCameraMove
{
public:
		 CCameraMove();
		 ~CCameraMove();

	void Init();
	void Load();

	void CGReqViewe(PMSG_REQ_CAMERAMOVE_VIEWE* lpMsg, int aIndex);
	void GCAnsViewe(int aIndex);

	BOOL CheckViewport(int aIndex, int x, int y);
};

extern CCameraMove g_CameraMove;

#endif