
#pragma once

#include <puffin.h>

#include "Layer/GameLayer.h"

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

        ImGui_ImplSDL2_InitForSDLRenderer(puffin::Application::Get().GetWindow()->GetWindow()->GetWindow(), puffin::Graphics::Get().GetRenderer()->get());
        ImGui_ImplSDLRenderer_Init(puffin::Graphics::Get().GetRenderer()->get());

        // Load the icons
        m_GameObjectIcon = new puffin::render::SDLTexture (puffin::Graphics::Get().GetRenderer().get(),
         "C:/Users/100044352/Desktop/Puffin-scripting/ice/editor/Assets/GameObjectSprite.bmp", 50, 50);

        m_selectedEntity = nullptr;
    };

    void OnDetach() override
    {

    };

    void Update() override
    {

    };

    void Start() override
    {

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
            // TODO fix the id's on this
            if(ImGui::InvisibleButton("some id", {300,20}))
            {
                printf("Adding some entity");
                m_selectedEntity = &entity;
            }

            puffin::components::Tag &tag = entity.GetComponent<puffin::components::Tag>();

            ImGui::SameLine(x);
            ImGui::Image((ImTextureID)m_GameObjectIcon->get(), ImVec2(20,20));
            ImGui::SameLine();
            ImGui::Text("%s", tag.m_Tag.c_str());
        }

        ImGui::End();

        ImGui::Begin("Viewport");

        ImGui::Image((ImTextureID)puffin::Graphics::Get().GetRenderTexture().get()->get(), ImVec2(192 * 5,108 * 5));

        ImGui::End();

        ImGui::Begin("Inspector");

        if(m_selectedEntity != nullptr)
        {
            ImGui::Text("Entity selected");
            // Gui for Transform
            ImGui::Text("Transform Component");
            puffin::components::Transform &transform = m_selectedEntity->GetComponent<puffin::components::Transform>();

            ImGui::InputInt("Position x", &transform.m_rect->x);
            ImGui::InputInt("Position y", &transform.m_rect->y);
            ImGui::InputInt("Width", &transform.m_rect->w);
            ImGui::InputInt("Height", &transform.m_rect->h);

            // Gui for ID
            ImGui::Text("ID Component");
            puffin::components::IDComponent &ID = m_selectedEntity->GetComponent<puffin::components::IDComponent>();

            ImGui::Text("%lu", ID.m_ID);

            // Gui for tag component
            ImGui::Text("Tag Component");
            puffin::components::Tag &tag = m_selectedEntity->GetComponent<puffin::components::Tag>();

            ImGui::Text("%s", tag.m_Tag.c_str());
        }

        ImGui::End();

        ImGui::Render();
        ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
    }

    static puffin::Scene *s_currentScene;

    puffin::render::SDLTexture *m_GameObjectIcon;
    puffin::Entity *m_selectedEntity;

    void SetCurrentScene()
    {
    }
};
