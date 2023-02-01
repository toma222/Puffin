
#include "Components/Transform.h"
#include "Components/Rigidbody2D.h"

#include "Core/Container.h"

#include "Physics.h"

namespace puffin
{
    void PhysicsSystem::Start()
    {
    }

    void PhysicsSystem::Update()
    {
        for (auto *ent : m_currentEntities)
        {
            ent->GetComponent<components::Transform>()->Translate(0, 0);
        }
    }

    void PhysicsSystem::OnImGuiUpdate()
    {
        printf("Start\n");
    }

    void Physics::AddRequiredComponent(PUFFIN_ID id) override
    {
        m_requiredComponents[0] = components::Rigidbody2D::COMPONENT_ID;
    }

    bool Physics::CheckComponent(PUFFIN_ID componentID, Entity *entity) override
    {
        for (size_t comp = 0; comp < 8; comp++)
        {
            //* PUT_THE COMPONENTS YOU WANT IN HERE
            if (componentID == components::Rigidbody2D::COMPONENT_ID)
            {
                PN_CORE_TRACE("Found a match");

                m_currentEntities.push_back(entity);
                Start();
                return true;
            }
        }
        return false;
    }
} // namespace puffin
