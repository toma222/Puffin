
#include "puffin/core/Base.h"
#include "puffin/core/Logging.h"

#include <string>

namespace PN
{
    namespace graphics
    {
        // @param fragment shader path
        // @param vertex shader path
        class PUFFIN_API Shader
        {
        private:
            std::string m_vertexShaderPath;
            std::string m_fragmentShaderPath;

        public:
            std::string m_textVertexShader;
            std::string m_textFragmentShader;

            Shader(std::string fragPath, std::string vertPath)
            {
                m_fragmentShaderPath = fragPath;
                m_vertexShaderPath = vertPath;
            };

            void CompileShader();
            const char *ReadVertexShader();
            const char *ReadFragmentShader();
        };
    } // namespace graphics

} // namespace PN
