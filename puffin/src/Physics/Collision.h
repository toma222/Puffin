
#pragma once

#include "Scene/Entity.h"

#include <functional>

namespace puffin
{
    /*
    class Collider
    {
        public:
            std::function<int(Entity)>() CheckFunction;
    }
    */

    int CheckCollision(Entity A, Entity B);
    void ApplyImpulse();
} // namespace puffin
