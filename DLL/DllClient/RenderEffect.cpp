#include "stdafx.h"
#include "ReadScript.h"
#include "Import.h"
#include "TMemory.h"
#include "Defines.h"
#include "Interface.h"
#include "BMD.h"
#include "LargeRand.h"



#include "RenderEffect.h"



#if(ENABLE_RENDER_EFFECT)

//DYNAMIC_EFFECT_INFO *m_DynamicEffectInfo = (DYNAMIC_EFFECT_INFO*)0x8907508;

CRenderEffect g_RenderEffect;

CRenderEffect::CRenderEffect()
{

}

CRenderEffect::~CRenderEffect()
{

}

void CRenderEffect::Init()
{
	for(int n=0;n < MAX_MODEL_EFFECT;n++)
	{
		this->m_ModelEffectData[n].Index = -1;
		this->m_ModelEffectData[n].ItemIndex = -1;
	}
}

void CRenderEffect::Load()
{
	this->Init();

	//this->Read(".\\Data\\ZtData\\ModelEffect.txt");

	#if(ENABLE_LUA)
	this->m_Lua.DoFile("Effect.lua");
	#endif

   //SetRange((LPVOID)0x0060B36A, 12, ASM::NOP );
   //SetOp((LPVOID)0x0060B36A, WingsSetInvisibleEffect, ASM::JMP );

   //SetRange((LPVOID)0x005FF97C, 1, ASM::NOP);
   //SetOp((LPVOID)0x005FF97C, HieuUngBufferGlow, ASM::JMP);

	SetOp((LPVOID)0x0061041C, (LPVOID)this->CreateItemEffect, ASM::CALL);
	SetOp((LPVOID)0x005666C1, (LPVOID)this->CreateItemEffect, ASM::CALL);
	//SetOp((LPVOID)0x00610466, (LPVOID)this->CreateItemEffect, ASM::CALL);

	//SetOp((LPVOID)0x00633FFB, this->LoadModels, ASM::CALL);

	////SetCompleteHook(0xFF, 0x0040487D, &this->DrawViewPortEffects);
	////SetCompleteHook(0xFF, 0x0048E56C, &this->DrawViewPortEffects);
	////SetCompleteHook(0xFF, 0x0057D4FF, &this->DrawViewPortEffects);
	////SetCompleteHook(0xFF, 0x0057D513, &this->DrawViewPortEffects);
	//SetOp((LPVOID)0x0040487D, (LPVOID)this->DrawViewPortEffects, ASM::CALL);
	//SetOp((LPVOID)0x0048E56C, (LPVOID)this->DrawViewPortEffects, ASM::CALL);
	//SetOp((LPVOID)0x0057D4FF, (LPVOID)this->DrawViewPortEffects, ASM::CALL);
	//SetOp((LPVOID)0x0057D513, (LPVOID)this->DrawViewPortEffects, ASM::CALL);
}

void CRenderEffect::Read(char* filename)
{
	SMDFile = fopen(filename, "r");

	if(!SMDFile)
	{
		MessageBox(pGameWindow, ".\\Data\\ZtData\\ModelEffect.txt", "ModelEffect.txt load error!", NULL);
		return;
	}

	int n = 0;

	while(true)
	{
		SMDToken Token = GetToken();

		if(Token == END || !strcmp(TokenString, "end"))
		{
			break;
		}

		this->m_ModelEffectData[n].Index = n;

		this->m_ModelEffectData[n].ItemType = TokenNumber;	

		Token = GetToken();
		this->m_ModelEffectData[n].ItemIndex = TokenNumber;

		Token = GetToken();
		this->m_ModelEffectData[n].MinLevel = TokenNumber;

		Token = GetToken();
		this->m_ModelEffectData[n].MaxLevel = TokenNumber;

		Token = GetToken();
		this->m_ModelEffectData[n].MinExcellent = TokenNumber;

		Token = GetToken();
		this->m_ModelEffectData[n].MaxExcellent = TokenNumber;

		Token = GetToken();
		this->m_ModelEffectData[n].Color[0] = TokenNumber;

		Token = GetToken();
		this->m_ModelEffectData[n].Color[1] = TokenNumber;

		Token = GetToken();
		this->m_ModelEffectData[n].Color[2] = TokenNumber;

		Token = GetToken();
		this->m_ModelEffectData[n].EffectIndex = TokenNumber;

		Token = GetToken();
		this->m_ModelEffectData[n].EffectType = TokenNumber;

		Token = GetToken();
		this->m_ModelEffectData[n].EffectCode = TokenNumber;

		Token = GetToken();
		this->m_ModelEffectData[n].EffectScale = TokenNumber;		

		n++;
	}

	fclose(SMDFile);
}

float CRenderEffect::GetRender(float a1, float a2)
{
	float v5;
	float v2 = a2 * 0.01745f;
	float v6 = (float)((int)(v2 * 1000.0f / a1 + timeGetTime()) % (int)(6283.185546875f / a1))* 0.001f * a1;

	if (v6 >= 3.14f)
		v5 = cosf(v6);
	else
		v5 = -cosf(v6);

	return (float)((v5 + 1.0f) * 0.5f);
}

double CRenderEffect::absf(float a1)
{
	double result;

	if (a1 >= 0.0)
		result = a1;
	else
		result = -a1;
	return result;
}

double CRenderEffect::sub_4E7B95(float a1)
{
  return (float)sin(a1);
}

void CRenderEffect::LoadModels()
{
	//pLoadModel(406, "Data\\Custom\\Skill\\", "sign_gm", -1);
	//pLoadTexture(406, "Custom\\Skill\\", 0x2901, 0x2600, 1);
	//pLoadModel(407, "Data\\Custom\\Skill\\", "sign_em", -1);
	//pLoadTexture(407, "Custom\\Skill\\", 0x2901, 0x2600, 1);
	//pLoadModel(408, "Data\\Custom\\Skill\\", "sign_admin", -1);
	//pLoadTexture(408, "Custom\\Skill\\", 0x2901, 0x2600, 1);
	// ----
	pLoadModel(32587, "Data\\Effect\\", "shiny06", -1);
	pLoadTexture(32587, "Effect\\", GL_REPEAT, GL_NEAREST, GL_TRUE);

	pInitModelData2();
}

void CRenderEffect::AddItemEffect(int lpModel, int ItemID)
{
	LPVOID Model = pGetModel(pModelThis(), ItemID);

	vec3_t p;
	vec3_t Bone;
	vec3_t Color;
	vec3_t WorldPos;

	Vector(0.0f, 0.0f, 0.0f, p);
	Vector(0.0f, 0.0f, 0.0f, Bone);
	Vector(0.0f, 0.0f, 0.0f, Color);
	Vector(0.0f, 0.0f, 0.0f, WorldPos);

	Vector(WorldPos[0], WorldPos[1], WorldPos[2], WorldPos);

	switch (ItemID)
	{
		case ITEM2(0, 44): //Blessed Sword
		{
			float v234 = GetRender(-4.0, 0.0);
			float v1875 = v234 * 0.5 + 0.5;
			Vector(v1875 * 0.4000000059604645, v1875 * 0.550000011920929, v1875 * 0.1500000059604645, Color);
			for (int i43 = 53; i43 < 129; ++i43 )
			{
				pQuickPlayStaticEffect(Model, 32002, i43, 0.64999998, Color, lpModel);
			}
			float v237 = ((int) timeGetTime() % 15) / 37.5;
			float v1879 = v237 + 0.5;
			Vector(v1879, v1879, v1879, Color);
			for(int i44 = 4; i44 < 23; ++i44)
			{
				pQuickPlayStaticEffect(Model, 32229, i44, 0.30000001, Color, lpModel);	//32229
			}
			pQuickPlayStaticEffect(Model, 32229, 47, 0.30000001, Color, lpModel);	//32229
			pQuickPlayStaticEffect(Model, 32229, 23, 0.30000001, Color, lpModel);	//32229
			Vector(v1875 * 0.8500000238418579, v1875 * 0.1000000014901161, v1875 * 0.8999999761581421, Color);
			pQuickPlayStaticEffect(Model, 32229, 45, 0.80000001, Color, lpModel);	//32229
			pQuickPlayStaticEffect(Model, 32229, 46, 0.80000001, Color, lpModel);	//32229
			pQuickPlayStaticEffect(Model, 32229, 28, 0.80000001, Color, lpModel);	//32229
			pQuickPlayStaticEffect(Model, 32229, 30, 0.80000001, Color, lpModel);	//32229
			Vector(v1875 * 0.1500000059604645, v1875 * 0.1500000059604645, v1875 * 0.8999999761581421, Color);
			int JointID1[] = { 27,32,29,43,34,40,37,35,25,41,42,44 };
			int JointID2[] = { 34,40,36,38 };
			for ( int i45 = 0; i45 < 12; ++i45 )
			{
				pQuickPlayStaticEffect(Model, 32002, JointID1[i45], 0.60000002, Color, lpModel);
			}
			for ( int i46 = 0; i46 < 4; ++i46 )
			{
				pQuickPlayStaticEffect(Model, 32002, JointID2[i46], 0.30000001, Color, lpModel);
			}
			if(GetRender(-4.0, 0.0) + 0.5 <= 1.0)
			  float v1163 = 1.0;
			else
			  float v1163 = GetRender(-4.0, 0.0) + 0.5;
			Vector(v1875 * 0.2000000029802322, v1875 * 0.300000011920929, v1875 * 1.0, Color);
			pQuickPlayStaticEffect(Model, 32114, 1, 1.4, Color, lpModel);
		
			//if (*(BYTE*)(oUserPreviewStruct+14) == 0 && pPlayerState == 5 )
			{
				float ColorR[3] = { (int)timeGetTime() % 11 * 0.1000000014901161 * v1875 + 0.699999988079071,
									(int)timeGetTime() % 11 * 0.1000000014901161 * v1875 + 0.699999988079071, 
									(int)timeGetTime() % 11 * 0.1000000014901161 * v1875 + 0.699999988079071 };
				ColorR[GetLargeRand() % 3] = 0.69999999f;
				ColorR[GetLargeRand() % 3] = 1.0f;

				pAllowPlayEffect(Model, Bone, lpModel, 27, 0);

				float v240 = (double)(timeGetTime() % 1441) * 0.25;
				pPlayStaticEffect(32805, (DWORD*)Bone, 1.0, Color, lpModel, v240, 0);	//32805

				pAllowPlayEffect(Model, Bone, lpModel, 32, (int)&p);	//(int)&p

				float v241 = (double)(1440 - ((int) timeGetTime() % 1441) * 0.25);
				pPlayStaticEffect(32805, (DWORD*)Bone, 1.0, ColorR, lpModel, v241, 0);	//32805	32587

				pAllowPlayEffect(Model, Bone, lpModel, 1, 0);

				WorldPos[0] = Bone[0] - WorldPos[0];
				WorldPos[1] = Bone[1] - WorldPos[1];
				WorldPos[2] = Bone[2] - WorldPos[2];

				g_RenderEffect.AddDynamicEffect(52379, Bone, WorldPos, ColorR, 6, 1.0f, &*(ObjectModel*)Model);
			}
		}
		break;
	}
}

