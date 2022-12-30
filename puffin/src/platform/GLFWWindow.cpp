
#include "GLFWWindow.h"
#include "puffin/core/Base.h"
#include "puffin/core/Logging.h"

#include <string>

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace PN
{

    void GLFWWindow::UpdateWindow()
    {
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    void GLFWWindow::InitWindow(std::string name)
    {
        m_monitor = glfwGetPrimaryMonitor();

        m_vidMode = glfwGetVideoMode(m_monitor);

        glfwWindowHint(GLFW_RED_BITS, m_vidMode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, m_vidMode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, m_vidMode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, m_vidMode->refreshRate);

        // set fullscreen
        m_window = glfwCreateWindow(m_vidMode->width, m_vidMode->height, name.c_str(), m_monitor, NULL);

        // set the windows properties such that it renders fullscreen
        props.height = m_vidMode->height;
        props.width = m_vidMode->width;

        glfwMakeContextCurrent(m_window);

        gladLoadGL(glfwGetProcAddress);

        // Enable depth
        glEnable(GL_DEPTH_TEST);
    }

    void GLFWWindow::ClearWindow()
    {
        // Clear the current window

        glViewport(0, 0, props.height, props.width);

        // Clear colors and depth buffer
        // I KNOW THAT I SHOULD PROBABLY NOT CLEAR DEPTH UNLESS IT'S ENABLED BUT SHUT UP
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void GLFWWindow::GetIO()
    {
        // Get IO (idk yet)
        // prob going to use for events and mouse and keyboard
    }

    int GLFWWindow::GetWidth()
    {
        // return the width of the current viewport
        return props.width;
    }

    int GLFWWindow::GetHeight()
    {
        // return the height of the current viewport
        return props.height;
    }

    void GLFWWindow::CleanWindow()
    {
        // Delete the window and all it's pointers and such
        PN_CORE_CLEAN("Destroying window");

        // cleans m_window in the proccess
        glfwDestroyWindow(m_window);
        // memory leaks be gone!
    }

    void GLFWWindow::SetVSync(bool onOff)
    {
        // Turn on and off vsync to the current monitor speed
        glfwSwapInterval((int)onOff);
    }

    int GLFWWindow::ShouldClose()
    {
        return glfwWindowShouldClose(m_window);
    }
} // namespace PN
