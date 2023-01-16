
#include <puffin.h>
#include <string>

#include "Layer/GameLayer.h"

#include "Scene1.h"

namespace game
{

    void Scene1::StartScene()
    {
        puffin::Entity *entity = GameLayer::m_currentContainer->AddEntity();
        entity->AddComponent<puffin::components::Image>("C:/Users/Aidan/Documents/programming/EngineInADay - Copy/ice/game/Assets/Images/download.bmp", 0);
    }

    void Scene1::UpdateScene()
    {
    }

    void Scene1::ClearScene()
    {
        GM_CORE_TRACE("Clearing scene");
        GameLayer::m_currentContainer->ClearScene();
        puffin::Application::Get().GetGraphics()->ClearTextureRenderQue();
    }

    void Scene1::DestroyScene()
    {
    }

    std::string Scene1::s_sceneName = "Scene 1";
} // namespace game
