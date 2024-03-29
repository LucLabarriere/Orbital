#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/ECS/Handle.h"
#include "OrbitalPhysics/Transform.h"

namespace Orbital
{
	using TransformComponent = Physics::Transform;
	using TransformHandle = SafeHandle<TransformComponent>;

	template <>
	ORBITAL_ENGINE_API auto SafeHandle<TransformComponent>::operator*() const -> const TransformComponent&;

	template <>
	ORBITAL_ENGINE_API auto SafeHandle<TransformComponent>::operator*() -> TransformComponent&;

	template <>
	[[nodiscard]] ORBITAL_ENGINE_API auto SafeHandle<TransformComponent>::isValid() const -> bool;
} // namespace Orbital
