
#include <puffin.h>

#include "GameLayer.h"

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"

#include <functional>

std::shared_ptr<puffin::Scene> GameLayer::s_currentScene = std::make_shared<puffin::Scene>();

void GameLayer::OnAttach()
{
    ImGui::CreateContext();
    ImGui_ImplSDL2_InitForSDLRenderer(puffin::Application::Get().GetWindow()->GetWindow()->GetWindow(), puffin::Graphics::Get().GetRenderer()->get());
    ImGui_ImplSDLRenderer_Init(puffin::Graphics::Get().GetRenderer()->get());

    GM_CORE_INFO("Attach called for game layer");

    /*
    puffin::Entity Image = s_currentScene->AddEntity("Tree Building Image");
    Image.AddComponent<puffin::components::Image>("/ice/game/Assets/Images/TreeBuilding.bmp");
    auto &imageT = Image.GetComponent<puffin::components::Transform>();
    imageT.m_rect->x = 0;
    imageT.m_rect->y = 0;
    imageT.m_rect->w = 192;
    imageT.m_rect->h = 108;
    */

    puffin::SceneSerializer serialize(s_currentScene);
    // serialize.SerializeScene("C:/Users/Aidan/Documents/OtherUsslessProjects'/Puffin/Scene.json");
    // C:\Users\100044352\Desktop\New folder\Puffin\Scene.json
    serialize.Deserialize("C:/Users/Aidan/Documents/OtherUsslessProjects'/Puffin/Scene.json");
}

void GameLayer::OnDetach()
{
    GM_CORE_INFO("Detach called for game layer");
}

void GameLayer::Start()
{
}

void GameLayer::Update()
{
    s_currentScene->TickRuntime(1.0f);
}