int CRenderEffect::AddDynamicEffect(DWORD ModelID, vec3_t VecPos, vec3_t WorldPos, vec3_t Color, int SubEffectID, float Scale, ObjectModel* lpModel)
{
	int iResult = 0;

	DYNAMIC_EFFECT_INFO *m_DynamicEffectInfo = (DYNAMIC_EFFECT_INFO*)0x8907508;

	DYNAMIC_EFFECT_INFO *lpEffect;

	for(int i = 0; i < 3000; ++i)
	{
		

		lpEffect = &m_DynamicEffectInfo[i];

		if(!lpEffect->Enable)
		{
			iResult = i;
			break;
		}	
	}

	if (!lpEffect)
	{
		return 0;
	}

	lpEffect->Enable = 1;
	lpEffect->EffectID = ModelID;
	lpEffect->TextureID = ModelID;
	lpEffect->SubEffectID = SubEffectID;
	lpEffect->VecPos.X = VecPos[0];
	lpEffect->VecPos.Y = VecPos[1];
	lpEffect->VecPos.Z = VecPos[2];
	lpEffect->VecPos2.X = VecPos[0];
	lpEffect->VecPos2.Y = VecPos[1];
	lpEffect->VecPos2.Z = VecPos[2];
	lpEffect->Color.X = Color[0];
	lpEffect->Color.Y = Color[1];
	lpEffect->Color.Z = Color[2];
	lpEffect->Scale = Scale;
	lpEffect->Unknown80 = 0.0;
	lpEffect->Unknown60 = 2;
	lpEffect->Unknown72 = 0;
	lpEffect->m_Owner = lpModel;
	lpEffect->Unknown68 = 0.0;
	lpEffect->Unknown76 = 1;
	lpEffect->WorldPos.X = WorldPos[0];
	lpEffect->WorldPos.Y = WorldPos[1];
	lpEffect->WorldPos.Z = WorldPos[2];
	lpEffect->Unknown84.X = 0.0;
	lpEffect->Unknown84.Y = 0.0;
	lpEffect->Unknown84.Z = 0.0;

	switch (lpEffect->EffectID)
	{
	case 32587: //shiny06
		if (lpEffect->SubEffectID)
		{
			if (lpEffect->SubEffectID > 0 && lpEffect->SubEffectID <= 3)
			{
				lpEffect->Unknown60 = GetLargeRand() % 11 + 20;
				lpEffect->Unknown56 = 0.0;
				lpEffect->Unknown68 = (float)(GetLargeRand() % 180);
				lpEffect->Scale = Scale - (float)(GetLargeRand() % 6) * (Scale / 10.0f);

				switch (lpEffect->SubEffectID)
				{
				case 1:
					lpEffect->VecPos.X = (float)(GetLargeRand() % 31) - 15.0f + lpEffect->VecPos.X;
					lpEffect->VecPos.Y = (float)(GetLargeRand() % 31) - 15.0f + lpEffect->VecPos.Y;
					lpEffect->VecPos.Z = (float)(GetLargeRand() % 21) + 12.0f + lpEffect->VecPos.Z;
					break;
				case 2:
					lpEffect->VecPos.X = (float)(GetLargeRand() % 31) / 30.0f * 40.0f - 20.0f + lpEffect->VecPos.X;
					lpEffect->VecPos.Y = (float)(GetLargeRand() % 31) / 30.0f * 40.0f - 20.0f + lpEffect->VecPos.Y;
					lpEffect->VecPos.Z = (float)(GetLargeRand() % 24) + 14.0f + lpEffect->VecPos.Z;
					break;
				case 3:
					lpEffect->VecPos.X = (float)(GetLargeRand() % 31) / 30.0f * 70.0f - 35.0f + lpEffect->VecPos.X;
					lpEffect->VecPos.Y = (float)(GetLargeRand() % 31) / 30.0f * 70.0f - 35.0f + lpEffect->VecPos.Y;
					lpEffect->VecPos.Z = (float)(GetLargeRand() % 30) + 20.0f + lpEffect->VecPos.Z;
					break;
				}
			}
			else
			{
				switch (lpEffect->SubEffectID)
				{
				case 4:
					break;
				case 6:
					lpEffect->Unknown60 = 15;
					lpEffect->Unknown68 = (float)(GetLargeRand() % 360);
					lpEffect->Unknown84.X = (float)-(GetLargeRand() % 2 - 1);
					lpEffect->Unknown84.Y = (float)-(GetLargeRand() % 4);
					lpEffect->Unknown84.Z = (float)-(GetLargeRand() % 4);
					break;
				case 7:
					lpEffect->Scale = 0.1;
					lpEffect->VecPos2.X = Scale;
					lpEffect->Unknown60 = GetLargeRand() % 10 + 20;
					lpEffect->VecPos.X = (float)(GetLargeRand() % 50 - 25) + lpEffect->VecPos.X;
					lpEffect->VecPos.Y = (float)(GetLargeRand() % 50 - 25) + lpEffect->VecPos.Y;
					lpEffect->VecPos.Z = (float)(GetLargeRand() % 50 - 25) + lpEffect->VecPos.Z;
					lpEffect->Unknown80 = 1.0;
					lpEffect->WorldPos.X = (float)(GetLargeRand() % 360);
					lpEffect->WorldPos.Y = (float)(GetLargeRand() % 360);
					lpEffect->WorldPos.Z = (float)(GetLargeRand() % 360);
					lpEffect->Unknown68 = (float)(GetLargeRand() % 20 - 10);
					break;
				}
			}
		}
		else
		{
			lpEffect->Unknown60 = 18;
			lpEffect->WorldPos.X = 45.0;
		}
		break;
	// --
	case 52379: //hikorora Custom
		if (lpEffect->SubEffectID)
		{
			switch (lpEffect->SubEffectID)
			{
			case 1:
			case 2:
				lpEffect->Unknown60 = 15;
				lpEffect->Scale = 0.2;
				break;
			case 3:
				lpEffect->Scale = 0.0;
				lpEffect->Unknown60 = 35;
				break;
			case 4:
				lpEffect->Unknown68 = (float)(GetLargeRand() % 360);
				lpEffect->Unknown60 = 5;
				lpEffect->Scale = 1.2;
				break;
			case 5:
			case 6:
				lpEffect->Unknown60 = 6;
				lpEffect->Unknown68 = (int)(timeGetTime()* 0.75f) % 360;
				lpEffect->Unknown72 = 2;
				lpEffect->Scale = Scale - (float)(GetLargeRand() % 6) * (Scale / 10.0f) + 0.3;
				break;
			}
		}
		else
		{
			lpEffect->Unknown60 = 100;
			lpEffect->Scale = 0.2;
		}
		break;
	// --
	case 52229: //flareBlue Custom
		if (lpEffect->SubEffectID)
		{
			switch (lpEffect->SubEffectID)
			{
			case 6:
				lpEffect->Unknown56 = 1.0;
				lpEffect->Unknown84.X = (float)(GetLargeRand() % 8) + -4.0;
				lpEffect->Unknown84.Y = (float)(GetLargeRand() % 4);
				lpEffect->Unknown84.Z = (float)(GetLargeRand() % 8) + -4.0;
				lpEffect->Unknown60 = 12;
				lpEffect->Scale = Scale - (float)(GetLargeRand() % 4) * (Scale / 10.0f);
				break;
			}
		}
		break;
	// ==
		case 32355:
		if (lpEffect->SubEffectID)
		{
			if (lpEffect->SubEffectID > 0 && lpEffect->SubEffectID <= 3)
			{
				lpEffect->Unknown60 = GetLargeRand() % 11 + 20;
				lpEffect->Unknown56 = 0.0;
				lpEffect->Unknown68 = (float)(GetLargeRand() % 180);
				lpEffect->Scale = Scale - (float)(GetLargeRand() % 6) * (Scale / 10.0f);

				switch (lpEffect->SubEffectID)
				{
					case 1:
						lpEffect->VecPos.X = (float)(GetLargeRand() % 31) - 15.0f + lpEffect->VecPos.X;
						lpEffect->VecPos.Y = (float)(GetLargeRand() % 31) - 15.0f + lpEffect->VecPos.Y;
						lpEffect->VecPos.Z = (float)(GetLargeRand() % 21) + 12.0f + lpEffect->VecPos.Z;
						break;
					case 2:
						lpEffect->VecPos.X = (float)(GetLargeRand() % 31) / 30.0f * 40.0f - 20.0f + lpEffect->VecPos.X;
						lpEffect->VecPos.Y = (float)(GetLargeRand() % 31) / 30.0f * 40.0f - 20.0f + lpEffect->VecPos.Y;
						lpEffect->VecPos.Z = (float)(GetLargeRand() % 24) + 14.0f + lpEffect->VecPos.Z;
						break;
					case 3:
						lpEffect->VecPos.X = (float)(GetLargeRand() % 31) / 30.0f * 70.0f - 35.0f + lpEffect->VecPos.X;
						lpEffect->VecPos.Y = (float)(GetLargeRand() % 31) / 30.0f * 70.0f - 35.0f + lpEffect->VecPos.Y;
						lpEffect->VecPos.Z = (float)(GetLargeRand() % 30) + 20.0f + lpEffect->VecPos.Z;
						break;
				}
			}
			else
			{
				switch (lpEffect->SubEffectID)
				{
					case 4:

						break;
					case 6:
						lpEffect->Unknown60 = 15;
						lpEffect->Unknown68 = (float)(GetLargeRand() % 360);
						lpEffect->Unknown84.X = (float)-(GetLargeRand() % 2 - 1);
						lpEffect->Unknown84.Y = (float)-(GetLargeRand() % 4);
						lpEffect->Unknown84.Z = (float)-(GetLargeRand() % 4);
						break;
					case 7:
						lpEffect->Scale = (float)(GetLargeRand() % 8 + 1) * 0.1 * Scale;
						lpEffect->Unknown60 = GetLargeRand() % 20 + 20;
						lpEffect->Unknown56 = 1.0f;
						lpEffect->Unknown68 = (float)(GetLargeRand() % 180);
						break;
				}
			}
		}
		else
		{
			lpEffect->Unknown60 = 18;
			lpEffect->WorldPos.X = 45.0;
		}
		break; //return i; <---
	// ==
	case 32290:
		if (lpEffect->SubEffectID)
		{
			switch (lpEffect->SubEffectID)
			{
			case 0x11://for wings of conqueror
				lpEffect->Unknown68 = (float)(GetLargeRand() % 360);
				lpEffect->Unknown60 = 25;
				lpEffect->Scale = Scale;
				break;
			}
		}
		else
		{
			lpEffect->Unknown60 = 20;
			lpEffect->Unknown84.Z = (GetLargeRand() % 5 + 2);
		}
		//lpEffect->Unknown68 = (double)(GetLargeRand() % 360);
		//lpEffect->Scale = (double)(GetLargeRand() % 10 + 10) * 0.01999999955296516;
		// --
		lpEffect->VecPos.X = (double)(GetLargeRand() % 40) - 20.0 + lpEffect->VecPos.X;
		lpEffect->VecPos.Y = (double)(GetLargeRand() % 40) - 20.0 + lpEffect->VecPos.Y;
		lpEffect->VecPos.Z = (double)(GetLargeRand() % 20) - 10.0 + lpEffect->VecPos.Z;
		break;
		// ----
		case 32289: //Texture ID Main Season 13 -- Effect\\shiny06.jpg
		if (lpEffect->SubEffectID)
		{
			if (lpEffect->SubEffectID > 0 && lpEffect->SubEffectID <= 3)
			{
				lpEffect->Unknown60 = GetLargeRand() % 11 + 20;
				lpEffect->Unknown56 = 0.0;
				lpEffect->Unknown68 = (float)(GetLargeRand() % 180);
				lpEffect->Scale = Scale - (float)(GetLargeRand() % 6) * (Scale / 10.0f);

				switch (lpEffect->SubEffectID)
				{
					case 1:
						lpEffect->VecPos.X = (float)(GetLargeRand() % 31) - 15.0f + lpEffect->VecPos.X;
						lpEffect->VecPos.Y = (float)(GetLargeRand() % 31) - 15.0f + lpEffect->VecPos.Y;
						lpEffect->VecPos.Z = (float)(GetLargeRand() % 21) + 12.0f + lpEffect->VecPos.Z;
						break;
					case 2:
						lpEffect->VecPos.X = (float)(GetLargeRand() % 31) / 30.0f * 40.0f - 20.0f + lpEffect->VecPos.X;
						lpEffect->VecPos.Y = (float)(GetLargeRand() % 31) / 30.0f * 40.0f - 20.0f + lpEffect->VecPos.Y;
						lpEffect->VecPos.Z = (float)(GetLargeRand() % 24) + 14.0f + lpEffect->VecPos.Z;
						break;
					case 3:
						lpEffect->VecPos.X = (float)(GetLargeRand() % 31) / 30.0f * 70.0f - 35.0f + lpEffect->VecPos.X;
						lpEffect->VecPos.Y = (float)(GetLargeRand() % 31) / 30.0f * 70.0f - 35.0f + lpEffect->VecPos.Y;
						lpEffect->VecPos.Z = (float)(GetLargeRand() % 30) + 20.0f + lpEffect->VecPos.Z;
						break;
				}
			}
			else
			{
				switch (lpEffect->SubEffectID)
				{
				case 4:

					break;
				case 6:
					lpEffect->Unknown60 = 15;
					lpEffect->Unknown68 = (float)(GetLargeRand() % 360);
					lpEffect->Unknown84.X = (float)-(GetLargeRand() % 2 - 1);
					lpEffect->Unknown84.Y = (float)-(GetLargeRand() % 4);
					lpEffect->Unknown84.Z = (float)-(GetLargeRand() % 4);
					break;
				case 7:
					lpEffect->Scale = (float)(GetLargeRand() % 8 + 1) * 0.1 * Scale;
					lpEffect->Unknown60 = GetLargeRand() % 20 + 20;
					lpEffect->Unknown56 = 1.0f;
					lpEffect->Unknown68 = (float)(GetLargeRand() % 180);
					break;
				}
			}
		}
		else
		{
			lpEffect->Unknown60 = 18;
			lpEffect->WorldPos.X = 45.0;
		}
		break; //return i; <---

	}

	//return 0;

	return iResult;
}

