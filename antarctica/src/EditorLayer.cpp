
#include <puffin.h>

#include "EditorLayer.h"

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"

#include "tools/Gizmos.h"

#include <functional>

namespace puffin
{
    void EditorLayer::OnAttach()
    {
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

        m_activeScene = std::make_shared<Scene>();
        puffin::SceneSerializer serialize(m_activeScene);
        // C:/Users/Aidan/Documents/OtherUsslessProjects'/Puffin/Scene.json
        // C:/Users/100044352/Desktop/refactor/Puffin/Scene.json
        serialize.Deserialize("C:/Users/Aidan/Documents/OtherUsslessProjects'/Puffin/Scene.json");

        m_heirarchyPanel.AttachContext(m_activeScene);

        /* TESTING NEW COMPONENTS */
        Entity entity = m_activeScene->AddEntity("point light");
        entity.AddComponent<components::Light>(new PointLight(10, 10));
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
        m_activeScene->TickRuntime(0);
    }

    void EditorLayer::GizmosRender()
    {
        antarctica::Gizmos::StartGizmosRender();

        if (m_heirarchyPanel.GetSelectedEntity())
        {
            components::Transform &t = m_heirarchyPanel.GetSelectedEntity().GetComponent<components::Transform>();
            antarctica::Gizmos::PlaceSquare(t.m_rect->x, t.m_rect->y, t.m_rect->w, t.m_rect->h);
        }

        antarctica::Gizmos::EndGizmosRender();
    }

    void EditorLayer::ImGuiUpdate()
    {
        ImGui_ImplSDLRenderer_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

        ImGui::Begin("Workspace", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize);
        ImGuiID dockSpaceID = ImGui::GetID("Workspace");
        ImGui::DockSpace(dockSpaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
        ImGui::End();

        ImGui::ShowDemoWindow();

        ImGui::Begin("Viewport");
        ImGui::Image((ImTextureID)Graphics::Get().GetRenderTexture().get()->get(), ImVec2(192 * 5, 108 * 5));
        ImGui::End();

        m_heirarchyPanel.RenderImGui();

        ImGui::Render();
        ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
    }
}