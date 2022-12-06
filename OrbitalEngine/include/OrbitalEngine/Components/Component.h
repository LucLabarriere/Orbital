#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/Handle.h"
#include "OrbitalEngine/Entity.h"

namespace Orbital
{
	template <typename T>
	class Component : Handle<T>
	{
	public:
		Component(T* instance, const Entity& entity) : Handle<T>(instance), mEntity(entity)
		{
		}
		virtual ~Component()
		{
		}

		virtual bool isValid()
		{
			// get the Component from the entity, if it is the same as the current one, say it is valid
			return false;
		}

	private:
		Entity mEntity;
	};
} // namespace Orbital
