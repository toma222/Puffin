
#pragma once

// inherits from the game layer class
#include <puffin.h>
#include "../Layer/GameLayer.h"

#include <string>

namespace game
{
    class Scene2 : public puffin::Scene
    {
    private:
        static std::string s_sceneName;
        puffin::Container *m_container;

    public:
        void ClearScene() override;
        void DestroyScene() override;

        void UpdateScene() override;
        void StartScene() override;

        std::string GetName() override { return Scene2::s_sceneName; };

        Scene2()
        {
        }

        ~Scene2()
        {
            GM_CORE_CLEAN("Destroying Scene 2");
            // delete m_sceneContainer;
        };
    };
} // namespace game
