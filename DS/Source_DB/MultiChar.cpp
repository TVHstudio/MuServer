#include "stdafx.h"
#include "MainFrm.h"
#include "MultiChar.h"


/*
#include "TMemory.h"
#include "Debugger.h"
#include "Protocol.h"
#include "Import.h"
#include "User.h"
#include "Connection.h"
#include "UserDefine.h"
*/
#if(ENABLE_MULTI_CHAR)

CMultiChar g_MultiChar;

CMultiChar::CMultiChar()
{

}

CMultiChar::~CMultiChar()
{

}

bool CMultiChar::Connect()
{
	bool Result = this->m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass);

	if(!Result)
	{
		MsgBox("CMultiChar DB Connect Fail");
	}

	return Result;
}

void CMultiChar::Load()
{
	
}

void CMultiChar::GDCharacterListRecv(SDHP_GETCHARLIST_MULTICHAR* lpMsg, int index)
{
	BYTE send[2048];

	SDHP_CHARLISTCOUNT pMsg;
	memset(&pMsg, 0, sizeof(pMsg));
	pMsg.h.set((LPBYTE)&pMsg, 0x01, 0);

	#if(FIX_MULTI_CHAR)
	pMsg.DbNumber = lpMsg->Page;
	#else
	pMsg.DbNumber = 3;
	#endif	

	int size = sizeof(pMsg);

	pMsg.Number = lpMsg->index;

	memcpy(pMsg.AccountId,lpMsg->account,sizeof(pMsg.AccountId));

	pMsg.AccountId[10] = 0;

	char szAccountCharacter[32];
	memset(&szAccountCharacter, 0, sizeof(szAccountCharacter));

	if(lpMsg->Page == 1)
	{
		sprintf(szAccountCharacter, "AccountCharacter");
	}
	else
	{
		sprintf(szAccountCharacter, "AccountCharacter%d", lpMsg->Page);
	}

	if(this->m_DBQuery.ExecQuery("SELECT Id FROM %s WHERE Id='%s'", szAccountCharacter, lpMsg->account) == 0 || this->m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		this->m_DBQuery.Clear();

		this->m_DBQuery.ExecQuery("INSERT INTO %s (Id) VALUES ('%s')",szAccountCharacter, lpMsg->account);
		this->m_DBQuery.Clear();
	}
	else
	{
		this->m_DBQuery.Clear();
	}

	char CharacterName[5][11];

	memset(CharacterName,0,sizeof(CharacterName));

	this->m_DBQuery.ExecQuery("SELECT * FROM %s WHERE Id='%s'",szAccountCharacter, lpMsg->account);

	this->m_DBQuery.Fetch();

	pMsg.MoveCnt = (BYTE)this->m_DBQuery.GetInt("MoveCnt");

	pMsg.GenerableClass = 0;

	this->m_DBQuery.GetStr("GameID1",CharacterName[0]);

	this->m_DBQuery.GetStr("GameID2",CharacterName[1]);

	this->m_DBQuery.GetStr("GameID3",CharacterName[2]);

	this->m_DBQuery.GetStr("GameID4",CharacterName[3]);

	this->m_DBQuery.GetStr("GameID5",CharacterName[4]);

	this->m_DBQuery.Clear();

	pMsg.Count = 0;

	SDHP_CHARLIST info;

	for(int n=0;n < 5;n++)
	{
		if(CharacterName[n][0] == 0)
		{
			continue;
		}

		if(this->m_DBQuery.ExecQuery("SELECT cLevel,Class,Inventory,CtlCode FROM Character WHERE AccountID='%s' AND Name='%s'",lpMsg->account,CharacterName[n]) == 0 || this->m_DBQuery.Fetch() == SQL_NO_DATA)
		{
			this->m_DBQuery.Clear();
		}
		else
		{
			info.Index = n;

			info.DbVersion = 3;

			memcpy(info.Name,CharacterName[n],sizeof(info.Name));

			info.Level = (WORD)this->m_DBQuery.GetInt("cLevel");

			info.Class = (BYTE)this->m_DBQuery.GetInt("Class");

			BYTE Inventory[MAX_DBINVENTORY];
			//BYTE Inventory[192];

			this->m_DBQuery.ReadBlob("Inventory",Inventory);

			info.CtlCode = (BYTE)this->m_DBQuery.GetInt("CtlCode");

			this->m_DBQuery.Clear();

			if((info.CtlCode&0x80) == FALSE)
			{
				if(info.Level >= 150)
				{
					if(info.Level >= 220)
					{
						if(pMsg.GenerableClass < 2)
						{
							pMsg.GenerableClass = 2;
						}
					}
					else if(pMsg.GenerableClass < 2)
					{
						pMsg.GenerableClass = 1;
					}
				}
			}

			memset(info.dbInventory,0xFF,sizeof(info.dbInventory));
			
			for(int j = 0; j < MAX_EQUIPMENT; j++)
			{
				memcpy(&info.dbInventory[4 * j], &Inventory[16 * j], 2);
				info.dbInventory[4 * j + 2] = Inventory[16 * j + 7];
				info.dbInventory[4 * j + 3] = Inventory[16 * j + 9];
			}

			if(this->m_DBQuery.ExecQuery("SELECT G_Status FROM GuildMember WHERE Name='%s'",CharacterName[n]) == 0 || this->m_DBQuery.Fetch() == SQL_NO_DATA)
			{
				this->m_DBQuery.Clear();

				info.btGuildStatus = 0xFF;
			}
			else
			{
				info.btGuildStatus = (BYTE)this->m_DBQuery.GetInt("G_Status");

				this->m_DBQuery.Clear();
			}

			memcpy(&send[size],&info,sizeof(info));
			size += sizeof(info);

			pMsg.Count++;
		}
	}

	pMsg.h.sizeH = SET_NUMBERH(size);
	pMsg.h.sizeL = SET_NUMBERL(size);

	memcpy(send,&pMsg,sizeof(pMsg));

	//gSocketManager.DataSend(index,send,size);

	wsjServer.DataSend(index, (char*)send, size);
}


