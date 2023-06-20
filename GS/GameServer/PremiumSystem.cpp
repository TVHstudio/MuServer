#include "StdAfx.h"
#include "PremiumSystem.h"
#include "Message.h"
#include "ZtUser.h"
#include "ZtLicense.h"
#include "OffExp.h"
#include "OffTrade.h"
#include "ConnectZt.h"
#include "Functions.h"
#include "GMManager.h"
#include "ZtLicense.h"

PremiumSystem Premium;

void PremiumSystem::Loader()
{
	if(g_ZtLicense.user.PremiumZt == true)
	{
		return;
	}

	this->Enable = GetPrivateProfileInt("Common","Enable",0,PREMIUM_DIR);
	this->PlusExp = GetPrivateProfileInt("Common","PlusExp",0,PREMIUM_DIR);
	this->PlusZen = GetPrivateProfileInt("Common","PlusZen",0,PREMIUM_DIR);

#ifdef PREM_TYPE
	if(g_ZtLicense.CheckUser(eZtUB::Local) || g_ZtLicense.CheckUser(eZtUB::ulasevich) || g_ZtLicense.CheckUser(eZtUB::ulasevich2))
	{
		this->BronzePlusExp = GetPrivateProfileInt("PremType","BronzePlusExp",0,PREMIUM_DIR);
		this->BronzePlusZen = GetPrivateProfileInt("PremType","BronzePlusZen",0,PREMIUM_DIR);
		this->SilverPlusExp = GetPrivateProfileInt("PremType","SilverPlusExp",0,PREMIUM_DIR);
		this->SilverPlusZen = GetPrivateProfileInt("PremType","SilverPlusZen",0,PREMIUM_DIR);
		this->GoldPlusExp = GetPrivateProfileInt("PremType","GoldPlusExp",0,PREMIUM_DIR);
		this->GoldPlusZen = GetPrivateProfileInt("PremType","GoldPlusZen",0,PREMIUM_DIR);	
	}
#endif

	this->m_PremiumServerEnable = GetPrivateProfileInt("Common","PremiumServerEnable",0,PREMIUM_DIR);	

	if(g_ZtLicense.CheckUser(eZtUB::PrideMuLocal) || 
		g_ZtLicense.CheckUser(eZtUB::PrideMu) || 
		g_ZtLicense.CheckUser(eZtUB::drynea) || 
		g_ZtLicense.CheckUser(eZtUB::Local3) || 
		g_ZtLicense.CheckUser(eZtUB::feqan)	||
		g_ZtLicense.CheckUser(eZtUB::MU2Play) || 
		g_ZtLicense.CheckUser(eZtUB::bassreflexive)	||
		g_ZtLicense.CheckUser(eZtUB::Escalate) ||
		g_ZtLicense.CheckUser(eZtUB::MedoniAndrei) ||
		g_ZtLicense.CheckUser(eZtUB::mu4you) ||
		g_ZtLicense.CheckUser(eZtUB::eternalmu) ||
		g_ZtLicense.CheckUser(eZtUB::NSGames)
		)
	{
		this->Value = GetPrivateProfileInt("Common","Value",0,PREMIUM_DIR);
		this->Price = GetPrivateProfileInt("Common","Price",0,PREMIUM_DIR); // Price			1 - Zen; 2 - ZtCred; 3 - WCoinC; 4 - WCoinP; 5 - Goblin
		for(int i(0);i<MAX_RES_PREM;i++)
		{
			this->NumberResPrem[i].Res = 0;
			this->NumberResPrem[i].Exp = 0;
			this->NumberResPrem[i].Zen = 0;
		}
		FILE * file = fopen(PREMIUM_DIR,"r");
		if(file == NULL)
		{
			MessageBoxA(0,PREMIUM_DIR,"LOAD FILE ERROR",0);
			ExitProcess(0);
		}

		char Buff[256];
		int Flag = 0;
		this->CountRes = 0;

		while(!feof(file))
		{
			fgets(Buff,256,file);
			if(Zt_IsBadFileLine(Buff, Flag))
				continue;
			if(Flag == 1)
			{
				if(this->CountRes == MAX_RES_PREM) break;
				int n[3];
				sscanf(Buff, "%d %d %d", &n[0], &n[1], &n[2]);
				this->NumberResPrem[this->CountRes].Res = n[0];
				this->NumberResPrem[this->CountRes].Exp = n[1];
				this->NumberResPrem[this->CountRes].Zen = n[2];
				this->CountRes++;
			}
		}
		fclose(file);
	
	}

#ifdef _BUY_VIP_FOR_CRED_
	this->BuyVipCred = GetPrivateProfileInt("Common","BuyVipCred",1,PREMIUM_DIR);
#endif
}

