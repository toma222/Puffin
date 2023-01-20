
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

            const PUFFIN_ID COMPONENT_ID = IDGenerator::Get().GetRandomID();

        public:
            void UpdateComponent() override;
            void StartComponent() override;
            void UpdateComponentImGui() override;

            void Translate(int x, int y);

            Entity *m_entity;

            Transform(Entity *entity, int x, int y, int w, int h);
            virtual PUFFIN_ID GetID() { return COMPONENT_ID; };
            ~Transform() override;
        };
    } // namespace components

} // namespace puffin
