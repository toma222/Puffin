
#include <math.h>

#include "Rendering/PRenderer.h"

#include "Logging.h"
#include "Core/Core.h"

#include "Graphics.h"

#include <SDL2/SDL.h>

void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    Uint32 *const target_pixel = (Uint32 *)((Uint8 *)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel);
    *target_pixel = pixel;
}

namespace puffin
{
    Graphics::Graphics(Uint32 SDLFlags)
    {
        SDL_Init(SDL_INIT_EVERYTHING);

        m_renderQue.resize(MAX_SPRITES_IN_SCENE);
    }

    Graphics::~Graphics()
    {
        PN_CORE_CLEAN("Graphics deconstructor called");
    }

    // Assumes that the pointers are taken care of externally
    // THIS WILL GIVE MEMORY LEAKS IF YOU ARE STUPID
    void Graphics::ClearTextureRenderQue()
    {
        m_renderQue.reserve(MAX_SPRITES_IN_SCENE);

        // for (auto &&texture : m_renderQue)
        //{
        //     if (texture != nullptr)
        //         delete texture;
        // }

        m_renderQue.clear();

        int w, h;
        SDL_GetRendererOutputSize(m_renderer->get(), &w, &h);

        m_renderTexture->ClearTexture(m_renderer.get(), 192, 108);

        RenderTextures();
    }

    void Graphics::AddTextureToQue(std::shared_ptr<render::SDLSurface> item)
    {
        m_renderQue.push_back(item);
    };

    void Graphics::RenderTextures()
    {
        SDL_SetRenderTarget(m_renderer->get(), m_renderTexture->get());
        m_renderer->Clear();

        for (auto &&item : m_renderQue)
        {
            if (item != nullptr)
            {
                SDL_BlitScaled(item.get()->get(), NULL, m_renderSurface.get()->get(), item->GetDimensions());
            }
        }

        for (size_t x = 0; x < 192; x++)
        {
            for (size_t y = 0; y < 108; y++)
            {
                Uint8 *const target_pixel = ((Uint8 *)m_renderSurface->get()->pixels + y * m_renderSurface->get()->pitch + x * m_renderSurface->get()->format->BytesPerPixel);

                Uint8 r = target_pixel[2];
                Uint8 g = target_pixel[1];
                Uint8 b = target_pixel[0];

                double distnaces = 0.0;

                // Put a test light at 0,0
                for (auto light : m_lights)
                {
                    double distance = std::sqrt(((x - light.x) * (x - light.x)) + ((y - light.y) * (y - light.y)));

                    double calc = 1 - std::min(distance / light.distance, 1.2);

                    distnaces += calc;
                    distnaces += calc;
                    distnaces += calc;
                }

                r *= std::min(distnaces, 1.0);
                g *= std::min(distnaces, 1.0);
                b *= std::min(distnaces, 1.0);

                Uint8 finalColor[3] = {0, 0, 0};
                double closest = 300;

                for (auto hexValue : m_pallet->colors)
                {
                    Uint8 pr = ((hexValue >> 16) & 0xFF);
                    Uint8 pg = ((hexValue >> 8) & 0xFF);
                    Uint8 pb = ((hexValue)&0xFF);

                    double distance = std::sqrt(((pr - r) * (pr - r)) +
                                                ((pg - g) * (pg - g)) +
                                                ((pb - b) * (pb - b)));

                    if (distance < closest)
                    {
                        closest = distance;

                        finalColor[0] = pr;
                        finalColor[1] = pg;
                        finalColor[2] = pb;
                    }
                }

                m_renderSurface->PutPixel(x, y, SDL_MapRGB(m_renderSurface.get()->get()->format, finalColor[0], finalColor[1], finalColor[2]));
            }
        }

        SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer.get()->get(), m_renderSurface.get()->get());

        SDL_RenderCopy(m_renderer.get()->get(), texture, NULL, NULL);

        SDL_DestroyTexture(texture);

        SDL_SetRenderTarget(m_renderer->get(), NULL);
        m_renderer->CopyFull(m_renderTexture.get());
    }

    void Graphics::RenderPresent()
    {
        m_renderer->Present();
    }

    void Graphics::ClearRenderer()
    {
        m_renderer->Clear();
    }

    void Graphics::CreateRenderer(render::SDLWindow *window)
    {
        m_renderer = CreateRef<render::SDLRenderer>(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
        m_renderTexture = std::make_shared<render::SDLTexture>(m_renderer.get(), 192, 108);

        if (m_renderer == NULL)
            printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());

        int w, h;
        SDL_GetRendererOutputSize(m_renderer->get(), &w, &h);
        SDL_SetRenderTarget(m_renderer->get(), m_renderTexture->get());

        m_renderSurface = std::make_shared<render::SDLSurface>("C:/Users/Aidan/Desktop/Puffin-rendering/ice/game/Assets/Images/TreeBuilding.bmp", 192, 108);

        Light basicLight = {1, 80, 25, 33};
        m_lights.push_back(basicLight);
        m_lights.push_back({1, 74, 162, 32});

        m_lights.push_back({1, 30, 27, 107});
        m_lights.push_back({1, 30, 96, 107});
        m_lights.push_back({1, 30, 167, 107});

        m_pallet = new RenderPallet(40);

        m_pallet->SetPallet({0x7a2d30,
                             0x632b38,
                             0x4a2936,
                             0x362530,
                             0x292225,
                             0x8f422c,
                             0x995325,
                             0xab6c2c,
                             0xa67c23,
                             0x996d20,
                             0x805622,
                             0x5e431f,
                             0x403125,
                             0x8c7f0b,
                             0x686700,
                             0x4d5e21,
                             0x374529,
                             0x364f33,
                             0x81a867,
                             0x669170,
                             0x466b5d,
                             0x344a4d,
                             0x29323b,
                             0x304452,
                             0x375c69,
                             0x418791,
                             0x9c525a,
                             0x783e51,
                             0x5c3047,
                             0x442e4a,
                             0x63413f,
                             0x9e6a55,
                             0xbe9167,
                             0xccab78,
                             0x3e3c42,
                             0x5e5d5d,
                             0x78736d,
                             0x8f897b,
                             0xb3b09f,
                             0xdbdbd0});
    }
} // namespace puffin
