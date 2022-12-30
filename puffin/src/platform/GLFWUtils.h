
#include "puffin/graphics/Context.h"
#include "puffin/graphics/Graphics.h"
#include "puffin/core/Base.h"
#include "GLFWContext.h"

namespace PN
{
    graphics::GraphicsAPI *PUFFIN_API MakeContextForGLFW()
    {
        graphics::GraphicsAPI *api = new graphics::GraphicsAPI();

        api->InitGraphicsAPI<graphics::GLFWContext>();

        api->m_renderContext->InitGraphics();

        return api;
    }
}
