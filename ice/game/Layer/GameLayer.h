
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

        template <typename T>
        void SetCurrentScene()
        {
            if (s_currentScene == nullptr)
            {
                s_currentScene = new T();
                s_currentScene->CreateContainer();
            }
            else
            {
                s_currentScene->ClearScene();
                s_currentScene->DestroyScene();

                delete s_currentScene;

                s_currentScene = new T();
                s_currentScene->StartScene();
                s_currentScene->CreateContainer();
            }
        }
    };

} // namespace game
