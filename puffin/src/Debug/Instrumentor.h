
#pragma once

// #include "Core/Logging.h"

#include <string>
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

    class Timer
    {
    public:
        // Starts the timer
        void start()
        {
            m_startTime = std::chrono::high_resolution_clock::now();
        }

        // Stops the timer and returns the elapsed time in microseconds
        long long stop()
        {
            auto endTime = std::chrono::high_resolution_clock::now();
            m_savedTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - m_startTime).count();
            return m_savedTime;
        }

        double m_savedTime;

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
    };

} // namespace puffin

// #define PN_LOG_ALLOC(bytes, class, file) puffin::s_puffinDebug->LogObjectCreated(bytes, class, file)
