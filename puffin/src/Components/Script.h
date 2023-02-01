
#pragma once

#include "Core/Container.h"
#include "Core/ID.h"

#include "Component.h"
#include "Transform.h"

#include "Scripting/LuaGlue.h"

#include <SDL2/SDL.h>

namespace puffin
{
    namespace components
    {
        class Script : public Component
        {
        private:
            std::unique_ptr<LuaContext> m_luaInstance;

            static PUFFIN_ID COMPONENT_ID;

        public:
            void UpdateComponent() override;
            void StartComponent() override;
            void UpdateComponentImGui() override;

            PUFFIN_ID GetID() override
            {
                if (COMPONENT_ID == 0)
                {
                    COMPONENT_ID = IDGenerator::Get().GetRandomID();
                }

                return COMPONENT_ID;
            };

            Entity *m_entity;

            int *someData;

            Script(Entity *entity, std::string src);
            ~Script() override;
        };
    } // namespace components

} // namespace puffin
