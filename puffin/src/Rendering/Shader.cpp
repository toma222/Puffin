
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
            ImGui::Checkbox("Active", &m_active);

            ImGui::TreePop();
        }
    }

    PNColor CrossDithering::Frag(int x, int y, PNColor color)
    {
        const int dithering_matrix[8][8] = {
            {2, 50, 14, 62, 3, 51, 15, 63},
            {48, 18, 46, 16, 52, 22, 50, 20},
            {13, 45, 7, 39, 12, 44, 6, 38},
            {61, 31, 59, 29, 62, 32, 60, 30},
            {4, 52, 16, 64, 1, 49, 13, 61},
            {50, 20, 48, 18, 52, 22, 50, 20},
            {15, 47, 9, 41, 14, 46, 8, 40},
            {63, 33, 61, 31, 62, 32, 60, 30}};

        // ANTI ALIASING
        int xm = x % 8;
        int ym = y % 8;

        float M = dithering_matrix[xm][ym] + 1;
        float p = M * (1 / 64) - 0.5f;

        color.m_color[0] += (m_spread * M);
        color.m_color[1] += (m_spread * M);
        color.m_color[2] += (m_spread * M);

        return color;
    }

    void CrossDithering::ImGuiUpdate()
    {
        if (ImGui::TreeNode("Cross Dithering"))
        {
            ImGui::Checkbox("Active", &m_active);
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

                bottomRightSquare[(px * m_boxSize) + py] = c.LuminanceScaled();
                bottomRightSTD += c.LuminanceScaled();
            }
        }

        // Top Left
        for (int px = 0; px < m_boxSize; px++)
        {
            for (int py = 0; py < m_boxSize; py++)
            {
                PNColor c = m_surfaceRef->GetPixel(x - px, py + y);

                bottomLeftSquare[(px * m_boxSize) + py] = c.LuminanceScaled();
                bottomLeftSTD += c.LuminanceScaled();
            }
        }

        // Bottom Left
        for (int px = 0; px < m_boxSize; px++)
        {
            for (int py = 0; py < m_boxSize; py++)
            {
                PNColor c = m_surfaceRef->GetPixel(x - px, y - py);

                topLeftSquare[(px * m_boxSize) + py] = c.LuminanceScaled();
                topLeftSTD += c.LuminanceScaled();
            }
        }

        // Bottom Right
        for (int px = 0; px < m_boxSize; px++)
        {
            for (int py = 0; py < m_boxSize; py++)
            {
                PNColor c = m_surfaceRef->GetPixel(px + x, y - py);

                topRightSquare[(px * m_boxSize) + py] = c.LuminanceScaled();
                topRightSTD += c.LuminanceScaled();
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

        for (int i = 0; i < m_boxSize * m_boxSize; i++)
        {
            TLsum += (topLeftSquare[i] - topLeftSTD) * (topLeftSquare[i] - topLeftSTD);
            BLsum += (bottomLeftSquare[i] - bottomLeftSTD) * (bottomLeftSquare[i] - bottomLeftSTD);
            TRsum += (topRightSquare[i] - topRightSTD) * (topRightSquare[i] - topRightSTD);
            BRsum += (bottomRightSquare[i] - bottomRightSTD) * (bottomRightSquare[i] - bottomRightSTD);
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

        if (bottomLeftSTD > topRightSTD && bottomLeftSTD > bottomRightSTD && bottomLeftSTD > topLeftSTD)
        {
            // Bottom Left wins
            xSign = -1;
            ySign = 1;
        }

        if (bottomRightSTD > topLeftSTD && bottomRightSTD > topRightSTD && bottomRightSTD > bottomLeftSTD)
        {
            // Bottom Right wins
            xSign = 1;
            ySign = 1;
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
            ImGui::Checkbox("Active", &m_active);
            ImGui::SliderInt("Box Size", &m_boxSize, 0, 50);
            ImGui::TreePop();
        }
    }

    PNColor Blur::Frag(int x, int y, PNColor color)
    {
        PNColor convolution = PNColor(0, 0, 0);

        if (x < m_kernalSize && y < m_kernalSize)
            return color;

        if (x + m_kernalSize > 192 && y + m_kernalSize > 108)
            return color;

        for (int kernalX = 0; kernalX < m_kernalSize; kernalX++)
        {
            for (int kernalY = 0; kernalY < m_kernalSize; kernalY++)
            {
                convolution.m_color[0] += color.m_color[0] * 0.1;
                convolution.m_color[1] += color.m_color[2] * 0.1;
                convolution.m_color[2] += color.m_color[2] * 0.1;
            }
        }

        return convolution;
    };

    void Blur::SetKernel(BLUR_ALGORITHM algorithm, int kernalSize)
    {
        printf("%i\n", m_kernalSize);
        for (int x = 0; x < m_kernalSize; x++)
        {
            for (int y = 0; y < m_kernalSize; y++)
            {
                printf("%f\n", (double)(1 / 9));
                m_kernal[x][y] = 1 / (m_kernalSize * m_kernalSize);
            }
        }
    }

    void Blur::ImGuiUpdate()
    {
        if (ImGui::TreeNode("Blur"))
        {
            ImGui::SliderInt("Kernal Size (does not update)", &m_kernalSize, 0, 5);

            ImGui::TreePop();
        }
    };
} // namespace puffin
