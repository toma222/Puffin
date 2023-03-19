

#pragma once

#include "Core/Core.h"

#include "Rendering/PRenderer.h"
#include "Rendering/PWindow.h"

#include <vector>
#include <array>
#include <memory>
#include <SDL2/SDL.h>

namespace puffin
{
    class Graphics
    {
    private:
        const SDL_Rect *c_fullSpriteMap = new SDL_Rect({0, 0, 0, 0});

        // Simple properties of the renderer
        struct GraphicsProperties
        {
            int index;
            Uint32 flags;
        };

        struct RenderItem
        {
            int layer; // z cordnate
            Ref<render::SDLSurface> surface;
        };

        struct GraphicsProperties *m_graphicsProps;

        Ref<render::SDLRenderer> m_renderer;
        Ref<render::SDLTexture> m_renderTexture;
        Ref<render::SDLSurface> m_renderSurface;

        Graphics();

    public:
        Graphics(const Graphics &graphics) = delete;
        ~Graphics();

        void ClearRenderer();
        void InitRenderer(render::SDLWindow *window);

        void StartRenderCycle();
        void PresentAndEndRenderCycle();
        void Flush();

        void PlaceImage(render::SDLSurface *image, SDL_Rect *bounds);

        Ref<render::SDLRenderer> GetRenderer() { return m_renderer; };
        Ref<render::SDLTexture> GetRenderTexture() { return m_renderTexture; };

        static Graphics &Get()
        {
            if (s_graphics == nullptr)
                s_graphics = new Graphics();

            return *s_graphics;
        }

        struct Statistics
        {
            int m_drawCalls;
        };

        Statistics m_stats;

    private:
        static Graphics *s_graphics;
        bool m_rendering = false;
    };
} // namespace puffin
