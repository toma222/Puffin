
#include "Base.h"
#include <string>
#include <GLFW/glfw3.h>

namespace PN
{
    typedef struct PUFFIN_API
    {
        int width;
        int height;
        std::string name;
    } WindowProporties;


    class PUFFIN_API Window
    {
    public:
        Window();
        ~Window();

        virtual void UpdateWindow();
        virtual void ClearWindow();

        virtual void GetIO();

        virtual void GetWidth();
        virtual void GetHeight();

        virtual void CleanWindow();
        virtual void SetVSync(bool onOff);
    };
} // namespace PN
