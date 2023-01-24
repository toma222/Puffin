
#include "Instrumentor.h"

namespace puffin
{
    Debug *Debug::s_debug = nullptr;

    void Debug::writeFunction(std::string name, std::string file, float start, float elapsed)
    {
        std::stringstream json;

        json << std::setprecision(3) << std::fixed;
        json << ",{";
        json << "\"cat\":\"function\",";
        json << "\"dur\":" << elapsed << ',';
        json << "\"name\":\"" << name << "\",";
        json << "\"ph\":\"X\",";
        json << "\"pid\":0,";
        json << "\"tid\":" << s_pid << ",";
        json << "\"ts\":" << start;
        json << "}\n";

        printf("%i pid\n", s_pid);

        m_output << json.str();
        m_output.flush();
    }

    Proccess::Proccess(std::string fileName, std::string functionName)
    {
        // Profiles how long the proccess takes
        // Puts it on the base proccess pid (0)
        m_profile = new Profile(fileName, functionName);
        s_pid += 1;
    }

} // namespace puffin
