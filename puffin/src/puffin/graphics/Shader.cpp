
#include "puffin/core/Base.h"
#include "Shader.h"
#include "puffin/core/Logging.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

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
            vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

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
    } // namespace graphics

} // namespace PN
