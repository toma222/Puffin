
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
        json << "\"tid\":" << 0 << ",";
        json << "\"ts\":" << start;
        json << "}\n";

        m_output << json.str();
        m_output.flush();
    }
} // namespace puffin
