
#pragma once

#define PN_BUILD_DLL 1

#include "base.h"
#include "Window.h"
#include "Logging.h"

#include "puffin/graphics/Graphics.h"
#include "puffin/graphics/Context.h"
// #include "Layer.h"
#include "LayerStack.h"

#include <cstdio>
#include <string>
#include <iostream>
#include <memory>

namespace PN
{
    // Make logging for the entire engine

    class PUFFIN_API Application
    {
    public:
        Window *m_window;
        LayerStack m_layers;

    private:
        bool m_Open;

    public:
        Application();
        ~Application();

        // Starts current application
        // only returns on exit or error
        void StartApplication();

        // Makes external things like the renderer and the context
        void InitExternal();

        // Sets the window
        // This just makes sure that we have the correct window for the job
        template <typename T>
        void SetWindow()
        {
            // Runtime polymorphism is very cool
            m_window = new T;
        };
    };
} // namespace Puffin
