
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"

#include "Core.h"
#include "Container.h"
#include "Logging.h"
#include "Components/Component.h"

#include <memory>
#include <vector>

#include "Components/Transform.h"

namespace puffin
{
    Container::Container(int initialSize)
    {
        PN_CORE_INFO("Container Constructor called");
        m_entities.resize(10);

        m_IDCounter = 0;
    }

    Entity *Container::AddEntity()
    {

        m_IDCounter++;

        Entity *entity = new Entity(m_IDCounter);

        entity->AddComponent<components::Transform>((float)0, (float)0, (float)0);

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

        // m_entities[0]->UpdateComponentsImGui();
    }

    void Container::UpdateComponents()
    {
        // for (size_t i = 0; i < m_pool.size(); i++)
        //{
        //     if (m_pool[i] != NULL)
        //     {
        //         // Update the component
        //         m_pool[i]->UpdateComponent();
        //     }
        // }
    }

    void Entity::UpdateComponentsImGui()
    {
        ImGui::BeginChild(m_ID, ImVec2(320, m_componentCount * 160), true);
        ImGui::Text("Entity ID %i", m_ID);

        // for (auto &&comp : m_components)
        // {
        //     if (comp != nullptr)
        //         comp->UpdateComponentImGui();
        // }

        m_components[0]->UpdateComponentImGui();

        ImGui::EndChild();
    }
} // namespace pn
