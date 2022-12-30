#pragma once

#include "Application.h"
#include "Logging.h"

extern Puffin::Application *CreateApplication();

int main()
{
    PN_CORE_TRACE("Calling Application extern from entry point");

    // Ask for application
    Puffin::Application *app = CreateApplication();

    // Get this show on the road
    app->StartApplication();

    // Delete this show :(
    delete app;
}
