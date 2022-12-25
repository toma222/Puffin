
#include "Application.h"

extern Puffin::Application* CreateApplication();

int main(){
    // Ask for application
    Puffin::Application *app = CreateApplication();

    // Get this show on the road
    app->StartApplication();

    delete app;
}
