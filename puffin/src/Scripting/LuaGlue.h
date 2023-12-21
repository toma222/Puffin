
#pragma once

#include "sol/sol.hpp"

namespace puffin
{
    class LuaGlue
    {
    public:
        static void LoadInternal(sol::state &lua);
    };
} // namespace puffin
