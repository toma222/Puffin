
#include <puffin.h>
#include <string>

#include "Layer/GameLayer.h"

#include "Scene1.h"
#include "Scene2.h"

namespace game
{

    void Scene1::StartScene()
    {
        PN_PROFILE_FUNCTION("StartScene");
        puffin::Entity *entity = GameLayer::s_currentContainer->AddEntity();

        entity->GetComponent<puffin::components::Transform>()->transformRect->w = 600;
        entity->GetComponent<puffin::components::Transform>()->transformRect->h = 600;

        entity->AddComponent<puffin::components::Image>("C:/Users/Aidan/Documents/programming/EngineInADay - Copy/ice/game/Assets/Images/download.bmp", 0);
        entity->AddComponent<puffin::components::Script>("C:/Users/Aidan/Documents/OtherUsslessProjects'/Puffin/ice/game/Assets/Scripts/lua/script.lua");
        // context = new puffin::LuaContext("C:/Users/Aidan/Documents/OtherUsslessProjects'/Puffin/ice/script.lua");
    }

    void Scene1::UpdateScene()
    {
    }

    void Scene1::ClearScene()
    {
        GM_CORE_TRACE("Clearing scene");

        GameLayer::s_currentContainer->ClearScene();
        puffin::Application::Get().GetGraphics()->ClearTextureRenderQue();
    }

    void Scene1::DestroyScene()
    {
    }

    std::string Scene1::s_sceneName = "Scene 1";
} // namespace game
