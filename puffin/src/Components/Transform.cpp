
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"

#include "Component.h"
#include "Transform.h"
#include <cstdio>

namespace puffin
{
    namespace components
    {
        void Transform::UpdateComponent()
        {
            return;
        }

        void Transform::StartComponent()
        {
            m_x = 0;
            m_y = 0;
            m_z = 0;
        }

        void Transform::Translate(float x, float y, float z)
        {
            m_x += x;
            m_y += y;
            m_z += z;
        }

        void Transform::UpdateComponentImGui()
        {
            ImGui::BeginChild("transform", ImVec2(300, 120), true);

            ImGui::Text("Transform Component - COMP ID %i", m_entity->GetEntityID());
            ImGui::InputFloat("X position", &m_x, 0.5f, 2.0f);
            ImGui::InputFloat("Y position", &m_y, 0.5f, 2.0f);
            ImGui::InputFloat("Z position", &m_z, 0.5f, 2.0f);

            ImGui::EndChild();
            return;
        }
    } // namespace components
} // namespace puffin
