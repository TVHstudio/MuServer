#pragma once

#if(ENABLE_MAPRULES)

struct MAPRULES_DATA
{
	int MapNumber;
	int ResetNumber;
	int GrandNumber;
};

class CMapRules
{
	void Load();
	void Run();
	bool GetResult(int aIndex);

	std::vector<MAPRULES_DATA> m_Data;
};

extern CMapRules g_MapRules;

#endif