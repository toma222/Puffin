
#include <puffin.h>

#include "EditorLayer.h"

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"
#include "ImGuiFileDialog/ImGuiFileDialog.h"

#include "tools/Gizmos.h"

#include <functional>

namespace puffin
{
    void EditorLayer::OnAttach()
    {
        m_sceneState = EDITING;

        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        ImGui::StyleColorsDark();
        ImGui::GetStyle().WindowRounding = 0; // <- Set this on init or use ImGui::PushStyleVar()
        ImGui::GetStyle().ChildRounding = 0;
        ImGui::GetStyle().FrameRounding = 0;
        ImGui::GetStyle().GrabRounding = 0;
        ImGui::GetStyle().PopupRounding = 0;
        ImGui::GetStyle().ScrollbarRounding = 0;
        ImGui::GetStyle().TabRounding = 0;

        ImVec4 primaryColor1 = ImVec4(0.85f, 0.45f, 0.25f, 1.00f);                   // Orange
        ImVec4 primaryColor2 = ImVec4(0.85f / 1.5, 0.45f / 1.5, 0.25f / 1.5, 1.00f); // Orange
        ImVec4 primaryColor3 = ImVec4(0.85f / 2, 0.45f / 2, 0.25f / 2, 1.00f);       // Orange
        ImVec4 secondaryColor = ImVec4(0.5f, 0.5f, 0.5f, 1.00f);                     // Light gray
        ImVec4 textColor = ImVec4(0.8f, 0.8f, 0.8f, 0.8f);
        ImVec4 bgColor1 = ImVec4(0.20f, 0.20f, 0.20f, 0.80f);                   // Dark gray
        ImVec4 bgColor2 = ImVec4(0.20f * 1.5, 0.20f * 1.5, 0.20f * 1.5, 0.80f); // light gray
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

        m_gameObjectIcon = std::make_shared<puffin::render::SDLTexture>(puffin::Graphics::Get().GetRenderer().get(), "/antarctica/resources/icons/GameObject.bmp", 16, 16);
        m_pauseSceneIcon = std::make_shared<puffin::render::SDLTexture>(puffin::Graphics::Get().GetRenderer().get(), "/antarctica/resources/icons/PauseSceneButton.bmp", 16, 16);
        m_playSceneIcon = std::make_shared<puffin::render::SDLTexture>(puffin::Graphics::Get().GetRenderer().get(), "/antarctica/resources/icons/PlaySceneButton.bmp", 8, 8);

        m_editorScene = std::make_shared<Scene>();

        m_activeScene = m_editorScene;

        // C:/Users/Aidan/Documents/OtherUsslessProjects'/Puffin/Scene.json
        // C:/Users/100044352/Desktop/refactor/Puffin/Scene.json
        // C:/Users.Aidan/Desktop/github/Puffin/Scene.json

        puffin::LuaScripting::InitLuaScripting();

        // std::shared_ptr<puffin::Scene> newScene = std::make_shared<puffin::Scene>();
        puffin::SceneSerializer serialize(m_editorScene);
        if (serialize.Deserialize("C:/Users/Aidan/Desktop/Github/Puffin/Scene copy.json"))
        {
            Entity e = m_editorScene->AddEntity("Physics");
            e.AddComponent<components::Image>("/ice/assets/Images/square.bmp");
            e.AddComponent<components::RigidBody2D>(5);
            m_editorScene->m_name = "editor";

            m_activeScene = m_editorScene;

            m_heirarchyPanel.AttachContext(m_activeScene);
        }
    }

    void EditorLayer::OnDetach()
    {
        GM_CORE_INFO("Detach called for game layer");
    }

    void EditorLayer::Start()
    {
    }

    void EditorLayer::Update()
    {
        switch (m_sceneState)
        {
        case SCENE_STATE::EDITING:
            m_activeScene->TickEditor(0);
            break;

        case SCENE_STATE::PLAYING:
            m_activeScene->TickRuntime(0);
            m_activeScene->TickPhysicsSimulation(0.001);
            break;

        default:
            break;
        }
    }

