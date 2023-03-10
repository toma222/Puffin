
#pragma once

#include "PTexture.h"

#include "SDL2/SDL.h"

#include "PWindow.h"

namespace puffin
{
    namespace render
    {
        // Sorry, I have to forward declare :(
        class SDLTexture;

        class SDLRenderer
        {
        private:
            SDL_Renderer *m_render;

        public:
            SDLRenderer(SDLWindow *window, int index, Uint32 flags);
            ~SDLRenderer();

            SDL_Renderer *get() { return m_render; };

            void Clear();
            void Copy(SDLTexture *texture);
            void CopyFull(SDLTexture *texture);
            // void Copy(SDLTexture *texture, SDL_Rect *rect);
            void Present();
        };
    }
} // namespace pn
