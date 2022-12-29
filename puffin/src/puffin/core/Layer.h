
#pragma once

#include "Base.h"
#include "puffin/events/Event.h"
#include "Application.h"

#define ATTACH_APPLICATION m_attached = attachTo;

namespace PN
{
    // this is like a layer of the engine
    class Application;

    class PUFFIN_API Layer
    {
    public:
        virtual void OnAttach(Application *attachTo) { return; };
        virtual void OnDetach() { return; };

        virtual void Update() { return; };
        virtual void OnEvent(Event *event) { return; };

        Application *m_attached;
    };
} // namespace PN
