
#include "Scene.h"
#include "Entity.h"
#include "Components.h"

#include "Core/ID.h"
#include "Rendering/Graphics.h"
#include "ScriptableComponent.h"
#include <SDL2/SDL.h>
#include "Core/Timestep.h"

#include "Physics/Physics.h"

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

        /*

        auto c = registry.view<components::BoxCollider>();
        int i = 0;
        int j = 0;

        for (auto eA : c)
        {
            Entity A = {this, eA};
            auto &Atransform = A.GetComponent<components::Transform>();
            auto &Acollider = A.GetComponent<components::BoxCollider>();
            auto &Arigidbody = A.GetComponent<components::Rigidbody2D>();

            i = j + 1;

            for (auto eB : c)
            {
                Entity B = {this, eB};

                if (A != B && j < i)
                {
                    auto &Btransform = B.GetComponent<components::Transform>();
                    auto &Bcollider = B.GetComponent<components::BoxCollider>();
                    auto &Brigidbody = B.GetComponent<components::Rigidbody2D>();

                    bool colliding = true;

                    Vector2 r2 = Vector2(Atransform.m_rect->x + Atransform.m_rect->w, Atransform.m_rect->y + Atransform.m_rect->h);
                    Vector2 l2 = Vector2(Btransform.m_rect->x + Btransform.m_rect->w, Btransform.m_rect->y + Btransform.m_rect->h);

                    Vector2 r1 = Vector2(Atransform.m_rect->x, Atransform.m_rect->y);
                    Vector2 l1 = Vector2(Btransform.m_rect->x, Btransform.m_rect->y);

                    if (!((r1.x > l2.x) || (r2.x < l1.x) || (r1.y > l2.y) ||
                          (r2.y < l1.y)))
                    {
                        printf("asd\n");

                        Vector2 collisionNormal = Vector2(Atransform.m_rect->x - Btransform.m_rect->x, Atransform.m_rect->y - Btransform.m_rect->y);
                        Vector2 relativeVelocity = Vector2(Arigidbody.m_velocity.x - Brigidbody.m_velocity.x, Arigidbody.m_velocity.y - Brigidbody.m_velocity.y);

                        collisionNormal.NormalizeVector();

                        float e = 0.0f; // who knows what this does
                        float J = (-(1 + e) * relativeVelocity.DotProduct(collisionNormal)) / ((1 / Arigidbody.m_mass) + (1 / Brigidbody.m_mass));

                        Arigidbody.m_velocity.x += (1 / Arigidbody.m_mass) * J * collisionNormal.x;
                        Arigidbody.m_velocity.y += (1 / Arigidbody.m_mass) * J * collisionNormal.y;

                        Brigidbody.m_velocity.x -= (1 / Brigidbody.m_mass) * J * collisionNormal.x;
                        Brigidbody.m_velocity.y -= (1 / Brigidbody.m_mass) * J * collisionNormal.y;
                    }
                }

                j++;
            }

            i++;
        }

        */

        auto r = registry.view<components::Rigidbody2D>();

        for (auto e : r)
        {
            Entity entity = {this, e};
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
