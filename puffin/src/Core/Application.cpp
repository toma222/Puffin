
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
        m_graphics = std::make_shared<Graphics>(0);
        m_window = std::make_shared<Window>();
        m_layerStack = std::make_shared<LayerStack>();

        m_graphics->CreateRenderer(m_window->GetWindow());
    }

    Application::~Application()
    {
        s_Instance = nullptr;
    }

    void Application::StartApplication()
    {
        bool open = true;

        m_layerStack->AttachLayers();

        while (open == true)
        {
            // poll for events

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
            m_graphics->ClearRenderer();
            m_graphics->RenderTextures();
            m_layerStack->UpdateLayers();

            m_graphics->RenderPresent();
            m_window->UpdateWindow();
        }

        m_layerStack->DetachLayers();
    }
} // namespace puffin
