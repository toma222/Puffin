
#include "Application.h"
#include "base.h"

#include <cstdio>
#include <string>

namespace PN
{
    Application::Application()
    {
        // Setting up the application
        m_Open = false;
        m_graphics = new graphics::GraphicsAPI;
    }

    Application::~Application(){
        PN_CORE_CLEAN("Cleaning Application");

        m_window->CleanWindow();
        delete m_window;
        delete m_graphics;
    }

    void Application::InitExternal(){
        PN_CORE_TRACE("Calling app->m_graphics->m_renderContext->InitGraphics to initlize open GLFW");
        m_graphics->m_renderContext->InitGraphics();

        // Tell the window to make itself 
        PN_CORE_TRACE("app->m_window->InitWindow to make the window");
        m_window->InitWindow("Game");
    }

    void Application::StartApplication()
    {
        PN_CORE_TRACE("Application loop started");

        while (m_Open == true)
        {
            // Open
        }
    }
} // namespace Puffin


