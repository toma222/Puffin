#pragma once

#include "Core/Container.h"
#include "Core/ID.h"

#include "Math/PNVector.h"

#include "Component.h"

#include <SDL2/SDL.h>

namespace puffin
{
    namespace components
    {
        class Rigidbody2D : public Component
        {
        public:
            static PUFFIN_ID COMPONENT_ID;

        public:
            void UpdateComponent() override;
            void StartComponent() override;
            void UpdateComponentImGui() override;

            PUFFIN_ID GetID() override
            {
                if (COMPONENT_ID == 0)
                {
                    COMPONENT_ID = IDGenerator::Get().GetRandomID();
                }

                return COMPONENT_ID;
            };

            Rigidbody2D(Entity *entity, float mass);
            ~Rigidbody2D() override;

            Entity *m_entity;

        public:
            float m_mass;
            Vector2 m_velocity;
        };

    } // namespace components

} // namespace puffin
