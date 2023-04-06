#pragma once

#include <puffin.h>

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"

// ! this wont go into a cpp file without throwing a fit :(
namespace puffin
{
    class EditorLayer : public Layer
    {
    public:
        void OnAttach() override
        {
            ImGui::CreateContext();
            ImGui_ImplSDL2_InitForSDLRenderer(puffin::Application::Get().GetWindow()->GetWindow()->GetWindow(), puffin::Graphics::Get().GetRenderer()->get());
            ImGui_ImplSDLRenderer_Init(puffin::Graphics::Get().GetRenderer()->get());

            m_activeScene = std::make_shared<Scene>();

            puffin::SceneSerializer serialize(m_activeScene);
            serialize.Deserialize("C:/Users/Aidan/Documents/OtherUsslessProjects'/Puffin/Scene.json");
        };

        void OnDetach() override{

        };

        void Update() override{

        };

        void Start() override{

        };

    private:
        std::shared_ptr<Scene> m_activeScene;

        // * Implement an editor scene
        // std::shared_ptr<Scene> m_editorScene;
    };

} // namespace game
