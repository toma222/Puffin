#pragma once
#include <cmath>

namespace puffin
{
    struct Vector2
    {
        int x;
        int y;

        double direction;
        double magnitude;

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

        Vector2 operator+(Vector2 const &obj)
        {
            x += obj.x;
            y += obj.y;

            CalculateMagnitude();
            CalculateDirection();
        }
    };
} // namespace puffin
