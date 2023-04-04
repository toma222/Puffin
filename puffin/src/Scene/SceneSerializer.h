
#pragma once

#include "Scene.h"
#include "Entity.h"

#include "Core/Core.h"

namespace puffin
{
    class SceneSerializer
    {
    public:
        SceneSerializer(const Ref<Scene> &scene);

        void SerializeScene(const std::string &filepath);
        bool Deserialize(const std::string &filepath);

    private:
        Ref<Scene> m_Scene;
    };
} // namespace puffin
