#include "Instrumentor.h"

namespace puffin
{
        Debug *Debug::s_debug = nullptr;

        uint64_t micros()
        {
                uint64_t us = std::chrono::duration_cast<std::chrono::microseconds>(
                                  std::chrono::high_resolution_clock::now().time_since_epoch())
                                  .count();
                return us;
        }

        void Debug::writeFunction(std::string name, std::string file, uint64_t start, uint64_t elapsed)
        {
                std::stringstream json;

                json << std::setprecision(3) << std::fixed;
                json << "\n,{";
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
