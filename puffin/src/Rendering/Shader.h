
#pragma once

#include <functional>

#include "Math/PNVector.h"

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

    public:
        PostEffect()
        {
            m_ref = nullptr;
        }

        // ! may cause memory leaks
        ~PostEffect() = default;

        virtual PNColor Frag(int x, int y, PNColor) { return PNColor(0, 0, 0); };
        virtual void ImGuiUpdate(){};
    };

    class PalletCurver : public PostEffect
    {
    private:
        std::vector<PNColor> m_pallet;

    public:
        PNColor Frag(int x, int y, PNColor) override;
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

        PNColor Frag(int x, int y, PNColor) override;
        void ImGuiUpdate() override;
    };
} // namespace puffin
