
#pragma once

#include "sol/sol.hpp"

namespace puffin
{
    class LuaGlue
    {

    public:
        static void LoadFunctions();
        static void LoadObjects();
    };
} // namespace puffin
