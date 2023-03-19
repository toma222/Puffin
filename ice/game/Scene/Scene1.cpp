
#include <puffin.h>
#include <string>

#include "Layer/GameLayer.h"

#include "Scene1.h"
#include "Scene2.h"

namespace game
{

    void Scene1::StartScene()
    {
        puffin::Entity *entity = GameLayer::m_currentContainer->AddEntity();

        entity->GetComponent<puffin::components::Transform>()->transformRect->w = 100;
        entity->GetComponent<puffin::components::Transform>()->transformRect->h = 100;

        entity->AddComponent<puffin::components::Image>("C:/Users/aidan/Desktop/Puffin-rendering/ice/game/Assets/Images/BuildingWall.bmp", 0);
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
