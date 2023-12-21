
#pragma once

#include "Entity.h"

namespace puffin
{
    class NativeScript
    {
    public:
        virtual ~NativeScript() {}

        template <typename T>
        T &GetComponent()
        {
            return m_Entity.GetComponent<T>();
        }

    protected:
        virtual void OnCreate() {}
        virtual void OnDestroy() {}
        virtual void OnUpdate() {}

        // virtual void OnGuiUpdate() {}
        // virtual void OnGizmosDraw() {}

    private:
        Entity m_Entity;
        friend class Scene;
    };
} // namespace puffin
