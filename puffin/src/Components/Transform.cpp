
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
        Transform::Transform(Entity *entity, int x, int y, int w, int h)
        {
            transformRect = std::make_shared<SDL_Rect>();

            transformRect->x = x;
            transformRect->y = y;
            transformRect->w = w;
            transformRect->h = h;

            m_entity = entity;

            printf("Component id %li\n", COMPONENT_ID);
        }

        Transform::~Transform()
        {
            PN_CORE_CLEAN("Transform Deconstructor called");
            return;
        }

        void Transform::UpdateComponent()
        {
            return;
        }

        void Transform::StartComponent()
        {
            // m_x = 0;
            // m_y = 0;
            // m_z = 0;
        }

        void Transform::Translate(int x, int y)
        {
            transformRect->x += x;
            transformRect->y += y;
        }

        void Transform::UpdateComponentImGui()
        {
            ImGui::BeginChild("transform", ImVec2(300, 150), true);

            ImGui::Text("Transform - id %li", COMPONENT_ID);
            ImGui::InputInt("X position", &transformRect->x, 0.5f, 2.0f);
            ImGui::InputInt("Y position", &transformRect->y, 0.5f, 2.0f);
            ImGui::InputInt("Width", &transformRect->w, 0.5f, 2.0f);
            ImGui::InputInt("Height", &transformRect->h, 0.5f, 2.0f);

            ImGui::EndChild();
            return;
        }
    } // namespace components
} // namespace puffin
