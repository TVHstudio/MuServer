#include "StdAfx.h"
#include "protocol.h"

struct ZT_GC_CONFIG_SEND
{
	PBMSG_HEAD2 h;
	BYTE CharSwitch;	
	BYTE sGENS;
	short HelperLevel;
	BYTE AutoParty;
	BYTE Top100;
	BYTE EventTimer;
	BYTE MoveTargetPosEffect;
	BYTE CastleSiegeSkill;
	BYTE AntiCheat;
	BYTE GensColorEnable;
	BYTE GensColorRed;
	BYTE GensColorGreen;
	BYTE GensColorBlue;
	int MaxStats;
	BYTE DLReflect;
	BYTE MasterSkills;
	DWORD DivFireScreamSpeed;
	int MultiWarehouse;
	int MaxLevel;
};

void ztGCConfigSend(int aIndex);
bool ztCheckSimbol(char* String, int StrLen);
char * ztMapName(int MapNum);
CTime StrToCTime(const char* str);
bool CheckFile(char* File);
bool CheckOptionItem(int Item1, int Item2, int iType);
void CheckAndFixMinNumber(int &Number, int MinNumber);
void CheckAndFixNumber(int &Number, int MinNumber, int MaxNumber);