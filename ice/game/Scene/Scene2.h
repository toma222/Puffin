
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

    public:
        void ClearScene() override;
        void DestroyScene() override;

        void UpdateScene() override;
        void StartScene() override;

        std::string GetName() override { return Scene2::s_sceneName; };
    };

} // namespace game
