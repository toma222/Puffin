
#include <puffin.h>

using namespace puffin;

class BasicScript : public PN_SCRIPT_MONO
{
    // public:
    components::Transform *transform;

    void Start() override
    {
        printf("hello from native script\n");
        transform = entity->GetComponent<components::Transform>();
    }

    void Update() override
    {
        transform->Translate(1, 0);
    }
};