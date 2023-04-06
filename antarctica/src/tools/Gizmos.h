
#pragma once

#include "puffin.h"

namespace antarctica
{
    class Gizmos
    {
    private:
        static bool s_rendering;
        static puffin::PNColor s_gizmosColor;

    public:
        static void StartGizmosRender();
        static void EndGizmosRender();

        static void PlaceSquare(int x, int y, int w, int h);
        static void PlaceCircle(int r, int px, int py);
    };
} // namespace antarctica
