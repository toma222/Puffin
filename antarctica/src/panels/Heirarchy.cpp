
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
        m_selectedEntity = sceneRef->m_entities[0];
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

    void Heirarchy::RenderImGui()
    {
        ImGui::Begin("Heirarchy");

        if (m_sceneRef)
        {
            if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
                m_selectedEntity = {};

            // Right-click on blank space
            if (ImGui::BeginPopupContextWindow(0, false))
            {
                if (ImGui::MenuItem("Create Empty Entity"))
                    m_sceneRef->AddEntity("Empty Entity");

                ImGui::EndPopup();
            }

            for (auto entity : m_sceneRef->m_entities)
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

            if (DisplayComponentEntry<puffin::components::Light>("Point Light"))
            {
                m_selectedEntity.GetComponent<puffin::components::Light>().m_lightType = new puffin::PointLight(100, 100);
            }

            if (DisplayComponentEntry<puffin::components::Light>("Global Light"))
            {
                m_selectedEntity.GetComponent<puffin::components::Light>().m_lightType = new puffin::GlobalLight(100);
            }

            ImGui::EndPopup();
        }

        ImGui::PopItemWidth();

        DrawComponent<puffin::components::Transform>("Transform", entity, [](auto &component)
                                                     { 
            ImGui::InputInt("Position x", &component.m_rect.x);
            ImGui::InputInt("Position y", &component.m_rect.y);
            ImGui::InputInt("Width", &component.m_rect.w);
            ImGui::InputInt("Height", &component.m_rect.h); });

        DrawComponent<puffin::components::Image>("Image", entity, [](auto &component)
                                                 { ImGui::Text("%s", component.m_path.c_str()); });

        DrawComponent<puffin::components::Light>("Light", entity, [](auto &component)
                                                 { component.m_lightType->UpdateImGui(); });
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
