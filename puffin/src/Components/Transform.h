
#include "Core/Container.h"
#include "Core/ID.h"

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

            static PUFFIN_ID COMPONENT_ID;

        public:
            void UpdateComponent() override;
            void StartComponent() override;
            void UpdateComponentImGui() override;
            PUFFIN_ID GetID() override { return COMPONENT_ID; };

            void Translate(int x, int y);

            Entity *m_entity;

            Transform(Entity *entity, int x, int y, int w, int h);

            ~Transform() override;
        };

        } // namespace components

} // namespace puffin
