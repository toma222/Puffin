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
        // Updates the window, usualy entails polling for events
        void UpdateWindow() override;

        // Initilizes the window and the properties class
        void InitWindow(std::string name) override;

        // Clears the window and sets it back to black
        void ClearWindow() override;

        // Checks if it needs to close
        int ShouldClose() override;


        // Gets the current IO inputs like keyboard and mouse
        void GetIO() override;


        // Returns width
        int GetWidth() override;

        // Returns height
        int GetHeight() override;
        

        // Frees all pointers and destoys the window
        void CleanWindow() override;

        // Sets vsync on and off (vsync set to the monitors Hz)
        void SetVSync(bool onOff) override;
    };    
} // namespace PN

