#pragma once

#include "Application.h"
#include "Logging.h"

extern Puffin::Application *CreateApplication();

int main()
{
    // Ask for application
    Puffin::Application *app = CreateApplication();

    /*
    Tell the context to make GLFW things
    PN_CORE_TRACE("Calling app->m_graphics->m_renderContext->InitGraphics to initlize open GLFW");
    app->m_graphics->m_renderContext->InitGraphics();

    Tell the window to make itself
    PN_CORE_TRACE("app->m_window->InitWindow to make the window");
    app->m_window->InitWindow("Game");
    */

    // Get this show on the road
    app->StartApplication();

    // Delete this show :(
    delete app;
}
