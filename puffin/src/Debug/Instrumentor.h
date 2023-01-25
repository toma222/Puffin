
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
    class Debug
    {
    private:
        static Debug *s_debug;

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

            m_output.open("C:/Users/Aidan/Documents/OtherUsslessProjects'/Puffin/Debug.json");

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

        void writeFunction(std::string name, std::string file, float start, float elapsed);

    private:
        std::ofstream m_output;
    };

    class Profile
    {
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
        std::string m_fileName;
        std::string m_functionName;

    public:
        Profile(std::string fileName, std::string functionName)
        {
            m_start = std::chrono::high_resolution_clock::now();

            m_fileName = fileName;
            m_functionName = functionName;
        }

        ~Profile()
        {
            long long endTime = std::chrono::high_resolution_clock::now().time_since_epoch().count();

            long long duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - m_start).count();

            Debug::Get()->writeFunction(m_functionName, m_fileName, m_start.time_since_epoch().count(), duration);
        }
    };
}

#define PN_PROFILE_FUNCTION(functionName) puffin::Profile profile(__FILE__, functionName)
