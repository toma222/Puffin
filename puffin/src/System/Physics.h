
#pragma once

#include "Core/Container.h"
#include "Components/Rigidbody2D.h"

namespace puffin
{
    class PhysicsSystem : public System
    {
    public:
        std::vector<Entity *> m_currentEntities;
        PUFFIN_ID m_requiredComponents[8];

        PhysicsSystem()
        {
            return;
        }

        ~PhysicsSystem() override
        {
            return;
        }

        void Start() override;
        void Update() override;
        void OnImGuiUpdate() override;

        void AddRequiredComponent(PUFFIN_ID id) override;
        bool CheckComponent(PUFFIN_ID componentID, Entity *entity) override;
    };
} // namespace puffin
