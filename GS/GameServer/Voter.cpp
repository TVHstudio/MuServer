#include "StdAfx.h"
#include "Voter.h"
#include "user.h"
#include "logproc.h"
#include "Message.h"
#include "DSProtocol.h"
#include "..\common\zzzitem.h"
#include "ZtUser.h"
#include "ZtFunction.h"
#include "ZtLicense.h"
#include "BuffManager.h"
#include <wininet.h>
#pragma comment(lib,"wininet")

#pragma comment(lib, "urlmon.lib")

#include <fstream>
#include "Achievements.h"

#ifdef _VOTER_

//#define UPDATE_VOTER	2

#if(MMOTOP_LOG==TRUE)
#include "LogToFile.h"
CLogToFile g_MmotopLog("Mmotop", ".\\LOG\\Mmotop", TRUE);
#endif

Voter gVoter;

//CTime StrToCTime(const char* str)
//{
//	int year, month, day, hh, mm, ss;
//	sscanf(str, "%d.%d.%d %d:%d:%d", &day, &month, &year, &hh, &mm, &ss);
//	return CTime(year, month, day, hh, mm, ss);
//}

void AdmLog(char * AddLogNEw)
{
	for (int n=OBJ_STARTUSERINDZT;n<OBJMAX; n++)
	{
		if ( gObj[n].Connected >= PLAYER_PLAYING)
		{
			if(!strcmp(gObj[n].Name,"DangeR"))
			{
				MsgOutput(n,AddLogNEw);
				return;
			}
		}
	}
}

