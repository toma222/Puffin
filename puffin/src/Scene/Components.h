
#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include <string>

#include "Rendering/PSurface.h"
#include "Rendering/Graphics.h"
#include "Rendering/Light.h"
#include "Math/PNVector.h"
#include "Core/ID.h"

#include "Physics/Physics.h"

#include "Scripting/LuaGlue.h"
#include "Scripting/LuaScripting.h"

namespace puffin
{
    class NativeScript;

    namespace components
    {
        struct Transform
        {
            std::shared_ptr<SDL_Rect> m_rect;

            Transform() = default;
            Transform(const Transform &transform)
            {
                m_rect = std::make_shared<SDL_Rect>();

                m_rect->x = transform.m_rect->x;
                m_rect->y = transform.m_rect->y;
                m_rect->w = transform.m_rect->w;
                m_rect->h = transform.m_rect->h;
            }

            Transform(int x, int y, int w, int h)
            {
                m_rect = std::make_shared<SDL_Rect>();

                m_rect->x = x;
                m_rect->y = y;
                m_rect->w = w;
                m_rect->h = h;
            }
        };

        struct Tag
        {
            std::string m_Tag;

            Tag() = default;
            Tag(const Tag &tag) = default;
            Tag(std::string tag)
                : m_Tag(tag){};
        };

        struct Image
        {
            std::string m_path;
            std::shared_ptr<render::SDLSurface> surface;

            Image() : m_path("PATH NOT SET")
            {
                surface = std::make_shared<render::SDLSurface>(m_path.c_str(), 100, 10);
            }

            Image(const Image &image)
            {
                surface = std::make_shared<render::SDLSurface>(image.m_path.c_str(), 100, 10);
            }

            Image(std::string path)
                : m_path(path)
            {
                surface = std::make_shared<render::SDLSurface>(path.c_str(), 100, 10);
            };
        };

        struct IDComponent
        {
            UUID m_ID;

            IDComponent() = default;
            IDComponent(const IDComponent &idComponent) = default;
            IDComponent(UUID id)
                : m_ID(id){};
        };

        struct Light
        {
            // ! this is a memory leak (that I will deal with latter)
            // ! also the copy scene code wont play nice with this pointer
            std::shared_ptr<LightType> m_lightType;
            LIGHT_TYPE m_enumType;

            Light() = default;
            /*Light(const Light &light)
            {
                if (light.m_enumType == LIGHT_TYPE::POINT)
                {

                    std::shared_ptr<PointLight> pointLightRef = std::static_pointer_cast<PointLight>(light.m_lightType);
                    m_lightType = std::make_shared<PointLight>(pointLightRef->m_power, pointLightRef->m_luminance, light.m_lightType->m_lightColor);
                }

                if (light.m_enumType == LIGHT_TYPE::GLOBAL)
                {

                    std::shared_ptr<GlobalLight> globalLightRef = std::static_pointer_cast<GlobalLight>(light.m_lightType);
                    m_lightType = std::make_shared<GlobalLight>(globalLightRef->m_power, light.m_lightType->m_lightColor);
                }
            }*/
            Light(const Light &light) = default;

            template <typename T, typename... Args>
            void AttachType(Args &&...args)
            {
                m_lightType = std::make_shared<T>(std::forward<Args>(args)...);
                m_enumType = m_lightType->GetType();
            };
        };

        struct Script
        {
            std::shared_ptr<LuaScript> m_scriptInstance;
            std::string m_path;
            bool m_initilized;

            Script(std::string path, std::string moduleName)
            {
                m_scriptInstance = std::make_shared<LuaScript>(path, moduleName);
                LuaGlue::LoadInternal(m_scriptInstance->m_luaState);
                m_initilized = false;
            };

            Script(const Script &script)
            {
                m_scriptInstance = std::make_shared<LuaScript>(script.m_path, script.m_scriptInstance->m_moduleName);
                LuaGlue::LoadInternal(m_scriptInstance->m_luaState);
                m_initilized = false;
            };
        };

        struct RigidBody2D
        {
            enum BodyType
            {
                STATIC = 0,
                DYNAMIC,
                KINEMATIC
            };

            BodyType m_type = BodyType::STATIC;
            PhysicsModel m_model;

            RigidBody2D() = default;
            RigidBody2D(float mass)
            {
                m_model.m_mass = mass;
            };

            RigidBody2D(const RigidBody2D &rb) = default;
        };

        template <typename... Component>
        struct ComponentGroup
        {
        };

        using AllComponents = ComponentGroup<RigidBody2D, Transform, Image, Light, Script>;
    }
}
