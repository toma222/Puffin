
#include <puffin.h>

#include "GameLayer.h"
#include "Assets/NativeScriptIncludes.h"

#include <functional>

namespace game
{
    std::shared_ptr<puffin::Scene> GameLayer::s_currentScene = std::make_shared<puffin::Scene>();

    void GameLayer::OnAttach()
    {
        GM_CORE_INFO("Attach called for game layer");

        /*
        puffin::Entity Image = s_currentScene->AddEntity("Tree Building Image");
        Image.AddComponent<puffin::components::Image>("/ice/game/Assets/Images/TreeBuilding.bmp");
        auto &imageT = Image.GetComponent<puffin::components::Transform>();
        imageT.m_rect->x = 0;
        imageT.m_rect->y = 0;
        imageT.m_rect->w = 192;
        imageT.m_rect->h = 108;

        puffin::Entity l3 = s_currentScene->AddEntity("light 3");
        l3.AddComponent<puffin::components::Light>(new puffin::GlobalLight(1, puffin::PNColor(255, 255, 255)));
        auto &l3T = l3.GetComponent<puffin::components::Transform>();
        l3T.m_rect->x = 60;
        l3T.m_rect->y = 80;

        */

        // Post
        // puffin::Graphics::Get().PlacePostEffect<puffin::KuwaharaFilter>(2);
        puffin::Graphics::Get().PlacePostEffect<puffin::CrossDithering>(0.25f);
        puffin::PalletCurver *p = puffin::Graphics::Get().PlacePostEffect<puffin::PalletCurver>();

        static int Pallet[40] = {
            0x7a2d30,
            0x632b38,
            0x4a2936,
            0x362530,
            0x292225,
            0x8f422c,
            0x995325,
            0xab6c2c,
            0xa67c23,
            0x996d20,
            0x805622,
            0x5e431f,
            0x403125,
            0x8c7f0b,
            0x686700,
            0x4d5e21,
            0x374529,
            0x364f33,
            0x81a867,
            0x669170,
            0x466b5d,
            0x344a4d,
            0x29323b,
            0x304452,
            0x375c69,
            0x418791,
            0x9c525a,
            0x783e51,
            0x5c3047,
            0x442e4a,
            0x63413f,
            0x9e6a55,
            0xbe9167,
            0xccab78,
            0x3e3c42,
            0x5e5d5d,
            0x78736d,
            0x8f897b,
            0xb3b09f,
            0xdbdbd0};

        p->AppendPallet<40>(Pallet);

        puffin::SceneSerializer serialize(s_currentScene);
        // serialize.SerializeScene("C:/Users/Aidan/Documents/OtherUsslessProjects'/Puffin/Scene.json");
        serialize.Deserialize("C:/Users/Aidan/Documents/OtherUsslessProjects'/Puffin/Scene.json");
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