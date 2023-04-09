
#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include <string>

#include "Rendering/PSurface.h"
#include "Rendering/Graphics.h"
#include "Rendering/Light.h"
#include "Math/PNVector.h"
#include "Core/ID.h"

#include "Scripting/LuaGlue.h"
#include "Scripting/LuaScripting.h"

namespace puffin
{
    class NativeScript;

    namespace components
    {

        // Contains the transform rect for the renderer
        struct Transform
        {
            std::shared_ptr<SDL_Rect> m_rect;

            Transform() = default;
            Transform(const Transform &transform) = default;
            Transform(const std::shared_ptr<SDL_Rect> &rect)
                : m_rect(rect){};
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

            Image(const Image &image) = default;
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
            puffin::LightType *m_lightType;

            Light() = default;
            Light(const Light &light) = default;
            Light(puffin::LightType *lightType)
                : m_lightType(lightType){};
        };

        struct Script
        {
            LuaScript m_scriptInstance;
            bool m_initilized;

            Script(std::string path, std::string moduleName)
                : m_scriptInstance(path, moduleName)
            {
                LuaGlue::LoadInternal(m_scriptInstance.m_luaState);
                m_initilized = false;
            };
        };

    }
}
