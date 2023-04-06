#pragma once

#include <puffin.h>

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"

#include "panels/Heirarchy.h"

namespace puffin
{
    class EditorLayer : public Layer
    {
    public:
        void OnAttach() override;
        void OnDetach() override;
        void Update() override;
        void ImGuiUpdate() override;
        void Start() override;

    private:
        std::shared_ptr<Scene> m_activeScene;

        puffin::Heirarchy m_heirarchyPanel;
    };

} // namespace puffin
