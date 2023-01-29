
#include <sol/sol.hpp>
#include <cassert>

#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"

#include "LuaGlue.h"
#include "LuaPuffinFunctions.h"

namespace puffin
{

    LuaContext::LuaContext(std::string scriptPath, Entity *attached)
    {
        m_lua = (lua_State *)malloc(1000);

        m_lua = luaL_newstate();
        luaL_openlibs(m_lua);
        luaL_dofile(m_lua, scriptPath.c_str());

        // Load all the fun puffin functions
        RegisterFunctions(m_lua);

        // Creates the global module for the lua script
        lua_setglobal(m_lua, "script");
        lua_settop(m_lua, 0);

        lua_getglobal(m_lua, "script");
        CallFunction("init");
    }

    void LuaContext::CallFunction(std::string function)
    {
        lua_getfield(m_lua, -1, function.c_str()); // -1 means stack top.
        lua_call(m_lua, 0, 0);                     // 0, 0 = #args, #retvals
    }

    LuaContext::~LuaContext()
    {
        lua_close(m_lua);
    }
} // namespace puffin
