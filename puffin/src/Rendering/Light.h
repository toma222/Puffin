#pragma once

#include <functional>
#include <cstdio>

#include "Math/PNVector.h"

namespace puffin
{
    enum LIGHT_TYPE
    {
        POINT,
        GLOBAL
    };

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
        PointLight(float power, float luminance, PNColor lightColor = PNColor(255, 255, 255))
            : m_power(power), m_luminance(luminance)
        {
            m_lightColor = PNColor(lightColor.m_color[0] / 255, lightColor.m_color[1] / 255, lightColor.m_color[2] / 255);
        };

        PNColor GetPixelColor(int pixelX, int pixelY, int lightX, int lightY) override;
    };

    class GlobalLight : public LightType
    {
    private:
        float m_power;

    public:
        GlobalLight(float power, PNColor lightColor = PNColor(255, 255, 255))
            : m_power(power)
        {
            m_lightColor = PNColor(lightColor.m_color[0] / 255, lightColor.m_color[1] / 255, lightColor.m_color[2] / 255);
        };

        PNColor GetPixelColor(int pixelX, int pixelY, int lightX, int lightY) override;
    };

    class LightProfile
    {
    public:
        // ! change to smart pointer later
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
