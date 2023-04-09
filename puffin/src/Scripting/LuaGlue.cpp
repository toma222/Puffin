
#include "LuaGlue.h"
#include "LuaScripting.h"

#include "Core/Logging.h"

#include "Math/PNVector.h"

namespace puffin
{
#define ADD_INTERNAL_LUA_CALL(name) lib.set_function(#name, &name)

    static const void DebugPrint()
    {
        PN_CORE_INFO("Hello from debug.print");
    }

    sol::table LoadLibTable(sol::this_state s)
    {
        sol::state_view lua(s);
        sol::table lib = lua.create_table();

        ADD_INTERNAL_LUA_CALL(DebugPrint);

        // INTERNAL STRUCTS AND CLASSES
        lua.new_usertype<Vector2>("Vector2",
                                  sol::constructors<Vector2(), Vector2(double, double)>(),
                                  "x",
                                  sol::property(&Vector2::x, &Vector2::x),
                                  "y",
                                  sol::property(&Vector2::y, &Vector2::y));

        return lib;
    }

    void LuaGlue::LoadInternal(sol::state &lua)
    {
        PN_CORE_INFO("Loading internal calls for a lua script");
        lua.require("PuffinInternal", sol::c_call<decltype(&LoadLibTable), &LoadLibTable>);
    }
} // namespace puffin
