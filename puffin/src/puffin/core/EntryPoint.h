#pragma once

#include "Application.h"
#include "Logging.h"

extern Puffin::Application *CreateApplication();

int main()
{
    // Ask for application
    Puffin::Application *app = CreateApplication();

    // Get this show on the road
    app->StartApplication();

    // Delete this show :(
    delete app;
}
