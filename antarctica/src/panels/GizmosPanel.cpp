#include <memory>

#include "GizmosPanel.h"
#include "../tools/Gizmos.h"

#include "puffin.h"

#include <imgui/imgui.h>

namespace antarctica
{
    void GizmosPanel::AttachContext(std::shared_ptr<puffin::Scene> sceneRef)
    {
        m_sceneRef = sceneRef;
    }

    void GizmosPanel::RenderGizmosPanel()
    {
        ImGui::Begin("Gizmos Settings");

        ImGui::End();
    }

    void GizmosPanel::RenderEntityGizmos(puffin::Entity entity)
    {
        puffin::components::Transform &t = entity.GetComponent<puffin::components::Transform>();
        antarctica::Gizmos::PlaceSquare(t.m_rect->x, t.m_rect->y, t.m_rect->w, t.m_rect->h);
    }
} // namespace antarctica
