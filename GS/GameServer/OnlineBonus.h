#pragma once

#define ONLINEBONUS_DIR "..\\Data\\ZtData\\OnlineBonus.ini"

class OnlineBonus
{
private:
	int Enable;

	int WCoinCActive;
	int WCoinCTime;
	int WCoinCBonus;

	int WCoinPActive;
	int WCoinPTime;
	int WCoinPBonus;

	int GoblinActive;
	int GoblinTime;
	int GoblinBonus;

	int ZtCredActive;
	int ZtCredTime;
	int ZtCredBonus;

#if(LICENSE_UKRAINE)
	int AutoExpActive;
	int AutoExpTimeSec;
	int AutoExpBonus;
	int AutoExpMaxLvl;
#endif

public:
	void Load();
	void TickTime(int aIndex);
	void TickSecond(int aIndex);
};
extern OnlineBonus gOnlineBonus;

