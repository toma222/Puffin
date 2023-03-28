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

        Vector2() = default;

        Vector2(double xv, double yv)
        {
            x = xv;
            y = yv;
        }

        double CalculateMagnitude()
        {
            magnitude = sqrt(x * x + y * y);
            return magnitude;
        }

        double CalculateDirection()
        {
            direction = atan(y / x);
            return direction;
        }

        void NormalizeVector()
        {
            double length = std::sqrt(x * x + y * y);

            x /= length;
            y /= length;
        }

        double DotProduct(Vector2 b)
        {
            return (x * b.x) + (y * b.y);
        }

        // @warning vectors must be normalized or this will be wrong
        double AngleBetweenVectors(Vector2 b)
        {
            // ! this is a slow thing (std::acos)
            return std::acos(DotProduct(b)) * (57.2957795131);
        }
    };

    struct PNColor
    {
        // float m_r;
        // float m_g;
        // float m_b;
        float m_color[3];

        PNColor() = default;
        PNColor(const PNColor &color) = default;
        PNColor(float r, float g, float b)
        {
            m_color[0] = r;
            m_color[1] = g;
            m_color[2] = b;
        }
    };

} // namespace puffin
