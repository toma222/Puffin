
#pragma once

#include <memory>
#include <string>

#include "PSurface.h"
#include "PRenderer.h"
// #include "Core/Application.h"

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
            std::shared_ptr<SDL_Rect> m_surfaceRect;
            SDL_Texture *m_texture;

        public:
            // Make texture from a surface
            SDLTexture(SDLRenderer *renderer, SDLSurface *surface);
            SDLTexture(SDLRenderer *render, std::string imagePath, int width, int height);
            SDLTexture(SDLRenderer *renderer, int width, int height);

            SDLTexture(std::shared_ptr<SDL_Rect> attachToRect, SDLRenderer *render, std::string imagePath, int width, int height);

            ~SDLTexture();

            SDL_Texture *get() { return m_texture; };
            std::shared_ptr<SDL_Rect> GetSDLRect() { return m_surfaceRect; };

            void DestroyTexture()
            {
                SDL_DestroyTexture(m_texture);
            };
            void ClearTexture(SDLRenderer *renderer, int sizeX, int sizeY);

            void LoadSurface(SDLSurface surface);

            void PutPixel()
            {
                /*
                // initialize SDL, window, renderer, texture
                int pitch, w, h;
                void *pixels;
                int *access;

                // SDL_SetTextureBlendMode(t, SDL_BLENDMODE_BLEND);

                SDL_QueryTexture(m_texture, NULL, access, &w, &h);
                SDL_LockTexture(m_texture, NULL, &pixels, &pitch);
                Uint32 *upixels = (Uint32 *)pixels;

                // you will need to know the color of the pixel even if it's transparent
                Uint32 transparent = SDL_MapRGBA(m_format, 0, 0, 0, 0x00);

                // replace the old pixels with the new ones
                // memcpy(pixels, upixels, (pitch / 4) * h);

                SDL_UnlockTexture(m_texture);
                */
            }
        };
    }
} // namespace pn
