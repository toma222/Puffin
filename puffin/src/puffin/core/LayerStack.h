
#pragma once

#include "Application.h"
#include "Base.h"
#include "Layer.h"
#include "Logging.h"

#include <vector>

namespace PN
{
    class PUFFIN_API LayerStack
    {
    private:
        int m_layerInsertPosition;

    public:
        LayerStack();
        ~LayerStack();

        void RenderStack();

        void AttachLayer(int index, Application *app) { stack[index]->OnAttach(app); };
        void AttachLayer(Layer *layer, Application *app) { layer->OnAttach(app); };

        void AttachLayers(Application *app);

        template <typename T>
        void AddLayer(Application *toAttach)
        {
            stack[m_layerInsertPosition] = new T;
            // stack[m_layerInsertPosition]->OnAttach(toAttach);

            m_layerInsertPosition++;
        }

        Layer *stack[5];
    };

    LayerStack::LayerStack()
    {
        // Just 5 layers
        m_layerInsertPosition = 0;
    }

    LayerStack::~LayerStack()
    {
        PN_CORE_CLEAN("Detaching and freeing layers");

        // call detach
        for (size_t i = 0; i < m_layerInsertPosition; i++)
        {
            // Remove this layer from the mortal world
            stack[i]->OnDetach();

            delete stack[i];
        }
    }

    void LayerStack::AttachLayers(Application *app)
    {
        for (size_t layers = 0; layers < m_layerInsertPosition; layers++)
        {
            AttachLayer(layers, app);
        }
    }

    void LayerStack::RenderStack()
    {
        for (size_t i = 0; i < m_layerInsertPosition; i++)
        {
            stack[i]->Update();
        }
    }

} // namespace PN
