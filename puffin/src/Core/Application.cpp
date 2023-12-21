
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"

#include "Rendering/Graphics.h"

#include "Window.h"
#include "Logging.h"
#include "Gui.h"

#include "Rendering/Graphics.h"

#include "Application.h"

namespace puffin
{
    Application *Application::s_Instance = nullptr;

    Application::Application()
    {
        PN_CORE_INFO("Application Constructor Called");

        s_Instance = this;
        Graphics::Get();
        m_window = std::make_shared<Window>();
        m_layerStack = std::make_shared<LayerStack>();
        Graphics::Get().InitRenderer(m_window->GetWindow());
    }

    Application::~Application()
    {
        PN_CORE_CLEAN("Application Deconstructor called");
        s_Instance = nullptr;
    }

    void Application::Exit()
    {
        m_running = false;
    }

    void Application::StartApplication()
    {
        m_running = true;

        m_layerStack->AttachLayers();

        while (m_running == true)
        {
            SDL_Event e;
            while (SDL_PollEvent(&e) > 0)
            {
                ImGui_ImplSDL2_ProcessEvent(&e);

                switch (e.type)
                {
                case SDL_QUIT:
                    m_running = false;
                    break;
                }
            }

            puffin::Graphics::Get().StartRenderCycle();

            m_layerStack->UpdateLayers();

            puffin::Graphics::Get().PresentAndEndRenderCycle();
            m_window->UpdateWindow();
        }

        m_layerStack->DetachLayers();
    }
} // namespace puffin
