#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalPhysics/Transform.h"
#include "OrbitalEngine/ECS/Handle.h"

namespace Orbital
{	
	using TransformComponent = Physics::Transform;
	using TransformHandle = SafeHandle<TransformComponent>;

	template <>
	OENGINE_API const TransformComponent& SafeHandle<TransformComponent>::operator*() const;
	template <>
	OENGINE_API TransformComponent& SafeHandle<TransformComponent>::operator*();
	template <>
	OENGINE_API bool SafeHandle<TransformComponent>::isValid() const;
} // namespace Orbital
