
#include <puffin.h>

#include "GameLayer.h"

#include "../Scene/Scene1.h"
#include "../Scene/Scene2.h"

namespace game
{
    puffin::Scene *GameLayer::s_currentScene = nullptr;
    puffin::Container *GameLayer::m_currentContainer = nullptr;

    void GameLayer::OnAttach()
    {
        GM_CORE_INFO("Attach called for game layer");

        m_currentContainer = new puffin::Container(10);

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

    void GameLayer::Update()
    {
        s_currentScene->UpdateScene();

        if (tick < 100)
        {
            tick++;
        }
        else
        {
            if (swap == false)
            {
                swap = true;
                GM_CORE_INFO("Swapping scenes");
                SetCurrentScene<Scene2>();
            }
        }
    }

} // namespace game
