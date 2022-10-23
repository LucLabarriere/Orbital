#include "OrbitalEditor/EditorApplication.h"
#include "OrbitalEngine/Components.h"
#include "OrbitalEngine/Components/NativeScriptManager.h"
#include "OrbitalEngine/Components/TransformComponent.h"
#include "OrbitalInputs/Event.h"
#include "OrbitalTools/Random.h"
#include "OrbitalScripts/PlayerController.h"

namespace Orbital
{
    EditorApplication::EditorApplication()
        : OrbitalApplication()
    {

    }
    
    void EditorApplication::initialize()
    {
        OrbitalApplication::initialize();
        initializeScripts();
    }

    void EditorApplication::terminate()
    {
        OrbitalApplication::terminate();
    }

    void EditorApplication::onLoad()
    {
        auto e = mServices.ECS.CreateEntity();
        e.get<NativeScriptManager>()->push("CoreEditorApplication", e);
    }

    void EditorApplication::update(const Time& dt)
    {
        OrbitalApplication::update(dt);
    }

    bool EditorApplication::onKeyPressed(KeyPressedEvent& e)
    {
        if (e.getKey() == OE_KEY_ESCAPE)
        {
            Logger::Log("Reloading scripts");
            mServices.ECS.Reset();

            bool compilationSucceeded = mServices.ScriptEngine.Reload();

            if (compilationSucceeded)
            {
                onLoad(); // Initializing application specific stuff
                mServices.Scenes.OnLoad();
                mServices.Scenes.OnStart();
            }

            Logger::Trace("Done reloading scripts");
        }

        return true;
    }

    void EditorApplication::initializeScripts()
    {
        mServices.ScriptEngine.RegisterScript("CoreEditorApplication");
        mServices.ScriptEngine.RegisterScript("PlayerController");
    }
}
