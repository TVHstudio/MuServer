#pragma once

#if(ENABLE_PACK_MANAGER)

#include "NewInterface.h"
#include "Protocol.h"

struct PackSystemData
{
	int JewelID;
	int JewelBundleID;
	int Price10;
	int Price20;
	int Price30;
	int PriceUnPack10;
	int PriceUnPack20;
	int PriceUnPack30;
};

enum eCurrentPage
{
	eJewelPackType = 0,
	eJewelPackMix = 1,
	eJewelPackUnMix = 2,
	eJewelPackConfirm = 3,
};

struct CG_MIX_SEND
{
	PBMSG_HEAD2	h;
	int index;
	int type;
};

struct CG_MIX_RESULT_SEND
{
	PBMSG_HEAD2	h;
	BYTE result;
};

struct PMSG_RECV_PACKSYSTEM
{
	PWMSG_HEAD2 header;
	int count;
};

#define CGNpcTalkCloseSend			((void(*)()) 0x4E0E60)

class CPackSystem
{
public:
	void Init();
	void AddItem(PackSystemData* data);
	int getCountOfItems() {return this->m_Data.size();}
	PackSystemData* getInfoByID(int index);

	void SwitchPackSystemWindowState() {(gInterface.Data[ePack].OnShow == true)? gInterface.Data[ePack].Close(),CGNpcTalkCloseSend(),this->currentPage = 0,this->currentType=-1 : gNewInterface.m_Data[ePack].Open();};
	void Draw();
	bool EventPackWindow(DWORD Event);
	void SendPack(int type);
	void GC_ResultRecv(CG_MIX_RESULT_SEND* lpMsg);
	void GCPackSystemDataRecv(PMSG_RECV_PACKSYSTEM* lpMsg);
	char* ParseReducedValue(DWORD Num);

private:
	int currentPage;
	int selectedIndex;
	int currentType;
	std::vector<PackSystemData> m_Data;
}; 

extern CPackSystem gPackSystem;



#endif