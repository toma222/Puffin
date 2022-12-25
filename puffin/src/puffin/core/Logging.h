
#include "Base.h"
#include <string>

namespace PN{

    enum LOGGING_LEVEL {INFO, PROCCESS, SUCCESS, TRACE, CLEAN};

    class PUFFIN_API Logging
    {
    private:
        LOGGING_LEVEL m_logginLevel;

    public:
        Logging();

        void StartLogging(LOGGING_LEVEL level);
        void SetLoggingLevel(LOGGING_LEVEL level);

        void LogClean(std::string message);
        void LogTrace(std::string message);
        void LogFatal(std::string message);
        void LogProccess(std::string message);
        void LogSuccess(std::string message);
    };
}

