
#include "Heirarchy.h"

#include "puffin.h"

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"
#include <imgui/imgui_internal.h>

#include <memory>

namespace antarctica
{
    void Heirarchy::AttachContext(std::shared_ptr<puffin::Scene> sceneRef)
    {
        m_sceneRef = sceneRef;
        m_selectedEntity = {};
    }

    template <typename T, typename UIFunction>
    static void DrawComponent(const std::string &name, puffin::Entity entity, UIFunction uiFunction)
    {
        const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
        if (entity.HasComponent<T>())
        {
            auto &component = entity.GetComponent<T>();
            ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{4, 4});
            float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
            ImGui::Separator();
            bool open = ImGui::TreeNodeEx((void *)typeid(T).hash_code(), treeNodeFlags, name.c_str());
            ImGui::PopStyleVar();
            ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
            if (ImGui::Button("+", ImVec2{lineHeight, lineHeight}))
            {
                ImGui::OpenPopup("ComponentSettings");
            }

            bool removeComponent = false;
            if (ImGui::BeginPopup("ComponentSettings"))
            {
                if (ImGui::MenuItem("Remove component"))
                    removeComponent = true;

                ImGui::EndPopup();
            }

            if (open)
            {
                uiFunction(component);
                ImGui::TreePop();
            }

            if (removeComponent)
                entity.RemoveComponent<T>();
        }
    }

    puffin::Entity Heirarchy::GetSelectedEntity()
    {
        return m_selectedEntity;
    }

    void Heirarchy::DrawEntityNode(puffin::Entity entity)
    {
        ImGuiTreeNodeFlags flags = ((m_selectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
        flags |= ImGuiTreeNodeFlags_SpanAvailWidth;

        puffin::components::Tag &tag = entity.GetComponent<puffin::components::Tag>();

        bool opened = ImGui::TreeNodeEx((void *)(uint64_t)(uint32_t)entity, flags, tag.m_Tag.c_str());

        if (ImGui::IsItemClicked())
        {
            m_selectedEntity = entity;
        }

        if (ImGui::BeginPopupContextItem())
        {
            if (ImGui::MenuItem("Delete Entity"))
            {
                printf("Delete entity at some point\n");
            }

            ImGui::EndPopup();
        }

        if (opened)
        {
            ImGui::TreePop();
        }
    }

    void Heirarchy::RenderImGui()
    {
        ImGui::Begin("Heirarchy");
        ImGui::Text("%s", m_sceneRef->m_name.c_str());

        if (m_sceneRef)
        {
            if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
                m_selectedEntity = {};

            // Right-click on blank space
            /*
            if (ImGui::BeginPopupContextWindow(0, 1, false))
            {
                if (ImGui::MenuItem("Create Empty Entity"))
                    m_sceneRef->AddEntity("Empty Entity");

                ImGui::EndPopup();
            }
            */

            for (auto [key, entity] : m_sceneRef->m_entities)
            {
                DrawEntityNode({m_sceneRef.get(), entity});
            }
        }

        ImGui::End();

        ImGui::Begin("Properties");

        if (m_selectedEntity)
        {
            RenderSelectedEntityComponents(m_selectedEntity);
        }

        ImGui::End();
    }

    void Heirarchy::RenderSelectedEntityComponents(puffin::Entity entity)
    {
        ImGui::Text("%s", entity.GetName().c_str());
        ImGui::Text("%lld", (uint64_t)entity.GetUUID());

        ImGui::PushItemWidth(-1);

        if (ImGui::Button("Add Component"))
            ImGui::OpenPopup("AddComponent");

        if (ImGui::BeginPopup("AddComponent"))
        {
            DisplayComponentEntry<puffin::components::Image>("Image");

            ImGui::EndPopup();
        }

        ImGui::PopItemWidth();

        DrawComponent<puffin::components::Transform>("Transform", entity, [](auto &component)
                                                     { 
            ImGui::InputInt("Position x", &component.m_rect->x);
            ImGui::InputInt("Position y", &component.m_rect->y);
            ImGui::InputInt("Width", &component.m_rect->w);
            ImGui::InputInt("Height", &component.m_rect->h); });

        DrawComponent<puffin::components::Image>("Image", entity, [](auto &component)
                                                 { ImGui::Text("%s", component.m_path.c_str()); });

        DrawComponent<puffin::components::Script>("Script", entity, [](auto &component)
                                                  { ImGui::Text("%s", component.m_path.c_str());
                                                    ImGui::Text("%s", component.m_scriptInstance->m_moduleName.c_str()); });

        DrawComponent<puffin::components::RigidBody2D>("RigidBody2D", entity, [](auto &component)
                                                       { 
        const char* items[] = { "Static", "Dynamic" };
        static const char* current_item = NULL;

        if (ImGui::BeginCombo("##combo", current_item)) // The second parameter is the label previewed before opening the combo.
        {
            for (int n = 0; n < IM_ARRAYSIZE(items); n++)
            {
                bool is_selected = (current_item == items[n]); // You can store your selection however you want, outside or inside your objects
                if (ImGui::Selectable(items[n], is_selected))
                {         
                    current_item = items[n];

                    if(n == 0)
                        component.m_type = puffin::components::RigidBody2D::STATIC;                

                    if(n == 1)
                        component.m_type = puffin::components::RigidBody2D::DYNAMIC;
                    
                }   

                if (is_selected)
                    ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
            }
            ImGui::EndCombo();
        } 
        ImGui::Checkbox("Physics", &component.m_model.m_gravity);
        ImGui::InputFloat("Gravity Scale", &component.m_model.m_gravityScale); });
    }

    template <typename T>
    bool Heirarchy::DisplayComponentEntry(const std::string &entryName)
    {
        if (!m_selectedEntity.HasComponent<T>())
        {
            if (ImGui::MenuItem(entryName.c_str()))
            {
                m_selectedEntity.AddComponent<T>();
                ImGui::CloseCurrentPopup();
                return true;
            }
        }
        else
        {
            ImGui::Text("(%s)", entryName.c_str());
        }

        return false;
    }

} // namespace antarctica
