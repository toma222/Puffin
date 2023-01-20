
#include <chrono>
#include <iostream>

#include <SDL2/SDL.h>

#include <puffin.h>
#include <Core/EntryPoint.h>

#include "editor/editorGUI.h"
#include "editor/EditorApplication.h"

#include "game/Layer/GameLayer.h"

puffin::Application *CreateApplication()
{
    editor::EditorApplication *editorApp = new editor::EditorApplication();

    editorApp->SetEditorGUI();

    puffin::Application *app = editorApp; // new puffin::Application(); //
    app->GetLayerStack()->AddLayer<game::GameLayer>();

    return app;
}