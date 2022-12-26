
#pragma once

#define PN Puffin

#define PUFFIN_PLATFORM_WINDOWS

#define OPENGL_MAJOR_VERSION 3
#define OPENGL_MINOR_VERSION 2

#ifdef PUFFIN_PLATFORM_WINDOWS
    #ifdef PN_BUILD_DLL
        #define PUFFIN_API __declspec(dllexport)
    #else
        #define PUFFIN_API __declspec(dllexport)
    #endif
#else
    #error Puffin only supports windows. go touch grass nerd
#endif
