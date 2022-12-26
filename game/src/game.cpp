
#include <puffin.h>

#include <cstdio>

namespace Puffin
{
    
} // namespace Puffin


// This function is called as an extern to the engine
// Called in file puffin\src\puffin\EntryPoint.h
// Creates the CONTEXT, WINDOW, and the APPLICATION
Puffin::Application* CreateApplication(){
    GM_CORE_INFO("Making application");
    Puffin::Application *app = new Puffin::Application;

    GM_CORE_INFO("Making window GLFW");
    app->SetWindow<Puffin::GLFWWindow>();

    GM_CORE_INFO("Making context GLFW");
    app->m_graphics->InitGraphicsAPI<Puffin::graphics::GLFWContext>();

    app->InitExternal();
    
    return app;
}
