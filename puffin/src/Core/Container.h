
#pragma once

#include "Core.h"
#include "Logging.h"
#include "Components/Component.h"

#include <memory>
#include <vector>

// Only 2 different components
#define UNIQUE_COMPONENTS 2

namespace puffin
{
    class Entity
    {
    private:
        unsigned int m_CompID;
        unsigned int m_ID;
        short int m_componentCount;

        // only 32 components allowed
        std::vector<components::Component *> m_components;

    public:
        Entity(unsigned int ID)
        {
            m_ID = ID;
            m_componentCount = 0;
            m_components.resize(32);
        }

        ~Entity()
        {
            PN_CORE_CLEAN("Entity destructor called");

            for (auto *component : m_components)
            {
                if (component != nullptr)
                {
                    delete component;
                }
            }
        }

        template <typename T, typename... Args>
        T *AddComponent(Args &&...mArgs)
        {
            T *comp = new T(this, std::forward<Args>(mArgs)...);

            m_components[T::BIT_MASK_INDEX] = comp;
            m_componentCount++;

            return comp;
        }

        template <typename T>
        T *GetComponent()
        {
            return (T *)m_components[T::BIT_MASK_INDEX];
        }

        unsigned int GetEntityID() { return m_ID; };

        void UpdateComponents();
        void UpdateComponentsImGui();
        void CleanComponentVector();
    };

    class Container
    {
    private:
        // All the components in one array
        std::vector<Entity *> m_entities;

    public:
        unsigned int m_IDCounter;

        Container(int initialSize);
        ~Container();

        Entity *AddEntity();

        void UpdateComponents();
        void RenderImGuiComponents();
        void ClearScene();
    };
} // namespace pn
