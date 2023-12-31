#include "stdafx.h"
#include "PersonalShopZt.h"
#include "Interface.h"
#include "Protocol.h"
#include "Console.h"
#include "TMemory.h"
#include "Object.h"
#include "ZtText.h"
#include "ZtLicense.h"

#if(CUSTOM_PERONAL_ZT==TRUE)

PersonalShopZt g_PersonalShopZt;
// ----------------------------------------------------------------------------------------------



static DWORD _0079AE5D = 0x0079AE5D;

void PSShopVieweFix()
{
	PMSG_REQ_BUYITEM_FROM_PSHOP pReq;
	pReq.h.set((LPBYTE)&pReq, 0x3F, 0x06, sizeof(pReq));
	pReq.NumberH = SET_NUMBERH(g_PersonalShopZt.aTargetIndex);
	pReq.NumberL = SET_NUMBERL(g_PersonalShopZt.aTargetIndex);
	memcpy(pReq.btName, g_PersonalShopZt.TargetName, 10);

	pReq.btItemPos = g_PersonalShopZt.ReturnPos();

	gProtocol.DataSend((LPBYTE)&pReq, pReq.h.size);

}
// ----------------------------------------------------------------------------------------------

static DWORD _007E44B3 = 0x007E44B3;
static DWORD _007E4577 = 0x007E4577;
static DWORD _0D4592C = 0x0D4592C;

Naked(ConutPriceDraw)
{
	if(g_PersonalShopZt.PriceBek < g_PersonalShopZt.TotalPrice)
	{
		g_PersonalShopZt.PriceBek++;
		_asm
		{
			jmp _007E44B3;
		}
	}
	
	g_PersonalShopZt.PriceBek = 1;

	_asm
	{
		PUSH _0D4592C
		JMP _007E4577
	}
}
// ----------------------------------------------------------------------------------------------

char PersonalShopZt::CheckPersonalPrice()
{
	int v0;
	LPVOID v1; // eax@4
	int v2; // eax@4
	int v3; // eax@5
	int v5; // [sp+0h] [bp-14h]@4
	int v6; // [sp+4h] [bp-10h]@5
	int v7; // [sp+8h] [bp-Ch]@4
	int i; // [sp+Ch] [bp-8h]@1
	char Result; // [sp+13h] [bp-1h]@1

	Result = 1;
	for ( i = 0; i < 32; ++i )
	{
		v5 = 0;
		v0 = i;
		v1 = sub_860FC0();
		v2 = sub_8612B0(v1);
		v7 = sub_840DF0((LPVOID)v2, v0);

		if ( v7 )
		{
			Result = 0;
			v6 = *(BYTE *)(v7 + 67) + 8 * *(BYTE *)(v7 + 68) + 204;

			v6 = v6 - 204;

			Result = 1;

			if(g_PersonalShopZt.PSInvetrory[v6].Zen > 0 )
			{
				Result = 0;
			}
//#if(PERSONAL_BONUS==TRUE)
			if(g_PersonalShopZt.iPERSONAL_BONUS)
			{
				if(g_PersonalShopZt.PSInvetrory[v6].Bonus > 0)
				{
					Result = 0;
				}
			}
//#endif
			if(g_PersonalShopZt.PSInvetrory[v6].Bless > 0)
			{
				Result = 0;
			}
			if(g_PersonalShopZt.PSInvetrory[v6].Soul > 0)
			{
				Result = 0;
			}
			if(g_PersonalShopZt.PSInvetrory[v6].Chaos > 0)
			{
				Result = 0;
			}
			if(g_PersonalShopZt.PSInvetrory[v6].Life > 0)
			{
				Result = 0;
			}
			#if(DEV_PERSONAL_CREDIT)
			if(g_PersonalShopZt.iPERSONAL_CREDIT)
			{
				if(g_PersonalShopZt.PSInvetrory[v6].Credit > 0)
				{
					Result = 0;
				}
			}
			#endif

			if(Result == 1)
			{
				break;
			}
		}
	}
	return Result;
}
// ----------------------------------------------------------------------------------------------

#define pGetPSItemPos			((char(__cdecl*)(char a1, int a2, int a3)) 0x4FA7C0)

char PersonalShopZt::GetPSItemPos(int a1, int a2, int a3)
{
	g_PersonalShopZt.ItemShowPos = a1;

	if(g_PersonalShopZt.aTargetIndex == pGameIndex)
	{
		int pos = g_PersonalShopZt.ItemShowPos - 204;

		bool Result = 0;

		if(g_PersonalShopZt.PSInvetrory[pos].Zen > 0 )
		{
			Result = 1;
		}

		if(g_PersonalShopZt.PSInvetrory[pos].Bless > 0)
		{
			Result = 1;
		}
		if(g_PersonalShopZt.PSInvetrory[pos].Soul > 0)
		{
			Result = 1;
		}
		if(g_PersonalShopZt.PSInvetrory[pos].Chaos > 0)
		{
			Result = 1;
		}
		if(g_PersonalShopZt.PSInvetrory[pos].Life > 0)
		{
			Result = 1;
		}

		#if(DEV_PERSONAL_CREDIT)
		if(g_PersonalShopZt.PSInvetrory[pos].Credit > 0)
		{
			if(g_PersonalShopZt.iPERSONAL_CREDIT)
			{
				Result = 1;
			}
			else
			{
				Result = 0;
			}
		}
		#endif

		if(g_PersonalShopZt.PSInvetrory[pos].Bonus > 0)
		{
//#if(PERSONAL_BONUS==TRUE)
			//Result = 1;
//#else
			//Result = 0;
//#endif
			if(g_PersonalShopZt.iPERSONAL_BONUS)
			{
				Result = 1;
			}
			else
			{
				Result = 0;
			}
		}


		if(Result == 0)
		{
			return 0;
		}
	}

	return pGetPSItemPos(a1,a2,a3);
}
// ----------------------------------------------------------------------------------------------

void PersonalShopZt::PriceInvenory(int itempos, int zen, int bonus, short bless, short soul, short chaos, short life, int credit)
{

	//gConsole.Output(cGREY, "PriceInvenory");

	g_PersonalShopZt.PSInvetrory[itempos].Zen = zen;
	g_PersonalShopZt.PSInvetrory[itempos].Bonus = bonus;
	g_PersonalShopZt.PSInvetrory[itempos].Bless = bless;
	g_PersonalShopZt.PSInvetrory[itempos].Soul = soul;
	g_PersonalShopZt.PSInvetrory[itempos].Chaos = chaos;
	g_PersonalShopZt.PSInvetrory[itempos].Life = life;
	#if(DEV_PERSONAL_CREDIT)
	g_PersonalShopZt.PSInvetrory[itempos].Credit = credit;
	#endif
}
// ----------------------------------------------------------------------------------------------

void PersonalShopZt::PriceInvTarget(int itempos, int zen, int bonus, short bless, short soul, short chaos, short life, int credit)
{
	g_PersonalShopZt.PSInvTarget[itempos].Zen = zen;
	g_PersonalShopZt.PSInvTarget[itempos].Bonus = bonus;
	g_PersonalShopZt.PSInvTarget[itempos].Bless = bless;
	g_PersonalShopZt.PSInvTarget[itempos].Soul = soul;
	g_PersonalShopZt.PSInvTarget[itempos].Chaos = chaos;
	g_PersonalShopZt.PSInvTarget[itempos].Life = life;
	#if(DEV_PERSONAL_CREDIT)
	g_PersonalShopZt.PSInvTarget[itempos].Credit = credit;
	#endif
}
// ----------------------------------------------------------------------------------------------

