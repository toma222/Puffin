
#include <puffin.h>

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GameLayer : public Puffin::Layer
{
private:
    Puffin::graphics::GraphicsAPI *m_graphics;
    Puffin::graphics::Shader m_shader;
    Puffin::graphics::PerspectiveCamera *m_camera;

public:
    void OnAttach(Puffin::Application *attachTo) override;
    void OnDetach() override;

    void Update() override;
    void OnEvent(Puffin::Event *event) override;

    GameLayer();

    Puffin::Application *m_attached;
};

GameLayer::GameLayer() : m_shader("C:/Users/Aidan/Documents/OtherUsslessProjects'/Puffin/test/shader/BasicFragmentShader.glsl",
                                  "C:/Users/Aidan/Documents/OtherUsslessProjects'/Puffin/test/shader/BasicVertexShader.glsl")
{
    m_graphics = Puffin::MakeContextForGLFW();

    // m_shader("C:/Users/Aidan/Documents/OtherUsslessProjects'/Puffin/test/shader/BasicFragmentShader.glsl",
    //                                         "C:/Users/Aidan/Documents/OtherUsslessProjects'/Puffin/test/shader/BasicVertexShader.glsl");

    m_graphics->m_renderContext->SetBackfaceCulling(false);

    m_camera = new Puffin::graphics::PerspectiveCamera(glm::vec2(500, 500), glm::vec3(0.0f, 0.0f, 8.0f));

    m_shader.CompileShader();
}

void GameLayer::OnAttach(Puffin::Application *attachTo)
{
    ATTACH_APPLICATION;
    GM_CORE_TRACE("Game Layer Attached and running on attach code");

    Puffin::graphics::Vertex vertices[36] =
        {
            {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
            {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
            {{0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
            {{0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
            {{-0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
            {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},

            {{-0.5f, -0.5f, 0.5f}, {1.0f, 1.0f, 0.0f}},
            {{0.5f, -0.5f, 0.5f}, {1.0f, 1.0f, 0.0f}},
            {{0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 0.0f}},
            {{0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 0.0f}},
            {{-0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 0.0f}},
            {{-0.5f, -0.5f, 0.5f}, {1.0f, 1.0f, 0.0f}},

            {{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
            {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
            {{-0.5f, -0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
            {{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},

            {{0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 1.0f}},
            {{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 1.0f}},
            {{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 1.0f}},
            {{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 1.0f}},
            {{0.5f, -0.5f, 0.5f}, {0.0f, 1.0f, 1.0f}},
            {{0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 1.0f}},

            {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}},
            {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}},
            {{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
            {{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
            {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}},

            {{-0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}},
            {{0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}},
            {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 1.0f}},
            {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 1.0f}},
            {{-0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 1.0f}},
            {{-0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}}};

    Puffin::graphics::RenderVertices(&m_shader, vertices, 36);
}

void GameLayer::OnDetach()
{
}

void GameLayer::Update()
{
    m_camera->Translate(glm::vec3(0, 0.01f, 0));
    glm::mat4 proj = m_camera->GetCameraProjectionMatrix(); // glm::perspective(glm::radians(45.0f), (float)500 / (float)500, 0.1f, 100.0f);
    m_shader.SetMat4("MVP", proj);
    m_graphics->RenderGraphics();
    // m_shader.UseShader();
}

void GameLayer::OnEvent(Puffin::Event *event)
{
}
