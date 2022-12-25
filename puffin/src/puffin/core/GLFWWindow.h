
#include "Base.h"
#include "Window.h"

namespace PN
{
    class PUFFIN_API GLFWWindow : Window
    {
    private:
        /* data */
    public:
        GLFWWindow(/* args */);
        ~GLFWWindow();

        void UpdateWindow() override;
        void ClearWindow() override;

        void GetIO() override;

        void GetWidth() override;
        void GetHeight() override;

        void CleanWindow() override;
        void SetVSync(bool onOff) override;
    };    
} // namespace PN

