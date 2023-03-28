
#include <puffin.h>

#include "GameLayer.h"
#include "Assets/NativeScriptIncludes.h"

#include <functional>

namespace game
{
    puffin::Scene *GameLayer::s_currentScene = nullptr;
    // puffin::Container *GameLayer::m_currentContainer = nullptr;

    void GameLayer::OnAttach()
    {
        GM_CORE_INFO("Attach called for game layer");
        s_currentScene = new puffin::Scene();

        puffin::Entity ground = s_currentScene->AddEntity("ground");
        ground.AddComponent<puffin::components::Image>("/ice/game/Assets/Images/square.bmp");
        ground.AddComponent<puffin::components::BoxCollider>();
        auto &groundT = ground.GetComponent<puffin::components::Transform>();
        groundT.m_rect->x = 0;
        groundT.m_rect->y = 90;
        groundT.m_rect->w = 50;
        groundT.m_rect->h = 10;

        ground.AddComponent<puffin::components::Rigidbody2D>(5, false);

        puffin::Entity rigid = s_currentScene->AddEntity("rigid");
        rigid.AddComponent<puffin::components::Image>("/ice/game/Assets/Images/square.bmp");
        rigid.AddComponent<puffin::components::BoxCollider>();
        auto &t = rigid.GetComponent<puffin::components::Transform>();
        t.m_rect->x = 0;
        t.m_rect->y = 0;
        t.m_rect->w = 10;
        t.m_rect->h = 10;

        rigid.AddComponent<puffin::components::Rigidbody2D>(5, false);

        puffin::Graphics::Get().PlacePixelShader(&puffin::PalletPixelShader);
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
        s_currentScene->TickRuntime(1.0f);
    }
}