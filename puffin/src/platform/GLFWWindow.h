
#include "puffin/core/Base.h"
#include "puffin/core/Window.h"

namespace PN
{   
    
    class PUFFIN_API GLFWWindow : Window
    {
    public:
        void UpdateWindow() override;
        void ClearWindow() override;
        void InitWindow() override;

        void GetIO() override;

        void GetWidth() override;
        void GetHeight() override;

        void CleanWindow() override;
        void SetVSync(bool onOff) override;
    };    
} // namespace PN

