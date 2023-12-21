/*
#pragma once

#include "Scene/Entity.h"

#include <functional>

#define PENETRATING 1
#define COLLIDING 0
#define NOT_COLLIDING -1;

namespace puffin
{
    
    class Collider
    {
        public:
            std::function<int(Entity)>() CheckFunction;
    }
    

int CheckCollision(Entity A, Entity B);
void ApplyImpulse(Entity A, Entity B);
} // namespace puffin

*/