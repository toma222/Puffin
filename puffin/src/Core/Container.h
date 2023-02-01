
#pragma once

#include "Core.h"
#include "Logging.h"
#include "ID.h"
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

        bool HasComponent(PUFFIN_ID id)
        {
            for (auto *comp : m_components)
            {
                if (comp != nullptr)
                {
                    if (comp->COMPONENT_ID == id)
                    {
                        return true;
                    }
                }
            }

            return false;
        }

        template <typename T, typename... Args>
        T *AddComponent(Args &&...mArgs)
        {
            T *comp = new T(this, std::forward<Args>(mArgs)...);

            m_components[m_componentCount] = (components::Component *)comp;
            m_componentCount++;

            return comp;
        }

        template <typename T>
        T *GetComponent()
        {
            for (auto *c : m_components)
            {
                if (c != nullptr)
                {
                    if (c->GetID() == T::COMPONENT_ID)
                    {
                        return (T *)c;
                    }
                }
            }

            return nullptr;
        }

        unsigned int GetEntityID() { return m_ID; };

        void UpdateComponents();
        void UpdateComponentsImGui();
        void CleanComponentVector();
    };

    class Component
    {
    public:
        const PUFFIN_ID COMPONENT_ID = 1;

    public:
        virtual void UpdateComponent();
        virtual void UpdateComponentImGui();
        virtual void StartComponent();
        virtual PUFFIN_ID GetID();

        virtual ~Component() = default;
    };

    class System
    {
    public:
        std::vector<Entity *> m_currentComponents;
        std::vector<PUFFIN_ID> m_requiredComponents;

        virtual void Start() { return; };
        virtual void Update() { return; };
        virtual void OnImGuiUpdate() { return; };

        virtual ~System() = default;

        void CheckComponent(PUFFIN_ID componentID, Entity *entity)
        {
            int check = 0; // m_requiredComponents.size();

            for (auto id : m_requiredComponents)
            {
                if (id == componentID)
                {
                    check++;
                    return;
                }
            }

            if (check >= (int)m_currentComponents.size())
                m_currentComponents.push_back(entity);
        }
    };

    class SystemManager
    {
    private:
        static SystemManager *s_instance;
        std::vector<std::shared_ptr<System>> m_systems;

        SystemManager()
        {
            PN_CORE_TRACE("System manager created");
        }

    public:
        SystemManager(const SystemManager &obj) = delete;

        static SystemManager *Get()
        {
            if (s_instance == nullptr)
            {
                s_instance = new SystemManager();
                return s_instance;
            }
            else
            {
                return s_instance;
            }
        }

        template <typename T, typename... Args>
        std::shared_ptr<T> AddSystem(Args &&...mArgs)
        {
            std::shared_ptr<T> sys = std::make_shared<T>(std::forward<Args>(mArgs)...);
            // m_systems.push_back(sys);
            return sys;
        }
    };

    class Container
    {
    private:
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
