#pragma once

#include "OrbitalScripts/Context.h"
#include "OrbitalEngine/Components/NativeScript.h"
#include "OrbitalEngine/Components/TransformComponent.h"

namespace Orbital
{
    class OSCRIPTS_API PlayerController : public NativeScript
    {
        public:
            PlayerController(const Entity& e) : NativeScript(e), mTransform(e.get<TransformComponent>()) { }
            virtual ~PlayerController() override { };

            virtual void onLoad() override;
            virtual void onUpdate(Time dt) override;

        private:
            float mSpeed = 0.0f;
            ComponentHandle<TransformComponent> mTransform;
    };
    
    typedef PlayerController* CreatePlayerController_t(const Entity& e);
    typedef void DestroyPlayerController_t(PlayerController*);
}
