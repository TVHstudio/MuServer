#pragma once

#include "LargeRand.h"
#include "Import.h"
#include "Defines.h"
#include "RenderEffect.h"
#include "Console.h"
#include "TMemory.h"
#include "Interface.h"
#include "ZtUtils.h"

#if(ENABLE_LUA)

class LuaZtport
{
public:
	LuaZtport();
	virtual ~LuaZtport();

	void AddTable(lua_State * Lua);
	void AddGlobal(lua_State * Lua);

	static BOOL	LuaMessageBox(lua_State * Lua)
	{
		MessageBox(pGameWindow, "LuaMessageBoName", "Lua Loading", 0);
		return true;
	};

	static BOOL	LuaCreateItemEffect(lua_State * Lua)
	{
		int lpModel = lua_tointeger(Lua, 1);

		int ItemID = lua_tointeger(Lua, 2);

		LPVOID Model = pGetModel(pModelThis(), ItemID);

		vec3_t p;
		vec3_t Bone;
		vec3_t Color;
		vec3_t WorldPos;

		Vector(0.0f, 0.0f, 0.0f, p);
		Vector(WorldPos[0], WorldPos[1], WorldPos[2], WorldPos);

		switch (ItemID)
		{
			case ITEM2(0, 44): //Blessed Sword
			{
				float v234 = g_RenderEffect.GetRender(-4.0, 0.0);
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
					pQuickPlayStaticEffect(Model, 32229, i44, 0.30000001, Color, lpModel);
				}
				pQuickPlayStaticEffect(Model, 32229, 47, 0.30000001, Color, lpModel);
				pQuickPlayStaticEffect(Model, 32229, 23, 0.30000001, Color, lpModel);
				Vector(v1875 * 0.8500000238418579, v1875 * 0.1000000014901161, v1875 * 0.8999999761581421, Color);
				pQuickPlayStaticEffect(Model, 32229, 45, 0.80000001, Color, lpModel);
				pQuickPlayStaticEffect(Model, 32229, 46, 0.80000001, Color, lpModel);
				pQuickPlayStaticEffect(Model, 32229, 28, 0.80000001, Color, lpModel);
				pQuickPlayStaticEffect(Model, 32229, 30, 0.80000001, Color, lpModel);
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
				if(g_RenderEffect.GetRender(-4.0, 0.0) + 0.5 <= 1.0)
				  float v1163 = 1.0;
				else
				  float v1163 = g_RenderEffect.GetRender(-4.0, 0.0) + 0.5;
				Vector(v1875 * 0.2000000029802322, v1875 * 0.300000011920929, v1875 * 1.0, Color);
				pQuickPlayStaticEffect(Model, 32114, 1, 1.4, Color, lpModel);
		
				if (*(BYTE*)(oUserPreviewStruct+14) == 0 && pPlayerState == 5 )
				{
					float ColorR[3] = { (int)timeGetTime() % 11 * 0.1000000014901161 * v1875 + 0.699999988079071,
										(int)timeGetTime() % 11 * 0.1000000014901161 * v1875 + 0.699999988079071, 
										(int)timeGetTime() % 11 * 0.1000000014901161 * v1875 + 0.699999988079071 };
					ColorR[GetLargeRand() % 3] = 0.69999999f;
					ColorR[GetLargeRand() % 3] = 1.0f;

					pAllowPlayEffect(Model, Bone, lpModel, 27, 0);
					float v240 = ((int) timeGetTime() % 1441) * 0.25;
					pPlayStaticEffect(32805, (DWORD*)Bone, 1.0, Color, lpModel, v240, 0);
					pAllowPlayEffect(Model, Bone, lpModel, 32, (int)&p);
					float v241 = (double)(1440 - ((int) timeGetTime() % 1441) * 0.25);
					pPlayStaticEffect(32805, (DWORD*)Bone, 1.0, ColorR, lpModel, v241, 0);
					pAllowPlayEffect(Model, Bone, lpModel, 1, 0);
					WorldPos[0] = Bone[0] - WorldPos[0];
					WorldPos[1] = Bone[1] - WorldPos[1];
					WorldPos[2] = Bone[2] - WorldPos[2];
					g_RenderEffect.AddDynamicEffect(52379, Bone, WorldPos, ColorR, 6, 1.0f, &*(ObjectModel*)Model);
				}
			}
		}

