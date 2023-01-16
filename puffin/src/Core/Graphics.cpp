
#include "Rendering/PRenderer.h"

#include "Logging.h"
#include "Core/Core.h"

#include "Graphics.h"

#include <SDL2/SDL.h>

namespace puffin
{

    Graphics::Graphics(Uint32 SDLFlags)
    {
        SDL_Init(SDL_INIT_EVERYTHING);

        m_textureQue.resize(MAX_SPRITES_IN_SCENE);
    }

    Graphics::~Graphics()
    {
        PN_CORE_CLEAN("Graphics deconstructor called");
    }

    // Assumes that the pointers are taken care of externally
    // THIS WILL GIVE MEMORY LEAKS IF YOU ARE STUPID
    void Graphics::ClearTextureRenderQue()
    {
        m_textureQue.reserve(MAX_SPRITES_IN_SCENE);

        // for (auto &&texture : m_textureQue)
        //{
        //     if (texture != nullptr)
        //         delete texture;
        // }

        m_textureQue.clear();

        int w, h;
        SDL_GetRendererOutputSize(m_renderer->get(), &w, &h);

        m_renderTexture->ClearTexture(m_renderer.get(), w, h);

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
        m_renderer->Copy(m_renderTexture.get());
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
        m_renderTexture = std::make_shared<render::SDLTexture>(m_renderer.get(), 100, 100);

        if (m_renderer == NULL)
            printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());

        int w, h;
        SDL_GetRendererOutputSize(m_renderer->get(), &w, &h);
        SDL_SetRenderTarget(m_renderer->get(), m_renderTexture->get());
    }
} // namespace puffin