void CMultiChar::GDCharacterCreateRecv(SDHP_CREATECHAR* lpMsg,int index)
{
/*
	SDHP_CREATECHARRESULT pMsg;

	char szAccount[11];

	char szName[11];

	pMsg.h.set(0xA1,sizeof(pMsg));

	pMsg.Number = lpMsg->Number;

	memcpy(szAccount,lpMsg->AccountId,sizeof(szAccount));

	memcpy(szName,lpMsg->Name,sizeof(szName));

	szAccount[10] = 0;

	szName[10] = 0;

	memcpy(pMsg.AccountId,szAccount,sizeof(pMsg.AccountId));

	memcpy(pMsg.Name,szName,sizeof(pMsg.Name));

	if(CheckTextSyntax(szName,sizeof(szName)) == 0)
	{
		pMsg.Result = 0;
	}
	else
	{
		pMsg.Result = 1;
	}

	pMsg.Pos = 0;

	pMsg.ClassSkin = lpMsg->ClassSkin;

	memset(pMsg.Equipment,0xFF,sizeof(pMsg.Equipment));

	pMsg.Level = 1;

	char szAccountCharacter[32];

	if(lpMsg->Page == 1)
	{
		sprintf(szAccountCharacter, "AccountCharacter");
	}
	else
	{
		sprintf(szAccountCharacter, "AccountCharacter%d", lpMsg->Page);
	}

	char CharacterName[5][11] = {0};

	if(pMsg.Result == 0 || this->m_DBQuery.ExecQuery("SELECT * FROM %s WHERE Id='%s'",szAccountCharacter, szAccount) == 0 || this->m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		this->m_DBQuery.Close();

		pMsg.Result = 0;
	}
	else
	{
		this->m_DBQuery.GetAsString("GameID1",CharacterName[0],sizeof(CharacterName[0]));
		this->m_DBQuery.GetAsString("GameID2",CharacterName[1],sizeof(CharacterName[1]));
		this->m_DBQuery.GetAsString("GameID3",CharacterName[2],sizeof(CharacterName[2]));
		this->m_DBQuery.GetAsString("GameID4",CharacterName[3],sizeof(CharacterName[3]));
		this->m_DBQuery.GetAsString("GameID5",CharacterName[4],sizeof(CharacterName[4]));
		this->m_DBQuery.Close();

		if(GetCharacterSlot(CharacterName,"",&pMsg.Pos) == 0)
		{
			pMsg.Result = 2;
		}
		else
		{
			char szWZ_CreateCharacter[32];

			if(lpMsg->Page == 1)
			{
				sprintf(szWZ_CreateCharacter, "WZ_CreateCharacter");
			}
			else
			{
				sprintf(szWZ_CreateCharacter, "WZ_CreateCharacter%d", lpMsg->Page);
			}

			if(this->m_DBQuery.ExecQuery("EXEC %s '%s','%s','%d'",szWZ_CreateCharacter, szAccount,szName,lpMsg->ClassSkin) == 0 || this->m_DBQuery.Fetch() == SQL_NO_DATA)
			{
				this->m_DBQuery.Close();

				pMsg.Result = 0;
			}
			else
			{
				pMsg.Result = this->m_DBQuery.GetResult(0);

				this->m_DBQuery.Close();
			}

			if(pMsg.Result == 1)
			{
				this->m_DBQuery.ExecQuery("UPDATE %s SET GameID%d='%s' WHERE Id='%s'",szAccountCharacter,(pMsg.Pos+1),szName,szAccount);
				
				this->m_DBQuery.Close();
			}
		}
	}

	gSocketManager.DataSend(index,(BYTE*)&pMsg,pMsg.h.size);
	*/
}

