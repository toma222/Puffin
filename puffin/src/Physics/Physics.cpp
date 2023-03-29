

#include "Math/PNVector.h"
#include "Physics.h"
#include "Collision.h"
#include "Core/Timestep.h"

#define LINIER_DRAG_COEFFICIENT 0.1

namespace puffin
{
    float Physics2D::s_e = 0.5f;
    float Physics2D::s_gravity = 5.0f;

    void Physics2D::UpdateBodyEuler(Entity body, Timestep deltaTime)
    {
        components::Rigidbody2D &rigidbody = body.GetComponent<components::Rigidbody2D>();
        components::Transform &transform = body.GetComponent<components::Transform>();

        // Calculate loads here

        CalculateLoads(rigidbody, deltaTime);

        // Done!

        if (rigidbody.m_simulated)
        {
            rigidbody.m_speed = rigidbody.m_velocity.CalculateMagnitude();

            float tmp = 0.5f * rigidbody.m_speed * rigidbody.m_speed * rigidbody.m_drag;

            rigidbody.m_forces.x += -rigidbody.m_velocity.x * tmp * LINIER_DRAG_COEFFICIENT;
            rigidbody.m_forces.y += -rigidbody.m_velocity.y * tmp * LINIER_DRAG_COEFFICIENT;

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
        if(body.m_gravity)
        {
            body.m_forces.y += s_gravity;
        }
    }
}; // namespace puffin

