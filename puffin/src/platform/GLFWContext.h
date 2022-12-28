#pragma once

#include "puffin/graphics/Context.h"
#include "puffin/core/Base.h"

namespace PN
{
    namespace graphics
    {
        class PUFFIN_API GLFWContext : public Context
        {
        public:
            // Initilized the GLFW graphics this includes
            //      - Hinting to GLFW about versions
            //      - Setting error callback
            //      - Setting up GLAD
            void InitGraphics() override;

            // Turns on depth (if you're into that)
            void SetDepthBufferOn() override;

            // Turns on backface culling (if you like programs that run fast)
            void SetBackfaceCulling(bool Back) override;

            // Turns on backface culling (if you like programs that run fast)
            void SetWireFrame(bool on) override;
        };
    } // namespace Graphics
} // namespace PN
