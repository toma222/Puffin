
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"

#include "Core/Logging.h"

#include "Component.h"
#include "Script.h"

namespace puffin
{
    namespace components
    {
        Script::Script(Entity *entity)
        {
            m_entity = entity;
        }
        
        Script::~Script()
        {
            PN_CORE_CLEAN("Transform Deconstructor called");
        }

        void Script::UpdateComponent(){
            
        }

        void Script::StartComponent(){

        }

        void Script::UpdateComponentImGui(){
            ImGui::BeginChild("Script", ImVec2(300, 150), true);

            ImGui::EndChild();
        }
    }
}


