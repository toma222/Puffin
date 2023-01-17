
#include "Core/Container.h"
#include "Component.h"

namespace puffin
{
    namespace components
    {
        class Script : public Component
        {
        public:
            const static int32_t BIT_MASK_INDEX = 2;
            Entity *m_entity;
            
        public:
            virtual void UpdateComponent();
            virtual void StartComponent();
            virtual void UpdateComponentImGui();

            Script(Entity *entity);
            ~Script();
        };
    }
}
