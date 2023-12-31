// Queue.h: interface for the CQueue class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "StdAfx.h"

#if(ENABLE_PROTOCOL_QUEUE || DEV_SOCKET_MANAGER)

#include "CriticalSectionZt.h"
#include <queue>

#define MAX_QUEUE_SIZE 2048

struct QUEUE_INFO
{
	WORD index;
	BYTE head;
	BYTE buff[8192];
	DWORD size;
	DWORD encrypt;
	int serial;	//DWORD serial;
};

class CQueue
{
public:
	CQueue();
	virtual ~CQueue();
	void ClearQueue();
	DWORD GetQueueSize();
	bool AddToQueue(QUEUE_INFO* lpInfo);
	bool GetFromQueue(QUEUE_INFO* lpInfo);
private:
	CCriticalSectionZt m_critical;
	std::queue<QUEUE_INFO> m_QueueInfo;
};

#endif