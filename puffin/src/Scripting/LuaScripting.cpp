
#include "LuaScripting.h"
#include "sol/sol.hpp"

namespace puffin
{
    LuaScript::LuaScript(std::string path, std::string moduleName)
    {
        PN_CORE_INFO("Starting lua script");
        m_moduleName = moduleName;
        m_path = path;

        m_luaState.open_libraries(sol::lib::base, sol::lib::package);

        // m_luaState.script_file("C:/Users/Aidan/Documents/OtherUsslessProjects'/Puffin/ice/assets/Scripts/Scroll.lua");
    }

    sol::state LuaScripting::s_globalState = sol::state();

    void LuaScripting::InitLuaScripting()
    {
        s_globalState.open_libraries(sol::lib::base, sol::lib::package);
    }

    void LuaScripting::RegisterModule(LuaScript &script)
    {
        s_globalState.require_file(script.m_moduleName.c_str(), script.m_path.c_str());
    }

    void LuaScripting::CallGlobalFunction(const char *functionName)
    {
        s_globalState[functionName]();
    }

    void LuaScripting::CallLoadedModuleFunction(const char *module, const char *function)
    {
        s_globalState[module][function]();
    }
}
