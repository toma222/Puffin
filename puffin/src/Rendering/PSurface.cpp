
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "PSurface.h"

#include "Core/Core.h"
#include "Core/Logging.h"
#include "Math/PNVector.h"

#include <string>
#include <iostream>
#include <memory>

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

namespace puffin
{
    namespace render
    {
        SDLSurface::SDLSurface(int width, int height)
        {
            // m_surface = new SDL_Surface; // CreateRef<SDL_Surface>();

            m_surface = SDL_CreateRGBSurface(
                SDL_SWSURFACE,
                width, height, // Sizes
                16,            // BPP
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
                0x000000FF,
                0x0000FF00,
                0x00FF0000,
                0xFF000000);
#else
                0xFF000000,
                0x00FF0000,
                0x0000FF00,
                0x000000FF);
#endif
            //;
        }

        SDLSurface::SDLSurface(std::string path, int width, int height)
        {
            char buff[FILENAME_MAX]; // create string buffer to hold path
            GetCurrentDir(buff, FILENAME_MAX);
            std::string current_working_dir(buff);
            m_surface = IMG_Load(current_working_dir.append(path.c_str()).c_str());

            if (m_surface == NULL)
                std::cout << "could not load image, please check your file path\n";

            printf("%s\n", current_working_dir.append(path.c_str()).c_str());

            m_surfaceRect = new SDL_Rect;

            m_surfaceRect->h = height;
            m_surfaceRect->w = width;
            m_surfaceRect->x = 0;
            m_surfaceRect->y = 0;
        }

        SDLSurface::~SDLSurface()
        {
            PN_CORE_CLEAN("SDLSurface destructor has been called");

            // free(m_surface);
            // free(m_surfaceRect);
            // delete m_surface;

            SDL_FreeSurface(m_surface);
        }

        void SDLSurface::PutPixel(int x, int y, int r, int g, int b)
        {
            // m_surface->get()->clip_rect
            Uint32 color = SDL_MapRGB(m_surface->format, r, g, b);
            Uint32 *const target_pixel = (Uint32 *)((Uint8 *)m_surface->pixels + y * m_surface->pitch + x * m_surface->format->BytesPerPixel);
            *target_pixel = color;
        }

        void SDLSurface::PutPixel(int x, int y, Uint32 color)
        {
            Uint32 *const target_pixel = (Uint32 *)((Uint8 *)m_surface->pixels + y * m_surface->pitch + x * m_surface->format->BytesPerPixel);
            *target_pixel = color;
        }

        void SDLSurface::BlitSurface(SDLSurface *from)
        {
            SDL_BlitScaled(from->get(), NULL, m_surface, from->GetDimensions());
        }

        void SDLSurface::ConvertSurface(SDLSurface *windowSurface)
        {
            m_surface = SDL_ConvertSurface(m_surface, windowSurface->get()->format, 0);
        }

        PNColor SDLSurface::GetPixel(int x, int y)
        {
            Uint8 *const target_pixel = ((Uint8 *)m_surface->pixels + y * m_surface->pitch + x * m_surface->format->BytesPerPixel);

            return PNColor(target_pixel[2], target_pixel[1], target_pixel[0]);
        }
    } // namespace render
} // namespace pn
