

#include "PRenderer.h"
#include "PWindow.h"
#include "PTexture.h"

#include "Core/Logging.h"

#include "SDL2/SDL.h"

namespace puffin
{
    namespace render
    {
        SDLRenderer::SDLRenderer(SDLWindow *window, int index, Uint32 flags)
        {
            m_render = SDL_CreateRenderer(window->GetWindow(), index, flags);
        }

        SDLRenderer::~SDLRenderer()
        {
            PN_CORE_CLEAN("SDLRenderer destructor");
        }

        void SDLRenderer::Clear()
        {
            SDL_RenderClear(m_render);
        }

        void SDLRenderer::Copy(SDLTexture *texture)
        {
            SDL_RenderCopy(m_render, texture->get(), NULL, NULL);
        }

        void SDLRenderer::Present()
        {
            SDL_RenderPresent(m_render);
        }
    } // namespace render

} // namespace pn
