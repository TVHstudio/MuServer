#include "stdafx.h"
#include "Interface.h"
#include "User.h"
#include "Configs.h"
#include "JewelsBank.h"
#include "ZtLicense.h"
#include "ZtText.h"
#include "PremiumSystemZt.h"

JewelsBank gJewelsBank;

void JewelsBank::JewelsBankImageLoad()
{
	//if(!gJEWELSBANK) return;
	gInterface.LoadImages("ZtTeam\\JewelsBank\\newui_gens_rankback.tga", 400000, 0x2601, 0x2900, 1);
}

void JewelsBank::JewelsBankLoad()
{
	if(!gJEWELSBANK) return;
	this->Active = false;
	gInterface.BindObject(eJewelsBank, 400000, 85, 100, 1, 23);
	gInterface.Data[eJewelsBank].OnShow = true;

	#if(INTERFACE_JEWELBANK)
	this->Bind();
	#endif
}

void JewelsBank::JewelsBankDraw()
{
	if(!gJEWELSBANK) return;

	if( gInterface.CheckWindow(ObjWindow::Trade) || gInterface.CheckWindow(ObjWindow::CashShop)
		|| gInterface.CheckWindow(ObjWindow::FullMap) || gInterface.CheckWindow(ObjWindow::SkillTree)
		|| gInterface.CheckWindow(ObjWindow::MoveList) /*|| gObjUser.m_MapNumber == 34 || gObjUser.m_MapNumber == 30*/ )
	{
		this->Active = false;
		return;
	}

	if(this->Active == false) return;

	#if(INTERFACE_JEWELBANK)
	if(g_ZtLicense.CheckUser(eZtUB::Local) || g_ZtLicense.CheckUser(eZtUB::SILVER1)	|| g_ZtLicense.CheckUser(eZtUB::SILVER2) ||
		g_ZtLicense.CheckUser(eZtUB::Gredy) || g_ZtLicense.CheckUser(eZtUB::GredyLocal) || g_ZtLicense.CheckUser(eZtUB::Gredy2) ||
		g_ZtLicense.CheckUser(eZtUB::mu4you) || g_ZtLicense.CheckUser(eZtUB::Escalate) || g_ZtLicense.CheckUser(eZtUB::MedoniAndrei) ||
	    g_ZtLicense.CheckUser(eZtUB::eternalmu) ||
	    g_ZtLicense.CheckUser(eZtUB::Artem) || 
	    g_ZtLicense.CheckUser(eZtUB::Artem2) ||
		g_ZtLicense.CheckUser(eZtUB::NSGames) || g_ZtLicense.CheckUser(eZtUB::Chebuk) || g_ZtLicense.CheckUser(eZtUB::Jancis) ||
		g_ZtLicense.CheckUser(eZtUB::SaksonPavel))
	{
		this->Draw();
		return;
	}
	#endif

	gInterface.DrawGUI(eJewelsBank);
	
	//pDrawColorButton(0x7880, gInterface.Data[eJewelsBank].X, gInterface.Data[eJewelsBank].Y, gInterface.Data[eJewelsBank].Width, gInterface.Data[eJewelsBank].Height - 10, NULL, NULL, Color4f(0, 0, 0, 255));

	//gInterface.DrawFormat(eGold, 22, 25+5, 50, 1, "ExInfo Table");

	int Alg = 15;
#if(ADD_JEWELBANK_CREATEON)
	if(g_ZtLicense.CheckUser(eZtUB::Local) || g_ZtLicense.CheckUser(eZtUB::SILVER1)	|| g_ZtLicense.CheckUser(eZtUB::SILVER2) ||
		g_ZtLicense.CheckUser(eZtUB::Gredy) || g_ZtLicense.CheckUser(eZtUB::GredyLocal) || g_ZtLicense.CheckUser(eZtUB::Gredy2))
	{
		Alg = 17;
	}
#endif
	int plusY = 10;


	if(g_ZtLicense.CheckUser(eZtUB::SILVER1) || g_ZtLicense.CheckUser(eZtUB::SILVER2))
	{
		gInterface.DrawFormat(eShinyGreen, 10, 25+plusY+10-Alg, 60, 1, "%s-%s", 
			g_PremiumSystemZt.GetName(gObjUser.PremiumType), g_ZtText.GetText(40));
	}
	else
	{
		gInterface.DrawFormat(eShinyGreen, 10, 25+plusY+10-Alg, 60, 1, g_ZtText.GetText(40));
	}

	plusY += 10;
	gInterface.DrawFormat(eShinyGreen, 10, 25+plusY+10-Alg, 60, 1, g_ZtText.GetText(41));
	plusY += 10;
	gInterface.DrawFormat(eShinyGreen, 10, 25+plusY+10-Alg, 60, 1, g_ZtText.GetText(42));
	plusY += 10;
	gInterface.DrawFormat(eShinyGreen, 10, 25+plusY+10-Alg, 60, 1, g_ZtText.GetText(43));
	plusY += 10;
#ifdef PRIVATE_MODULE
	if(g_ZtLicense.CheckUser(eZtUB::Vadim))
	{
		gInterface.DrawFormat(eShinyGreen, 10, 25+plusY+10-Alg, 60, 1, "JoW:");
	}
	else
	{
		gInterface.DrawFormat(eShinyGreen, 10, 25+plusY+10-Alg, 60, 1, g_ZtText.GetText(44));
	}
#else
	gInterface.DrawFormat(eShinyGreen, 10, 25+50+10-Alg, 60, 1, g_ZtText.GetText(44));
#endif
	plusY += 10;
#if(ADD_JEWELBANK_CREATEON)
	if(g_ZtLicense.CheckUser(eZtUB::Local) || g_ZtLicense.CheckUser(eZtUB::SILVER1) || g_ZtLicense.CheckUser(eZtUB::SILVER2) ||
		g_ZtLicense.CheckUser(eZtUB::Gredy) || g_ZtLicense.CheckUser(eZtUB::GredyLocal) || g_ZtLicense.CheckUser(eZtUB::Gredy2))
	{ 
		gInterface.DrawFormat(eShinyGreen, 10, 25+plusY+10-Alg, 60, 1, g_ZtText.GetText(45));
		plusY += 10;
	}
#endif
	gInterface.DrawFormat(eShinyGreen, 10, 25+plusY+10-Alg, 60, 1, g_ZtText.GetText(46));
	//plusY += 10;
	//gInterface.DrawFormat(eShinyGreen, 10, 25+plusY+10-Alg, 60, 1, "Donate:");
	plusY += 10;
	gInterface.DrawFormat(eShinyGreen, 10, 25+plusY+10-Alg, 60, 1, g_ZtText.GetText(47));

	
	// ----
	plusY = 10;

	if(g_ZtLicense.CheckUser(eZtUB::Local)			|| 
	   g_ZtLicense.CheckUser(eZtUB::drynea)			|| 
	   g_ZtLicense.CheckUser(eZtUB::SILVER1)		|| 
	   g_ZtLicense.CheckUser(eZtUB::SILVER2)		||	
	   g_ZtLicense.CheckUser(eZtUB::PrideMu)		||		
	   g_ZtLicense.CheckUser(eZtUB::PrideMuLocal)	||		
	   g_ZtLicense.CheckUser(eZtUB::Local2)			|| 
	   g_ZtLicense.CheckUser(eZtUB::Local3)			||
	   g_ZtLicense.CheckUser(eZtUB::Jancis))
	{ 
		gInterface.DrawFormat(eWhite, 50, 25+plusY+10-Alg, 40, 1, "%d Day",(gObjUser.Premium/(3600*24)));
	}
	else
	{
		gInterface.DrawFormat(eWhite, 50, 25+plusY+10-Alg, 40, 1, "%d",(gObjUser.Premium/3600));
	}
	plusY += 10;
	gInterface.DrawFormat(eWhite, 50, 25+plusY+10-Alg, 40, 1, "%d",gObjUser.ChaosBank);
	plusY += 10;
	gInterface.DrawFormat(eWhite, 50, 25+plusY+10-Alg, 40, 1, "%d",gObjUser.BlessBank);
	plusY += 10;
	gInterface.DrawFormat(eWhite, 50, 25+plusY+10-Alg, 40, 1, "%d",gObjUser.SoulBank);
	plusY += 10;
	gInterface.DrawFormat(eWhite, 50, 25+plusY+10-Alg, 40, 1, "%d",gObjUser.LifeBank);
	plusY += 10;
#if(ADD_JEWELBANK_CREATEON)
	if(g_ZtLicense.CheckUser(eZtUB::Local) || g_ZtLicense.CheckUser(eZtUB::SILVER1) || g_ZtLicense.CheckUser(eZtUB::SILVER2) ||
		g_ZtLicense.CheckUser(eZtUB::Gredy) || g_ZtLicense.CheckUser(eZtUB::GredyLocal) || g_ZtLicense.CheckUser(eZtUB::Gredy2) || g_ZtLicense.CheckUser(eZtUB::Jancis))
	{ 
		gInterface.DrawFormat(eWhite, 50, 25+plusY+10-Alg, 40, 1, "%d",gObjUser.CreateonBank);
		plusY += 10;
	}
#endif

	//gInterface.DrawFormat(eWhite, 50, 25+plusY+10-Alg, 40, 1, "%.2f",gObjUser.ZtCred);
	gInterface.DrawFormat(eWhite, 50, 25+plusY+10-Alg, 40, 1, "%d",(int)gObjUser.ZtCred);
	//plusY += 10;
	//gInterface.DrawFormat(eWhite, 50, 25+plusY+10-Alg, 40, 1, "%d",gObjUser.m_iDonateCredit);
	plusY += 10;
	gInterface.DrawFormat(eWhite, 50, 25+plusY+10-Alg, 40, 1, "%d kk",gObjUser.Zen);
	plusY += 10;
}

