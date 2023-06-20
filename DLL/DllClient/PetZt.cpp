#include "stdafx.h"
#include "Object.h"
#include "Import.h"
#include "Protocol.h"
#include "Interface.h"
#include "PetZt.h"
#include "Defines.h"
#include "TMemory.h"
#include "ToolKit.h"
#include "Console.h"
#include "ReadScript.h"
#include "Controller.h"
#include "Cape.h"

#if(ENABLE_PETZT)
//ага значит петы подключаются только со стороны сервера
//найдем другой пример

CPetZt g_PetZt;

CPetZt::CPetZt()
{
	this->m_Enable = 1;
}

CPetZt::~CPetZt()
{
}

void CPetZt::Load()
{
	this->m_Enable = 1;

	this->m_PetCount = 0;
	this->m_EffectCount = 0;
	this->m_OptCount = 0;

	memset(g_PetZt.m_Data, 0, sizeof(g_PetZt.m_Data));
	memset(g_PetZt.m_Option, 0, sizeof(g_PetZt.m_Option));
	memset(g_PetZt.m_Effect, 0, sizeof(g_PetZt.m_Effect));

	this->Read(PETZT_PATH);

	SetOp((LPVOID)0x007DD1B4, this->CreatePetHook, ASM::CALL); 
	SetOp((LPVOID)0x008339B8, this->CreatePetHook, ASM::CALL); 
	SetOp((LPVOID)0x00836331, this->ResetPetPreview, ASM::CALL);
	SetOp((LPVOID)0x007DF76B, this->PetHPBar, ASM::CALL);	
	SetOp((LPVOID)0x00664117, this->RefreshViewPortItem, ASM::CALL);
	SetOp((LPVOID)0x0048E17D, this->PetsMovement, ASM::CALL);
	SetOp((LPVOID)0x00503756, this->PetsMovement, ASM::CALL);
	SetOp((LPVOID)0x005CA126, this->InventorySize, ASM::JMP);
	SetOp((LPVOID)0x0048E504, this->CreateEffect, ASM::CALL);
	SetOp((LPVOID)0x00503986, this->CreateEffect, ASM::CALL);
}

void CPetZt::Read(char* filename)
{
	SMDFile = fopen(filename, "r");

	if(SMDFile == NULL)
	{
		MessageBox(pGameWindow, filename, "LOAD FILE ERROR", NULL);
		return;
	}

	SMDToken Token;

	int iType = -1;

	while(true)
	{
		Token = GetToken();

        if(Token == END)
		{
            break;
		}

		iType = (int)TokenNumber;

		if(iType < 0 || iType > 2)
		{
			break;
		}

		while(true)
		{
			if(iType == 0)
			{
				Token = GetToken();

				if(!strcmp("end", TokenString))
				{
					break;
				}

				this->m_Enable = (int)TokenNumber;
			}
			else if(iType == 1)
			{
				Token = GetToken();

				if(!strcmp("end", TokenString))
				{
					break;
				}

				if(g_PetZt.m_PetCount >= MAX_PETZT_COUNT)
				{
					break;
				}

				PETZT_DATA* pList = &g_PetZt.m_Data[g_PetZt.m_PetCount];

				pList->Active = true;

				pList->ItemType = TokenNumber;

				Token = GetToken();
				pList->ItemIndex = TokenNumber;

				Token = GetToken();
				pList->PetZ = TokenNumber;

				Token = GetToken();
				pList->PetSize = TokenNumber;

				Token = GetToken();
				pList->InvSize = TokenNumber;

				Token = GetToken();
				pList->InvX = TokenNumber;

				Token = GetToken();
				pList->InvY = TokenNumber;

				Token = GetToken();
				memcpy(pList->ModelName, TokenString, sizeof(pList->ModelName));

				g_PetZt.m_PetCount++;
			}
			else if(iType == 2)
			{
				Token = GetToken();

				if(!strcmp("end", TokenString))
				{
					break;
				}

				PETZT_EFFECT* pEffectList = &this->m_Effect[this->m_EffectCount];

				pEffectList->Index = this->m_EffectCount;

				pEffectList->ItemType = TokenNumber;	

				Token = GetToken();
				pEffectList->ItemIndex = TokenNumber;	

				Token = GetToken();
				pEffectList->EffectIndex = TokenNumber;

				Token = GetToken();
				pEffectList->ColorR = TokenNumber;

				Token = GetToken();
				pEffectList->ColorG = TokenNumber;

				Token = GetToken();
				pEffectList->ColorB = TokenNumber;

				Token = GetToken();
				pEffectList->ColorSize = TokenNumber;

				Token = GetToken();
				pEffectList->ColorMain = TokenNumber;

				Token = GetToken();
				pEffectList->ColorSide = TokenNumber;

				this->m_EffectCount++;
			}
		}
	}

	fclose(SMDFile);
}

