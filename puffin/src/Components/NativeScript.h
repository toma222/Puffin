#pragma once

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"

#include "Core/ID.h"
#include "Component.h"

#include "Core/Container.h"
#include "Core/Application.h"
#include "Core/Core.h"

#include "Component.h"
#include "memory.h"

// #define DEFAULT_SCRIPT_BEHAVIOR(name) void name(Entity *m_)

namespace puffin
{
    namespace components
    {
        class NativeScript : public Component
        {
        public:
            static PUFFIN_ID COMPONENT_ID;

        public:
            class Script
            {
            public:
                Entity *entity;
                virtual void Update() { return; };
                virtual void Start() { return; };
            };

            // Looks at the transform for it's scale and position
            void UpdateComponent() override;
            void StartComponent() override;
            void UpdateComponentImGui() override;

            PUFFIN_ID GetID() override { return COMPONENT_ID; };

            Entity *m_entity;

            NativeScript(Entity *entity);
            ~NativeScript() override;

            template <typename T>
            void AttachScript()
            {
                m_script = std::make_unique<T>();
                m_script->entity = m_entity;
                m_script->Start();
            }

        private:
            std::unique_ptr<Script> m_script;
        };
    } // namespace components
} // namespace puffin

#define PN_SCRIPT_MONO puffin::components::NativeScript::Script