void PersonalShopZt::SendPrice(int itempos, int zen, int bonus, short bless, short soul, short chaos, short life, int credit)
{
	PMSG_REQ_PSHOP_SETITEMPRICE_ZT pReq;
	pReq.h.set((LPBYTE)&pReq, 0x3F, 0x01, sizeof(pReq));
	pReq.btItemPos	= itempos;

	pReq.sItemPrice4 = ((zen>>16)>>8);
	pReq.sItemPrice3 = ((zen>>16)&0xFF);
	pReq.sItemPrice2 = ((zen&0xFFFF)>>8);
	pReq.sItemPrice1 = ((zen&0xFFFF)&0xFF);

	pReq.sBonusPrice4 = ((bonus>>16)>>8);
	pReq.sBonusPrice3 = ((bonus>>16)&0xFF);
	pReq.sBonusPrice2 = ((bonus&0xFFFF)>>8);
	pReq.sBonusPrice1 = ((bonus&0xFFFF)&0xFF);

	pReq.sBlessCnt2 = SET_NUMBERH(bless);
	pReq.sBlessCnt1 = SET_NUMBERL(bless);

	pReq.sSoulCnt2 = SET_NUMBERH(soul);
	pReq.sSoulCnt1 = SET_NUMBERL(soul);

	pReq.sChaosCnt2 = SET_NUMBERH(chaos);
	pReq.sChaosCnt1 = SET_NUMBERL(chaos);

	pReq.sLifeCnt2 = SET_NUMBERH(life);
	pReq.sLifeCnt1 = SET_NUMBERL(life);

	#if(DEV_PERSONAL_CREDIT)
	pReq.sCreditPrice4 = ((credit>>16)>>8);
	pReq.sCreditPrice3 = ((credit>>16)&0xFF);
	pReq.sCreditPrice2 = ((credit&0xFFFF)>>8);
	pReq.sCreditPrice1 = ((credit&0xFFFF)&0xFF);
	#endif

	gProtocol.DataSend((LPBYTE)&pReq, pReq.h.size);
}
// ----------------------------------------------------------------------------------------------

int PersonalShopZt::ReturnPos()
{
	LPVOID  v11 = (LPVOID)sub_8612D0(pWindowThis());
	int v16 = sub_668930(v11) + 204;
	return v16;
}
// ----------------------------------------------------------------------------------------------

void PersonalShopZt::ShowPrice(DWORD a1, const char *a2, char *Price)
{
	int pos = g_PersonalShopZt.ItemShowPos - 204;

	int Zen = 0;
	int Bonus = 0;
	int Bless = 0;
	int Soul = 0;
	int Chaos = 0;
	int Life = 0;
	#if(DEV_PERSONAL_CREDIT)
	int Credit = 0;
	#endif

	if(g_PersonalShopZt.aTargetIndex == pGameIndex)
	{
		Zen = g_PersonalShopZt.PSInvetrory[pos].Zen;
		Bonus = g_PersonalShopZt.PSInvetrory[pos].Bonus;
		Bless = g_PersonalShopZt.PSInvetrory[pos].Bless;
		Soul = g_PersonalShopZt.PSInvetrory[pos].Soul;
		Chaos = g_PersonalShopZt.PSInvetrory[pos].Chaos;
		Life = g_PersonalShopZt.PSInvetrory[pos].Life;
		#if(DEV_PERSONAL_CREDIT)
		Credit = g_PersonalShopZt.PSInvetrory[pos].Credit;
		#endif
	}
	else
	{
		Zen = g_PersonalShopZt.PSInvTarget[pos].Zen;
		Bonus = g_PersonalShopZt.PSInvTarget[pos].Bonus;
		Bless = g_PersonalShopZt.PSInvTarget[pos].Bless;
		Soul = g_PersonalShopZt.PSInvTarget[pos].Soul;
		Chaos = g_PersonalShopZt.PSInvTarget[pos].Chaos;
		Life = g_PersonalShopZt.PSInvTarget[pos].Life;
		#if(DEV_PERSONAL_CREDIT)
		Credit = g_PersonalShopZt.PSInvTarget[pos].Credit;
		#endif
	}

	g_PersonalShopZt.TotalPrice = 0;

	if(Zen > 0)
	{
		g_PersonalShopZt.TotalPrice++;
		if(g_PersonalShopZt.PriceBek == 1)
		g_PersonalShopZt.bDPrice[0] = true;
	}
	if(Bonus > 0)
	{
		g_PersonalShopZt.TotalPrice++;
		if(g_PersonalShopZt.PriceBek == 1)
		g_PersonalShopZt.bDPrice[1] = true;
	}
	if(Bless > 0)
	{
		g_PersonalShopZt.TotalPrice++;
		if(g_PersonalShopZt.PriceBek == 1)
		g_PersonalShopZt.bDPrice[2] = true;
	}
	if(Soul > 0)
	{
		g_PersonalShopZt.TotalPrice++;
		if(g_PersonalShopZt.PriceBek == 1)
		g_PersonalShopZt.bDPrice[3] = true;
	}
	if(Chaos > 0)
	{
		g_PersonalShopZt.TotalPrice++;
		if(g_PersonalShopZt.PriceBek == 1)
		g_PersonalShopZt.bDPrice[4] = true;
	}
	if(Life > 0)
	{
		g_PersonalShopZt.TotalPrice++;
		if(g_PersonalShopZt.PriceBek == 1)
		g_PersonalShopZt.bDPrice[5] = true;
	}
	#if(DEV_PERSONAL_CREDIT)
	if(Credit > 0)
	{
		g_PersonalShopZt.TotalPrice++;
		if(g_PersonalShopZt.PriceBek == 1)
		g_PersonalShopZt.bDPrice[6] = true;
	}
	#endif

	// ----

	if(g_PersonalShopZt.bDPrice[0] == true)
	{
		g_PersonalShopZt.bDPrice[0] = false;

		char MoneyBuff[50];
		pGetMoneyFormat((double)Zen, MoneyBuff, 0);
		pShowPrice(a1, g_ZtText.GetText(176), MoneyBuff); 
		return;
	}

	if(g_PersonalShopZt.bDPrice[1] == true)
	{
		g_PersonalShopZt.bDPrice[1] = false;
//#if(PERSONAL_BONUS == TRUE)
//		pShowPrice(a1, "Price: %d Bonus", Bonus); 
//#else
		if(g_PersonalShopZt.iPERSONAL_BONUS == 1)
		{
			pShowPrice(a1, g_ZtText.GetText(177), Bonus); 
		}
		else
		{
			pShowPrice(a1, g_ZtText.GetText(178), Bonus); 
		}
		
//#endif
		return;
	}

	if(g_PersonalShopZt.bDPrice[2] == true)
	{
		g_PersonalShopZt.bDPrice[2] = false;
		pShowPrice(a1, g_ZtText.GetText(179), Bless); 
		return;
	}

	if(g_PersonalShopZt.bDPrice[3] == true)
	{
		g_PersonalShopZt.bDPrice[3] = false;
		pShowPrice(a1, g_ZtText.GetText(180), Soul); 
		return;
	}

	if(g_PersonalShopZt.bDPrice[4] == true)
	{
		g_PersonalShopZt.bDPrice[4] = false;
		pShowPrice(a1, g_ZtText.GetText(181), Chaos); 
		return;
	}

	if(g_PersonalShopZt.bDPrice[5] == true)
	{
		g_PersonalShopZt.bDPrice[5] = false;
		pShowPrice(a1, g_ZtText.GetText(182), Life); 
		return;
	}

	#if(DEV_PERSONAL_CREDIT)
	if(g_PersonalShopZt.bDPrice[6] == true)
	{
		g_PersonalShopZt.bDPrice[6] = false;
		if(g_PersonalShopZt.iPERSONAL_CREDIT)
		{
			pShowPrice(a1, "Price: %d Credit", Credit); 
		}
		return;
	}
	#endif
}
// ----------------------------------------------------------------------------------------------

