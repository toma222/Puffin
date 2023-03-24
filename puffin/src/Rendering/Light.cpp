
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

        return PNColor(lum, lum, lum);
    }
} // namespace puffin
