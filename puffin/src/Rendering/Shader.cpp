
#include "Shader.h"
#include "Math/PNVector.h"
#include <cstdio>
#include "imgui/imgui.h"

namespace puffin
{
    PNColor PalletCurver::Frag(int x, int y, PNColor color)
    {
        float maxDistance = 260;
        PNColor picked = PNColor(255, 0, 0);

        for (PNColor iter : m_pallet)
        {
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
        if (ImGui::TreeNode("Pallet Curve"))
        {
            ImGui::TreePop();
        }
    }

    PNColor CrossDithering::Frag(int x, int y, PNColor color)
    {
        const int map4x4[4][4] = {
            {0, 8, 2, 10},
            {12, 4, 14, 6},
            {3, 11, 1, 9},
            {15, 7, 13, 5}};

        // ANTI ALIASING
        int xm = x % 4;
        int ym = y % 4;

        float M = map4x4[xm][ym];
        float p = M * (1 / 16) - 0.5f;

        color.m_color[0] += (m_spread * M);
        color.m_color[1] += (m_spread * M);
        color.m_color[2] += (m_spread * M);

        return color;
    }

    void CrossDithering::ImGuiUpdate()
    {
        if (ImGui::TreeNode("Cross Dithering"))
        {
            ImGui::SliderFloat("Spread", &m_spread, 0, 1.0f);

            ImGui::TreePop();
        }
    }
} // namespace puffin
