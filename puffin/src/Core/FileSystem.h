
#pragma once

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#include <string>

namespace puffin
{
    std::string GetRootPath();
    std::string GetPathFromLocal(std::string p);
} // namespace puffin
