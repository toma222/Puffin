#pragma once

#include <cassert>
#include <map>

#include "Core/Container.h"
#include "Components/Transform.h"

#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"

// Transform identifier for the Lua metatable
#define LUA_Transform "Transform"

namespace puffin
{
    // Create & return Transform instance to Lua
    static int Transform_new(lua_State *L)
    {
        double x = luaL_checknumber(L, 1);
        double y = luaL_checknumber(L, 2);
        double w = luaL_checknumber(L, 3);
        double h = luaL_checknumber(L, 4);

        // Instead of calling the
        *reinterpret_cast<components::Transform **>(lua_newuserdata(L, sizeof(components::Transform *))) = new components::Transform(nullptr, x, y, w, h);
        luaL_setmetatable(L, LUA_Transform);
        return 1;
    }

    // Free Transform instance by Lua garbage collection
    static int Transform_delete(lua_State *L)
    {
        delete *reinterpret_cast<components::Transform **>(lua_touserdata(L, 1));
        return 0;
    }

    // Transform member functions in Lua
    static int Transform_translate(lua_State *L)
    {
        (*reinterpret_cast<components::Transform **>(luaL_checkudata(L, 1, LUA_Transform)))->Translate(luaL_checknumber(L, 2), luaL_checknumber(L, 3));
        return 0;
    }

    /*
    class TransformBinding
    {
    public:
        Entity *attached;

        static int transform(lua_State *L)
        {
            double x = luaL_checknumber(L, 1);
            double y = luaL_checknumber(L, 2);
            double w = luaL_checknumber(L, 3);
            double h = luaL_checknumber(L, 4);

            *reinterpret_cast<components::Transform **>(lua_newuserdata(L, sizeof(components::Transform *))) = attached.GetComponent<components::Transform>();
            luaL_setmetatable(L, LUA_Transform);
            return 1;
        }
    };
    */

    // Register Transform to Lua
    static void register_Transform(lua_State *L)
    {
        lua_register(L, LUA_Transform, Transform_new);
        luaL_newmetatable(L, LUA_Transform);
        lua_pushcfunction(L, Transform_delete);
        lua_setfield(L, -2, "__gc");
        lua_pushvalue(L, -1);
        lua_setfield(L, -2, "__index");

        lua_pushcfunction(L, Transform_translate);
        lua_setfield(L, -2, "translate");

        lua_pop(L, 1);
    }

    static void RegisterFunctions(lua_State *L)
    {
        register_Transform(L);
    }
}
