#pragma once

#include <cassert>
#include <map>

#include "Core/Container.h"

#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"

namespace puffin
{
    /*
    class TransformBinding
    {
    private:
        double x;
        double y;
        double z;

    public:
        TransformBinding(double x, double y, double z) : x(x), y(y), z(z) {}

        void translate(double x, double y, double z)
        {
            this->x += x;
            this->y += y;
            this->z += z;
        }

        double get() const { return this->x; }
    };
    */

// TransformBinding identifier for the Lua metatable
#define LUA_TransformBinding "TransformBinding"

    // Create & return TransformBinding instance to Lua
    static int TransformBinding_new(lua_State *L)
    {
        double x = luaL_checknumber(L, 1);
        double y = luaL_checknumber(L, 2);
        double z = luaL_checknumber(L, 3);

        // Instead of calling the
        *reinterpret_cast<TransformBinding **>(lua_newuserdata(L, sizeof(TransformBinding *))) = new TransformBinding(x, y, z);
        luaL_setmetatable(L, LUA_TransformBinding);
        return 1;
    }

    // Free TransformBinding instance by Lua garbage collection
    static int TransformBinding_delete(lua_State *L)
    {
        delete *reinterpret_cast<TransformBinding **>(lua_touserdata(L, 1));
        return 0;
    }

    // TransformBinding member functions in Lua
    static int TransformBinding_translate(lua_State *L)
    {
        (*reinterpret_cast<TransformBinding **>(luaL_checkudata(L, 1, LUA_TransformBinding)))->translate(luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4));
        return 0;
    }
    static int TransformBinding_get(lua_State *L)
    {
        lua_pushnumber(L, (*reinterpret_cast<TransformBinding **>(luaL_checkudata(L, 1, LUA_TransformBinding)))->get());
        return 1;
    }

    // Register TransformBinding to Lua
    static void register_TransformBinding(lua_State *L)
    {
        lua_register(L, LUA_TransformBinding, TransformBinding_new);
        luaL_newmetatable(L, LUA_TransformBinding);
        lua_pushcfunction(L, TransformBinding_delete);
        lua_setfield(L, -2, "__gc");
        lua_pushvalue(L, -1);
        lua_setfield(L, -2, "__index");

        lua_pushcfunction(L, TransformBinding_translate);
        lua_setfield(L, -2, "translate");

        lua_pushcfunction(L, TransformBinding_get);
        lua_setfield(L, -2, "get");
        lua_pop(L, 1);
    }

    static void RegisterFunctions(lua_State *L)
    {
        register_TransformBinding(L);
    }
}
