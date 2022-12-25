
#include "Application.h"
#include "base.h"

#include <cstdio>
#include <string>

namespace PN
{
    Application::Application()
    {
        // Setting up the application
        m_Open = true;
    }
    
    Application::~Application()
    {
        // Shuts down the application
    }

    void Application::StartApplication()
    {
        m_log.LogProccess("Application loop started");

        while (m_Open == true)
        {
            // Open
        }

        m_log.LogClean("Application closing");
    }
} // namespace Puffin


