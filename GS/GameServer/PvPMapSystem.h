#include "StdAfx.h"
#include "MapClass.h"
#define PVPMAPSYSTEM_DIR	"..\\Data\\ZtData\\PvPSystem.ini"

#if(ENABLE_MAP_RULE)

struct MAP_RULE_DATA
{
	int MapNumber;
	int MinReset;
	int MaxReset;
	int MinGrand;
	int MaxGrand;
};

#endif

class cPvPMapSystem
{
private:
	int EnablePvPMap;
	int EnableLoraRing;
	struct  
	{
		int Map;
		int Status;
#if UPDATE_PVP == 1
		int X1;
		int X2;
		int Y1;
		int Y2;
#endif
	}PvP[MAX_NUMBER_MAP];
	int pCount;
public:
	void LoadConfig();
	bool CheckAttackMap(LPOBJ lpObj, LPOBJ lpTargetObj);
	bool CheckPkMap(LPOBJ lpObj, LPOBJ lpTargetObj);
	bool CheckPvPMap(LPOBJ lpObj);

	#if(ENABLE_MAP_RULE)
	bool GetMapRule(int aIndex, int MapNum);
	#endif

	int m_LoraRingX1;
	int m_LoraRingY1;
	int m_LoraRingX2;
	int m_LoraRingY2;

	#if(ENABLE_MAP_RULE)
	std::vector<MAP_RULE_DATA> m_MapRule;
	#endif
};
extern cPvPMapSystem PvPMapSystem;