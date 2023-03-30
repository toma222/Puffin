
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

        /*
        ! put physics in latter
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
        */

        // GRAPHICS-DEMO
        puffin::Entity Image = s_currentScene->AddEntity("image");
        Image.AddComponent<puffin::components::Image>("/ice/game/Assets/Images/BuildingWall.bmp");
        auto &imageT = Image.GetComponent<puffin::components::Transform>();
        imageT.m_rect->x = 0;
        imageT.m_rect->y = 0;
        imageT.m_rect->w = 192;
        imageT.m_rect->h = 108;

        puffin::Entity globalLight = s_currentScene->AddEntity("global light");
        globalLight.AddComponent<puffin::components::Light>(new puffin::GlobalLight(0.4f, puffin::PNColor(255, 255, 255)));

        puffin::Entity l1 = s_currentScene->AddEntity("light 1");
        l1.AddComponent<puffin::components::Light>(new puffin::PointLight(60, 0, puffin::PNColor(211, 226, 140)));
        auto &l1T = l1.GetComponent<puffin::components::Transform>();
        l1T.m_rect->x = 34;
        l1T.m_rect->y = 28;

        puffin::Entity l2 = s_currentScene->AddEntity("light 2");
        l2.AddComponent<puffin::components::Light>(new puffin::PointLight(50, 10, puffin::PNColor(211, 226, 140)));
        auto &l2T = l2.GetComponent<puffin::components::Transform>();
        l2T.m_rect->x = 162;
        l2T.m_rect->y = 27;

        puffin::Graphics::Get().PlacePostEffect<puffin::PalletCurver>();

        /*
        puffin::Entity l3 = s_currentScene->AddEntity("light 3");
        l3.AddComponent<puffin::components::Light>(new puffin::PointLight(10, 10, puffin::PNColor(255, 255, 255)));
        auto &l3T = l3.GetComponent<puffin::components::Transform>();
        l3T.m_rect->x = 60;
        l3T.m_rect->y = 80;
        */
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