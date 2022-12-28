
#pragma once

#include "puffin/core/Base.h"
#include "Context.h"

#include "platform/GLFWContext.h"
#include "platform/GLFWWindow.h"

namespace PN
{
    namespace graphics
    {
        // This is the main container for all graphical functions and interfaces
        class PUFFIN_API GraphicsAPI
        {
        public:
            Context *m_renderContext;

        public:
            void RenderGraphics();

            ~GraphicsAPI();

            // @param contextType the class of the context we want the graphics to use currently only support for GLFW
            template <typename T>
            void InitGraphicsAPI()
            {
                m_renderContext = new T;
            }
        };
    } // namespace Render
} // namespace NP
