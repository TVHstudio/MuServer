#pragma once

#include "StdAfx.h"
#include "user.h"

#define PANDORA_EVENT_DIR	"..\\Data\\ZtData\\Events\\PandoraBox.ini"

#define PAN_EVENT_MAX_CORD 300
#define PAN_EVENT_MAX_TIME 20
#define PAN_EVENT_MAX_REWARD_ITEM 100

/*	
	Кординат?возможны?точе?появлен? сундук?
*/
struct CordsBox
{
	int X;
	int Y;
	int Map;
};
/*
	Время появлен? сундук?
*/
struct TimePandora
{
	int Hour;
	int Min;
};
struct PandoraRewardDrop
{
	int Type;
	int Index;
	int Level;
	int Skill;
	int Luck;
	int Opt;
	int Exl;
	int Anc;
};
class cPandoraBoxEvent
{
public:
	void Init();
	void Load();
	void Start();
	void End();
	void TickTime();
	void RespawnBox(CordsBox RandCord);
	bool BoxClick(LPOBJ lpNpc, LPOBJ lpObj);
	void Player(LPOBJ lpObj);
	bool ProcessKill(LPOBJ lpObj, LPOBJ lpTargetObj);
	void Prize();
	bool PkCheck(LPOBJ lpObj, LPOBJ lpTarget);
	bool BlockTeleport(int aIndex);
	void CloseClient(int aIndex);
	void LoadMonsterPos();

	int ActivePlayer;
	bool Started;
//private:
	bool Enable;
	CordsBox Cords[PAN_EVENT_MAX_CORD];
	int CountCord;
	TimePandora Times[PAN_EVENT_MAX_TIME];
	int CountTimes;
	PandoraRewardDrop Reward[PAN_EVENT_MAX_REWARD_ITEM];
	int CountReward;
	int ActiveMap;
	int EventTime;
	int EventTimeSecond;

	int ActivePlayerPkLevel;

	int BoxIndex;
	int BoxPos;

	int RewardCredits;
	int RewardWcoinC;
	int RewardWcoinP;
	int RewardGoblinPoints;
};
extern cPandoraBoxEvent gPandoraBoxEvent;
