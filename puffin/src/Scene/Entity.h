
#pragma once

#include "Scene.h"
#include "Components.h"
#include "Core/Logging.h"
#include "Core/ID.h"
#include "entt/entt.hpp"

namespace puffin
{
    class Entity
    {
    public:
        Entity(Scene *scene, entt::entity entity);

        template <typename T, typename... Args>
        T &AddComponent(Args &&...args)
        {
            if (HasComponent<T>() == false)
            {
                T &component = m_sceneRef->registry.emplace<T>(m_entity, std::forward<Args>(args)...);
                m_sceneRef->OnComponentAdded<T>(*this, component);
                return component;
            }
            else
            {
                printf("Already has component you can't tell me what to do :(, I am not adding it\n");
            }

            // return T(std::forward<Args>(args)...);
        }

        // Assumes the entity has this component
        template <typename T>
        T &GetComponent()
        {
            return m_sceneRef->registry.get<T>(m_entity);
        }

        template <typename T>
        bool HasComponent()
        {
            return m_sceneRef->registry.all_of<T>(m_entity);
        }

        template <typename T>
        T RemoveComponent()
        {
        }

        operator bool() const { return m_entity != entt::null; }
        operator entt::entity() const { return m_entity; }
        operator uint32_t() const { return (uint32_t)m_entity; }

    private:
        Scene *m_sceneRef = nullptr;
        entt::entity m_entity{entt::null};
    };
}
