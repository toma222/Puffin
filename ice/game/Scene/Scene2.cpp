
#include "Scene2.h"

#include "Layer/GameLayer.h"

namespace game
{
    void Scene2::StartScene()
    {
        PN_PROFILE_FUNCTION("StartScene");
        puffin::Entity *entity = GameLayer::s_currentContainer->AddEntity();

        entity->GetComponent<puffin::components::Transform>()->transformRect->w = 500;
        entity->GetComponent<puffin::components::Transform>()->transformRect->h = 500;

        entity->AddComponent<puffin::components::Image>("C:/Users/Aidan/Documents/programming/EngineInADay - Copy/ice/game/Assets/Images/TreeBuilding.bmp", 0);
        // entity->AddComponent<puffin::components::Script>("C:/Users/Aidan/Documents/OtherUsslessProjects'/Puffin/ice/game/Assets/Scripts/lua/script.lua");
    }

    void Scene2::UpdateScene()
    {
    }

    void Scene2::ClearScene()
    {
        GM_CORE_TRACE("Clearing scene");

        GameLayer::s_currentContainer->ClearScene();
        puffin::Application::Get().GetGraphics()->ClearTextureRenderQue();
    }

    void Scene2::DestroyScene()
    {
    }

    std::string Scene2::s_sceneName = "Scene 2";
} // namespace game
