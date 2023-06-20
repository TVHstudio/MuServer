#pragma once

#if(CUSTOM_CAMERA_MOVE)

/*
004D89E7 - FSTP DWORD PTR DS:[87933DC]
005DBC10
006365EF - если сюда вбить координаты 
00636744 - курсор хотьбы

005B7E1E - не зачто не отвечает
*/

#define sub_5DB130			((int(__cdecl*)(int a1, char a2)) 0x5DB130)

#define CAMERAMOVE_ADD		10

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
	void Hook();

	void Move();
	void Mouse(WPARAM wParam, MOUSEHOOKSTRUCTEX* HookStruct);
	void KeyBoard(DWORD KeyID);  

	static int CreateFrustrum2D(int a1, char a2);

	void CGReqViewe(int ActiveMove);
	void GCAnsViewe(PMSG_ANS_CAMERAMOVE_VIEWE* lpMsg);

	void DrawMiniMap(float StartX, float StartY);
	
	bool m_CameraMoveKey;

	int	m_TempCursorX;
	int	m_TempCursorY;
};

extern CCameraMove g_CameraMove;

#endif