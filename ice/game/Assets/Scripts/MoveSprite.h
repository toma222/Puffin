
#include <puffin.h>

// STFU i get to do what I want no matter if it is bad practice
using namespace puffin;
using namespace puffin::components;

namespace game
{
    class MoveSprite : public Component
    {
    public:
        const static int32_t BIT_MASK_INDEX = 2;
        Entity *m_entity;

    public:
        MoveSprite(Entity *entity)
        {
            m_entity = entity;
        }

        void UpdateComponent() override{

        }

        void StartComponent() override{

        }

        void UpdateComponentImGui() override{

        }
    };
}

