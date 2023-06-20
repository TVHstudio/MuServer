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
	int Map;
	int Player;
	int Party;
	int Guild;
	int Alliance;
	int Phonoman;
	int NPC;
	int Monster;
	int Boss;
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
	void Read(char*filename);
	void Run();
	void GCMapSend(int aIndex);
	MINIMAP_DATA* GetData(int MapNum);

	int m_Enable;

	std::vector<MINIMAP_DATA> m_Data;
};

extern CMiniMapZt g_MiniMapZt;


#endif