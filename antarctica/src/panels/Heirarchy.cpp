
#include "Heirarchy.h"

#include "puffin.h"

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"
#include <imgui/imgui_internal.h>

#include <memory>

namespace puffin
{
    void Heirarchy::AttachContext(std::shared_ptr<puffin::Scene> sceneRef)
    {
        m_sceneRef = sceneRef;
    }

    template <typename T, typename UIFunction>
    static void DrawComponent(const std::string &name, Entity entity, UIFunction uiFunction)
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

    void Heirarchy::RenderImGui()
    {
        ImGui::Begin("Heirarchy");

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

        ImGui::End();

        ImGui::Begin("Properties");

        if (m_selectedEntity)
        {
            RenderSelectedEntityComponents(m_selectedEntity);
        }

        ImGui::End();
    }

    void Heirarchy::RenderSelectedEntityComponents(Entity entity)
    {
        ImGui::Text("%s", entity.GetName().c_str());
        ImGui::Text("%lld", (uint64_t)entity.GetUUID());

        DrawComponent<components::Transform>("Transform", entity, [](auto &component)
                                             { 
            ImGui::InputInt("Position x", &component.m_rect->x);
            ImGui::InputInt("Position y", &component.m_rect->y);
            ImGui::InputInt("Width", &component.m_rect->w);
            ImGui::InputInt("Height", &component.m_rect->h); });

        DrawComponent<components::Image>("Image", entity, [](auto &component)
                                         { ImGui::Text("%s", component.m_path.c_str()); });
    }
} // namespace antarctica
