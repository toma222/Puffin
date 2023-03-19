
#include "Scene2.h"

#include "Layer/GameLayer.h"

namespace game
{
    void Scene2::StartScene()
    {
        puffin::Entity *entity = GameLayer::m_currentContainer->AddEntity();

        entity->GetComponent<puffin::components::Transform>()->transformRect->w = 100;
        entity->GetComponent<puffin::components::Transform>()->transformRect->h = 100;

        entity->AddComponent<puffin::components::Image>("C:/Users/aidan/Desktop/Puffin-main/ice/game/Assets/Images/TreeBuilding.bmp", 0);
    }

    void Scene2::UpdateScene()
    {
    }

    void Scene2::ClearScene()
    {
        GM_CORE_TRACE("Clearing scene");

        GameLayer::m_currentContainer->ClearScene();
        puffin::Application::Get().GetGraphics()->ClearTextureRenderQue();
    }

    void Scene2::DestroyScene()
    {
    }

    std::string Scene2::s_sceneName = "Scene 2";
} // namespace game
