#pragma once

#include "Core.h"
#include "Application.h"

namespace puffin
{
    class Layer
    {
    public:
        virtual void OnAttach() { return; };
        virtual void OnDetach() { return; };
        virtual void Update() { return; };
        virtual void Start() { return; };
        virtual void ImGuiUpdate() { return; };

        virtual ~Layer() { return; };
    };
} // namespace pn