#if(INTERFACE_JEWELBANK)

void JewelsBank::Bind()
{
	gInterface.BindObject(eJEWELBANK_MAIN, 0x7A5A, 222, 320, -1, -1);	//230
	gInterface.BindObject(eJEWELBANK_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eJEWELBANK_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eJEWELBANK_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eJEWELBANK_POINT, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(eJEWELBANK_LINE, 0x7B67, 154, 3, -1, -1);
	gInterface.BindObject(eJEWELBANK_DIV, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(eJEWELBANK_PAGEUP1, 0x7AA4, 15, 15, -1, -1);
	gInterface.BindObject(eJEWELBANK_PAGEUP2, 0x7AA4, 15, 15, -1, -1);
	gInterface.BindObject(eJEWELBANK_PAGEUP3, 0x7AA4, 15, 15, -1, -1);
	gInterface.BindObject(eJEWELBANK_PAGEUP4, 0x7AA4, 15, 15, -1, -1);
	gInterface.BindObject(eJEWELBANK_PAGEUP5, 0x7AA4, 15, 15, -1, -1);
	gInterface.BindObject(eJEWELBANK_PAGEUP6, 0x7AA4, 15, 15, -1, -1);
	gInterface.BindObject(eJEWELBANK_PAGEUP7, 0x7AA4, 15, 15, -1, -1);
	gInterface.BindObject(eJEWELBANK_PAGEUP8, 0x7AA4, 15, 15, -1, -1);
	gInterface.BindObject(eJEWELBANK_PAGEUP9, 0x7AA4, 15, 15, -1, -1);
	gInterface.BindObject(eJEWELBANK_PAGEUP10, 0x7AA4, 15, 15, -1, -1);
	gInterface.BindObject(eJEWELBANK_PAGEUP11, 0x7AA4, 15, 15, -1, -1);
	gInterface.BindObject(eJEWELBANK_PAGEDN1, 0x7C0D, 15, 15, -1, -1);
	gInterface.BindObject(eJEWELBANK_PAGEDN2, 0x7C0D, 15, 15, -1, -1);
	gInterface.BindObject(eJEWELBANK_PAGEDN3, 0x7C0D, 15, 15, -1, -1);
	gInterface.BindObject(eJEWELBANK_PAGEDN4, 0x7C0D, 15, 15, -1, -1);
	gInterface.BindObject(eJEWELBANK_PAGEDN5, 0x7C0D, 15, 15, -1, -1);
	gInterface.BindObject(eJEWELBANK_PAGEDN6, 0x7C0D, 15, 15, -1, -1);
	gInterface.BindObject(eJEWELBANK_PAGEDN7, 0x7C0D, 15, 15, -1, -1);
	gInterface.BindObject(eJEWELBANK_PAGEDN8, 0x7C0D, 15, 15, -1, -1);
	gInterface.BindObject(eJEWELBANK_PAGEDN9, 0x7C0D, 15, 15, -1, -1);
	gInterface.BindObject(eJEWELBANK_PAGEDN10, 0x7C0D, 15, 15, -1, -1);
	gInterface.BindObject(eJEWELBANK_PAGEDN11, 0x7C0D, 15, 15, -1, -1);
}

void JewelsBank::Draw()
{
	pSetCursorFocus = true;

	DWORD Color				= eGray100;
	float MainWidth			= 230.0;
	float MainHeight		= 350.0;
	float StartY			= 23;
	float StartX			= 0;

	gInterface.DrawWindow(eJEWELBANK_MAIN, eJEWELBANK_TITLE, eJEWELBANK_FRAME, eJEWELBANK_FOOTER, 14, StartX, StartY, "Jewel Bank System");

	float flDrawX = StartX + 20;
	float flDrawY = StartY + 30;

	if(g_ZtLicense.CheckUser(eZtUB::Chebuk) )
	{
		//this->DrawInfo(flDrawX, flDrawY, "WCoin", false, gObjUser.WCoinC);
	}
	else
	{
		this->DrawInfo(flDrawX, flDrawY, "Premium", false, gObjUser.Premium);

		flDrawY += 20;
		this->DrawInfo(flDrawX, flDrawY, "Credit", false, (int)gObjUser.ZtCred);

		flDrawY += 20;
		this->DrawInfo(flDrawX, flDrawY, "Zen", true, gObjUser.Zen);

		flDrawY += 20;
		gInterface.DrawGUI(eJEWELBANK_DIV, StartX, flDrawY + 10);
	}
	// -> jewel



	flDrawY += 20;
	this->DrawLine(12, 15, 1, flDrawX, flDrawY, "Jewel Of Chaos", gObjUser.ChaosBank);

	flDrawY += 20;
	this->DrawLine(14, 13, 2, flDrawX, flDrawY, "Jewel Of Bless", gObjUser.BlessBank);

	flDrawY += 20;
	this->DrawLine(14, 14, 3, flDrawX, flDrawY, "Jewel Of Soul", gObjUser.SoulBank);

	flDrawY += 20;
	this->DrawLine(14, 16, 4, flDrawX, flDrawY, "Jewel Of Life", gObjUser.LifeBank);

	// -> next jewel

	flDrawY += 20;
	this->DrawLine(14, 22, 5, flDrawX, flDrawY, "Jewel Of Creation", gObjUser.CreateonBank);

	flDrawY += 20;
	this->DrawLine(14, 31, 6, flDrawX, flDrawY, "Jewel of Guardian", gObjUser.GuardianBank);

	flDrawY += 20;
	this->DrawLine(14, 42, 7, flDrawX, flDrawY, "Jewel of Harmony", gObjUser.HarmonyBank);

	flDrawY += 20;
	this->DrawLine(14, 43, 8, flDrawX, flDrawY, "Jewel Of LowStone", gObjUser.LowStoneBank);

	flDrawY += 20;
	this->DrawLine(14, 44, 9, flDrawX, flDrawY, "Jewel Of HighStone", gObjUser.HighStoneBank);

	flDrawY += 20;
	this->DrawLine(14, 41, 10, flDrawX, flDrawY, "Jewel Of GemStone", gObjUser.GemStoneBank);
}

void JewelsBank::DrawLine(int ItemType, int ItemIndex, int ItemLevel, float ItemDrawX, float ItemDrawY, char * ItemName, int Count)
{
	ItemBmdStruct* ItemInfo = pGetItemBmdStruct(ITEM(ItemType, ItemIndex));
	const int WidthValue = 24;
	const int HeightValue = 26;
	float barWidth = WidthValue * ItemInfo->ItemWidth;
	float barHeight = HeightValue * ItemInfo->ItemHeight;
	float flX = ItemDrawX + 10;
	float flY = ItemDrawY;
	int iLevel = 0;
	gInterface.DrawItem(flX, flY, barWidth, barHeight, ITEMGET(ItemType,ItemIndex), SET_ITEMOPT_LEVEL(iLevel), 1, 0, 0);

	flX += 30;
	flY += 10;
	gInterface.DrawFormat(eYellow, flX, flY + 2, 100, 1, "%s x %d", ItemName, Count);

	flX += 95;
	gInterface.DrawGUI(eJEWELBANK_PAGEDN1 + ItemLevel, flX, flY);

	if(gInterface.IsWorkZone(eJEWELBANK_PAGEDN1 + ItemLevel))
	{
		if(gInterface.Data[eJEWELBANK_PAGEDN1 + ItemLevel].OnClick)
		{
			gInterface.DrawColoredGUI(eJEWELBANK_PAGEDN1 + ItemLevel, gInterface.Data[eJEWELBANK_PAGEDN1 + ItemLevel].X, gInterface.Data[eJEWELBANK_PAGEDN1 + ItemLevel].Y, eGray150);
		}	
	}

	flX += 20;
	gInterface.DrawGUI(eJEWELBANK_PAGEUP1 + ItemLevel, flX, flY);

	if(gInterface.IsWorkZone(eJEWELBANK_PAGEUP1 + ItemLevel))
	{
		if(gInterface.Data[eJEWELBANK_PAGEUP1 + ItemLevel].OnClick)
		{
			gInterface.DrawColoredGUI(eJEWELBANK_PAGEUP1 + ItemLevel, gInterface.Data[eJEWELBANK_PAGEUP1 + ItemLevel].X, gInterface.Data[eJEWELBANK_PAGEUP1 + ItemLevel].Y, eGray150);
		}
	}

	gInterface.DrawGUI(eJEWELBANK_LINE, ItemDrawX + 15, flY + 15);
}

void JewelsBank::DrawInfo(float InfoDrawX, float InfoDrawY, char* Text, bool Type, int Count)
{
	float flX = InfoDrawX + 10;
	float flY = InfoDrawY;

	gInterface.DrawGUI(eJEWELBANK_POINT, flX + 8, flY + 10);

	flX += 30;
	flY += 10;
	

	if(Type)
	{
		gInterface.DrawFormat(eYellow, flX, flY + 2, 100, 1, "%s: %d 000 000", Text, Count);

		flX += 95;
		gInterface.DrawGUI(eJEWELBANK_PAGEDN1, flX, flY);
	
		if(gInterface.IsWorkZone(eJEWELBANK_PAGEDN1))
		{
			if(gInterface.Data[eJEWELBANK_PAGEDN1].OnClick)
			{
				gInterface.DrawColoredGUI(eJEWELBANK_PAGEDN1, gInterface.Data[eJEWELBANK_PAGEDN1].X, gInterface.Data[eJEWELBANK_PAGEDN1].Y, eGray150);
			}
		}

		flX += 20;
		gInterface.DrawGUI(eJEWELBANK_PAGEUP1, flX, flY);

		if(gInterface.IsWorkZone(eJEWELBANK_PAGEUP1))
		{
			if(gInterface.Data[eJEWELBANK_PAGEUP1].OnClick)
			{
				gInterface.DrawColoredGUI(eJEWELBANK_PAGEUP1, gInterface.Data[eJEWELBANK_PAGEUP1].X, gInterface.Data[eJEWELBANK_PAGEUP1].Y, eGray150);
			}
			
		}
	}
	else
	{
		gInterface.DrawFormat(eYellow, flX, flY + 2, 100, 1, "%s: %d", Text, Count);
	}

	flX += 95;
	gInterface.DrawGUI(eJEWELBANK_LINE, InfoDrawX + 15, flY + 15);

}

void JewelsBank::Button(DWORD key)
{
	if(this->Active == false)
	{
		return;
	}
	
	for(int i = 0; i < 11; i++)
	{
		if(gInterface.ButtonZt(key, eJEWELBANK_PAGEUP1 + i, false))
		{
			this->Packet(i);
			return;
		}
		else if(gInterface.ButtonZt(key, eJEWELBANK_PAGEDN1 + i, false))
		{
			this->Packet(i+11);
			return;
		}
	}

}

void JewelsBank::Packet(int number)
{
	PMSG_JEWELBANK pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xDA, sizeof(pMsg));
	pMsg.Result = number;
	gProtocol.DataSend((LPBYTE)&pMsg, pMsg.h.size);
}


#endif