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
        enum SCENE_STATE
        {
            PLAYING,
            EDITING,
            PAUSED
        };

        void LoadNewScene(std::string path);
        void StartScene();
        void SetSceneState(SCENE_STATE state);
        void RenderSceneToolbar();

    public:
        void OnAttach() override;
        void OnDetach() override;
        void Update() override;
        void ImGuiUpdate() override;
        void GizmosRender() override;
        void Start() override;

    private:
        std::shared_ptr<Scene> m_activeScene;
        std::shared_ptr<Scene> m_editorScene;

        std::string m_currentScenePath;

        antarctica::Heirarchy m_heirarchyPanel;
        antarctica::GizmosPanel m_gizmosPanel;

        SCENE_STATE m_sceneState;

    private:
        std::shared_ptr<puffin::render::SDLTexture> m_playSceneIcon;
        std::shared_ptr<puffin::render::SDLTexture> m_pauseSceneIcon;
        std::shared_ptr<puffin::render::SDLTexture> m_gameObjectIcon;
    };

} // namespace puffin