void PersonalShopZt::Init()
{
	this->ACTIVE = false;
	this->iPERSONAL_BONUS = false;

	ZeroMemory(&this->PShop,sizeof(this->PShop));
	this->Page = 0;
	this->TotalShop = 0;
	this->aTargetIndex = -1;
	ZeroMemory(&this->TargetName,sizeof(this->TargetName));

	this->ActivePrice = 1;
	this->PriceBek = 1;

	ZeroMemory(g_PersonalShopZt.ZenText,sizeof(g_PersonalShopZt.ZenText));
	ZeroMemory(g_PersonalShopZt.BonusText,sizeof(g_PersonalShopZt.BonusText));
	ZeroMemory(g_PersonalShopZt.BlessText,sizeof(g_PersonalShopZt.BlessText));
	ZeroMemory(g_PersonalShopZt.SoulText,sizeof(g_PersonalShopZt.SoulText));
	ZeroMemory(g_PersonalShopZt.ChaosText,sizeof(g_PersonalShopZt.ChaosText));
	ZeroMemory(g_PersonalShopZt.LifeText,sizeof(g_PersonalShopZt.LifeText));
	#if(DEV_PERSONAL_CREDIT)
	ZeroMemory(g_PersonalShopZt.CreditText,sizeof(g_PersonalShopZt.CreditText));
	#endif

	sprintf(g_PersonalShopZt.ZenText,"0");
	sprintf(g_PersonalShopZt.BonusText,"0");
	sprintf(g_PersonalShopZt.BlessText,"0");
	sprintf(g_PersonalShopZt.SoulText,"0");
	sprintf(g_PersonalShopZt.ChaosText,"0");
	sprintf(g_PersonalShopZt.LifeText,"0");
	#if(DEV_PERSONAL_CREDIT)
	sprintf(g_PersonalShopZt.CreditText,"0");
	#endif
}
// ----------------------------------------------------------------------------------------------

char PersonalShopZt::RightClickItemPersonalStore(LPVOID a1)
{
	g_PersonalShopZt.ActivePrice = 1;

	ZeroMemory(g_PersonalShopZt.ZenText,sizeof(g_PersonalShopZt.ZenText));
	ZeroMemory(g_PersonalShopZt.BonusText,sizeof(g_PersonalShopZt.BonusText));
	ZeroMemory(g_PersonalShopZt.BlessText,sizeof(g_PersonalShopZt.BlessText));
	ZeroMemory(g_PersonalShopZt.SoulText,sizeof(g_PersonalShopZt.SoulText));
	ZeroMemory(g_PersonalShopZt.ChaosText,sizeof(g_PersonalShopZt.ChaosText));
	ZeroMemory(g_PersonalShopZt.LifeText,sizeof(g_PersonalShopZt.LifeText));
	#if(DEV_PERSONAL_CREDIT)
	ZeroMemory(g_PersonalShopZt.CreditText,sizeof(g_PersonalShopZt.CreditText));
	#endif

	sprintf(g_PersonalShopZt.ZenText,"0");
	sprintf(g_PersonalShopZt.BonusText,"0");
	sprintf(g_PersonalShopZt.BlessText,"0");
	sprintf(g_PersonalShopZt.SoulText,"0");
	sprintf(g_PersonalShopZt.ChaosText,"0");
	sprintf(g_PersonalShopZt.LifeText,"0");
	#if(DEV_PERSONAL_CREDIT)
	sprintf(g_PersonalShopZt.CreditText,"0");
	#endif

	gInterface.OpenWindowZt(ztWinPersonalPrice);

	return 1;
}
// ----------------------------------------------------------------------------------------------

void PersonalShopZt::Load()
{
	this->Init();
	
	SetOp((LPVOID)0x007E44F1, (LPVOID)&this->ShowPrice, ASM::CALL);
	SetOp((LPVOID)0x007E449F, (LPVOID)&this->GetPSItemPos, ASM::CALL);

	SetRange((LPVOID)0x007E4572, 5, ASM::NOP);
	SetOp((LPVOID)0x007E4572, (LPVOID)&ConutPriceDraw, ASM::JMP);

	//SetRange((LPVOID)0x0079AD99, 6, ASM::NOP);
	//SetOp((LPVOID)0x0079AD9F, &PSShopVieweFix, ASM::JMP);
	SetRange((LPVOID)0x0079AD99, 191, ASM::NOP);
	SetOp((LPVOID)0x0079AD9F, &PSShopVieweFix, ASM::CALL);
	// -----

	SetOp((LPVOID)0x00841744, &this->RightClickItemPersonalStore, ASM::CALL);
	SetOp((LPVOID)0x008414B7, &this->RightClickItemPersonalStore, ASM::CALL);
	SetOp((LPVOID)0x008415F3, &this->RightClickItemPersonalStore, ASM::CALL);
	SetOp((LPVOID)0x005D5950, &this->RightClickItemPersonalStore, ASM::CALL);

	SetByte((LPVOID)(0x007E4508+7), 0x04);
	SetByte((LPVOID)(0x007E4524+7), 0x04);
	SetByte((LPVOID)(0x007E4550+7), 0x04);

	SetOp((LPVOID)0x00841A0A, &this->CheckPersonalPrice, ASM::CALL);	

	this->ACTIVE = true;
}
// ----------------------------------------------------------------------------------------------

void PersonalShopZt::LoadImages()
{
	pLoadImage("ZtTeam\\Interface\\PartySearch_Title.tga", zt_PEROSNAL_SEATCH_TITLE, 0x2601, 0x2900, 1, 0);
}
// ----------------------------------------------------------------------------------------------

