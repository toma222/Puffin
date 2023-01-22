
#include <chrono>
#include <iostream>

#include <SDL2/SDL.h>

#include <puffin.h>
#include <Core/EntryPoint.h>

#include "editor/editorGUI.h"
#include "editor/EditorApplication.h"

#include "game/Layer/GameLayer.h"

#include <sol/sol.hpp>
#include <cassert>

#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"

puffin::Application *CreateApplication()
{
    // sol::state lua;
    // lua.open_libraries(sol::lib::base);
    //  lua.script("");

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    luaL_dofile(L, "C:/Users/Aidan/Documents/OtherUsslessProjects'/Puffin/ice/script.lua");
    lua_setglobal(L, "script");
    lua_settop(L, 0);

    // Run the init() function.
    lua_getglobal(L, "script");
    lua_getfield(L, -1, "init"); // -1 means stack top.
    lua_call(L, 0, 0);           // 0, 0 = #args, #retvals

    editor::EditorApplication *editorApp = new editor::EditorApplication();

    editorApp->SetEditorGUI();

    puffin::Application *app = editorApp; // new puffin::Application(); //
    app->GetLayerStack()->AddLayer<game::GameLayer>();

    return app;
}