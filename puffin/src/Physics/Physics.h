
#pragma once

#include "Scene/Components.h"
#include "Collision.h"
#include "Scene/Entity.h"
#include "Core/Timestep.h"

#include <functional>
#include <cstdint>

// Holds the code for the physics model


namespace puffin
{
    class Model
    {
    public:
        std::function<void(Entity)> m_CalculateLoadsFunction;

        // ! implement this with the std::function loading and stuff
        void AttachLoadFunction()
        {

        }
    };

    class Physics2D
    {
        public:
        static void UpdateBodyEuler(Entity body, Timestep time);
        static void CalculateLoads(components::Rigidbody2D &body, Timestep time);

        public:
        static float s_gravity;
        static float s_e; // the elastic for collision IDK // TODO find out what e means in the j calc
    };

} // namespace puffin
