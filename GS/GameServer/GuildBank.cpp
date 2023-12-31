#include "StdAfx.h"
#include "user.h"
#include "GuildBank.h"
#include "DSProtocol.h"
#include "DBSockMng.h"
#include "logproc.h"
#include "GuildClass.h"
#include "GameMain.h"
#include "ZtLicense.h"
#include "protocol.h"
#include "ZtUser.h"

#if(DEV_GUILDBANK)

CGuildBank g_GuildBank;

void CGuildBank::Load()
{
	this->m_iEnable = 0;
	this->m_iGuildBankMap = 0;

	if(g_ZtLicense.CheckUser(eZtUB::Local) ||
	   g_ZtLicense.CheckUser(eZtUB::MedoniAndrei) ||
	   g_ZtLicense.CheckUser(eZtUB::Gredy) || 
	   g_ZtLicense.CheckUser(eZtUB::GredyLocal) || 
	   g_ZtLicense.CheckUser(eZtUB::Gredy2) ||
	   g_ZtLicense.CheckUser(eZtUB::ProtectDebug) ||
	   g_ZtLicense.CheckUser(eZtUB::mu4you) ||
	   g_ZtLicense.CheckUser(eZtUB::Escalate) ||
	   g_ZtLicense.CheckUser(eZtUB::Artem) || 
	   g_ZtLicense.CheckUser(eZtUB::Artem2) ||
	   g_ZtLicense.CheckUser(eZtUB::eternalmu) ||
	   g_ZtLicense.CheckUser(eZtUB::SILVER1) ||
	   g_ZtLicense.CheckUser(eZtUB::SILVER2) ||
	   g_ZtLicense.CheckUser(eZtUB::SILVER_Local) ||
	   g_ZtLicense.CheckUser(eZtUB::NSGames) ||
	   g_ZtLicense.GetCustom())
	{
		this->Read(gDirPath.GetNewPath("ZtData\\GuildBank.ini"));
	}
}

void CGuildBank::Read(char* filename)
{
	this->m_iEnable = GetPrivateProfileInt("ZtTeam", "Enable", 0, filename);
	this->m_iGuildBankMap = GetPrivateProfileInt("ZtTeam", "GuildBankMap", 0, filename);
	this->m_iGuildBankX = GetPrivateProfileInt("ZtTeam", "GuildBankX", 0, filename);
	this->m_iGuildBankY = GetPrivateProfileInt("ZtTeam", "GuildBankY", 0, filename);
}

void CGuildBank::GDGetGuildWarehouseList(int aIndex)
{
	if(OBJMAX_RANGE(aIndex) == 0)
	{
		return;
	}

	if(strlen(gObj[aIndex].AccountID) < 1)
	{
		return;
	}

	if(strlen(gObj[aIndex].GuildName) < 1)
	{
		GCServerMsgStringSend("You need to be in a Guild before open GuildWarehouse!",aIndex, 0x01);
		gObj[aIndex].m_ReqWarehouseOpen = false;
		gObj[aIndex].m_IfState.use = 0;
		gObj[aIndex].m_IfState.state = 0;
		return;
	}

	if(gObj[aIndex].GuildNumber <= 0)
	{
		GCServerMsgStringSend("You need to be in a Guild before open GuildWarehouse!",aIndex, 0x01);
		gObj[aIndex].m_ReqWarehouseOpen = false;
		gObj[aIndex].m_IfState.use = 0;
		gObj[aIndex].m_IfState.state = 0;
		return;
	}

	if(gObj[aIndex].lpGuild->WareOpen == 1)
	{
		GCServerMsgStringSend("Some other character is using this GuildWarehouse!",aIndex, 0x01);
		gObj[aIndex].m_ReqWarehouseOpen = false;
		gObj[aIndex].m_IfState.use = 0;
		gObj[aIndex].m_IfState.state = 0;
		return;
	}

	gObj[aIndex].m_bGuildBank = true;

	gObj[aIndex].lpGuild->WareOpen = 1;

	/* Guild Bank Fix */
	this->ClearWarehouse(aIndex);

	SDHP_GETGUILDWAREHOUSEDB pMsg;

	pMsg.h.c = 0xC1;
	pMsg.h.headcode = Protocol_GSSend_GetGuildWarehouseList;
	pMsg.h.size = sizeof(SDHP_GETGUILDWAREHOUSEDB);
	pMsg.aIndex = aIndex;
	pMsg.Number = gObj[aIndex].WarehouseNumber;

	//memcpy(pMsg.G_Name, gObj[aIndex].GuildName, sizeof(pMsg.G_Name));
	memcpy(pMsg.G_Name, gObj[aIndex].lpGuild->Name, sizeof(pMsg.G_Name));
	memcpy(pMsg.AccountID, gObj[aIndex].AccountID, sizeof(pMsg.AccountID));

	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}

