
#include "Scene2.h"

#include "Layer/GameLayer.h"

namespace game
{
    void Scene2::StartScene()
    {
        if (GameLayer::m_currentContainer == nullptr)
            printf("been deleted :(\n");

        puffin::Entity *entity = GameLayer::m_currentContainer->AddEntity();
        entity->AddComponent<puffin::components::Image>("C:/Users/Aidan/Documents/programming/EngineInADay - Copy/ice/game/Assets/Images/TreeBuilding.bmp", 0);
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
