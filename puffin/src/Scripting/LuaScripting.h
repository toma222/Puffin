
#pragma once

#include <string>

#include "sol/sol.hpp"

#include "Core/Assert.h"
#include "Core/Logging.h"

namespace puffin
{
    class LuaScript
    {
    private:
        std::string m_path;
        std::string m_moduleName;
        sol::state m_luaState;

    public:
        std::string GetPath() { return m_path; };

        LuaScript(std::string path, std::string moduleName = "script") : m_moduleName(moduleName)
        {
            m_luaState.open_libraries(sol::lib::base);

            m_luaState.script_file(path.c_str());

            m_path = path;
        };

        template <typename... Args>
        void RunFunction(std::string functionName, Args &&...args)
        {
            m_luaState[m_moduleName.c_str()][functionName.c_str()](std::forward<Args>(args)...);
        }

        template <typename T>
        T GetField(const char *name)
        {
            return (T)m_luaState[m_moduleName.c_str()][name];
        }

        template <typename T>
        bool SetVariable(const char *name)
        {
            // m_luaState[m_moduleName.c_str()][name].
            return false;
        }
    };

    class LuaScripting
    {
    private:
        static sol::state s_globalState;

    public:
        static void RunLuaScriptFunction(LuaScript script);
        static void RegisterScriptToGlobal(LuaScript script, std::string name);
        static void CallFunction(std::string functionName);
        static void CallModuleFunction(std::string moduleName, std::string functionName);
    };
}
