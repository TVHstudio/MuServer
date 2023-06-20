#include "StdAfx.h"

#ifdef _VOTER_


#define VOTER_DIR	"..\\Data\\ZtData\\Voter.ini"
#define MMOTOP_FILE	"mmotop.txt"
#define QTOP_FILE	"qtop.txt"
#define ANONS_FILE	"anonse.txt"

//#define VOTE_DEBUG	0

class Voter
{
private:

	bool MMOTOP_Enable;

	// ----

	bool MMOTOP_DeleteVoteFile;
	bool MMOTOP_DownloadFile;

	int MMOTOP_UPDATE_VOTER;

	char MMOTOP_FileName[200];

	int MMOTOP_BonusWcoinC;
	int MMOTOP_BonusWcoinP;
	int MMOTOP_BonusWcoinG;
	int MMOTOP_BonusZtCred;

	int MMOTOP_BonusItemActive;
	int MMOTOP_BonusItemType;
	int MMOTOP_BonusItemIndex;
	int MMOTOP_BonusItemLevel;

	int MMOTOP_BonusChaosBank;
	int MMOTOP_BonusBlessBank;
	int MMOTOP_BonusSoulBank;
	int MMOTOP_BonusLifeBank;

	int MMOTOP_SMSBonusWcoinC;
	int MMOTOP_SMSBonusWcoinP;
	int MMOTOP_SMSBonusWcoinG;
	int MMOTOP_SMSBonusZtCred;

	int MMOTOP_SMSBonusItemActive;
	int MMOTOP_SMSBonusItemType;
	int MMOTOP_SMSBonusItemIndex;
	int MMOTOP_SMSBonusItemLevel;

	int MMOTOP_SMSBonusChaosBank;
	int MMOTOP_SMSBonusBlessBank;
	int MMOTOP_SMSBonusSoulBank;
	int MMOTOP_SMSBonusLifeBank;

	//~~~~~~~~~~~~~~~~

	bool QTOP_Enable;

	bool QTOP_DeleteVoteFile;
	bool QTOP_DownloadFile;

	int QTOP_UPDATE_VOTER;

	char QTOP_FileName[200];

	int QTOP_BonusWcoinC;
	int QTOP_BonusWcoinP;
	int QTOP_BonusWcoinG;
	int QTOP_BonusZtCred;

	int QTOP_BonusItemActive;
	int QTOP_BonusItemType;
	int QTOP_BonusItemIndex;
	int QTOP_BonusItemLevel;

	int QTOP_BonusChaosBank;
	int QTOP_BonusBlessBank;
	int QTOP_BonusSoulBank;
	int QTOP_BonusLifeBank;

	int QTOP_SMSBonusWcoinC;
	int QTOP_SMSBonusWcoinP;
	int QTOP_SMSBonusWcoinG;
	int QTOP_SMSBonusZtCred;

	int QTOP_SMSBonusItemActive;
	int QTOP_SMSBonusItemType;
	int QTOP_SMSBonusItemIndex;
	int QTOP_SMSBonusItemLevel;

	int QTOP_SMSBonusChaosBank;
	int QTOP_SMSBonusBlessBank;
	int QTOP_SMSBonusSoulBank;
	int QTOP_SMSBonusLifeBank;

	// ----

	int MMOTOP_BuffTime;
	int MMOTOP_SMSBuffTime;
	int QTOP_BuffTime;
	int QTOP_SMSBuffTime;

	#if(ENABLE_GAMESERVER_DLL)

	bool ANONS_Enable;

	// ----

	bool ANONS_DeleteVoteFile;
	bool ANONS_DownloadFile;

	int ANONS_UPDATE_VOTER;

	char ANONS_FileName[200];

	int ANONS_BonusWcoinC;
	int ANONS_BonusWcoinP;
	int ANONS_BonusWcoinG;
	int ANONS_BonusZtCred;

	int ANONS_BonusItemActive;
	int ANONS_BonusItemType;
	int ANONS_BonusItemIndex;
	int ANONS_BonusItemLevel;

	int ANONS_BonusChaosBank;
	int ANONS_BonusBlessBank;
	int ANONS_BonusSoulBank;
	int ANONS_BonusLifeBank;

	int ANONS_SMSBonusWcoinC;
	int ANONS_SMSBonusWcoinP;
	int ANONS_SMSBonusWcoinG;
	int ANONS_SMSBonusZtCred;

	int ANONS_SMSBonusItemActive;
	int ANONS_SMSBonusItemType;
	int ANONS_SMSBonusItemIndex;
	int ANONS_SMSBonusItemLevel;

	int ANONS_SMSBonusChaosBank;
	int ANONS_SMSBonusBlessBank;
	int ANONS_SMSBonusSoulBank;
	int ANONS_SMSBonusLifeBank;

	//~~~~~~~~~~~~~~~~

	#endif
	

public:
	void Init();
	// ----
	void Mootop();
	void MootopReed();
	// ----
	void Qtop();
	void QtopReed();
	// ----
	#if(ENABLE_GAMESERVER_DLL)
	void Anons();
	void AnonsReed();
	#endif

	void Run();
	void PlayerCalculator(int aIndex);
};
extern Voter gVoter;

#endif