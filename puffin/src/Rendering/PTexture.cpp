
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "PTexture.h"
#include "PRenderer.h"

#include "Core/Logging.h"

#include <iostream>

namespace puffin
{
    namespace render
    {

        SDLTexture::SDLTexture(SDLRenderer *renderer, int width, int height)
        {
            // SDL_CreateTextureFromSurface(surface.GetSDLSurface());
            m_texture = SDL_CreateTexture(renderer->get(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1024, 1024);
        }

        SDLTexture::SDLTexture(SDLRenderer *renderer, std::string imagePath, int width, int height)
        {
            SDL_Surface *surface = IMG_Load(imagePath.c_str());

            if (surface == NULL)
                std::cout << "could not load surface\n";

            m_texture = SDL_CreateTextureFromSurface(renderer->get(), surface);

            SDL_FreeSurface(surface);

            m_surfaceRect = new SDL_Rect;

            m_surfaceRect->h = height;
            m_surfaceRect->w = width;
            m_surfaceRect->x = 0;
            m_surfaceRect->y = 0;
        }

        SDLTexture::~SDLTexture()
        {
            PN_CORE_CLEAN("Cleaning the SDL texture");

            SDL_DestroyTexture(m_texture);
        }

        void SDLTexture::ClearTexture(SDLRenderer *renderer, int sizeX, int sizeY)
        {
            DestroyTexture();
            m_texture = SDL_CreateTexture(renderer->get(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, sizeX, sizeY);
        }

        // void SDLTextureLoadSurface(Surface surface)
        //{
        // }

    } // namespace render
} // namespace pn
