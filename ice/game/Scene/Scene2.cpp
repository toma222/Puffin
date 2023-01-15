
#include "Scene2.h"

namespace game
{
    void Scene2::StartScene()
    {
        puffin::render::SDLTexture *texture = new puffin::render::SDLTexture(puffin::Application::Get().GetGraphics()->GetRenderer(),
                                                                             "C:/Users/Aidan/Documents/programming/EngineInADay - Copy/ice/game/Assets/Images/TreeBuilding.bmp",
                                                                             192, 108);

        puffin::Application::Get().GetGraphics()->AddTextureToQue(texture, 0);
    }

    void Scene2::UpdateScene()
    {
    }

    void Scene2::ClearScene()
    {
        GM_CORE_TRACE("Clearing scene");

        puffin::Application::Get().GetGraphics()->ClearTextureRenderQue();
    }

    void Scene2::DestroyScene()
    {
        delete m_sceneContainer;
    }

    std::string Scene2::s_sceneName = "Scene 2";
} // namespace game