void PremiumSystem::TickTime(int aIndex)
{
	if(!this->Enable) return;
	LPOBJ lpObj = &gObj[aIndex];
	if(g_ZtLicense.CheckUser(eZtUB::PrideMuLocal) || g_ZtLicense.CheckUser(eZtUB::PrideMu) || g_ZtLicense.CheckUser(eZtUB::Local3))
	{
		if((lpObj->PremiumTime > 0) && (!lpObj->OffTrade) && (!lpObj->OffExp))
		{
			lpObj->PremiumTime--;
			if(lpObj->PremiumTime == 0)
			{
				MessageChat(aIndex,"@[Premium Status] Time is over");
			}
		}
	}
	else
	{
		if(lpObj->PremiumTime > 0)
		{
			lpObj->PremiumTime--;
			if(lpObj->PremiumTime == 0)
			{
				MessageChat(aIndex,"@[Premium Status] Time is over");
			}
		}
	}
}

void PremiumSystem::Exp(LPOBJ lpObj, __int64 & Experience)
{
	if(!this->Enable) return;
	if(lpObj->PremiumTime > 0)
	{
		if(g_ZtLicense.CheckUser(eZtUB::PrideMuLocal) || g_ZtLicense.CheckUser(eZtUB::PrideMu) || g_ZtLicense.CheckUser(eZtUB::Local3) || g_ZtLicense.CheckUser(eZtUB::Local))
		{
			for(int i=0;i<this->CountRes;i++)
			{
				if(this->NumberResPrem[i].Res == lpObj->Reset)
				{
					Experience += (( Experience * this->NumberResPrem[i].Exp ) / 100 );
				}
			}
		}
#ifdef PREM_TYPE
		else if(g_ZtLicense.CheckUser(eZtUB::Local) || g_ZtLicense.CheckUser(eZtUB::ulasevich) || g_ZtLicense.CheckUser(eZtUB::ulasevich2))
		{
			if (lpObj->PremiumTimeType == PREM_BRONZE)
			{
				Experience += (( Experience * this->BronzePlusExp) / 100 );
			}
			if (lpObj->PremiumTimeType == PREM_SILVER)
			{
				Experience += (( Experience * this->SilverPlusExp ) / 100 );
			}
			if (lpObj->PremiumTimeType == PREM_GOLD)
			{
				Experience += (( Experience * this->GoldPlusExp) / 100 );
			}

		}
#endif
		else 
		{
			Experience += (( Experience * this->PlusExp ) / 100 );
		}
	}
}

void PremiumSystem::Zen(LPOBJ lpObj, float & money)
{
	if(!this->Enable) return;
	if(lpObj->PremiumTime > 0)
	{

		if(g_ZtLicense.CheckUser(eZtUB::PrideMuLocal) || g_ZtLicense.CheckUser(eZtUB::PrideMu) || g_ZtLicense.CheckUser(eZtUB::Local3) || g_ZtLicense.CheckUser(eZtUB::Local))
		{
			for(int i=0;i<this->CountRes;i++)
			{
				if(this->NumberResPrem[i].Res == lpObj->Reset)
				{
					money += (( money * this->NumberResPrem[i].Zen ) / 100 );
				}
			}
		}
#ifdef PREM_TYPE
		else if(g_ZtLicense.CheckUser(eZtUB::Local) || g_ZtLicense.CheckUser(eZtUB::ulasevich) || g_ZtLicense.CheckUser(eZtUB::ulasevich2))
		{
			if (lpObj->PremiumTimeType == PREM_BRONZE)
			{
				money += (( money * this->BronzePlusZen) / 100 );
			}
			if (lpObj->PremiumTimeType == PREM_SILVER)
			{
				money += (( money * this->SilverPlusZen ) / 100 );
			}
			if (lpObj->PremiumTimeType == PREM_GOLD)
			{
				money += (( money * this->GoldPlusZen) / 100 );
			}
		}
#endif
		else 
		{
			money += (( money * this->PlusZen ) / 100 );
		}
	}
}

