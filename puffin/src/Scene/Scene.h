
#pragma once

#include "Core/ID.h"
#include "Core/ID.h"

#include <entt/entt.hpp>

#include <unordered_map>

namespace puffin
{
    class Entity;

    class Scene
    {
    public:
        Scene();

        Entity AddEntity(const std::string &name);
        Entity MakeEntityWithUUID(PUFFIN_ID uuid, const std::string &name);

        template <typename T>
        void OnComponentAdded(Entity entity, T &component);

        void TickRuntime(float deltaTime);

    public:
        entt::registry registry;
    };
} // namespace puffin
