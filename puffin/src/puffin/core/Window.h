#pragma once

#include "Base.h"
#include <string>
#include <GLFW/glfw3.h>

#include <string>

namespace PN
{
    typedef struct PUFFIN_API
    {
        int width;
        int height;
        std::string name;
    } WindowProporties;


    class PUFFIN_API Window
    {
    private:
        WindowProporties m_proporties;
     
    public:
        virtual void UpdateWindow();
        virtual void InitWindow(std::string name);
        virtual void ClearWindow();
        virtual int ShouldClose();

        virtual void GetIO();

        virtual int GetWidth();
        virtual int GetHeight();

        virtual void CleanWindow();
        virtual void SetVSync(bool onOff);
    };
} // namespace PN
