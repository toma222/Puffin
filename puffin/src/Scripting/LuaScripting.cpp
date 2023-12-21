
#include "LuaScripting.h"
#include "sol/sol.hpp"

namespace puffin
{
    LuaScript::LuaScript(std::string path, std::string moduleName)
    {
        PN_CORE_INFO("Starting lua script");
        m_moduleName = moduleName;
        m_path = path;

        m_luaState.open_libraries(sol::lib::base, sol::lib::package, sol::lib::math);

        auto script_from_file_result = m_luaState.safe_script_file(
            path.c_str(), sol::script_pass_on_error);
        if (!script_from_file_result.valid())
        {
            sol::error err = script_from_file_result;
            PN_CORE_FATAL("Script Error!");
            printf("%s\n", err.what());
            PN_CORE_ASSERT(false, "sol2 can not validate the script");
        }
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
