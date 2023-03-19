
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

        static puffin::Scene *s_currentScene;

        void SetCurrentScene()
        {
        }
    };

} // namespace game
