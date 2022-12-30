
#include "puffin/core/Base.h"
#include "Shader.h"
#include "puffin/core/Logging.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace PN
{
    namespace graphics
    {
        void Shader::CompileShader()
        {
            std::string vertexCode;
            std::string fragmentCode;
            std::ifstream vShaderFile;
            std::ifstream fShaderFile;

            // ensure ifstream objects can throw exceptions:
            vShaderFile.exceptions(std::ifstream::failbit);
            fShaderFile.exceptions(std::ifstream::failbit);

            try
            {
                // open files
                vShaderFile.open(m_vertexShaderPath.c_str());
                fShaderFile.open(m_fragmentShaderPath.c_str());
                std::stringstream vShaderStream, fShaderStream;

                // read file's buffer contents into streams
                vShaderStream << vShaderFile.rdbuf();
                fShaderStream << fShaderFile.rdbuf();

                // close file handlers
                vShaderFile.close();
                fShaderFile.close();

                // convert stream into string
                vertexCode = vShaderStream.str();
                fragmentCode = fShaderStream.str();
            }
            catch (std::ifstream::failure e)
            {
                PN_CORE_FATAL("Shader file could not be read");
            }

            m_textFragmentShader = fragmentCode;
            m_textVertexShader = vertexCode;
            // vertexCode.copy(m_compiledVertexShader);

            PN_CORE_INFO("Shader has been read and compiled");
        }

        const char *Shader::ReadFragmentShader()
        {
            return m_textFragmentShader.c_str();
        }

        const char *Shader::ReadVertexShader()
        {
            return m_textVertexShader.c_str();
        }

        void Shader::SetBool(const std::string &name, bool val)
        {
            glUniform1i(glGetUniformLocation(m_shaderID, name.c_str()), val);
        }

        void Shader::SetFloat(const std::string &name, float val)
        {
            glUniform1f(glGetUniformLocation(m_shaderID, name.c_str()), val);
        }

        void Shader::SetMat4(const std::string &name, glm::mat4 val)
        {
            glUniformMatrix4fv(glGetUniformLocation(m_shaderID, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
        }

        void Shader::SetVec3(const std::string &name, glm::vec3 val)
        {
            glUniformMatrix3fv(glGetUniformLocation(m_shaderID, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
        }

    } // namespace graphics

} // namespace PN
