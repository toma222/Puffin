
#pragma once

#include "Application.h"
#include "Logging.h"

extern puffin::Application *CreateApplication();

// puffin::Application *puffin::Application::s_Instance = CreateApplication();

int main(int argc, char *argv[])
{
    // Asks the engine to make an app with all it's thing
    PN_CORE_INFO("Main function called");
    puffin::Application *app = CreateApplication();

    // Run the app
    PN_CORE_INFO("Starting main application loop, watch out world!");
    app->StartApplication();

    delete app;

    PN_CORE_CLEAN("Clean up complete, we did well!");

    return 0;
}