int CRenderEffect::AddDynamicEffectEx(DWORD ModelID, float VecPos0, float VecPos1, float VecPos2, float WorldPos0, float WorldPos1, float WorldPos2, float Color0, float Color1, float Color2, int SubEffectID, float Scale, ObjectModel* lpModel)
{
	int iResult = 0;

	DYNAMIC_EFFECT_INFO *lpEffect;

	DYNAMIC_EFFECT_INFO *m_DynamicEffectInfo = (DYNAMIC_EFFECT_INFO*)0x8907508;

	for (int i = 0; i < 3000; ++i)
	{
		lpEffect = &m_DynamicEffectInfo[i];

		if (!lpEffect->Enable)
		{
			iResult = i;
			break;
		}
			
	}

	if (!lpEffect)
	{
		return 0;
	}
	/*
	WorldPos0 = VecPos0 - WorldPos0;
	WorldPos1 = VecPos1 - WorldPos1;
	WorldPos2 = VecPos2 - WorldPos2;
	*/

	lpEffect->Enable = 1;
	lpEffect->EffectID = ModelID;
	lpEffect->TextureID = ModelID;
	lpEffect->SubEffectID = SubEffectID;
	lpEffect->VecPos.X = VecPos0;
	lpEffect->VecPos.Y = VecPos1;
	lpEffect->VecPos.Z = VecPos2;
	lpEffect->VecPos2.X = VecPos0;
	lpEffect->VecPos2.Y = VecPos1;
	lpEffect->VecPos2.Z = VecPos2;
	lpEffect->Color.X = Color0;
	lpEffect->Color.Y = Color1;
	lpEffect->Color.Z = Color2;
	lpEffect->Scale = Scale;
	lpEffect->Unknown80 = 0.0;
	lpEffect->Unknown60 = 2;
	lpEffect->Unknown72 = 0;
	lpEffect->m_Owner = lpModel;
	lpEffect->Unknown68 = 0.0;
	lpEffect->Unknown76 = 1;
	lpEffect->WorldPos.X = WorldPos0;
	lpEffect->WorldPos.Y = WorldPos1;
	lpEffect->WorldPos.Z = WorldPos2;
	lpEffect->Unknown84.X = 0.0;
	lpEffect->Unknown84.Y = 0.0;
	lpEffect->Unknown84.Z = 0.0;

	switch (lpEffect->EffectID)
	{
	case 32587: //shiny06
		if (lpEffect->SubEffectID)
		{
			if (lpEffect->SubEffectID > 0 && lpEffect->SubEffectID <= 3)
			{
				lpEffect->Unknown60 = GetLargeRand() % 11 + 20;
				lpEffect->Unknown56 = 0.0;
				lpEffect->Unknown68 = (float)(GetLargeRand() % 180);
				lpEffect->Scale = Scale - (float)(GetLargeRand() % 6) * (Scale / 10.0f);

				switch (lpEffect->SubEffectID)
				{
				case 1:
					lpEffect->VecPos.X = (float)(GetLargeRand() % 31) - 15.0f + lpEffect->VecPos.X;
					lpEffect->VecPos.Y = (float)(GetLargeRand() % 31) - 15.0f + lpEffect->VecPos.Y;
					lpEffect->VecPos.Z = (float)(GetLargeRand() % 21) + 12.0f + lpEffect->VecPos.Z;
					break;
				case 2:
					lpEffect->VecPos.X = (float)(GetLargeRand() % 31) / 30.0f * 40.0f - 20.0f + lpEffect->VecPos.X;
					lpEffect->VecPos.Y = (float)(GetLargeRand() % 31) / 30.0f * 40.0f - 20.0f + lpEffect->VecPos.Y;
					lpEffect->VecPos.Z = (float)(GetLargeRand() % 24) + 14.0f + lpEffect->VecPos.Z;
					break;
				case 3:
					lpEffect->VecPos.X = (float)(GetLargeRand() % 31) / 30.0f * 70.0f - 35.0f + lpEffect->VecPos.X;
					lpEffect->VecPos.Y = (float)(GetLargeRand() % 31) / 30.0f * 70.0f - 35.0f + lpEffect->VecPos.Y;
					lpEffect->VecPos.Z = (float)(GetLargeRand() % 30) + 20.0f + lpEffect->VecPos.Z;
					break;
				}
			}
			else
			{
				switch (lpEffect->SubEffectID)
				{
				case 4:
					break;
				case 6:
					lpEffect->Unknown60 = 15;
					lpEffect->Unknown68 = (float)(GetLargeRand() % 360);
					lpEffect->Unknown84.X = (float)-(GetLargeRand() % 2 - 1);
					lpEffect->Unknown84.Y = (float)-(GetLargeRand() % 4);
					lpEffect->Unknown84.Z = (float)-(GetLargeRand() % 4);
					break;
				case 7:
					lpEffect->Scale = 0.1;
					lpEffect->VecPos2.X = Scale;
					lpEffect->Unknown60 = GetLargeRand() % 10 + 20;
					lpEffect->VecPos.X = (float)(GetLargeRand() % 50 - 25) + lpEffect->VecPos.X;
					lpEffect->VecPos.Y = (float)(GetLargeRand() % 50 - 25) + lpEffect->VecPos.Y;
					lpEffect->VecPos.Z = (float)(GetLargeRand() % 50 - 25) + lpEffect->VecPos.Z;
					lpEffect->Unknown80 = 1.0;
					lpEffect->WorldPos.X = (float)(GetLargeRand() % 360);
					lpEffect->WorldPos.Y = (float)(GetLargeRand() % 360);
					lpEffect->WorldPos.Z = (float)(GetLargeRand() % 360);
					lpEffect->Unknown68 = (float)(GetLargeRand() % 20 - 10);
					break;
				}
			}
		}
		else
		{
			lpEffect->Unknown60 = 18;
			lpEffect->WorldPos.X = 45.0;
		}
		break;
	// --
	case 52379: //hikorora Custom
		if (lpEffect->SubEffectID)
		{
			switch (lpEffect->SubEffectID)
			{
			case 1:
			case 2:
				lpEffect->Unknown60 = 15;
				lpEffect->Scale = 0.2;
				break;
			case 3:
				lpEffect->Scale = 0.0;
				lpEffect->Unknown60 = 35;
				break;
			case 4:
				lpEffect->Unknown68 = (float)(GetLargeRand() % 360);
				lpEffect->Unknown60 = 5;
				lpEffect->Scale = 1.2;
				break;
			case 5:
			case 6:
				lpEffect->Unknown60 = 6;
				lpEffect->Unknown68 = (int)(timeGetTime() * 0.75f) % 360;
				lpEffect->Unknown72 = 2;
				lpEffect->Scale = Scale - (float)(GetLargeRand() % 6) * (Scale / 10.0f) + 0.3;
				break;
			}
		}
		else
		{
			lpEffect->Unknown60 = 100;
			lpEffect->Scale = 0.2;
		}
		break;
	// --
	case 52229: //flareBlue Custom
		if (lpEffect->SubEffectID)
		{
			switch (lpEffect->SubEffectID)
			{
			case 6:
				lpEffect->Unknown56 = 1.0;
				lpEffect->Unknown84.X = (float)(GetLargeRand() % 8) + -4.0;
				lpEffect->Unknown84.Y = (float)(GetLargeRand() % 4);
				lpEffect->Unknown84.Z = (float)(GetLargeRand() % 8) + -4.0;
				lpEffect->Unknown60 = 12;
				lpEffect->Scale = Scale - (float)(GetLargeRand() % 4) * (Scale / 10.0f);
				break;
			}
		}
		break;
	// ==
		case 32355:
		if (lpEffect->SubEffectID)
		{
			if (lpEffect->SubEffectID > 0 && lpEffect->SubEffectID <= 3)
			{
				lpEffect->Unknown60 = GetLargeRand() % 11 + 20;
				lpEffect->Unknown56 = 0.0;
				lpEffect->Unknown68 = (float)(GetLargeRand() % 180);
				lpEffect->Scale = Scale - (float)(GetLargeRand() % 6) * (Scale / 10.0f);

				switch (lpEffect->SubEffectID)
				{
					case 1:
						lpEffect->VecPos.X = (float)(GetLargeRand() % 31) - 15.0f + lpEffect->VecPos.X;
						lpEffect->VecPos.Y = (float)(GetLargeRand() % 31) - 15.0f + lpEffect->VecPos.Y;
						lpEffect->VecPos.Z = (float)(GetLargeRand() % 21) + 12.0f + lpEffect->VecPos.Z;
						break;
					case 2:
						lpEffect->VecPos.X = (float)(GetLargeRand() % 31) / 30.0f * 40.0f - 20.0f + lpEffect->VecPos.X;
						lpEffect->VecPos.Y = (float)(GetLargeRand() % 31) / 30.0f * 40.0f - 20.0f + lpEffect->VecPos.Y;
						lpEffect->VecPos.Z = (float)(GetLargeRand() % 24) + 14.0f + lpEffect->VecPos.Z;
						break;
					case 3:
						lpEffect->VecPos.X = (float)(GetLargeRand() % 31) / 30.0f * 70.0f - 35.0f + lpEffect->VecPos.X;
						lpEffect->VecPos.Y = (float)(GetLargeRand() % 31) / 30.0f * 70.0f - 35.0f + lpEffect->VecPos.Y;
						lpEffect->VecPos.Z = (float)(GetLargeRand() % 30) + 20.0f + lpEffect->VecPos.Z;
						break;
				}
			}
			else
			{
				switch (lpEffect->SubEffectID)
				{
					case 4:

						break;
					case 6:
						lpEffect->Unknown60 = 15;
						lpEffect->Unknown68 = (float)(GetLargeRand() % 360);
						lpEffect->Unknown84.X = (float)-(GetLargeRand() % 2 - 1);
						lpEffect->Unknown84.Y = (float)-(GetLargeRand() % 4);
						lpEffect->Unknown84.Z = (float)-(GetLargeRand() % 4);
						break;
					case 7:
						lpEffect->Scale = (float)(GetLargeRand() % 8 + 1) * 0.1 * Scale;
						lpEffect->Unknown60 = GetLargeRand() % 20 + 20;
						lpEffect->Unknown56 = 1.0f;
						lpEffect->Unknown68 = (float)(GetLargeRand() % 180);
						break;
				}
			}
		}
		else
		{
			lpEffect->Unknown60 = 18;
			lpEffect->WorldPos.X = 45.0;
		}
		break; //return i; <---
	// ==
	case 32290:
		if (lpEffect->SubEffectID)
		{
			switch (lpEffect->SubEffectID)
			{
			case 0x11://for wings of conqueror
				lpEffect->Unknown68 = (float)(GetLargeRand() % 360);
				lpEffect->Unknown60 = 25;
				lpEffect->Scale = Scale;
				break;
			}
		}
		else
		{
			lpEffect->Unknown60 = 20;
			lpEffect->Unknown84.Z = (GetLargeRand() % 5 + 2);
		}
		//lpEffect->Unknown68 = (double)(GetLargeRand() % 360);
		//lpEffect->Scale = (double)(GetLargeRand() % 10 + 10) * 0.01999999955296516;
		// --
		lpEffect->VecPos.X = (double)(GetLargeRand() % 40) - 20.0 + lpEffect->VecPos.X;
		lpEffect->VecPos.Y = (double)(GetLargeRand() % 40) - 20.0 + lpEffect->VecPos.Y;
		lpEffect->VecPos.Z = (double)(GetLargeRand() % 20) - 10.0 + lpEffect->VecPos.Z;
		break;
		// ----
		case 32289: //Texture ID Main Season 13 -- Effect\\shiny06.jpg
		if (lpEffect->SubEffectID)
		{
			if (lpEffect->SubEffectID > 0 && lpEffect->SubEffectID <= 3)
			{
				lpEffect->Unknown60 = GetLargeRand() % 11 + 20;
				lpEffect->Unknown56 = 0.0;
				lpEffect->Unknown68 = (float)(GetLargeRand() % 180);
				lpEffect->Scale = Scale - (float)(GetLargeRand() % 6) * (Scale / 10.0f);

				switch (lpEffect->SubEffectID)
				{
					case 1:
						lpEffect->VecPos.X = (float)(GetLargeRand() % 31) - 15.0f + lpEffect->VecPos.X;
						lpEffect->VecPos.Y = (float)(GetLargeRand() % 31) - 15.0f + lpEffect->VecPos.Y;
						lpEffect->VecPos.Z = (float)(GetLargeRand() % 21) + 12.0f + lpEffect->VecPos.Z;
						break;
					case 2:
						lpEffect->VecPos.X = (float)(GetLargeRand() % 31) / 30.0f * 40.0f - 20.0f + lpEffect->VecPos.X;
						lpEffect->VecPos.Y = (float)(GetLargeRand() % 31) / 30.0f * 40.0f - 20.0f + lpEffect->VecPos.Y;
						lpEffect->VecPos.Z = (float)(GetLargeRand() % 24) + 14.0f + lpEffect->VecPos.Z;
						break;
					case 3:
						lpEffect->VecPos.X = (float)(GetLargeRand() % 31) / 30.0f * 70.0f - 35.0f + lpEffect->VecPos.X;
						lpEffect->VecPos.Y = (float)(GetLargeRand() % 31) / 30.0f * 70.0f - 35.0f + lpEffect->VecPos.Y;
						lpEffect->VecPos.Z = (float)(GetLargeRand() % 30) + 20.0f + lpEffect->VecPos.Z;
						break;
				}
			}
			else
			{
				switch (lpEffect->SubEffectID)
				{
				case 4:

					break;
				case 6:
					lpEffect->Unknown60 = 15;
					lpEffect->Unknown68 = (float)(GetLargeRand() % 360);
					lpEffect->Unknown84.X = (float)-(GetLargeRand() % 2 - 1);
					lpEffect->Unknown84.Y = (float)-(GetLargeRand() % 4);
					lpEffect->Unknown84.Z = (float)-(GetLargeRand() % 4);
					break;
				case 7:
					lpEffect->Scale = (float)(GetLargeRand() % 8 + 1) * 0.1 * Scale;
					lpEffect->Unknown60 = GetLargeRand() % 20 + 20;
					lpEffect->Unknown56 = 1.0f;
					lpEffect->Unknown68 = (float)(GetLargeRand() % 180);
					break;
				}
			}
		}
		else
		{
			lpEffect->Unknown60 = 18;
			lpEffect->WorldPos.X = 45.0;
		}
		break; //return i; <---

	}

	//return 0;

	return iResult;
}


