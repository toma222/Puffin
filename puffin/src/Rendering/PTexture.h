
#pragma once

#include <memory>
#include <string>

#include "PSurface.h"
#include "PRenderer.h"

#include "SDL2/SDL.h"

namespace puffin
{
    namespace render
    {
        // Sorry have to forward declare
        class SDLRenderer;

        class SDLTexture
        {
        private:
            SDL_Texture *m_texture;
            SDL_Rect *m_surfaceRect;

        public:
            // Make texture from a surface
            SDLTexture(SDLRenderer *renderer, SDLSurface *surface);
            SDLTexture(SDLRenderer *render, std::string imagePath, int width, int height);
            SDLTexture(SDLRenderer *renderer, int width, int height);

            ~SDLTexture();

            SDL_Texture *get() { return m_texture; };

            void DestroyTexture() { SDL_DestroyTexture(m_texture); };
            void ClearTexture(SDLRenderer *renderer, int sizeX, int sizeY);

            void LoadSurface(SDLSurface surface);
        };
    }
} // namespace pn
