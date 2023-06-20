#pragma once

#if(CUSTOM_ITEM_MOVE)

#define ITEM_MOVE_DATA_MAX	1000

#define ITEM_MOVE_PATH "..\\Data\\ZtData\\ItemMove.txt"

struct ITEM_MOVE_DATA
{
	int Type;	
	int Index;	
	int AllowDrop;	
	int AllowSell;
	int AllowTrade;	
	int AllowVault;
};

class CItemMove
{
public:
		 CItemMove();
		 ~CItemMove();

	void Init();
	void Load();
	void Read(char* FileName);

	bool CheckDrop(int ItemType);
	bool CheckSell(int ItemType);
	bool CheckTrade(int ItemType);
	bool CheckVault(int ItemType);

	//ITEM_MOVE_DATA m_Data[ITEM_MOVE_DATA_MAX];
	std::vector<ITEM_MOVE_DATA> m_Data;
};

extern CItemMove g_ItemMove;

#endif