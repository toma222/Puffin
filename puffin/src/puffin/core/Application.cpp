
#include "Application.h"
#include "base.h"

#include <cstdio>
#include <string>

namespace PN
{
    Application::Application()
    {
        // Setting up the application
        m_Open = false;
    }
    
    Application::~Application()
    {
        // Shuts down the application
    }

    void Application::StartApplication()
    {
        //m_log->LogTrace("Application loop started");
        PN_CORE_TRACE("Application loop started");

        while (m_Open == true)
        {
            // Open
        }

        //pLog->LogTrace("Closing Application");
    }
} // namespace Puffin


