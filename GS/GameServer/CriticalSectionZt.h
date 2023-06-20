#pragma once

#include "StdAfx.h"

class CCriticalSectionZt
{
public:
	CCriticalSectionZt();
	virtual ~CCriticalSectionZt();
	void lock();
	void unlock();

private:
	CRITICAL_SECTION m_critical;
};