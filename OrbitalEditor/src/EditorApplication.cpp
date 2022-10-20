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
        mScriptsLibrary.registerScript("CoreEditorApplication");
        mScriptsLibrary.registerScript("PlayerController");
        NativeScriptManager::SetLibraryLoader(&mScriptsLibrary);
    }

    void EditorApplication::terminate()
    {
        OrbitalApplication::terminate();
    }

    void EditorApplication::update(Time& dt)
    {
        OrbitalApplication::update(dt);
    }

    bool EditorApplication::onKeyPressed(KeyPressedEvent& e)
    {
        if (e.getKey() == OE_KEY_ESCAPE)
        {
            Logger::Log("Reloading scripts");

            // Reset all scripts but keep the managers intact to reconstruct
            for (auto& [ uuid, manager ] : mRegistry.components<NativeScriptManager>())
            {
                // TODO Check here, std::vector useless ?
                std::vector<std::string> names = manager.getScriptNames();
                if (names.size() != 0)
                {
                    manager.clearPointers();
                }
            }

            bool compilationResult = mScriptsLibrary.reload();

            if (compilationResult)
            {
                // Reset the managers and refill them
                for (auto& [ uuid, manager ] : mRegistry.components<NativeScriptManager>())
                {
                    std::vector<std::string> names = manager.getScriptNames();
                    if (names.size() != 0)
                    {
                        manager.clearContainer();
                        
                        for (auto& name : names)
                        {
                            manager.push(name, mRegistry.getEntity(uuid));
                        }
                    }
                }
            }

            Logger::Trace("Done reloading scripts");
        }

        return true;
    }
}
