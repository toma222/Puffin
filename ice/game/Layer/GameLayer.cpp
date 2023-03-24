
#include <puffin.h>

#include "GameLayer.h"

namespace game
{
    puffin::Scene *GameLayer::s_currentScene = nullptr;
    // puffin::Container *GameLayer::m_currentContainer = nullptr;

    void GameLayer::OnAttach()
    {
        GM_CORE_INFO("Attach called for game layer");
        s_currentScene = new puffin::Scene();

        puffin::Entity e = s_currentScene->AddEntity("jeff");
        e.AddComponent<puffin::components::Image>("C:/Users/aidan/Desktop/Puffin-rendering/ice/game/Assets/Images/BuildingWall.bmp");
        e.AddComponent<puffin::components::Light>(new puffin::PointLight(5, 5));
    }

    void GameLayer::OnDetach()
    {
        GM_CORE_INFO("Detach called for game layer");
    }

    void GameLayer::Start()
    {
    }

    int tick = 0;
    bool swap = false;
    bool scene1 = true;

    void GameLayer::Update()
    {
        s_currentScene->TickRuntime(0.0f);
    }
}