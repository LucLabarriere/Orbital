#pragma once

#include "OrbitalScripts/Context.h"
#include "OrbitalEngine/Components/NativeScript.h"
#include "OrbitalEngine/Components/TransformComponent.h"
#include "OrbitalEngine/Components/NativeScriptManager.h"

namespace Orbital
{
    class OSCRIPTS_API PlayerController : public NativeScript
    {
        public:
            PlayerController(const Entity& e);
            virtual ~PlayerController() { };

            virtual size_t getTypeId() const override { return typeid(PlayerController).hash_code(); }
            virtual void onLoad() override;
            virtual void onUpdate(Time dt) override;

        private:
            float mSpeed;
            ComponentHandle<TransformComponent> mTransform;
    };

    extern "C" OSCRIPTS_API NativeScript* CreatePlayerController(const Entity& e);
    extern "C" OSCRIPTS_API size_t GetPlayerControllerID();
}
