#include "StdAfx.h"

#include "user.h"

#define MAX_ZT_QUEST		1000
#define DIR_ZT_QUEST_SYSTEM "..\\Data\\ZtData\\ZtQuestSystem.ini"

class cZtQuest
{
public:
	int Enable;
	int NPC;
	char NameQuest[50];

	void Loader();
	void NPCClick(LPOBJ lpNpc, LPOBJ lpObj);
	void MonsterKill(LPOBJ lpObj, LPOBJ lpTargetObj);
	void Pressent(LPOBJ lpObj, int Present, int Gifts,int Level);

	struct
	{
		int Monster;
		int Count;
		int Procent;
		int Reward;
		int Gift;
		int iLevel;
		char Msg1[100];
		char Msg2[100];
	}Quest[MAX_ZT_QUEST];

	int qNum;

};
extern cZtQuest ZtQuestSystem;
