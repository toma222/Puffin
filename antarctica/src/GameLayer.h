
#include <puffin.h>

class GameLayer : public Puffin::Layer
{
private:
    /* data */
public:
    void OnAttach(Puffin::Application *attachTo) override;
    void OnDetach() override;

    void Update() override;
    void OnEvent(Puffin::Event *e) override;

    Puffin::Application *m_attached;
};

void GameLayer::OnAttach(Puffin::Application *attachTo)
{
    ATTACH_APPLICATION;

    GM_CORE_TRACE("attaching layer");

    Puffin::graphics::Vertex vertices[6] =
        {
            {{5, 5, -1}, {1.f, 0.f, 0.f}},
            {{5, 0, -1}, {1.f, 0.f, 0.f}},
            {{0, 5, -1}, {1.f, 0.f, 0.f}},
            {{0, 0, -1}, {1.f, 0.f, 0.f}},
            {{5, 0, -1}, {1.f, 0.f, 0.f}},
            {{0, 5, -1}, {1.f, 0.f, 0.f}}};

    Puffin::graphics::RenderVertices(vertices, 6);
}

void GameLayer::OnDetach()
{
}

void GameLayer::Update()
{
}

void GameLayer::OnEvent(Puffin::Event *e)
{
}
