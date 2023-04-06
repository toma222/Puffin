
#include "Gizmos.h"
#include "puffin.h"

#include <SDL2/SDL.h>

// ! fix the assert function to remove these if statements
namespace antarctica
{
    bool Gizmos::s_rendering = false;
    puffin::PNColor Gizmos::s_gizmosColor = puffin::PNColor(0,255,0);

    void Gizmos::StartGizmosRender()
    {
        if(s_rendering == true)
            PN_CORE_ASSERT(false, "StartGizmosRender when a rendering is true. Maybe you forgot to close a render");
        

        s_rendering = true;
    }

    void Gizmos::EndGizmosRender()
    {
        if(!s_rendering)
            PN_CORE_ASSERT(false, "EndGizmosRender when rendering is false. You might have forgoten to open a render session");

        s_rendering = false;
    }

    void Gizmos::PlaceSquare(int x, int y, int w, int h)
    {
        //PN_CORE_ASSERT(s_rendering, "s_rendering is false. You forgot to open a Gizmos render session");

        SDL_SetRenderDrawColor(puffin::Graphics::Get().GetRenderer()->get(), s_gizmosColor.m_color[0], s_gizmosColor.m_color[1], s_gizmosColor.m_color[2], 255);
        SDL_RenderDrawRect(puffin::Graphics::Get().GetRenderer()->get(), new SDL_Rect({x,y,w,h}));
        //puffin::Graphics::Get().GetRenderer()->get();
    }
} // namespace antarctica
