
#pragma once

#define PN_BUILD_DLL 1

#include "base.h"
#include "Logging.h"

#include <cstdio>
#include <string>

namespace PN
{
    class PUFFIN_API Application
    {
    public:
        Application();
        ~Application();

        void StartApplication();
        // Starts current application
        // only returns on exit or error
    private:
        Logging m_log;
        bool m_Open;
    };
} // namespace Puffin

