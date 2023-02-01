
#include "Core/Container.h"
#include "Core/ID.h"

#include "Component.h"

#include <SDL2/SDL.h>

#include "Script.h"
#include "Transform.h"

namespace puffin
{
    namespace components
    {
        PUFFIN_ID Script::COMPONENT_ID = IDGenerator::Get().GetRandomID();

        void Script::StartComponent()
        {
            m_luaInstance->CallFunction("start");
        }

        void Script::UpdateComponentImGui()
        {
        }

        void Script::UpdateComponent()
        {
            m_luaInstance->CallFunction("update");
            // m_entity->GetComponent<components::Transform>()->Translate(m_luaInstance->GetGlobalNumber("transformX"), 0);
        }

        Script::Script(Entity *entity, std::string src)
        {
            m_luaInstance = std::make_unique<LuaContext>(src.c_str(), entity);

            // Set the objects transform as a global
            someData = new int(1);
            m_luaInstance->AddGlobalNumber("transformX", 0);
            // m_luaInstance->PushGlobalPointer<int>(someData, "x");

            m_entity = entity;
            if (COMPONENT_ID == 0)
                COMPONENT_ID = IDGenerator::Get().GetRandomID();
        }

        Script::~Script()
        {
        }
    }
}
