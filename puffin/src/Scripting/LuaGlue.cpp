
#include "LuaGlue.h"
#include "LuaScripting.h"

#include "Core/Logging.h"

#include "Math/PNVector.h"

#include "Scene/Components.h"
#include "Scene/Scene.h"
#include "Scene/Entity.h"

#include "SDL2/SDL.h"

namespace puffin
{
#define ADD_INTERNAL_LUA_CALL(name) lib.set_function(#name, &name)

    static const void DebugPrint()
    {
        PN_CORE_INFO("Hello from debug.print");
    }

    static const bool IsKeyPressed(int keycode)
    {
        const Uint8 *state = SDL_GetKeyboardState(nullptr);

        if (state[keycode] || state[keycode])
            return true;

        return false;
    }

    void
    LoadClasses(sol::state_view lua)
    {
        lua.new_usertype<Vector2>("Vector2",
                                  sol::constructors<Vector2(), Vector2(double, double)>(),
                                  "x",
                                  sol::property(&Vector2::x, &Vector2::x),
                                  "y",
                                  sol::property(&Vector2::y, &Vector2::y));

        lua.new_usertype<SDL_Rect>("Rectangle",
                                   "x",
                                   &SDL_Rect::x,
                                   "y",
                                   &SDL_Rect::y,
                                   "w",
                                   &SDL_Rect::w,
                                   "h",
                                   &SDL_Rect::h);

        sol::usertype entity = lua.new_usertype<Entity>("Entity");
        entity["GetName"] = &Entity::GetName;
        entity["GetUUID"] = &Entity::GetUUIDInt;

        auto getTransform = &Entity::GetComponent<components::Transform>;
        entity["GetComponent"] = sol::overload(getTransform);

        auto newImage = &Entity::AddComponent<components::Image, std::string>;
        entity["AddComponent"] = sol::overload(newImage);

        sol::usertype transform = lua.new_usertype<components::Transform>("Transform");
        transform["Translate"] = [](components::Transform &t, int x, int y)
        {
            t.m_rect->x += x;
            t.m_rect->y += y;
        };

        transform["GetRect"] = [](components::Transform &t)
        {
            return t.m_rect;
        };
    }

    sol::table LoadLibTable(sol::this_state s)
    {
        sol::state_view lua(s);
        sol::table lib = lua.create_table();

        ADD_INTERNAL_LUA_CALL(DebugPrint);
        ADD_INTERNAL_LUA_CALL(IsKeyPressed);

        LoadClasses(lua);

        return lib;
    }

    void LuaGlue::LoadInternal(sol::state &lua)
    {
        PN_CORE_INFO("Loading internal calls for a lua script");
        lua.require("puffin", sol::c_call<decltype(&LoadLibTable), &LoadLibTable>);
    }
} // namespace puffin
