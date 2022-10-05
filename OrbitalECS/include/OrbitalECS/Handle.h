#pragma once
#include "OrbitalECS/Context.h"

namespace Orbital
{
    template<typename T>
    class Handle
    {
    public:
        Handle(T& object) : mObject(&object) {  }
        T* operator->() { return mObject; }

    private:
        T* mObject;
    };
}
