
#include "Physics.h"
#include "Math/PNVector.h"

#include <cstdio>

#define LINIER_DRAG_COEFFICIENT 0.1

namespace puffin
{
    PNRect Physics2D::UpdateBodyEuler(PhysicsModel *model, Timestep deltaTime)
    {
        model->m_forces.x = 0;
        model->m_forces.y = 0;

        model->m_speed = model->m_velocity.CalculateMagnitude();

        CalculateLoads(model, deltaTime);

        Vector2 a((model->m_forces.x / model->m_mass) * deltaTime.GetMilliseconds(),
                  (model->m_forces.y / model->m_mass) * deltaTime.GetMilliseconds());

        model->m_velocity.x += a.x;
        model->m_velocity.y += a.y;

        return PNRect(model->m_velocity.x * deltaTime.GetMilliseconds(),
                      model->m_velocity.y * deltaTime.GetMilliseconds(),
                      0, 0);
    }

    void Physics2D::CalculateLoads(PhysicsModel *model, Timestep time)
    {
        model->m_forces.y = model->m_gravityScale * model->m_gravity;

        float tmp = 0.5f * model->m_speed * model->m_speed;

        model->m_forces.x += -model->m_velocity.x * tmp * LINIER_DRAG_COEFFICIENT;
        model->m_forces.y += -model->m_velocity.y * tmp * LINIER_DRAG_COEFFICIENT;
    }
} // namespace puffin
