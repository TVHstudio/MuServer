#pragma once

#if(ENABLE_RENDER_EFFECT)

/*
	if (*(BYTE*)(oUserPreviewStruct+14) == 0 && pPlayerState == 5 ) //<< Si el PJ esta en Zona Safe y Select Character
	Sword = 32805
	Арбалето?= 52229
	Скипет?= 32805
	Стик = 32113
*/

#include "Object.h"
#include "MuLua.h"

#define LUA_SCRIPT_EFFECT		1

#define MAX_MODEL_EFFECT		200

#define pQuickPlayStaticEffect	((int(__cdecl*)(LPVOID Model, int ModelID, int Joint, float size, vec3_t Color, int ObjModel)) 0x565560)
#define pAllowPlayEffect		((void(__thiscall*)(LPVOID This, vec3_t Bone1, int lpModel, signed int joint, int a5)) 0x544E60)
#define pPlayStaticEffectZt		((int(__cdecl*)(int ModelID, vec3_t Bone1, float size, vec3_t Color, int ObjPos, float, int)) 0x7711C0)
#define pPlayDynamicEffectEx	((int(__cdecl*)(int ModelID, vec3_t VecPos, vec3_t WorlPos, vec3_t color, int effectID, float size, int)) 0x74CBE0)
#define pSetItemEffect			((void(__cdecl*)(int lpModel, int ItemID, vec3_t Light, float Alpha, int ItemLevel, int NewOption, int a10, int a11, int RenderType)) 0x00609E70)
#define pModelThis				((LPVOID(*)())0x004CDA10)	//OK
#define pGetModel				((LPVOID(__thiscall*)(LPVOID This, signed int a2)) 0x00969AD0)
#define pDrawViewPortEffects	((int(__cdecl*)(DWORD ObjectPointer, DWORD ModelPointer, int a3)) 0x56F210)
#define sub_6D9070				((void(__cdecl*)(int a1, int a2, int a3, float * a4, int a5, int a6, __int16 a7, __int16 a8, __int16 a9, __int16 a10, float a11, __int16 a12)) 0x6D8F20)
#define sub_74CD30				((int(__cdecl*)(int a1, int a2, int a3, vec3_t a4, int a5, float a6, int a7)) 0x74CBE0)
#define pInitModelData2			((void(__cdecl*)()) 0x00626190)

struct MU3Float
{
	float X;
	float Y;
	float Z;
};

struct MODEL_EFFECT_INFO
{
	int		Index;
	int		ItemType;
	int		ItemIndex;
	int		MinLevel;
	int		MaxLevel;
	int		MinExcellent;
	int		MaxExcellent;
	float	Color[3];
	int		EffectIndex;
	int		EffectType;
	int		EffectCode;		
	int		EffectScale;
};

#pragma pack(push, 1)
struct DYNAMIC_EFFECT_INFO //(size: 132)
{
	/*+0*/ bool Enable; //int
	BYTE gap1[3];
	/*+4*/ DWORD EffectID;
	/*+8*/ DWORD TextureID;
	/*+12*/ int SubEffectID;
	/*+16*/ float Scale;
	/*+20*/ VAngle VecPos;
	/*+32*/ VAngle WorldPos;
	/*+44*/ VAngle Color;
	/*+56*/ float Unknown56; //Alpha
	/*+60*/ DWORD Unknown60;
	/*+64*/ ObjectModel * m_Owner;
	/*+68*/ float Unknown68; //
	/*+72*/ DWORD Unknown72;
	/*+76*/ BYTE Unknown76; //int
	BYTE Gap01[3];
	/*+80*/ float Unknown80;
	/*+84*/ VAngle Unknown84;
	/*+96*/ VAngle Color2;
	/*+108*/ VAngle VecPos2;
	BYTE Gap02[12];
};
#pragma pack(pop)

class CRenderEffect
{
public:
		 CRenderEffect();
		~CRenderEffect();

	void Init();
	void Load();
	void Read(char* filename);

	float GetRender(float a1, float a2);
	double absf(float a1);
	double sub_4E7B95(float a1);
	
	void AddItemEffect(int lpModel, int ItemID);
	int AddDynamicEffect(DWORD ModelID, vec3_t VecPos, vec3_t WorldPos, vec3_t Color, int SubEffectID, float Scale, ObjectModel* lpModel);
	int AddDynamicEffectEx(DWORD ModelID, float VecPos0, float VecPos1, float VecPos2, float WorldPos0, float WorldPos1, float WorldPos2, float Color0, float Color1, float Color2, int SubEffectID, float Scale, ObjectModel* lpModel);
	
	static void LoadModels();
	static void CreateItemEffect(int lpModel, int ItemID, vec3_t Light, float Alpha, int ItemLevel, int NewOption, int a10, int a11, int RenderType);
	static void DrawViewPortEffects(DWORD ObjectPointer, DWORD ObjectModel, DWORD a3);

	static void WingsSetInvisibleEffect();
	static void HieuUngBufferGlow() ;

public:
	MODEL_EFFECT_INFO m_ModelEffectData[MAX_MODEL_EFFECT];

	#if(ENABLE_LUA)
	MULua m_Lua;
	#endif
};

extern CRenderEffect g_RenderEffect;

#endif