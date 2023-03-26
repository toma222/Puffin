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
        PNColor m_lightColor;

        virtual PNColor GetPixelColor(int pixelX, int pixelY, int lightX, int lightY)
        {
            return PNColor(0, 255, 0);
        };
    };

    class PointLight : public LightType
    {
    private:
        float m_power;
        float m_luminance;

    public:
        PointLight(float power, float luminance, PNColor lightColor = PNColor(0, 0, 0))
            : m_power(power), m_luminance(luminance)
        {
            m_lightColor = lightColor;
        };

        PNColor GetPixelColor(int pixelX, int pixelY, int lightX, int lightY) override;
    };

    class GlobalLight : public LightType
    {
    private:
        float m_power;

    public:
        GlobalLight(float power, PNColor lightColor = PNColor(0, 0, 0))
            : m_power(power){};

        PNColor GetPixelColor(int pixelX, int pixelY, int lightX, int lightY) override;
    };

    class LightProfile
    {
    public:
        // ! this is just a memory leak, here : cant delete because it causes undefined behavior
        LightType *m_lightType;

        int m_x;
        int m_y;

        LightProfile(LightType *type, int x, int y)
            : m_lightType(type), m_x(x), m_y(y){};

        ~LightProfile()
        {
            // delete m_lightType;
        }
    };

} // namespace puffin
