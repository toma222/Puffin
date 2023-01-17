
#include <puffin.h>
#include <string>

#include "Layer/GameLayer.h"

#include "Scene1.h"
#include "Scene2.h"

#include "Assets/Scripts/MoveSprite.h"

namespace game
{

    void Scene1::StartScene()
    {
        puffin::Entity *entity = GameLayer::m_currentContainer->AddEntity();

        entity->GetComponent<puffin::components::Transform>()->transformRect->w = 600;
        entity->GetComponent<puffin::components::Transform>()->transformRect->h = 600;

        entity->AddComponent<puffin::components::Image>("C:/Users/100044352/Desktop/engine/clo/ice/game/Assets/Images/TreeBuilding.bmp", 0);
        entity->AddComponent<MoveSprite>();
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
