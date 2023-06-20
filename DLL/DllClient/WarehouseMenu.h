#pragma once




class CWarehouseMenu
{
public:
		CWarehouseMenu();
		~CWarehouseMenu();

	void Load();
	void BindImg();
	void DrawUser();
	void DrawGuild();
	void MouseUser(DWORD Event);
	void MouseGuild(DWORD Event);
	void CGSendUser();
	void CGSendGuild();
	void GCRecvUser();
	void GCRecvGuild();

};

extern CWarehouseMenu g_WarehouseMenu;