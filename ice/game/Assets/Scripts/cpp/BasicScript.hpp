
#include <puffin.h>

using namespace puffin;

class BasicScript : public PN_SCRIPT_MONO
{
    components::Transform *transform;
    int speed = 4;

    void Start() override
    {
        transform = entity->GetComponent<components::Transform>();
    }

    void Update() override
    {
        if (Input::KeyDown(SDL_SCANCODE_D))
        {
            transform->Translate(speed, 0);
        }

        if (Input::KeyDown(SDL_SCANCODE_A))
        {
            transform->Translate(-speed, 0);
        }
    }
};