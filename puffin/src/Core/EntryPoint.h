
#pragma once

#include "Application.h"
#include "ID.h"
#include "Logging.h"
#include "Debug/Instrumentor.h"

extern puffin::Application *CreateApplication();

puffin::IDGenerator puffin::IDGenerator::s_generator;

int main(int argc, char *argv[])
{
    // Asks the engine to make an app with all it's thing
    puffin::Debug debug;

    PN_CORE_INFO("Main function called");
    puffin::Application *app = CreateApplication();

    // Run the app
    PN_CORE_INFO("Starting main application loop, watch out world!");
    app->StartApplication();

    delete app;
    // delete puffin::s_puffinDebug;

    PN_CORE_INFO("Clean up complete, we did well!");

    return 0;
}
