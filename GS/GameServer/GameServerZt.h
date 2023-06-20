#pragma once


#if(ENABLE_GAMESERVER_DLL)


class CGameServerZt
{
public:
		CGameServerZt();
		~CGameServerZt();

	void Load();
	void TimerSecond();
};

extern CGameServerZt g_GameServerZt;

#endif