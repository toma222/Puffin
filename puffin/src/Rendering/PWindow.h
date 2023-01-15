
#pragma once

#include "PSurface.h"

#include "Core/Core.h"

#include "SDL2/SDL.h"

#include <string>

namespace puffin
{
    namespace render
    {
        class SDLWindow
        {
        private:
            SDL_Window *m_window;
            // SDLSurface *m_windowSurface;
            // Ref<SDLSurface> *m_windowSurface;

            bool m_RendererCreated;

        public:
            // Stack overflow said to apply inline and it made the linker error go away. that's all I want.
            SDLWindow(std::string title, int x, int y, int width, int height, Uint32 flags);
            SDLWindow(int x, int y, int width, int height);
            ~SDLWindow();

            void UpdateSurface();

            SDL_Window *get() { return m_window; };
            SDL_Surface *GetWindowSurface() { return SDL_GetWindowSurface(m_window); };
            SDLSurface *SetWindowSurface();
        };
    }
} // namespace puffin
