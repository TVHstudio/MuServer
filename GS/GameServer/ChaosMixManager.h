#include "StdAfx.h"
#ifdef DRYNEA_LIST_CUSTOM
// b.��������?����?�� ���� Mixmanager
#endif
#define MAX_MIX 2000
#define CHAOS_ITEM 2000
#define MIX_DIR "..\\Data\\ZtData\\ChaosMixManager.ini"

class cChaosMixManager
{
private:
	int MixCount;
	int MixID[MAX_MIX];
	int MixPercent[MAX_MIX];
	int ItemCount[MAX_MIX];
	int MixZen[MAX_MIX];

	struct
	{
		int MixType;
		int Type;
		int Index;
		int Lvl;
		int Skill;
		int Luck;
		int Opt;
		int Exl;
		int Anc;
		int MinSocket;
		int MaxSocket;
	}Mix[MAX_MIX][CHAOS_ITEM];

	void Box(int aIndex, int IMix, int Num);
	bool nIBox(int aIndex, int iType, int iLevel, int iSkill, int iLuck, int iOpt, int iExl, int iAnc);

public:
	void Init();
	bool Main(int aIndex, int MixIndex);

};
extern cChaosMixManager ChaosMixManager;