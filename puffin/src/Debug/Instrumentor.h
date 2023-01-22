
#pragma once

// #include "Core/Logging.h"

#include <string>
#include <iostream>
#include <chrono>

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

    class Profile
    {
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_start;

    public:
        Profile()
        {
            m_start = std::chrono::high_resolution_clock::now();
        }

        ~Profile()
        {
            auto endTime = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - m_start);
            std::cout << "Time taken by function: "
                      << duration.count() << " microseconds" << std::endl;
        }
    };
} // namespace puffin

// #define PN_LOG_ALLOC(bytes, class, file) puffin::s_puffinDebug->LogObjectCreated(bytes, class, file)
