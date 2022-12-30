
#include "puffin/core/Base.h"
#include "Graphics.h"
#include "puffin/core/Logging.h"

#include <glm/glm.hpp>

#include "Mesh.h"

namespace PN
{
    namespace graphics
    {
        typedef struct PUFFIN_API
        {
            glm::vec3 pos;
            glm::vec3 col;
        } Vertex;

        void PUFFIN_API RenderVertices(Shader *shader, Vertex vertices[], int size);
    } // namespace graphics

} // namespace PN
