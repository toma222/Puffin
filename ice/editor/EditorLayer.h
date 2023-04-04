
#pragma once

#include <puffin.h>

#include "Layer/GameLayer.h"

#include <fstream>
#include <iostream>
#include <filesystem>

#define GRAPH_DATA 100

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
        // io.Fonts->AddFontFromFileTTF("C:/Users/Aidan/Documents/OtherUsslessProjects'/Puffin/resources/Editor/Fonts/static/FiraCode-Medium.ttf", 16);

        ImGui::StyleColorsDark();

        ImGui::GetStyle().WindowRounding = 0; // <- Set this on init or use ImGui::PushStyleVar()
        ImGui::GetStyle().ChildRounding = 0;
        ImGui::GetStyle().FrameRounding = 0;
        ImGui::GetStyle().GrabRounding = 0;
        ImGui::GetStyle().PopupRounding = 0;
        ImGui::GetStyle().ScrollbarRounding = 0;
        ImGui::GetStyle().TabRounding = 0;

        // Set up ImGui style with dark theme and pastel orange accents
        ImVec4 primaryColor1 = ImVec4(0.85f, 0.45f, 0.25f, 1.00f);                   // Orange
        ImVec4 primaryColor2 = ImVec4(0.85f / 1.5, 0.45f / 1.5, 0.25f / 1.5, 1.00f); // Orange
        ImVec4 primaryColor3 = ImVec4(0.85f / 2, 0.45f / 2, 0.25f / 2, 1.00f);       // Orange
        // ImVec4 primaryColor4 = ImVec4(0.85f / 2.5, 0.45f / 2.5, 0.25f / 2.5, 1.00f); // Orange

        ImVec4 secondaryColor = ImVec4(0.5f, 0.5f, 0.5f, 1.00f); // Light gray
        // ImVec4 secondaryColor2 = ImVec4(0.96f, 0.96f, 0.96f, 1.00f); // Light gray
        // ImVec4 secondaryColor3 = ImVec4(0.96f, 0.96f, 0.96f, 1.00f); // Light gray
        // ImVec4 secondaryColor4 = ImVec4(0.96f, 0.96f, 0.96f, 1.00f); // Light gray

        ImVec4 textColor = ImVec4(0.8f, 0.8f, 0.8f, 0.8f);

        ImVec4 bgColor1 = ImVec4(0.20f, 0.20f, 0.20f, 0.80f);                   // Dark gray
        ImVec4 bgColor2 = ImVec4(0.20f * 1.5, 0.20f * 1.5, 0.20f * 1.5, 0.80f); // light gray
        // ImVec4 bgColor3 = ImVec4(0.20f * 2, 0.20f * 2, 0.20f * 2, 0.80f);       // Lightest gray

        ImGuiStyle &style = ImGui::GetStyle();

        style.Colors[ImGuiCol_Text] = textColor;
        style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
        style.Colors[ImGuiCol_WindowBg] = bgColor1;
        style.Colors[ImGuiCol_ChildBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
        style.Colors[ImGuiCol_PopupBg] = bgColor2;
        style.Colors[ImGuiCol_Border] = secondaryColor;
        style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        style.Colors[ImGuiCol_FrameBg] = bgColor2;
        style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
        style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.45f, 0.45f, 0.45f, 1.00f);
        style.Colors[ImGuiCol_TitleBg] = primaryColor1;
        style.Colors[ImGuiCol_TitleBgActive] = primaryColor2;
        style.Colors[ImGuiCol_TitleBgCollapsed] = primaryColor3;
        style.Colors[ImGuiCol_MenuBarBg] = bgColor1;
        style.Colors[ImGuiCol_ScrollbarBg] = bgColor2;
        style.Colors[ImGuiCol_ScrollbarGrab] = secondaryColor;
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
        style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
        style.Colors[ImGuiCol_CheckMark] = primaryColor1;
        style.Colors[ImGuiCol_SliderGrab] = secondaryColor;
        style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.55f, 0.55f, 0.55f, 1.00f);
        style.Colors[ImGuiCol_Button] = primaryColor1;
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.80f, 0.50f, 0.30f, 1.00f);
        style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.90f, 0.60f, 0.40f, 1.00f);
        style.Colors[ImGuiCol_Header] = primaryColor1;
        style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.80f, 0.50f, 0.30f, 1.00f);
        style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.90f, 0.60f, 0.40f, 1.00f);
        style.Colors[ImGuiCol_Separator] = secondaryColor;
        style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
        style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
        style.Colors[ImGuiCol_ResizeGrip] = secondaryColor;
        style.Colors[ImGuiCol_ResizeGripHovered] = primaryColor2;
        style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.90f, 0.60f, 0.40f, 1.00f);
        style.Colors[ImGuiCol_Tab] = primaryColor1;
        style.Colors[ImGuiCol_TabHovered] = primaryColor3;
        style.Colors[ImGuiCol_TabActive] = primaryColor3;
        style.Colors[ImGuiCol_TabUnfocused] = primaryColor2;
        style.Colors[ImGuiCol_TabUnfocusedActive] = primaryColor2;
        style.Colors[ImGuiCol_DockingPreview] = primaryColor1;
        style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.80f);
        style.Colors[ImGuiCol_PlotLines] = primaryColor2;
        style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.50f, 1.00f);
        style.Colors[ImGuiCol_PlotHistogram] = primaryColor1;
        style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.90f, 0.70f, 0.50f, 1.00f);
        style.Colors[ImGuiCol_TextSelectedBg] = primaryColor2;
        style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.90f, 0.60f, 0.40f, 1.00f);
        style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.80f, 0.50f, 0.30f, 1.00f);
        style.Colors[ImGuiCol_NavWindowingHighlight] = primaryColor2;
        style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.80f);

        ImGui_ImplSDL2_InitForSDLRenderer(puffin::Application::Get().GetWindow()->GetWindow()->GetWindow(), puffin::Graphics::Get().GetRenderer()->get());
        ImGui_ImplSDLRenderer_Init(puffin::Graphics::Get().GetRenderer()->get());

        // Load the icons
        m_GameObjectIcon = new puffin::render::SDLTexture(puffin::Graphics::Get().GetRenderer().get(),
                                                          "/ice/icons/GameObject.bmp", 50, 50);

        m_FileIcon = new puffin::render::SDLTexture(puffin::Graphics::Get().GetRenderer().get(),
                                                    "/ice/icons/Folder.bmp", 50, 50);

        m_viewportScale = 5;

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

        ImGui::Begin("Debug");

        ImGui::Text("TODO : this lol");

        // FPS Historgram

        float FrameFPS = 1.0f / ImGui::GetIO().DeltaTime;
        float RollingAverage = ImGui::GetIO().Framerate;
        double effectsAndLighting = (puffin::Graphics::Get().m_stats.m_postTime.m_savedTime / 1000);
        double renderCycle = (puffin::Graphics::Get().m_stats.m_openCloseGraphicsTime.m_savedTime / 1000);

        ImGui::Text("Time Data");
        if (ImGui::BeginTable("table", 3, ImGuiTableFlags_Borders))
        {
            ImGui::TableNextColumn();
            ImGui::Text("Name");
            ImGui::TableNextColumn();
            ImGui::Text("Status");
            ImGui::TableNextColumn();
            ImGui::Text("Time");

            ImGui::TableNextColumn();
            ImGui::Text("Per Frame FPS");
            ImGui::TableNextColumn();
            if (FrameFPS > 55)
                ImGui::TextColored(ImVec4(0, 255, 0, 255), "Good");
            else if (FrameFPS > 30)
                ImGui::TextColored(ImVec4(255, 0, 255, 255), "Poor");
            else
                ImGui::TextColored(ImVec4(255, 0, 0, 255), "Bad");
            ImGui::TableNextColumn();
            ImGui::Text("%f", FrameFPS);

            ImGui::TableNextColumn();
            ImGui::Text("Rolling Average FPS");
            ImGui::TableNextColumn();
            if (RollingAverage > 55)
                ImGui::TextColored(ImVec4(0, 255, 0, 255), "Good");
            else if (RollingAverage > 30)
                ImGui::TextColored(ImVec4(255, 0, 255, 255), "Poor");
            else
                ImGui::TextColored(ImVec4(255, 0, 0, 255), "Bad");
            ImGui::TableNextColumn();
            ImGui::Text("%f", RollingAverage);

            ImGui::TableNextColumn();
            ImGui::Text("Effects And Lighting");
            ImGui::TableNextColumn();
            if (effectsAndLighting > 0 && effectsAndLighting < 6)
                ImGui::TextColored(ImVec4(0, 255, 0, 255), "Good");
            if (effectsAndLighting >= 6 && effectsAndLighting < 10)
                ImGui::TextColored(ImVec4(255, 0, 255, 255), "Poor");
            if (effectsAndLighting >= 14)
                ImGui::TextColored(ImVec4(255, 0, 0, 255), "Bad");
            ImGui::TableNextColumn();
            ImGui::Text("%f", effectsAndLighting);

            ImGui::TableNextColumn();
            ImGui::Text("Render Cycle");
            ImGui::TableNextColumn();
            if (renderCycle > 0 && renderCycle < 17)
                ImGui::TextColored(ImVec4(0, 255, 0, 255), "Good");
            if (renderCycle >= 17 && renderCycle < 21)
                ImGui::TextColored(ImVec4(255, 0, 255, 255), "Poor");
            if (renderCycle >= 21)
                ImGui::TextColored(ImVec4(255, 0, 0, 255), "Bad");

            ImGui::TableNextColumn();
            ImGui::Text("%f", renderCycle);

            ImGui::EndTable();
        }

        ImGui::End();

        ImGui::Begin("Hierarchy");

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

        ImGui::Image((ImTextureID)puffin::Graphics::Get().GetRenderTexture().get()->get(), ImVec2(192 * m_viewportScale, 108 * m_viewportScale));

        if (ImGui::BeginPopupContextItem("Viewport settings"))
        {
            ImGui::SliderFloat("Viewport size", &m_viewportScale, 1, 12);
            ImGui::EndPopup();
        }

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

            if (m_selectedEntity.HasComponent<puffin::components::BoxCollider>())
            {
                if (ImGui::TreeNode("Box Collider"))
                {
                    // puffin::components::BoxCollider &light = m_selectedEntity.GetComponent<puffin::components::BoxCollider>();

                    ImGui::TreePop();
                }
            }

            if (m_selectedEntity.HasComponent<puffin::components::Rigidbody2D>())
            {
                if (ImGui::TreeNode("Rigidbody"))
                {
                    puffin::components::Rigidbody2D &rb = m_selectedEntity.GetComponent<puffin::components::Rigidbody2D>();

                    ImGui::InputFloat("mass", &rb.m_mass);
                    ImGui::InputFloat("drag", &rb.m_drag);

                    ImGui::Spacing();

                    ImGui::Checkbox("gravity", &rb.m_gravity);
                    ImGui::Checkbox("simulated", &rb.m_simulated);

                    ImGui::Spacing();

                    ImGui::InputFloat("angular velocity", &rb.m_angularVelocity);

                    ImGui::Text("Speed %f", rb.m_speed);

                    ImGui::Text("Velocity x:%f  y:%f", rb.m_velocity.x, rb.m_velocity.y);
                    ImGui::Text("Forces x:%f  y:%f", rb.m_forces.x, rb.m_forces.y);

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
        /*
        for (auto &directoryEntry : std::filesystem::directory_iterator("C:/Users/Aidan/Documents/OtherUsslessProjects'/Puffin/ice/game/Assets"))
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
        */

        ImGui::End();

        ImGui::Begin("Post Controll Panel");

        for (auto effect : puffin::Graphics::Get().m_postBuffer)
        {
            effect->ImGuiUpdate();
        }

        ImGui::End();

        ImGui::Render();
        ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
    }

    static puffin::Scene *s_currentScene;

    puffin::render::SDLTexture *m_GameObjectIcon;
    puffin::render::SDLTexture *m_FileIcon;
    puffin::Entity m_selectedEntity;

    float m_viewportScale;

    void SetCurrentScene()
    {
    }
};
