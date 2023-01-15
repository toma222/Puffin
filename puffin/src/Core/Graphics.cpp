
#include "Rendering/PRenderer.h"

#include "Logging.h"
#include "Core/Core.h"

#include "Graphics.h"

#include <SDL2/SDL.h>

namespace puffin
{

    Graphics::Graphics(Uint32 SDLFlags)
    {
        PN_CORE_INFO("SDL INIT called with flag EVERYRTHING");
        SDL_Init(SDL_INIT_EVERYTHING);
        m_textureQue.resize(MAX_SPRITES_IN_SCENE);
        PN_CORE_TRACE("Graphics constructor called");
    }

    Graphics::~Graphics()
    {
    }

    void Graphics::ClearTextureRenderQue()
    {
        PN_CORE_INFO("Clearing Texture");
        m_textureQue.reserve(MAX_SPRITES_IN_SCENE);

        for (auto &&texture : m_textureQue)
        {
            if (texture != nullptr)
                delete texture;
        }

        int w, h;
        SDL_GetRendererOutputSize(m_renderer->get(), &w, &h);

        m_renderTexture->ClearTexture(m_renderer, w, h);

        RenderTextures();
    }

    void Graphics::AddTextureToQue(render::SDLTexture *texture, int layer)
    {
        m_textureQue.push_back(texture);
    };

    void Graphics::RenderTextures()
    {
        SDL_SetRenderTarget(m_renderer->get(), m_renderTexture->get());
        for (auto &&text : m_textureQue)
        {
            if (text != nullptr)
                m_renderer->Copy(text);
        }

        SDL_SetRenderTarget(m_renderer->get(), NULL);
        m_renderer->Copy(m_renderTexture);
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
        m_renderer = new render::SDLRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
        if (m_renderer == NULL)
            printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());

        int w, h;

        SDL_GetRendererOutputSize(m_renderer->get(), &w, &h);

        m_renderTexture = new render::SDLTexture(m_renderer, w, h);
        SDL_SetRenderTarget(m_renderer->get(), m_renderTexture->get());
    }
} // namespace puffin
