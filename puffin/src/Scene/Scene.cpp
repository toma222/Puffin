
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

    template <typename... Component>
    static void CopyComponent(components::ComponentGroup<Component...>, entt::registry &dst, entt::registry &src, const std::unordered_map<UUID, entt::entity> &enttMap)
    {
        CopyComponent<Component...>(dst, src, enttMap);
    }

    template <typename... component>
    static void CopyComponent(entt::registry &dst, entt::registry &src, const std::unordered_map<UUID, entt::entity> &enttMap)
    {
        ([&]()
         {
             auto view = src.view<component>();

             for (auto srcEntity : view)
             {
                 entt::entity dstEntity = enttMap.at(src.get<components::IDComponent>(srcEntity).m_ID);

                 auto srcComponent = src.get<component>(srcEntity);
                 dst.emplace_or_replace<component>(dstEntity, srcComponent);
             } }(),
         ...);
    }

    std::shared_ptr<Scene> Scene::Copy(std::shared_ptr<Scene> other)
    {
        std::shared_ptr<Scene> newScene = std::make_shared<Scene>();

        auto &srcRegistry = other->registry;
        auto &dstRegistry = newScene->registry;
        std::unordered_map<UUID, entt::entity> enttMap;

        auto eView = srcRegistry.view<components::IDComponent>();
        for (auto e : eView)
        {
            UUID uuid = srcRegistry.get<components::IDComponent>(e).m_ID;
            const auto &name = srcRegistry.get<components::Tag>(e).m_Tag;
            Entity entity = newScene->MakeEntityWithUUID(uuid, name);
            enttMap[uuid] = (entt::entity)entity;
        }

        CopyComponent(components::AllComponents{}, dstRegistry, srcRegistry, enttMap);

        return newScene;
    }

    Entity Scene::AddEntity(const std::string &name)
    {
        return MakeEntityWithUUID(UUID(), name);
    }

    Entity Scene::MakeEntityWithUUID(UUID uuid, const std::string &name)
    {
        PN_CORE_INFO("Adding entity");
        Entity entity = {this, registry.create()};

        entity.AddComponent<components::IDComponent>().m_ID = uuid;
        entity.AddComponent<components::Transform>(10, 0, 10, 10);
        entity.AddComponent<components::Tag>(name.empty() ? "Entity" : name);

        m_entities[uuid] = entity.m_entity;

        return entity;
    }

    void Scene::TickRuntime(float deltaTime)
    {
        auto view = registry.view<components::Image>();

        for (auto e : view)
        {
            Entity entity = {this, e};
            auto &transform = entity.GetComponent<components::Transform>();
            auto &image = entity.GetComponent<components::Image>();

            Graphics::Get().PlaceImage(image.surface.get(), transform.m_rect.get());
        }

        auto scriptView = registry.view<components::Script>();
        for (auto e : scriptView)
        {
            Entity entity = {this, e};
            auto &script = entity.GetComponent<components::Script>();

            if (!script.m_initilized)
            {
                script.m_initilized = true;
                script.m_scriptInstance->RunFunction("Start");
            }

            script.m_scriptInstance->RunFunction("Update");
        }
    }

    void Scene::TickPhysicsSimulation(Timestep deltaTime)
    {
        auto rigidBodyView = registry.view<components::RigidBody2D>();

        for (auto e : rigidBodyView)
        {
            Entity entity = {this, e};
            components::RigidBody2D &r = entity.GetComponent<components::RigidBody2D>();
            components::Transform &t = entity.GetComponent<components::Transform>();

            if (r.m_type == components::RigidBody2D::DYNAMIC)
            {
                PNRect newTransform = Physics2D::UpdateBodyEuler(&r.m_model, deltaTime);
                t.m_rect->x += newTransform.m_x;
                t.m_rect->y += newTransform.m_y;
            }
        }
    }

    void Scene::TickEditor(Timestep deltaTime)
    {
        auto view = registry.view<components::Image>();

        for (auto e : view)
        {
            Entity entity = {this, e};
            auto &transform = entity.GetComponent<components::Transform>();
            auto &image = entity.GetComponent<components::Image>();

            Graphics::Get().PlaceImage(image.surface.get(), transform.m_rect.get());
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
    }

    template <>
    void Scene::OnComponentAdded<components::RigidBody2D>(Entity entity, components::RigidBody2D &component)
    {
        components::Transform &t = entity.GetComponent<components::Transform>();
        component.m_model.m_projectedArea = t.m_rect->w * t.m_rect->h;
    }

    template <>
    void Scene::OnComponentAdded<components::Script>(Entity entity, components::Script &component)
    {
        // IDK why but this line of code makes me laugh
        // sol::reference ref = sol::make_reference_userdata<Vector2>(LuaScripting::s_globalState.lua_state(), 0, 0);

        component.m_scriptInstance->m_luaState[component.m_scriptInstance->m_moduleName.c_str()]["entity"] = entity;
        component.m_scriptInstance->m_luaState[component.m_scriptInstance->m_moduleName.c_str()]["transform"] = entity.GetComponent<components::Transform>();
    }
} // namespace puffinz
