

#include <SDL2/SDL.h>

#include <Core/EntryPoint.h>
#include <puffin.h>

#include "EditorLayer.h"

puffin::Application *CreateApplication()
{
    puffin::Application *app = new puffin::Application();
    app->GetLayerStack()->AddLayer<puffin::EditorLayer>();

    puffin::LuaScript script("C:/Users/aidan/Desktop/github/Puffin/ice/assets/Scripts/Scroll.lua", "Scroll");

    script.RunFunction("Start");

    return app;
}