#include "stdafx.h"
#include "Other.h"
#include "User.h"
#include "Interface.h"
#include "Console.h"
#include "TMemory.h"
#include "Configs.h"
#include "UserAsm.h"
#include "VisualFix.h"
#include "NewHpBar.h"
#include "AddPoints.h"

User gObjUser;

void User::Load()
{
	ZeroMemory(ExViewe,sizeof(ExViewe));

	this->Class = 0;
	this->MagickAttack = NULL;
	this->WCoinC = 0;
	this->WCoinP = 0;
	this->WCoinG = 0;
	
	this->GuildNamber = 0;

	this->m_MapQuestShow = false;
	this->m_MapQuestCount = 0;
	this->m_MapQuestMaxCount = 0;

	this->PremiumType = 0;
	this->Premium = 0;

	this->WarehouseNumber = 0;

	this->SetCharacter(0, 18, 18, 15, 30, 0);
	this->SetCharacter(1, 28, 20, 25, 10, 0);
	this->SetCharacter(2, 22, 25, 20, 15, 0);
	this->SetCharacter(3, 26, 26, 26, 26, 0);
	this->SetCharacter(4, 26, 20, 20, 15, 25);
	this->SetCharacter(5, 21, 21, 18, 23, 0);

	//if(gGENS)
	//{
	//	SetOp((LPVOID)oIsBattleServer_Call1, (LPVOID)this->IsBattleServer, ASM::CALL);
	//	SetOp((LPVOID)oIsBattleServer_Call2, (LPVOID)this->IsBattleServer, ASM::CALL);
	//}

	SetOp((LPVOID)0x0077F9A9, (LPVOID)this->IsMasterClass, ASM::CALL);
	SetOp((LPVOID)0x0064A85F, (LPVOID)this->IsMasterClass, ASM::CALL);
	SetOp((LPVOID)0x0064AC02, (LPVOID)this->IsMasterClass, ASM::CALL);
	SetOp((LPVOID)0x0063DDF2, (LPVOID)this->IsMasterClass, ASM::CALL);
	SetOp((LPVOID)0x0063DF89, (LPVOID)this->IsMasterClass, ASM::CALL);
	SetOp((LPVOID)0x0063EA4C, (LPVOID)this->IsMasterClass, ASM::CALL);
	SetOp((LPVOID)0x0064A79A, (LPVOID)this->IsMasterClass, ASM::CALL);
	SetOp((LPVOID)0x0064AB3D, (LPVOID)this->IsMasterClass, ASM::CALL);
	SetOp((LPVOID)0x008105CB, (LPVOID)this->IsMasterClass, ASM::CALL);
	SetOp((LPVOID)0x0081064B, (LPVOID)this->IsMasterClass, ASM::CALL);

	LoadUserAsm();

	this->CursorX_Ex = 0;
	this->CursorY_Ex = 0;

	this->m_PartyMapCount = 0;
	memset(this->m_PartyMapData, 0, sizeof(this->m_PartyMapData));

	#if(DEV_PLAYERINFO)
	this->m_TargetInfo = false;
	memset(&this->m_TargetData, 0, sizeof(this->m_TargetData));
	#endif	

	#if(DEV_DAMAGE_TABLE)
	this->m_SecondDamageMax = 0;
	this->m_SecondDamage = 0;
	this->m_SecondDefence = 0;
	this->m_SecondReflect = 0;
	#endif
	
	this->m_PCPoint = 0;

	#if(DEV_MAX_BUFF_32)
	SetByte((LPVOID)(0x006420DF + 1), 32);
	SetByte((LPVOID)(0x006425A7 + 1), 32);
	SetByte((LPVOID)(0x00643120 + 1), 32);
	SetByte((LPVOID)(0x006434C4 + 1), 32);
	SetByte((LPVOID)(0x006420E6 + 1), 68);
	SetByte((LPVOID)(0x006425AE + 1), 70);
	SetByte((LPVOID)(0x00643127 + 1), 42);
	SetByte((LPVOID)(0x006420E6 + 1), 68);
	#endif
}

