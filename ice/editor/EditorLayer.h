
#pragma once

#include <puffin.h>

#include "Layer/GameLayer.h"

#include <fstream>
#include <iostream>
#include <filesystem>

ImVec4 ImGuiConvertHex(Uint32 hexValue)
{
    return ImVec4((double)((hexValue >> 16) & 0xFF) / 255,
                  (double)((hexValue >> 8) & 0xFF) / 255,
                  (double)((hexValue)&0xFF) / 255,
                  (double)255);
}

class GameLayer : public puffin::Layer
{
public:
    void OnAttach() override
    {
        GM_CORE_INFO("Start gui called in editorGUI");
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        //(void)io;

        ImGui::StyleColorsDark();

        ImGui::GetStyle().WindowRounding = 8; // <- Set this on init or use ImGui::PushStyleVar()
        ImGui::GetStyle().ChildRounding = 8;
        ImGui::GetStyle().FrameRounding = 8;
        ImGui::GetStyle().GrabRounding = 8;
        ImGui::GetStyle().PopupRounding = 8;
        ImGui::GetStyle().ScrollbarRounding = 16;

        /*

        auto &colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_WindowBg] = ImGuiConvertHex(1c1c16)

        // Headers
        colors[ImGuiCol_Header] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
        colors[ImGuiCol_HeaderHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
        colors[ImGuiCol_HeaderActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

        // Buttons
        colors[ImGuiCol_Button] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
        colors[ImGuiCol_ButtonHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
        colors[ImGuiCol_ButtonActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

        // Frame BG
        colors[ImGuiCol_FrameBg] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
        colors[ImGuiCol_FrameBgHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
        colors[ImGuiCol_FrameBgActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

        // Tabs
        colors[ImGuiCol_Tab] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
        colors[ImGuiCol_TabHovered] = ImVec4{0.38f, 0.3805f, 0.381f, 1.0f};
        colors[ImGuiCol_TabActive] = ImVec4{0.28f, 0.2805f, 0.281f, 1.0f};
        colors[ImGuiCol_TabUnfocused] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};

        // Title
        colors[ImGuiCol_TitleBg] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
        colors[ImGuiCol_TitleBgActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

        */

        ImGui_ImplSDL2_InitForSDLRenderer(puffin::Application::Get().GetWindow()->GetWindow()->GetWindow(), puffin::Graphics::Get().GetRenderer()->get());
        ImGui_ImplSDLRenderer_Init(puffin::Graphics::Get().GetRenderer()->get());

        // Load the icons
        m_GameObjectIcon = new puffin::render::SDLTexture(puffin::Graphics::Get().GetRenderer().get(),
                                                          "/ice/icons/GameObject.bmp", 50, 50);

        m_FileIcon = new puffin::render::SDLTexture(puffin::Graphics::Get().GetRenderer().get(),
                                                    "/ice/icons/Folder.bmp", 50, 50);

        // m_selectedEntity = nullptr;
    };

    void OnDetach() override{

    };

    void Update() override{

    };

    void Start() override{

    };

    void ImGuiUpdate() override
    {
        ImGui_ImplSDLRenderer_NewFrame();
        ImGui_ImplSDL2_NewFrame();

        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

        // Dockspace
        ImGui::Begin("Workspace", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize);
        ImGuiID dockSpaceID = ImGui::GetID("Workspace");
        ImGui::DockSpace(dockSpaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
        ImGui::End();

        ImGui::ShowDemoWindow();

        ImGui::Begin("Logging");

        ImGui::Text("TODO : this lol");

        ImGui::End();

        ImGui::Begin("Hierarchy");

        float x = ImGui::GetCursorPosX();

        for (puffin::Entity entity : game::GameLayer::GetCurrentScene().m_entities)
        {
            ImGuiTreeNodeFlags flags = ((m_selectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
            flags |= ImGuiTreeNodeFlags_SpanAvailWidth;

            puffin::components::Tag &tag = entity.GetComponent<puffin::components::Tag>();

            bool opened = ImGui::TreeNodeEx((void *)(uint64_t)(uint32_t)entity, flags, tag.m_Tag.c_str());

            if (ImGui::IsItemClicked())
            {
                m_selectedEntity = entity;
                printf("Selected");
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

        ImGui::Begin("Viewport");

        ImGui::Image((ImTextureID)puffin::Graphics::Get().GetRenderTexture().get()->get(), ImVec2(192 * 5, 108 * 5));

        ImGui::End();

        ImGui::Begin("Inspector");

        if (m_selectedEntity)
        {
            ImGui::Text("Entity selected");

            if (ImGui::TreeNode("Transform"))
            {
                puffin::components::Transform &transform = m_selectedEntity.GetComponent<puffin::components::Transform>();

                ImGui::InputInt("Position x", &transform.m_rect->x);
                ImGui::InputInt("Position y", &transform.m_rect->y);
                ImGui::InputInt("Width", &transform.m_rect->w);
                ImGui::InputInt("Height", &transform.m_rect->h);

                ImGui::TreePop();
            }

            if (ImGui::TreeNode("IDComponent"))
            {
                puffin::components::IDComponent &ID = m_selectedEntity.GetComponent<puffin::components::IDComponent>();

                ImGui::Text("%llu", (uint64_t)ID.m_ID);
                ImGui::TreePop();
            }

            if (ImGui::TreeNode("Tag"))
            {
                puffin::components::Tag &tag = m_selectedEntity.GetComponent<puffin::components::Tag>();

                ImGui::Text("%s", tag.m_Tag.c_str());
                ImGui::TreePop();
            }

            if (m_selectedEntity.HasComponent<puffin::components::Light>())
            {
                if (ImGui::TreeNode("Light"))
                {
                    puffin::components::Light &light = m_selectedEntity.GetComponent<puffin::components::Light>();

                    ImGui::ColorEdit3("Light Color", light.m_lightType->m_lightColor.m_color);

                    ImGui::TreePop();
                }
            }
        }

        ImGui::End();

        ImGui::Begin("Content Browser");

        static float padding = 16.0f;
        static float thumbnailSize = 128.0f;
        float cellSize = thumbnailSize + padding;

        float panelWidth = ImGui::GetContentRegionAvail().x;
        int columnCount = (int)(panelWidth / cellSize);
        if (columnCount < 1)
            columnCount = 1;

        ImGui::Columns(columnCount, 0, false);

        // ! will crash if the directory does not exist
        for (auto &directoryEntry : std::filesystem::directory_iterator("C:/Users/100044352/Desktop/New folder/Puffin/ice/game/Assets"))
        {

            const auto &path = directoryEntry.path();
            std::string filenameString = path.filename().string();

            ImGui::PushID(filenameString.c_str());
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
            ImGui::ImageButton((ImTextureID)m_FileIcon->get(), {100, 100});

            if (ImGui::BeginDragDropSource())
            {
                std::filesystem::path relativePath(path);
                const wchar_t *itemPath = relativePath.c_str();
                ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t));
                ImGui::EndDragDropSource();
            }

            ImGui::PopStyleColor();
            if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
            {
                if (directoryEntry.is_directory())
                    printf("Enter directory\n");
            }

            ImGui::TextWrapped(filenameString.c_str());

            ImGui::NextColumn();

            ImGui::PopID();
        }

        ImGui::Columns(1);

        ImGui::End();

        ImGui::Render();
        ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
    }

    static puffin::Scene *s_currentScene;

    puffin::render::SDLTexture *m_GameObjectIcon;
    puffin::render::SDLTexture *m_FileIcon;

    puffin::Entity m_selectedEntity;

    void SetCurrentScene()
    {
    }
};
