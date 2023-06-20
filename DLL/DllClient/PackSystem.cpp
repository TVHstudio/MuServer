#include "stdafx.h"
#include "Interface.h"
#include "NewInterface.h"
#include "User.h"
#include "PackSystem.h"
#include "Font.h"

#if(ENABLE_PACK_MANAGER)

CPackSystem gPackSystem;

void CPackSystem::Init()
{
	this->m_Data.clear();
	this->currentPage = eJewelPackType;
	this->selectedIndex = -1;
	this->currentType = -1;
}

void CPackSystem::AddItem(PackSystemData* data)
{
	this->m_Data.push_back(*data);
	//g_Console.AddMessage(5,"TEST = %d %d %d",this->m_Data[m_Data.size()-1].JewelID,this->m_Data[m_Data.size()-1].JewelBundleID,this->m_Data[m_Data.size()-1].Price);
}

PackSystemData* CPackSystem::getInfoByID(int index)
{
	return &this->m_Data[index];
}

void CPackSystem::Draw()
{
	if (!gNewInterface.CheckWindow(ePack))
	{
		return;
	}

	pSetCursorFocus = true;

	
	if (this->currentPage == eJewelPackType)
	{
		float MainWidth			= 190.0;
		float MainHeight		= 90.0;
		//float StartY			= 80.0;
		float StartY			= (MAX_WIN_HEIGHT-50)/2-MainHeight/2;
		float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
		gNewInterface.DrawBackground(-1,StartX,StartY,MainWidth,MainHeight,"[Pack System]");

		gNewInterface.DrawButton(ePackJewelPack,StartX+10,StartY+20,170,20,&gNewInterface.Button,&gNewInterface.ButtonOnClick,&gNewInterface.ButtonHover,"Pack");
		gNewInterface.DrawButton(ePackJewelUnPack,StartX+10,StartY+50,170,20,&gNewInterface.Button,&gNewInterface.ButtonOnClick,&gNewInterface.ButtonHover,"UnPack");
	}
	else if (this->currentPage == eJewelPackMix)
	{
		int count = gPackSystem.getCountOfItems();
		float MainWidth			= 190.0;
		float MainHeight		= 20.0+(30*ceil((float)count/2));
		float StartY			= (MAX_WIN_HEIGHT-50)/2-MainHeight/2;
		float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
		gNewInterface.DrawBackground(-1,StartX,StartY,MainWidth,MainHeight,"[Pack System::Jewel Pack]");

		int counter=0;

		for	(int i=0; i<count;i++)
		{
			PackSystemData* lpInfo = gPackSystem.getInfoByID(i);

			if (i%2==0 && i != 0)
			{
				counter++;
			}

			ItemBmdStruct* ItemBmdInfo = pGetItemBmdStruct(lpInfo->JewelID);

			gNewInterface.DrawButton(ePackJewel1+i,StartX+10+(90*(i-counter*2)),StartY+20+(30*counter),80,20,&gNewInterface.Button,&gNewInterface.ButtonOnClick,&gNewInterface.ButtonHover,ItemBmdInfo->Name);
		}
	}
	else if (this->currentPage == eJewelPackConfirm)
	{
		float MainWidth			= 190.0;
		float MainHeight		= 120.0;
		//float StartY			= 50.0;
		float StartY			= (MAX_WIN_HEIGHT-50)/2-MainHeight/2;
		float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
		gNewInterface.DrawBackground(-1,StartX,StartY,MainWidth,MainHeight,"[Pack System::Jewel Pack]");

		PackSystemData* lpInfo = gPackSystem.getInfoByID(this->selectedIndex);

		if (this->currentType == 0)
		{
			ItemBmdStruct* ItemBmdInfo = pGetItemBmdStruct(lpInfo->JewelID);
			gNewInterface.TextDraw(StartX+MainWidth/2,StartY+17,0,1,eGold,0,8,gFont[ARIAL_16]->m_Font,ItemBmdInfo->Name);

			char Text[100];

			sprintf_s(Text,"Combine 10 (Price %d)",lpInfo->Price10);
			gNewInterface.DrawButton(ePackConfirm10,StartX+10,StartY+30,170,20,&gNewInterface.Button,&gNewInterface.ButtonOnClick,&gNewInterface.ButtonHover,Text);
			sprintf_s(Text,"Combine 20 (Price %d)",lpInfo->Price20);
			gNewInterface.DrawButton(ePackConfirm20,StartX+10,StartY+60,170,20,&gNewInterface.Button,&gNewInterface.ButtonOnClick,&gNewInterface.ButtonHover,Text);
			sprintf_s(Text,"Combine 30 (Price %d)",lpInfo->Price30);
			gNewInterface.DrawButton(ePackConfirm30,StartX+10,StartY+90,170,20,&gNewInterface.Button,&gNewInterface.ButtonOnClick,&gNewInterface.ButtonHover,Text);
		}
		else if (this->currentType == 1)
		{
			ItemBmdStruct* ItemBmdInfo = pGetItemBmdStruct(lpInfo->JewelBundleID);
			gNewInterface.TextDraw(StartX+MainWidth/2,StartY+17,0,1,eGold,0,8,gFont[ARIAL_16]->m_Font,ItemBmdInfo->Name);

			char Text[100];

			sprintf_s(Text,"Disband 10 (Price %d)",lpInfo->PriceUnPack10);
			gNewInterface.DrawButton(ePackConfirm10,StartX+10,StartY+30,170,20,&gNewInterface.Button,&gNewInterface.ButtonOnClick,&gNewInterface.ButtonHover,Text);
			sprintf_s(Text,"Disband 20 (Price %d)",lpInfo->PriceUnPack20);
			gNewInterface.DrawButton(ePackConfirm20,StartX+10,StartY+60,170,20,&gNewInterface.Button,&gNewInterface.ButtonOnClick,&gNewInterface.ButtonHover,Text);
			sprintf_s(Text,"Disband 30 (Price %d)",lpInfo->PriceUnPack30);
			gNewInterface.DrawButton(ePackConfirm30,StartX+10,StartY+90,170,20,&gNewInterface.Button,&gNewInterface.ButtonOnClick,&gNewInterface.ButtonHover,Text);
		}
		else
		{
			gNewInterface.TextDraw(StartX+MainWidth/2,StartY+17,0,1,eGold,0,8,gFont[ARIAL_16]->m_Font,"ERROR!");
		}
		
	}
	else if (this->currentPage == eJewelPackUnMix)
	{
		int count = gPackSystem.getCountOfItems();
		float MainWidth			= 190.0;
		float MainHeight		= 20.0+(30*ceil((float)count/2));
		float StartY			= (MAX_WIN_HEIGHT-50)/2-MainHeight/2;
		float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
		gNewInterface.DrawBackground(-1,StartX,StartY,MainWidth,MainHeight,"[Pack System::Jewel UnPack]");

		int counter=0;

		for	(int i=0; i<count;i++)
		{
			PackSystemData* lpInfo = gPackSystem.getInfoByID(i);

			if (i%2==0 && i != 0)
			{
				counter++;
			}

			ItemBmdStruct* ItemBmdInfo = pGetItemBmdStruct(lpInfo->JewelBundleID);

			//char Text[100];
			//sprintf_s(Text,"Bundled %s",ItemBmdInfo->Name);

			gNewInterface.DrawButton(ePackJewel1+i,StartX+10+(90*(i-counter*2)),StartY+20+(30*counter),80,20,&gNewInterface.Button,&gNewInterface.ButtonOnClick,&gNewInterface.ButtonHover,ItemBmdInfo->Name);
		}
	}
}

