

#pragma once

#include "Core/Core.h"
#include <array>

#include "Rendering/PRenderer.h"
#include "Rendering/PWindow.h"

#include <vector>

namespace puffin
{
    class RenderPallet
    {
        public:
            std::vector<int> colors;
            int length;

            RenderPallet(int numberOfColors)
            {
                length = numberOfColors;
            };

            void SetPallet(std::vector<int> array)
            {
                colors = array;
                return;
            }
    };

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

        struct RenderItem
        {
            int layer; // z cordnate
            Ref<render::SDLSurface> surface;
        };

        typedef struct
        {
            double power;
            double distance;

            int x;
            int y;
        } Light;

        struct GraphicsProperties *m_graphicsProps;

        Ref<render::SDLRenderer> m_renderer;
        Ref<render::SDLTexture> m_renderTexture;
        Ref<render::SDLSurface> m_renderSurface;

        std::vector<std::shared_ptr<render::SDLSurface>> m_renderQue;
        std::vector<Light> m_lights;

        RenderPallet *m_pallet;

        // std::array<int, 40> m_pallet;

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

        void AddTextureToQue(std::shared_ptr<render::SDLSurface> item);
        void ClearTextureRenderQue();

        Ref<render::SDLRenderer> GetRenderer() { return m_renderer; };
        Ref<render::SDLTexture> GetRenderTexture() { return m_renderTexture; };
    };
} // namespace puffin
