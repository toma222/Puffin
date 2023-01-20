#include "Core/Container.h"
#include "Core/ID.h"

#include "Component.h"

#include "Rendering/PTexture.h"

namespace puffin
{
    namespace components
    {
        class Image : public Component
        {
        private:
            std::shared_ptr<render::SDLTexture> m_texture;
            std::string m_filePath;
            std::string m_fileName;

            const PUFFIN_ID COMPONENT_ID = IDGenerator::Get().GetRandomID();

        public:
            // Looks at the transform for it's scale and position
            void UpdateComponent() override;
            void StartComponent() override;
            void UpdateComponentImGui() override;

            Entity *m_entity;

            Image(Entity *entity, std::string path, int layer);
            virtual PUFFIN_ID GetID() { return COMPONENT_ID; };
            ~Image() override;
        };
    } // namespace components

} // namespace puffin
