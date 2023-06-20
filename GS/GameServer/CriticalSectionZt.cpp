#include "StdAfx.h"
#include "CriticalSectionZt.h"

CCriticalSectionZt::CCriticalSectionZt()
{
	InitializeCriticalSection(&this->m_critical);
}

CCriticalSectionZt::~CCriticalSectionZt()
{
	DeleteCriticalSection(&this->m_critical);
}

void CCriticalSectionZt::lock()
{
	EnterCriticalSection(&this->m_critical);
}

void CCriticalSectionZt::unlock()
{
	LeaveCriticalSection(&this->m_critical);
}
