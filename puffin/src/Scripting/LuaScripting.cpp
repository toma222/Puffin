
#include "LuaScripting.h"
#include "sol/sol.hpp"

namespace puffin
{
    sol::state LuaScripting::s_globalState = sol::state();

    void LuaScripting::RunLuaScriptFunction(LuaScript script)
    {
    }

    void LuaScripting::RegisterScriptToGlobal(LuaScript script, std::string name)
    {
        s_globalState.load_file(script.GetPath().c_str());
    }

    void LuaScripting::CallFunction(std::string functionName)
    {
        s_globalState[functionName]();
    }
    void LuaScripting::CallModuleFunction(std::string moduleName, std::string functionName)
    {
    }
}
