#pragma once

#include "OrbitalEngine/Context.h"

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
		Access##Name() : Name()                                                                                        \
		{                                                                                                              \
		}                                                                                                              \
		Access##Name(const SharedApplication& app) : Name(app)                                                         \
		{                                                                                                              \
		}                                                                                                              \
	}

namespace Orbital
{
	template <typename... Accesses>
	class Services : public Accesses...
	{
	public:
		void InitializeServices()
		{
			(Accesses::InitializeService(), ...);
		}

	protected:
		Services() : Accesses()..., mApp()
		{
		}
		Services(const SharedApplication& app) : Accesses(app)..., mApp(app)
		{
		}

		friend OrbitalApplication;
		SharedApplication mApp;
	};
} // namespace Orbital
