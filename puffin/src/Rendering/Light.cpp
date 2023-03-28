
#include "Light.h"
#include "Math/PNVector.h"
namespace puffin
{
    PNColor PointLight::GetPixelColor(int pixelX, int pixelY, int lightX, int lightY)
    {
        // Standard distance formula
        float distance = std::sqrt(((pixelX - lightX) * (pixelX - lightX)) + ((pixelY - lightY) * (pixelY - lightY)));

        // needs to be in between 1 and 0;
        // 1 meaning the the pixel is fully lit
        // 0 meaning the pixel is not lit
        float lum = 1 - std::min(distance / m_power, 1.0f);

        return PNColor(lum * m_lightColor.m_color[0], lum * m_lightColor.m_color[1], lum * m_lightColor.m_color[2]);
    }

    PNColor SpotLight::GetPixelColor(int pixelX, int pixelY, int lightX, int lightY)
    {
        // Standard distance formula
        float distance = std::sqrt(((pixelX - lightX) * (pixelX - lightX)) + ((pixelY - lightY) * (pixelY - lightY)));

        Vector2 pv = Vector2(pixelX, pixelY);
        pv.NormalizeVector();

        double angle = pv.AngleBetweenVectors(m_direction);

        if (angle > 90)
        {
            return PNColor(1, 1, 1);
        }
        else
        {
            return PNColor(0, 0, 0);
        }

        // needs to be in between 1 and 0;
        // 1 meaning the the pixel is fully lit
        // 0 meaning the pixel is not lit
        // float lum = 1 - std::min(distance / m_power, 1.0f);

        // return PNColor(lum * m_lightColor.m_color[0], lum * m_lightColor.m_color[1], lum * m_lightColor.m_color[2]);
    }

    PNColor GlobalLight::GetPixelColor(int pixelX, int pixelY, int lightX, int lightY)
    {
        return PNColor(m_power * (m_lightColor.m_color[0] / 255), m_power * (m_lightColor.m_color[1] / 255), m_power * (m_lightColor.m_color[2] / 255));
    }
} // namespace puffin