void CMultiChar::GDCharacterDeleteRecv(SDHP_CHARDELETE* lpMsg, int index)
{
	/*

	SDHP_CHARDELETERESULT pMsg;

	pMsg.h.set(0xA2,sizeof(pMsg));

	pMsg.Number = lpMsg->Number;

	char szAccount[11] = { 0 };

	char szName[11] = { 0 };

	memcpy(szAccount,lpMsg->AccountID,sizeof(szAccount));

	memcpy(szName,lpMsg->Name,sizeof(szName));

	szAccount[10] = 0;

	szName[10] = 0;

	memcpy(pMsg.AccountID,szAccount,sizeof(pMsg.AccountID));

	if(CheckTextSyntax(szName,sizeof(szName)) == 0)
	{
		pMsg.Result = 0;
	}
	else
	{
		pMsg.Result = 1;
	}

	char szAccountCharacter[32];

	if(lpMsg->Page == 1)
	{
		sprintf(szAccountCharacter, "AccountCharacter");
	}
	else
	{
		sprintf(szAccountCharacter, "AccountCharacter%d", lpMsg->Page);
	}

	if(pMsg.Result == 0 || this->m_DBQuery.ExecQuery("DELETE FROM Character WHERE AccountID='%s' AND Name='%s'", szAccount, szName) == 0)
	{
		this->m_DBQuery.Close();

		pMsg.Result = 0;
	}
	else
	{
		this->m_DBQuery.Close();

		char CharacterName[5][11] = {0};

		if(this->m_DBQuery.ExecQuery("SELECT * FROM %s WHERE Id='%s'", szAccountCharacter, szAccount) == 0 || this->m_DBQuery.Fetch() == SQL_NO_DATA)
		{
			this->m_DBQuery.Close();

			pMsg.Result = 1;
		}
		else
		{
			this->m_DBQuery.GetAsString("GameID1",CharacterName[0],sizeof(CharacterName[0]));
			this->m_DBQuery.GetAsString("GameID2",CharacterName[1],sizeof(CharacterName[1]));
			this->m_DBQuery.GetAsString("GameID3",CharacterName[2],sizeof(CharacterName[2]));
			this->m_DBQuery.GetAsString("GameID4",CharacterName[3],sizeof(CharacterName[3]));
			this->m_DBQuery.GetAsString("GameID5",CharacterName[4],sizeof(CharacterName[4]));
			this->m_DBQuery.Close();

			BYTE slot;

			if(GetCharacterSlot(CharacterName,szName,&slot) != 0)
			{
				this->m_DBQuery.ExecQuery("UPDATE %s SET GameID%d=NULL WHERE Id='%s'", szAccountCharacter, (slot+1), szAccount);
				this->m_DBQuery.Close();
			}
		}
	}

	gSocketManager.DataSend(index,(BYTE*)&pMsg,pMsg.h.size);

	*/
}

#endif