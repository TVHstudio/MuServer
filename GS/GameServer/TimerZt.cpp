#include "StdAfx.h"
#include "TimerZt.h"

CTimerZt g_TimerZt;

CTimerZt::CTimerZt()
{
	this->Init();
}

CTimerZt::~CTimerZt()
{
}

void CTimerZt::Init()
{
	this->m_TickSecond = 0;
}

void CTimerZt::Run()
{
	this->m_TickSecond++;

	if(this->m_TickSecond >= 60)
	{
		this->m_TickSecond = 0;
	}
}

int CTimerZt::GetSecond()
{
	return this->m_TickSecond;
}