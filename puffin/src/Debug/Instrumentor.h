
#pragma once

// #include "Core/Logging.h"

#include <string>

namespace puffin
{
    // @deprecated
    class Debug
    {
    private:
        unsigned int m_allocatedMemory;
        unsigned int m_objects;

    public:
        Debug();
        ~Debug();

        void LogObjectCreated(int memory, std::string className, std::string fileName);
        void LogObjectDestroyed();

        unsigned int GetAllocatedMemory() { return m_allocatedMemory; };
    };

    static Debug *s_puffinDebug = new Debug();

} // namespace puffin

// #define PN_LOG_ALLOC(bytes, class, file) puffin::s_puffinDebug->LogObjectCreated(bytes, class, file)
