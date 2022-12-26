#pragma once

#include "Base.h"
#include <string>
#include <GLFW/glfw3.h>

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
        virtual void InitWindow();
        virtual void ClearWindow();

        virtual void GetIO();

        virtual void GetWidth();
        virtual void GetHeight();

        virtual void CleanWindow();
        virtual void SetVSync(bool onOff);
    };
} // namespace PN
