#pragma once

#include "Base.h"
#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <string>

namespace PN
{
    typedef struct PUFFIN_API
    {
        int width;
        int height;
        std::string name;
    } WindowProporties;

    // Contains the genaric functions for running the window
    // Window runs independitly from the renderer and other things
    class PUFFIN_API Window
    {
    private:
        WindowProporties m_proporties;

    public:
        // Updates the window, usualy entails polling for events
        virtual void UpdateWindow();

        // Initilizes the window and the properties class
        virtual void InitWindow(std::string name);

        // Clears the window and sets it back to black
        virtual void ClearWindow();

        // Checks if it needs to close
        virtual int ShouldClose();

        // Gets the current IO inputs like keyboard and mouse
        virtual void GetIO();

        // Returns width
        virtual int GetWidth();

        // Returns height
        virtual int GetHeight();

        // Frees all pointers and destoys the window
        virtual void CleanWindow();

        // Sets vsync on and off (vsync set to the monitors Hz)
        virtual void SetVSync(bool onOff);
    };
} // namespace PN