void CRenderEffect::CreateItemEffect(int lpModel, int ItemID, vec3_t Light, float Alpha, int ItemLevel, int NewOption, int a10, int a11, int RenderType)
{
	pSetItemEffect(lpModel, ItemID, Light, Alpha, ItemLevel, NewOption, a10, a11, RenderType);

	#if(LUA_SCRIPT_EFFECT)
	g_RenderEffect.m_Lua.Generic_Call("LuaCreateEffect", "ii", lpModel, ItemID);
	#else
	g_RenderEffect.AddItemEffect(lpModel, ItemID);
	#endif
}

void CRenderEffect::DrawViewPortEffects(DWORD ObjectPointer, DWORD ObjectModel, DWORD a3)
{
	//lpViewObj Object = &*(ObjectPreview*)(ObjectPointer);

	//MU3Float lBone[MAX_MODEL_EFFECT];
	//MU3Float lBone2[MAX_MODEL_EFFECT];
	//vec3_t Color;
	//vec3_t ColorRandom;

	//for (int i = 0; i < MAX_MODEL_EFFECT; i++)
	//{
	//	lBone[i].X = *(float*)(ObjectModel + 252);
	//	lBone[i].Y = *(float*)(ObjectModel + 256);
	//	lBone[i].Z = *(float*)(ObjectModel + 260);
	//	lBone2[i].X =*(float*)(ObjectModel + 264);
	//	lBone2[i].Y =*(float*)(ObjectModel + 268);
	//	lBone2[i].Z =*(float*)(ObjectModel + 272);
	//}

	//Vector(1.0, 1.0, 1.0, Color);
	//Vector(((float)(rand() % 100) / 100), ((float)(rand() % 100) / 100), ((float)(rand() % 100) / 100), ColorRandom);

	//// -> Helm

	//for(int i = 0; i < MAX_MODEL_EFFECT; i++)	//QUANGKY
	//{
	//	if(Object->HelmSlot >= ITEM2(gCreateEffect.m_ModelEffectData[i].ItemType, gCreateEffect.m_ModelEffectData[i].ItemIndex) //&& Object->HelmSlot <= ITEM2(7, 255)
	//	/*&&
	//	   Object->HelmLevel >= gCreateEffect.m_ModelEffectData[i].MinLevel && Object->HelmLevel <= gCreateEffect.m_ModelEffectData[i].MaxLevel	&&
	//	   Object->HelmExcellent >= gCreateEffect.m_ModelEffectData[i].MinExcellent && Object->HelmExcellent <= gCreateEffect.m_ModelEffectData[i].MaxExcellent*/)
	//	{
	//		lBone[i].Z = lBone[i].Z + (float)(150);
	//		lBone2[i].Z = lBone2[i].Z + (float)(150);
	//		Vector(gCreateEffect.m_ModelEffectData[i].Color[0], gCreateEffect.m_ModelEffectData[i].Color[1], gCreateEffect.m_ModelEffectData[i].Color[2], Color);

	//		if(gCreateEffect.m_ModelEffectData[i].EffectIndex == 1)
	//		{
	//			sub_74CD30(gCreateEffect.m_ModelEffectData[i].EffectCode, (int)&lBone[i], (int)&lBone2[i], Color, gCreateEffect.m_ModelEffectData[i].EffectType, gCreateEffect.m_ModelEffectData[i].EffectScale, 0);	// 3
	//		} 
	//		else if(gCreateEffect.m_ModelEffectData[i].EffectIndex == 2)
	//		{
	//			sub_6D9070(gCreateEffect.m_ModelEffectData[i].EffectCode, (int)&lBone[i], (int)&lBone2[i], Color, gCreateEffect.m_ModelEffectData[i].EffectType, 0, 0, 0, 0, 0, 0.0, -1);
	//		}
	//		else
	//		{
	//			pPlayStaticEffect(gCreateEffect.m_ModelEffectData[i].EffectCode, (DWORD*)&lBone[i], gCreateEffect.m_ModelEffectData[i].EffectScale, Color, (int)&lBone2[i], 0, 0);
	//		}
	//	}
	//}

	//// -> Armor

	//for(int i = 0; i < MAX_MODEL_EFFECT; i++)
	//{
	//	if(
	//		Object->ArmorSlot == ITEM2(gCreateEffect.m_ModelEffectData[i].ItemType, gCreateEffect.m_ModelEffectData[i].ItemIndex) /*&&
	//	   Object->ArmorLevel >= gCreateEffect.m_ModelEffectData[i].MinLevel && Object->ArmorLevel <= gCreateEffect.m_ModelEffectData[i].MaxLevel &&
	//	   Object->ArmorExcellent >= gCreateEffect.m_ModelEffectData[i].MinExcellent && Object->ArmorExcellent <= gCreateEffect.m_ModelEffectData[i].MaxExcellent*/
	//	   )
	//	{
	//		lBone[i].Z = lBone[i].Z + (float)(120);
	//		lBone2[i].Z = lBone2[i].Z + (float)(120);
	//		Vector(gCreateEffect.m_ModelEffectData[i].Color[0], gCreateEffect.m_ModelEffectData[i].Color[1], gCreateEffect.m_ModelEffectData[i].Color[2], Color);

	//		if(gCreateEffect.m_ModelEffectData[i].EffectIndex == 1)
	//		{
	//			//sub_74CD30(gCreateEffect.m_ModelEffectData[i].EffectCode, (int)&lBone[i], (int)&lBone2[i], Color, gCreateEffect.m_ModelEffectData[i].EffectType, gCreateEffect.m_ModelEffectData[i].EffectScale, 0); // 3
	//			sub_74CD30(gCreateEffect.m_ModelEffectData[i].EffectCode, (int)&lBone[i], (int)&lBone2[i], Color, gCreateEffect.m_ModelEffectData[i].EffectType, gCreateEffect.m_ModelEffectData[i].EffectScale, 0); // 3
	//		}
	//		else if(gCreateEffect.m_ModelEffectData[i].EffectIndex == 2)
	//		{
	//			sub_6D9070(gCreateEffect.m_ModelEffectData[i].EffectCode, (int)&lBone[i], (int)&lBone2[i], Color, gCreateEffect.m_ModelEffectData[i].EffectType, 0, 0, 0, 0, 0, 0.0, -1);
	//		}
	//		else
	//		{
	//			pPlayStaticEffect(gCreateEffect.m_ModelEffectData[i].EffectCode, (DWORD*)&lBone[i], gCreateEffect.m_ModelEffectData[i].EffectScale, Color, (int)&lBone2[i], 0, 0);
	//		}
	//	}
	//}

	//// -> Pants

	//for (int i = 0; i < MAX_MODEL_EFFECT; i++)
	//{
	//	
	//	if(Object->PantsSlot == ITEM2(gCreateEffect.m_ModelEffectData[i].ItemType, gCreateEffect.m_ModelEffectData[i].ItemIndex) /*&&
	//		Object->PantsLevel >= gCreateEffect.m_ModelEffectData[i].MinLevel && Object->PantsLevel <= gCreateEffect.m_ModelEffectData[i].MaxLevel &&
	//		Object->PantsExcellent >= gCreateEffect.m_ModelEffectData[i].MinExcellent && Object->PantsExcellent <= gCreateEffect.m_ModelEffectData[i].MaxExcellent*/)
	//		{
	//			lBone[i].Z = lBone[i].Z + (float)(60);
	//			lBone2[i].Z = lBone2[i].Z + (float)(60);
	//			Vector(gCreateEffect.m_ModelEffectData[i].Color[0], gCreateEffect.m_ModelEffectData[i].Color[1], gCreateEffect.m_ModelEffectData[i].Color[2], Color);
	//			if(gCreateEffect.m_ModelEffectData[i].EffectIndex == 1)
	//			{sub_74CD30(gCreateEffect.m_ModelEffectData[i].EffectCode, (int)&lBone[i], (int)&lBone2[i], Color, gCreateEffect.m_ModelEffectData[i].EffectType, gCreateEffect.m_ModelEffectData[i].EffectScale, 0);} // 3}
	//			else if(gCreateEffect.m_ModelEffectData[i].EffectIndex == 2)
	//			{sub_6D9070(gCreateEffect.m_ModelEffectData[i].EffectCode, (int)&lBone[i], (int)&lBone2[i], Color, gCreateEffect.m_ModelEffectData[i].EffectType, 0, 0, 0, 0, 0, 0.0, -1);}
	//			else
	//			pPlayStaticEffect(gCreateEffect.m_ModelEffectData[i].EffectCode, (DWORD*)&lBone[i], gCreateEffect.m_ModelEffectData[i].EffectScale, Color, (int)&lBone2[i], 0, 0);
	//		}
	//}

	//// -> Boots

	//for (int i = 0; i < MAX_MODEL_EFFECT; i++)	//QUANGKY
	//{
	//	if(Object->BootsSlot == ITEM2(gCreateEffect.m_ModelEffectData[i].ItemType, gCreateEffect.m_ModelEffectData[i].ItemIndex) /*&&
	//		Object->BootsLevel >= gCreateEffect.m_ModelEffectData[i].MinLevel && Object->BootsLevel <= gCreateEffect.m_ModelEffectData[i].MaxLevel &&
	//		Object->BootsExcellent >= gCreateEffect.m_ModelEffectData[i].MinExcellent && Object->BootsExcellent <= gCreateEffect.m_ModelEffectData[i].MaxExcellent*/)
	//		{
	//			if (Object->WingsSlot >= 1)
	//			{
	//				if (Object->InSafeZone)
	//				{
	//					lBone[i].Z = lBone[i].Z + (float)(20);
	//					lBone2[i].Z = lBone2[i].Z + (float)(20);
	//				}
	//				else
	//				{
	//					lBone[i].Z = lBone[i].Z + (float)(80);
	//					lBone2[i].Z = lBone2[i].Z + (float)(80);
	//				}
	//			}
	//			else
	//			{
	//				lBone[i].Z = lBone[i].Z + (float)(20);
	//				lBone2[i].Z = lBone2[i].Z + (float)(20);
	//			}
	//			Vector(gCreateEffect.m_ModelEffectData[i].Color[0], gCreateEffect.m_ModelEffectData[i].Color[1], gCreateEffect.m_ModelEffectData[i].Color[2], Color);
	//			if(gCreateEffect.m_ModelEffectData[i].EffectIndex == 1)
	//			{sub_74CD30(gCreateEffect.m_ModelEffectData[i].EffectCode, (int)&lBone[i], (int)&lBone2[i], Color, gCreateEffect.m_ModelEffectData[i].EffectType, gCreateEffect.m_ModelEffectData[i].EffectScale, 0);} // 3}
	//			else if(gCreateEffect.m_ModelEffectData[i].EffectIndex == 2)
	//			{sub_6D9070(gCreateEffect.m_ModelEffectData[i].EffectCode, (int)&lBone[i], (int)&lBone2[i], Color, gCreateEffect.m_ModelEffectData[i].EffectType, 0, 0, 0, 0, 0, 0.0, -1);}
	//			else
	//			{
	//				pPlayStaticEffect(gCreateEffect.m_ModelEffectData[i].EffectCode, (DWORD*)&lBone[i], gCreateEffect.m_ModelEffectData[i].EffectScale, Color, (int)&lBone2[i], 0, 0);
	//			}
	//		}

	//}

	//pDrawViewPortEffects(ObjectPointer, ObjectModel,  a3);
}