void PersonalShopZt::BindImages()
{
	gInterface.BindObject(ePT_PERSONAL_SEARCH_MAIN, 0x7A5A, 222, 345.0, -1, -1);
	gInterface.BindObject(ePT_PERSONAL_SEARCH_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(ePT_PERSONAL_SEARCH_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(ePT_PERSONAL_SEARCH_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(ePT_PERSONAL_SEARCH_DIV, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(ePT_PERSONAL_SEARCH_CLOSE, 0x7EC5, 36, 29, -1, -1);
	gInterface.BindObject(ePT_PERSONAL_SEARCH_L, 0x7BAA, 17, 17, -1, -1);
	gInterface.BindObject(ePT_PERSONAL_SEARCH_R, 0x7BAB, 17, 17, -1, -1);

	gInterface.BindObject(ePT_PERSONAL_SEARCH_PAGEUP1, zt_PEROSNAL_SEATCH_TITLE, 170, 21, -1, -1);
	gInterface.BindObject(ePT_PERSONAL_SEARCH_PAGEUP2, zt_PEROSNAL_SEATCH_TITLE, 170, 21, -1, -1);
	gInterface.BindObject(ePT_PERSONAL_SEARCH_PAGEUP3, zt_PEROSNAL_SEATCH_TITLE, 170, 21, -1, -1);
	gInterface.BindObject(ePT_PERSONAL_SEARCH_PAGEUP4, zt_PEROSNAL_SEATCH_TITLE, 170, 21, -1, -1);
	gInterface.BindObject(ePT_PERSONAL_SEARCH_PAGEUP5, zt_PEROSNAL_SEATCH_TITLE, 170, 21, -1, -1);
	gInterface.BindObject(ePT_PERSONAL_SEARCH_PAGEUP6, zt_PEROSNAL_SEATCH_TITLE, 170, 21, -1, -1);
	gInterface.BindObject(ePT_PERSONAL_SEARCH_PAGEUP7, zt_PEROSNAL_SEATCH_TITLE, 170, 21, -1, -1);
	gInterface.BindObject(ePT_PERSONAL_SEARCH_PAGEUP8, zt_PEROSNAL_SEATCH_TITLE, 170, 21, -1, -1);
	gInterface.BindObject(ePT_PERSONAL_SEARCH_PAGEUP9, zt_PEROSNAL_SEATCH_TITLE, 170, 21, -1, -1);
	gInterface.BindObject(ePT_PERSONAL_SEARCH_PAGEUP10, zt_PEROSNAL_SEATCH_TITLE, 170, 21, -1, -1);

	// ----
	#if(DEV_PERSONAL_CREDIT)
	gInterface.BindObject(ePS_PRICE_MAIN, 0x7A5A, 222, 182 + 20 + 20, -1, -1);
	#else
	gInterface.BindObject(ePS_PRICE_MAIN, 0x7A5A, 222, 182 + 20, -1, -1);
	#endif
	gInterface.BindObject(ePS_PRICE_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(ePS_PRICE_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(ePS_PRICE_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(ePS_PRICE_DIV, 0x7A62, 223, 21, -1, -1);

	gInterface.BindObject(ePS_PRICE_ZEN, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(ePS_PRICE_BONUS, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(ePS_PRICE_BLESS, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(ePS_PRICE_SOUL, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(ePS_PRICE_CHAOS, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(ePS_PRICE_LIFE, 0x7AA3, 170, 21, -1, -1);
	#if(DEV_PERSONAL_CREDIT)
	gInterface.BindObject(ePS_PRICE_CREDIT, 0x7AA3, 170, 21, -1, -1);
	#endif

	gInterface.BindObject(ePS_PRICE_OK, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(ePS_PRICE_CLOSE, 0x7A5F, 62, 27, -1, -1);
}
// ----------------------------------------------------------------------------------------------

void PersonalShopZt::Draw()
{
	if(!this->ACTIVE)
	{
		return;
	}

	if( gInterface.CheckWindow(Store) )
	{
		g_PersonalShopZt.aTargetIndex = pGameIndex;
		return;
	}

	if( gInterface.CheckWindow(OtherStore) )
	{
		return;
	}

	if(!gInterface.CheckWindowZt(ztWinPersonalSearch))
	{
		return;
	}

	pSetCursorFocus = true;

	// ----
	DWORD ItemNameColor		= eWhite;
	float MainWidth			= 230.0;
	float MainHeight		= 350.0;
	float StartY			= 50;	//100
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);

	float ContentX          = StartX;
	float ContentY			= StartY;

	// ----
	gInterface.DrawGUI(ePT_PERSONAL_SEARCH_MAIN, StartX, StartY + 2);
	gInterface.DrawGUI(ePT_PERSONAL_SEARCH_TITLE, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(ePT_PERSONAL_SEARCH_FRAME, StartX, StartY + 67.0, 16);
	gInterface.DrawGUI(ePT_PERSONAL_SEARCH_FOOTER, StartX, StartY);
	gInterface.DrawGUI(ePT_PERSONAL_SEARCH_CLOSE, StartX + MainWidth - gInterface.Data[ePT_PERSONAL_SEARCH_CLOSE].Width, ContentY);
	// ----
	if( gInterface.IsWorkZone(ePT_PERSONAL_SEARCH_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[ePT_PERSONAL_SEARCH_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(ePT_PERSONAL_SEARCH_CLOSE, gInterface.Data[ePT_PERSONAL_SEARCH_CLOSE].X, gInterface.Data[ePT_PERSONAL_SEARCH_CLOSE].Y, Color);
		gInterface.DrawToolTip(gInterface.Data[ePT_PERSONAL_SEARCH_CLOSE].X + 5, gInterface.Data[ePT_PERSONAL_SEARCH_CLOSE].Y + 25, g_ZtText.GetText(24));
	}
	// ----

	gInterface.DrawFormat(eGold, ContentX + 10, ContentY + 10, 210, 3, g_ZtText.GetText(138));

	// -> Content

	gInterface.DrawGUI(ePT_PERSONAL_SEARCH_DIV, ContentX, ContentY + 40);

	float ListDrawX = ContentX + 20 + 15;
	float ListDrawY = ContentY + 10 + 25;

	gInterface.DrawFormat(eGold, ListDrawX, ListDrawY + 20, 100, 1, g_ZtText.GetText(28));

	ListDrawX += 50;
	gInterface.DrawFormat(eGold, ListDrawX, ListDrawY + 20, 100, 1, g_ZtText.GetText(138));

	ListDrawX += 50;

	ListDrawX += 15;

	ListDrawX += 20;

	ListDrawX += 35;

	gInterface.DrawGUI(ePT_PERSONAL_SEARCH_DIV, ContentX, ListDrawY + 23);

	// ----------

	// -> Draw Listing

	for(int i = 0; i < 10; i++)
	{

		if(this->PShop[i].Name[0] == NULL) continue;

		gInterface.DrawGUI(ePT_PERSONAL_SEARCH_PAGEUP1 + i, ContentX + 10 + 18, ContentY + 77 + i * 22);

		ListDrawX = ContentX + 20 + 18;
		ListDrawY = ContentY + 60 + i * 22;

		gInterface.DrawFormat(eYellow, ListDrawX - 7, ListDrawY + 21, 100, 1, this->PShop[i].Name);

		ListDrawX += 50;
		gInterface.DrawFormat(eWhite, ListDrawX, ListDrawY + 21, 100, 1, "%s", this->PShop[i].PersonalText);

		ListDrawX += 50;

		ListDrawX += 15;

		ListDrawX += 20;

		ListDrawX += 27;

		ListDrawX += 10;

		if(gInterface.IsWorkZone(ePT_PERSONAL_SEARCH_PAGEUP1 + i))
		{
			DWORD Color = eGray100;
			// ----
			if( gInterface.Data[ePT_PERSONAL_SEARCH_PAGEUP1 + i].OnClick )
			{
				Color = eGray150;
			}
			// ----
			gInterface.DrawColoredGUI(ePT_PERSONAL_SEARCH_PAGEUP1 + i, gInterface.Data[ePT_PERSONAL_SEARCH_PAGEUP1 + i].X, gInterface.Data[ePT_PERSONAL_SEARCH_PAGEUP1 + i].Y, Color);
		}

	}

	// -----------

	// -> Page Draw

	gInterface.DrawGUI(ePT_PERSONAL_SEARCH_DIV, ContentX, gInterface.Data[ePT_PERSONAL_SEARCH_FOOTER].Y - 10);

	gInterface.DrawGUI(ePT_PERSONAL_SEARCH_L, ContentX + 80, ContentY + 325);
	gInterface.DrawGUI(ePT_PERSONAL_SEARCH_R, ContentX + 130, ContentY + 325);

	if(gInterface.IsWorkZone(ePT_PERSONAL_SEARCH_L))
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[ePT_PERSONAL_SEARCH_L].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(ePT_PERSONAL_SEARCH_L, gInterface.Data[ePT_PERSONAL_SEARCH_L].X, gInterface.Data[ePT_PERSONAL_SEARCH_L].Y, Color);
	}

	if(gInterface.IsWorkZone(ePT_PERSONAL_SEARCH_R))
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[ePT_PERSONAL_SEARCH_R].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(ePT_PERSONAL_SEARCH_R, gInterface.Data[ePT_PERSONAL_SEARCH_R].X, gInterface.Data[ePT_PERSONAL_SEARCH_R].Y, Color);
	}

	gInterface.DrawFormat(eGold, ContentX+97, ContentY + 329, 100, 1, g_ZtText.GetText(34), this->Page+1,(this->TotalShop-1)/10+1);
}
// ----------------------------------------------------------------------------------------------

void PersonalShopZt::DrawPrice()
{
	if(!this->ACTIVE)
	{
		return;
	}


	if(!gInterface.CheckWindowZt(ztWinPersonalPrice))
	{
		return;
	}

	pSetCursorFocus = true;

	DWORD ItemNameColor		= eWhite;
	float MainWidth			= 230.0;
	float MainHeight		= 250.0;
	float StartY			= 100;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);

	float ContentX          = StartX;
	float ContentY			= StartY;
	// ----
	gInterface.DrawGUI(ePS_PRICE_MAIN, StartX, StartY + 2);
	gInterface.DrawGUI(ePS_PRICE_TITLE, StartX, StartY);
	#if(DEV_PERSONAL_CREDIT)
	StartY = gInterface.DrawRepeatGUI(ePS_PRICE_FRAME, StartX, StartY + 67.0, 8);
	#else
	StartY = gInterface.DrawRepeatGUI(ePS_PRICE_FRAME, StartX, StartY + 67.0, 6);
	#endif
	gInterface.DrawGUI(ePS_PRICE_FOOTER, StartX, StartY);
	// ----
	gInterface.DrawFormat(eGold, ContentX + 10, ContentY + 10, 210, 3, g_ZtText.GetText(139));
	// ----
	ContentY += 40;

	if(!g_ZtLicense.CheckUser(eZtUB::Chebuk))
	{
		gInterface.DrawGUI(ePS_PRICE_ZEN, ContentX + 30, ContentY);
		gInterface.DrawFormat(eGold, ContentX + 35, ContentY + 5, 70, 3, g_ZtText.GetText(47));
		gInterface.DrawFormat(eWhite, ContentX + 135, ContentY + 5, 70, 1, this->ZenText);
	}
	// ----
//#if(PERSONAL_BONUS==TRUE)
	if(g_PersonalShopZt.iPERSONAL_BONUS == 1)
	{
		ContentY += 20;
		gInterface.DrawGUI(ePS_PRICE_BONUS, ContentX + 30, ContentY);
		gInterface.DrawFormat(eGold, ContentX + 35, ContentY + 5, 70, 3, g_ZtText.GetText(46));
		gInterface.DrawFormat(eWhite, ContentX + 135, ContentY + 5, 70, 1, this->BonusText);
	}
	else if(g_PersonalShopZt.iPERSONAL_BONUS == 2)
	{
		ContentY += 20;
		gInterface.DrawGUI(ePS_PRICE_BONUS, ContentX + 30, ContentY);
		gInterface.DrawFormat(eGold, ContentX + 35, ContentY + 5, 70, 3, g_ZtText.GetText(140));
		gInterface.DrawFormat(eWhite, ContentX + 135, ContentY + 5, 70, 1, this->BonusText);
	}
//#endif
	// ----
	ContentY += 20;
	gInterface.DrawGUI(ePS_PRICE_BLESS, ContentX + 30, ContentY);
	gInterface.DrawFormat(eGold, ContentX + 35, ContentY + 5, 70, 3, g_ZtText.GetText(42));
	gInterface.DrawFormat(eWhite, ContentX + 135, ContentY + 5, 70, 1, this->BlessText);
	// ----
	ContentY += 20;
	gInterface.DrawGUI(ePS_PRICE_SOUL, ContentX + 30, ContentY);
	gInterface.DrawFormat(eGold, ContentX + 35, ContentY + 5, 70, 3, g_ZtText.GetText(43));
	gInterface.DrawFormat(eWhite, ContentX + 135, ContentY + 5, 70, 1, this->SoulText);
	// ----
	ContentY += 20;
	gInterface.DrawGUI(ePS_PRICE_CHAOS, ContentX + 30, ContentY);
	gInterface.DrawFormat(eGold, ContentX + 35, ContentY + 5, 70, 3, g_ZtText.GetText(41));
	gInterface.DrawFormat(eWhite, ContentX + 135, ContentY + 5, 70, 1, this->ChaosText);

	ContentY += 20;
	gInterface.DrawGUI(ePS_PRICE_LIFE, ContentX + 30, ContentY);
	gInterface.DrawFormat(eGold, ContentX + 35, ContentY + 5, 70, 3, g_ZtText.GetText(44));
	gInterface.DrawFormat(eWhite, ContentX + 135, ContentY + 5, 70, 1, this->LifeText);

	#if(DEV_PERSONAL_CREDIT)
	if(g_PersonalShopZt.iPERSONAL_CREDIT)
	{
		ContentY += 20;
		gInterface.DrawGUI(ePS_PRICE_CREDIT, ContentX + 30, ContentY);
		gInterface.DrawFormat(eGold, ContentX + 35, ContentY + 5, 70, 3, "Credit:");
		gInterface.DrawFormat(eWhite, ContentX + 135, ContentY + 5, 70, 1, this->CreditText);
	}
	#endif

	if(this->ActivePrice == ePSzen)
	{
		DWORD Color = eGray100;
		gInterface.DrawColoredGUI(ePS_PRICE_ZEN, gInterface.Data[ePS_PRICE_ZEN].X, gInterface.Data[ePS_PRICE_ZEN].Y, Color);
	}
//#if(PERSONAL_BONUS==TRUE)
	if(g_PersonalShopZt.iPERSONAL_BONUS)
	{
		if(this->ActivePrice == ePSBonus)
		{
			DWORD Color = eGray100;
			gInterface.DrawColoredGUI(ePS_PRICE_BONUS, gInterface.Data[ePS_PRICE_BONUS].X, gInterface.Data[ePS_PRICE_BONUS].Y, Color);
		}
	}
//#endif
	if(this->ActivePrice == ePSBless)
	{
		DWORD Color = eGray100;
		gInterface.DrawColoredGUI(ePS_PRICE_BLESS, gInterface.Data[ePS_PRICE_BLESS].X, gInterface.Data[ePS_PRICE_BLESS].Y, Color);
	}
	if(this->ActivePrice == ePSSoul)
	{
		DWORD Color = eGray100;
		gInterface.DrawColoredGUI(ePS_PRICE_SOUL, gInterface.Data[ePS_PRICE_SOUL].X, gInterface.Data[ePS_PRICE_SOUL].Y, Color);
	}
	if(this->ActivePrice == ePSChaos)
	{
		DWORD Color = eGray100;
		gInterface.DrawColoredGUI(ePS_PRICE_CHAOS, gInterface.Data[ePS_PRICE_CHAOS].X, gInterface.Data[ePS_PRICE_CHAOS].Y, Color);
	}
	if(this->ActivePrice == ePSLife)
	{
		DWORD Color = eGray100;
		gInterface.DrawColoredGUI(ePS_PRICE_LIFE, gInterface.Data[ePS_PRICE_LIFE].X, gInterface.Data[ePS_PRICE_LIFE].Y, Color);
	}
	#if(DEV_PERSONAL_CREDIT)
	if(g_PersonalShopZt.iPERSONAL_CREDIT)
	{
		if(this->ActivePrice == ePSCredit)
		{
			DWORD Color = eGray100;
			gInterface.DrawColoredGUI(ePS_PRICE_CREDIT, gInterface.Data[ePS_PRICE_CREDIT].X, gInterface.Data[ePS_PRICE_CREDIT].Y, Color);
		}
	}
	#endif

	// -> Button
	ContentY += 30;
	gInterface.DrawGUI(ePS_PRICE_OK, StartX+30, ContentY - 5);
	gInterface.DrawFormat(eWhite, StartX + 35, ContentY+5, 50, 3, g_ZtText.GetText(120));

	if( gInterface.IsWorkZone(ePS_PRICE_OK) )
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[ePS_PRICE_OK].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(ePS_PRICE_OK, gInterface.Data[ePS_PRICE_OK].X, gInterface.Data[ePS_PRICE_OK].Y, Color);
	}
	// ---- 
	gInterface.DrawGUI(ePS_PRICE_CLOSE, StartX + 70 + 62, ContentY - 5 );
	gInterface.DrawFormat(eWhite, StartX + 75 + 62, ContentY+5, 50, 3, g_ZtText.GetText(129));

	if( gInterface.IsWorkZone(ePS_PRICE_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[ePS_PRICE_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(ePS_PRICE_CLOSE, gInterface.Data[ePS_PRICE_CLOSE].X, gInterface.Data[ePS_PRICE_CLOSE].Y, Color);
	}
}
// ----------------------------------------------------------------------------------------------

void PersonalShopZt::Button(DWORD Event)
{
	if(!this->ACTIVE)
	{
		return;
	}

	if( gInterface.CheckWindow(Store) || gInterface.CheckWindow(OtherStore) )
	{
		return;
	}

	if(!gInterface.CheckWindowZt(ztWinPersonalSearch))
	{
		return;
	}

	if(gInterface.Button(Event, ztWinPersonalSearch, ePT_PERSONAL_SEARCH_CLOSE, 0))
	{
		gInterface.CloseWindowZt(ztWinPersonalSearch);
	}

	if( gInterface.Button(Event, ztWinPersonalSearch, ePT_PERSONAL_SEARCH_L, false ) )
	{
		if(this->Page != 0)
		{
			this->Page--;
			this->CG_Send();
		}
		return;
	}
	else if( gInterface.Button(Event, ztWinPersonalSearch, ePT_PERSONAL_SEARCH_R, false ) )
	{
		if(this->Page != (this->TotalShop-1)/10)
		{
			 this->Page++;
			 this->CG_Send();
		}
		return;
	}

	// --------

	if(gInterface.CheckWindowZt(ztWinPersonalSearch))
	{
		for(int i = 0; i < 10; i++)
		{
			if(gInterface.Button(Event, ztWinPersonalSearch, ePT_PERSONAL_SEARCH_PAGEUP1 + i, false))
			{
				PMSG_REQ_BUYLIST_FROM_PSHOP pReq;
				pReq.h.set((LPBYTE)&pReq, 0x3F, 0x05, sizeof(pReq));

				pReq.NumberH = SET_NUMBERH(this->PShop[i].aIndex);
				pReq.NumberL = SET_NUMBERL(this->PShop[i].aIndex);

				memcpy(pReq.btName, this->PShop[i].Name, 10);

				gProtocol.DataSend((LPBYTE)&pReq, pReq.h.size);
			}
		}
	}
}
// ----------------------------------------------------------------------------------------------

void PersonalShopZt::ButtonPrice(DWORD Event)
{
	if(!this->ACTIVE)
	{
		return;
	}

	if(!gInterface.CheckWindowZt(ztWinPersonalPrice))
	{
		return;
	}

	if(!g_ZtLicense.CheckUser(eZtUB::Chebuk) )
	{
		if( gInterface.Button(Event, ztWinPersonalPrice, ePS_PRICE_ZEN, false ) )
		{
			this->ActivePrice = 1;
			return;
		}
	}
//#if(PERSONAL_BONUS==TRUE)
	if(g_PersonalShopZt.iPERSONAL_BONUS)
	{
		if( gInterface.Button(Event, ztWinPersonalPrice, ePS_PRICE_BONUS, false ) )
		{
			this->ActivePrice = 2;
			return;
		}
	}
//#endif
	if( gInterface.Button(Event, ztWinPersonalPrice, ePS_PRICE_BLESS, false ) )
	{
		this->ActivePrice = 3;
		return;
	}
	if( gInterface.Button(Event, ztWinPersonalPrice, ePS_PRICE_SOUL, false ) )
	{
		this->ActivePrice = 4;
		return;
	}
	if( gInterface.Button(Event, ztWinPersonalPrice, ePS_PRICE_CHAOS, false ) )
	{
		this->ActivePrice = 5;
		return;
	}
	if( gInterface.Button(Event, ztWinPersonalPrice, ePS_PRICE_LIFE, false ) )
	{
		this->ActivePrice = 6;
		return;
	}
	#if(DEV_PERSONAL_CREDIT)
	if(g_PersonalShopZt.iPERSONAL_CREDIT)
	{
		if( gInterface.Button(Event, ztWinPersonalPrice, ePS_PRICE_CREDIT, false ) )
		{
			this->ActivePrice = 7;
			return;
		}
	}
	#endif

	if( gInterface.Button(Event, ztWinPersonalPrice, ePS_PRICE_CLOSE, false ) )
	{
		gInterface.CloseWindowZt(ztWinPersonalPrice);

		ZeroMemory(g_PersonalShopZt.ZenText,sizeof(g_PersonalShopZt.ZenText));
		ZeroMemory(g_PersonalShopZt.BonusText,sizeof(g_PersonalShopZt.BonusText));
		ZeroMemory(g_PersonalShopZt.BlessText,sizeof(g_PersonalShopZt.BlessText));
		ZeroMemory(g_PersonalShopZt.SoulText,sizeof(g_PersonalShopZt.SoulText));
		ZeroMemory(g_PersonalShopZt.ChaosText,sizeof(g_PersonalShopZt.ChaosText));
		ZeroMemory(g_PersonalShopZt.LifeText,sizeof(g_PersonalShopZt.LifeText));
		#if(DEV_PERSONAL_CREDIT)
		ZeroMemory(g_PersonalShopZt.CreditText,sizeof(g_PersonalShopZt.CreditText));
		#endif

		sprintf(g_PersonalShopZt.ZenText,"0");
		sprintf(g_PersonalShopZt.BonusText,"0");
		sprintf(g_PersonalShopZt.BlessText,"0");
		sprintf(g_PersonalShopZt.SoulText,"0");
		sprintf(g_PersonalShopZt.ChaosText,"0");
		sprintf(g_PersonalShopZt.LifeText,"0");
		#if(DEV_PERSONAL_CREDIT)
		sprintf(g_PersonalShopZt.CreditText, "0");
		#endif

		this->PStorePrice();
		return;
	}
	if( gInterface.Button(Event, ztWinPersonalPrice, ePS_PRICE_OK, false ) )
	{
		gInterface.CloseWindowZt(ztWinPersonalPrice);
		this->PStorePrice();
	}
}
// ----------------------------------------------------------------------------------------------

void PersonalShopZt::Key(DWORD Event)
{
	if(!this->ACTIVE)
	{
		return;
	}

	if(!gInterface.CheckWindowZt(ztWinPersonalPrice))
	{
		return;
	}

	if(ActivePrice == 1)
	{
		gInterface.KeyBoxEvent(Event, this->ZenText, 9);
	}
//#if(PERSONAL_BONUS==TRUE)
	if(g_PersonalShopZt.iPERSONAL_BONUS)
	{
		if(ActivePrice == 2)
		{
			gInterface.KeyBoxEvent(Event, this->BonusText, 9);
		}	
	}
//#endif
	if(ActivePrice == 3)
	{
		gInterface.KeyBoxEvent(Event, this->BlessText, 4);
	}	
	if(ActivePrice == 4)
	{
		gInterface.KeyBoxEvent(Event, this->SoulText, 4);
	}	
	if(ActivePrice == 5)
	{
		gInterface.KeyBoxEvent(Event, this->ChaosText, 4);
	}	
	if(ActivePrice == 6)
	{
		gInterface.KeyBoxEvent(Event, this->LifeText, 4);
	}	
	#if(DEV_PERSONAL_CREDIT)
	if(g_PersonalShopZt.iPERSONAL_CREDIT)
	{
		if(ActivePrice == 7)
		{
			gInterface.KeyBoxEvent(Event, this->CreditText, 4);
		}	
	}
	#endif
}
// ----------------------------------------------------------------------------------------------

void PersonalShopZt::GC_Recv(LPBYTE aRecv)
{
	if(!this->ACTIVE)
	{
		return;
	}

	ZeroMemory(&this->PShop,sizeof(this->PShop));
	int datasize = 8;
	int ztcount = MAKE_NUMBERW(aRecv[datasize-3], aRecv[datasize-2]);
	this->TotalShop = ztcount;

	int SendCount = aRecv[datasize-1];

	for (int n = 0; n < SendCount; n++)
	{
		GC_PersonalShopInfo ap;
		memcpy(&ap,&aRecv[datasize],sizeof(ap));

		this->PShop[n].aIndex = ap.aIndex;
		strncpy(this->PShop[n].Name, ap.Name, 10);
		strncpy(this->PShop[n].PersonalText, ap.PersonalText, 36);
		this->PShop[n].Value = ap.Value;

		datasize += sizeof(ap);
	}

	if(!gInterface.CheckWindowZt(ztWinPersonalSearch))
	{
		gInterface.OpenWindowZt(ztWinPersonalSearch);
	}
}
// ----------------------------------------------------------------------------------------------

void PersonalShopZt::CG_Send()
{
	CG_PersonalPage pRequest;
	pRequest.h.set((LPBYTE)&pRequest, 0xFB, 0x0E, sizeof(pRequest));
	pRequest.Page = this->Page;
	gProtocol.DataSend((LPBYTE)&pRequest, pRequest.h.size);
}
// ----------------------------------------------------------------------------------------------

void PersonalShopZt::GC_PSRecv(PMSG_ANS_BUYLIST_FROM_PSHOP* aRecv)
{
	this->aTargetIndex = MAKE_NUMBERW(aRecv->NumberH, aRecv->NumberL);
	memcpy(this->TargetName, aRecv->btName, 10);
}
// ----------------------------------------------------------------------------------------------

void PersonalShopZt::PStorePrice()
{
	LPVOID v3; // eax@7
	int v4; // eax@7
	LPVOID v5; // eax@7
	int v6; // eax@7
	int v7; // ST00_4@12
	int v8; // eax@13
	int v9; // eax@13
	int v10; // eax@13
	LPVOID v11; // eax@15
	int v12; // eax@15
	LPVOID v13; // eax@18
	int v14; // eax@18
	LPVOID v15; // eax@18
	void *v16; // eax@18
	LPVOID v17; // eax@19
	int v18; // esi@22
	LPVOID v19; // eax@22
	int v20; // eax@22
	int v21; // eax@24
	LPVOID v22; // eax@25
	int v23; // eax@25
	int v24; // eax@25
	int v25; // eax@25
	LPVOID v26; // eax@26
	int v27; // eax@26
	void *v28; // eax@26
	char v29; // [sp+8h] [bp-2AD0h]@13
	char v30; // [sp+24h] [bp-2AB4h]@13
	char v31; // [sp+40h] [bp-2A98h]@12
	char v32; // [sp+44h] [bp-2A94h]@25
	char v33; // [sp+853h] [bp-2285h]@25
	char v34; // [sp+854h] [bp-2284h]@23
	char v35; // [sp+1063h] [bp-1A75h]@23
	char v36; // [sp+1064h] [bp-1A74h]@21
	char v37; // [sp+1873h] [bp-1265h]@21
	char v38; // [sp+1874h] [bp-1264h]@19
	char v39; // [sp+2083h] [bp-A55h]@19
	int v40; // [sp+2084h] [bp-A54h]@18
	int v41; // [sp+2088h] [bp-A50h]@18
	char v42; // [sp+208Ch] [bp-A4Ch]@16
	int v43; // [sp+2898h] [bp-240h]@17
	int v44; // [sp+289Ch] [bp-23Ch]@17
	int v45; // [sp+28A0h] [bp-238h]@17
	char v46; // [sp+28A4h] [bp-234h]@13
	char v47; // [sp+28A5h] [bp-233h]@13
	int v48; // [sp+29A8h] [bp-130h]@12
	char v49; // [sp+29B7h] [bp-121h]@8
	int v50; // [sp+29B8h] [bp-120h]@3
	char v51; // [sp+29BCh] [bp-11Ch]@1
	char v52; // [sp+29BDh] [bp-11Bh]@1
	int v53; // [sp+2AC0h] [bp-18h]@5
	int v54; // [sp+2AC4h] [bp-14h]@5
	int v55; // [sp+2AC8h] [bp-10h]@1
	int v56; // [sp+2AD4h] [bp-4h]@12

	g_PersonalShopZt.aTargetIndex = pGameIndex;

	int ZenPrice = atoi(g_PersonalShopZt.ZenText);
	int BonusPrice = atoi(g_PersonalShopZt.BonusText);
	int BlessPrice = atoi(g_PersonalShopZt.BlessText);
	int SoulPrice = atoi(g_PersonalShopZt.SoulText);
	int ChaosPrice = atoi(g_PersonalShopZt.ChaosText);
	int LifePrice = atoi(g_PersonalShopZt.LifeText);
	#if(DEV_PERSONAL_CREDIT)
	int CreditPrice = atoi(g_PersonalShopZt.CreditText);
	#endif

	v54 = sub_7DCFA0();
	v53 = 0;
	if ( v54 )
	{
		v53 = sub_7D92E0((LPVOID)v54);
	}
	else
	{
		v3 = sub_860FC0();
        v4 = sub_8612B0(sub_860FC0());
        v54 = sub_668720((LPVOID)v4);
        v5 = sub_860FC0();
        v6 = sub_8612B0(v5);
        v53 = sub_840DF0((LPVOID)v6, v54);
    }

    v49 = 0;

    if ( v53 && v50 < sub_58E3B0(v53, 2) )
	{
		v49 = 1;
	}

    v11 = sub_860FC0();
    v12 = sub_8612B0(v11);
    if ( sub_841200((LPVOID)v12) == 1 )
    {
		PMSG_REQ_PSHOP_SETITEMPRICE pReq;
		pReq.h.set((LPBYTE)&pReq, 0x3F, 0x03, sizeof(pReq));
		gProtocol.DataSend((LPBYTE)&pReq, pReq.h.size);
    }

    v44 = sub_7DCFA0();
    v43 = -1;
    v45 = -1;

    if ( v44 )
	{
		v41 = sub_7D92E0((LPVOID)v44);
		v43 = sub_7D9390((LPVOID)v44);
		v13 = sub_860FC0();
		v14 = sub_8612B0(v13);
		v45 = sub_6688B0((LPVOID)v14);
		v54 = sub_7D92C0((LPVOID)v44);
		v15 = sub_860FC0();
		v16 = (void *)sub_861110(v15);
		v40 = sub_83C5C0((LPVOID)v16, v54);
		if ( v40 == -1 )
		{
			if ( sub_7D92C0((LPVOID)v44) )
			{
				v18 = sub_7D92C0((LPVOID)v44);
				v19 = sub_860FC0();
				v20 = sub_8612B0(v19);
				if ( v18 == sub_668700((LPVOID)v20) )
				{
					v35 = v43 - 52;

					g_PersonalShopZt.SendPrice(v35, ZenPrice, BonusPrice, BlessPrice, SoulPrice, ChaosPrice, LifePrice, CreditPrice);
					//g_PersonalShopZt.PriceInvenory(v43, ZenPrice, BonusPrice, BlessPrice, SoulPrice, ChaosPrice, LifePrice);
					sub_5BD850(4, v43 + 12, v41, 4, v45 - 52);
				}
			}
			else
			{
				v37 = v43;

				g_PersonalShopZt.SendPrice(v37, ZenPrice, BonusPrice, BlessPrice, SoulPrice, ChaosPrice, LifePrice, CreditPrice);
				//g_PersonalShopZt.PriceInvenory(v43, ZenPrice, BonusPrice, BlessPrice, SoulPrice, ChaosPrice, LifePrice);
				sub_5BD850(0, v43, v41, 4, v45 - 52);
			}
		}
		else
		{
			v54 = v40;
			v53 = v43;
			v17 = sub_860FC0();
			sub_861110(v17);
			v43 = sub_83C330(v53, v54);
			v39 = v43 + 12;

			g_PersonalShopZt.SendPrice(v39, ZenPrice, BonusPrice, BlessPrice, SoulPrice, ChaosPrice, LifePrice, CreditPrice);

			sub_5BD850(0, v43 + 12, v41, 4, v45 - 52);
		}

		
		g_PersonalShopZt.PriceInvenory(v45, ZenPrice, BonusPrice, BlessPrice, SoulPrice, ChaosPrice, LifePrice, CreditPrice);

		//gConsole.Output(cGREEN, "v45: %d", v45);

		v21 = sub_790950();
		sub_6684E0(v45 - 52, ZenPrice, v21);
    }
    else
    {
		v22 = sub_860FC0();
		v23 = sub_8612B0(v22);
		v24 = sub_668720((LPVOID)v23);
		v43 = v24 + 204;

		g_PersonalShopZt.SendPrice(v43, ZenPrice, BonusPrice, BlessPrice, SoulPrice, ChaosPrice, LifePrice, CreditPrice);
		g_PersonalShopZt.PriceInvenory(v24, ZenPrice, BonusPrice, BlessPrice, SoulPrice, ChaosPrice, LifePrice, CreditPrice);

		//gConsole.Output(cGREEN, "v24: %d", v24);

		v25 = sub_790950();
		sub_6684E0(v43, ZenPrice, v25);
	}

	v54 = 0;
	v26 = sub_860FC0();
	v27 = sub_8612B0(v26);
	sub_842440((LPVOID)v27, v54);
	sub_6D6AD0(25, 0, 0);
	v54 = 1;
	int a1 = 0;
	v53 = a1;	//a1
	v28 = sub_8248E0();
	sub_824B30(v28, v53, v54);
}
// ----------------------------------------------------------------------------------------------

void PersonalShopZt::GC_RecvUpdatePSInvValue(LPBYTE aRecv)
{
	ZeroMemory(&this->PSInvetrory,sizeof(this->PSInvetrory));
	int datasize = 6;
	int ztcount = aRecv[datasize-1];

	this->aTargetIndex = pGameIndex;

	for (int n = 0; n < ztcount; n++)
	{
		GC_PSInventoryValue psv;
		memcpy(&psv,&aRecv[datasize],sizeof(psv));

		int itemPos = psv.ItemPos;
		itemPos = itemPos - 204;
		PriceInvenory(itemPos, psv.Zen, psv.Bonus, psv.Bless, psv.Soul, psv.Chaos, psv.Life, psv.Credit);

		datasize += sizeof(psv);
	}
}
// ----------------------------------------------------------------------------------------------

void PersonalShopZt::GC_RecvUpdatePSInvTargetValue(LPBYTE aRecv)
{
	ZeroMemory(&this->PSInvTarget,sizeof(this->PSInvTarget));
	int datasize = 8;
	int ztcount = aRecv[datasize-1];

	this->aTargetIndex = MAKE_NUMBERW(aRecv[datasize-3], aRecv[datasize-2]);

	for (int n = 0; n < ztcount; n++)
	{
		GC_PSInventoryValue psv;
		memcpy(&psv,&aRecv[datasize],sizeof(psv));

		int itemPos = psv.ItemPos;
		itemPos = itemPos - 204;

		PriceInvTarget(itemPos, psv.Zen, psv.Bonus, psv.Bless, psv.Soul, psv.Chaos, psv.Life, psv.Credit);

		datasize += sizeof(psv);
	}
}
// ----------------------------------------------------------------------------------------------

void PersonalShopZt::GC_ResultPrice(PMSG_ANS_PSHOP_SETITEMPRICE* aRecv)
{
	if( aRecv->btResult != 1)
	{
		int itpos = aRecv->btItemPos - 204;
		if(itpos >= 0 && itpos < 32)
		{
			this->PriceInvenory(itpos, 0, 0, 0, 0, 0, 0, 0);
		}
	}
}
// ----------------------------------------------------------------------------------------------
#endif