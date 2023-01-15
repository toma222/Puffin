
#pragma once

#include "Window.h"
#include "Graphics.h"
#include "Gui.h"
#include "LayerStack.h"

#include <iostream>
#include <memory>

namespace puffin
{

    // In charge of runtime and takes care of upkeep on all the systems required for rendering
    // things it currently holds
    // - the window
    // - the graphics
    // - the imgui context
    class Application
    {
    protected:
        // std::unique_pointer<Window> window;
        std::unique_ptr<Window> m_window;
        // std::unique_ptr<Graphics> m_graphics;
        Graphics *m_graphics;
        LayerStack *m_layerStack;

        Gui *m_currentGUI;

        static Application *s_Instance;

    public:
        virtual void StartApplication();

        LayerStack *GetLayerStack() { return m_layerStack; };

        static Application &Get() { return *s_Instance; };

        // no touchy :(
        Graphics *GetGraphics() { return m_graphics; };

        Application();
        ~Application();
    };
} // namespace puffin
