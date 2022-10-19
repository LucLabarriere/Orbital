#include "OrbitalScripts/PlayerController.h"

namespace Orbital
{
    PlayerController::PlayerController(const Entity& e)
        : NativeScript(e)
        , mSpeed(2.0f)
        , mTransform(e.get<TransformComponent>())
    {
        mTransform->scale = Maths::Vec3(1.0f, 1.0f, 1.0f);
    }

    void PlayerController::onLoad()
    {

    }

    void PlayerController::onUpdate(Time dt)
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

    NativeScript* CreatePlayerController(const Entity& e)
    {
        return new PlayerController(e);
    }

    size_t GetPlayerControllerID()
    {
        return typeid(PlayerController).hash_code();
    }
}
