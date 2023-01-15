
// #include "PSurface.h"

#include "SDL2/SDL.h"
#include "Core/Logging.h"
#include "PWindow.h"
#include "PSurface.h"

namespace puffin
{
    namespace render
    {
        SDLWindow::SDLWindow(std::string title, int x, int y, int width, int height, Uint32 flags)
        {
            m_window = SDL_CreateWindow(title.c_str(), x, y, width, height, flags);
            // m_windowSurface = new SDLSurface(SDL_GetWindowSurface(m_window));
            m_RendererCreated = false;
        }

        // Sets the window's name to puffin engine
        SDLWindow::SDLWindow(int x, int y, int width, int height)
        {
            m_window = SDL_CreateWindow("puffin engine", x, y, width, height, 0);
            // m_windowSurface = new SDLSurface(SDL_GetWindowSurface(m_window));
            m_RendererCreated = false;
        }

        SDLWindow::~SDLWindow()
        {
            PN_CORE_CLEAN("SDLWindow destructor called");
            SDL_DestroyWindow(m_window);
            // delete m_windowSurface;
        }

        void SDLWindow::UpdateSurface()
        {
            SDL_UpdateWindowSurface(this->m_window);
        }

        SDLSurface *SDLWindow::SetWindowSurface()
        {
            // m_windowSurface = new Ref<SDLSurface>(SDL_GetWindowSurface(m_window));

            return NULL; // m_windowSurface->get();
        }
    }
} // namespace puffin