void __declspec(naked) CRenderEffect::WingsSetInvisibleEffect()
//Naked ( WingsSetInvisibleEffect ) {
{
    static DWORD WingsSetInvisibleEffect_Pointer;
    static DWORD WingsSetInvisibleEffect_Buff;
    _asm {
        mov WingsSetInvisibleEffect_Buff, esi
        // ----
        mov ecx, dword ptr ss : [ebp + 8]
        mov esi, dword ptr ds : [ecx + 0x30]
        mov WingsSetInvisibleEffect_Pointer, esi
        // ----
        mov esi, WingsSetInvisibleEffect_Buff
    }

    // ----
    if ( WingsSetInvisibleEffect_Pointer == 0x1EA5
            || WingsSetInvisibleEffect_Pointer == ITEM2 ( 12, 234 )
            || WingsSetInvisibleEffect_Pointer == ITEM2 ( 12, 235 )
            || WingsSetInvisibleEffect_Pointer == ITEM2 ( 12, 236 )
            || WingsSetInvisibleEffect_Pointer == ITEM2 ( 12, 224 )
            || WingsSetInvisibleEffect_Pointer == ITEM2 ( 12, 226 )
            || WingsSetInvisibleEffect_Pointer == ITEM2 ( 12, 227 )
            || WingsSetInvisibleEffect_Pointer == ITEM2 ( 12, 220 )
            || WingsSetInvisibleEffect_Pointer == ITEM2 ( 12, 230 )
            || WingsSetInvisibleEffect_Pointer == ITEM2 ( 12, 231 )
            || WingsSetInvisibleEffect_Pointer == ITEM2 ( 12, 249 )
            || WingsSetInvisibleEffect_Pointer == ITEM2 ( 12, 242 ) 
			
			|| WingsSetInvisibleEffect_Pointer == ITEM2 ( 0, 44 )
			) {
        _asm {
            mov WingsSetInvisibleEffect_Buff, 0x0060B37A
            jmp WingsSetInvisibleEffect_Buff
        }
    }
    else {
        _asm {
            mov WingsSetInvisibleEffect_Buff, 0x0060B41D
            jmp WingsSetInvisibleEffect_Buff
        }
    }
}

