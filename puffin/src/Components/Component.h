#pragma once

#include "core/Core.h"
#include "Core/Logging.h"
#include "Core/ID.h"

namespace puffin
{
    namespace components
    {
        class Component
        {
        private:
            

        public:
            virtual void UpdateComponent();
            virtual void UpdateComponentImGui();
            virtual void StartComponent();
            virtual PUFFIN_ID GetID();
            // virtual ~Component() = default;

            virtual ~Component() = default;

            const PUFFIN_ID COMPONENT_ID = 1;

            //{
            //    PN_CORE_CLEAN("Destroying Component");
            //}
        };
    } // namespace components

} // namespace pn
