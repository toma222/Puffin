
#include <puffin.h>

#include <cstdio>

#include "GameLayer.h"

// This function is called as an extern to the engine
// Called in file puffin\src\puffin\EntryPoint.h
// Creates the CONTEXT, WINDOW, and the APPLICATION
Puffin::Application *CreateApplication()
{
    GM_CORE_INFO("Making application");
    Puffin::Application *app = new Puffin::Application;

    GM_CORE_INFO("Making GLFW window");
    app->SetWindow<Puffin::GLFWWindow>();

    app->m_layers.AddLayer<GameLayer>(app);

    app->InitExternal();

    return app;
}
