
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
#include <string>

#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"

puffin::Application *CreateApplication()
{
    // PN_PROFILE_FUNCTION("Create Application", __FILE__);

    editor::EditorApplication *editorApp = new editor::EditorApplication();

    editorApp->SetEditorGUI();

    puffin::Application *app = editorApp; // new puffin::Application(); //
    app->GetLayerStack()->AddLayer<game::GameLayer>();

    return app;
}