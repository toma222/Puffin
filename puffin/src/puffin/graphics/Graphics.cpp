
#include "puffin/core/Base.h"
#include "Graphics.h"
#include "puffin/core/Logging.h"

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace PN
{
    namespace graphics
    {

        // All the vertex buffers and such
        GraphicsAPI::~GraphicsAPI()
        {
            PN_CORE_CLEAN("Cleaning GraphicsAPI::m_renderContext");
            delete m_renderContext;
        }

        void GraphicsAPI::RenderGraphics()
        {
            glDrawArrays(GL_TRIANGLES, 0, 12);
        }
    } // namespace Render
} // namespace NP
