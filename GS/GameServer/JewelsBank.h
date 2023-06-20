#pragma once
#include "StdAfx.h"
#include "DSProtocol.h"

#define JEWELSBANK_DIR	"..\\Data\\ZtData\\JewelsBank.ini"

struct PMSG_JEWELBANK
{
	PBMSG_HEAD2 h;
	int Result;
};

class JewelsBank
{
private: 
	bool Enable;
	
	int ZtChaosTeen;
	int ZtChaosTwenty;
	int ZtChaosThirty;
	int ZtChaosForty;
	int ZtChaosFifty;
	int ZtChaosHundred;

	int ZtBlessTeen;
	int ZtBlessTwenty;
	int ZtBlessThirty;
	int ZtBlessForty;
	int ZtBlessFifty;
	int ZtBlessHundred;

	int ZtSoulTeen;
	int ZtSoulTwenty;
	int ZtSoulThirty;
	int ZtSoulForty;
	int ZtSoulFifty;
	int ZtSoulHundred;

	int ZtLifeTeen;
	int ZtLifeTwenty;
	int ZtLifeThirty;
	int ZtLifeForty;
	int ZtLifeFifty;
	int ZtLifeHundred;

	int ZtCreateonTeen;
	int ZtCreateonTwenty;
	int ZtCreateonThirty;
	int ZtCreateonForty;
	int ZtCreateonFifty;
	int ZtCreateonHundred;

	/**/
	int ZtGuardianTeen;
	int ZtGuardianTwenty;
	int ZtGuardianThirty;
	int ZtGuardianForty;
	int ZtGuardianFifty;
	int ZtGuardianHundred;

	int ZtHarmonyTeen;
	int ZtHarmonyTwenty;
	int ZtHarmonyThirty;
	int ZtHarmonyForty;
	int ZtHarmonyFifty;
	int ZtHarmonyHundred;

	int ZtLowStoneTeen;
	int ZtLowStoneTwenty;
	int ZtLowStoneThirty;
	int ZtLowStoneForty;
	int ZtLowStoneFifty;
	int ZtLowStoneHundred;

	int ZtHighStoneTeen;
	int ZtHighStoneTwenty;
	int ZtHighStoneThirty;
	int ZtHighStoneForty;
	int ZtHighStoneFifty;
	int ZtHighStoneHundred;

	int ZtGemStoneTeen;
	int ZtGemStoneTwenty;
	int ZtGemStoneThirty;
	int ZtGemStoneForty;
	int ZtGemStoneFifty;
	int ZtGemStoneHundred;
	/**/

	int ExForty;

	int CountExChaos;
	int CountExBless;
	int CountExSoul;
	int CountExLife;
	int CountExCreateon;

public:
	void Load();

	void sendchaosbank(int aIndex, int Count);
	void sendblessbank(int aIndex, int Count);
	void sendsoulbank(int aIndex, int Count);
	void sendlifebank(int aIndex, int Count);
	void sendcreateonbank(int aIndex, int Count);

	void recvchaosbank(int aIndex, int Count);
	void recvblessbank(int aIndex, int Count);
	void recvsoulbank(int aIndex, int Count);
	void recvlifebank(int aIndex, int Count);
	void recvcreateonbank(int aIndex, int Count);
	
#ifdef PRIVATE_MODULE
#if _CONFLICT_
	void exchaos(int aIndex, int Count);
	void exbless(int aIndex, int Count);
	void exsoul(int aIndex, int Count);
	void exlife(int aIndex, int Count);
	void excreateon(int aIndex, int Count);

	void exGuardian(int aIndex, int Count);
	void exHarmony(int aIndex, int Count);
	void exLowStone(int aIndex, int Count);
	void exHighStone(int aIndex, int Count);
	void exGemStone(int aIndex, int Count);
#endif
#endif
	
	void sendzen(int aIndex, int Count);
	void recvzen(int aIndex, int Count);
	void sendGuardianBank(int aIndex, int Count);
	void sendHarmonyBank(int aIndex, int Count);
	void sendLowStoneBank(int aIndex, int Count);
	void sendHighStoneBank(int aIndex, int Count);
	void sendGemStoneBank(int aIndex, int Count);
	void recvGuardianBank(int aIndex, int Count);
	void recvHarmonyBank(int aIndex, int Count);
	void recvLowStoneBank(int aIndex, int Count);
	void recvHighStoneBank(int aIndex, int Count);
	void recvGemStoneBank(int aIndex, int Count);
	void Packet(int aIndex, PMSG_JEWELBANK* lpMsg);
};
extern JewelsBank gJewelsBank;