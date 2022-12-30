
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
        m_Open = true;
    }

    Application::~Application()
    {
        m_window->CleanWindow();
        delete m_window;
    }

    void Application::InitExternal()
    {
        PN_CORE_TRACE("Application initializing external things");
        m_window->InitWindow("Game");
    }

    void Application::StartApplication()
    {
        PN_CORE_TRACE("Attaching all layers to the application");
        m_layers.AttachLayers(this);

        while (m_Open == true)
        {
            // Clear the window and get ready for the next render
            m_window->ClearWindow();

            // Render our layers
            m_layers.RenderStack();

            // Render our things
            // m_graphics->RenderGraphics();

            // Update the window and draw whatever we put in the draw buffer or something
            m_window->UpdateWindow();

            // Ask the window if it should close
            m_Open = !m_window->ShouldClose();
        }
    }
} // namespace Puffin
