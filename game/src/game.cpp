
#include <puffin.h>

#include <cstdio>

// This function is called as an extern to the engine
// Called in file puffin\src\puffin\EntryPoint.h
Puffin::Application* CreateApplication(){
    Puffin::Application *app = new Puffin::Application;

    return app;
}
