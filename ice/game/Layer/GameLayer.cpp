
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

        puffin::Entity phil = s_currentScene->AddEntity("image");
        phil.AddComponent<puffin::components::Image>("C:/Users/Aidan/Documents/OtherUsslessProjects'/Puffin/ice/game/Assets/Images/download.bmp");
        phil.AddComponent<puffin::components::NativeScriptComponent>().Bind<BasicScript>();

        puffin::Entity e = s_currentScene->AddEntity("light");
        // e.AddComponent<puffin::components::Image>("C:/Users/Aidan/Documents/OtherUsslessProjects'/Puffin/ice/game/Assets/Images/Circle.bmp");
        // e.AddComponent<puffin::components::Light>(new puffin::PointLight(100, 100, puffin::PNColor(255, 255, 255)));

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
        s_currentScene->TickRuntime(0.0f);
    }
}