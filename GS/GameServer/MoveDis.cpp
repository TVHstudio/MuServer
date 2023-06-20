#include "StdAfx.h"
#include "MoveDis.h"
#include "ConnectZt.h"
#include "logproc.h"

#if(ENABLE_MOVE_DIS)

CMoveDis g_MoveDis;

CMoveDis::CMoveDis()
{
	this->Init();
}

CMoveDis::~CMoveDis()
{

}

void CMoveDis::Init()
{
	memset(this->m_User, 0, sizeof(this->m_User));
}

void CMoveDis::Load()
{
	this->Init();
}

void CMoveDis::Start(int aIndex)
{
	this->m_User[aIndex].Active = true;
	this->m_User[aIndex].Show;
}

void CMoveDis::MoveProc(int aIndex)
{
	int iTickCount = GetTickCount();

	if(this->m_User[aIndex].Show)
	{
		
	}

	if(iTickCount > this->m_User[aIndex].TickCount + 1000)
	{
		this->m_User[aIndex].TickCount = iTickCount;

		LPOBJ lpUser = &gObj[aIndex];

		if(this->CalDistance(lpUser->X, lpUser->Y, this->m_User[aIndex].X, this->m_User[aIndex].Y) > MAX_MOVE_DIS)
		{
			LogAddC(2,"[AntiHack] Move Hack Accaunt: %s, NickName: %s",lpUser->AccountID,lpUser->Name);

			g_ConnectZt.SendClose(aIndex, NORM_DC);
		}
	}
}

int CMoveDis::CalDistance(int X1, int Y1, int X2, int Y2)
{
	if(X1 == X2 && Y1 == Y2)
	{
		return 0;
	}

	float tx = (float)(X1 - X2);
	float ty = (float)(Y1 - Y2);

	return (int)(sqrt((tx*tx)+(ty*ty)));
}


#endif