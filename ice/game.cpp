
#include <chrono>
#include <iostream>

#include <SDL2/SDL.h>

#include <Core/EntryPoint.h>
#include <puffin.h>

#include "editor/editorGUI.h"
#include "editor/EditorApplication.h"

#include "game/Layer/GameLayer.h"

puffin::Application *CreateApplication()
{
    editor::EditorApplication *editor = new editor::EditorApplication();

    editor->SetEditorGUI();

    puffin::Application *app = editor;
    app->GetLayerStack()->AddLayer<game::GameLayer>();

    return app;
}