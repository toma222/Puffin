
#pragma once

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"

#include <vector>
#include <puffin.h>

#include "EditorColors.h"

#include "../game/Layer/GameLayer.h"

bool my_tool_active = true;

namespace editor
{
    class editorGUI
    {
    private:
        float m_frameRateSamples[500];
        int m_sampleCount;

    public:
        void UpdateGUI(puffin::render::SDLTexture *renderTexture)
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

            // The viewport
            ImGui::Begin("Viewport");
            ImGui::Image((ImTextureID)(renderTexture->get()),
                         {16 * 70,
                          9 * 70});

            ImGui::End();

            ImGui::Begin("Scene Debug");

            ImGui::BeginChild("Scene Data", ImVec2(250, 100), true);

            ImGui::Text("Scene Data");
            // ImGui::Text("   name : %s", game::GameLayer::s_currentScene->GetName().c_str());
            ImGui::Text("Container");
            // ImGui::Text("   entities : %i", game::GameLayer::m_currentContainer->m_IDCounter);

            ImGui::EndChild();

            ImGui::End();

            ImGui::Begin("Entities");

            // game::GameLayer::m_currentContainer->RenderImGuiComponents();

            ImGui::End();

            ImGui::Begin("Runtime Stats");

            ImGui::TextColored({255, 255, 255, 255}, "Runtime");
            ImGui::PlotLines("Frame rate", m_frameRateSamples, 500, 0, NULL, 0, 80, {ImGui::GetWindowSize().x - 200, 100});

            if (m_sampleCount < 500)
            {
                m_frameRateSamples[m_sampleCount] = ImGui::GetIO().Framerate;
                m_sampleCount++;
            }
            else
            {
                m_sampleCount = 0;
            }

            ImGui::End();

            ImGui::ShowDemoWindow();

            ImGui::Render();
            ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
        }

        void StartGUI(puffin::render::SDLWindow *window, puffin::render::SDLRenderer *renderer)
        {
            GM_CORE_INFO("Start gui called in editorGUI");
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO &io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
            //(void)io;

            ImGui::StyleColorsDark();
            m_sampleCount = 0;

            ColorImGUI();

            ImGui::GetStyle().WindowRounding = 8; // <- Set this on init or use ImGui::PushStyleVar()
            ImGui::GetStyle().ChildRounding = 8;
            ImGui::GetStyle().FrameRounding = 8;
            ImGui::GetStyle().GrabRounding = 8;
            ImGui::GetStyle().PopupRounding = 8;
            ImGui::GetStyle().ScrollbarRounding = 16;

            ImGui_ImplSDL2_InitForSDLRenderer(window->GetWindow(), renderer->get());
            ImGui_ImplSDLRenderer_Init(renderer->get());
        };
    };
} // namespace editor