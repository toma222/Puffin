#pragma once

#include "puffin/core/Base.h"
#include "puffin/core/Logging.h"

#include <string>

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"

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

            unsigned int m_shaderID;

        public:
            std::string m_textVertexShader;
            std::string m_textFragmentShader;

            Shader(std::string fragPath, std::string vertPath)
            {
                m_fragmentShaderPath = fragPath;
                m_vertexShaderPath = vertPath;
            };

            void CompileShader();

            void SetShaderID(const unsigned int ID) { m_shaderID = ID; }
            void UseShader() { glUseProgram(m_shaderID); };

            const char *ReadVertexShader();
            const char *ReadFragmentShader();

            void SetBool(const std::string &name, bool val);
            void SetFloat(const std::string &name, float val);
            void SetMat4(const std::string &name, glm::mat4 val);
            void SetVec3(const std::string &name, glm::vec3 val);
        };
    } // namespace graphics

} // namespace PN