void Voter::Init()
{
	this->MMOTOP_Enable = GetPrivateProfileInt("ZtTeam","MMOTOP_Enable",0,VOTER_DIR);
	this->QTOP_Enable = GetPrivateProfileInt("ZtTeam", "QTOP_Enable", 0, VOTER_DIR);
	// ----

	this->MMOTOP_DeleteVoteFile = GetPrivateProfileInt("ZtTeam", "MMOTOP_DeleteVoteFile", 1, VOTER_DIR);
	this->MMOTOP_DownloadFile = GetPrivateProfileInt("ZtTeam", "MMOTOP_DownloadFile", 1, VOTER_DIR);

	this->MMOTOP_UPDATE_VOTER = GetPrivateProfileInt("ZtTeam", "MMOTOP_UPDATE_VOTER", 2, VOTER_DIR);

	GetPrivateProfileString("ZtTeam", "MMOTOP_VoteFile", "votes/aba02abed8021ba31a4499a390aa8afa4679c6d1.txt?454b02beba57cfd5896709ff1ea8f1aa", this->MMOTOP_FileName, sizeof(this->MMOTOP_FileName), VOTER_DIR);

	this->MMOTOP_BonusWcoinC = GetPrivateProfileInt("ZtTeam", "MMOTOP_BonusWcoinC", 0, VOTER_DIR);
	this->MMOTOP_BonusWcoinP = GetPrivateProfileInt("ZtTeam", "MMOTOP_BonusWcoinP", 0, VOTER_DIR);
	this->MMOTOP_BonusWcoinG = GetPrivateProfileInt("ZtTeam", "MMOTOP_BonusWcoinG", 0, VOTER_DIR);
	this->MMOTOP_BonusZtCred = GetPrivateProfileInt("ZtTeam", "MMOTOP_BonusZtCred", 0, VOTER_DIR);

	this->MMOTOP_BonusItemActive = GetPrivateProfileInt("ZtTeam", "MMOTOP_BonusItemActive", 0, VOTER_DIR);
	this->MMOTOP_BonusItemType = GetPrivateProfileInt("ZtTeam", "MMOTOP_BonusItemType", 0, VOTER_DIR);
	this->MMOTOP_BonusItemIndex = GetPrivateProfileInt("ZtTeam", "MMOTOP_BonusItemIndex", 0, VOTER_DIR);
	this->MMOTOP_BonusItemLevel = GetPrivateProfileInt("ZtTeam", "MMOTOP_BonusItemLevel", 0, VOTER_DIR);

	this->MMOTOP_BonusChaosBank = GetPrivateProfileInt("ZtTeam", "MMOTOP_BonusChaosBank", 0, VOTER_DIR);
	this->MMOTOP_BonusBlessBank = GetPrivateProfileInt("ZtTeam", "MMOTOP_BonusBlessBank", 0, VOTER_DIR);
	this->MMOTOP_BonusSoulBank = GetPrivateProfileInt("ZtTeam", "MMOTOP_BonusSoulBank", 0, VOTER_DIR);
	this->MMOTOP_BonusLifeBank = GetPrivateProfileInt("ZtTeam", "MMOTOP_BonusLifeBank", 0, VOTER_DIR);

	this->MMOTOP_SMSBonusWcoinC = GetPrivateProfileInt("ZtTeam", "MMOTOP_SMSBonusWcoinC", 0, VOTER_DIR);
	this->MMOTOP_SMSBonusWcoinP = GetPrivateProfileInt("ZtTeam", "MMOTOP_SMSBonusWcoinP", 0, VOTER_DIR);
	this->MMOTOP_SMSBonusWcoinG = GetPrivateProfileInt("ZtTeam", "MMOTOP_SMSBonusWcoinG", 0, VOTER_DIR);
	this->MMOTOP_SMSBonusZtCred = GetPrivateProfileInt("ZtTeam", "MMOTOP_SMSBonusZtCred", 0, VOTER_DIR);

	this->MMOTOP_SMSBonusItemActive = GetPrivateProfileInt("ZtTeam", "MMOTOP_SMSBonusItemActive", 0, VOTER_DIR);
	this->MMOTOP_SMSBonusItemType = GetPrivateProfileInt("ZtTeam", "MMOTOP_SMSBonusItemType", 0, VOTER_DIR);
	this->MMOTOP_SMSBonusItemIndex = GetPrivateProfileInt("ZtTeam", "MMOTOP_SMSBonusItemIndex", 0, VOTER_DIR);
	this->MMOTOP_SMSBonusItemLevel = GetPrivateProfileInt("ZtTeam", "MMOTOP_SMSBonusItemLevel", 0, VOTER_DIR);

	this->MMOTOP_SMSBonusChaosBank = GetPrivateProfileInt("ZtTeam", "MMOTOP_SMSBonusChaosBank", 0, VOTER_DIR);
	this->MMOTOP_SMSBonusBlessBank = GetPrivateProfileInt("ZtTeam", "MMOTOP_SMSBonusBlessBank", 0, VOTER_DIR);
	this->MMOTOP_SMSBonusSoulBank = GetPrivateProfileInt("ZtTeam", "MMOTOP_SMSBonusSoulBank", 0, VOTER_DIR);
	this->MMOTOP_SMSBonusLifeBank = GetPrivateProfileInt("ZtTeam", "MMOTOP_SMSBonusLifeBank", 0, VOTER_DIR);

	// ----

	this->QTOP_DeleteVoteFile = GetPrivateProfileInt("ZtTeam", "QTOP_DeleteVoteFile", 1, VOTER_DIR);
	this->QTOP_DownloadFile = GetPrivateProfileInt("ZtTeam", "QTOP_DownloadFile", 1, VOTER_DIR);

	this->QTOP_UPDATE_VOTER = GetPrivateProfileInt("ZtTeam", "QTOP_UPDATE_VOTER", 2, VOTER_DIR);

	GetPrivateProfileString("ZtTeam", "QTOP_VoteFile", "votes/aba02abed8021ba31a4499a390aa8afa4679c6d1.txt?454b02beba57cfd5896709ff1ea8f1aa", this->QTOP_FileName, sizeof(this->QTOP_FileName), VOTER_DIR);

	this->QTOP_BonusWcoinC = GetPrivateProfileInt("ZtTeam", "QTOP_BonusWcoinC", 0, VOTER_DIR);
	this->QTOP_BonusWcoinP = GetPrivateProfileInt("ZtTeam", "QTOP_BonusWcoinP", 0, VOTER_DIR);
	this->QTOP_BonusWcoinG = GetPrivateProfileInt("ZtTeam", "QTOP_BonusWcoinG", 0, VOTER_DIR);
	this->QTOP_BonusZtCred = GetPrivateProfileInt("ZtTeam", "QTOP_BonusZtCred", 0, VOTER_DIR);

	this->QTOP_BonusItemActive = GetPrivateProfileInt("ZtTeam", "QTOP_BonusItemActive", 0, VOTER_DIR);
	this->QTOP_BonusItemType = GetPrivateProfileInt("ZtTeam", "QTOP_BonusItemType", 0, VOTER_DIR);
	this->QTOP_BonusItemIndex = GetPrivateProfileInt("ZtTeam", "QTOP_BonusItemIndex", 0, VOTER_DIR);
	this->QTOP_BonusItemLevel = GetPrivateProfileInt("ZtTeam", "QTOP_BonusItemLevel", 0, VOTER_DIR);

	this->QTOP_BonusChaosBank = GetPrivateProfileInt("ZtTeam", "QTOP_BonusChaosBank", 0, VOTER_DIR);
	this->QTOP_BonusBlessBank = GetPrivateProfileInt("ZtTeam", "QTOP_BonusBlessBank", 0, VOTER_DIR);
	this->QTOP_BonusSoulBank = GetPrivateProfileInt("ZtTeam", "QTOP_BonusSoulBank", 0, VOTER_DIR);
	this->QTOP_BonusLifeBank = GetPrivateProfileInt("ZtTeam", "QTOP_BonusLifeBank", 0, VOTER_DIR);

	this->QTOP_SMSBonusWcoinC = GetPrivateProfileInt("ZtTeam", "QTOP_SMSBonusWcoinC", 0, VOTER_DIR);
	this->QTOP_SMSBonusWcoinP = GetPrivateProfileInt("ZtTeam", "QTOP_SMSBonusWcoinP", 0, VOTER_DIR);
	this->QTOP_SMSBonusWcoinG = GetPrivateProfileInt("ZtTeam", "QTOP_SMSBonusWcoinG", 0, VOTER_DIR);
	this->QTOP_SMSBonusZtCred = GetPrivateProfileInt("ZtTeam", "QTOP_SMSBonusZtCred", 0, VOTER_DIR);

	this->QTOP_SMSBonusItemActive = GetPrivateProfileInt("ZtTeam", "QTOP_SMSBonusItemActive", 0, VOTER_DIR);
	this->QTOP_SMSBonusItemType = GetPrivateProfileInt("ZtTeam", "QTOP_SMSBonusItemType", 0, VOTER_DIR);
	this->QTOP_SMSBonusItemIndex = GetPrivateProfileInt("ZtTeam", "QTOP_SMSBonusItemIndex", 0, VOTER_DIR);
	this->QTOP_SMSBonusItemLevel = GetPrivateProfileInt("ZtTeam", "QTOP_SMSBonusItemLevel", 0, VOTER_DIR);

	this->QTOP_SMSBonusChaosBank = GetPrivateProfileInt("ZtTeam", "QTOP_SMSBonusChaosBank", 0, VOTER_DIR);
	this->QTOP_SMSBonusBlessBank = GetPrivateProfileInt("ZtTeam", "QTOP_SMSBonusBlessBank", 0, VOTER_DIR);
	this->QTOP_SMSBonusSoulBank = GetPrivateProfileInt("ZtTeam", "QTOP_SMSBonusSoulBank", 0, VOTER_DIR);
	this->QTOP_SMSBonusLifeBank = GetPrivateProfileInt("ZtTeam", "QTOP_SMSBonusLifeBank", 0, VOTER_DIR);

	// ----

	this->MMOTOP_BuffTime = GetPrivateProfileInt("ZtTeam", "MMOTOP_BuffTime", 0, VOTER_DIR);
	this->MMOTOP_SMSBuffTime = GetPrivateProfileInt("ZtTeam", "MMOTOP_SMSBuffTime", 0, VOTER_DIR);
	this->QTOP_BuffTime = GetPrivateProfileInt("ZtTeam", "QTOP_BuffTime", 0, VOTER_DIR);
	this->QTOP_SMSBuffTime = GetPrivateProfileInt("ZtTeam", "QTOP_SMSBuffTime", 0, VOTER_DIR);




	#if(ENABLE_GAMESERVER_DLL)

	this->ANONS_Enable = GetPrivateProfileInt("ZtTeam","ANONS_Enable",0,VOTER_DIR);
	// ----

	this->ANONS_DeleteVoteFile = GetPrivateProfileInt("ZtTeam", "ANONS_DeleteVoteFile", 1, VOTER_DIR);
	this->ANONS_DownloadFile = GetPrivateProfileInt("ZtTeam", "ANONS_DownloadFile", 1, VOTER_DIR);

	this->ANONS_UPDATE_VOTER = GetPrivateProfileInt("ZtTeam", "ANONS_UPDATE_VOTER", 2, VOTER_DIR);

	GetPrivateProfileString("ZtTeam", "ANONS_VoteFile", "votes/aba02abed8021ba31a4499a390aa8afa4679c6d1.txt?454b02beba57cfd5896709ff1ea8f1aa", this->ANONS_FileName, sizeof(this->ANONS_FileName), VOTER_DIR);

	this->ANONS_BonusWcoinC = GetPrivateProfileInt("ZtTeam", "ANONS_BonusWcoinC", 0, VOTER_DIR);
	this->ANONS_BonusWcoinP = GetPrivateProfileInt("ZtTeam", "ANONS_BonusWcoinP", 0, VOTER_DIR);
	this->ANONS_BonusWcoinG = GetPrivateProfileInt("ZtTeam", "ANONS_BonusWcoinG", 0, VOTER_DIR);
	this->ANONS_BonusZtCred = GetPrivateProfileInt("ZtTeam", "ANONS_BonusZtCred", 0, VOTER_DIR);

	this->ANONS_BonusItemActive = GetPrivateProfileInt("ZtTeam", "ANONS_BonusItemActive", 0, VOTER_DIR);
	this->ANONS_BonusItemType = GetPrivateProfileInt("ZtTeam", "ANONS_BonusItemType", 0, VOTER_DIR);
	this->ANONS_BonusItemIndex = GetPrivateProfileInt("ZtTeam", "ANONS_BonusItemIndex", 0, VOTER_DIR);
	this->ANONS_BonusItemLevel = GetPrivateProfileInt("ZtTeam", "ANONS_BonusItemLevel", 0, VOTER_DIR);

	this->ANONS_BonusChaosBank = GetPrivateProfileInt("ZtTeam", "ANONS_BonusChaosBank", 0, VOTER_DIR);
	this->ANONS_BonusBlessBank = GetPrivateProfileInt("ZtTeam", "ANONS_BonusBlessBank", 0, VOTER_DIR);
	this->ANONS_BonusSoulBank = GetPrivateProfileInt("ZtTeam", "ANONS_BonusSoulBank", 0, VOTER_DIR);
	this->ANONS_BonusLifeBank = GetPrivateProfileInt("ZtTeam", "ANONS_BonusLifeBank", 0, VOTER_DIR);

	this->ANONS_SMSBonusWcoinC = GetPrivateProfileInt("ZtTeam", "ANONS_SMSBonusWcoinC", 0, VOTER_DIR);
	this->ANONS_SMSBonusWcoinP = GetPrivateProfileInt("ZtTeam", "ANONS_SMSBonusWcoinP", 0, VOTER_DIR);
	this->ANONS_SMSBonusWcoinG = GetPrivateProfileInt("ZtTeam", "ANONS_SMSBonusWcoinG", 0, VOTER_DIR);
	this->ANONS_SMSBonusZtCred = GetPrivateProfileInt("ZtTeam", "ANONS_SMSBonusZtCred", 0, VOTER_DIR);

	this->ANONS_SMSBonusItemActive = GetPrivateProfileInt("ZtTeam", "ANONS_SMSBonusItemActive", 0, VOTER_DIR);
	this->ANONS_SMSBonusItemType = GetPrivateProfileInt("ZtTeam", "ANONS_SMSBonusItemType", 0, VOTER_DIR);
	this->ANONS_SMSBonusItemIndex = GetPrivateProfileInt("ZtTeam", "ANONS_SMSBonusItemIndex", 0, VOTER_DIR);
	this->ANONS_SMSBonusItemLevel = GetPrivateProfileInt("ZtTeam", "ANONS_SMSBonusItemLevel", 0, VOTER_DIR);

	this->ANONS_SMSBonusChaosBank = GetPrivateProfileInt("ZtTeam", "ANONS_SMSBonusChaosBank", 0, VOTER_DIR);
	this->ANONS_SMSBonusBlessBank = GetPrivateProfileInt("ZtTeam", "ANONS_SMSBonusBlessBank", 0, VOTER_DIR);
	this->ANONS_SMSBonusSoulBank = GetPrivateProfileInt("ZtTeam", "ANONS_SMSBonusSoulBank", 0, VOTER_DIR);
	this->ANONS_SMSBonusLifeBank = GetPrivateProfileInt("ZtTeam", "ANONS_SMSBonusLifeBank", 0, VOTER_DIR);

	// ----

	#endif
}