bool CPackSystem::EventPackWindow(DWORD Event)
{
	//((BOOL(__thiscall*)(LPVOID This))0x0077FAE0)(This);
	//g_Console.AddMessage(5,"Value = %d",((int(*)())0x7B9E50)());
	//g_Console.AddMessage(5,"Value = %d",*(DWORD*)0x9816D14);
	
	//int lol = ((signed int(*)())0x005C6E80)();
	//g_Console.AddMessage(5,"lol = %d",lol);
	//signed int sub_5C6E80()

	if (!gNewInterface.CheckWindow(ePack))
	{
		return false;
	}

	if (Event!=WM_LBUTTONUP)
	{
		return false;
	}
	//g_Console.AddMessage(5,"KEKIY");
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay	= (CurrentTick - gNewInterface.m_Data[ePack].EventTick);

	if (this->currentPage == eJewelPackType)
	{
		if (gNewInterface.IsWorkZone(ePackJewelPack))
		{
			
			gNewInterface.m_Data[ePackJewelPack].OnClick = false;
			if( Delay < 500 )
			{
				return false;
			}
			gNewInterface.m_Data[ePack].EventTick	= GetTickCount();

			this->currentPage = eJewelPackMix;
			this->currentType = 0;
			return true;
		}
		else if (gNewInterface.IsWorkZone(ePackJewelUnPack))
		{
			
			gNewInterface.m_Data[ePackJewelUnPack].OnClick = false;
			if( Delay < 500 )
			{
				return false;
			}
			gNewInterface.m_Data[ePack].EventTick	= GetTickCount();

			this->currentPage = eJewelPackUnMix;
			this->currentType = 1;
			//*(DWORD*)0x9816D14 = 1;
			//g_Console.AddMessage(5,"Press");
			return true;
		}
	}

	if (this->currentPage == eJewelPackMix)
	{
		for	(int i=0; i<gPackSystem.getCountOfItems();i++)
		{
			if (gNewInterface.IsWorkZone(ePackJewel1+i))
			{
				//DWORD Delay	= (CurrentTick - gNewInterface.m_Data[ePackJewel1+i].EventTick);
				gNewInterface.m_Data[ePackJewel1+i].OnClick = false;
				if( Delay < 500 )
				{
					return false;
				}
				gNewInterface.m_Data[ePack].EventTick	= GetTickCount();

				this->selectedIndex = i;
				this->currentPage = eJewelPackConfirm;
				return true;
			}
		}
	}

	if (this->currentPage == eJewelPackUnMix)
	{
		for	(int i=0; i<gPackSystem.getCountOfItems();i++)
		{
			if (gNewInterface.IsWorkZone(ePackJewel1+i))
			{
				//DWORD Delay	= (CurrentTick - gNewInterface.m_Data[ePackJewel1+i].EventTick);
				gNewInterface.m_Data[ePackJewel1+i].OnClick = false;
				if( Delay < 500 )
				{
					return false;
				}
				gNewInterface.m_Data[ePack].EventTick	= GetTickCount();

				this->selectedIndex = i;
				this->currentPage = eJewelPackConfirm;
				return true;
			}
		}
	}

	if (this->currentPage == eJewelPackUnMix)
	{
		for	(int i=0; i<gPackSystem.getCountOfItems();i++)
		{
			if (gNewInterface.IsWorkZone(ePackJewel1+i))
			{
				//DWORD Delay	= (CurrentTick - gNewInterface.m_Data[ePackJewel1+i].EventTick);
				gNewInterface.m_Data[ePackJewel1+i].OnClick = false;
				if( Delay < 500 )
				{
					return false;
				}
				gNewInterface.m_Data[ePack].EventTick	= GetTickCount();

				this->selectedIndex = i;
				this->currentPage = eJewelPackConfirm;
				return true;
			}
		}
	}

	if (this->currentPage == eJewelPackConfirm)
	{
		if( Delay < 500 )
		{
			return false;
		}

		if (gNewInterface.IsWorkZone(ePackConfirm10))
		{
			this->SendPack(0);
			this->SwitchPackSystemWindowState();
			gNewInterface.m_Data[ePack].EventTick	= GetTickCount();
			return true;
		}
		if (gNewInterface.IsWorkZone(ePackConfirm20))
		{
			this->SendPack(1);
			this->SwitchPackSystemWindowState();
			gNewInterface.m_Data[ePack].EventTick	= GetTickCount();
			return true;
		}
		if (gNewInterface.IsWorkZone(ePackConfirm30))
		{
			this->SendPack(2);
			this->SwitchPackSystemWindowState();
			gNewInterface.m_Data[ePack].EventTick	= GetTickCount();
			return true;
		}
	}
	return false;
}

