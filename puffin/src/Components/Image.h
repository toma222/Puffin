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

            static PUFFIN_ID COMPONENT_ID;

        public:
            // Looks at the transform for it's scale and position
            void UpdateComponent() override;
            void StartComponent() override;
            void UpdateComponentImGui() override;

            PUFFIN_ID GetID() override
            {
                if (COMPONENT_ID == 0)
                {
                    COMPONENT_ID = IDGenerator::Get().GetRandomID();
                }

                return COMPONENT_ID;
            };

            Entity *m_entity;

            Image(Entity *entity, std::string path, int layer);
            ~Image() override;
        };
    } // namespace components

} // namespace puffin
