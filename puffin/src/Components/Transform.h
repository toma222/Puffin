
#include "Core/Container.h"

#include "Component.h"

#include <SDL2/SDL.h>

namespace puffin
{
    namespace components
    {
        class Transform : public Component
        {
        public:
            int layer;
            std::shared_ptr<SDL_Rect> transformRect;

            const static int32_t BIT_MASK_INDEX = 0;

        public:
            void UpdateComponent() override;
            void StartComponent() override;
            void UpdateComponentImGui() override;

            void Translate(int x, int y);

            Entity *m_entity;

            Transform(Entity *entity, int x, int y, int w, int h);
            ~Transform() override;
        };
    } // namespace components

} // namespace puffin
