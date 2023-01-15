#pragma once

#include "Core.h"
#include "Application.h"

namespace puffin
{
    // Please ignore my forward deceleration
    class Application;

    class Layer
    {
    public:
        virtual void OnAttach() { return; };
        virtual void OnDetach() { return; };
        virtual void Update() { return; };
        virtual void Start() { return; };

        virtual ~Layer() { return; };
    };
} // namespace pn
