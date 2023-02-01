
#include <chrono>
#include <iostream>

#include <SDL2/SDL.h>

#include <puffin.h>
#include <Core/EntryPoint.h>

#include "editor/editorGUI.h"
#include "editor/EditorApplication.h"

#include "game/Layer/GameLayer.h"

#include <cassert>
#include <string>

puffin::Application *CreateApplication()
{

    // editor::EditorApplication *editorApp = new editor::EditorApplication();

    // editorApp->SetEditorGUI();

    puffin::Application *app = new puffin::Application(); // editorApp; //
    app->GetLayerStack()->AddLayer<game::GameLayer>();

    return app;
}