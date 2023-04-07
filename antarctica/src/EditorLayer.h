#pragma once

#include <puffin.h>

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"

#include "panels/Heirarchy.h"
#include "panels/GizmosPanel.h"

namespace puffin
{
    class EditorLayer : public Layer
    {
    public:
        void LoadNewScene(std::string path);

    public:
        void OnAttach() override;
        void OnDetach() override;
        void Update() override;
        void ImGuiUpdate() override;
        void GizmosRender() override;
        void Start() override;

    private:
        std::shared_ptr<Scene> m_activeScene;
        std::string m_currentScenePath;

        antarctica::Heirarchy m_heirarchyPanel;
        antarctica::GizmosPanel m_gizmosPanel;
    };

} // namespace puffin
