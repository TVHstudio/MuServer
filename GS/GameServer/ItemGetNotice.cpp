#include "StdAfx.h"
#include "..\\include\ReadScript.h"
#include "GameMain.h"
#include "ItemGetNotice.h"
#include "logproc.h"
#include "ZtLicense.h"
#include "MapClass.h"
#include "Message.h"

CItemGetNotice g_ItemGetNotice;

CItemGetNotice::CItemGetNotice()
{
	this->Init();
}

CItemGetNotice::~CItemGetNotice()
{
}

void CItemGetNotice::Init()
{
	this->m_TextData.clear();
	this->m_ItemGetNotice.clear();
}

void CItemGetNotice::Read()
{
	this->Init();
	char* filename = gDirPath.GetNewPath("ZtData\\ItemGetNotice.txt");

	SMDFile = fopen(filename, "r");

	if (SMDFile == NULL)
	{
		MessageBox(NULL, "Error ZtData\\ItemGetNotice.txt", "Error", MB_OK);
		ExitProcess(1);
	}

	SMDToken Token;

	int iType = -1;
	int iMaxType = 1;
	while (true)
	{
		Token = GetToken();

		if (Token == END)
		{
			break;
		}

		iType = (int)TokenNumber;

		if (iType < 0 || iType > iMaxType)
		{
			break;
		}

		while (true)
		{
			if (iType == 0) //Data item Get
			{
				Token = GetToken();

				if (!strcmp("end", TokenString))
				{
					break;
				}

				DATA_ITEMGET infoItemGet;


				int Group = TokenNumber;
				Token = GetToken();
				int Type = TokenNumber;

				infoItemGet.IDItem = ITEMGET(Group, Type);
				Token = GetToken();
				infoItemGet.SkillCheck = TokenNumber;
				Token = GetToken();
				infoItemGet.LuckCheck = TokenNumber;
				Token = GetToken();
				infoItemGet.OptionCheck = TokenNumber;
				Token = GetToken();
				infoItemGet.ExcCheck = TokenNumber;
				Token = GetToken();
				infoItemGet.AncCheck = TokenNumber;
				Token = GetToken();
				infoItemGet.ColorMess = TokenNumber;
				Token = GetToken();
				infoItemGet.TextID = TokenNumber;
				this->m_ItemGetNotice.push_back(infoItemGet);
				//this->m_ItemGetNotice.insert(std::pair<int, DATA_ITEMGET>(infoItemGet.IDItem, infoItemGet));
			}
			else if (iType == 1) // DB Text
			{
				Token = GetToken();

				if (!strcmp("end", TokenString))
				{
					break;
				}
				DATA_TEXT infoText;
				infoText.Index = TokenNumber;
				Token = GetToken();
				strncpy_s(infoText.Message, TokenString, sizeof(infoText.Message));
				this->m_TextData.insert(std::pair<int, DATA_TEXT>(infoText.Index, infoText));
			}
		}
	}
	fclose(SMDFile);

	LogAdd("%s file load!", filename);
}

char* CItemGetNotice::GetMessage(int index) // OK
{
	std::map<int, DATA_TEXT>::iterator it = this->m_TextData.find(index);

	if (it == this->m_TextData.end())
	{
		char Error[256];
		wsprintf(Error, "Could not find message %d!", index);
		return Error;
	}
	else
	{
		return it->second.Message;
	}

}
DATA_ITEMGET* CItemGetNotice::CheckItemGetNotice(CMapItem* lpMapItem)
{
	for (std::vector<DATA_ITEMGET>::iterator it = this->m_ItemGetNotice.begin(); it != this->m_ItemGetNotice.end(); it++)
	{
		if (it->IDItem != lpMapItem->m_Type)
		{
			continue;
		}
		if (it->SkillCheck == 1 && lpMapItem->m_Option1 == 0 ) 
		{
			continue;
		}
		if (it->LuckCheck == 1 && lpMapItem->m_Option2 == 0)
		{
			continue;
		}
		if (it->OptionCheck == 1 && lpMapItem->m_Option3 == 0)
		{
			continue;
		}
		if (it->ExcCheck == 1 && !lpMapItem->IsExtItem())
		{
			continue;
		}
		if (it->AncCheck == 1 && !lpMapItem->IsSetItem())
		{
			continue;
		}
		return &(*it);
	}

	return 0;
}
void SetNoticeGobal(char* message, ...) // OK
{
	char buff[256] = { 0 };

	va_list arg;
	va_start(arg, message);
	vsprintf_s(buff, message, arg);
	va_end(arg);

	int size = strlen(buff);

	size = ((size > MAX_MESSAGE_SIZE) ? MAX_MESSAGE_SIZE : size);
	buff[size] = 0;

	AllSendServerMsg(buff);
}
int Color[4] = { 7,1,6,9};
void  CItemGetNotice::ItemGetNotice(CMapItem* lpMapItem, int aIndex)
{
	DATA_ITEMGET* GetInfoNoticeItem = this->CheckItemGetNotice(lpMapItem);
	if (!GetInfoNoticeItem) return;
	LPOBJ lpUser = &gObj[aIndex];
	//char MessText[256] = { 0 };
	//wsprintf(MessText, "+%d", it->Level);

	if (GetInfoNoticeItem->ColorMess < 4)
	{
		if (GetInfoNoticeItem->TextID > 3)
		{
			MessageSendAllEx(Color[GetInfoNoticeItem->ColorMess], "", this->GetMessage(GetInfoNoticeItem->TextID), lpUser->Name, lpMapItem->m_Level, lpMapItem->GetName());
		}
		else
		{
			MessageSendAllEx(Color[GetInfoNoticeItem->ColorMess], "", this->GetMessage(GetInfoNoticeItem->TextID), lpUser->Name, lpMapItem->GetName());
		}
	}
	else
	{

		if (GetInfoNoticeItem->TextID > 3)
		{
			SetNoticeGobal(this->GetMessage(GetInfoNoticeItem->TextID), lpUser->Name, lpMapItem->m_Level, lpMapItem->GetName());
		}
		else
		{
			SetNoticeGobal(this->GetMessage(GetInfoNoticeItem->TextID), lpUser->Name, lpMapItem->GetName());
		}
	}
}