		return true;
	}
	
	static BOOL	LuaGetModel(lua_State * Lua)
	{
		LPVOID Model = pGetModel(pModelThis(), (signed int)lua_tointeger(Lua, 1));
		lua_pushinteger(Lua, (int&)Model);
		return true;
	}

	static BOOL	LuaRender(lua_State * Lua)
	{
		float Result;

		Result = g_RenderEffect.GetRender((float)lua_tonumber(Lua, 1), (float)lua_tonumber(Lua, 2));

		lua_pushnumber(Lua, (float)Result);

		return true;
	}

	static BOOL	LuaQuickPlayStaticEffect(lua_State * Lua)
	{

		float Color[3] = { 0.0, 0.0, 0.0 };

		Color[0] = (float)lua_tonumber(Lua, 5);
		Color[1] = (float)lua_tonumber(Lua, 6);
		Color[2] = (float)lua_tonumber(Lua, 7);

		pQuickPlayStaticEffect((LPVOID)lua_tointeger(Lua, 1), 
								(int)lua_tointeger(Lua, 2), 
								(int)lua_tointeger(Lua, 3), 
								(float)lua_tonumber(Lua, 4), 								
								(vec3_t)Color,	
								(int)lua_tointeger(Lua, 8));

		return true;
	}

	static BOOL	LuaAllowPlayEffect(lua_State * Lua)
	{
		float Result[3] = { 0.0, 0.0, 0.0 };

		LPVOID Model = (LPVOID)lua_tointeger(Lua, 1);
		int lpModel = lua_tointeger(Lua, 2);
		signed int Joint = lua_tointeger(Lua, 3);

		pAllowPlayEffect(Model, Result, lpModel, Joint, 0);	//(int&)P

		
		lua_pushnumber(Lua, (float)Result[0]);
		lua_pushnumber(Lua, (float)Result[1]);
		lua_pushnumber(Lua, (float)Result[2]);
		

		return true;
	}

	static BOOL	LuaAllowPlayEffectTest(lua_State * Lua)
	{
		float Result[3] = { 0.0, 0.0, 0.0 };

		LPVOID Model = (LPVOID)lua_tointeger(Lua, 1);
		int lpModel = lua_tointeger(Lua, 2);
		signed int Joint = lua_tointeger(Lua, 3);

		pAllowPlayEffect(Model, Result, lpModel, Joint, 0);	//(int&)P

		lua_pushinteger(Lua, (int&)Result);
		
		return true;
	}

	static BOOL	LuaPlayStaticEffect(lua_State * Lua)
	{
		float Bone1[3] = { 0.0, 0.0, 0.0 };
		float Color1[3] = { 0.0, 0.0, 0.0 };

		Bone1[0] = (float)lua_tonumber(Lua, 2);
		Bone1[1] = (float)lua_tonumber(Lua, 3);
		Bone1[2] = (float)lua_tonumber(Lua, 4);
		
		Color1[0] = (float)lua_tonumber(Lua, 6);
		Color1[1] = (float)lua_tonumber(Lua, 7);
		Color1[2] = (float)lua_tonumber(Lua, 8);

		pPlayStaticEffectZt((int)lua_tointeger(Lua, 1), 
							(vec3_t)Bone1, 
							(float)lua_tonumber(Lua, 5), 
							(vec3_t)Color1, 								
							(int)lua_tointeger(Lua, 9),
							(float)lua_tonumber(Lua, 10), 
							(int)lua_tointeger(Lua, 11));

		return true;
	}

	static BOOL	LuaDynamicEffectEx(lua_State * Lua)
	{
		
		float Bone[3] = { 0.0, 0.0, 0.0 };
		float WorldPos[3] = { 0.0, 0.0, 0.0 };
		float ColorR[3] = { 0.0, 0.0, 0.0 };

		Bone[0] = lua_tonumber(Lua, 2);
		Bone[1] = lua_tonumber(Lua, 3);
		Bone[2] = lua_tonumber(Lua, 4);
		
		WorldPos[0] = (float)lua_tonumber(Lua, 5);
		WorldPos[1] = (float)lua_tonumber(Lua, 6);
		WorldPos[2] = (float)lua_tonumber(Lua, 7);
		
		ColorR[0] = (float)lua_tonumber(Lua, 8);
		ColorR[1] = (float)lua_tonumber(Lua, 9);
		ColorR[2] = (float)lua_tonumber(Lua, 10);
		/*
		WorldPos[0] = Bone[0] - WorldPos[0];
		WorldPos[1] = Bone[1] - WorldPos[1];
		WorldPos[2] = Bone[2] - WorldPos[2];
		*/
		g_RenderEffect.AddDynamicEffect(lua_tointeger(Lua, 1), 
										(vec3_t)Bone, 
										(vec3_t)WorldPos, 
										(vec3_t)ColorR,					
										(int)lua_tointeger(Lua, 11),
										(float)lua_tonumber(Lua, 12), 
										&*(ObjectModel*)lua_tointeger(Lua, 13));
										

		return true;
	}

	static BOOL	LuaGetRandomValue(lua_State * Lua)
	{
		int Div = lua_tointeger(Lua, 1);

		if (Div == 0)
		{
			//g_Log.AddC(TColor::Red, "[LUA] ERROR - LuaGetRandomValue Divider == 0");
			return false;
		}

		int Val = rand() % Div + 1;

		lua_pushinteger(Lua, Val);

		return true;
	}

	static BOOL	LuaGetLargeRandomValue(lua_State * Lua)
	{
		int Div = lua_tointeger(Lua, 1);

		if (Div == 0)
		{
			//g_Log.AddC(TColor::Red, "[LUA] ERROR - LuaGetLargeRandomValue Divider == 0");
			return false;
		}

		int Val = GetLargeRand() % Div + 1;

		lua_pushinteger(Lua, Val);

		return true;
	}

	static BOOL	LuaTimeGetTime(lua_State * Lua)
	{
		int Div = lua_tointeger(Lua, 1);

		int Val = timeGetTime() % Div;

		lua_pushinteger(Lua, Val);

		return true;
	}

	static BOOL LuaWindowTitle(lua_State * Lua)
	{
		MsgBox("TEXT FORMAT");

		return true;
	};
};

extern LuaZtport gLuaZtport;

#endif

