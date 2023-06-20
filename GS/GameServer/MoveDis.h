#pragma once

#include "user.h"

#if(ENABLE_MOVE_DIS)

#define MAX_MOVE_DIS	5

struct MOVEDIS_DATA
{
	bool Active;
	bool Show;
	short X;
	short Y;
	int TickCount;
};

class CMoveDis
{
public:
	 CMoveDis();
	~CMoveDis();
	void Init();
	void Load();
	void Start(int aIndex);
	void MoveProc(int aIndex);
	int CalDistance(int X1, int Y1, int X2, int Y2);

	MOVEDIS_DATA m_User[OBJMAX];
};

extern CMoveDis g_MoveDis;

#endif