void CGuildBank::GDDelGuildWarehouseList(int aIndex)
{
	if(OBJMAX_RANGE(aIndex) == 0)
	{
		return;
	}

	if(strlen(gObj[aIndex].AccountID) < 1)
	{
		return;
	}

	if(strlen(gObj[aIndex].GuildName) < 1)
	{
		GCServerMsgStringSend("You need to be in a Guild before Del GuildWarehouse!",aIndex, 0x01);
		gObj[aIndex].m_ReqWarehouseOpen = false;
		gObj[aIndex].m_IfState.use = 0;
		gObj[aIndex].m_IfState.state = 0;
		return;
	}

	if(gObj[aIndex].GuildNumber <= 0)
	{
		GCServerMsgStringSend("You need to be in a Guild before Del GuildWarehouse!",aIndex, 0x01);
		gObj[aIndex].m_ReqWarehouseOpen = false;
		gObj[aIndex].m_IfState.use = 0;
		gObj[aIndex].m_IfState.state = 0;
		return;
	}

	SDHP_GETGUILDWAREHOUSEDB pMsg;

	pMsg.h.c = 0xC1;
	pMsg.h.headcode = Protocol_GSSend_DelGuildWarehouseList;
	pMsg.h.size = sizeof(SDHP_GETGUILDWAREHOUSEDB);
	pMsg.aIndex = aIndex;

	memcpy(pMsg.G_Name, gObj[aIndex].GuildName, sizeof(pMsg.G_Name));
	memcpy(pMsg.AccountID, gObj[aIndex].AccountID, sizeof(pMsg.AccountID));

	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}

void CGuildBank::GDSetGuildWarehouseList(int aIndex)
{
	if(OBJMAX_RANGE(aIndex) == 0)
	{
		return;
	}

	SDHP_GETGUILDWAREHOUSEDB_SAVE pMsg;

	if(strlen(gObj[aIndex].AccountID) < 1)
	{
		return;
	}

	if(strlen(gObj[aIndex].GuildName) < 1)	///NoGuild
	{
		gObj[aIndex].m_ReqWarehouseOpen = false;
		gObj[aIndex].m_IfState.use = 0;
		gObj[aIndex].m_IfState.state = 0;
		return;
	}

	if(gObj[aIndex].GuildNumber <= 0)
	{
		gObj[aIndex].m_ReqWarehouseOpen = false;
		gObj[aIndex].m_IfState.use = 0;
		gObj[aIndex].m_IfState.state = 0;
		return;
	}

	gObj[aIndex].lpGuild->WareOpen = 0;

	if(gObj[aIndex].WarehouseSave == 0)
	{
		LogAddTD("[%s][%s] WareHouse Save Fail : WarehouseSave = 0", gObj[aIndex].AccountID, gObj[aIndex].Name);
		return;
	}
	
	if(gObj[aIndex].LoadWareHouseInfo == false)
	{
		LogAddTD("[%s][%s] WareHouse Save Fail : Not Open", gObj[aIndex].AccountID, gObj[aIndex].Name);
		return;
	}

	//gObj[aIndex].m_bGuildBank = false;

	//gObj[aIndex].lpGuild->WareOpen = 0;

	memcpy(pMsg.AccountID, gObj[aIndex].AccountID, sizeof(pMsg.AccountID));
	//memcpy(pMsg.G_Name, gObj[aIndex].GuildName, sizeof(pMsg.G_Name));
	memcpy(pMsg.G_Name, gObj[aIndex].lpGuild->Name, sizeof(pMsg.G_Name));
	
	pMsg.aIndex = aIndex;
	pMsg.h.c = 0xC2;
	pMsg.h.headcode = Protocol_GSSend_SetGuildWarehouseList;
	pMsg.h.sizeH = HIBYTE(sizeof(pMsg));
	pMsg.h.sizeL = LOBYTE(sizeof(pMsg));
	pMsg.Money = gObj[aIndex].WarehouseMoney;
	pMsg.pw = gObj[aIndex].WarehousePW;
	pMsg.DbVersion = 3;
	pMsg.Number	= gObj[aIndex].WarehouseNumber;

	memset(pMsg.dbItems,0xFF,sizeof(pMsg.dbItems));
	ItemByteConvert16(pMsg.dbItems, gObj[aIndex].pWarehouse, WAREHOUSE_SIZE);

	cDBSMng.Send((PCHAR)&pMsg, sizeof(pMsg));

	gObjSavePetItemInfo(aIndex, 1);
	gObjWarehouseTextSave(&gObj[aIndex]);
}

