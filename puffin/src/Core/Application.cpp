
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"

#include "Rendering/Graphics.h"

#include "Window.h"
#include "Logging.h"
#include "Gui.h"

#include "Rendering/Light.h"
#include "Rendering/Graphics.h"

#include "Application.h"

namespace puffin
{
    Application *Application::s_Instance = nullptr;

    Application::Application()
    {
        s_Instance = this;

        Graphics::Get(); // Wakes up SDL

        m_window = std::make_shared<Window>();
        m_layerStack = std::make_shared<LayerStack>();

        Graphics::Get().InitRenderer(m_window->GetWindow());
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
            SDL_Event e;
            while (SDL_PollEvent(&e) > 0)
            {
                ImGui_ImplSDL2_ProcessEvent(&e);

                switch (e.type)
                {
                case SDL_QUIT:
                    open = false;
                    break;
                }
            }

            puffin::Graphics::Get().StartRenderCycle();

            m_layerStack->UpdateLayers();

            puffin::Graphics::Get().PlaceLight(puffin::PointLight(0, 0), 0, 0);

            puffin::Graphics::Get().PresentAndEndRenderCycle();
            m_window->UpdateWindow();
        }

        m_layerStack->DetachLayers();
    }
} // namespace puffin
