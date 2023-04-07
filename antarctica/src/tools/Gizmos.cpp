
#include "Gizmos.h"
#include "puffin.h"

#include <SDL2/SDL.h>

// ! fix the assert function to remove these if statements
namespace antarctica
{
    bool Gizmos::s_rendering = false;
    puffin::PNColor Gizmos::s_gizmosColor = puffin::PNColor(0, 255, 0);

    void Gizmos::StartGizmosRender()
    {
        if (s_rendering == true)
            PN_CORE_ASSERT(false, "StartGizmosRender when a rendering is true. Maybe you forgot to close a render");

        s_rendering = true;
    }

    void Gizmos::EndGizmosRender()
    {
        if (!s_rendering)
            PN_CORE_ASSERT(false, "EndGizmosRender when rendering is false. You might have forgotten to open a render session");

        s_rendering = false;
    }

    void Gizmos::PlaceSquare(int x, int y, int w, int h)
    {
        // PN_CORE_ASSERT(s_rendering, "s_rendering is false. You forgot to open a Gizmos render session");

        SDL_SetRenderDrawColor(puffin::Graphics::Get().GetRenderer()->get(), s_gizmosColor.m_color[0], s_gizmosColor.m_color[1], s_gizmosColor.m_color[2], 255);
        SDL_RenderDrawRect(puffin::Graphics::Get().GetRenderer()->get(), new SDL_Rect({x, y, w, h}));
        // puffin::Graphics::Get().GetRenderer()->get();
    }

    void Gizmos::PlaceCircle(int r, int px, int py)
    {
        const int arrSize = ((r * 8 * 35 / 49) + (8 - 1)) & -8;
        SDL_Point points[arrSize];
        int drawCount = 0;

        const int32_t diameter = (r * 2);

        int32_t x = (r - 1);
        int32_t y = 0;
        int32_t tx = 1;
        int32_t ty = 1;
        int32_t error = (tx - diameter);

        while (x >= y)
        {
            // Each of the following renders an octant of the circle
            points[drawCount + 0] = {px + x, py - y};
            points[drawCount + 1] = {px + x, py + y};
            points[drawCount + 2] = {px - x, py - y};
            points[drawCount + 3] = {px - x, py + y};
            points[drawCount + 4] = {px + y, py - x};
            points[drawCount + 5] = {px + y, py + x};
            points[drawCount + 6] = {px - y, py - x};
            points[drawCount + 7] = {px - y, py + x};

            drawCount += 8;

            if (error <= 0)
            {
                ++y;
                error += ty;
                ty += 2;
            }

            if (error > 0)
            {
                --x;
                tx += 2;
                error += (tx - diameter);
            }
        }

        SDL_RenderDrawPoints(puffin::Graphics::Get().GetRenderer()->get(), points, drawCount);
    }

    void Gizmos::PlaceLine(int x1, int y1, int x2, int y2)
    {
        SDL_SetRenderDrawColor(puffin::Graphics::Get().GetRenderer()->get(), s_gizmosColor.m_color[0], s_gizmosColor.m_color[1], s_gizmosColor.m_color[2], 255);
        SDL_RenderDrawLine(puffin::Graphics::Get().GetRenderer()->get(), x1, y1, x2, y2);
    }

    void Gizmos::ChangeEditorColor(puffin::PNColor color)
    {
        s_gizmosColor = color;
    }
} // namespace antarctica
