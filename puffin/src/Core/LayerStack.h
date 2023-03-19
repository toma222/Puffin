
#pragma once

#include "Core.h"
#include "Logging.h"
#include "Layer.h"

namespace puffin
{
    class LayerStack
    {
    private:
        int m_layerStackLocation;

    public:
        ~LayerStack()
        {
            PN_CORE_CLEAN("LayerStack destructor Called");

            for (int lIndex = 0; lIndex < m_layerStackLocation; lIndex++)
                free(stack[lIndex]);
        }

        void InitLayerStack() { m_layerStackLocation = 0; };

        Layer *stack[5];

        template <typename T>
        void AddLayer()
        {
            stack[m_layerStackLocation] = new T;
            m_layerStackLocation++;
        }

        void AttachLayers()
        {
            for (int lIndex = 0; lIndex < m_layerStackLocation; lIndex++)
            {
                stack[lIndex]->OnAttach();
            }
        }

        void DetachLayers()
        {
            for (int lIndex = 0; lIndex < m_layerStackLocation; lIndex++)
                stack[lIndex]->OnDetach();
        }

        void UpdateLayers()
        {
            for (int lIndex = 0; lIndex < m_layerStackLocation; lIndex++)
            {
                stack[lIndex]->Update();
            }
        }

        void ImGuiUpdate()
        {
            for (int lIndex = 0; lIndex < m_layerStackLocation; lIndex++)
            {
                stack[lIndex]->ImGuiUpdate();
            }
        }

        void ClearLayers()
        {
            for (int lIndex = 0; lIndex < m_layerStackLocation; lIndex++)
                free(stack[lIndex]);
        }
    };
} // namespace pn
