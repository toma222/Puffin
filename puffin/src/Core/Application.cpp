
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"

#include "Graphics.h"
#include "Window.h"
#include "Logging.h"
#include "Gui.h"

#include "Application.h"

namespace puffin
{
    Application *Application::s_Instance = nullptr;

    Application::Application()
    {
        s_Instance = this;

        // Init the systems for the application
        m_graphics = new Graphics(0); // std::make_unique<Graphics>(0);

        m_window = std::make_unique<Window>();

        m_layerStack = new LayerStack();

        m_graphics->CreateRenderer(m_window->GetWindow());
        PN_CORE_TRACE("Created Application");
    }

    Application::~Application()
    {
        // Just want to check that we get NO memory links
        PN_CORE_CLEAN("Application deconstructor called");
        s_Instance = nullptr;
    }

    void Application::StartApplication()
    {
        bool open = true;

        m_layerStack->AttachLayers();

        while (open == true)
        {
            // poll for events
            m_graphics->ClearRenderer();
            m_graphics->RenderTextures();

            m_layerStack->UpdateLayers();

            SDL_Event e;
            while (SDL_PollEvent(&e) > 0)
            {
                switch (e.type)
                {
                case SDL_QUIT:
                    open = false;
                    break;
                }
            }

            m_graphics->RenderPresent();
            m_window->UpdateWindow();
        }

        m_layerStack->DetachLayers();
    }
} // namespace puffin
