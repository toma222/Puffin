
#pragma once

#include <functional>

#include "Math/PNVector.h"

#include "Rendering/PSurface.h"

namespace puffin
{
    class PixelShader
    {
    public:
        std::function<PNColor(int, int, PNColor)> m_FragReference;
    };

    class PostEffect
    {
    private:
        PostEffect *m_ref;
        bool m_active;

    public:
        PostEffect()
        {
            m_ref = nullptr;
            m_surfaceRef = nullptr;
            m_active = true;
        }

        // ! may cause memory leaks
        ~PostEffect() = default;

        virtual PNColor Frag(int x, int y, PNColor) { return PNColor(0, 0, 0); };
        virtual void ImGuiUpdate(){};

        void LoadSurface(render::SDLSurface *surfaceRef)
        {
            m_surfaceRef = surfaceRef;
        }

        render::SDLSurface *m_surfaceRef;

        bool GetActive() { return m_active; };
    };

    class PalletCurver : public PostEffect
    {
    private:
        std::vector<PNColor> m_pallet;

    public:
        PNColor Frag(int x, int y, PNColor color) override;
        void ImGuiUpdate() override;

        PalletCurver() = default;

    public:
        template <int size>
        void AppendPallet(int pallet[size])
        {
            for (size_t c = 0; c < size; c++)
            {
                m_pallet.push_back(puffin::PNColor(((double)((pallet[c] >> 16) & 0xFF)),
                                                   ((double)((pallet[c] >> 8) & 0xFF)),
                                                   ((double)((pallet[c]) & 0xFF))));
            }
        }
    };

    class CrossDithering : public PostEffect
    {
    private:
        float m_spread;

    public:
        CrossDithering(float spread) : m_spread(spread){};

        PNColor Frag(int x, int y, PNColor color) override;
        void ImGuiUpdate() override;
    };

    class KuwaharaFilter : public PostEffect
    {
    private:
        int m_boxSize;

    public:
        KuwaharaFilter(int boxSize) : m_boxSize(boxSize){};

        PNColor Frag(int x, int y, PNColor color) override;
        void ImGuiUpdate() override;
    };
} // namespace puffin
