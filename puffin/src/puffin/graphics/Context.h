#pragma once

#include "puffin/core/Base.h"

// NOT USING MACRO BECAUSE IT WAS NOT BEING NICE
namespace Puffin
{
    namespace Graphics
    {
        // This handles the state of GLFW and all it's fun
        // non rendering things
        class PUFFIN_API Context
        {
        public:
            virtual void InitGraphics();
            // Initilizes GLFW libraries

            virtual void SetDepthBufferOn();
            // Turns on the depth buffer

            virtual void SetBackfaceCulling(bool Back);
            // Turns on Backface Culling
        };
    } // namespace for glfw things
    
} // namespace NP