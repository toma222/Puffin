
#include "Entity.h"

namespace puffin
{
    Entity::Entity(Scene *scene, entt::entity entity)
        : m_sceneRef(scene), m_entity(entity){};

} // namespace puffin
