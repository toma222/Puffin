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
            class Collision
            {
            public:
                Entity *m_attached;

                Collision(Entity *att)
                {
                    m_attached = att;
                }

                virtual bool CheckCollision();
                virtual void ResolveCollision(Entity *b);
            };

            std::unique_ptr<Collision> m_collisionResolver;

            template <typename T>
            void AddCollisionResolver()
            {
                m_collisionResolver = std::dynamic_pointer_cast<Collision>(
                    std::make_unique<T>(this));
            }

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
            float m_terminalVelocity;
            Vector2 m_velocity;
        };

        class AABB : public Rigidbody2D::Collision
        {
        public:
            virtual bool CheckCollision()
            {
            }

            virtual void ResolveCollision(Entity *a, Entity *b)
            {
            }
        };

    } // namespace components

} // namespace puffin
