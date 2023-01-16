
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
        std::shared_ptr<Window> m_window;
        std::shared_ptr<Graphics> m_graphics;
        std::shared_ptr<LayerStack> m_layerStack;

        Gui *m_currentGUI;

        static Application *s_Instance;

    public:
        virtual void StartApplication();

        std::shared_ptr<LayerStack> GetLayerStack() { return m_layerStack; };
        std::shared_ptr<Graphics> GetGraphics() { return m_graphics; };
        std::shared_ptr<Window> GetWindow() { return m_window; };

        static Application &Get() { return *s_Instance; };

        Application();
        ~Application();
    };
} // namespace puffin
