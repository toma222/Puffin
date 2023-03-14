
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
        static puffin::Container *s_currentContainer;

        template <typename T>
        void SetCurrentScene()
        {
            if (s_currentScene == nullptr)
            {
                s_currentScene = new T();
            }
            else
            {
                s_currentScene->ClearScene();
                s_currentScene->DestroyScene();

                delete s_currentScene;

                s_currentScene = new T();
                s_currentScene->StartScene();
            }
        }
    };

} // namespace game
