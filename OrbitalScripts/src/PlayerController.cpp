#include "OrbitalScripts/PlayerController.h"
#include "OrbitalEngine/Components/NativeScript.h"

namespace Orbital
{
    PlayerController::PlayerController(const Entity& e, ScriptServiceManager services)
        : NativeScript(e, services)
        , mSpeed(5.0f)
        , mTransform(e.get<TransformComponent>())
    {
        mTransform->scale = Maths::Vec3(1.0f, 1.0f, 1.0f) * 0.1f;
    }

    void PlayerController::onLoad()
    {

    }

    void PlayerController::onUpdate(const Time& dt)
    {
        mTransform->rotation.z += mSpeed * dt.seconds();

        if (Inputs::IsKeyDown(OE_KEY_Q))
        {
            mTransform->scale -= mSpeed * dt.seconds();
        }

        if (Inputs::IsKeyDown(OE_KEY_E))
        {
            mTransform->scale += mSpeed * dt.seconds();
        }

        if (Inputs::IsKeyDown(OE_KEY_S))
        {
            mTransform->position.y -= mSpeed * dt.seconds();
        }

        if (Inputs::IsKeyDown(OE_KEY_W))
        {
            mTransform->position.y += mSpeed * dt.seconds();
        }

        if (Inputs::IsKeyDown(OE_KEY_A))
        {
            mTransform->position.x -= mSpeed * dt.seconds();
        }

        if (Inputs::IsKeyDown(OE_KEY_D))
        {
            mTransform->position.x += mSpeed * dt.seconds();
        }
    }
}

OE_DEFINE_CREATOR(PlayerController);
