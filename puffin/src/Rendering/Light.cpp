
#include "Light.h"
#include "Math/PNVector.h"

#include "imgui.h"

namespace puffin
{
    PNColor PointLight::GetPixelColor(int pixelX, int pixelY, int lightX, int lightY)
    {
        float distance = std::sqrt(((pixelX - lightX) * (pixelX - lightX)) + ((pixelY - lightY) * (pixelY - lightY)));
        float lum = 1 - std::min(distance / m_power, 1.0f);

        return PNColor(lum * m_lightColor.m_color[0], lum * m_lightColor.m_color[1], lum * m_lightColor.m_color[2]);
    }

    void PointLight::UpdateImGui()
    {
        ImGui::Text("Type : Point light");
        ImGui::ColorEdit3("Light Color", m_lightColor.m_color);
        ImGui::InputFloat("Luminance", &m_luminance);
        ImGui::InputFloat("Power", &m_power);
    }

    PNColor GlobalLight::GetPixelColor(int pixelX, int pixelY, int lightX, int lightY)
    {
        return PNColor(m_power * (m_lightColor.m_color[0]), m_power * (m_lightColor.m_color[1]), m_power * (m_lightColor.m_color[2]));
    }

    void GlobalLight::UpdateImGui()
    {
        ImGui::Text("Type : Global light");
        ImGui::ColorEdit3("Light Color", m_lightColor.m_color);
    }
} // namespace puffin
