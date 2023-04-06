
/*
#include "Math/PNVector.h"
#include "Physics.h"
#include "Collision.h"
#include "Core/Timestep.h"

#define LINIER_DRAG_COEFFICIENT 0.1

namespace puffin
{
    float Physics2D::s_e = 0.5f;
    float Physics2D::s_gravity = 5.0f;

    void Physics2D::UpdateBodyEuler(Entity e, Timestep deltaTime)
    {
        components::Rigidbody2D &rigidbody = e.GetComponent<components::Rigidbody2D>();
        components::Transform &transform = e.GetComponent<components::Transform>();

        CalculateLoads(rigidbody, deltaTime);

        // Done!

        if (rigidbody.m_simulated)
        {
            Vector2 acceleration = Vector2(rigidbody.m_forces.x / rigidbody.m_mass,
                                           rigidbody.m_forces.y / rigidbody.m_mass);

            Vector2 deltaVelocity = Vector2(acceleration.x * deltaTime, acceleration.y * deltaTime);

            rigidbody.m_velocity.x += deltaVelocity.x;
            rigidbody.m_velocity.y += deltaVelocity.y;

            transform.m_rect->x += rigidbody.m_velocity.x * deltaTime;
            transform.m_rect->y += rigidbody.m_velocity.y * deltaTime;

            rigidbody.m_forces.x = 0;
            rigidbody.m_forces.y = 0;
        }
    }

    void Physics2D::CalculateLoads(components::Rigidbody2D &body, Timestep time)
    {
        // Calculate Gravity
        if (body.m_gravity)
        {
            body.m_forces.y += s_gravity;
        }

        body.m_speed = body.m_velocity.CalculateMagnitude();

        float tmp = 0.5f * body.m_speed * body.m_speed * body.m_drag;

        body.m_forces.x += -body.m_velocity.x * tmp * LINIER_DRAG_COEFFICIENT;
        body.m_forces.y += -body.m_velocity.y * tmp * LINIER_DRAG_COEFFICIENT;
    }
}; // namespace puffin

*/