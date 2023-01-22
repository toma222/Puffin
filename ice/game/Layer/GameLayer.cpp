
#include <puffin.h>

#include "GameLayer.h"

#include "../Scene/Scene1.h"
#include "../Scene/Scene2.h"

namespace game
{
    puffin::Scene *GameLayer::s_currentScene = nullptr;
    puffin::Container *GameLayer::s_currentContainer = nullptr;

    void GameLayer::OnAttach()
    {
        GM_CORE_INFO("Attach called for game layer");

        s_currentContainer = new puffin::Container(10);

        SetCurrentScene<Scene1>();
        s_currentScene->StartScene();
    }

    void GameLayer::OnDetach()
    {
        GM_CORE_INFO("Detach called for game layer");
        s_currentScene->DestroyScene();
    }

    void GameLayer::Start()
    {
    }

    int tick = 0;
    bool swap = false;
    bool scene1 = true;

    void GameLayer::Update()
    {
        s_currentScene->UpdateScene();
        s_currentContainer->UpdateComponents();

        if (tick < 300)
        {
            tick++;
        }
        else
        {
            tick = 0;

            if (scene1)
            {
                GM_CORE_INFO("Swapping scenes");
                SetCurrentScene<Scene2>();
                scene1 = false;
            }
            else
            {
                GM_CORE_INFO("Swapping scenes");
                SetCurrentScene<Scene1>();
                scene1 = true;
            }
        }
    }

} // namespace game