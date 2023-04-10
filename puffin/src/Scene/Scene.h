
#pragma once

#include "Core/ID.h"
#include "Core/Timestep.h"

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
        Entity MakeEntityWithUUID(UUID uuid, const std::string &name);

        template <typename T>
        void OnComponentAdded(Entity entity, T &component);

        void TickRuntime(float deltaTime);
        void TickPhysicsSimulation(Timestep deltaTime);
        void DrawGizmos();

    public:
        entt::registry registry;

        // std::unordered_map<UUID, entt::entity> m_entityMap;
        std::vector<Entity> m_entities;
        int m_testValue;
    };
} // namespace puffin
