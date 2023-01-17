
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
            m_surfaceRect = std::make_shared<SDL_Rect>();

            m_surfaceRect->h = 1920;
            m_surfaceRect->w = 1080;
            m_surfaceRect->x = 0;
            m_surfaceRect->y = 0;

            m_texture = SDL_CreateTexture(renderer->get(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
        }

        SDLTexture::SDLTexture(std::shared_ptr<SDL_Rect> attachToRect, SDLRenderer *renderer, std::string imagePath, int width, int height)
        {
            SDL_Surface *surface = IMG_Load(imagePath.c_str());

            if (surface == NULL)
            {
                PN_CORE_FATAL("Could not load image : PATH ->");
                std::cout << imagePath.c_str() << "\n";
            }

            m_texture = SDL_CreateTextureFromSurface(renderer->get(), surface);

            SDL_FreeSurface(surface);

            m_surfaceRect = attachToRect;
        }

        SDLTexture::SDLTexture(SDLRenderer *renderer, std::string imagePath, int width, int height)
        {
            SDL_Surface *surface = IMG_Load(imagePath.c_str());

            if (surface == NULL)
            {
                PN_CORE_FATAL("Could not load image : PATH ->");
                std::cout << imagePath.c_str() << "\n";
            }

            m_texture = SDL_CreateTextureFromSurface(renderer->get(), surface);

            SDL_FreeSurface(surface);

            m_surfaceRect = std::make_shared<SDL_Rect>();

            m_surfaceRect->h = width;
            m_surfaceRect->w = height;
            m_surfaceRect->x = 0;
            m_surfaceRect->y = 0;
        }

        SDLTexture::~SDLTexture()
        {
            PN_CORE_CLEAN("SDL Texture destructor called");

            SDL_DestroyTexture(m_texture);
            // free(m_surfaceRect);
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
