
#include <memory>
#include "puffin.h"

namespace antarctica
{
    class GizmosPanel
    {
    private:
        std::shared_ptr<puffin::Scene> m_sceneRef;
        bool m_showTransformGizmos;

    public:
        int m_transformGizmoLength;

    public:
        void AttachContext(std::shared_ptr<puffin::Scene> sceneRef);

        void RenderEntityGizmos(puffin::Entity entity);
        void RenderGizmosPanel();
    };
} // namespace antarctica