void __declspec(naked) CRenderEffect::HieuUngBufferGlow() 
{
    DWORD dwItem;
    _asm {
        MOV EAX, DWORD PTR SS : [EBP + 0x10]
        MOV dwItem, EAX
        // ----
        CMP dwItem, ITEM2 ( 12, 234 )
        JE Return
        CMP dwItem, ITEM2 ( 12, 247 )
        JE Return
        CMP dwItem, ITEM2 ( 12, 248 )
        JE Return
        CMP dwItem, ITEM2 ( 12, 250 )
        JE Return
        CMP dwItem, ITEM2 ( 12, 251 )
        JE Return
        CMP dwItem, ITEM2 ( 0, 44 )
        JE Return
        Return :
        MOV EAX, 0x005FF983
        JMP EAX
    }
}

//void CreateItemEffect(int lpModel, int ItemID, vec3_t Light, float Alpha, int ItemLevel, int NewOption, int a10, int a11, int RenderType)
//{
//	pSetItemEffect(lpModel, ItemID, Light, Alpha, ItemLevel, NewOption, a10, a11, RenderType);
//
//	LPVOID Model = pGetModel(pModelThis(), ItemID);
//
//	vec3_t p;
//	vec3_t Bone;
//	vec3_t Color;
//	vec3_t WorldPos;
//
//	Vector(0.0f, 0.0f, 0.0f, p);
//	Vector(WorldPos[0], WorldPos[1], WorldPos[2], WorldPos);
//
//	switch (ItemID)
//	{
//		case ITEM2(0, 44): //Blessed Sword
//		{
//			float v234 = GetRender(-4.0, 0.0);
//			float v1875 = v234 * 0.5 + 0.5;
//			Vector(v1875 * 0.4000000059604645, v1875 * 0.550000011920929, v1875 * 0.1500000059604645, Color);
//			for (int i43 = 53; i43 < 129; ++i43 )
//			{
//				pQuickPlayStaticEffect(Model, 32002, i43, 0.64999998, Color, lpModel);
//			}
//			float v237 = ((int) timeGetTime() % 15) / 37.5;
//			float v1879 = v237 + 0.5;
//			Vector(v1879, v1879, v1879, Color);
//			for(int i44 = 4; i44 < 23; ++i44)
//			{
//				pQuickPlayStaticEffect(Model, 32229, i44, 0.30000001, Color, lpModel);
//			}
//			pQuickPlayStaticEffect(Model, 32229, 47, 0.30000001, Color, lpModel);
//			pQuickPlayStaticEffect(Model, 32229, 23, 0.30000001, Color, lpModel);
//			Vector(v1875 * 0.8500000238418579, v1875 * 0.1000000014901161, v1875 * 0.8999999761581421, Color);
//			pQuickPlayStaticEffect(Model, 32229, 45, 0.80000001, Color, lpModel);
//			pQuickPlayStaticEffect(Model, 32229, 46, 0.80000001, Color, lpModel);
//			pQuickPlayStaticEffect(Model, 32229, 28, 0.80000001, Color, lpModel);
//			pQuickPlayStaticEffect(Model, 32229, 30, 0.80000001, Color, lpModel);
//			Vector(v1875 * 0.1500000059604645, v1875 * 0.1500000059604645, v1875 * 0.8999999761581421, Color);
//			int JointID1[] = { 27,32,29,43,34,40,37,35,25,41,42,44 };
//			int JointID2[] = { 34,40,36,38 };
//			for ( int i45 = 0; i45 < 12; ++i45 )
//			{
//				pQuickPlayStaticEffect(Model, 32002, JointID1[i45], 0.60000002, Color, lpModel);
//			}
//			for ( int i46 = 0; i46 < 4; ++i46 )
//			{
//				pQuickPlayStaticEffect(Model, 32002, JointID2[i46], 0.30000001, Color, lpModel);
//			}
//			if(GetRender(-4.0, 0.0) + 0.5 <= 1.0)
//			  float v1163 = 1.0;
//			else
//			  float v1163 = GetRender(-4.0, 0.0) + 0.5;
//			Vector(v1875 * 0.2000000029802322, v1875 * 0.300000011920929, v1875 * 1.0, Color);
//			pQuickPlayStaticEffect(Model, 32114, 1, 1.4, Color, lpModel);
//		
//			if (*(BYTE*)(oUserPreviewStruct+14) == 0 && pPlayerState == 5 )
//			{
//				float ColorR[3] = { (int)timeGetTime() % 11 * 0.1000000014901161 * v1875 + 0.699999988079071,
//									(int)timeGetTime() % 11 * 0.1000000014901161 * v1875 + 0.699999988079071, 
//									(int)timeGetTime() % 11 * 0.1000000014901161 * v1875 + 0.699999988079071 };
//				ColorR[GetLargeRand() % 3] = 0.69999999f;
//				ColorR[GetLargeRand() % 3] = 1.0f;
//
//				pAllowPlayEffect(Model, Bone, lpModel, 27, 0);
//				float v240 = ((int) timeGetTime() % 1441) * 0.25;
//				pPlayStaticEffect(32805, (DWORD*)Bone, 1.0, Color, lpModel, v240, 0);
//				pAllowPlayEffect(Model, Bone, lpModel, 32, (int)&p);
//				float v241 = (double)(1440 - ((int) timeGetTime() % 1441) * 0.25);
//				pPlayStaticEffect(32805, (DWORD*)Bone, 1.0, ColorR, lpModel, v241, 0);
//				pAllowPlayEffect(Model, Bone, lpModel, 1, 0);
//				WorldPos[0] = Bone[0] - WorldPos[0];
//				WorldPos[1] = Bone[1] - WorldPos[1];
//				WorldPos[2] = Bone[2] - WorldPos[2];
//				//gCreateEffect.DynamicEffectEx(52379, Bone, WorldPos, ColorR, 6, 1.0f, &*(ObjectModel*)Model);
//				gCreateEffect.DynamicEffectEx(52379, Bone, WorldPos, ColorR, 6, 1.0f, &*(ObjectModel*)Model);
//			}
//		}
//		break;
//
//		case ITEM2(12, 186)://Wings of chaos
//		{
//			float v89 = timeGetTime() * 0.002000000094994903f;
//			float v90 = cosf(v89);
//			float v308 = absf(v90);
//
//			Vector(v308 + 0.300000011920929f, v308 + 0.300000011920929f, v308 + 0.300000011920929f, Color);
//			pQuickPlayStaticEffect(Model, 32501, 43, 0.40000001f, Color, lpModel);
//
//			float v91 = timeGetTime() * 0.05000000074505806f;
//			float v93 = cosf(v91);
//			v308 = absf(v93);
//
//			Vector(v308 + 0.300000011920929f, v308 + 0.300000011920929f, v308 + 0.300000011920929f, Color);
//			pQuickPlayStaticEffect(Model, 32836, 43, 0.60000002f, Color, lpModel);
//
//			Vector(1.0, 0.30000001, 1.0, Color);
//			pQuickPlayStaticEffect(Model, 32783, 43, 0.2f, Color, lpModel);
//
//			Vector(1.0, 1.0, 1.0, Color);
//			pQuickPlayStaticEffect(Model, 32836, 43, 0.15000001f, Color, lpModel);
//		}
//		break;
//	}
//}

