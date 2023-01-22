#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/ECS/Handle.h"
#include "OrbitalPhysics/Transform.h"

namespace Orbital
{
	using TransformComponent = Physics::Transform;
	using TransformHandle = SafeHandle<TransformComponent>;

	template <>
	auto SafeHandle<TransformComponent>::operator*() const
		-> ORBITAL_ENGINE_API const TransformComponent&;

	template <>
	ORBITAL_ENGINE_API auto SafeHandle<TransformComponent>::operator*()
		-> TransformComponent&;

	template <>
	ORBITAL_ENGINE_API [[nodiscard]] auto SafeHandle<TransformComponent>::isValid() const
		-> bool;
} // namespace Orbital
