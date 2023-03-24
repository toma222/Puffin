#pragma once
#include <cmath>
#include <SDL2/SDL.h>

namespace puffin
{
    struct Vector2
    {
        double x;
        double y;

        double direction;
        double magnitude;

        Vector2(double xv, double yv)
        {
            x = xv;
            y = yv;
        }

        double CalculateMagnitude()
        {
            magnitude = sqrt(x * x * y * y);
            return magnitude;
        }

        double CalculateDirection()
        {
            direction = atan(y / x);
            return direction;
        }
    };

    struct PNColor
    {
        float m_r;
        float m_g;
        float m_b;

        PNColor() = default;
        PNColor(const PNColor &color) = default;
        PNColor(float r, float g, float b)
            : m_r(r), m_g(g), m_b(b);
    };

} // namespace puffin
