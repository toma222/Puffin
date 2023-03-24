#pragma once

#include <functional>
#include <cstdio>

#include "Math/PNVector.h"

namespace puffin
{

    // @param func this function must take in two ints and output a float
    class LightType
    {
    public:
        virtual PNColor GetPixelColor(int pixelX, int pixelY, int lightX, int lightY)
        {
            return PNColor(0, 0, 0);
        };
    };

    class PointLight : public LightType
    {
    private:
        float m_power;
        float m_luminance;

    public:
        PointLight(float power, float luminance)
            : m_power(power), m_luminance(luminance){};

        PNColor GetPixelColor(int pixelX, int pixelY, int lightX, int lightY) override;
    };

    class LightProfile
    {
    public:
        LightType m_lightType;

        int m_x;
        int m_y;

        LightProfile(LightType type, int x, int y)
            : m_lightType(type), m_x(x), m_y(y){};
    };

} // namespace puffin
