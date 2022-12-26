
#pragma once

#define PN_BUILD_DLL 1

#include "base.h"
#include "Logging.h"

#include "puffin/graphics/Graphics.h"

#include <cstdio>
#include <string>

namespace PN
{
    // Make logging for the entire engine
    
    class PUFFIN_API Application
    {
    public:
        Application();
        ~Application();

        void StartApplication();
        // Starts current application
        // only returns on exit or error
        Graphics::GLFWContext context;
        
    private:
        bool m_Open;
    };
} // namespace Puffin

