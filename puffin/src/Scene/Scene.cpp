
#include "Scene.h"
#include "Entity.h"
#include "Components.h"

#include "Core/ID.h"
#include "Rendering/Graphics.h"
#include "ScriptableComponent.h"
#include <SDL2/SDL.h>
#include "Core/Timestep.h"

#include "Physics/Physics.h"
#include "Physics/Collision.h"

#include "Core/Logging.h"
#include "Core/Assert.h"

#include <unordered_map>

#define LINIER_DRAG_COEFFICIENT 0.1

namespace puffin
{
    Scene::Scene()
    {
        PN_CORE_INFO("Scene constructor called");
    }

    Entity Scene::AddEntity(const std::string &name)
    {
        PN_CORE_INFO("Adding entity");
        return MakeEntityWithUUID(UUID(), name);
    }

    Entity Scene::MakeEntityWithUUID(UUID uuid, const std::string &name)
    {
        Entity entity = {this, registry.create()};

        entity.AddComponent<components::IDComponent>().m_ID = uuid;
        entity.AddComponent<components::Transform>(10, 0, 10, 10);
        entity.AddComponent<components::Tag>(name.empty() ? "Entity" : name);

        m_entities.push_back(entity);

        return entity;
    }

    void Scene::TickRuntime(float deltaTime)
    {

        TickPhysicsSimulation(deltaTime);

        auto view = registry.view<components::Image>();

        for (auto e : view)
        {
            Entity entity = {this, e};
            auto &transform = entity.GetComponent<components::Transform>();
            auto &image = entity.GetComponent<components::Image>();

            Graphics::Get().PlaceImage(image.surface.get(), transform.m_rect.get());
        }

        // Lights
        auto lightView = registry.view<components::Light>();

        for (auto e : lightView)
        {
            Entity entity = {this, e};
            auto &transform = entity.GetComponent<components::Transform>();
            auto &light = entity.GetComponent<components::Light>();

            Graphics::Get().PlaceLight(light.m_lightType, transform.m_rect->x, transform.m_rect->y);
        }
    }

    void Scene::TickPhysicsSimulation(float deltaTime)
    {
    }

    void Scene::DrawGizmos()
    {
    }

    template <typename T>
    void Scene::OnComponentAdded(Entity entity, T &component)
    {
        static_assert(sizeof(T) == 0);
    }

    template <>
    void Scene::OnComponentAdded<components::Transform>(Entity entity, components::Transform &component)
    {
    }

    template <>
    void Scene::OnComponentAdded<components::Tag>(Entity entity, components::Tag &component)
    {
    }

    template <>
    void Scene::OnComponentAdded<components::IDComponent>(Entity entity, components::IDComponent &component)
    {
    }

    template <>
    void Scene::OnComponentAdded<components::Image>(Entity entity, components::Image &component)
    {
        Graphics::Get().PlaceImage(component.surface.get(), entity.GetComponent<components::Transform>().m_rect.get());
    }

    template <>
    void Scene::OnComponentAdded<components::Light>(Entity entity, components::Light &component)
    {
    }
} // namespace puffin
