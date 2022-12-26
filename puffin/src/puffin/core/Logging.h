
#pragma once

#include "Base.h"
#include <string>

namespace PN{

    enum LOGGING_LEVEL {INFO, PROCCESS, SUCCESS, TRACE, CLEAN};

    class PUFFIN_API Logging
    {
    private:
        LOGGING_LEVEL m_logginLevel;
        std::string m_name;

    public:
        Logging(std::string name);

        void StartLogging(LOGGING_LEVEL level);
        void SetLoggingLevel(LOGGING_LEVEL level);

        void LogClean(std::string message);
        void LogTrace(std::string message);
        void LogFatal(std::string message);
        void LogInfo(std::string message);
    };

    static Logging *PuffinLogger = new Logging("PUFFIN");
    static Logging *GameLogger = new Logging("GAME");
}

// engine logging macros
// only for use in the CORE off the engine
#define PN_CORE_TRACE(MESSAGE) Puffin::PuffinLogger->LogTrace(MESSAGE)
#define PN_CORE_CLEAN(MESSAGE) Puffin::PuffinLogger->LogClean(MESSAGE)
#define PN_CORE_FATAL(MESSAGE) Puffin::PuffinLogger->LogFatal(MESSAGE)
#define PN_CORE_INFO(MESSAGE) Puffin::PuffinLogger->LogInfo(MESSAGE)

// Game logging macros
// only for use in the game directory
#define GM_CORE_TRACE(MESSAGE) Puffin::GameLogger->LogTrace(MESSAGE)
#define GM_CORE_CLEAN(MESSAGE) Puffin::GameLogger->LogClean(MESSAGE)
#define GM_CORE_FATAL(MESSAGE) Puffin::GameLogger->LogFatal(MESSAGE)
#define GM_CORE_INFO(MESSAGE) Puffin::GameLogger->LogInfo(MESSAGE)

