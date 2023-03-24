
#include "Light.h"
#include "Math/PNVector.h"
namespace puffin
{
    PNColor PointLight::GetPixelColor(int pixelX, int pixelY, int lightX, int lightY)
    {
        // Standard distance formula
        float distance = std::sqrt(((pixelX - lightX) * (pixelX - lightX)) + ((pixelY - lightY) * (pixelY - lightY)));

        return PNColor(0, 0, 0);
    }
} // namespace puffin