void PremiumSystem::ChatSell(int aIndex, LPBYTE Protocol)
{
	if(!this->Enable) return;
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->Authority == 8 || lpObj->Authority == 32)
	{
		// ----
		if(!g_GMManager.CheckCommand(aIndex, egm_cmd_sellpremium))
		{
			return;
		}
		// ----
		if(g_ZtLicense.CheckUser(eZtUB::ulasevich) || g_ZtLicense.CheckUser(eZtUB::ulasevich2) || g_ZtLicense.CheckUser(eZtUB::Local3))
		{
#ifdef PREM_TYPE
			char SellCmdBronze[] = "/sellpremiumbronze";
			char SellCmdSilver[] = "/sellpremiumsilver";
			char SellCmdGold[] = "/sellpremiumgold";
			if(!memcmp(&Protocol[13],SellCmdBronze,strlen(SellCmdBronze)))
			{
				if(strlen((char*)Protocol+13+strlen(SellCmdBronze))>15)return;
				char sName[100];
				unsigned int Day;
				sscanf((char*)Protocol+13+strlen(SellCmdBronze),"%s %d",&sName,&Day);
				if(Day < 0 || Day > 10000) return;
				for(int i=OBJ_STARTUSERINDZT;i<OBJMAX;i++)
				{
					LPOBJ sObj = &gObj[i];
					if(!strcmp(sObj->Name,sName))
					{
						sObj->PremiumTime += ( Day * 86400 );
						sObj->PremiumTimeType = PREM_BRONZE;
						MsgNormal(aIndex,"[Sell Premium] %s",sObj->Name);
						MessageChat(i,"@[Premium Status] +%d Day, Type:Bronze",Day);
						ZtUserDataSend(i);
						return;
					}
				}
			}
			if(!memcmp(&Protocol[13],SellCmdSilver,strlen(SellCmdSilver)))
			{
				if(strlen((char*)Protocol+13+strlen(SellCmdSilver))>15)return;
				char sName[100];
				unsigned int Day;
				sscanf((char*)Protocol+13+strlen(SellCmdSilver),"%s %d",&sName,&Day);
				if(Day < 0 || Day > 10000) return;
				for(int i=OBJ_STARTUSERINDZT;i<OBJMAX;i++)
				{
					LPOBJ sObj = &gObj[i];
					if(!strcmp(sObj->Name,sName))
					{
						sObj->PremiumTime += ( Day * 86400 );
						sObj->PremiumTimeType = PREM_SILVER;
						MsgNormal(aIndex,"[Sell Premium] %s",sObj->Name);
						MessageChat(i,"@[Premium Status] +%d Day, Type:Silver",Day);
						ZtUserDataSend(i);
						return;
					}
				}
			}
			if(!memcmp(&Protocol[13],SellCmdGold,strlen(SellCmdGold)))
			{
				if(strlen((char*)Protocol+13+strlen(SellCmdGold))>15)return;
				char sName[100];
				unsigned int Day;
				sscanf((char*)Protocol+13+strlen(SellCmdGold),"%s %d",&sName,&Day);
				if(Day < 0 || Day > 10000) return;
				for(int i=OBJ_STARTUSERINDZT;i<OBJMAX;i++)
				{
					LPOBJ sObj = &gObj[i];
					if(!strcmp(sObj->Name,sName))
					{
						sObj->PremiumTime += ( Day * 86400 );
						sObj->PremiumTimeType = PREM_GOLD;
						MsgNormal(aIndex,"[Sell Premium] %s",sObj->Name);
						MessageChat(i,"@[Premium Status] +%d Day, Type:Gold",Day);
						ZtUserDataSend(i);
						return;
					}
				}
			}
#endif
		}
		else
		{
			char SellCmd[] = "/sellpremium";
			if(!memcmp(&Protocol[13],SellCmd,strlen(SellCmd)))
			{
				if(strlen((char*)Protocol+13+strlen(SellCmd))>15)return;
				char sName[100];
				unsigned int Day;
				sscanf((char*)Protocol+13+strlen(SellCmd),"%s %d",&sName,&Day);
				if(Day < 0 || Day > 10000) return;
				for(int i=OBJ_STARTUSERINDZT;i<OBJMAX;i++)
				{
					LPOBJ sObj = &gObj[i];
					if(sObj->Connected == PLAYER_PLAYING)
					{
						if(!strcmp(sObj->Name,sName))
						{
							sObj->PremiumTime += ( Day * 86400 );
							MsgNormal(aIndex,"[Sell Premium] %s",sObj->Name);
							MessageChat(i,"@[Premium Status] +%d Day",Day);
							ZtUserDataSend(i);
							return;
						}
					}
				}
			}	
		}
	}
}