void User::Refresh()
{


	lpCharObj lpPlayer			= pUserObjectStruct;

	//this->lpViewPlayer		= &*(ObjectPreview*)oUserPreviewStruct;
	//this->GetTarget();
	//this->Money = lpPlayer->MoneyInventory;
	//// ----
	this->m_CursorX			= pCursorX;
	this->m_CursorY			= pCursorY;
	this->m_MapNumber		= pMapNumber;

	this->VieweTargetID		= pViewAttackTargetID;

	this->BattleCursor		= CheckBattleCursor();

	this->Class				= this->GetClass();

	//SpeedBug Fix?
#if(SPEED_BUG_FIX)
	if( (lpPlayer->Class & 7) != 6 )
	{
		SetByte((PVOID)(0x00556C32 + 6), 2);
	}
	else
	{
		SetByte((PVOID)(0x00556C32 + 6), 15);
	}
#endif
	//this->lpPlayer->Strength = 1;

	//gConsole.Output(cGREEN,"this->lpPlayer->LevelPoint : %d",this->lpPlayer->Strength );
	//this->m_MasterLevel		= pMasterLevel;
	//this->m_MasterPoint		= pMasterPoint;
	//this->m_MasterExp		= pMasterExp;
	//this->m_MasterNextExp	= pMasterNextExp;
	//// ----
	//if( (gObjUser.lpPlayer->Class & 7) != 6 )
	//{
	//	SetByte((PVOID)(0x00556C32 + 6), 2);
	//}
	//else
	//{
	//	SetByte((PVOID)(0x00556C32 + 6), 15);
	//}
	//// ----
	//if( gTrayMode.InTray )
	//{
	//	if( !this->lpViewPlayer->m_Model.Unknown4 && gConnectEx.m_ConnectState == 0 )
	//	{
	//		gTrayMode.ShowMessage(NIIF_WARNING, "MU Online", "Your character has been killed");
	//	}
	//}

	this->CursorX_Ex		= pWinWidth * pCursorX / 640;
	this->CursorY_Ex		= pWinHeight * pCursorY / 480;
}

bool User::IsMasterClass(BYTE Class)
{
	// ----
	lpCharObj lpPlayer = pUserObjectStruct;
	if( pIsMaster(Class) && lpPlayer->Level == 400 )
	{
		return true;
	}
	// ----
	return false;
}

bool User::IsMasterLevel()
{
	// ----
	lpCharObj lpPlayer = pUserObjectStruct;
	if( pIsMaster(lpPlayer->Class) && lpPlayer->Level == 400 )
	{
		return true;
	}
	// ----
	return false;
}

bool User::IsBattleServer()
{
	return true;
}

void User::UpdateCharInfo(CHAR_UPDATEINFO * aRecv)
{
	lpCharObj lpPlayer		= pUserObjectStruct;
	lpPlayer->Strength		= aRecv->Strength;
	lpPlayer->Dexterity		= aRecv->Dexterity;
	lpPlayer->Vitality		= aRecv->Vitality;
	lpPlayer->Energy		= aRecv->Energy;
	lpPlayer->Leadership	= aRecv->Leadership;
	lpPlayer->LevelPoint	= aRecv->LevelUpPoint;
	gVisualFix.UpPoint		= aRecv->LevelUpPoint;

#if(CUSTOM_ADD_POINTS==TRUE)
	g_AddPoints.Result(true);
#endif
}

int User::GetClass()
{
	lpCharObj lpPlayer			= pUserObjectStruct;

	int Result = 0;
	int Class = lpPlayer->Class;

	if( Class == DarkWizard || Class == SoulMaster || Class == GrandMaster )
	{
		Result = CLASS_WIZARD;
	}
	else if( Class == DarkKnight || Class == BladeKnight || Class == BladeMaster )
	{
		Result = CLASS_KNIGHT;
	}
	else if( Class == Elf || Class == MuseElf || Class == HightElf )
	{
		Result = CLASS_ELF;
	}
	else if( Class == MagicGladiator || Class == DuelMaster )
	{
		Result = CLASS_MAGUMSA;
	}
	else if ( Class == DarkLord || Class == LordEmperor )
	{
		Result = CLASS_DARKLORD;
	}
	else if( Class == Summoner || Class == BloodySummoner || Class == DimensionMaster )
	{
		Result = CLASS_SUMMONER;
	}
	else  if( Class == Monk || Class == FirstMaster || Class == FirstMaster2 )
	{
		Result = CLASS_MONK;
	}

	return Result;
}
// ----------------------------------------------------------------------------------------------

int User::GetActiveSkill()
{
	lpCharObj lpPlayer		= pUserObjectStruct;
	lpViewObj lpViewPlayer		= &*(ObjectPreview*)oUserPreviewStruct;
	return lpPlayer->pMagicList[lpViewPlayer->ActiveMagic];
}
// ----------------------------------------------------------------------------------------------

