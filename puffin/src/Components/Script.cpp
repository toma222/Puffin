
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"

#include "Component.h"
#include "Core/ID.h"

#include "Core/Container.h"
#include "Core/Application.h"
#include "Core/Core.h"

#include "Script.h"

namespace puffin
{
    namespace components
    {
        PUFFIN_ID NativeScript::COMPONENT_ID = IDGenerator::Get().GetRandomID();

        NativeScript::NativeScript(Entity *entity)
        {
            m_entity = entity;

            if (COMPONENT_ID == 0)
                COMPONENT_ID = IDGenerator::Get().GetRandomID();
        }

        NativeScript::~NativeScript()
        {
            PN_CORE_CLEAN("NativeScript destructor called");
        }

        void NativeScript::UpdateComponent()
        {
            m_script->Update();
        }

        void NativeScript::StartComponent()
        {
        }

        void NativeScript::UpdateComponentImGui()
        {
            ImGui::BeginChild("NativeScript", ImVec2(300, 150), true);

            ImGui::Text("NativeScript - id %lu", COMPONENT_ID);

            ImGui::EndChild();
        }
    } // namespace components
} // namespace puffin
