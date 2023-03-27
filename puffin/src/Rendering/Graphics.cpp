
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"

#include <math.h>

#include "Rendering/PRenderer.h"

#include "Core/Logging.h"
#include "Core/Application.h"
#include "Core/Core.h"
#include "Math/PNVector.h"
#include "Light.h"

#include "Graphics.h"

#include <SDL2/SDL.h>

#include <memory>

namespace puffin
{
    Graphics *Graphics::s_graphics = nullptr;

    Graphics::Graphics()
    {
        PN_CORE_TRACE("Graphics instance created");
        SDL_Init(SDL_INIT_EVERYTHING);
    }

    void Graphics::InitRenderer(render::SDLWindow *window)
    {
        PN_CORE_TRACE("Creating Graphics Renderer");

        m_renderer = CreateRef<render::SDLRenderer>(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
        m_renderTexture = std::make_shared<render::SDLTexture>(m_renderer.get(), 192, 108);

        if (m_renderer == NULL)
            printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());

        int w, h;
        SDL_GetRendererOutputSize(m_renderer->get(), &w, &h);
        SDL_SetRenderTarget(m_renderer->get(), m_renderTexture->get());

        // ! this needs to be changed to work on the computer because it will give null if the image path does not work
        m_renderSurface = std::make_shared<render::SDLSurface>("C:/Users/Aidan/Documents/OtherUsslessProjects'/Puffin/ice/game/Assets/Images/BuildingWall.bmp", 192, 108);
    }

    Graphics::~Graphics()
    {
    }

    void Graphics::StartRenderCycle()
    {
        Flush();
    }

    void Graphics::PresentAndEndRenderCycle()
    {
        SDL_SetRenderTarget(m_renderer->get(), m_renderTexture->get());
        m_renderer->Clear();

        // Render the pixels and things
        // TODO put this in a more elegant fashion and have maybe custom render shaders
        // * multi threading would also be really cool (and fast)
        for (int x = 0; x < 192; x++)
        {
            for (int y = 0; y < 108; y++)
            {
                Uint8 *const albedoColor = (Uint8 *)m_renderSurface->get()->pixels + y * m_renderSurface->get()->pitch + x * m_renderSurface->get()->format->BytesPerPixel;

                Uint8 SplitR = albedoColor[2];
                Uint8 SplitG = albedoColor[1];
                Uint8 SplitB = albedoColor[0];

                Uint8 R = SplitR;
                Uint8 G = SplitG;
                Uint8 B = SplitB;

                for (auto light : m_lightBuffer)
                {
                    PNColor lightColor = light.m_lightType->GetPixelColor(x, y, light.m_x, light.m_y);

                    R *= lightColor.m_color[0];
                    G *= lightColor.m_color[1];
                    B *= lightColor.m_color[2];
                }

                puffin::PNColor shaded = m_pixelShader(x, y, puffin::PNColor(R, G, B));

                m_renderSurface->PutPixel(x, y, shaded.m_color[0], shaded.m_color[1], shaded.m_color[2]);
            }
        }

        SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer.get()->get(), m_renderSurface.get()->get());
        SDL_RenderCopy(m_renderer.get()->get(), texture, NULL, NULL);
        SDL_DestroyTexture(texture);

        SDL_SetRenderTarget(m_renderer->get(), NULL);
        m_renderer->CopyFull(m_renderTexture.get());

        Application::Get().GetLayerStack()->ImGuiUpdate();

        m_renderer->Present();
        // Flush();
    }

    void Graphics::Flush()
    {
        m_renderer->Clear();
        m_lightBuffer.clear();
        SDL_FillRect(m_renderSurface->get(), NULL, 0x000000);
    }

    void Graphics::PlaceImage(render::SDLSurface *image, SDL_Rect *bounds)
    {
        SDL_BlitScaled(image->get(), NULL, m_renderSurface.get()->get(), bounds);
    }

    void Graphics::PlaceLight(LightType *light, int x, int y)
    {
        PlaceLightFromProfile(LightProfile(light, x, y));
    }

    void Graphics::PlaceLightFromProfile(LightProfile profile)
    {
        m_lightBuffer.push_back(profile);
    }

    void Graphics::PlacePixelShader(PNColor (*func)(int, int, PNColor))
    {
        m_pixelShader = func;
    }
} // namespace puffin
