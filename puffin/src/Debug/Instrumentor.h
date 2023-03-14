
#pragma once

// #include "Core/Logging.h"

#include <string>
#include <iostream>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <thread>
#include <mutex>
#include <sstream>

namespace puffin
{
    uint64_t micros();

    class Debug
    {
    private:
        static Debug *s_debug;
        int m_subsectionPid;
        uint64_t m_debugStartTime;

    public:
        static Debug *Get() { return s_debug; };

        ~Debug()
        {
            writeFooter();
        }

        Debug()
        {
            // Open a file to write to
            // std::lock_guard lock(m_mutex);
            s_debug = this;
            m_subsectionPid = 0;

            m_output.open("C:/Users/100044352/Desktop/engine/puffin/Runtime.json");
            m_debugStartTime = micros();

            if (m_output.is_open())
            {
                writeHeader();
            }
        }

        void writeHeader()
        {
            m_output << "{\"otherData\": {},\"traceEvents\":[{}";
            m_output.flush();
        }

        void writeFooter()
        {
            m_output << "]}";
            m_output.flush();
        }

        void writeFunction(std::string name, std::string file, uint64_t start, uint64_t elapsed);

    private:
        std::ofstream m_output;
    };

    class Profile
    {
    private:
        // std::chrono::time_point<std::chrono::system_clock> m_StartTime;
        // std::chrono::time_point<std::chrono::system_clock> m_EndTime;
        uint64_t m_start;
        uint64_t m_end;

        std::string m_fileName;
        std::string m_functionName;

    public:
        Profile(std::string fileName, std::string functionName)
        {
            m_start = micros();

            m_fileName = fileName;
            m_functionName = functionName;
        }

        ~Profile()
        {
            long long duration = m_end - m_start;

            Debug::Get()->writeFunction(m_functionName, m_fileName, m_start, duration);
        }
    };
}

#define PN_PROFILE_FUNCTION(functionName) puffin::Profile profile(__FILE__, functionName)
