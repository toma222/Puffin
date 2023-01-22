
#include "Core/Container.h"
#include "Core/ID.h"

#include "Component.h"

#include <SDL2/SDL.h>

#include "Script.h"

namespace puffin
{
    namespace components
    {
        PUFFIN_ID Script::COMPONENT_ID = 0;

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
        }

        Script::Script(Entity *entity, std::string src)
        {
            m_luaInstance = std::make_unique<LuaContext>(src.c_str());

            m_entity = entity;
            if (COMPONENT_ID == 0)
                COMPONENT_ID = IDGenerator::Get().GetRandomID();
        }

        Script::~Script()
        {
        }
    } // namespace components

} // namespace puffin
