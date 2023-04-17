
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"

#include <math.h>

#include "Rendering/PRenderer.h"
#include "Core/Assert.h"
#include "Core/Logging.h"
#include "Core/Application.h"
#include "Core/Core.h"
#include "Math/PNVector.h"

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
        {
            printf("%s\n", SDL_GetError());
            PN_CORE_ASSERT(false, "SDL Could not create renderer, error above");
        }

        int w, h;
        SDL_GetRendererOutputSize(m_renderer->get(), &w, &h);
        SDL_SetRenderTarget(m_renderer->get(), m_renderTexture->get());

        // ! this needs to be changed to work on the computer because it will give null if the image path does not work
        // ! we need a texture that us used just by the engine
        m_renderSurface = std::make_shared<render::SDLSurface>("/ice/assets/Images/BuildingWall.bmp", 192, 108);
    }

    Graphics::~Graphics()
    {
        PN_CORE_CLEAN("Graphics deconstructor called");
    }

    void Graphics::StartRenderCycle()
    {
        m_stats.m_openCloseGraphicsTime.start();
        Flush();
    }

    void Graphics::PresentAndEndRenderCycle()
    {
        m_stats.m_postTime.start();

        SDL_SetRenderTarget(m_renderer->get(), m_renderTexture->get());
        m_renderer->Clear();

        // Render the pixels and things
        // TODO put this in a more elegant fashion and have maybe custom render shaders
        // * multi threading would also be really cool (and fast)

        m_stats.m_postTime.stop();
        m_stats.m_openCloseGraphicsTime.stop();

        SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer.get()->get(), m_renderSurface.get()->get());
        SDL_RenderCopy(m_renderer.get()->get(), texture, NULL, NULL);
        SDL_DestroyTexture(texture);

        Application::Get().GetLayerStack()->GizmosUpdate();

        SDL_SetRenderTarget(m_renderer->get(), NULL);
        m_renderer->CopyFull(m_renderTexture.get());

        // ! make this called from the application.cpp class and not from here for readability
        Application::Get().GetLayerStack()->ImGuiUpdate();

        m_renderer->Present();
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
