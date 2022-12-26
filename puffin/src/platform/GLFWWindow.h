#pragma once

#include "puffin/core/Base.h"
#include "puffin/core/Window.h"

#include <GLFW/glfw3.h>

namespace PN
{   
    
    class PUFFIN_API GLFWWindow : public Window
    {
    private:
        GLFWmonitor *m_monitor;
        GLFWwindow *m_window;
        const GLFWvidmode *m_vidMode;

    private:
        WindowProporties props;
        
    public:
        void UpdateWindow() override;
        void ClearWindow() override;
        void InitWindow(std::string name) override;
        int ShouldClose() override;

        void GetIO() override;

        int GetWidth() override;
        int GetHeight() override;

        void CleanWindow() override;
        void SetVSync(bool onOff) override;
    };    
} // namespace PN

