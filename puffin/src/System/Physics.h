
#pragma once

#include "Core/Container.h"
#include "Components/Rigidbody2D.h"

namespace puffin
{
    class PhysicsSystem : public System
    {
    public:
        Vector2 m_globalGravity;
        int m_attachedEntities;

    public:
        std::vector<Entity *> m_currentEntities;

        PhysicsSystem() : m_globalGravity((double)0, (double)0)
        {
            m_globalGravity.x = (double)0;
            m_globalGravity.y = (double)1.0;

            return;
        }

        ~PhysicsSystem() override
        {
            return;
        }

        void Start() override;
        void Update() override;
        void OnImGuiUpdate() override;

        void Clear() override
        {
            m_currentEntities.clear();
        }

        bool CheckComponent(PUFFIN_ID componentID, Entity *entity) override;
    };
} // namespace puffin
