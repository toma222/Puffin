
#include <chrono>
#include <iostream>

#include <SDL2/SDL.h>

#include <Core/EntryPoint.h>
#include <puffin.h>

// #include "editor/EditorLayer.h"
#include "GameLayer.h"

puffin::Application *CreateApplication()
{
    puffin::Application *app = new puffin::Application();
    app->GetLayerStack()->AddLayer<GameLayer>();

    return app;
}