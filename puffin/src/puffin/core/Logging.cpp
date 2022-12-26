
#include "Base.h"
#include "Logging.h"

#include <string>

#include <GLFW/glfw3.h>

#ifdef PUFFIN_PLATFORM_WINDOWS
    #include <stdlib.h>
#endif

namespace PN
{
    Logging::Logging(std::string name){
        m_logginLevel = INFO;
        m_name = name;
    }

    void Logging::SetLoggingLevel(LOGGING_LEVEL level){
        m_logginLevel = level;
    }

    void Logging::StartLogging(LOGGING_LEVEL level){
        SetLoggingLevel(level);
    }

    void Logging::LogClean(std::string message){
        printf("\x1b[0;33m%s  %s  CLEAN\x1b[0;0m  %s\n", __TIME__, m_name.c_str(), message.c_str());
    }

    void Logging::LogTrace(std::string message){
        printf("\x1b[0;32m%s  %s  TRACE\x1b[0;0m  %s\n", __TIME__, m_name.c_str(), message.c_str());
    }

    void Logging::LogFatal(std::string message){
        printf("\x1b[0;31m%s  %s  FATAL\x1b[0;0m  %s\n", __TIME__, m_name.c_str(), message.c_str());
    }

    void Logging::LogInfo(std::string message){
        printf("\x1b[0;34m%s  %s  INFO\x1b[0;0m  %s\n", __TIME__, m_name.c_str(), message.c_str());
    }

    void AssertErrorGLFW(int error, const char *description){
        printf("ASSERT FATAL ERROR -> CODE %i -> %s\n", error, description);
    }

} // namespace PN

