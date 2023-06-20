#pragma once

#if(ENABLE_PACK_MANAGER)

class CPackManager
{
public:
	CPackManager();
	~CPackManager();
};

extern CPackManager g_PackManager;

#endif