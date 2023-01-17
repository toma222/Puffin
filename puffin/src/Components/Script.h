
#include "Component.h"

namespace puffin
{
    namespace components
    {
        class Script : public Component
        {
        public:
            const static int32_t BIT_MASK_INDEX = 1;
            /* data */
        public:
            void UpdateComponent() override;
            void StartComponent() override;
            void UpdateComponentImGui() override;

            Script(/* args */);
            ~Script();
        };
    }
}
