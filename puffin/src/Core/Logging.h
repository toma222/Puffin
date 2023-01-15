
#pragma once

#include <string>

namespace puffin
{
    enum LOGGING_LEVEL
    {
        INFO,
        PROCCESS,
        SUCCESS,
        TRACE,
        CLEAN
    };

    void AssertErrorGLFW(int error, const char *description);

    class Logging
    {
    private:
        LOGGING_LEVEL m_logginLevel;
        std::string m_name;

    public:
        Logging(std::string name);

        void StartLogging(LOGGING_LEVEL level);
        void SetLoggingLevel(LOGGING_LEVEL level);

        void LogClean(std::string message, std::string path);
        void LogTrace(std::string message, std::string path);
        void LogFatal(std::string message, std::string path);
        void LogInfo(std::string message, std::string path);
    };

    static Logging *PuffinLogger = new Logging("PUFFIN");
    static Logging *GameLogger = new Logging("GAME");
}

// engine logging macros
// only for use in the CORE off the engine
#define PN_CORE_TRACE(MESSAGE) puffin::PuffinLogger->LogTrace(MESSAGE, __FILE__)
#define PN_CORE_CLEAN(MESSAGE) puffin::PuffinLogger->LogClean(MESSAGE, __FILE__)
#define PN_CORE_FATAL(MESSAGE) puffin::PuffinLogger->LogFatal(MESSAGE, __FILE__)
#define PN_CORE_INFO(MESSAGE) puffin::PuffinLogger->LogInfo(MESSAGE, __FILE__)

// Game logging macros
// only for use in the game directory
#define GM_CORE_TRACE(MESSAGE) puffin::GameLogger->LogTrace(MESSAGE, __FILE__)
#define GM_CORE_CLEAN(MESSAGE) puffin::GameLogger->LogClean(MESSAGE, __FILE__)
#define GM_CORE_FATAL(MESSAGE) puffin::GameLogger->LogFatal(MESSAGE, __FILE__)
#define GM_CORE_INFO(MESSAGE) puffin::GameLogger->LogInfo(MESSAGE, __FILE__)