bool CGuildBank::WarehousePassword(int aIndex)
{
	if(!this->m_iEnable)
	{
		return true;
	}

	if(OBJMAX_RANGE(aIndex) == 0)
	{
		return false;
	}

	if(strlen(gObj[aIndex].GuildName) < 1)	///NoGuild
	{
		return true;
	}

	if(gObj[aIndex].GuildNumber <= 0)
	{
		return true;
	}

	if(gObj[aIndex].GuildStatus == GUILD_MASTER)
	{
		return true;
	}

	return false;
}

void CGuildBank::CGOpenGuildWarehouse(PMSG_GUILD_BANK* lpMsg, int aIndex)
{
	if(!this->m_iEnable)
	{
		return;
	}

	if(OBJMAX_RANGE(aIndex) == 0)
	{
		return;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(!PacketCheckTime(lpObj))
	{
		return;
	}

	if(gObj[aIndex].CloseType != -1)
	{
		return;
	}

	if(!gObjIsConnectedGP(aIndex))
	{
		LogAddTD("[ANTI-HACK][NPC Talk] Couldn't talk.. (%s)(%s)", gObj[aIndex].AccountID, gObj[aIndex].Name);
		return;
	}

	if ( lpObj->m_IfState.use > 0 )
	{
		return;
	}

	if ( ::gObjFixInventoryPointer(aIndex) == false )
	{
		LogAdd("[Fix Inv.Ptr] False Location - %s, %d", __FILE__, __LINE__);
	}

	#if(CUSTOM_VALUE_MENU)
	if(g_ZtUser.GCSendValueMenu(aIndex, 2))
	{
		return;
	}
	#endif

	lpObj->TargetShopNumber = 100;
	lpObj->m_IfState.use = 1;
	//lpObj->m_IfState.type = 3;
	lpObj->m_ShopTime = 0;

	if(gObj[aIndex].m_ReqWarehouseOpen != false)
	{
		return;
	}
		
	gObj[aIndex].m_ReqWarehouseOpen = true;

	lpObj->m_IfState.type = 6;
	lpObj->m_IfState.state = 0;

	gObj[aIndex].WarehouseTickCount = GetTickCount();
	gObj[aIndex].WarehouseCount = 0;

#if(CUSTOM_MULTIWAREHOUSE)
	lpObj->WareChange = false;
	lpObj->WarehouseNumber = 0;
	WarehouseNumberSend(lpObj->m_Index);

	gObj[aIndex].m_bGuildBank = false;
	this->GDGetGuildWarehouseList(aIndex);

#else
	GDGetWarehouseListOLD(aIndex, gObj[aIndex].AccountID);
#endif

	
}

void CGuildBank::ClearWarehouse(int aIndex)
{
	if(OBJMAX_RANGE(aIndex) == 0)
	{
		return;
	}
	LPOBJ lpObj = &gObj[aIndex];
	/* Guild Bank Fix */

	lpObj->WarehouseMoney = 0;

	if(lpObj->Type == OBJ_USER)
	{
		for(int i=0;i<WAREHOUSE_SIZE;i++)
		{
			lpObj->pWarehouse[i].Clear();
		}
	}

}

#endif
