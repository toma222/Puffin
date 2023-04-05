
#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include <string>

#include "Rendering/PSurface.h"
#include "Rendering/Graphics.h"
#include "Rendering/Light.h"
#include "Math/PNVector.h"
#include "Core/ID.h"

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
            UUID m_ID;

            IDComponent() = default;
            IDComponent(const IDComponent &idComponent) = default;
            IDComponent(UUID id)
                : m_ID(id){};
        };

        struct Light
        {
            // puffin::Graphics::Get().PlaceLight(new puffin::PointLight(100, 100), 0, 0);
            puffin::LightType *m_lightType;

            Light() = default;
            Light(const Light &light) = default;
            Light(puffin::LightType *lightType)
                : m_lightType(lightType){};
        };

        // Borrowed from the cherno (thanks)
        struct NativeScriptComponent
        {
            NativeScript *Instance;

            template <typename T>
            void Bind()
            {
                Instance = (NativeScript *)new T();
            }
        };

        struct Rigidbody2D
        {
            float m_mass;
            float m_angularVelocity; // z rotation 'buffer' if you will
            float m_speed;
            float m_drag;

            Vector2 m_velocityBody;
            Vector2 m_forces;
            Vector2 m_velocity;
            Vector2 m_velocityBuffer; // this is added to the rigidbody then set to zero
            Vector2 m_centerOfMass;

            bool m_gravity;
            bool m_simulated;

            Rigidbody2D(float mass, bool gravity)
                : m_mass(mass), m_angularVelocity(0), m_speed(0), m_velocityBody(0, 0), m_forces(0, 0), m_velocity(0, 0), m_simulated(true)
            {
                m_gravity = gravity;
                m_drag = 1;
                m_centerOfMass = Vector2(0, 0);
            };
        };

        struct BoxCollider
        {
            Vector2 m_offset;

            BoxCollider() = default;
            BoxCollider(Vector2 offset) : m_offset(offset){};
        };

        struct Particle
        {
            int x;
            int y;
            int w;
            int h;

            std::shared_ptr<render::SDLSurface> m_image;
        };

        struct ParticleSystem
        {
            bool m_update;
            int m_instantiations;
            std::shared_ptr<SDL_Rect> m_rect;
            std::vector<Particle> m_particles;
            std::shared_ptr<render::SDLSurface> m_surface;

            ParticleSystem() = default;
            ParticleSystem(const ParticleSystem &system) = default;
            ParticleSystem(std::string path, int instantiations, int sizeX, int sizeY, bool update = false) : m_update(update)
            {
                m_instantiations = instantiations;
                m_rect = std::make_shared<SDL_Rect>();
                m_rect->w = sizeX;
                m_rect->h = sizeY;
                m_surface = std::make_shared<render::SDLSurface>(path.c_str(), sizeX, sizeY);

                for (int i = 0; i < instantiations; i++)
                {
                    Particle p = Particle();

                    p.w = sizeX;
                    p.h = sizeY;
                    p.m_image = m_surface;

                    m_particles.push_back(p);
                }
            };
        };
    }
}