    void EditorLayer::GizmosRender()
    {
        antarctica::Gizmos::StartGizmosRender();

        if (m_heirarchyPanel.GetSelectedEntity())
            m_gizmosPanel.RenderEntityGizmos(m_heirarchyPanel.GetSelectedEntity());

        antarctica::Gizmos::EndGizmosRender();
    }

    void EditorLayer::LoadNewScene(std::string path)
    {
        if (path != "NONE")
        {
            m_activeScene = std::make_shared<Scene>();

            puffin::SceneSerializer serialize(m_activeScene);
            serialize.Deserialize(path.c_str());

            m_heirarchyPanel.AttachContext(m_activeScene);
        }
        else
        {
            m_activeScene = std::make_shared<Scene>();

            m_heirarchyPanel.AttachContext(m_activeScene);
        }
    }

    void EditorLayer::ImGuiUpdate()
    {
        ImGui_ImplSDLRenderer_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("Workspace", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_MenuBar);
        ImGui::PopStyleVar();

        ImGuiID dockSpaceID = ImGui::GetID("Workspace");
        ImGui::DockSpace(dockSpaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Open Project...", "Ctrl+O"))
                {
                    ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".json", ".");
                }

                ImGui::Separator();

                if (ImGui::MenuItem("New Scene", "Ctrl+N"))
                {
                    LoadNewScene("NONE");
                }

                if (ImGui::MenuItem("Save Scene", "Ctrl+S"))
                {
                    puffin::SceneSerializer serialize(m_activeScene);
                    serialize.SerializeScene(m_currentScenePath.c_str());
                }

                if (ImGui::MenuItem("Save Scene As...", "Ctrl+Shift+S"))
                    GM_CORE_FATAL("Save As Scene not implemented yet");

                ImGui::Separator();

                if (ImGui::MenuItem("Exit"))
                    puffin::Application::Get().Exit();

                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();

                LoadNewScene(filePathName);
            }

            ImGuiFileDialog::Instance()->Close();
        }

        ImGui::End();

        ImGui::ShowDemoWindow();

        ImGui::Begin("Viewport");
        ImGui::Image((ImTextureID)Graphics::Get().GetRenderTexture().get()->get(), ImVec2(192 * 5, 108 * 5));
        ImGui::End();

        m_heirarchyPanel.RenderImGui();
        m_gizmosPanel.RenderGizmosPanel();

        RenderSceneToolbar();

        ImGui::Render();
        ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
    }

    void EditorLayer::RenderSceneToolbar()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 12));
        ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0, 0));
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        auto &colors = ImGui::GetStyle().Colors;
        const auto &buttonHovered = colors[ImGuiCol_ButtonHovered];
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(buttonHovered.x, buttonHovered.y, buttonHovered.z, 0.5f));
        const auto &buttonActive = colors[ImGuiCol_ButtonActive];
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(buttonActive.x, buttonActive.y, buttonActive.z, 0.5f));

        ImGui::Begin("##toolbar", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

        float size = ImGui::GetWindowHeight() - 4.0f;
        ImGui::SetCursorPosX((ImGui::GetWindowContentRegionMax().x * 0.5f) - (size * 0.5f));

        if (m_sceneState == PLAYING)
        {
            if (ImGui::ImageButton(m_pauseSceneIcon->get(), ImVec2(size - 25, size - 25)))
            {
                m_sceneState = EDITING;
                SetSceneState(EDITING);
            }
        }
        else if (m_sceneState == EDITING)
        {
            if (ImGui::ImageButton(m_playSceneIcon->get(), ImVec2(size - 25, size - 25)))
            {
                m_sceneState = PLAYING;
                SetSceneState(PLAYING);
            }
        }

        ImGui::PopStyleVar(2);
        ImGui::PopStyleColor(3);
        ImGui::End();
    }

    void EditorLayer::SetSceneState(SCENE_STATE state)
    {
        switch (state)
        {
        case EditorLayer::PLAYING:
            printf("playing scene\n");
            m_activeScene = Scene::Copy(m_editorScene);
            m_activeScene->m_name = "Running";
            m_heirarchyPanel.AttachContext(m_activeScene);
            break;

        case EditorLayer::EDITING:
            printf("going back to editing\n");
            m_activeScene = m_editorScene;
            m_heirarchyPanel.AttachContext(m_activeScene);
            break;

        default:
            break;
        }
    }
}