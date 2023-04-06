
#include <SDL2/SDL.h>

#include "Window.h"
#include "Rendering/PWindow.h"
#include "Logging.h"

#include <string>

namespace puffin
{
    Window::Window()
    {
        PN_CORE_INFO("Window Constructor called");
        SDL_DisplayMode dm;

        if (SDL_GetDesktopDisplayMode(0, &dm) != 0)
        {
            SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
        }

        int w, h;
        w = dm.w;
        h = dm.h;

        m_window = new render::SDLWindow("puffin engine", 0, 0, w, h, SDL_WINDOW_FULLSCREEN_DESKTOP);
        m_window->SetWindowSurface();

        m_props.m_height = h;
        m_props.m_width = w;
    }

    Window::~Window()
    {
        PN_CORE_CLEAN("Window Context destroyed");
        delete m_window;
    }

    void Window::UpdateWindow()
    {
        m_window->UpdateSurface();
    }

} // namespace puffin
