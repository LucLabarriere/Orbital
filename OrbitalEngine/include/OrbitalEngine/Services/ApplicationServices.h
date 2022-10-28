#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/Services.h"
#include "OrbitalEngine/SharedApplication.h"

#define OCREATE_SERVICE(Name)                                                                                          \
	class Access##Name                                                                                                 \
	{                                                                                                                  \
	public:                                                                                                            \
		void InitializeService()                                                                                       \
		{                                                                                                              \
			Name.Initialize();                                                                                         \
		}                                                                                                              \
		Name##Interface Name;                                                                                          \
                                                                                                                       \
	protected:                                                                                                         \
		Access##Name(const SharedApplication& app) : Name(app)                                                         \
		{                                                                                                              \
		}                                                                                                              \
	}

namespace Orbital
{
	OCREATE_SERVICE(Physics);
	OCREATE_SERVICE(Renderer);
	OCREATE_SERVICE(Scenes);
	OCREATE_SERVICE(ECS);
	OCREATE_SERVICE(ScriptEngine);

	template <typename... Accesses>
	class Services : public Accesses...
	{
	public:
		void InitializeServices()
		{
			(Accesses::InitializeService(), ...);
		}

	protected:
		Services(const SharedApplication& app) : Accesses(app)..., mApp(app)
		{
		}

		friend OrbitalApplication;

		SharedApplication mApp = nullptr;
	};

	using AllServices = Services<AccessPhysics, AccessRenderer, AccessScenes, AccessECS, AccessScriptEngine>;
} // namespace Orbital