void PremiumSystem::ConnectInfo(int aIndex)
{
	if(!this->Enable) return;
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->PremiumTime > 0)
	{
#ifdef DRYNEA_31_10
#else
		if(g_ZtLicense.CheckUser(eZtUB::drynea))
		{
		}
		else
		{
#endif
			MessageChat(aIndex,"@[Premium Status] Active");
#ifdef DRYNEA_31_10
			if(g_ZtLicense.CheckUser(eZtUB::SILVER1) || g_ZtLicense.CheckUser(eZtUB::SILVER2) || g_ZtLicense.CheckUser(eZtUB::PrideMuLocal) || g_ZtLicense.CheckUser(eZtUB::PrideMuLocal) || g_ZtLicense.CheckUser(eZtUB::PrideMu) || g_ZtLicense.CheckUser(eZtUB::drynea) || g_ZtLicense.CheckUser(eZtUB::Local3))
#else
			if(g_ZtLicense.CheckUser(eZtUB::SILVER1) || g_ZtLicense.CheckUser(eZtUB::SILVER2) || g_ZtLicense.CheckUser(eZtUB::PrideMuLocal) || g_ZtLicense.CheckUser(eZtUB::PrideMuLocal) || g_ZtLicense.CheckUser(eZtUB::PrideMu) || g_ZtLicense.CheckUser(eZtUB::Local3) || g_ZtLicense.CheckUser(eZtUB::Local))
#endif
			{
				MessageChat(aIndex,"@[Premium Status] Day: %d",(lpObj->PremiumTime/(60 * 60 * 24)));
			}
			else 
			{
				MessageChat(aIndex,"@[Premium Status] Min: %d",(lpObj->PremiumTime/60));
			}
#ifdef DRYNEA_31_10
#else
		}
#endif
	}
}

bool PremiumSystem::CheckPremium(int aIndex)
{
	if(!this->Enable) return false;
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->PremiumTime > 0)
	{
		return true;
	}
	return false;
}

//void PremiumSystem::ChatBuyVipUser(int aIndex, LPBYTE Protocol)
//{
//	if(!this->Enable || !this->BuyVipCred) return;
//	char BuyCMD[] = "/buypremium";
//	if(!memcmp(&Protocol[13],BuyCMD,strlen(BuyCMD)))
//	{
//		LPOBJ lpObj = &gObj[aIndex];
//
//		int Day = 0;
//		sscanf((char*)Protocol+13+strlen(BuyCMD),"%d",&Day);
//		if(Day < 1 || Day > 10000) return;
//
//		int NeedCred = this->BuyVipCred * Day;
//
//		if(NeedCred > lpObj->ZtCred)
//		{
//			MsgNormal(aIndex,"[Buy Premium] Need %d Credits",NeedCred);
//			return;
//		}
//
//		lpObj->ZtCred -= NeedCred;
//
//		lpObj->PremiumTime += Day*86400;
//
//		MessageChat(aIndex,"@[Buy Status] +%d Day",Day);
//	}
//}

bool PremiumSystem::CheckPremiumServer(int aIndex)
{
	if(!OBJMAX_RANGE(aIndex))
	{
		return false;
	}

	if(this->m_PremiumServerEnable)
	{
		LPOBJ lpUser = &gObj[aIndex];

		if(lpUser->PremiumTime <= 0)
		{
			return false;
		}
	}

	return true;
}
