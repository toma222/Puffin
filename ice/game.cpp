
#include <chrono>
#include <iostream>

#include <SDL2/SDL.h>

#include <Core/EntryPoint.h>
#include <puffin.h>

#include "editor/EditorLayer.h"
#include "game/Layer/GameLayer.h"

puffin::Application *CreateApplication()
{
    // editor::EditorApplication *editorApp = new editor::EditorApplication();

    // editorApp->SetEditorGUI();
    puffin::Vector2 a = puffin::Vector2(0, 1);
    puffin::Vector2 b = puffin::Vector2(1, 0);

    printf("%f\n", a.AngleBetweenVectors(b));

    puffin::Application *app = new puffin::Application();
    app->GetLayerStack()->AddLayer<GameLayer>();
    app->GetLayerStack()->AddLayer<game::GameLayer>();

    return app;
}