
#pragma once

#include "SDL2/SDL.h"

#include "Core/Core.h"

#include <string>
#include <memory>

namespace puffin
{
    namespace render
    {

        class SDLSurface
        {
        private:
            // Ref<SDL_Surface> m_surface;
            SDL_Surface *m_surface;
            SDL_Rect *m_surfaceRect;

        public:
            // File path to the image to load as a Surface
            // Surface(std::string path);
            SDLSurface(int width, int height);
            SDLSurface(std::string path, int width, int height);
            SDLSurface(SDL_Surface *surface) { m_surface = surface; };

            ~SDLSurface();

            SDL_Surface *get() { return m_surface; };
            SDL_Rect *GetDimensions() { return m_surfaceRect; };

        public:
            void PutPixel(int x, int y, int r, int g, int b);
            void PutPixel(int x, int y, Uint32 color);

            // Does a scaled blit so that you can change the size and such
            void BlitSurface(SDLSurface *from);

            void ConvertSurface(SDLSurface *windowSurface);
        };
        // namespace graphics

    } // namespace render

} // namespace pn
