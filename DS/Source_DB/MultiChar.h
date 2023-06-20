#pragma once



#if(ENABLE_MULTI_CHAR)

struct SDHP_GETCHARLIST_MULTICHAR
{
	PBMSG_HEAD h;	// C1:01
	char account[10];	// 3
	short index;	// E
	int Page;
};

/*
struct SDHP_CHARLISTCOUNT
{
	PWMSG_HEAD h;
	short Number;	// 4
	BYTE Count;	// 6
	int DbNumber;	// 8	//Page
	BYTE Magumsa;	// C
	char AccountId[11];	// D
	BYTE MoveCnt;	// 18
	BYTE ExpandedWarehouse;
};

struct SDHP_CHARLIST
{
	BYTE Index;	// 0
	char Name[10];	// 1
	WORD Level;	// C
	BYTE Class;	// E
	BYTE CtlCode;	// F
	BYTE dbInventory[48];	// 10
	BYTE DbVersion;	// 40
	BYTE btGuildStatus;	// 41
};
*/

// -------------------------
/*
struct SDHP_CREATECHAR
{
	PBMSG_HEAD h;	// C1:04
	int UserNumber;	// 4
	int DBNumber;	// 8
	short Number;	// C
	char AccountId[10];	// E
	char Name[10];	// 18
	BYTE ClassSkin;	// 22
	int Page;
};

struct SDHP_CREATECHARRESULT
{
	PBMSG_HEAD h;
	unsigned char Result;	// 3
	short Number;	// 4
	char AccountId[10];	// 6
	char Name[10];	// 10
	BYTE Pos;	// 1A
	BYTE ClassSkin;	// 1B
	BYTE Equipment[24];	// 1C
	WORD Level;	// 34
};

// ------------------------------

struct SDHP_CHARDELETE_MULTI
{
	PBMSG_HEAD h;	// C1:05
	short Number;	// 4
	char AccountID[10];	// 6
	char Name[10];	// 10
	BYTE Guild;	// [0:NoGuild] [1:Master] [2:Member] 1A
	char GuildName[8];	// 1B
	int Page;
};

struct SDHP_CHARDELETERESULT
{
	PBMSG_HEAD h;
	unsigned char Result;	// 3
	short Number;	// 4
	char AccountID[10];	// 6
};
*/

class CMultiChar
{
public:
		CMultiChar();
		~CMultiChar();

	void Load();
	bool Connect();

	void GDCharacterListRecv(SDHP_GETCHARLIST_MULTICHAR* lpMsg, int index);
	void GDCharacterCreateRecv(SDHP_CREATECHAR* lpMsg,int index);
	void GDCharacterDeleteRecv(SDHP_CHARDELETE* lpMsg, int index);

	CQuery	m_DBQuery;
};

extern CMultiChar g_MultiChar;

#endif

