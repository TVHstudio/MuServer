#pragma once 

#if(DEV_ZTMENU_V3)

/*
	newui_position02
	MonsterCount
	0x7A0C - BattleSkill
*/

enum ZTMENU_NUMBER
{
	eVERSION_NO		= 0,
	eVERSION_NS		= 1,
	eVERSION_ET		= 2,
	eVERSION_WB		= 3,
	eVERSION_CHEBUK = 4,
};

class CZtMenuV3
{
public:
	CZtMenuV3();
	~CZtMenuV3();

	void Init();
	void LoadIMG();
	void Bind();
	void Load(ZTMENU_NUMBER Number);
	void DrawMain();
	void DrawMenu();
	void DrawMenuChebuk();
	
	void DrawWindow();
	void DrawWindowChebuk();
	float DrawButton(char* Text, int ID, float X, float Y);

	void CursorButton(DWORD Event);

	void DrawMenu2();
	void DrawWindow2();

	bool m_Enable;
	int m_Version;
};

extern CZtMenuV3 g_ZtMenuV3;

#endif