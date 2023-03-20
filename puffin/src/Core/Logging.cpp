
#include "Logging.h"
#include "Core.h"

#include <string>

namespace puffin
{
    Logging::Logging(std::string name)
    {
        m_logginLevel = INFO;
        m_name = name;

        // s_logArchive.resize(0);
    }

    void Logging::SetLoggingLevel(LOGGING_LEVEL level)
    {
        m_logginLevel = level;
    }

    void Logging::StartLogging(LOGGING_LEVEL level)
    {
        SetLoggingLevel(level);
    }

    void Logging::LogClean(std::string message, std::string path)
    {
        printf("\x1b[0;33m%s  %s  CLEAN  %s\x1b[0;0m  %s\n", __TIME__, m_name.c_str(), path.c_str(), message.c_str());
        // s_logArchive.push_back(message);
    }

    void Logging::LogTrace(std::string message, std::string path)
    {
        printf("\x1b[0;32m%s  %s  TRACE  %s\x1b[0;0m  %s\n", __TIME__, m_name.c_str(), path.c_str(), message.c_str());
        // s_logArchive.push_back(message);
    }

    void Logging::LogFatal(std::string message, std::string path)
    {
        printf("\x1b[0;31m%s  %s  FATAL  %s\x1b[0;0m  %s\n", __TIME__, m_name.c_str(), path.c_str(), message.c_str());
        // s_logArchive.push_back(message);
    }

    void Logging::LogInfo(std::string message, std::string path)
    {
        printf("\x1b[0;34m%s  %s  INFO   %s\x1b[0;0m  %s\n", __TIME__, m_name.c_str(), path.c_str(), message.c_str());
        // s_logArchive.push_back(message);
    }

    void AssertErrorGLFW(int error, const char *description)
    {
        printf("ASSERT FATAL ERROR -> CODE %i -> %s\n", error, description);
    }

} // namespace PN
