#include "Core/Container.h"

#include "Component.h"

#include "Rendering/PTexture.h"

namespace puffin
{
    namespace components
    {
        class Image : public Component
        {
        private:
            render::SDLTexture *m_texture;

        public:
            const static int32_t BIT_MASK_INDEX = 1;

        public:
            // Looks at the transform for it's scale and position
            void UpdateComponent() override;
            void StartComponent() override;
            void UpdateComponentImGui() override;

            Entity *m_entity;

            Image(Entity *entity, std::string path, int layer);
            ~Image() override;
        };
    } // namespace components

} // namespace puffin
