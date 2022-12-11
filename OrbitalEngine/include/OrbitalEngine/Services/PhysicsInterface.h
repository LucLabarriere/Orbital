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

	class OENGINE_API PhysicsInterface: public ServiceInterface
	{
	public:
		PhysicsInterface();
		PhysicsInterface(const SharedApplication& app);
		void Initialize();

		std::weak_ptr<Physics::Engine> GetInstance() const { return mInstance; }

	private:
		std::weak_ptr<Physics::Engine> mInstance;
	};

	OCREATE_SERVICE(Physics);

} // namespace Orbital
