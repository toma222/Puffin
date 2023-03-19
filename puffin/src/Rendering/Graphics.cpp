
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"

#include <math.h>

#include "Rendering/PRenderer.h"

#include "Core/Logging.h"
#include "Core/Application.h"
#include "Core/Core.h"

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

        m_renderSurface = std::make_shared<render::SDLSurface>("C:/Users/Aidan/Desktop/Puffin-newECS/ice/game/Assets/Images/TreeBuilding.bmp", 192, 108);
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
        SDL_FillRect(m_renderSurface->get(), NULL, 0x000000);
    }

    void Graphics::PlaceImage(render::SDLSurface *image, SDL_Rect *bounds)
    {
        SDL_BlitScaled(image->get(), NULL, m_renderSurface.get()->get(), bounds);
    }
} // namespace puffin
