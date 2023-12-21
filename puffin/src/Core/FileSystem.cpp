
#include "FileSystem.h"

#include <string>

namespace puffin
{
    std::string GetRootPath()
    {
        char buff[FILENAME_MAX]; // create string buffer to hold path
        GetCurrentDir(buff, FILENAME_MAX);
        std::string current_working_dir(buff);
        return current_working_dir;
    }

    std::string GetPathFromLocal(std::string p)
    {
        std::string root = GetRootPath();
        return root.append(p.c_str());
    }
} // namespace puffin
