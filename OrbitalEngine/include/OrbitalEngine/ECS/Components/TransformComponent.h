#pragma once

/* Transform Component
 * - By default : the transform data are stored as TransformComponent
 * (Physics::Transform) in the ECS registry.
 * - If a PhysicsComponent is added to an entity, the TransformComponent
 * object is moved from the ECS registry to the PhysicsComponent object.
 * - If a PhysicsComponent is removed from an entity, the Physics::Transform
 * is moved from the PhysicsComponent object to the ECS registry
 * - Requesting the Transform component using entity.get<TransformComponent>()
 * returns a handle pointing to either of those two objects.
 * - Attempting to remove a Transform component from an object that has a
 * PhysicsComponent raises an error
 * */

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
