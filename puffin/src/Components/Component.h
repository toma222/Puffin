#pragma once

#include "core/Core.h"

namespace puffin
{
    namespace components
    {
        class Component
        {
        private:
            const static int32_t BIT_MASK_INDEX = -1;

        public:
            virtual void UpdateComponent();
            virtual void UpdateComponentImGui();
            virtual void StartComponent();
            // virtual ~Component() = default;
        };
    } // namespace components

} // namespace pn
