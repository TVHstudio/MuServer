#include "StdAfx.h"
#include "DropEvent.h"
#include "USER.h"
#include "Functions.h"
#include "Message.h"
#include "DSProtocol.h"
#ifdef _MESSAGE_CONFIG_
#include "Configs.h"
#endif
#include "ZtFunction.h"
#include "ZtLicense.h"
#include "TimerZt.h"
#include "ZtText.h"

cDropEvent DropEvent;

void cDropEvent::LoadConfigs()
{
	Enable = GetPrivateProfileInt("Common","Enable",1,DROP_EVENT_DIR);

	for(int i(0);i < DROP_EVENT_MAX; i++)
	{
		Item[i].Index = 0;
		Item[i].Type  = 0;
		Item[i].Level = 0;
		Item[i].Skill = 0;
		Item[i].Luck  = 0;
		Item[i].Opt   = 0;
		Item[i].Exl	  = 0;
		Item[i].Anc   = 0;
	}

	for(int j(0);j < DROP_EVENT_MAX; j++)
	{
		Time[j].Hour  = 0;
		Time[j].Min   = 0;
	}

	for(int f=0;f<100;f++)
	{
		Cord[f].Map	= 0;
		Cord[f].X	= 0;
		Cord[f].Y	= 0;
	}
}

