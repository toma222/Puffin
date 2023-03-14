
#include "Rendering/PRenderer.h"

#include "Logging.h"
#include "Debug/Instrumentor.h"
#include "Core/Core.h"

#include "Graphics.h"

#include <SDL2/SDL.h>

namespace puffin
{

    Graphics::Graphics(Uint32 SDLFlags)
    {
        PN_PROFILE_FUNCTION("Graphics");
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

        m_textureQue.clear();

        m_renderTexture->ClearTexture(m_renderer.get(), 192, 108);

        RenderTextures();
    }

    void Graphics::AddTextureToQue(std::shared_ptr<render::SDLTexture> texture, int layer)
    {
        m_textureQue.push_back(texture);
    };

    void Graphics::RenderTextures()
    {
        SDL_SetRenderTarget(m_renderer->get(), m_renderTexture->get());
        m_renderer->Clear();

        for (auto &&text : m_textureQue)
        {
            if (text != nullptr)
            {
                m_renderer->Copy(text.get());
            }
        }

        Uint32 *pixels;
        int pitch;

        SDL_Rect *rect = new SDL_Rect;
        rect->h = 192;
        rect->w = 108;

        SDL_RenderReadPixels(m_renderer->get(), rect, 0, pixels, pitch);

        delete rect;

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
        PN_PROFILE_FUNCTION("CreateRenderer");

        m_renderer = CreateRef<render::SDLRenderer>(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        m_renderTexture = std::make_shared<render::SDLTexture>(m_renderer.get(), 192, 108);

        if (m_renderer == NULL)
            printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());

        int w, h;
        SDL_GetRendererOutputSize(m_renderer->get(), &w, &h);
        SDL_SetRenderTarget(m_renderer->get(), m_renderTexture->get());
    }
} // namespace puffin
