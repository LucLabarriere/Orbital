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
        auto e = Services::Scene::CreateEntity();
        e.push<NativeScriptManager>()->push("CoreEditorApplication", e);
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
            Services::Scene::Reset();

            bool compilationSucceeded = Services::ScriptEngine::Reload();

            if (compilationSucceeded)
            {
                onLoad(); // Initializing application specific stuff
                Services::Scene::OnLoad();
                Services::Scene::OnStart();
            }

            Logger::Trace("Done reloading scripts");
        }

        return true;
    }

    void EditorApplication::initializeScripts()
    {
        Services::ScriptEngine::RegisterScript("CoreEditorApplication");
        Services::ScriptEngine::RegisterScript("PlayerController");
    }
}