void cDropEvent::LoadFile()
{
	LoadConfigs();

	

	FILE *file = fopen(DROP_EVENT_DIR,"r");

	if(file == NULL)
	{
		MessageBoxA(0,DROP_EVENT_DIR,"LOAD FILE ERROR",0);
		ExitProcess(1);
		return;
	}

	char Buff[256];
	int Flag = 0;

	Count[1] = 0;
	Count[2] = 0;
	Count[3] = 0;

	while(!feof(file)) // ��������� ���� �� ������ ?��������?
	{
		fgets(Buff,256,file);//������� ������ ������?������
		if(Zt_IsBadFileLine(Buff, Flag)) //��������������� �������
			continue;
		if(Flag == 1)
		{
			int n[10];
			sscanf(Buff, "%d %d %d %d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4], &n[5], &n[6], &n[7]);

			Item[Count[1]].Type  = n[0];
			Item[Count[1]].Index = n[1];
			Item[Count[1]].Level = n[2];
			Item[Count[1]].Skill = n[3];
			Item[Count[1]].Luck  = n[4];
			Item[Count[1]].Opt   = n[5];
			Item[Count[1]].Exl	 = n[6];
			Item[Count[1]].Anc   = n[7];
			Count[1]++;
		}

		if(Flag == 2)
		{
			int n[3];
			sscanf(Buff, "%d %d", &n[0], &n[1]);
			Time[Count[2]].Hour  = n[0];
			Time[Count[2]].Min   = n[1];
			Count[2]++;
		}

		if(Flag == 3)
		{
			int n[4];
			sscanf(Buff, "%d %d %d", &n[0], &n[1], &n[2]);
			Cord[Count[3]].Map  = n[0];
			Cord[Count[3]].X	= n[1];
			Cord[Count[3]].Y	= n[2];
			Count[3]++;
		}
	}
	fclose(file);
}
void cDropEvent::StartEvent()
{
	MessaageAllGlobal(g_ZtText.GetText(254));
	for(int i=0;i<Count[3];i++)
	{
		int Ran = rand()%Count[1];

		int NewExl = 0;
		int NewAnc = 0;

		int DropItem = ITEMGET(Item[Ran].Type,Item[Ran].Index);

		if(Item[Ran].Exl > 0)
			NewExl = GenExcOpt(Item[Ran].Exl);

		if(Item[Ran].Anc == 5 || Item[Ran].Anc == 10)
			NewAnc = Item[Ran].Anc;

		int CordMap = Cord[i].Map;
		int CordX = Cord[i].X;
		int CordY = Cord[i].Y;

		ItemSerialCreateSend(NULL,CordMap,CordX,CordY,DropItem,Item[Ran].Level,0,Item[Ran].Skill,Item[Ran].Luck,Item[Ran].Opt,NULL,NewExl,NewAnc);
	}
	//MessaageAllGlobal("[Drop Event] End");
}
void cDropEvent::TickTime()
{
	if(!Enable)
		return;

	SYSTEMTIME t;
	GetLocalTime(&t);

#if(NEWTIMEREX)
	if(g_TimerZt.GetSecond() == 00)
#else
	if(t.wSecond == 00)
#endif
	{
		for(int i = 0; i < Count[2]; i++)
		{
#ifdef _MESSAGE_CONFIG_
			if(g_ZtLicense.CheckUser(eZtUB::Gredy) || g_ZtLicense.CheckUser(eZtUB::GredyLocal) || g_ZtLicense.CheckUser(eZtUB::Gredy2))
			{
				if(Time[i].Min >= 1)
				{			
						if(Time[i].Hour == t.wHour && ((Time[i].Min-1) == t.wMinute))
							MessaageAllGlobal(ZtConfig.MessageConfig.DropEvent, 1);
				}
				else if(Time[i].Min == 0)
				{
					if(Time[i].Hour-1 == t.wHour && (59 == t.wMinute))
							MessaageAllGlobal(ZtConfig.MessageConfig.DropEvent, 1);
				}
				
			}
			else
			{
				if(Time[i].Min > 5)
				{
					for(int j=1; j <= 5; j++)
					{
			
						if(Time[i].Hour == t.wHour && (Time[i].Min-j) == t.wMinute)
							MessaageAllGlobal(ZtConfig.MessageConfig.DropEvent, j);
					}
				}
				else if(Time[i].Min == 4)
				{
						if(Time[i].Hour-1 == t.wHour && 59 == t.wMinute)
							MessaageAllGlobal(ZtConfig.MessageConfig.DropEvent, 5);
						if(Time[i].Hour == t.wHour && 0 == t.wMinute)
							MessaageAllGlobal(ZtConfig.MessageConfig.DropEvent, 4);
						if(Time[i].Hour == t.wHour && 1 == t.wMinute)
							MessaageAllGlobal(ZtConfig.MessageConfig.DropEvent, 3);
						if(Time[i].Hour == t.wHour && 2 == t.wMinute)
							MessaageAllGlobal(ZtConfig.MessageConfig.DropEvent, 2);
						if(Time[i].Hour == t.wHour && 3 == t.wMinute)
							MessaageAllGlobal(ZtConfig.MessageConfig.DropEvent, 1);

				}
				else if(Time[i].Min == 3)
				{
						if(Time[i].Hour-1 == t.wHour && 58 == t.wMinute)
							MessaageAllGlobal(ZtConfig.MessageConfig.DropEvent, 5);
						if(Time[i].Hour-1 == t.wHour && 59 == t.wMinute)
							MessaageAllGlobal(ZtConfig.MessageConfig.DropEvent, 4);
						if(Time[i].Hour == t.wHour && 0 == t.wMinute)
							MessaageAllGlobal(ZtConfig.MessageConfig.DropEvent, 3);
						if(Time[i].Hour == t.wHour && 1 == t.wMinute)
							MessaageAllGlobal(ZtConfig.MessageConfig.DropEvent, 2);
						if(Time[i].Hour == t.wHour && 2 == t.wMinute)
							MessaageAllGlobal(ZtConfig.MessageConfig.DropEvent, 1);
				}
				else if(Time[i].Min == 2)
				{
						if(Time[i].Hour-1 == t.wHour && 57 == t.wMinute)
							MessaageAllGlobal(ZtConfig.MessageConfig.DropEvent, 5);
						if(Time[i].Hour-1 == t.wHour && 58 == t.wMinute)
							MessaageAllGlobal(ZtConfig.MessageConfig.DropEvent, 4);
						if(Time[i].Hour-1 == t.wHour && 59 == t.wMinute)
							MessaageAllGlobal(ZtConfig.MessageConfig.DropEvent, 3);
						if(Time[i].Hour == t.wHour && 0 == t.wMinute)
							MessaageAllGlobal(ZtConfig.MessageConfig.DropEvent, 2);
						if(Time[i].Hour == t.wHour && 1 == t.wMinute)
							MessaageAllGlobal(ZtConfig.MessageConfig.DropEvent, 1);
				}
				else if(Time[i].Min == 1)
				{
						if(Time[i].Hour-1 == t.wHour && 56 == t.wMinute)
							MessaageAllGlobal(ZtConfig.MessageConfig.DropEvent, 5);
						if(Time[i].Hour-1 == t.wHour && 57 == t.wMinute)
							MessaageAllGlobal(ZtConfig.MessageConfig.DropEvent, 4);
						if(Time[i].Hour-1 == t.wHour && 58 == t.wMinute)
							MessaageAllGlobal(ZtConfig.MessageConfig.DropEvent, 3);
						if(Time[i].Hour-1 == t.wHour && 59 == t.wMinute)
							MessaageAllGlobal(ZtConfig.MessageConfig.DropEvent, 2);
						if(Time[i].Hour == t.wHour && 0 == t.wMinute)
							MessaageAllGlobal(ZtConfig.MessageConfig.DropEvent, 1);
				}
				else if(Time[i].Min == 0)
				{
						if(Time[i].Hour-1 == t.wHour && 55 == t.wMinute)
							MessaageAllGlobal(ZtConfig.MessageConfig.DropEvent, 5);
						if(Time[i].Hour-1 == t.wHour && 56 == t.wMinute)
							MessaageAllGlobal(ZtConfig.MessageConfig.DropEvent, 4);
						if(Time[i].Hour-1 == t.wHour && 57 == t.wMinute)
							MessaageAllGlobal(ZtConfig.MessageConfig.DropEvent, 3);
						if(Time[i].Hour-1 == t.wHour && 58 == t.wMinute)
							MessaageAllGlobal(ZtConfig.MessageConfig.DropEvent, 2);
						if(Time[i].Hour-1 == t.wHour && 59 == t.wMinute)
							MessaageAllGlobal(ZtConfig.MessageConfig.DropEvent, 1);
				}
			}
#endif
			if(Time[i].Hour == t.wHour && Time[i].Min == t.wMinute)
			{

				this->StartEvent();
				return;
			}
		}
	}
}