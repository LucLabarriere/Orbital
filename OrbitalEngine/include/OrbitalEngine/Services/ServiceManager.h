#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/Services.h"

namespace Orbital
{
    template<typename ...S>
    class ServiceManager : public S...
    {
    public:
        template<typename ...Args>
        static inline ServiceManager<S...> Create(Args... args)
        {
            return {
                 args ...
            };
        }
    };

    using SceneServiceManager = ServiceManager<RendererService, ScriptEngineService>;
    using ScriptServiceManager = ServiceManager<ECSService, ScenesService>;
    using CompleteServiceManager = ServiceManager<ECSService, ScenesService, ScriptEngineService, RendererService>;
}
