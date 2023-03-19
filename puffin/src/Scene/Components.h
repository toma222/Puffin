
#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include <string>

#include "Rendering/PSurface.h"
#include "Rendering/Graphics.h"
#include "Core/ID.h"

namespace puffin
{
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

            Image() = default;
            Image(const Image &image) = default;
            Image(std::string path)
                : m_path(path)
            {
                surface = std::make_shared<render::SDLSurface>(path.c_str(), 100, 10);
            };
        };

        struct IDComponent
        {
            PUFFIN_ID m_ID;

            IDComponent() = default;
            IDComponent(const IDComponent &idComponent) = default;
            IDComponent(PUFFIN_ID id)
                : m_ID(id){};
        };
    }
}
