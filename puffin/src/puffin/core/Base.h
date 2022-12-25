
#pragma once

#define PN Puffin

#define PUFFIN_PLATFORM_WINDOWS 1

#ifdef PUFFIN_PLATFORM_WINDOWS
    #ifdef PN_BUILD_DLL
        #define PUFFIN_API __declspec(dllexport)
    #else
        #define PUFFIN_API __declspec(dllimport)
    #endif
#else
    #error Puffin only supports windows. go touch grass nerd
#endif
