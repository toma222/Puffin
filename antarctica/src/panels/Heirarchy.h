
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"

#include "puffin.h"
#include <memory>

namespace antarctica
{
    class Heirarchy
    {
    private:
        std::shared_ptr<puffin::Scene> m_sceneRef;
        puffin::Entity m_selectedEntity;

    public:
        Heirarchy() = default;
        ~Heirarchy() = default;

        void AttachContext(std::shared_ptr<puffin::Scene> sceneRef);

        void RenderImGui();
        void RenderSelectedEntityComponents(puffin::Entity entity);
        puffin::Entity GetSelectedEntity();

        template <typename T>
        bool DisplayComponentEntry(const std::string &entryName);
    };
} // namespace antarctica
