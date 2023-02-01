
#include "Core/Container.h"

namespace puffin
{
    class PhysicsSystem : public System
    {
    public:
        std::vector<Entity *> m_currentComponents;
        std::vector<PUFFIN_ID> m_requiredComponents;

        PhysicsSystem()
        {
            return;
        }

        ~PhysicsSystem() override
        {
            return;
        }

        void Start() override;
        void Update() override;
        void OnImGuiUpdate() override;
    };
} // namespace puffin
