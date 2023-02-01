
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"

#include "Component.h"
#include "Core/ID.h"
#include "Rigidbody2D.h"
#include "Transform.h"
#include <cstdio>

namespace puffin
{
    namespace components
    {
        PUFFIN_ID Rigidbody2D::COMPONENT_ID = IDGenerator::Get().GetRandomID();

        Rigidbody2D::Rigidbody2D(Entity *entity, float mass) : m_velocity(0, 0)
        {
            m_entity = entity;

            m_mass = mass;

            if (COMPONENT_ID == 0)
                COMPONENT_ID = IDGenerator::Get().GetRandomID();
        }

        Rigidbody2D::~Rigidbody2D()
        {
            PN_CORE_CLEAN("Rigidbody2D Deconstructor called");
            return;
        }

        void Rigidbody2D::UpdateComponent()
        {
            m_entity->GetComponent<Transform>()->Translate((int)m_velocity.x, (int)m_velocity.y);
            return;
        }

        void Rigidbody2D::StartComponent()
        {
        }

        void Rigidbody2D::UpdateComponentImGui()
        {
            ImGui::BeginChild("Rigidbody2D", ImVec2(300, 150), true);

            ImGui::Text("Rigidbody2D - id %lu", COMPONENT_ID);

            ImGui::InputDouble("Velocity X", &m_velocity.x);
            ImGui::InputDouble("Velocity Y", &m_velocity.y);

            ImGui::EndChild();
            return;
        }
    } // namespace components
} // namespace puffin
