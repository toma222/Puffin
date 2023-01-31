
#include "Core/Container.h"

namespace puffin
{
    class PhysicsSystem : public System
    {
    public:
        // PUFFIN_ID requiredComponents[5];
        static PUFFIN_ID requiredComponents;
        std::vector<Entity *> m_currentComponents;

    public:
        void Start() override;
        void Update() override;
        void OnImGuiUpdate() override;
    };
} // namespace puffin
