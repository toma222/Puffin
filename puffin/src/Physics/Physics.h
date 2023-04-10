

#pragma once

#include "Collision.h"
#include "Core/Timestep.h"

#include "Math/PNVector.h"

#include <functional>
#include <cstdint>
#include <vector>

// Holds the code for the physics model

namespace puffin
{
    class PhysicsModel
    {
    public:
        float m_mass;
        float m_inertia;

        Vector2 m_velocity;
        Vector2 m_velocityBody;
        Vector2 m_angularVelocity;

        float m_speed;

        Vector2 m_forces;
        Vector2 m_moment;

        float m_projectedArea;

        bool m_gravity;
        float m_gravityScale;

        PhysicsModel(float mass) : m_mass(mass)
        {
            m_gravity = false;
            m_projectedArea = 100;
        }

        PhysicsModel() = default;
    };

    class Physics2D
    {
    public:
        static PNRect UpdateBodyEuler(PhysicsModel *model, Timestep deltaTime);
        static void CalculateLoads(PhysicsModel *model, Timestep time);
    };

} // namespace puffin
