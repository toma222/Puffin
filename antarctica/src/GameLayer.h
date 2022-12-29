
#include <puffin.h>

class GameLayer : public Puffin::Layer
{
private:
    Puffin::graphics::GraphicsAPI *m_graphics;

public:
    void OnAttach(Puffin::Application *attachTo) override;
    void OnDetach() override;

    void Update() override;
    void OnEvent(Puffin::Event *event) override;

    GameLayer()
    {
        GM_CORE_INFO("Creating the graphics API");
        m_graphics = new Puffin::graphics::GraphicsAPI();

        m_graphics->InitGraphicsAPI<Puffin::graphics::GLFWContext>();

        GM_CORE_INFO("Initilizing it");
        m_graphics->m_renderContext->InitGraphics();
    }

    Puffin::Application *m_attached;
};

void GameLayer::OnAttach(Puffin::Application *attachTo)
{
    GM_CORE_TRACE("attaching layer");

    ATTACH_APPLICATION;

    Puffin::graphics::Vertex vertices[6] =
        {
            {{5, 5, -1}, {1.f, 0.f, 0.f}},
            {{5, 0, -1}, {1.f, 0.f, 0.f}},
            {{0, 5, -1}, {1.f, 0.f, 0.f}},
            {{0, 0, -1}, {1.f, 0.f, 0.f}},
            {{5, 0, -1}, {1.f, 0.f, 0.f}},
            {{0, 5, -1}, {1.f, 0.f, 0.f}}};

    GM_CORE_INFO("Vertex Time");
    Puffin::graphics::RenderVertices(vertices, 6);
}

void GameLayer::OnDetach()
{
}

void GameLayer::Update()
{
    m_graphics->RenderGraphics();
}

void GameLayer::OnEvent(Puffin::Event *event)
{
}
