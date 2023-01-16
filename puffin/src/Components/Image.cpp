
#include "Core/Container.h"
#include "Core/Application.h"
#include "Core/Core.h"

#include "Component.h"

#include "Image.h"

namespace puffin
{
    namespace components
    {
        Image::Image(Entity *entity, std::string path, int layer)
        {
            m_entity = entity;

            // create the texture
            // TODO get the transform's data for the scale
            // new render::SDLTexture(Application::Get().GetGraphics()->GetRenderer(), path, 100, 100); //
            m_texture = new render::SDLTexture(Application::Get().GetGraphics()->GetRenderer().get(), path, 100, 100);

            // Tell the engine to render the texture
            Application::Get()
                .GetGraphics()
                ->AddTextureToQue(m_texture, 0);
        }

        Image::~Image()
        {
            PN_CORE_CLEAN("Image destructor called");
        }

        void Image::UpdateComponent()
        {
        }

        void Image::StartComponent()
        {
        }

        void Image::UpdateComponentImGui()
        {
            ImGui::BeginChild("Image", ImVec2(300, 150), true);

            ImGui::Text("Image Component - COMP ID %i", m_entity->GetEntityID());

            ImGui::EndChild();
        }
    } // namespace components

} // namespace puffin
