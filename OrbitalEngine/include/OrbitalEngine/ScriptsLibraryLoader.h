#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalLogger/Logger.h"
#include "OrbitalEngine/Components/NativeScript.h"
#include "OrbitalTools/Services.h"

namespace Orbital
{
    namespace Services { class ScriptEngine; }

    class OENGINE_API ScriptsLibraryLoader
    {
    public:
        ScriptsLibraryLoader() { open(); };
        void open();
        void close();
        bool reload();
        void registerScript(const std::string& scriptName);
        NativeScript* createScript(const std::string& scriptName, const Entity& e);
        bool recompileLibrary();
        bool lastCompilationSucceeded() const { return mSucceeded; }

    private:
        void saveScriptNames();

    private:
        void* mLibrary = nullptr;
        std::unordered_map<std::string, CreateNativeScript_t*> mCreators;
        std::unordered_set<std::string> mScriptNames;
        bool mSucceeded = true;
    };

    namespace Services
    {
        class ScriptEngine : private UniqueService<Orbital::ScriptsLibraryLoader>
        {
        public:
            static inline bool LastCompilationSucceeded() { return sPtr->lastCompilationSucceeded(); }
            static inline void RegisterScript(const std::string& scriptName) { sPtr->registerScript(scriptName); }

        protected:
            friend Orbital::OrbitalApplication;

            static inline void Terminate() { sPtr->close(); }
            static inline NativeScript* CreateScript(const std::string& scriptName, const Entity& e) { return sPtr->createScript(scriptName, e); }
            static inline bool Reload() { return sPtr->reload(); }
        };
    }
}
