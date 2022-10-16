#include "OrbitalScripts/PlayerController.h"

namespace Orbital
{
    void PlayerController::onLoad()
    {

    }

    void PlayerController::onUpdate(Time dt)
    {
        if (Inputs::isKeyDown(OE_KEY_Z))
        {
            mTransform->position.y -= mSpeed * dt.seconds();
        }
        if (Inputs::isKeyDown(OE_KEY_S))
        {
            mTransform->position.y += mSpeed * dt.seconds();
        }
    }

    extern "C" PlayerController* CreatePlayerController(const Entity& e)
    {
        return new PlayerController(e);
    }

    extern "C" void DestroyPlayerController(PlayerController* p)
    {
        return delete p;
    }
}
