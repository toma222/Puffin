
#include "Entity.h"

namespace puffin
{
    Entity::Entity(Scene *scene, entt::entity entity)
    {
        m_sceneRef = scene;
        entity = m_entity;
    }
} // namespace puffin
