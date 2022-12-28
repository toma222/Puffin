
#include "Application.h"
#include "LayerStack.h"
#include "base.h"

#include "puffin/graphics/Vertices.h"

#include <cstdio>
#include <string>

#include <glm/glm.hpp>

namespace PN
{
    Application::Application()
    {
        // Setting up the application
        m_Open = true;
        m_graphics = new graphics::GraphicsAPI;
    }

    Application::~Application()
    {
        PN_CORE_CLEAN("Application::~Application Cleaning Application");

        m_window->CleanWindow();
        delete m_window;
        delete m_graphics;
    }

    void Application::InitExternal()
    {
        PN_CORE_TRACE("Calling the render context to configure the current graphics");
        m_graphics->m_renderContext->InitGraphics();

        // Tell the window to make itself
        PN_CORE_TRACE("InitWindow being called in m_window");
        m_window->InitWindow("Game");
    }

    void Application::StartApplication()
    {
        PN_CORE_TRACE("Application loop started");

        while (m_Open == true)
        {
            // Clear the window and get ready for the next render
            m_window->ClearWindow();

            // Render our layers
            m_layers.RenderStack();

            // Render our things
            m_graphics->RenderGraphics();

            // Update the window and draw whatever we put in the draw buffer or something
            m_window->UpdateWindow();

            // Ask the window if it should close
            m_Open = !m_window->ShouldClose();
        }
    }
} // namespace Puffin
