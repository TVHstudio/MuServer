#pragma once

class CTimerZt
{
public:
		CTimerZt();
		~CTimerZt();

	void Init();
	void Run();
	int GetSecond();

private:
	int m_TickSecond;

};

extern CTimerZt g_TimerZt;