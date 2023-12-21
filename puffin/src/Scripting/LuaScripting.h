
#pragma once

#include <string>

#include "sol/sol.hpp"

#include "Core/Assert.h"
#include "Core/Logging.h"

namespace puffin
{
    class LuaScripting;

    class LuaScript
    {
    public:
        std::string m_path;
        std::string m_moduleName;
        sol::state m_luaState;

    public:
        std::string GetPath() { return m_path; };

        LuaScript(std::string path, std::string moduleName);

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
    };

    class LuaScripting
    {
    public:
        static sol::state s_globalState;

    public:
        static void InitLuaScripting();

        static void RegisterModule(LuaScript &script);

        static void CallLoadedModuleFunction(const char *module, const char *function);
        static void CallGlobalFunction(const char *functionName);

        template <typename... Args>
        static void RunFunction(std::string name, std::string module, Args &&...args)
        {
            s_globalState[module.c_str()][name.c_str()](std::forward<Args>(args)...);
        }
    };
}
