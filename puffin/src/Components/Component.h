#pragma once

#include "Core/Core.h"
#include "Core/Logging.h"

namespace puffin
{
    namespace components
    {
        class Component
        {
        private:
            const static int32_t BIT_MASK_INDEX = -1;

        public:
            virtual void UpdateComponent(){ return; };
            virtual void UpdateComponentImGui(){ return; };
            virtual void StartComponent(){ return; };
            // virtual ~Component() = default;

            virtual ~Component() = default;

            //{
            //    PN_CORE_CLEAN("Destroying Component");
            //}
        };
    } // namespace components

} // namespace pn
