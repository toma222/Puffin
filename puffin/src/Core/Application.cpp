
#include <chrono>

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"

#include "Graphics.h"
#include "Window.h"
#include "Logging.h"
#include "Debug/Instrumentor.h"
#include "Gui.h"
#include "Input.h"

#include "Application.h"

namespace puffin
{
    Application *Application::s_Instance = nullptr;

    Application::Application()
    {
        s_Instance = this;

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
            auto start = std::chrono::high_resolution_clock::now();

            m_graphics->ClearRenderer();
            m_graphics->RenderTextures();

            SDL_Event e;
            while (SDL_PollEvent(&e) > 0)
            {
                switch (e.type)
                {
                case SDL_QUIT:
                    open = false;
                    break;
                case SDL_MOUSEBUTTONUP:
                    Input::m_mouseButton[0] = 0;
                }
            }

            m_layerStack->UpdateLayers();
            m_graphics->RenderPresent();

            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

            if (duration.count() < 16)
            {
                _sleep(16 - duration.count());
            }
        }

        m_layerStack->DetachLayers();
    }
} // namespace puffin
