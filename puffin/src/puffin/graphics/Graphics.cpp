
#include "puffin/core/Base.h"
#include "Graphics.h"
#include "puffin/core/Logging.h"

namespace PN
{
namespace graphics
{
    GraphicsAPI::~GraphicsAPI(){
        PN_CORE_CLEAN("Cleaning GraphicsAPI::m_renderContext");
        delete m_renderContext;
    }

    void GraphicsAPI::RenderGraphics(){
        return;
    }
} // namespace Render
} // namespace NP