void CPackSystem::SendPack(int type)
{
	CG_MIX_SEND pMsg;
	if (this->currentType==0)
	{
		pMsg.h.set((LPBYTE)&pMsg,0xFF,0x19,sizeof(pMsg));
	}
	else if (this->currentType==1)
	{
		pMsg.h.set((LPBYTE)&pMsg,0xFF,0x1A,sizeof(pMsg));
	}
	else
	{
		gNewInterface.OpenMessageBox("[ERROR]","Contact server administrator! [SendPack]");
	}
	pMsg.index = this->selectedIndex;
	pMsg.type = type;

	gProtocol.DataSend((BYTE*)&pMsg,pMsg.h.size);
}

void CPackSystem::GC_ResultRecv(CG_MIX_RESULT_SEND* lpMsg)
{
	switch(lpMsg->result)
	{
		case 1:
			//gInterface.DrawMessageBox("Successfully!");
			gNewInterface.OpenMessageBox("[Pack System]","Successfully!");
		break;
		case 4:
			gNewInterface.OpenMessageBox("[Pack System]","You dont have enough jewels!");
			//gInterface.DrawMessageBox("You dont have enough jewels!");
		break;
		case 5:
			//gInterface.DrawMessageBox("You dont have enough money!");
			gNewInterface.OpenMessageBox("[Pack System]","You dont have enough money!");
		break;
		default:
			//gInterface.DrawMessageBox("Error! Contact server administrator! [%d]",lpMsg->result);
			gNewInterface.OpenMessageBox("[ERROR]","Contact server administrator! [%d]",lpMsg->result);
		break;
	}
}

void CPackSystem::GCPackSystemDataRecv(PMSG_RECV_PACKSYSTEM* lpMsg)
{
	gPackSystem.Init();

	for (int n=0;n<lpMsg->count;n++)
	{
		PackSystemData* lpInfo = (PackSystemData*)(((BYTE*)lpMsg)+sizeof(PMSG_RECV_PACKSYSTEM)+(sizeof(PackSystemData)*n));

		//gSmithy.GCSocketRecv(lpInfo->index);
		gPackSystem.AddItem(lpInfo);
	}
}

char* CPackSystem::ParseReducedValue(DWORD Num)
{
	char Text[50];
	if (Num >= 10000000000)
		sprintf(Text, "%ldkkk", Num / 1000000000);
	else if (Num >= 10000000)
		sprintf(Text, "%ldkk", Num / 1000000);
	else if (Num >= 10000)
		sprintf(Text, "%ldk", Num / 1000);
	else
		sprintf(Text, "%ld", Num);

	return strdup(Text);
}

#endif