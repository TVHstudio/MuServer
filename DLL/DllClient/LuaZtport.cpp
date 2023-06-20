#include "stdafx.h"
#include "LuaZtport.h"

#if(ENABLE_LUA)

LuaZtport gLuaZtport;

LuaZtport::LuaZtport()
{
}

LuaZtport::~LuaZtport()
{
}

void LuaZtport::AddTable(lua_State * Lua)
{
	lua_register(Lua, "Lua_MessageBox", this->LuaMessageBox);
	lua_register(Lua, "Lua_CreateItemEffect", this->LuaCreateItemEffect);
	lua_register(Lua, "Lua_GetModel", this->LuaGetModel);
	lua_register(Lua, "Lua_Render", this->LuaRender);
	lua_register(Lua, "Lua_QuickPlayStaticEffect", this->LuaQuickPlayStaticEffect);
	lua_register(Lua, "Lua_AllowPlayEffect", this->LuaAllowPlayEffect);
	lua_register(Lua, "Lua_PlayStaticEffect", this->LuaPlayStaticEffect);
	lua_register(Lua, "Lua_DynamicEffectEx", this->LuaDynamicEffectEx);
	lua_register(Lua, "Lua_GetRandomValue", this->LuaGetRandomValue);
	lua_register(Lua, "Lua_GetLargeRandomValue", this->LuaGetLargeRandomValue);
	lua_register(Lua, "Lua_timeGetTime", this->LuaTimeGetTime);

	lua_register(Lua, "Lua_WindowTitle", this->LuaWindowTitle);

	lua_register(Lua, "Lua_AllowPlayEffectTest", this->LuaAllowPlayEffectTest);
	

	int arr[10] = { 10,20,30,40,50,60,70,80,90,100 };
	lua_newtable(Lua);
	lua_pushstring(Lua, "arr");

	for (int i = 0; i < 10; i++)
	{
		lua_pushinteger(Lua, arr[i]);
		lua_rawseti(Lua, -3, i + 1);
	}
	
}

void LuaZtport::AddGlobal(lua_State * Lua)
{
	lua_pushinteger(Lua, pPlayerState);
	lua_setglobal(Lua, "PlayerState");

	lua_pushinteger(Lua, *(BYTE*)(0x7BC4F04+14));
	lua_setglobal(Lua, "InSafeZone");
}

#endif
