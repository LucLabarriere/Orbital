#pragma once

#include "OrbitalEngine/Components/DynamicsComponent.h"
#include "OrbitalEngine/Components/TransformComponent.h"
#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/Physics/Collider.h"
#include "OrbitalTools/Maths.h"
#include "OrbitalTools/Time.h"

namespace Orbital
{
	class OENGINE_API BaseSolver
	{
	public:
		virtual void solve(const Collision& collision, const Time& dt) = 0;
	};

	class OENGINE_API Solver : public BaseSolver
	{
	public:
		virtual void solve(const Collision& collision, const Time& dt) override;
	};
} // namespace Orbital
