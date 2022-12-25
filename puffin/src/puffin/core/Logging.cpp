
#include "Base.h"
#include "Logging.h"

#include <string>

namespace PN
{
    Logging::Logging(){
        m_logginLevel = INFO;
    }

    void Logging::SetLoggingLevel(LOGGING_LEVEL level){
        m_logginLevel = level;
    }

    void Logging::StartLogging(LOGGING_LEVEL level){
        SetLoggingLevel(level);
    }

    void Logging::LogClean(std::string message){
        printf("LOGGING  %s  clean  %s\n", __TIME__, message.c_str());
    }

    void Logging::LogTrace(std::string message){
        printf("LOGGING  %s  trace  %s\n", __TIME__, message.c_str());
    }

    void Logging::LogFatal(std::string message){
        printf("LOGGING  %s  fatal  %s\n", __TIME__, message.c_str());
    }

    void Logging::LogProccess(std::string message){
        printf("LOGGING  %s  proccess  %s\n", __TIME__, message.c_str());
    }

    void Logging::LogSuccess(std::string message){
        printf("LOGGING  %s  succsess  %s\n", __TIME__, message.c_str());
    }

} // namespace PN

