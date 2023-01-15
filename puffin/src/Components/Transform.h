
#include "Core/Container.h"

#include "Component.h"

namespace puffin
{
    namespace components
    {
        class Transform : public Component
        {
        public:
            float m_x;
            float m_y;
            float m_z;

            const static int32_t BIT_MASK_INDEX = 0;

        public:
            void UpdateComponent() override;
            void StartComponent() override;
            void UpdateComponentImGui() override;

            void Translate(float x, float y, float z);

            Entity *m_entity;

            Transform(Entity *entity, float x, float y, float z)
            {
                m_x = x;
                m_y = y;
                m_z = z;

                m_entity = entity;
            }
        };
    } // namespace components

} // namespace puffin
