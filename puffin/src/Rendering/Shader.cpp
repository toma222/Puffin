
#include "Shader.h"
#include "Math/PNVector.h"

#include "imgui/imgui.h"

puffin::PNColor intToColor(Uint32 hexValue)
{
    return puffin::PNColor((double)((hexValue >> 16) & 0xFF),
                           (double)((hexValue >> 8) & 0xFF),
                           (double)((hexValue)&0xFF));
}


static Uint32 Pallet[40] = {
    0x7a2d30,
    0x632b38,
    0x4a2936,
    0x362530,
    0x292225,
    0x8f422c,
    0x995325,
    0xab6c2c,
    0xa67c23,
    0x996d20,
    0x805622,
    0x5e431f,
    0x403125,
    0x8c7f0b,
    0x686700,
    0x4d5e21,
    0x374529,
    0x364f33,
    0x81a867,
    0x669170,
    0x466b5d,
    0x344a4d,
    0x29323b,
    0x304452,
    0x375c69,
    0x418791,
    0x9c525a,
    0x783e51,
    0x5c3047,
    0x442e4a,
    0x63413f,
    0x9e6a55,
    0xbe9167,
    0xccab78,
    0x3e3c42,
    0x5e5d5d,
    0x78736d,
    0x8f897b,
    0xb3b09f,
    0xdbdbd0};


/*
static Uint32 Pallet[6] = {
    0xbdb5a8,
    0xa0938e,
    0x201d1f,
    0xfff2e6,
    0x5a5353,
    0x7d7071};
*/

int map[4][4] = {{0, 8, 2, 10}, {12, 4, 14, 6}, {3, 11, 1, 9}, {15, 7, 13, 5}};

namespace puffin
{
    PNColor PalletPixelShader(int x, int y, PNColor color)
    {

        // ANTI ALIASING
        int xm = x % 4;
        int ym = y % 4;

        float M = map[xm][ym];
        float p = M * (1 / 16) - 0.5f;
        float spread = .8f;

        color.m_color[0] += (spread * M);
        color.m_color[1] += (spread * M);
        color.m_color[2] += (spread * M);

        float maxDistance = 260;
        PNColor picked = intToColor(Pallet[0]);

        for (int i = 0; i < 40; i++)
        {
            PNColor iter = intToColor(Pallet[i]);

            float distance = std::sqrt(((color.m_color[0] - iter.m_color[0]) * (color.m_color[0] - iter.m_color[0])) +
                                       ((color.m_color[1] - iter.m_color[1]) * (color.m_color[1] - iter.m_color[1])) +
                                       ((color.m_color[2] - iter.m_color[2]) * (color.m_color[2] - iter.m_color[2])));

            if (distance < maxDistance)
            {
                picked = iter;
                maxDistance = distance;
            }
        }

        return picked;
    }

    PNColor PalletCurver::Frag(int x, int y, PNColor color)
    {
        float maxDistance = 260;
        PNColor picked = intToColor(Pallet[0]);

        for (int i = 0; i < 40; i++)
        {
            PNColor iter = intToColor(Pallet[i]);

            float distance = std::sqrt(((color.m_color[0] - iter.m_color[0]) * (color.m_color[0] - iter.m_color[0])) +
                                       ((color.m_color[1] - iter.m_color[1]) * (color.m_color[1] - iter.m_color[1])) +
                                       ((color.m_color[2] - iter.m_color[2]) * (color.m_color[2] - iter.m_color[2])));

            if (distance < maxDistance)
            {
                picked = iter;
                maxDistance = distance;
            }
        }

        return picked;
    }

    void PalletCurver::ImGuiUpdate()
    {
        ImGui::Text("Pallet Curver");
    }
} // namespace puffin
