
#include "Core/Container.h"
#include "Core/Application.h"
#include "Core/Core.h"

#include "Component.h"
#include "Transform.h"

#include "Image.h"

// Goes back to front
std::string GetLastSplitString(std::string str, const char *separator)
{
    std::string ret = "";

    for (int ch = str.size() - 1; ch >= 0; ch--)
    {
        if (str.c_str()[ch] == '/')
        {
            ret.append(&str.c_str()[ch + 1]);
            return ret;
        }
    }

    return ret;
}

namespace puffin
{
    namespace components
    {
        Image::Image(Entity *entity, std::string path, int layer)
        {
            m_entity = entity;
            m_filePath = path;

            // create the texture
            // TODO get the transform's data for the scale
            // new render::SDLTexture(Application::Get().GetGraphics()->GetRenderer(), path, 100, 100); //
            m_texture = std::make_shared<render::SDLTexture>(m_entity->GetComponent<Transform>()->transformRect, Application::Get().GetGraphics()->GetRenderer().get(), path, 100, 100);

            // Attach the texture rect
            // m_texture->SetSDLRect(&m_entity->GetComponent<Transform>()->transformRect
            // Tell the engine to render the texture
            Application::Get()
                .GetGraphics()
                ->AddTextureToQue(m_texture, 0);

            m_fileName = GetLastSplitString(path, "").c_str();
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
            ImGui::Text("file path -> %s", m_filePath.c_str());
            ImGui::Text("file name -> %s", m_fileName.c_str());

            ImGui::EndChild();
        }
    } // namespace components

} // namespace puffin