//void TestItemEffect(int lpModel, int ItemID)
//{
//	LPVOID Model;
//
//	//Model = pGetModel(pModelThis(), ItemID);
//	gCreateEffect.m_Lua.Generic_Call("Proc_GetModel", "i>i", ItemID, &Model);
//
//	vec3_t p;
//	vec3_t Bone;
//	vec3_t Color;
//	vec3_t WorldPos;
//
//	double dGetParam = 0.0;
//	double flColor[3] = { 0.0, 0.0, 0.0 };
//
//	//Vector(0.0f, 0.0f, 0.0f, p);
//	/*
//	gCreateEffect.m_Lua.Generic_Call("Run_GetVector", "ddd>ddd", 0.0f, 0.0f, 0.0f, &flColor[0], &flColor[1], &flColor[2]);
//	p[0] = flColor[0];
//	p[1] = flColor[1];
//	p[2] = flColor[2];
//	
//	Bone[0] = flColor[0];
//	Bone[1] = flColor[1];
//	Bone[2] = flColor[2];
//	*/
//	gCreateEffect.m_Lua.Generic_Call("Lua_Vector", "dddi",0.0f, 0.0f, 0.0f, (int)&p);
//
//
//	//Vector(WorldPos[0], WorldPos[1], WorldPos[2], WorldPos);
//	/*gCreateEffect.m_Lua.Generic_Call("Run_GetVector", "ddd>ddd", WorldPos[0], WorldPos[1], WorldPos[2], &flColor[0], &flColor[1], &flColor[2]);
//	WorldPos[0] = flColor[0];
//	WorldPos[1] = flColor[1];
//	WorldPos[2] = flColor[2];*/
//	gCreateEffect.m_Lua.Generic_Call("Lua_Vector", "dddi", WorldPos[0], WorldPos[1], WorldPos[2], (int)&WorldPos);
//
//	switch (ItemID)
//	{
//		case ITEM2(0, 44): //Blessed Sword
//		{
//			float v234;
//			//v234 = GetRender(-4.0, 0.0);
//			gCreateEffect.m_Lua.Generic_Call("Proc_Get4EC46D", "dd>d", -4.0, 0.0, &dGetParam);
//			v234 = dGetParam;
//
//			float v1875 = v234 * 0.5 + 0.5;
//			//Vector(v1875 * 0.4000000059604645, v1875 * 0.550000011920929, v1875 * 0.1500000059604645, Color);
//			////
//			
//			/*
//			gCreateEffect.m_Lua.Generic_Call("Run_GetVector", "ddd>ddd", 
//				(v1875 * 0.4000000059604645), (v1875 * 0.550000011920929), (v1875 * 0.1500000059604645), 
//				&flColor[0], &flColor[1], &flColor[2]);
//
//			Color[0] = flColor[0];
//			Color[1] = flColor[1];
//			Color[2] = flColor[2];
//			*/
//			////
//			gCreateEffect.m_Lua.Generic_Call("Lua_Vector", "dddi", v1875 * 0.4000000059604645, v1875 * 0.550000011920929, v1875 * 0.1500000059604645, (int)&Color);
//	
//
//
//			for (int i43 = 53; i43 < 129; ++i43 )
//			{
//				//pQuickPlayStaticEffect(Model, 32002, i43, 0.64999998, Color, lpModel);
//				//gCreateEffect.m_Lua.Generic_Call("Proc_QuickPlayStaticEffect", "iiiddddi", Model, 32002, i43, 0.64999998, Color[0], Color[1], Color[2], lpModel);
//				gCreateEffect.m_Lua.Generic_Call("Run_QuickPlayStaticEffect", "iiidii", Model, 32002, i43, 0.64999998, (int)&Color, lpModel);
//			}
//
//	//return;
//
//			float v237 = ((int) *(float*)0x5EF5A1C % 15) / 37.5;
//			float v1879 = v237 + 0.5;
//			//Vector(v1879, v1879, v1879, Color);
//			//gCreateEffect.m_Lua.Generic_Call("Run_GetVector", "ddd>ddd", v1879, v1879, v1879, &flColor[0], &flColor[1], &flColor[2]);
//			//Color[0] = flColor[0];
//			//Color[1] = flColor[1];
//			//Color[2] = flColor[2];
//			gCreateEffect.m_Lua.Generic_Call("Lua_Vector", "dddi", v1879, v1879, v1879, (int)&Color);
//
//			for(int i44 = 4; i44 < 23; ++i44)
//			{
//				//pQuickPlayStaticEffect(Model, 32229, i44, 0.30000001, Color, lpModel);
//				//gCreateEffect.m_Lua.Generic_Call("Proc_QuickPlayStaticEffect", "iiiddddi", Model, 32229, i44, 0.30000001, Color[0], Color[1], Color[2], lpModel);
//				gCreateEffect.m_Lua.Generic_Call("Run_QuickPlayStaticEffect", "iiidii", Model, 32229, i44, 0.30000001, (int)&Color, lpModel);
//			}
//			//pQuickPlayStaticEffect(Model, 32229, 47, 0.30000001, Color, lpModel);
//			//gCreateEffect.m_Lua.Generic_Call("Proc_QuickPlayStaticEffect", "iiiddddi", Model, 32229, 47, 0.30000001, Color[0], Color[1], Color[2], lpModel);
//			gCreateEffect.m_Lua.Generic_Call("Run_QuickPlayStaticEffect", "iiidii", Model, 32229, 47, 0.30000001, (int)&Color, lpModel);
//			//pQuickPlayStaticEffect(Model, 32229, 23, 0.30000001, Color, lpModel);
//			//gCreateEffect.m_Lua.Generic_Call("Proc_QuickPlayStaticEffect", "iiiddddi", Model, 32229, 23, 0.30000001, Color[0], Color[1], Color[2], lpModel);
//			gCreateEffect.m_Lua.Generic_Call("Run_QuickPlayStaticEffect", "iiidii", Model, 32229, 23, 0.30000001, (int)&Color, lpModel);
//			//Vector(v1875 * 0.8500000238418579, v1875 * 0.1000000014901161, v1875 * 0.8999999761581421, Color);
//			//gCreateEffect.m_Lua.Generic_Call("Run_GetVector", "ddd>ddd", v1875 * 0.8500000238418579, v1875 * 0.1000000014901161, v1875 * 0.8999999761581421, &flColor[0], &flColor[1], &flColor[2]);
//			//Color[0] = flColor[0];
//			//Color[1] = flColor[1];
//			//Color[2] = flColor[2];
//			gCreateEffect.m_Lua.Generic_Call("Lua_Vector", "dddi", v1875 * 0.8500000238418579, v1875 * 0.1000000014901161, v1875 * 0.8999999761581421, (int)&Color);
//
//			//pQuickPlayStaticEffect(Model, 32229, 45, 0.80000001, Color, lpModel);
//			//gCreateEffect.m_Lua.Generic_Call("Proc_QuickPlayStaticEffect", "iiiddddi", Model, 32229, 45, 0.80000001, Color[0], Color[1], Color[2], lpModel);
//			gCreateEffect.m_Lua.Generic_Call("Run_QuickPlayStaticEffect", "iiidii", Model, 32229, 45, 0.80000001, (int)&Color, lpModel);
//			//pQuickPlayStaticEffect(Model, 32229, 46, 0.80000001, Color, lpModel);
//			//gCreateEffect.m_Lua.Generic_Call("Proc_QuickPlayStaticEffect", "iiiddddi", Model, 32229, 46, 0.80000001, Color[0], Color[1], Color[2], lpModel);
//			gCreateEffect.m_Lua.Generic_Call("Run_QuickPlayStaticEffect", "iiidii", Model, 32229, 46, 0.80000001, (int)&Color, lpModel);
//			//pQuickPlayStaticEffect(Model, 32229, 28, 0.80000001, Color, lpModel);
//			//gCreateEffect.m_Lua.Generic_Call("Proc_QuickPlayStaticEffect", "iiiddddi", Model, 32229, 28, 0.80000001, Color[0], Color[1], Color[2], lpModel);
//			gCreateEffect.m_Lua.Generic_Call("Run_QuickPlayStaticEffect", "iiidii", Model, 32229, 28, 0.80000001, (int)&Color, lpModel);
//			//pQuickPlayStaticEffect(Model, 32229, 30, 0.80000001, Color, lpModel);
//			//gCreateEffect.m_Lua.Generic_Call("Proc_QuickPlayStaticEffect", "iiiddddi", Model, 32229, 30, 0.80000001, Color[0], Color[1], Color[2], lpModel);
//			gCreateEffect.m_Lua.Generic_Call("Run_QuickPlayStaticEffect", "iiidii", Model, 32229, 30, 0.80000001, (int)&Color, lpModel);
//			//Vector(v1875 * 0.1500000059604645, v1875 * 0.1500000059604645, v1875 * 0.8999999761581421, Color);
//			//gCreateEffect.m_Lua.Generic_Call("Run_GetVector", "ddd>ddd", v1875 * 0.1500000059604645, v1875 * 0.1500000059604645, v1875 * 0.8999999761581421, &flColor[0], &flColor[1], &flColor[2]);
//			//Color[0] = flColor[0];
//			//Color[1] = flColor[1];
//			//Color[2] = flColor[2];
//			gCreateEffect.m_Lua.Generic_Call("Lua_Vector", "dddi", v1875 * 0.1500000059604645, v1875 * 0.1500000059604645, v1875 * 0.8999999761581421, (int)&Color);
//
//			int JointID1[] = { 27,32,29,43,34,40,37,35,25,41,42,44 };
//			int JointID2[] = { 34,40,36,38 };
//
//			for ( int i45 = 0; i45 < 12; ++i45 )
//			{
//				//pQuickPlayStaticEffect(Model, 32002, JointID1[i45], 0.60000002, Color, lpModel);
//				//gCreateEffect.m_Lua.Generic_Call("Proc_QuickPlayStaticEffect", "iiiddddi", Model, 32002, JointID1[i45], 0.60000002, Color[0], Color[1], Color[2], lpModel);
//				gCreateEffect.m_Lua.Generic_Call("Run_QuickPlayStaticEffect", "iiidii", Model, 32002, JointID1[i45], 0.60000002, (int)&Color, lpModel);
//			}
//			for ( int i46 = 0; i46 < 4; ++i46 )
//			{
//				//pQuickPlayStaticEffect(Model, 32002, JointID2[i46], 0.30000001, Color, lpModel);
//				//gCreateEffect.m_Lua.Generic_Call("Proc_QuickPlayStaticEffect", "iiiddddi", Model, 32002, JointID1[i46], 0.60000002, Color[0], Color[1], Color[2], lpModel);
//				gCreateEffect.m_Lua.Generic_Call("Run_QuickPlayStaticEffect", "iiidii", Model, 32002, JointID2[i46], 0.30000001, (int)&Color, lpModel);
//			}
//
//			//if(GetRender(-4.0, 0.0) + 0.5 <= 1.0)
//			//  float v1163 = 1.0;
//			//else
//			//  float v1163 = GetRender(-4.0, 0.0) + 0.5;
//
//			float v1163 = 0.0;
//
//			gCreateEffect.m_Lua.Generic_Call("Proc_Get4EC46D", "dd>d", -4.0, 0.0, &dGetParam);
//			v1163 = dGetParam;
//
//
//			if(v1163 + 0.5 <= 1.0)
//			{
//			  v1163 = 1.0;
//			}
//			else
//			{
//				gCreateEffect.m_Lua.Generic_Call("Proc_Get4EC46D", "dd>d", -4.0, 0.0, &dGetParam);
//				v1163 = dGetParam + 0.5;
//			}
//
//			//Vector(v1875 * 0.2000000029802322, v1875 * 0.300000011920929, v1875 * 1.0, Color);
//			//gCreateEffect.m_Lua.Generic_Call("Run_GetVector", "ddd>ddd",v1875 * 0.2000000029802322, v1875 * 0.300000011920929, v1875 * 1.0, &flColor[0], &flColor[1], &flColor[2]);
//			//Color[0] = flColor[0];
//			//Color[1] = flColor[1];
//			//Color[2] = flColor[2];
//			gCreateEffect.m_Lua.Generic_Call("Lua_Vector", "dddi", v1875 * 0.2000000029802322, v1875 * 0.300000011920929, v1875 * 1.0, (int)&Color);
//
//			//pQuickPlayStaticEffect(Model, 32114, 1, 1.4, Color, lpModel);
//			//gCreateEffect.m_Lua.Generic_Call("Proc_QuickPlayStaticEffect", "iiiddddi", Model, 32114, 1, 1.4, Color[0], Color[1], Color[2], lpModel);
//			gCreateEffect.m_Lua.Generic_Call("Run_QuickPlayStaticEffect", "iiidii", Model, 32114, 1, 1.4, (int)&Color, lpModel);
//			
//			if (*(BYTE*)(oUserPreviewStruct+14) == 0 && pPlayerState == 5 )
//			{
//				float ColorR[3] = { (int)*(float*)0x5EF5A1C % 11 * 0.1000000014901161 * v1875 + 0.699999988079071,
//									(int)*(float*)0x5EF5A1C % 11 * 0.1000000014901161 * v1875 + 0.699999988079071, 
//									(int)*(float*)0x5EF5A1C % 11 * 0.1000000014901161 * v1875 + 0.699999988079071 };
//				ColorR[GetLargeRand() % 3] = 0.69999999f;
//				ColorR[GetLargeRand() % 3] = 1.0f;
//
//				pAllowPlayEffect(Model, Bone, lpModel, 27, 0);
//				//gCreateEffect.m_Lua.Generic_Call("Proc_AllowPlayEffect", "idddiii", Model, Bone[0], Bone[1], Bone[2], lpModel, 27, 0);
//				gCreateEffect.m_Lua.Generic_Call("Proc_AllowPlayEffect2", "iiiii", Model, (int)&Bone, lpModel, 27, 0);
//
//				float v240 = ((int) *(float*)0x5EF5A1C % 1441) * 0.25;
//				pPlayStaticEffect(32805, (DWORD*)Bone, 1.0, Color, lpModel, v240, 0);
//				//gCreateEffect.m_Lua.Generic_Call("Proc_PlayStaticEffect", "iidiidi", 32805, (DWORD*)Bone, 1.0, (int)&Color, lpModel, v240, 0);//*
//
//				//pAllowPlayEffect(Model, Bone, lpModel, 32, (int)&p);
//				//pAllowPlayEffect(Model, Bone, lpModel, 32, 0);
//				//gCreateEffect.m_Lua.Generic_Call("Proc_AllowPlayEffect", "idddiii>i", Model, Bone[0], Bone[1], Bone[2], lpModel, 32, (int)&p, (int)&p);
//				gCreateEffect.m_Lua.Generic_Call("Proc_AllowPlayEffect2", "iiiii", Model, (int)&Bone, lpModel, 32, (int)&p);
//
//				float v241 = (double)(1440 - ((int) *(float*)0x5EF5A1C % 1441) * 0.25);
//				pPlayStaticEffect(32805, (DWORD*)Bone, 1.0, ColorR, lpModel, v241, 0);
//				//gCreateEffect.m_Lua.Generic_Call("Proc_PlayStaticEffect", "iidiidi", 32805, (DWORD*)Bone, 1.0, (int)&ColorR, lpModel, v241, 0);//*
//
//				//pAllowPlayEffect(Model, Bone, lpModel, 1, 0);
//				//gCreateEffect.m_Lua.Generic_Call("Proc_AllowPlayEffect", "idddiii", Model, Bone[0], Bone[1], Bone[2], lpModel, 1, 0);
//				gCreateEffect.m_Lua.Generic_Call("Proc_AllowPlayEffect2", "iiiii", Model, (int)&Bone, lpModel, 1, 0);
//
//				WorldPos[0] = Bone[0] - WorldPos[0];
//				WorldPos[1] = Bone[1] - WorldPos[1];
//				WorldPos[2] = Bone[2] - WorldPos[2];
//				gCreateEffect.DynamicEffectEx(52379, Bone, WorldPos, ColorR, 6, 1.0f, &*(ObjectModel*)Model);
//				//gCreateEffect.DynamicEffectEx(52379, Bone, WorldPos, ColorR, 6, 1.0f, &*(ObjectModel*)Model);
//				//gCreateEffect.m_Lua.Generic_Call("Proc_DynamicEffectEx", "iiiiidi", 52379, (int)&Bone, (int)&WorldPos, (int)&ColorR, 6, 1.0f, &*(ObjectModel*)Model);
//			}
//		}
//		break;
//	}
//}

#endif