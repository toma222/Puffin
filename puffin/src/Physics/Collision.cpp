
/*

#include "Scene/Entity.h"
#include "Collision.h"

namespace puffin
{
    int CheckCollision(Entity A, Entity B)
    {
        components::Transform Atransform = A.GetComponent<components::Transform>();
        components::Rigidbody2D Arigidbody = A.GetComponent<components::Rigidbody2D>();
        components::BoxCollider ABoxCollider = A.GetComponent<components::BoxCollider>();

        components::Transform Btransform = B.GetComponent<components::Transform>();
        components::Rigidbody2D Brigidbody = B.GetComponent<components::Rigidbody2D>();
        components::BoxCollider BBoxCollider = B.GetComponent<components::BoxCollider>();

        // Check for simple box collision
        // * have the same deal for adding components to scean so that we handle all the check cases ourselvs

        bool colliding = true;

        // Get bounds of the rectangles
        Vector2 r2 = Vector2(Atransform.m_rect->x + Atransform.m_rect->w, Atransform.m_rect->y + Atransform.m_rect->h);
        Vector2 l2 = Vector2(Btransform.m_rect->x + Btransform.m_rect->w, Btransform.m_rect->y + Btransform.m_rect->h);

        Vector2 r1 = Vector2(Atransform.m_rect->x, Atransform.m_rect->y);
        Vector2 l1 = Vector2(Btransform.m_rect->x, Btransform.m_rect->y);

        if (!((r1.x > l2.x) || (r2.x < l1.x) || (r1.y > l2.y) || (r2.y < l1.y)))
        {
            return PENETRATING;
        }
        else
        {
            return NOT_COLLIDING;
        }
    }

    void ApplyImpulse(Entity A, Entity B)
    {
        components::Transform Atransform = A.GetComponent<components::Transform>();
        components::Rigidbody2D Arigidbody = A.GetComponent<components::Rigidbody2D>();

        components::Transform Btransform = B.GetComponent<components::Transform>();
        components::Rigidbody2D Brigidbody = B.GetComponent<components::Rigidbody2D>();

        Vector2 collisionNormal = Vector2(Atransform.m_rect->x - Btransform.m_rect->x, Atransform.m_rect->y - Btransform.m_rect->y);
        Vector2 relativeVelocity = Vector2(Arigidbody.m_velocity.x - Brigidbody.m_velocity.x, Arigidbody.m_velocity.y - Brigidbody.m_velocity.y);

        collisionNormal.NormalizeVector();

        float e = 0.0f; // who knows what this does
        float J = (-(1 + e) * relativeVelocity.DotProduct(collisionNormal)) / ((1 / Arigidbody.m_mass) + (1 / Brigidbody.m_mass));

        Arigidbody.m_velocity.x += (1 / Arigidbody.m_mass) * J * collisionNormal.x;
        Arigidbody.m_velocity.y += (1 / Arigidbody.m_mass) * J * collisionNormal.y;

        Brigidbody.m_velocity.x -= (1 / Brigidbody.m_mass) * J * collisionNormal.x;
        Brigidbody.m_velocity.y -= (1 / Brigidbody.m_mass) * J * collisionNormal.y;
    }
} // namespace puffin
*/