void CPetZt::LoadModel()
{
	WORD wItemNumber;
	char szItemName[256];
	
	for(int i = 0; i < g_PetZt.m_PetCount; i++)
	{
		wItemNumber = ITEM2(g_PetZt.m_Data[i].ItemType, g_PetZt.m_Data[i].ItemIndex);
		sprintf(szItemName, "%s", g_PetZt.m_Data[i].ModelName);

		pLoadModel(wItemNumber, "Data\\ZtData\\PetZt\\", g_PetZt.m_Data[i].ModelName, -1);
	}
}

void CPetZt::LoadTexture()
{
	WORD wItemNumber;

	for(int i = 0; i < g_PetZt.m_PetCount; i++)
	{
		wItemNumber = ITEM2(g_PetZt.m_Data[i].ItemType, g_PetZt.m_Data[i].ItemIndex);
		
		pLoadTexture(wItemNumber, "ZtData\\PetZt\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
	}
}

bool CPetZt::IsPet(int ItemID, bool Preview)
{
	for(int i = 0; i < MAX_PETZT_COUNT; i++)
	{
		if(!g_PetZt.m_Data[i].Active)
		{
			continue;
		}

		if(Preview)
		{
			if(ItemID == ITEM2(g_PetZt.m_Data[i].ItemType, g_PetZt.m_Data[i].ItemIndex))
			{
				return true;
			}
		}
		else
		{
			if(ItemID == ITEM(g_PetZt.m_Data[i].ItemType, g_PetZt.m_Data[i].ItemIndex))
			{
				return true;
			}
		}
	}

	return false;
}

PETZT_DATA* CPetZt::GetPetData(int ItemID, bool Preview)
{
	for(int i = 0; i < MAX_PETZT_COUNT; i++)
	{
		if(!g_PetZt.m_Data[i].Active)
		{
			continue;
		}

		if(Preview)
		{
			if(ItemID == ITEM2(g_PetZt.m_Data[i].ItemType, g_PetZt.m_Data[i].ItemIndex))
			{
				return &g_PetZt.m_Data[i];
			}
		}
		else
		{
			if(ItemID == ITEM(g_PetZt.m_Data[i].ItemType, g_PetZt.m_Data[i].ItemIndex))
			{
				return &g_PetZt.m_Data[i];
			}
		}
	}

	return NULL;
}

void CPetZt::PreviewCharSet(lpViewObj lpObj, BYTE * CharSet, lpViewObj Object, int Mode)
{
	BYTE btPet5 = CharSet[4];
	BYTE CustomPets = CharSet[15];

	if(CS_SET_HELPER(btPet5) == 3)
	{
		for(int i = 0; i < g_PetZt.m_PetCount; i++)
		{
			if(CustomPets == g_PetZt.m_Data[i].ItemIndex)
			{
				if(Mode)
				{
					*(BYTE*)(Mode + 4) = 0;
				}
				else
				{
					sub_5012D0((int)&lpObj->m_Model);
					sub_925280(sub_4DB230(), (int)&lpObj->m_Model, (int)&lpObj->PetSlot);
				}	

				lpObj->PetSlot = ITEM2(g_PetZt.m_Data[i].ItemType, g_PetZt.m_Data[i].ItemIndex);

				if(Mode)
				{
					gObjCreateBug2(lpObj->PetSlot, ((DWORD)&lpObj->m_Model) + 252, (DWORD)&lpObj->m_Model, Mode, 0);
				}
				else
				{
					gObjCreateBug(lpObj->PetSlot, ((DWORD)&lpObj->m_Model) + 252, (DWORD)&lpObj->m_Model, 0, 0);
				}

				break;
			}
		}
	}
}

void CPetZt::CreatePetHook(int ItemID)
{
    int ItemSwitch = *(WORD*)ItemID;
    int PetPreview = LODWORD(pPreviewPetThis) + 776;

	if(g_PetZt.IsPet(ItemSwitch, false))
	{
		gObjCreateBug(ItemSwitch + 1171, PetPreview + 252, PetPreview, 0, 0);
	}

	gObjCreatePet(ItemID);
}

bool CPetZt::ResetPetPreview(int ItemID)
{
    if(ItemID)
	{
		if(*(WORD*)ItemID == ITEM(13,0)		||
		   *(WORD*)ItemID == 0x1A01			||
		   *(WORD*)ItemID == 0x1A02			||
		   *(WORD*)ItemID == 0x1A03			||
		   *(WORD*)ItemID == 0x1A04			||
		   *(WORD*)ItemID == 0x1A05			||
		   *(WORD*)ItemID == 0x1A25			||
		   *(WORD*)ItemID == ITEM(13, 64)	||
		   *(WORD*)ItemID == ITEM(13, 65)	||
		   *(WORD*)ItemID == ITEM(13, 67)	||
		   *(WORD*)ItemID == ITEM(13, 80)	||
		   *(WORD*)ItemID == ITEM(13, 106)	||
		   *(WORD*)ItemID == ITEM(13, 123))
		{
			return true;
		}

		if(g_PetZt.IsPet(*(WORD*)ItemID, false))
		{
			return true;
		}

		#if(DEV_CAPE)
		if(gCapeAnimation.IsCape(*(WORD*)ItemID, false))	
		{
			return true;
		}
		#endif

	}

   return false;
}

char CPetZt::PetHPBar(int a1, int a2)
{
	lpViewObj Object = &*(ObjectPreview*)oUserPreviewStruct;

	if((Object->PetSlot < 7827 || Object->PetSlot > 7831)
		&& Object->PetSlot != 7891
		&& Object->PetSlot != 7892
		&& Object->PetSlot != 7894
		&& Object->PetSlot != 7907
		&& Object->PetSlot != 7933
		&& Object->PetSlot != 7950
		&& Object->PetSlot != 7864
		&& !g_PetZt.IsPet(Object->PetSlot, true))
	{
		return 0;
	}
	else
	{
		int PetHP = 0;
		char PetName[255];
		memset(&PetName, 0, 255);

		switch (Object->PetSlot)
		{
		case 7827:
			wsprintf(PetName, pGetTextLine_(pTextLineThis, 353));
			break;
		case 7828:
			wsprintf(PetName, (char *)oUserTextObject + 84 * (*(WORD *)(oUserPreviewStruct + 556) - 1171));
			break;
		case 7829:
			wsprintf(PetName, pGetTextLine_(pTextLineThis, 355));
			break;
		case 7830:
			wsprintf(PetName, pGetTextLine_(pTextLineThis, 354));
			break;
		case 7831:
			wsprintf(PetName, pGetTextLine_(pTextLineThis, 1187));
			break;
		case 7864:
			wsprintf(PetName, pGetTextLine_(pTextLineThis, 1916));
			break;
		case 7891:
			wsprintf(PetName, (char *)(oUserTextObject + 564480));
			break;
		case 7892:
			wsprintf(PetName, (char *)(oUserTextObject + 564564));
			break;
		case 7894:
			wsprintf(PetName, (char *)(oUserTextObject + 564732));
			break;
		case 7907:
			wsprintf(PetName, (char *)(oUserTextObject + 565824));
			break;
		case 7933:
			wsprintf(PetName, (char *)(oUserTextObject + 568008));
			break;
		case 7950:
			wsprintf(PetName, (char *)(oUserTextObject + 569436));
			break;
		default:
			wsprintf(PetName, (char *)oUserTextObject + 84 * (*(WORD *)(oUserPreviewStruct + 556) - 1171));
			break;
		}

		PetHP = *(BYTE*)(oUserObjectStruct_ + 5550);

		//sub_7DF910(1, 50, (int)&PetName, PetHP, 255, 0);
		sub_7DF910(a1, a2, (int)&PetName, PetHP, 255, 0);
	}

	return 1;
}

void CPetZt::RefreshViewPortItem(int a1)
{
	int v1 = sub_57D9A0(*(BYTE *)(a1 + 4) + (*(BYTE *)(a1 + 3) << 8));
	int result = sub_96A340(sub_402BC0(), v1);
	int v7 = result;

	if(result)
	{
		int v6 = result + 776;
		int v8 = sub_58AA80(a1 + 5);
		BYTE v11 = *(BYTE *)(a1 + 6) & 0xF;
		BYTE v10 = *(BYTE *)(a1 + 8) & 0x3F;
		BYTE v9 = *(BYTE *)(a1 + 9);

		switch((signed int)*(BYTE *)(a1 + 6) >> 4)
		{
		#if(DEV_CAPE)
		case 7:
			if (v8 == 0x1FFF)
			{
				if(gCapeAnimation.IsCape(v8, false))
				{
					sub_558630(v7, v6, 0);
				}

				*(WORD *)(v7 + 520) = -1;

				gConsole.Output(cGREY,"RefreshViewPortItem: -1");
			}
			else
			{
				*(WORD *)(v7 + 520) = v8 + 1171;
				*(BYTE *)(v7 + 522) = 0;

				if(gCapeAnimation.IsCape(v8, false))
				{
					sub_558630(v7, v6, 0);
				}

				gConsole.Output(cGREY,"RefreshViewPortItem: %d", *(WORD *)(v7 + 520));
			}
			break;
		#endif
		case 8:
			if (v8 == 0x1FFF)
			{
				*(WORD *)(v7 + 556) = -1;
				sub_5012D0(v6);
				sub_925280(sub_4DB230(), v7, -1);
			}
			else
			{
				*(WORD *)(v7 + 556) = v8 + 1171;
				*(BYTE *)(v7 + 558) = 0;

				if(g_PetZt.IsPet(v8, false))
				{
					gObjCreateBug(v8 + 1171, v6 + 252, v6, 0, 0);
				}
			}
			break;
		default:
			break;
		}
	}

	pRefreshViewPortItem(a1);
}

void CPetZt::PetsMovement(int a1, char a2)
{
	if(*(BYTE *)(a1 + 4))
	{
		lpViewObj lpObj = &*(ObjectPreview*)*(DWORD*)0x07BC4F04;

		if(pPlayerState == GameProcess && 
		   (pMapNumber < MAP_INDEX_DOUBLE_GOER1 || pMapNumber > MAP_INDEX_DOUBLE_GOER4) && 
		   (!*(BYTE*)(*(DWORD*)(a1 + 472) + 4) || *(BYTE*)(*(DWORD*)(a1 + 472) + 24) != 1))
		{
			*(BYTE*)(a1 + 4) = 0;
			pPetsMovement(a1, a2);
			return;
		}

		DWORD SkinID = *(DWORD*)(a1 + 48);
		DWORD Model = sub_969AD0(sub_4CDA10(), SLODWORD(SkinID));

		if(Model)
		{
			if(g_PetZt.IsPet(SkinID, true))
			{
				g_PetZt.PetFollowCharacter(a1, 150);

				PETZT_DATA* pPetData = g_PetZt.GetPetData(SkinID, true);

				if(pPetData)
				{
					*(float*)(a1 + 260) = *(float*)(*(DWORD*)(a1 + 472) + 260) + pPetData->PetZ;	//PetZ
				}
			}
		}
	}

	pPetsMovement(a1, a2);
}

void CPetZt::PetFollowCharacter(int a1, float MaxPos)
{
	float v22;
	vec3_t MUFLOAT;
	vec3_t PetPos;
	vec3_t OwnerPos;
	vec3_t CurrentPos;
	int LootPosition = 1000;

	OwnerPos[0] = *(float *)(*(DWORD *)(a1 + 472) + 252);
	OwnerPos[1] = *(float *)(*(DWORD *)(a1 + 472) + 256);
	OwnerPos[2] = *(float *)(*(DWORD *)(a1 + 472) + 260);

	PetPos[0] = OwnerPos[0] - *(float *)(a1 + 252);
	PetPos[1] = OwnerPos[1] - *(float *)(a1 + 256);
	PetPos[2] = OwnerPos[2] - *(float *)(a1 + 260);

	CurrentPos[0] = *(float *)(a1 + 252);
	CurrentPos[1] = *(float *)(a1 + 256);
	CurrentPos[2] = *(float *)(a1 + 260);
	
	float PetMapPos = PetPos[0] * PetPos[0] + PetPos[1] * PetPos[1];

	float diff1 = ((OwnerPos[0] > CurrentPos[0]) ? OwnerPos[0] - CurrentPos[0] : CurrentPos[0] - OwnerPos[0]);
	float diff2 = ((OwnerPos[1] > CurrentPos[1]) ? OwnerPos[1] - CurrentPos[1] : CurrentPos[1] - OwnerPos[1]);

	float angle = atan(diff2 / diff1) * 180 / PI;
	float angle2 = atan2(diff1, diff2) * 180 / PI; //

	if (PetMapPos >= MaxPos * MaxPos )
	{
		float speed;
		if (PetMapPos >= (MaxPos * 2) * (MaxPos * 2))
		{
			speed = 14.0f;
			speed += 1.0f;
			*(float *)(a1 + 120) = 0.89000002f;
		}
		else if (PetMapPos >= (MaxPos + (MaxPos / 2)) * (MaxPos + (MaxPos / 2)))
		{
			speed = 13.0f;
			*(float *)(a1 + 120) = 0.69000002f;
		}
		else
		{
			speed = 10.0f;
			*(float *)(a1 + 120) = 0.40000001f;
		}

		double MoveX = speed *(cos(angle * PI / 180));
		double MoveY = speed *(sin(angle * PI / 180));

		if (CurrentPos[0] < OwnerPos[0] && CurrentPos[1] < OwnerPos[1])
		{
			*(float *)(a1 + 252) += (float)MoveX;
			*(float *)(a1 + 256) += (float)MoveY;
			*(float *)(a1 + 272) = 180;
			*(float *)(a1 + 272) -= angle2;
		}
		else if (CurrentPos[0] < OwnerPos[0] && CurrentPos[1] > OwnerPos[1])
		{
			*(float *)(a1 + 252) += (float)MoveX;
			*(float *)(a1 + 256) -= (float)MoveY;
			*(float *)(a1 + 272) = angle2;
		}
		else if (CurrentPos[0] > OwnerPos[0] && CurrentPos[1] > OwnerPos[1])
		{
			*(float *)(a1 + 252) -= (float)MoveX;
			*(float *)(a1 + 256) -= (float)MoveY;
			*(float *)(a1 + 272) = 360;
			*(float *)(a1 + 272) -= angle2;
		}
		else if (CurrentPos[0] > OwnerPos[0] && CurrentPos[1] < OwnerPos[1])
		{
			*(float *)(a1 + 252) -= (float)MoveX;
			*(float *)(a1 + 256) += (float)MoveY;
			*(float *)(a1 + 272) = 180;
			*(float *)(a1 + 272) += angle2;
		}
		//else
		//{
		//	*(float *)(a1 + 252) += abs(MoveX);
		//	*(float *)(a1 + 256) += abs(MoveY);
		//	*(float *)(a1 + 272) = *(float *)(*(DWORD *)(a1 + 472) + 272);
		//}
		*(WORD*)(a1 + 18) = 2;
	}
	else if (PetMapPos < 70 * 70)
	{
		if ((*(WORD *)(*(DWORD *)(a1 + 472) + 18) < 15 || *(WORD *)(*(DWORD *)(a1 + 472) + 18) > 37))
		{
			*(WORD*)(a1 + 18) = 2;
			sub_959CC0(a1 + 264, a1 + 372);
			sub_95A1C0(a1 + 168, a1 + 372, MUFLOAT);
			*(float *)(a1 + 252) = *(float *)(a1 + 252) + MUFLOAT[0];
			*(float *)(a1 + 256) = *(float *)(a1 + 256) + MUFLOAT[1];
			//*(float *)(a1 + 260) = *(float *)(a1 + 260);
		}
	}
	else
	{
		if (GetTickCount() <= g_PetZt.m_PetTickCount + 800)
		{
			*(WORD*)(a1 + 18) = 1;
		}
		else if (GetTickCount() <= g_PetZt.m_PetTickCount + 12000)
		{
			*(WORD*)(a1 + 18) = 0;
		}
		else
		{
			g_PetZt.m_PetTickCount = GetTickCount();
		}
	}

	if (PetMapPos >= LootPosition * LootPosition)
	{
		if (*(float *)(a1 + 252) < *(float *)(*(DWORD *)(a1 + 472) + 252))
			*(float *)(a1 + 252) = *(float *)(a1 + 252) + PetPos[0] + rand() % 360;
		if (*(float *)(a1 + 252) > *(float *)(*(DWORD *)(a1 + 472) + 252))
			*(float *)(a1 + 252) = *(float *)(a1 + 252) + PetPos[0] - rand() % 360;

		if (*(float *)(a1 + 256) < *(float *)(*(DWORD *)(a1 + 472) + 256))
			*(float *)(a1 + 256) = *(float *)(a1 + 256) + PetPos[1] + rand() % 360;
		if (*(float *)(a1 + 256) > *(float *)(*(DWORD *)(a1 + 472) + 256))
			*(float *)(a1 + 256) = *(float *)(a1 + 256) + PetPos[1] - rand() % 360;
	}

	*(float *)(a1 + 260) = *(float *)(*(DWORD *)(a1 + 472) + 260);

	if (!(rand() % 100))
	{
		if (PetMapPos < MaxPos * MaxPos)
		{
			v22 = -(float)(rand() % 64 + 16) * 0.1000000014901161f;
			*(float *)(a1 + 272) = (float)(rand() % 360);
		}
		else
		{
			v22 = -(float)(rand() % 64 + 128) * 0.1000000014901161f;
		}
		*(float *)(a1 + 168) = 0.0f;
		*(float *)(a1 + 172) = v22;
		*(float *)(a1 + 176) = (float)(rand() % 64 - 32) * 0.1000000014901161f;
	}

	if (*(float *)(a1 + 260) < *(float *)(*(DWORD *)(a1 + 472) + 260) + 100.0f)
		*(float *)(a1 + 176) = *(float *)(a1 + 176) + 1.5f;

	if (*(float *)(a1 + 260) > *(float *)(*(DWORD *)(a1 + 472) + 260) + 200.0f)
		*(float *)(a1 + 176) = *(float *)(a1 + 176) - 1.5f;
}

static double dPetInvX = 0.0;
static double dPetInvY = 0.0;
static float flPetInvSize = 0.0;
static DWORD dwPetECX = 0;
static DWORD dwPetPosItem = 0;
static DWORD dwPetPosArg7 = 0;
static DWORD dwPetPosPush = 0x08793394;
static DWORD dwPetPosCall = 0x009598E0;
static DWORD dwPetInvJmp = 0x005CBFA4;
static DWORD dwPetPosArgTrue = 0x005CA12E;
static DWORD dwPetPosArgFalse = 0x005CA14F;

void __declspec(naked) CPetZt::InventorySize()
{
	__asm
	{
		MOV dwPetECX, ECX
		MOV ECX, DWORD PTR SS:[EBP+0x20]
		MOV dwPetPosArg7, ECX
		MOV ECX, DWORD PTR SS:[EBP+0x08]
		MOV dwPetPosItem, ECX
	}

	if(g_PetZt.IsPet(dwPetPosItem, true))
	{
		PETZT_DATA* pPetData = g_PetZt.GetPetData(dwPetPosItem, true);

		if(pPetData)
		{
			dPetInvX = (double)pPetData->InvX;
			dPetInvY = (double)pPetData->InvY;
			flPetInvSize = pPetData->InvSize;

			if(dwPetPosArg7)
			{
				flPetInvSize -= flPetInvSize * 0.3;
			}

			__asm 
			{
				LEA ECX,[EBP-0x4C]
				PUSH ECX
				LEA EDX,[EBP-0x38]
				PUSH EDX
				PUSH ECX
				FLD DWORD PTR DS:[flPetInvSize]
				FSTP DWORD PTR SS:[ESP]
				PUSH dwPetPosPush
				CALL dwPetPosCall	
				ADD ESP,0x10
			}	

			__asm
			{
				FLD DWORD PTR SS:[EBP-0x4C]
				FSUB QWORD PTR DS:[dPetInvX]
				FSTP DWORD PTR SS:[EBP-0x4C]
				FLD DWORD PTR SS:[EBP-0x48]
				FADD QWORD PTR DS:[dPetInvY]
				FSTP DWORD PTR SS:[EBP-0x48]
			}

			*(float*)0x82C6320 = 270.0000;
			*(float*)0x82C6324 = -10.0000;
			*(float*)0x82C6328 = 0.0;

			__asm
			{
				MOV ECX, dwPetECX
				JMP dwPetInvJmp
			}
		}
	}

	if(dwPetPosArg7)
	{
		__asm
		{
			MOV ECX, dwPetECX
			JMP dwPetPosArgTrue
		}		
	}
	else
	{
		__asm
		{
			MOV ECX, dwPetECX
			JMP dwPetPosArgFalse
		}
	}
}

char CPetZt::CreateEffect(int a4, char a5)
{
	if(*(BYTE*)(a4 + 4))
	{
		char v8 = 0;

		if(a5)
		{
			v8 = 1;
		}
		else
		{
			float v5 = *(float*)(a4 + 256) * 0.009999999776482582;
			float v6 = *(float*)(a4 + 252) * 0.009999999776482582;
			v8 = sub_5DBA10(v6, v5, -20.0);
		}

		*(BYTE*)(a4 + 12) = v8;

		if(*(BYTE*)(a4 + 12))
		{
			DWORD dwItemNumber = *(DWORD*)(a4 + 48);
		
			for(int n = 0; n < MAX_PETZT_EFFECT; n++)
			{
				if(ITEM2(g_PetZt.m_Effect[n].ItemType, g_PetZt.m_Effect[n].ItemIndex) == dwItemNumber)
				{
					float ItemColor[3];

					ItemColor[0] = g_PetZt.m_Effect[n].ColorR;

					ItemColor[1] = g_PetZt.m_Effect[n].ColorG;

					ItemColor[2] = g_PetZt.m_Effect[n].ColorB;

					pPlayStaticEffect(g_PetZt.m_Effect[n].EffectIndex, (DWORD*)(a4 + 252), g_PetZt.m_Effect[n].ColorSize, ItemColor, a4, g_PetZt.m_Effect[n].ColorMain, (DWORD)g_PetZt.m_Effect[n].ColorSide);
				}
			}

			if(*(DWORD *)(*(DWORD*)(a4 + 472) + 48) != 1163 && *(DWORD*)(a4 + 48) != 7827)
			{
				return 1;
			}

			if(a5)
			{
				*(float*)(a4 + 96) = *(float*)(a4 + 96);
			}
			else if(pPlayerState == 4)
			{
				*(float*)(a4 + 96) = 1.2;
			}
			else if(dwItemNumber != 384 && dwItemNumber != 386 && dwItemNumber != 385 && dwItemNumber != 387)
			{
				*(float*)(a4 + 96) = 1.0;
			}	
			   
			if(g_PetZt.IsPet(dwItemNumber, true))
			{
				PETZT_DATA* pPetData = g_PetZt.GetPetData(dwItemNumber, true);

				if(pPetData)
				{
					*(float*)(a4 + 96) = pPetData->PetSize;
				}
			}

			int v9 = 0;

			if(pet_4C8640((LPVOID)(*(DWORD*)(a4 + 472) + 484), 18))
			{
				v9 = 10;
			}
			
			pObjectMaxBug(a4, 0, 0, v9);
	
			float v10 = (double)((signed int)sub_9CFA0D() % 30 + 70) * 0.009999999776482582;

			if(dwItemNumber == 7827)
			{
				float v11[3];

				v11[0] = v10 * 0.5;
				v11[1] = v10 * 0.800000011920929;
				v11[2] = v10 * 0.6000000238418579;

				pPlayStaticEffect(32002, (DWORD*)(a4 + 252), 1.0, v11, a4, 0.0, 0);
			}
		}
	}

	return 1;
}

#endif