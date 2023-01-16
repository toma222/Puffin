
#pragma once

#include "Container.h"

namespace puffin
{
    class Scene
    {
    protected:
        // Container *m_sceneContainer;

    public:
        virtual void ClearScene();
        virtual void DestroyScene();

        virtual void UpdateScene();
        virtual void StartScene();

        virtual std::string GetName();
        // Container *GetContainer() { return m_sceneContainer; };

        // void CreateContainer()
        // {
        //     m_sceneContainer = new Container(100);
        // }
    };
} // namespace puffin
