
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"

#include "Core.h"
// #include "Debug/Instrumentor.h"
#include "Container.h"
#include "Logging.h"
#include "ID.h"
#include "Components/Component.h"

#include <memory>
#include <vector>

#include "Components/Transform.h"

namespace puffin
{

    SystemManager *SystemManager::s_instance = nullptr;

    Entity *Container::AddEntity()
    {
        m_IDCounter++;

        Entity *entity = new Entity(m_IDCounter);

        // Every entity needs a transform!!!!
        entity->AddComponent<components::Transform>(0, 0, 100, 100);

        m_entities.push_back(entity);

        return entity;
    }

    void Container::RenderImGuiComponents()
    {
        for (auto &&entities : m_entities)
        {
            if (entities != nullptr)
                entities->UpdateComponentsImGui();
        }
    }

    void Container::UpdateComponents()
    {
        for (auto *e : m_entities)
        {
            if (e != nullptr)
            {
                e->UpdateComponents();
            }
        }
    }

    void Entity::CleanComponentVector()
    {
        m_components.clear();
    }

    Container::Container(int initialSize)
    {
        // PN_PROFILE_FUNCTION("Container", __FILE__);
        m_entities.resize(10);

        m_IDCounter = 0;
    }

    Container::~Container()
    {
        PN_CORE_CLEAN("Container destructor called");

        for (auto &&entities : m_entities)
        {
            delete entities;
        }
    }

    void Container::ClearScene()
    {
        for (auto *entity : m_entities)
        {
            delete entity;
        }

        m_entities.clear();
        m_IDCounter = 0;
    }

    void Entity::UpdateComponentsImGui()
    {
        ImGui::BeginChild(m_ID, ImVec2(320, m_componentCount * 200), true);
        ImGui::Text("Entity ID %i", m_ID);

        for (auto *comp : m_components)
        {
            if (comp != nullptr)
                comp->UpdateComponentImGui();
        }

        ImGui::EndChild();
    }

    void Entity::UpdateComponents()
    {
        for (auto *comp : m_components)
        {
            if (comp != nullptr)
                comp->UpdateComponent();
        }
    }
} // namespace pn
