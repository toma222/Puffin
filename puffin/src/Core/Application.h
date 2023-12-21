
#pragma once

#include "Window.h"
#include "Rendering/Graphics.h"
#include "Gui.h"
#include "LayerStack.h"

#include <iostream>
#include <memory>

namespace puffin
{
    class Application
    {
    private:
        bool m_running;

    public:
        std::shared_ptr<Window> m_window;
        std::shared_ptr<LayerStack> m_layerStack;

        Gui *m_currentGUI;

        static Application *s_Instance;

    public:
        void StartApplication();
        void Exit();

        std::shared_ptr<LayerStack> GetLayerStack() { return m_layerStack; };
        std::shared_ptr<Window> GetWindow() { return m_window; };

        static Application &Get() { return *s_Instance; };

        Application();
        ~Application();
    };
} // namespace puffin
