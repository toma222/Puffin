
#pragma once

#include <puffin.h>

namespace game
{
    class GameLayer : public puffin::Layer
    {
    public:
        void OnAttach() override;
        void OnDetach() override;
        void Update() override;
        void Start() override;

        static std::shared_ptr<puffin::Scene> s_currentScene;

        static puffin::Scene &GetCurrentScene()
        {
            return *s_currentScene;
        }
    };

} // namespace game
