
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"

#include "Components/Transform.h"
#include "Components/Rigidbody2D.h"

#include "Core/Container.h"

#include "Physics.h"

namespace puffin
{
    // Called every time an entity is added
    void PhysicsSystem::Start()
    {
        }

    // called at the end of the entity update loop
    void PhysicsSystem::Update()
    {
        for (auto *ent : m_currentEntities)
        {
            components::Rigidbody2D *rb = ent->GetComponent<components::Rigidbody2D>();
            rb->m_velocity.x += m_globalGravity.x;
            rb->m_velocity.y += m_globalGravity.y;
        }
    }

    void PhysicsSystem::OnImGuiUpdate()
    {
        ImGui::BeginChild("PhysicsSystem", {300, 200}, true, 0);

        ImGui::InputDouble("Gravity X", &m_globalGravity.x);
        ImGui::InputDouble("Gravity Y", &m_globalGravity.y);

        ImGui::EndChild();
    }

    bool PhysicsSystem::CheckComponent(PUFFIN_ID componentID, Entity *entity)
    {
        //* put component you want to check for here *//
        if (componentID == components::Rigidbody2D::COMPONENT_ID)
        {
            m_currentEntities.push_back(entity);
            Start();
            return true;
        }

        return false;
    }
} // namespace puffin
