
#pragma once

// inherits from the game layer class
#include <puffin.h>
#include "../Layer/GameLayer.h"

#include <string>

namespace game
{
    class Scene1 : public puffin::Scene
    {
    private:
        static std::string s_sceneName;

    public:
        void ClearScene() override;
        void DestroyScene() override;

        void UpdateScene() override;
        void StartScene() override;

        std::string GetName() override { return Scene1::s_sceneName; };

        Scene1()
        {
            // if (m_sceneContainer == nullptr)
            //     CreateContainer();
        }

        ~Scene1()
        {
            GM_CORE_CLEAN("Destroying Scene 1");
            // delete m_sceneContainer;
        };
    };

} // namespace game
