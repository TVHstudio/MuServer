#pragma once

#if(ENABLE_MINIMAP_ZT)

#define MINIMAP_MAX		1024

enum 
{
	eMINIMAP_NONE,
	eMINIMAP_PLAYER,
	eMINIMAP_PARTY,
	eMINIMAP_GUILD,
	eMINIMAP_ALLIANCE,
	eMINIMAP_PHONOMAN,
	eMINIMAP_NPC,
	eMINIMAP_MONSTER,
	eMINIMAP_BOSS,
};


struct MINIMAP_DATA
{
	int Type;
	int Red;
	int Green;
	int Blue;
	int Alfa;
	int Size;
};

struct MINIMAP_MONSTER
{
	BYTE Type;
	BYTE MapX;
	BYTE MapY;
};

struct PMSG_MINIMAPZT
{
	PWMSG_HEAD2 h;
	int DataCount;
};

class CMiniMapZt
{
public:
		CMiniMapZt();
		~CMiniMapZt();

	void Load();
	void LoadImg();
	void BindImg();
	void Read(char* filename);
	void Run();
	void DrawMain();
	bool DrawCheck();
	void CGMapRecv(LPBYTE lpMsg);

	int m_Enable;
	bool m_Show;

	std::vector<MINIMAP_DATA> m_Config;

	MINIMAP_MONSTER m_Data[MINIMAP_MAX];
	int m_DataCount;
};

extern CMiniMapZt g_MiniMapZt;


#endif