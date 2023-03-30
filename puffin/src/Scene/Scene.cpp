
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

#include <unordered_map>

#define LINIER_DRAG_COEFFICIENT 0.1

namespace puffin
{
    Scene::Scene()
    {
        printf("Making Scene\n");
    }

    Entity Scene::AddEntity(const std::string &name)
    {
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

        // Scripts
        auto scripts = registry.view<components::NativeScriptComponent>();
        for (auto e : scripts)
        {
            Entity entity = {this, e};
            entity.GetComponent<components::NativeScriptComponent>().Instance->OnUpdate();
        }

        // Place images
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
        // ! the collision normal is not calculated using the center of the object
        // ! the collision needs to be in another function so you can back up the physics sim to when the objects are colliding not penetrating
        // * no spacial partitioning so this thing is slow
        // * IT WORKS

        auto r = registry.view<components::Rigidbody2D>();
        int i = 0;

        for (auto e : r)
        {
            float dTime;
            int tryAgain = true;
            bool didPen = false;

            Entity entity = {this, e};
            // components::Transform transform = entity.GetComponent<components::Transform>();
            // components::Rigidbody2D &rigidbody = entity.GetComponent<components::Rigidbody2D>();

            // loop through the objects it could collide with
            for (int j = 0; j < m_entities.size() - i; j++)
            {
                if (m_entities[j] != entity)
                {
                    while (tryAgain == true)
                    {
                        int resp = CheckCollision(entity, m_entities[j]);

                        if (resp == PENETRATING)
                        {
                            printf("colliding\n");
                            ApplyImpulse(entity, m_entities[j]);
                        }

                        tryAgain = false;
                    }
                }
            }

            i++;
        }

        for (auto e : r)
        {
            Entity entity = {this, e};
            components::Transform transform = entity.GetComponent<components::Transform>();
            components::Rigidbody2D &rigidbody = entity.GetComponent<components::Rigidbody2D>();

            Physics2D::UpdateBodyEuler(entity, Timestep(1.0f));
        }
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

    template <>
    void Scene::OnComponentAdded<components::NativeScriptComponent>(Entity entity, components::NativeScriptComponent &component)
    {
    }

    template <>
    void Scene::OnComponentAdded<components::Rigidbody2D>(Entity entity, components::Rigidbody2D &component)
    {
        components::Transform &t = entity.GetComponent<components::Transform>();

        component.m_centerOfMass.x = (t.m_rect->w / 2);
        component.m_centerOfMass.y = (t.m_rect->h / 2);
    }

    template <>
    void Scene::OnComponentAdded<components::BoxCollider>(Entity entity, components::BoxCollider &component)
    {
    }

} // namespace puffin
