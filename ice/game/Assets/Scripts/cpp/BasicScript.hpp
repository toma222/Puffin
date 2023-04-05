
#include <puffin.h>

class BasicScript : public puffin::NativeScript
{
public:
    BasicScript()
    {
        printf("script\n");
    }

    ~BasicScript()
    {
        printf("destroy script\n");
    }

    void OnUpdate()
    {
        
    }
};