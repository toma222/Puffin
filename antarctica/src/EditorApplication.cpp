

#include <SDL2/SDL.h>

#include <Core/EntryPoint.h>
#include <puffin.h>

#include "EditorLayer.h"

puffin::Application *CreateApplication()
{
    puffin::Application *app = new puffin::Application();
    app->GetLayerStack()->AddLayer<puffin::EditorLayer>();

    return app;
}