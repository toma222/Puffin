
#pragma once

#include <memory>
#include <string>

#include <sol/sol.hpp>
#include <cassert>

#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"

#include "LuaPuffinFunctions.h"

namespace puffin
{
    // Creates a lua context for a script
    // Should load the script then keep it such that we can call it's functions
    class LuaContext
    {
    private:
        lua_State *m_lua;

    private:
        void LoadScript(std::string scriptPath);

    public:
        struct Glue
        {
            std::string m_accessModuleName;
        };

        Glue m_glue;

        LuaContext(std::string scriptPath);
        ~LuaContext();

        void CallFunction(std::string function);

        void AddGlobalNumber(std::string name, int num)
        {
            lua_pushnumber(m_lua, num);
            lua_setglobal(m_lua, name.c_str());
        }

        int GetGlobalNumber(std::string name)
        {
            lua_getglobal(m_lua, name.c_str());
            int ret = lua_tonumber(m_lua, -1);
            lua_pop(m_lua, 1);
            return ret;
        }

        void LoadModule();

        lua_State *GetLuaState() { return m_lua; };
    };
} // namespace puffin

/*

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    luaL_dofile(L, "C:/Users/Aidan/Documents/OtherUsslessProjects'/Puffin/ice/script.lua");
    lua_setglobal(L, "script");
    lua_settop(L, 0);

    // Run the init() function.
    lua_getglobal(L, "script");
    lua_getfield(L, -1, "init"); // -1 means stack top.
    lua_call(L, 0, 0);           // 0, 0 = #args, #retvals

*/