#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/Components/ColliderComponent.h"
#include "OrbitalEngine/Components/TransformComponent.h"
#include "OrbitalEngine/Services.h"
#include "OrbitalEngine/Services/ECSInterface.h"

namespace Orbital
{
	using PhysicsEngineServices = Services<AccessECS>;

	class OENGINE_API PhysicsEngine : public Services<AccessECS>
	{
	public:
		PhysicsEngine(const SharedApplication& app);

		void initialize();
		void terminate();

		void onUpdate2D(const Time& dt);
		void onUpdate3D(const Time& dt);

		void setVerletSteps(size_t value)
		{
			Logger::Log("N Verlet steps = ", value);
			mVerletSteps = value;
		}
		size_t getVerletSteps() const
		{
			return mVerletSteps;
		}

		template <typename T>
		void verletIntegration(const Time& dt, std::unordered_map<EntityID, T>& bodies);

	private:
		friend class PhysicsInterface;

		size_t mVerletSteps = 4;
		std::function<void(Collision2D, const Time&)> mCollision2DSolver = [](Collision2D collision, const Time& dt) {};
		std::function<void(Collision3D, const Time&)> mCollision3DSolver = [](Collision3D collision, const Time& dt) {};
	};
} // namespace Orbital
