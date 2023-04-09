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

        ImGui::Selectable("T Gizm", &m_showTransformGizmos, 0, ImVec2(50, 20));

        ImGui::End();
    }

    void GizmosPanel::RenderEntityGizmos(puffin::Entity entity)
    {
        puffin::components::Transform &t = entity.GetComponent<puffin::components::Transform>();

        Gizmos::ChangeEditorColor({0, 255, 0});
        antarctica::Gizmos::PlaceSquare(t.m_rect.x, t.m_rect.y, t.m_rect.w, t.m_rect.h);

        if (m_showTransformGizmos)
        {
            Gizmos::ChangeEditorColor({255, 0, 0});
            int xMid = t.m_rect.x + (t.m_rect.w / 2);
            int yMid = t.m_rect.y + (t.m_rect.h / 2);
            Gizmos::PlaceLine(xMid, yMid, xMid + m_transformGizmoLength, yMid);

            Gizmos::ChangeEditorColor({0, 0, 255});
            Gizmos::PlaceLine(xMid, yMid, xMid, yMid - m_transformGizmoLength);
        }
    }
} // namespace antarctica
