#pragma once

#if(CUSTOM_MAP_TELEPORT)

#define MAX_MAPTELEPORT	40


struct MAPTELEPORT_DATA
{
	char MapName[20];
	int PointX;
	int PointY;
	int MinLevel;
	int MaxLevel;
	int MinReset;
	int MaxReset;
	int MinGrand;
	int MaxGrand;
	int PriceZen;
	int PriceWcoin;
	int PriceCredit;
	int NeedMaster;
	int NeedPK;
	int NeedGuild;
	int EmptyInvintory;
	int Premium;
};

struct MAPTELEPORT_USER
{
	int Level;
	int Reset;
	int Grand;
	int Zen;
	int WCoin;
	int Credit;
	int Master;
	int PKLevel;
	int Guild;
	int Invintory;
	int Premium;
};

struct PMSG_REQ_MAPTELEPORT_DATA
{
	PBMSG_HEAD2 h;
	BYTE Result;
};

struct PMSG_ANS_MAPTELEPORT_DATA
{ 
	PWMSG_HEAD2 h;
	int Count;
	MAPTELEPORT_USER User;
};

struct PMSG_REQ_MAPTELEPORT_SELECT
{
	PBMSG_HEAD2 h;
	int Result;
	int SelectNumber;
};

struct PMSG_ANS_MAPTELEPORT_SELECT
{
	PBMSG_HEAD2 h;
	int Result;
};

class CMapTeleport
{
public:
		 CMapTeleport();
		 ~CMapTeleport();

	void Init();
	void Load();
	void Hook();
	void Read(char* File);

	void LoadTeleportEx();
	void BindTeleportEx();
	void DrawTeleportEx();
	void DrawInfo(int ID, float StartX, float StartY, float Width, float Hight);
	
	DWORD GetColor(int Number, int Min);
	DWORD GetColor(int Number, int Min, int Max);
	int GetCountLine(MAPTELEPORT_DATA* lpData);
	
	void MouseTeleportEx(DWORD Event);
	static void KeyboardTeleportEx();	

	void CGReqData();
	void GCAnsData(PMSG_ANS_MAPTELEPORT_DATA* lpMsg);
	void CGReqSelect(int SelectNumber);
	void GCAnsSelect(PMSG_ANS_MAPTELEPORT_SELECT* lpMsg);

	int m_LoadedCount;
	MAPTELEPORT_DATA m_Data[MAX_MAPTELEPORT];
	
	MAPTELEPORT_USER m_User;
};

extern CMapTeleport g_MapTeleport;

#endif