#include "OrbitalEngine/Physics/Solver.h"

namespace Orbital
{

	void Solver::solve(const Collision& collision, const Time& dt)
	{
		auto dynamicsA = collision.A.get<DynamicsComponent>();
		auto dynamicsB = collision.B.get<DynamicsComponent>();

		auto colliderA = collision.A.get<Collider>();
		auto colliderB = collision.B.get<Collider>();

		{
			if (dynamicsA.isValid())
			{
				dynamicsA->force += collision.points.vector * 100.0f;
			}

			if (dynamicsB.isValid())
			{
				dynamicsB->force -= collision.points.vector * 100.0f;
			}
		}

		if (colliderA->isTrigger())
			colliderA->trigger();

		if (colliderB->isTrigger())
			colliderB->trigger();
	}
} // namespace Orbital
