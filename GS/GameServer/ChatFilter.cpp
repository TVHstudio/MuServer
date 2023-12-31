#include "StdAfx.h"
#include "ChatFilter.h"
#include "..\\include\\ReadScript.h"
#include "logproc.h"
#include "GameMain.h"
#include "ZtLicense.h"
#include "Configs.h"

#if(CUSTOM_CHATFILTER)

CChatFilter g_ChatFilter;

CChatFilter::CChatFilter()
{
	this->m_Active = false;
	this->m_Enable = false;
	this->m_Count = 0;
	this->m_iChatBanMin = 0;
	this->m_FilterInfo.clear();
}

CChatFilter::~CChatFilter()
{
}

void CChatFilter::Load()
{
	this->m_Active = false;

	if(g_ZtLicense.CheckUser(eZtUB::Gredy) || g_ZtLicense.CheckUser(eZtUB::GredyLocal) || g_ZtLicense.CheckUser(eZtUB::Gredy2) ||
		g_ZtLicense.CheckUser(eZtUB::SILVER1) || g_ZtLicense.CheckUser(eZtUB::SILVER2) || g_ZtLicense.CheckUser(eZtUB::SILVER_Local) ||
		g_ZtLicense.CheckUser(eZtUB::Artem) || g_ZtLicense.CheckUser(eZtUB::Artem2) || g_ZtLicense.CheckUser(eZtUB::mu4you) ||
		g_ZtLicense.CheckUser(eZtUB::NSGames) || g_ZtLicense.GetCustom())
	{
		this->m_Active = true;
	}

	if(!this->m_Active)
	{
		return;
	}

	this->m_Count = 0;
	this->m_FilterInfo.clear();
	this->Read(gDirPath.GetNewPath("ZtData\\ChatFilter.dat"));
}

void CChatFilter::Read(char* FileName)
{
	SMDToken Token;

	SMDFile = fopen(FileName, "r");

	if(!SMDFile)
	{
		MsgBox("%s file not found", FileName);
		return;
	}

	int iType = -1;

	while(true)
	{
		Token = GetToken();

		if(Token == END)
		{
			break;
		}

		if( Token != NUMBER )
		{
			continue;
		}

		iType = (int)TokenNumber;

		if(iType < 0 || iType > 1)
		{
			break;
		}

		while(1)
		{
			if(iType == 0)
			{
				Token = GetToken();

				if(strcmp("end", TokenString) == 0)
				{
					break;
				}

				this->m_Enable = TokenNumber;

				Token = GetToken();
				this->m_iChatBanMin = TokenNumber;

			}
			else if(iType == 1)
			{
				Token = GetToken();

				if(strcmp("end", TokenString) == 0)
				{
					break;
				}

				FILTER_INFO info;

				memset(&info, 0, sizeof(info));

				strcpy_s(info.label, TokenString);

				this->m_FilterInfo.push_back(info);
			}
		}
	}

	fclose(SMDFile);
	LogAdd("%s file load!", FileName);
}

void CChatFilter::CheckSyntax(int aIndex, char* text)
{
	if(!this->m_Enable)
	{
		return;
	}

	if(strcmp(text, ZtConfig.Command.CommandPost))
	{
		if(text[0] == '/')
		{
			return;
		}
	}

	for(int n = 0; n < this->m_FilterInfo.size(); n++)
	{
		char* temp = text;

		while(true)
		{
			temp = strstr(temp, this->m_FilterInfo[n].label);

			if(temp == 0)
			{
				break;
			}

			int len = strlen(this->m_FilterInfo[n].label);

			memset(temp, 0x2A, len);

			temp += len;

			if(len > 0)
			{
				LPOBJ lpUser = &gObj[aIndex];

				lpUser->BanPost = time(NULL) + ( this->m_iChatBanMin * 60 );
				lpUser->BanChat = time(NULL) + ( this->m_iChatBanMin * 60 );

				MsgOutput(aIndex, "[Chat Filter] ban %d min", this->m_iChatBanMin);

				return;
			}
		}
	}
}

#endif