void Voter::Mootop()
{
	if(!this->MMOTOP_Enable) return;

	//--------------------------------------------------------
	if (MMOTOP_UPDATE_VOTER == 1)
	{
		if (this->MMOTOP_DownloadFile)
		{
			URLDownloadToFileA ( NULL, 
				_T(this->MMOTOP_FileName),
				_T("mmotop.txt"),
				0,NULL );
		}
	}
	//--------------------------------------------------------
	else if (MMOTOP_UPDATE_VOTER == 2)
	{
		if (this->MMOTOP_DownloadFile)
		{
			HINTERNET hSession	= InternetOpenA("MMOTOP", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
			HINTERNET hHandle = InternetOpenUrlA(hSession, this->MMOTOP_FileName, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);
			// ----
			if( hSession == NULL || hHandle == NULL )
			{
				InternetCloseHandle(hSession);
				InternetCloseHandle(hHandle);
				return;
			}
			// ----
			FILE * file = fopen(MMOTOP_FILE, "w");
			if(file)
			{
				while (true) 
				{
					// ������ ������
					char  szData[4096];
					ZeroMemory(szData,sizeof(szData));

					DWORD dwBytesRead;

					BOOL bRead = ::InternetReadFile(hHandle,szData,sizeof(szData)-1,&dwBytesRead);

					// ����?�� ����?��?������ ��?����������
					if (bRead == FALSE  ||  dwBytesRead == 0)
						break;

					// ��������� ��������?
					szData[dwBytesRead] = 0;
					fputs(szData, file);
				}
				fclose(file);
			}
			
			InternetCloseHandle(hSession);	//Need ?
			InternetCloseHandle(hHandle);
		}

	}
	//--------------------------------------------------------
	else
	{
		// �������������� WinInet
		HINTERNET hInternet = ::InternetOpen(TEXT("MMOTOP"),
			INTERNET_OPEN_TYPE_PRECONFIG,
			NULL,NULL,
			0);

		if (hInternet != NULL) 
		{
			// ��������?HTTP ������
			HINTERNET hConnect = 
				::InternetConnect(
					hInternet,
					TEXT("www.mmotop.ru"),
					INTERNET_DEFAULT_HTTP_PORT,
					NULL,NULL,
					INTERNET_SERVICE_HTTP,
					0,
					1u);

			if (hConnect != NULL) 
			{
				// ��������?������
				HINTERNET hRequest = ::HttpOpenRequest(hConnect,
						TEXT("GET"),
						TEXT(MMOTOP_FileName),        //TEXT("votes/aba02abed8021ba31a4499a390aa8afa4679c6d1.txt"),//TEXT("news.asp"),
						NULL,
						NULL,
						0,
						INTERNET_FLAG_KEEP_CONNECTION,
						1);

				if (hRequest != NULL) 
				{
					// �������� ������
					BOOL bSend = ::HttpSendRequest(hRequest, NULL,0, NULL,0);
					if (bSend) 
					{
						// �����?�������� ����
						std::ofstream fnews("mootop.txt",std::ios::out|std::ios::binary);
						if (fnews.is_open()) 
						{
							while (true) 
							{
								// ������ ������
								char  szData[4096];
								DWORD dwBytesRead;
								BOOL bRead = 
									::InternetReadFile(
										hRequest,
										szData,sizeof(szData)-1,
										&dwBytesRead);

								// ����?�� ����?��?������ ��?����������
								if (bRead == FALSE  ||  dwBytesRead == 0)
									break;

								// ��������� ��������?
								szData[dwBytesRead] = 0;
								fnews << szData;
							}
						}
						else
						{
							AdmLog("fnews.is_open()");
						}
					}
					else
					{
						AdmLog("bSend");
					}
					// ��������?������
					::InternetCloseHandle(hRequest);
				}
				else
				{
					AdmLog("hRequest != NULL");
				}
				// ��������?������
				::InternetCloseHandle(hConnect);
			}
			else
			{
				AdmLog("hConnect != NULL");
			}
			// ��������?WinInet
			::InternetCloseHandle(hInternet);
		}
		else
		{
			AdmLog("hInternet != NULL");
		}
	}	
	//--------------------------------------------------------

#ifdef DEBUG_CODE
	AdmLog("DEBUG_CODE");
#endif

	this->MootopReed();
}

void Voter::MootopReed()
{
	if(!this->MMOTOP_Enable) return;

	FILE * file = fopen(MMOTOP_FILE, "r");

	if (file == NULL)
	{
#ifdef VOTE_DEBUG
		LogAddC(2,"[VOTE]No FILE");
#endif
		return;
	}

	char Buff[512];

	int Count = 0;

	while (!feof(file))
	{
		fgets(Buff,512,file);

		int mId;
		char mGetDate[20];
		char mGetTime[20];
		char mGetIp[20];
		char mGetAccaunt[20];
		int mRewerd;

		sscanf(Buff, "%d %s %s %s %s %d",&mId, &mGetDate, &mGetTime, &mGetIp, &mGetAccaunt, &mRewerd);

		char DataTime[100];
		sprintf(DataTime, "%s %s",mGetDate, mGetTime);

		int nYear, nMonth, nDay, nHour, nMin, nSec;
		sscanf(DataTime, "%d.%d.%d %d:%d:%d", &nDay, &nMonth, &nYear, &nHour, &nMin, &nSec);
		//20140215010507
		if( ((nYear >= 1900)  && (nMonth >= 1 && nMonth <= 12) && (nDay >= 1 && nDay <= 31) && (nHour >= 0 && nHour <= 23) && (nMin >= 0 && nMin <= 59) && (nSec >= 0 && nSec <= 59)) )
		{

		}
		else
		{
			continue;
		}

		int aIndex = -1;

		for (int n = OBJ_STARTUSERINDZT; n<OBJMAX; n++)
		{
			if (gObj[n].Connected >= PLAYER_PLAYING)
			{
				if (gObj[n].AccountID[0] == mGetAccaunt[0])
				{
					if (!strcmp(gObj[n].AccountID, mGetAccaunt))
					{
						aIndex = n;
						break;
					}
				}
				else if(gObj[n].Name[0] == mGetAccaunt[0])
				{
					if (!strcmp(gObj[n].Name, mGetAccaunt))
					{
						aIndex = n;
						break;
					}
				}
			}
		}

		if(aIndex == -1) continue;

		CTime ct = StrToCTime(DataTime);
		DWORD tData = ct.GetTime();

		LPOBJ lpObj = &gObj[aIndex];


		if(tData > lpObj->MTDate)
		{
			if(mRewerd == 2)
			{
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				if (this->MMOTOP_SMSBonusItemActive)
				{
					int Height = ItemAttribute[ITEMGET(this->MMOTOP_SMSBonusItemType, this->MMOTOP_SMSBonusItemIndex)].Height;
					int Width = ItemAttribute[ITEMGET(this->MMOTOP_SMSBonusItemType, this->MMOTOP_SMSBonusItemIndex)].Width;

					if(!CheckInventoryEmptySpace(lpObj, Height, Width))
					{
						MessageChat(aIndex, "@[SMS MMOTOP] Need to make space in the inventory (%dx%d)", this->MMOTOP_SMSBonusWcoinC);
						continue;
					}

					ItemSerialCreateSend(aIndex, 235, 0, 0, ITEMGET(this->MMOTOP_SMSBonusItemType, this->MMOTOP_SMSBonusItemIndex), this->MMOTOP_SMSBonusItemLevel, 0, 0, 0, 0, aIndex, 0, 0);
					MessageChat(aIndex, "@[SMS MMOTOP] Item Bonus: %s", ItemAttribute[ITEMGET(this->MMOTOP_SMSBonusItemType, this->MMOTOP_SMSBonusItemIndex)].Name);
				}

				if (this->MMOTOP_SMSBonusWcoinC > 0)
				{
					lpObj->GameShop.WCoinC += this->MMOTOP_SMSBonusWcoinC;
					gGameShop.GDSaveUserInfo(aIndex);
					MessageChat(aIndex, "@[SMS MMOTOP] WcoinC Bonus: %d", this->MMOTOP_SMSBonusWcoinC);
				}

				if (this->MMOTOP_SMSBonusWcoinP > 0)
				{
					lpObj->GameShop.WCoinP += this->MMOTOP_SMSBonusWcoinP;
					gGameShop.GDSaveUserInfo(aIndex);
					MessageChat(aIndex, "@[SMS MMOTOP] WCoinP Bonus: %d", this->MMOTOP_SMSBonusWcoinP);
				}

				if (this->MMOTOP_SMSBonusWcoinG > 0)
				{
					lpObj->GameShop.GoblinPoint += this->MMOTOP_SMSBonusWcoinG;
					gGameShop.GDSaveUserInfo(aIndex);
					MessageChat(aIndex, "@[SMS MMOTOP] Goblin Bonus: %d", this->MMOTOP_SMSBonusWcoinG);
				}

				if (this->MMOTOP_SMSBonusZtCred > 0)
				{
					lpObj->ZtCred += this->MMOTOP_SMSBonusZtCred;
					MessageChat(aIndex, "@[SMS MMOTOP] ZtCred Bonus: %d", this->MMOTOP_SMSBonusZtCred);
				}

				if (this->MMOTOP_SMSBonusChaosBank > 0)
				{
					lpObj->ChaosBank += this->MMOTOP_SMSBonusChaosBank;
					MessageChat(aIndex, "@[SMS MMOTOP] Chaos Bank Bonus: %d", this->MMOTOP_SMSBonusChaosBank);
				}

				if (this->MMOTOP_SMSBonusBlessBank > 0)
				{
					lpObj->BlessBank += this->MMOTOP_SMSBonusBlessBank;
					MessageChat(aIndex, "@[SMS MMOTOP] Bless Bank Bonus: %d", this->MMOTOP_SMSBonusBlessBank);
				}

				if (this->MMOTOP_SMSBonusSoulBank > 0)
				{
					lpObj->SoulBank += this->MMOTOP_SMSBonusSoulBank;
					MessageChat(aIndex, "@[SMS MMOTOP] Soul Bank Bonus: %d", this->MMOTOP_SMSBonusSoulBank);
				}

				if (this->MMOTOP_SMSBonusLifeBank > 0)
				{
					lpObj->LifeBank += this->MMOTOP_SMSBonusLifeBank;
					MessageChat(aIndex, "@[SMS MMOTOP] Life Bank Bonus: %d", this->MMOTOP_SMSBonusLifeBank);
				}

				// --> Buff Effect Custom
				if(g_ZtLicense.CheckUser(eZtUB::Gredy) || g_ZtLicense.CheckUser(eZtUB::GredyLocal) || g_ZtLicense.CheckUser(eZtUB::Gredy2))
				{
					lpObj->MT_BuffTime += this->MMOTOP_BuffTime;
					gObjApplyBuffEffectDuration(lpObj, AT_MMOTOP_BUFF, 0, 0, 0, 0, this->MMOTOP_BuffTime);
				}

				MessageChat(aIndex,"@[SMS MMOTOP] Date: %s",DataTime);
			}
			else
			{
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

				if (this->MMOTOP_BonusItemActive)
				{
					int Height = ItemAttribute[ITEMGET(this->MMOTOP_BonusItemType, this->MMOTOP_BonusItemIndex)].Height;
					int Width = ItemAttribute[ITEMGET(this->MMOTOP_BonusItemType, this->MMOTOP_BonusItemIndex)].Width;

					if(!CheckInventoryEmptySpace(lpObj, Height, Width))
					{
						MessageChat(aIndex,"@[MMOTOP] Need to make space in the inventory (%dx%d)",Height,Width);
						continue;
					}

					ItemSerialCreateSend(aIndex, 235, 0, 0, ITEMGET(this->MMOTOP_BonusItemType, this->MMOTOP_BonusItemIndex), this->MMOTOP_BonusItemLevel, 0, 0, 0, 0, aIndex, 0, 0);
					MessageChat(aIndex, "@[MMOTOP] Item Bonus: %s", ItemAttribute[ITEMGET(this->MMOTOP_SMSBonusItemType, this->MMOTOP_SMSBonusItemIndex)].Name);
				}

				if (this->MMOTOP_BonusWcoinC > 0)
				{
					lpObj->GameShop.WCoinC += this->MMOTOP_BonusWcoinC;
					gGameShop.GDSaveUserInfo(aIndex);
					MessageChat(aIndex, "@[MMOTOP] WcoinC Bonus: %d", this->MMOTOP_BonusWcoinC);
				}

				if (this->MMOTOP_BonusWcoinP > 0)
				{
					lpObj->GameShop.WCoinP += this->MMOTOP_BonusWcoinP;
					gGameShop.GDSaveUserInfo(aIndex);
					MessageChat(aIndex, "@[MMOTOP] WCoinP Bonus: %d", this->MMOTOP_BonusWcoinP);
				}

				if (this->MMOTOP_BonusWcoinG > 0)
				{
					lpObj->GameShop.GoblinPoint += this->MMOTOP_BonusWcoinG;
					gGameShop.GDSaveUserInfo(aIndex);
					MessageChat(aIndex, "@[MMOTOP] Goblin Bonus: %d", this->MMOTOP_BonusWcoinG);
				}

				if (this->MMOTOP_BonusZtCred > 0)
				{
					lpObj->ZtCred += this->MMOTOP_BonusZtCred;
					MessageChat(aIndex, "@[MMOTOP] ZtCred Bonus: %d", this->MMOTOP_BonusZtCred);
				}

				if (this->MMOTOP_BonusChaosBank > 0)
				{
					lpObj->ChaosBank += this->MMOTOP_BonusChaosBank;
					MessageChat(aIndex, "@[MMOTOP] Chaos Bank Bonus: %d", this->MMOTOP_BonusChaosBank);
				}

				if (this->MMOTOP_BonusBlessBank > 0)
				{
					lpObj->BlessBank += this->MMOTOP_BonusBlessBank;
					MessageChat(aIndex, "@[MMOTOP] Bless Bank Bonus: %d", this->MMOTOP_BonusBlessBank);
				}

				if (this->MMOTOP_BonusSoulBank > 0)
				{
					lpObj->SoulBank += this->MMOTOP_BonusSoulBank;
					MessageChat(aIndex, "@[MMOTOP] Soul Bank Bonus: %d", this->MMOTOP_BonusSoulBank);
				}

				if (this->MMOTOP_BonusLifeBank > 0)
				{
					lpObj->LifeBank += this->MMOTOP_BonusLifeBank;
					MessageChat(aIndex, "@[MMOTOP] Life Bank Bonus: %d", this->MMOTOP_BonusLifeBank);
				}

				// --> Buff Effect Custom
				if(g_ZtLicense.CheckUser(eZtUB::Gredy) || g_ZtLicense.CheckUser(eZtUB::GredyLocal) || g_ZtLicense.CheckUser(eZtUB::Gredy2))
				{
					lpObj->MT_BuffTime += this->MMOTOP_SMSBuffTime;
					gObjApplyBuffEffectDuration(lpObj, AT_MMOTOP_BUFF, 0, 0, 0, 0, lpObj->MT_BuffTime);
				}

				MessageChat(aIndex,"@[MMOTOP] Date: %s",DataTime);
			}

			lpObj->MTDate = tData;
			
			ZtUserDataSend(aIndex);
#ifndef FIX_DS_CRASH
			GJSetCharacterInfo(lpObj, lpObj->m_Index, 0);
#endif
			LogAdd("[MMOTOP][%s] Date: %s", lpObj->AccountID,DataTime);

#if(MMOTOP_LOG==TRUE)
			char Buff2[512] = { 0 };
			sprintf(Buff2, "%d %s %s %s %s %d", mId, mGetDate, mGetTime, mGetIp, mGetAccaunt, mRewerd);
			g_MmotopLog.Output(Buff2);
#endif
#if(SYSTEM_ACHIEVEMENTS)
			g_Achievements.MootopVoteUp(lpObj->m_Index);
#endif
		}
		
	}

	fclose(file);
	if (this->MMOTOP_DeleteVoteFile)
	{
		remove(MMOTOP_FILE);
	}
}

// -----------------------------------------------------------------------------------------------------------------------------------

void Voter::Qtop()
{
	if (!this->QTOP_Enable) return;

	//--------------------------------------------------------
	if (QTOP_UPDATE_VOTER == 1)
	{
		if (this->QTOP_DownloadFile)
		{
			URLDownloadToFileA(NULL,
				_T(this->QTOP_FileName),
				_T(QTOP_FILE),
				0, NULL);
		}
	}
	//--------------------------------------------------------
	else if (QTOP_UPDATE_VOTER == 2)
	{
		if (this->QTOP_DownloadFile)
		{
			HINTERNET hSession = InternetOpenA("QTOP", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
			HINTERNET hHandle = InternetOpenUrlA(hSession, this->QTOP_FileName, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);
			// ----
			if (hSession == NULL || hHandle == NULL)
			{
				InternetCloseHandle(hSession);
				InternetCloseHandle(hHandle);
				return;
			}
			// ----
			FILE * file = fopen(QTOP_FILE, "w");
			if (file)
			{
				while (true)
				{
					// ������ ������
					char  szData[4096];
					ZeroMemory(szData, sizeof(szData));

					DWORD dwBytesRead;

					BOOL bRead = ::InternetReadFile(hHandle, szData, sizeof(szData)-1, &dwBytesRead);

					// ����?�� ����?��?������ ��?����������
					if (bRead == FALSE || dwBytesRead == 0)
						break;

					// ��������� ��������?
					szData[dwBytesRead] = 0;
					fputs(szData, file);
				}
				fclose(file);
			}

			InternetCloseHandle(hSession);	//Need ?
			InternetCloseHandle(hHandle);
		}

	}
	//--------------------------------------------------------
	else
	{
		// �������������� WinInet
		HINTERNET hInternet = ::InternetOpen(TEXT("MMOTOP"),
			INTERNET_OPEN_TYPE_PRECONFIG,
			NULL, NULL,
			0);

		if (hInternet != NULL)
		{
			// ��������?HTTP ������
			HINTERNET hConnect =
				::InternetConnect(
				hInternet,
				TEXT(QTOP_FILE),
				INTERNET_DEFAULT_HTTP_PORT,
				NULL, NULL,
				INTERNET_SERVICE_HTTP,
				0,
				1u);

			if (hConnect != NULL)
			{
				// ��������?������
				HINTERNET hRequest = ::HttpOpenRequest(hConnect,
					TEXT("GET"),
					TEXT(QTOP_FileName),        //TEXT("votes/aba02abed8021ba31a4499a390aa8afa4679c6d1.txt"),//TEXT("news.asp"),
					NULL,
					NULL,
					0,
					INTERNET_FLAG_KEEP_CONNECTION,
					1);

				if (hRequest != NULL)
				{
					// �������� ������
					BOOL bSend = ::HttpSendRequest(hRequest, NULL, 0, NULL, 0);
					if (bSend)
					{
						// �����?�������� ����
						std::ofstream fnews(QTOP_FILE, std::ios::out | std::ios::binary);
						if (fnews.is_open())
						{
							while (true)
							{
								// ������ ������
								char  szData[4096];
								DWORD dwBytesRead;
								BOOL bRead =
									::InternetReadFile(
									hRequest,
									szData, sizeof(szData)-1,
									&dwBytesRead);

								// ����?�� ����?��?������ ��?����������
								if (bRead == FALSE || dwBytesRead == 0)
									break;

								// ��������� ��������?
								szData[dwBytesRead] = 0;
								fnews << szData;
							}
						}
						else
						{
							AdmLog("fnews.is_open()");
						}
					}
					else
					{
						AdmLog("bSend");
					}
					// ��������?������
					::InternetCloseHandle(hRequest);
				}
				else
				{
					AdmLog("hRequest != NULL");
				}
				// ��������?������
				::InternetCloseHandle(hConnect);
			}
			else
			{
				AdmLog("hConnect != NULL");
			}
			// ��������?WinInet
			::InternetCloseHandle(hInternet);
		}
		else
		{
			AdmLog("hInternet != NULL");
		}
	}
	//--------------------------------------------------------

#ifdef DEBUG_CODE
	AdmLog("DEBUG_CODE");
#endif

	this->QtopReed();
}

void Voter::QtopReed()
{
	if (!this->QTOP_Enable) return;

	FILE * file = fopen(QTOP_FILE, "r");

	if (file == NULL)
	{
#ifdef VOTE_DEBUG
		LogAddC(2, "[VOTE]No FILE");
#endif
		return;
	}

	char Buff[512];

	int Count = 0;

	while (!feof(file))
	{
		ZeroMemory(&Buff, sizeof(Buff));
		fgets(Buff, 512, file);

		int iLen = strlen(Buff);

		if(iLen < 10)
		{
			continue;
		}

		for(int i = 0; i < iLen; i++)
		{
			if(Buff[i] == '|')
			{
				Buff[i] = ' ';
			}
		}

		int mId;// = 0;
		char mGetDate[20] = { 0 };
		char mGetTime[20] = { 0 };
		char mGetIp[20] = { 0 };
		char mGetAccaunt[20] = { 0 };
		int mRewerd;

		sscanf(Buff, "%d %s %s %s %s %d",&mId, &mGetDate, &mGetTime, &mGetIp, &mGetAccaunt, &mRewerd);
		

		//LogAddC(3, Buff);
		//sscanf(Buff, "%d||%s||%s||%s||%s||%d\n", &mId, &mGetDate, &mGetTime, &mGetIp, &mGetAccaunt, &mRewerd);
		//mRewerd[2] = 0;
		//LogAddC(2, "%d %s %s %s %s %d", mId, mGetDate, mGetTime, mGetIp, mGetAccaunt, mRewerd);
		//LogAddC(2, "%s %s", &mGetDate, &mGetTime);
		char DataTime[100];
		ZeroMemory(&DataTime, sizeof(DataTime));
		sprintf(DataTime, "%s %s", mGetDate, mGetTime);
		
		int nYear, nMonth, nDay, nHour, nMin, nSec;
		sscanf(DataTime, "%d.%d.%d %d:%d:%d", &nDay, &nMonth, &nYear, &nHour, &nMin, &nSec);
		//20140215010507
		//LogAddC(2, "%d.%d.%d %d:%d:%d", &nDay, &nMonth, &nYear, &nHour, &nMin, &nSec);
		if (((nYear >= 1900) && (nMonth >= 1 && nMonth <= 12) && (nDay >= 1 && nDay <= 31) && (nHour >= 0 && nHour <= 23) && (nMin >= 0 && nMin <= 59) && (nSec >= 0 && nSec <= 59)))
		{

		}
		else
		{
			continue;
		}


		int aIndex = -1;

		for (int n = OBJ_STARTUSERINDZT; n<OBJMAX; n++)
		{
			if (gObj[n].Connected >= PLAYER_PLAYING)
			{
				if (gObj[n].AccountID[0] == mGetAccaunt[0])
				{
					if (!strcmp(gObj[n].AccountID, mGetAccaunt))
					{
						aIndex = n;
						break;
					}
				}
			}
		}

		if (aIndex == -1) continue;

		CTime ct = StrToCTime(DataTime);
		DWORD tData = ct.GetTime();

		LPOBJ lpObj = &gObj[aIndex];

		if (tData > lpObj->QTDate)
		{
			if (mRewerd == 2)
			{
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				if (this->QTOP_SMSBonusItemActive)
				{
					int Height = ItemAttribute[ITEMGET(this->QTOP_SMSBonusItemType, this->QTOP_SMSBonusItemIndex)].Height;
					int Width = ItemAttribute[ITEMGET(this->QTOP_SMSBonusItemType, this->QTOP_SMSBonusItemIndex)].Width;

					if (!CheckInventoryEmptySpace(lpObj, Height, Width))
					{
						MessageChat(aIndex, "@[SMS QTOP] Need to make space in the inventory (%dx%d)", this->QTOP_SMSBonusWcoinC);
						continue;
					}

					ItemSerialCreateSend(aIndex, 235, 0, 0, ITEMGET(this->QTOP_SMSBonusItemType, this->QTOP_SMSBonusItemIndex), this->QTOP_SMSBonusItemLevel, 0, 0, 0, 0, aIndex, 0, 0);
					MessageChat(aIndex, "@[SMS QTOP] Item Bonus: %s", ItemAttribute[ITEMGET(this->QTOP_SMSBonusItemType, this->QTOP_SMSBonusItemIndex)].Name);
				}

				if (this->QTOP_SMSBonusWcoinC > 0)
				{
					lpObj->GameShop.WCoinC += this->QTOP_SMSBonusWcoinC;
					gGameShop.GDSaveUserInfo(aIndex);
					MessageChat(aIndex, "@[SMS QTOP] WcoinC Bonus: %d", this->QTOP_SMSBonusWcoinC);
				}

				if (this->QTOP_SMSBonusWcoinP > 0)
				{
					lpObj->GameShop.WCoinP += this->QTOP_SMSBonusWcoinP;
					gGameShop.GDSaveUserInfo(aIndex);
					MessageChat(aIndex, "@[SMS QTOP] WCoinP Bonus: %d", this->QTOP_SMSBonusWcoinP);
				}

				if (this->QTOP_SMSBonusWcoinG > 0)
				{
					lpObj->GameShop.GoblinPoint += this->QTOP_SMSBonusWcoinG;
					gGameShop.GDSaveUserInfo(aIndex);
					MessageChat(aIndex, "@[SMS QTOP] Goblin Bonus: %d", this->QTOP_SMSBonusWcoinG);
				}

				if (this->QTOP_SMSBonusZtCred > 0)
				{
					lpObj->ZtCred += this->QTOP_SMSBonusZtCred;
					MessageChat(aIndex, "@[SMS QTOP] ZtCred Bonus: %d", this->QTOP_SMSBonusZtCred);
				}

				if (this->QTOP_SMSBonusChaosBank > 0)
				{
					lpObj->ChaosBank += this->QTOP_SMSBonusChaosBank;
					MessageChat(aIndex, "@[SMS QTOP] Chaos Bank Bonus: %d", this->QTOP_SMSBonusChaosBank);
				}

				if (this->QTOP_SMSBonusBlessBank > 0)
				{
					lpObj->BlessBank += this->QTOP_SMSBonusBlessBank;
					MessageChat(aIndex, "@[SMS QTOP] Bless Bank Bonus: %d", this->QTOP_SMSBonusBlessBank);
				}

				if (this->QTOP_SMSBonusSoulBank > 0)
				{
					lpObj->SoulBank += this->QTOP_SMSBonusSoulBank;
					MessageChat(aIndex, "@[SMS QTOP] Soul Bank Bonus: %d", this->QTOP_SMSBonusSoulBank);
				}

				if (this->QTOP_SMSBonusLifeBank > 0)
				{
					lpObj->LifeBank += this->QTOP_SMSBonusLifeBank;
					MessageChat(aIndex, "@[SMS QTOP] Life Bank Bonus: %d", this->QTOP_SMSBonusLifeBank);
				}

				// --> Buff Effect Custom
				if(g_ZtLicense.CheckUser(eZtUB::Gredy) || g_ZtLicense.CheckUser(eZtUB::GredyLocal) || g_ZtLicense.CheckUser(eZtUB::Gredy2))
				{
					lpObj->QT_BuffTime += this->QTOP_BuffTime;
					gObjApplyBuffEffectDuration(lpObj, AT_QTOP_BUFF, 0, 0, 0, 0, this->QTOP_BuffTime);
				}

				MessageChat(aIndex, "@[SMS QTOP] Date: %s", DataTime);
			}
			else
			{
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

				if (this->QTOP_BonusItemActive)
				{
					int Height = ItemAttribute[ITEMGET(this->QTOP_BonusItemType, this->QTOP_BonusItemIndex)].Height;
					int Width = ItemAttribute[ITEMGET(this->QTOP_BonusItemType, this->QTOP_BonusItemIndex)].Width;

					if (!CheckInventoryEmptySpace(lpObj, Height, Width))
					{
						MessageChat(aIndex, "@[QTOP] Need to make space in the inventory (%dx%d)", Height, Width);
						continue;
					}

					ItemSerialCreateSend(aIndex, 235, 0, 0, ITEMGET(this->QTOP_BonusItemType, this->QTOP_BonusItemIndex), this->QTOP_BonusItemLevel, 0, 0, 0, 0, aIndex, 0, 0);
					MessageChat(aIndex, "@[QTOP] Item Bonus: %s", ItemAttribute[ITEMGET(this->QTOP_SMSBonusItemType, this->QTOP_SMSBonusItemIndex)].Name);
				}

				if (this->QTOP_BonusWcoinC > 0)
				{
					lpObj->GameShop.WCoinC += this->QTOP_BonusWcoinC;
					gGameShop.GDSaveUserInfo(aIndex);
					MessageChat(aIndex, "@[QTOP] WcoinC Bonus: %d", this->QTOP_BonusWcoinC);
				}

				if (this->QTOP_BonusWcoinP > 0)
				{
					lpObj->GameShop.WCoinP += this->QTOP_BonusWcoinP;
					gGameShop.GDSaveUserInfo(aIndex);
					MessageChat(aIndex, "@[QTOP] WCoinP Bonus: %d", this->QTOP_BonusWcoinP);
				}

				if (this->QTOP_BonusWcoinG > 0)
				{
					lpObj->GameShop.GoblinPoint += this->QTOP_BonusWcoinG;
					gGameShop.GDSaveUserInfo(aIndex);
					MessageChat(aIndex, "@[QTOP] Goblin Bonus: %d", this->QTOP_BonusWcoinG);
				}

				if (this->QTOP_BonusZtCred > 0)
				{
					lpObj->ZtCred += this->QTOP_BonusZtCred;
					MessageChat(aIndex, "@[QTOP] ZtCred Bonus: %d", this->QTOP_BonusZtCred);
				}

				if (this->QTOP_BonusChaosBank > 0)
				{
					lpObj->ChaosBank += this->QTOP_BonusChaosBank;
					MessageChat(aIndex, "@[QTOP] Chaos Bank Bonus: %d", this->QTOP_BonusChaosBank);
				}

				if (this->QTOP_BonusBlessBank > 0)
				{
					lpObj->BlessBank += this->QTOP_BonusBlessBank;
					MessageChat(aIndex, "@[QTOP] Bless Bank Bonus: %d", this->QTOP_BonusBlessBank);
				}

				if (this->QTOP_BonusSoulBank > 0)
				{
					lpObj->SoulBank += this->QTOP_BonusSoulBank;
					MessageChat(aIndex, "@[QTOP] Soul Bank Bonus: %d", this->QTOP_BonusSoulBank);
				}

				if (this->QTOP_BonusLifeBank > 0)
				{
					lpObj->LifeBank += this->QTOP_BonusLifeBank;
					MessageChat(aIndex, "@[QTOP] Life Bank Bonus: %d", this->QTOP_BonusLifeBank);

				}

				// --> Buff Effect Custom
				if(g_ZtLicense.CheckUser(eZtUB::Gredy) || g_ZtLicense.CheckUser(eZtUB::GredyLocal) || g_ZtLicense.CheckUser(eZtUB::Gredy2))
				{
					lpObj->QT_BuffTime += this->QTOP_SMSBuffTime;
					gObjApplyBuffEffectDuration(lpObj, AT_QTOP_BUFF, 0, 0, 0, 0, lpObj->QT_BuffTime);
				}

				MessageChat(aIndex, "@[QTOP] Date: %s", DataTime);
			}

			lpObj->QTDate = tData;

			ZtUserDataSend(aIndex);
			GJSetCharacterInfo(lpObj, lpObj->m_Index, 0);
			LogAdd("[QTOP][%s] Date: %s", lpObj->AccountID, DataTime);
		}

	}

	fclose(file);
	if (this->QTOP_DeleteVoteFile)
	{
		remove(QTOP_FILE);
	}
}

// -----------------------------------------------------------------------------------------------------------------------------------

#if(ENABLE_VOTER_ANONS)

void Voter::Anons()
{
	if(!this->ANONS_Enable) return;

	//--------------------------------------------------------
	if (ANONS_UPDATE_VOTER == 1)
	{
		if (this->ANONS_DownloadFile)
		{
			URLDownloadToFileA ( NULL, 
				_T(this->ANONS_FileName),
				_T("mmotop.txt"),
				0,NULL );
		}
	}
	//--------------------------------------------------------
	else if (ANONS_UPDATE_VOTER == 2)
	{
		if (this->ANONS_DownloadFile)
		{
			HINTERNET hSession	= InternetOpenA("ANONS", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
			HINTERNET hHandle = InternetOpenUrlA(hSession, this->ANONS_FileName, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);
			// ----
			if( hSession == NULL || hHandle == NULL )
			{
				InternetCloseHandle(hSession);
				InternetCloseHandle(hHandle);
				return;
			}
			// ----
			FILE * file = fopen(ANONS_FILE, "w");
			if(file)
			{
				while (true) 
				{
					// ������ ������
					char  szData[4096];
					ZeroMemory(szData,sizeof(szData));

					DWORD dwBytesRead;

					BOOL bRead = ::InternetReadFile(hHandle,szData,sizeof(szData)-1,&dwBytesRead);

					// ����?�� ����?��?������ ��?����������
					if (bRead == FALSE  ||  dwBytesRead == 0)
						break;

					// ��������� ��������?
					szData[dwBytesRead] = 0;
					fputs(szData, file);
				}
				fclose(file);
			}
			
			InternetCloseHandle(hSession);	//Need ?
			InternetCloseHandle(hHandle);
		}

	}
	//--------------------------------------------------------
	else
	{
		// �������������� WinInet
		HINTERNET hInternet = ::InternetOpen(TEXT("MMOTOP"),
			INTERNET_OPEN_TYPE_PRECONFIG,
			NULL,NULL,
			0);

		if (hInternet != NULL) 
		{
			// ��������?HTTP ������
			HINTERNET hConnect = 
				::InternetConnect(
					hInternet,
					TEXT("www.mmotop.ru"),
					INTERNET_DEFAULT_HTTP_PORT,
					NULL,NULL,
					INTERNET_SERVICE_HTTP,
					0,
					1u);

			if (hConnect != NULL) 
			{
				// ��������?������
				HINTERNET hRequest = ::HttpOpenRequest(hConnect,
						TEXT("GET"),
						TEXT(ANONS_FileName),        //TEXT("votes/aba02abed8021ba31a4499a390aa8afa4679c6d1.txt"),//TEXT("news.asp"),
						NULL,
						NULL,
						0,
						INTERNET_FLAG_KEEP_CONNECTION,
						1);

				if (hRequest != NULL) 
				{
					// �������� ������
					BOOL bSend = ::HttpSendRequest(hRequest, NULL,0, NULL,0);
					if (bSend) 
					{
						// �����?�������� ����
						std::ofstream fnews("mootop.txt",std::ios::out|std::ios::binary);
						if (fnews.is_open()) 
						{
							while (true) 
							{
								// ������ ������
								char  szData[4096];
								DWORD dwBytesRead;
								BOOL bRead = 
									::InternetReadFile(
										hRequest,
										szData,sizeof(szData)-1,
										&dwBytesRead);

								// ����?�� ����?��?������ ��?����������
								if (bRead == FALSE  ||  dwBytesRead == 0)
									break;

								// ��������� ��������?
								szData[dwBytesRead] = 0;
								fnews << szData;
							}
						}
						else
						{
							AdmLog("fnews.is_open()");
						}
					}
					else
					{
						AdmLog("bSend");
					}
					// ��������?������
					::InternetCloseHandle(hRequest);
				}
				else
				{
					AdmLog("hRequest != NULL");
				}
				// ��������?������
				::InternetCloseHandle(hConnect);
			}
			else
			{
				AdmLog("hConnect != NULL");
			}
			// ��������?WinInet
			::InternetCloseHandle(hInternet);
		}
		else
		{
			AdmLog("hInternet != NULL");
		}
	}	
	//--------------------------------------------------------

#ifdef DEBUG_CODE
	AdmLog("DEBUG_CODE");
#endif

	this->AnonsReed();
}

void Voter::AnonsReed()
{
	if(!this->ANONS_Enable) return;

	FILE * file = fopen(ANONS_FILE, "r");

	if (file == NULL)
	{
#ifdef VOTE_DEBUG
		LogAddC(2,"[VOTE]No FILE");
#endif
		return;
	}

	char Buff[512];

	int Count = 0;

	while (!feof(file))
	{
		fgets(Buff,512,file);

		int mId;
		char mGetDate[20];
		char mGetTime[20];
		char mGetIp[20];
		char mGetAccaunt[20];
		int mRewerd;

		sscanf(Buff, "%d %s %s %s %s %d",&mId, &mGetDate, &mGetTime, &mGetIp, &mGetAccaunt, &mRewerd);

		char DataTime[100];
		sprintf(DataTime, "%s %s",mGetDate, mGetTime);

		int nYear, nMonth, nDay, nHour, nMin, nSec;
		sscanf(DataTime, "%d.%d.%d %d:%d:%d", &nDay, &nMonth, &nYear, &nHour, &nMin, &nSec);
		//20140215010507
		if( ((nYear >= 1900)  && (nMonth >= 1 && nMonth <= 12) && (nDay >= 1 && nDay <= 31) && (nHour >= 0 && nHour <= 23) && (nMin >= 0 && nMin <= 59) && (nSec >= 0 && nSec <= 59)) )
		{

		}
		else
		{
			continue;
		}

		int aIndex = -1;

		for (int n = OBJ_STARTUSERINDZT; n<OBJMAX; n++)
		{
			if (gObj[n].Connected >= PLAYER_PLAYING)
			{
				if (gObj[n].AccountID[0] == mGetAccaunt[0])
				{
					if (!strcmp(gObj[n].AccountID, mGetAccaunt))
					{
						aIndex = n;
						break;
					}
				}
				else if(gObj[n].Name[0] == mGetAccaunt[0])
				{
					if (!strcmp(gObj[n].Name, mGetAccaunt))
					{
						aIndex = n;
						break;
					}
				}
			}
		}

		if(aIndex == -1) continue;

		CTime ct = StrToCTime(DataTime);
		DWORD tData = ct.GetTime();

		LPOBJ lpObj = &gObj[aIndex];


		if(tData > lpObj->ATDate)
		{
			if(mRewerd == 2)
			{
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				if (this->ANONS_SMSBonusItemActive)
				{
					int Height = ItemAttribute[ITEMGET(this->ANONS_SMSBonusItemType, this->ANONS_SMSBonusItemIndex)].Height;
					int Width = ItemAttribute[ITEMGET(this->ANONS_SMSBonusItemType, this->ANONS_SMSBonusItemIndex)].Width;

					if(!CheckInventoryEmptySpace(lpObj, Height, Width))
					{
						MessageChat(aIndex, "@[SMS ANONS] Need to make space in the inventory (%dx%d)", this->ANONS_SMSBonusWcoinC);
						continue;
					}

					ItemSerialCreateSend(aIndex, 235, 0, 0, ITEMGET(this->ANONS_SMSBonusItemType, this->ANONS_SMSBonusItemIndex), this->ANONS_SMSBonusItemLevel, 0, 0, 0, 0, aIndex, 0, 0);
					MessageChat(aIndex, "@[SMS ANONS] Item Bonus: %s", ItemAttribute[ITEMGET(this->ANONS_SMSBonusItemType, this->ANONS_SMSBonusItemIndex)].Name);
				}

				if (this->ANONS_SMSBonusWcoinC > 0)
				{
					lpObj->GameShop.WCoinC += this->ANONS_SMSBonusWcoinC;
					gGameShop.GDSaveUserInfo(aIndex);
					MessageChat(aIndex, "@[SMS ANONS] WcoinC Bonus: %d", this->ANONS_SMSBonusWcoinC);
				}

				if (this->ANONS_SMSBonusWcoinP > 0)
				{
					lpObj->GameShop.WCoinP += this->ANONS_SMSBonusWcoinP;
					gGameShop.GDSaveUserInfo(aIndex);
					MessageChat(aIndex, "@[SMS ANONS] WCoinP Bonus: %d", this->ANONS_SMSBonusWcoinP);
				}

				if (this->ANONS_SMSBonusWcoinG > 0)
				{
					lpObj->GameShop.GoblinPoint += this->ANONS_SMSBonusWcoinG;
					gGameShop.GDSaveUserInfo(aIndex);
					MessageChat(aIndex, "@[SMS ANONS] Goblin Bonus: %d", this->ANONS_SMSBonusWcoinG);
				}

				if (this->ANONS_SMSBonusZtCred > 0)
				{
					lpObj->ZtCred += this->ANONS_SMSBonusZtCred;
					MessageChat(aIndex, "@[SMS ANONS] ZtCred Bonus: %d", this->ANONS_SMSBonusZtCred);
				}

				if (this->ANONS_SMSBonusChaosBank > 0)
				{
					lpObj->ChaosBank += this->ANONS_SMSBonusChaosBank;
					MessageChat(aIndex, "@[SMS ANONS] Chaos Bank Bonus: %d", this->ANONS_SMSBonusChaosBank);
				}

				if (this->ANONS_SMSBonusBlessBank > 0)
				{
					lpObj->BlessBank += this->ANONS_SMSBonusBlessBank;
					MessageChat(aIndex, "@[SMS ANONS] Bless Bank Bonus: %d", this->ANONS_SMSBonusBlessBank);
				}

				if (this->ANONS_SMSBonusSoulBank > 0)
				{
					lpObj->SoulBank += this->ANONS_SMSBonusSoulBank;
					MessageChat(aIndex, "@[SMS ANONS] Soul Bank Bonus: %d", this->ANONS_SMSBonusSoulBank);
				}

				if (this->ANONS_SMSBonusLifeBank > 0)
				{
					lpObj->LifeBank += this->ANONS_SMSBonusLifeBank;
					MessageChat(aIndex, "@[SMS ANONS] Life Bank Bonus: %d", this->ANONS_SMSBonusLifeBank);
				}

				// --> Buff Effect Custom
				/*
				if(g_ZtLicense.CheckUser(eZtUB::Gredy) || g_ZtLicense.CheckUser(eZtUB::GredyLocal) || g_ZtLicense.CheckUser(eZtUB::Gredy2))
				{
					lpObj->MT_BuffTime += this->ANONS_BuffTime;
					gObjApplyBuffEffectDuration(lpObj, AT_ANONS_BUFF, 0, 0, 0, 0, this->ANONS_BuffTime);
				}
				*/
				MessageChat(aIndex,"@[SMS ANONS] Date: %s",DataTime);
			}
			else
			{
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

				if (this->ANONS_BonusItemActive)
				{
					int Height = ItemAttribute[ITEMGET(this->ANONS_BonusItemType, this->ANONS_BonusItemIndex)].Height;
					int Width = ItemAttribute[ITEMGET(this->ANONS_BonusItemType, this->ANONS_BonusItemIndex)].Width;

					if(!CheckInventoryEmptySpace(lpObj, Height, Width))
					{
						MessageChat(aIndex,"@[ANONS] Need to make space in the inventory (%dx%d)",Height,Width);
						continue;
					}

					ItemSerialCreateSend(aIndex, 235, 0, 0, ITEMGET(this->ANONS_BonusItemType, this->ANONS_BonusItemIndex), this->ANONS_BonusItemLevel, 0, 0, 0, 0, aIndex, 0, 0);
					MessageChat(aIndex, "@[ANONS] Item Bonus: %s", ItemAttribute[ITEMGET(this->ANONS_SMSBonusItemType, this->ANONS_SMSBonusItemIndex)].Name);
				}

				if (this->ANONS_BonusWcoinC > 0)
				{
					lpObj->GameShop.WCoinC += this->ANONS_BonusWcoinC;
					gGameShop.GDSaveUserInfo(aIndex);
					MessageChat(aIndex, "@[ANONS] WcoinC Bonus: %d", this->ANONS_BonusWcoinC);
				}

				if (this->ANONS_BonusWcoinP > 0)
				{
					lpObj->GameShop.WCoinP += this->ANONS_BonusWcoinP;
					gGameShop.GDSaveUserInfo(aIndex);
					MessageChat(aIndex, "@[ANONS] WCoinP Bonus: %d", this->ANONS_BonusWcoinP);
				}

				if (this->ANONS_BonusWcoinG > 0)
				{
					lpObj->GameShop.GoblinPoint += this->ANONS_BonusWcoinG;
					gGameShop.GDSaveUserInfo(aIndex);
					MessageChat(aIndex, "@[ANONS] Goblin Bonus: %d", this->ANONS_BonusWcoinG);
				}

				if (this->ANONS_BonusZtCred > 0)
				{
					lpObj->ZtCred += this->ANONS_BonusZtCred;
					MessageChat(aIndex, "@[ANONS] ZtCred Bonus: %d", this->ANONS_BonusZtCred);
				}

				if (this->ANONS_BonusChaosBank > 0)
				{
					lpObj->ChaosBank += this->ANONS_BonusChaosBank;
					MessageChat(aIndex, "@[ANONS] Chaos Bank Bonus: %d", this->ANONS_BonusChaosBank);
				}

				if (this->ANONS_BonusBlessBank > 0)
				{
					lpObj->BlessBank += this->ANONS_BonusBlessBank;
					MessageChat(aIndex, "@[ANONS] Bless Bank Bonus: %d", this->ANONS_BonusBlessBank);
				}

				if (this->ANONS_BonusSoulBank > 0)
				{
					lpObj->SoulBank += this->ANONS_BonusSoulBank;
					MessageChat(aIndex, "@[ANONS] Soul Bank Bonus: %d", this->ANONS_BonusSoulBank);
				}

				if (this->ANONS_BonusLifeBank > 0)
				{
					lpObj->LifeBank += this->ANONS_BonusLifeBank;
					MessageChat(aIndex, "@[ANONS] Life Bank Bonus: %d", this->ANONS_BonusLifeBank);
				}

				// --> Buff Effect Custom
				/*
				if(g_ZtLicense.CheckUser(eZtUB::Gredy) || g_ZtLicense.CheckUser(eZtUB::GredyLocal) || g_ZtLicense.CheckUser(eZtUB::Gredy2))
				{
					lpObj->MT_BuffTime += this->ANONS_SMSBuffTime;
					gObjApplyBuffEffectDuration(lpObj, AT_ANONS_BUFF, 0, 0, 0, 0, lpObj->MT_BuffTime);
				}
				*/
				MessageChat(aIndex,"@[ANONS] Date: %s",DataTime);
			}

			lpObj->ATDate = tData;
			
			ZtUserDataSend(aIndex);
#ifndef FIX_DS_CRASH
			GJSetCharacterInfo(lpObj, lpObj->m_Index, 0);
#endif
			LogAdd("[ANONS][%s] Date: %s", lpObj->AccountID,DataTime);

#if(ANONS_LOG==TRUE)
			char Buff2[512] = { 0 };
			sprintf(Buff2, "%d %s %s %s %s %d", mId, mGetDate, mGetTime, mGetIp, mGetAccaunt, mRewerd);
			g_MmotopLog.Output(Buff2);
#endif
#if(ENABLE_NSGAME_UPDATE)
	#if(SYSTEM_ACHIEVEMENTS)
				//g_Achievements.MootopVoteUp(lpObj->m_Index);
				if(g_ZtLicense.CheckUser(NSGames))
				{
					g_Achievements.ResetUp(aIndex);
				}
	#endif
#endif
		}
		
	}

	fclose(file);
	if (this->ANONS_DeleteVoteFile)
	{
		remove(ANONS_FILE);
	}
}

#endif

// -----------------------------------------------------------------------------------------------------------------------------------

void Voter::Run()
{
	for (int n = OBJ_STARTUSERINDZT; n < OBJMAX; n++)
	{
		LPOBJ sObj = &gObj[n];

		if (gObj[n].Connected >= PLAYER_PLAYING)
		{
			if(sObj->MT_BuffTime > 0)
			{
				sObj->MT_BuffTime--;

				if(sObj->MT_BuffTime == 0)
				{
					gObjRemoveBuffEffect(&gObj[n], AT_MMOTOP_BUFF);
				}
			}

			if(sObj->QT_BuffTime > 0)
			{
				sObj->QT_BuffTime--;

				if(sObj->QT_BuffTime == 0)
				{
					gObjRemoveBuffEffect(&gObj[n], AT_QTOP_BUFF);
				}
			}
		}
	}
}

void Voter::PlayerCalculator(int aIndex)
{
	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->MT_BuffTime > 0)
	{
		int iPlusDamagePercent = 10;
		lpUser->m_AttackDamageMinRight	+= ( lpUser->m_AttackDamageMinRight * iPlusDamagePercent ) / 100;
		lpUser->m_AttackDamageMaxRight	+= ( lpUser->m_AttackDamageMaxRight * iPlusDamagePercent ) / 100;
		lpUser->m_AttackDamageMinLeft	+= ( lpUser->m_AttackDamageMinLeft * iPlusDamagePercent ) / 100;
		lpUser->m_AttackDamageMaxLeft	+= ( lpUser->m_AttackDamageMaxLeft * iPlusDamagePercent ) / 100;
		lpUser->m_MagicDamageMin		+= ( lpUser->m_MagicDamageMin * iPlusDamagePercent ) / 100;
		lpUser->m_MagicDamageMax		+= ( lpUser->m_MagicDamageMax * iPlusDamagePercent ) / 100;
	}

	if(lpUser->QT_BuffTime > 0)
	{
		int iPlusDefencePercent = 10;
		lpUser->m_Defense				+= ( lpUser->m_Defense * iPlusDefencePercent ) / 100;
		lpUser->m_MagicDefense			+= ( lpUser->m_MagicDefense * iPlusDefencePercent ) / 100;
	}
}

#endif