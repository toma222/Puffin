
#pragma once

#include <string>

namespace puffin
{
    class PlatformUtils
    {
    public:
        static std::string OpenFile(const char *filter);
        static std::string SaveFile(const char *filter);
    };

} // namespace puffin
