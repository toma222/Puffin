
#include "puffin/graphics/Context.h"
#include "puffin/core/Logging.h"
#include "puffin/core/Base.h"

#include "GLFWContext.h"

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace PN
{
    namespace graphics
    {
        void GLFWContext::InitGraphics()
        {

            // tell glfw to wake up

            PN_CORE_INFO("Initilizing GLFW");

            glfwSetErrorCallback(AssertErrorGLFW);

            if (glfwInit() != 1)
                PN_CORE_FATAL("GLFW not initilized");

            // Hint to opengl all our versions
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        }

        void GLFWContext::SetBackfaceCulling(bool front)
        {
            return;
        }

        void GLFWContext::SetWireFrame(bool on)
        {
            if (on)
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            }
            else
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
        }

        void GLFWContext::SetDepthBufferOn()
        {
            return;
        }

    } // namespace Graphics
} // namespace PN
