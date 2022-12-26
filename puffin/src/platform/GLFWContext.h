
#include "puffin/graphics/Context.h"
#include "puffin/core/Base.h"

namespace PN
{
namespace Graphics
{
    class PUFFIN_API GLFWContext : Context
    {
    public:
        void InitGraphics() override;

        void SetDepthBufferOn() override;

        void SetBackfaceCulling(bool Back) override;
    };    
} // namespace Graphics
} // namespace PN

