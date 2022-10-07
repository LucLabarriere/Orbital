#pragma once
#include "OrbitalECS/Context.h"
#include "OrbitalTools/UUID.h"

namespace Orbital
{
    template<typename T>
    class Handle
    {
    public:
        Handle() : mObject(nullptr), mUUID(0) {  }
        Handle(T& object, UUID uuid) : mObject(&object), mUUID(uuid) {  }
        
        T* operator->() { return mObject; }
        UUID getUUID() const { return mUUID; }

    private:
        T* mObject;
        UUID mUUID;
    };
}
