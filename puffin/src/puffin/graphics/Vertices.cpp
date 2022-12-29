
#include "puffin/core/Base.h"
#include "Graphics.h"
#include "puffin/core/Logging.h"
#include "Shader.h"

#include <vector>

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Vertices.h"

/*
static const Vertex vertices[3] =
    {
        {{-0.6f, -0.4f}, {1.f, 0.f, 0.f}},
        {{0.6f, -0.4f}, {0.f, 1.f, 0.f}},
        {{0.f, 0.6f}, {0.f, 0.f, 1.f}}};
*/

static const char *vertex_shader_text =
    "#version 330\n"
    "uniform mat4 MVP;\n"
    "in vec3 vCol;\n"
    "in vec3 vPos;\n"
    "out vec3 color;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = MVP * vec4(vPos, 1.0);\n"
    "    color = vCol;\n"
    "}\n";

const char *fragment_shader_text =
    "#version 330\n"
    "in vec3 color;\n"
    "out vec4 fragment;\n"
    "void main()\n"
    "{\n"
    "    fragment = vec4(color, 1.0);\n"
    "}\n";

namespace PN
{
    namespace graphics
    {
        void RenderVertices(Vertex vertices[], int size)
        {
            // Shader shader(
            //     "C:/Users/Aidan/Documents/OtherUsslessProjects'/Puffin/test/shader/BasicFragmentShader.glsl",
            //    "C:/Users/Aidan/Documents/OtherUsslessProjects'/Puffin/test/shader/BasicVertexShader.glsl");

            // shader.CompileShader();

            // const char *VertexShader = shader.ReadVertexShader();
            // const char *FragmentShader = shader.ReadFragmentShader();

            GLuint vertex_buffer;
            glGenBuffers(1, &vertex_buffer);
            glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * size, vertices, GL_STATIC_DRAW);

            const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
            glCompileShader(vertex_shader);

            const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
            glCompileShader(fragment_shader);

            const GLuint program = glCreateProgram();
            glAttachShader(program, vertex_shader);
            glAttachShader(program, fragment_shader);
            glLinkProgram(program);

            const GLint mvp_location = glGetUniformLocation(program, "MVP");
            const GLint vpos_location = glGetAttribLocation(program, "vPos");
            const GLint vcol_location = glGetAttribLocation(program, "vCol");

            GLuint vertex_array;
            glGenVertexArrays(1, &vertex_array);
            glBindVertexArray(vertex_array);
            glEnableVertexAttribArray(vpos_location);
            glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE,
                                  sizeof(Vertex), (void *)offsetof(Vertex, pos));
            glEnableVertexAttribArray(vcol_location);
            glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
                                  sizeof(Vertex), (void *)offsetof(Vertex, col));

            glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)500 / (float)500, 0.1f, 100.0f); // glm::ortho(0.f, 9.f, 0.f, 16.f, -1.f, 100.f); // glm::perspective(glm::radians(45.0f), (float)500 / (float)500, 0.1f, 100.0f);

            glUseProgram(program);
            glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(proj));
            glBindVertexArray(vertex_array);
        }
    } // namespace graphics

} // namespace PN