void User::ResetSystemGC_CharUpdate(GC_RESET_CHAR_UPDATE* Recv)
{
	lpCharObj lpPlayer		= pUserObjectStruct;

	lpPlayer->Level = Recv->Level;
	lpPlayer->Experience = Recv->Exp;
	lpPlayer->NextExperience = Recv->MaxExp;
	lpPlayer->Strength = Recv->Str;
	lpPlayer->Dexterity = Recv->Agi;
	lpPlayer->Vitality = Recv->Vit;
	lpPlayer->Energy = Recv->Ene;
	lpPlayer->Leadership = Recv->Cmd;
	lpPlayer->LevelPoint = Recv->UpPoint;
	
	gObjUser.Reset = Recv->Reset;
	gObjUser.GReset = Recv->Grand;

	gVisualFix.UpPoint = Recv->UpPoint;
}
// ----------------------------------------------------------------------------------------------

bool User::GetCheckSkill(int skillnumber)
{
	if(skillnumber < 0 || skillnumber > 650 )
	{
		return false;
	}

	//dk
	/*if(skillnumber == 330 || skillnumber == 332)
	{

		skillnumber = SKILL_WHEEL;
	}

	if(skillnumber == 331 || skillnumber == 333)
	{
		SKILL_BLOWOFFURY
	}*/

	lpCharObj lpPlayerEx		= pUserObjectStruct;
	for(int i = 0; i < 150; i++)
	{
		gConsole.Output(cGREY, "skillnumber: %d", lpPlayerEx->pMagicList[i]); 
		if(lpPlayerEx->pMagicList[i] == skillnumber)
		{
			return true;
		}
	}
	return false;
}
// ----------------------------------------------------------------------------------------------

bool User::InSafeZone()
{
	lpViewObj lpViewPlayerEx	= &*(ObjectPreview*)oUserPreviewStruct;
	return lpViewPlayerEx->InSafeZone;
}
// ----------------------------------------------------------------------------------------------

void User::SetCharacter(int Class, int Str, int Dex, int Vit, int Energy, int Leadership)
{
	this->DefClass[Class].Strength = Str;
	this->DefClass[Class].Dexterity = Dex;
	this->DefClass[Class].Vitality = Vit;
	this->DefClass[Class].Energy = Energy;
	this->DefClass[Class].Leadership = Leadership;
}
// ----------------------------------------------------------------------------------------------

void User::WarehouseReq(CHANGEWAREHOUSE * aRecv)
{
	this->WarehouseNumber = aRecv->Number;

	#if(CUSTOM_VALUE_MENU)
	if(gInterface.CheckWindowZt(ObjWindowsZt::ztWinValueMenu))
	{
		gInterface.CloseWindowZt(ObjWindowsZt::ztWinValueMenu);
	}

	if(gInterface.CheckWindowZt(ObjWindowsZt::ztWinGuildValueMenu))
	{
		gInterface.CloseWindowZt(ObjWindowsZt::ztWinGuildValueMenu);
	}
	#endif
}
// ----------------------------------------------------------------------------------------------

void User::PartyMiniMapInfo(PMSG_PARTY_MINIMAP* aRecv)
{
	this->m_PartyMapCount = 0;
	memset(this->m_PartyMapData, 0, sizeof(this->m_PartyMapData));

	if(aRecv->Count <= 0 || aRecv->Count > MAX_USER_IN_PARTY)
	{
		return;
	}

	this->m_PartyMapCount = aRecv->Count;

	for(int i = 0; i < this->m_PartyMapCount; i++ )
	{
		memcpy(this->m_PartyMapData[i].Name, aRecv->Data[i].Name, sizeof(aRecv->Data[i].Name));
		this->m_PartyMapData[i].Map = aRecv->Data[i].Map;
		this->m_PartyMapData[i].X = aRecv->Data[i].X;
		this->m_PartyMapData[i].Y = aRecv->Data[i].Y;
	}
}
// ----------------------------------------------------------------------------------------------

#if(FIX_VIEWE_MONSTER)

#endif
// ----------------------------------------------------------------------------------------------

#if(ENABLR_DEN_DEV)

void User::MiniMapSpotRecv(MINIMAP_SPOT_SEND* aRecv)
{
	this->m_MiniMapSpotCount = aRecv->Count;

	for(int i = 0; i < aRecv->Count; i++)
	{
		this->m_MiniMapSpot[i].X = aRecv->Spot[i].X;
		this->m_MiniMapSpot[i].Y = aRecv->Spot[i].Y;
	}
}

#endif