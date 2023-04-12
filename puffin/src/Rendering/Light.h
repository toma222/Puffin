#pragma once

#include <functional>
#include <cstdio>
#include <memory>

#include "Math/PNVector.h"

#include "imgui.h"

namespace puffin
{
    enum LIGHT_TYPE
    {
        POINT,
        GLOBAL,
        ERROR
    };

    // @param func this function must take in two ints and output a float
    class LightType
    {
    public:
        PNColor m_lightColor;

        virtual PNColor GetPixelColor(int pixelX, int pixelY, int lightX, int lightY) { return PNColor(0, 255, 0); };
        virtual void UpdateImGui(){};
        virtual LIGHT_TYPE GetType() { return ERROR; };
    };

    class PointLight : public LightType
    {
    public:
        float m_power;
        float m_luminance;

    public:
        PointLight(float power, float luminance, PNColor lightColor = PNColor(255, 255, 255))
            : m_power(power), m_luminance(luminance)
        {
            m_lightColor = PNColor(lightColor.m_color[0] / 255, lightColor.m_color[1] / 255, lightColor.m_color[2] / 255);
        };

        PNColor GetPixelColor(int pixelX, int pixelY, int lightX, int lightY) override;
        void UpdateImGui() override;

        LIGHT_TYPE GetType() override
        {
            return POINT;
        }

        const static LIGHT_TYPE s_TYPE = POINT;
    };

    class GlobalLight : public LightType
    {
    public:
        float m_power;

    public:
        GlobalLight(float power, PNColor lightColor = PNColor(255, 255, 255))
            : m_power(power)
        {
            m_lightColor = PNColor(lightColor.m_color[0] / 255, lightColor.m_color[1] / 255, lightColor.m_color[2] / 255);
        };

        PNColor GetPixelColor(int pixelX, int pixelY, int lightX, int lightY) override;
        void UpdateImGui() override;

        LIGHT_TYPE GetType() override
        {
            return GLOBAL;
        }

        const static LIGHT_TYPE s_TYPE = GLOBAL;
    };

    class LightProfile
    {
    public:
        // ! this is just a memory leak, here : cant delete because it causes undefined behavior
        std::shared_ptr<LightType> m_lightType;

        int m_x;
        int m_y;

        LightProfile(std::shared_ptr<LightType> type, int x, int y)
            : m_lightType(type), m_x(x), m_y(y){};

        ~LightProfile() = default;

        void UpdateImGui()
        {
            m_lightType->UpdateImGui();
        }
    };

} // namespace puffin
