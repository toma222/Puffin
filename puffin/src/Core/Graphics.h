

#pragma once

#include "Core/Core.h"

#include "Rendering/PRenderer.h"
#include "Rendering/PWindow.h"

#include <vector>

namespace puffin
{
    // Contains the renderer and is in charge of rendering images
    class Graphics
    {
    private:
        // Simple properties of the renderer
        struct GraphicsProperties
        {
            int index;
            Uint32 flags;
        };

        // typedef struct
        // {
        //     int layer;
        //     render::SDLTexture *texture;
        // } QueTextureItem;

        struct GraphicsProperties *m_graphicsProps;

        Ref<render::SDLRenderer> m_renderer;
        Ref<render::SDLTexture> m_renderTexture;

        std::vector<std::shared_ptr<render::SDLTexture>> m_textureQue;

        // All things rendered are stored in the render texture

    public:
        // Creates the SDL context
        Graphics(Uint32 SDLFlags);
        ~Graphics();

        void ClearRenderer();
        void CreateRenderer(render::SDLWindow *window);

        // Renders the textures in the que
        void RenderTextures();
        void RenderClear();

        // Presents the changes to the window
        void RenderPresent();

        void AddTextureToQue(std::shared_ptr<render::SDLTexture>, int layer);
        void ClearTextureRenderQue();

        Ref<render::SDLRenderer> GetRenderer() { return m_renderer; };
        Ref<render::SDLTexture> GetRenderTexture() { return m_renderTexture; };
    };
} // namespace puffin
