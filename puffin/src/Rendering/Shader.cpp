
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

    PNColor KuwaharaFilter::Frag(int x, int y, PNColor color)
    {
        if (x + m_boxSize > 192 || y + m_boxSize > 108)
        {
            return color;
        }

        if (x <= m_boxSize || y <= m_boxSize)
        {
            return color;
        }

        float topLeftSTD = 0;
        float topLeftSquare[m_boxSize * m_boxSize];

        float topRightSTD = 0;
        float topRightSquare[m_boxSize * m_boxSize];

        float bottomLeftSTD = 0;
        float bottomLeftSquare[m_boxSize * m_boxSize];

        float bottomRightSTD = 0;
        float bottomRightSquare[m_boxSize * m_boxSize];

        // Calculate standard deviation

        // Top Right
        for (int px = 0; px < m_boxSize; px++)
        {
            for (int py = 0; py < m_boxSize; py++)
            {
                PNColor c = m_surfaceRef->GetPixel(px + x, py + y);

                float brightness = (c.m_color[0] + c.m_color[1] + c.m_color[2]) / 3;
                bottomRightSquare[(px * m_boxSize) + py] = brightness;
                bottomRightSTD += brightness;
            }
        }

        // Top Left
        for (int px = 0; px < m_boxSize; px++)
        {
            for (int py = 0; py < m_boxSize; py++)
            {
                PNColor c = m_surfaceRef->GetPixel(x - px, py + y);

                float brightness = (c.m_color[0] + c.m_color[1] + c.m_color[2]) / 3;
                bottomLeftSquare[(px * m_boxSize) + py] = brightness;
                bottomLeftSTD += brightness;
            }
        }

        // Bottom Left
        for (int px = 0; px < m_boxSize; px++)
        {
            for (int py = 0; py < m_boxSize; py++)
            {
                PNColor c = m_surfaceRef->GetPixel(x - px, y - py);

                float brightness = (c.m_color[0] + c.m_color[1] + c.m_color[2]) / 3;
                topLeftSquare[(px * m_boxSize) + py] = brightness;
                topLeftSTD += brightness;
            }
        }

        // Bottom Right
        for (int px = 0; px < m_boxSize; px++)
        {
            for (int py = 0; py < m_boxSize; py++)
            {
                PNColor c = m_surfaceRef->GetPixel(px + x, y - py);

                float brightness = (c.m_color[0] + c.m_color[1] + c.m_color[2]) / 3;
                topRightSquare[(px * m_boxSize) + py] = brightness;
                topRightSTD += brightness;
            }
        }

        // Find the standard deviation
        topLeftSTD /= (m_boxSize * m_boxSize);
        topRightSTD /= (m_boxSize * m_boxSize);
        bottomLeftSTD /= (m_boxSize * m_boxSize);
        bottomRightSTD /= (m_boxSize * m_boxSize);

        float TLsum = 0;
        float BLsum = 0;
        float TRsum = 0;
        float BRsum = 0;

        for (int i = 0; i < m_boxSize; i++)
        {
            TLsum += (topLeftSquare[i] - topLeftSTD) * (topLeftSquare[i] - topLeftSTD);
            BLsum += (topLeftSquare[i] - bottomLeftSTD) * (topLeftSquare[i] - bottomLeftSTD);
            TRsum += (topLeftSquare[i] - topRightSTD) * (topLeftSquare[i] - topRightSTD);
            BRsum += (topLeftSquare[i] - bottomRightSTD) * (topLeftSquare[i] - bottomRightSTD);
        }

        topLeftSTD = std::sqrt(TLsum / (m_boxSize * m_boxSize));
        topRightSTD = std::sqrt(TRsum / (m_boxSize * m_boxSize));
        bottomLeftSTD = std::sqrt(BLsum / (m_boxSize * m_boxSize));
        bottomRightSTD = std::sqrt(BRsum / (m_boxSize * m_boxSize));

        // pick the square with the least STD
        int xSign = 0;
        int ySign = 0;

        if (topLeftSTD > topRightSTD && topLeftSTD > bottomRightSTD && topLeftSTD > bottomLeftSTD)
        {
            // Top Left wins
            xSign = -1;
            ySign = -1;
        }

        if (topRightSTD > topLeftSTD && topRightSTD > bottomRightSTD && topRightSTD > bottomLeftSTD)
        {
            // Top Right wins
            xSign = 1;
            ySign = -1;
        }

        // ! make bottom

        // Top Left tester
        PNColor averageColor = PNColor(0, 0, 0);

        for (int px = 0; px < m_boxSize; px++)
        {
            for (int py = 0; py < m_boxSize; py++)
            {
                PNColor c = m_surfaceRef->GetPixel(px + (xSign * x), y + (ySign * py));

                averageColor.m_color[0] += c.m_color[0];
                averageColor.m_color[1] += c.m_color[1];
                averageColor.m_color[2] += c.m_color[2];
            }
        }

        averageColor.m_color[0] /= (m_boxSize * m_boxSize);
        averageColor.m_color[1] /= (m_boxSize * m_boxSize);
        averageColor.m_color[2] /= (m_boxSize * m_boxSize);

        return averageColor;
    }

    void KuwaharaFilter::ImGuiUpdate()
    {
        if (ImGui::TreeNode("Kuwahara Filter"))
        {
            ImGui::TreePop();
        }
    }
} // namespace puffin
