#pragma once
#include <cmath>

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
} // namespace puffin
