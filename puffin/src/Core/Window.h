
#pragma once

#include <memory>

#include "Rendering/PRenderer.h"
#include "Rendering/PWindow.h"

namespace puffin
{
    // In charge of the window and such
    class Window
    {
    private:
        struct WindowProperties
        {
            int m_width;
            int m_height;
        };

        struct WindowProperties m_props;
        render::SDLWindow *m_window;

    public:
        Window();

        int getWidth() { return m_props.m_width; };
        int getHeight() { return m_props.m_height; };

        render::SDLWindow *GetWindow() { return m_window; };

        void UpdateWindow();

        ~Window();
    };

}
