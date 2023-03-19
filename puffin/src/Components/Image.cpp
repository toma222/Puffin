
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
        PUFFIN_ID Image::COMPONENT_ID = IDGenerator::Get().GetRandomID();

        Image::Image(Entity *entity, std::string path, int layer)
        {
            m_entity = entity;
            m_filePath = path;

            m_texture = std::make_shared<render::SDLSurface>(path.c_str(), 192, 108);

            Application::Get()
                .GetGraphics()
                ->AddTextureToQue(m_texture);

            m_fileName = GetLastSplitString(path, "").c_str();

            if (COMPONENT_ID == 0)
                COMPONENT_ID = IDGenerator::Get().GetRandomID();
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

            ImGui::Text("Image - id %lu", COMPONENT_ID);
            ImGui::Text("file path -> %s", m_filePath.c_str());
            ImGui::Text("file name -> %s", m_fileName.c_str());

            ImGui::EndChild();
        }
    } // namespace components

} // namespace puffin
