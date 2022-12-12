#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/Services.h"
#include "OrbitalEngine/Services/ServiceInterface.h"

namespace Orbital
{
	namespace Physics
	{
		class Engine;
	}

	class OENGINE_API PhysicsEngineInterface: public ServiceInterface
	{
	public:
		PhysicsEngineInterface();
		PhysicsEngineInterface(const SharedApplication& app);
		void Initialize();

		std::weak_ptr<Physics::Engine> Get() const { return mInstance; }

	private:
		std::weak_ptr<Physics::Engine> mInstance;
	};

	OCREATE_SERVICE(PhysicsEngine);

} // namespace Orbital