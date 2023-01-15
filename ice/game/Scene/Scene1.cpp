
#include <puffin.h>
#include "Scene1.h"

namespace game
{

    void Scene1::StartScene()
    {
        puffin::render::SDLTexture *texture = new puffin::render::SDLTexture(puffin::Application::Get().GetGraphics()->GetRenderer(),
                                                                             "C:/Users/Aidan/Documents/programming/EngineInADay - Copy/ice/game/Assets/Images/download.bmp",
                                                                             192, 108);

        puffin::Application::Get().GetGraphics()->AddTextureToQue(texture, 0);

        puffin::Entity *entity = m_sceneContainer->AddEntity();
        puffin::components::Transform *trans = entity->GetComponent<puffin::components::Transform>();
    }

    void Scene1::UpdateScene()
    {
    }

    void Scene1::ClearScene()
    {
        // Clear the render que
        GM_CORE_TRACE("Clearing scene");
        puffin::Application::Get().GetGraphics()->ClearTextureRenderQue();
    }

    void Scene1::DestroyScene()
    {
        delete m_sceneContainer;
    }

    std::string Scene1::s_sceneName = "Scene 1";
} // namespace game
