#ifndef OECS_INCLUDED
#define OECS_INCLUDED

#include "OrbitalECS/Context.h"

namespace Orbital
{
	namespace ECS
	{
		using EntityID = UUID;
		class Registry;
	} // namespace ECS
} // namespace Orbital

#include "OrbitalECS/Containers.h"

#include "OrbitalECS/Handle.h"

#include "OrbitalECS/Registry.h"

#include "OrbitalECS/BaseEntity.h"

namespace Orbital
{
	namespace ECS
	{
		// IMPLEMENTATIONS
		template <typename T>
		bool Handle<T>::isValid() const
		{
			if (mRegistry->getPool<T>()->tryGet(mEntityID) != nullptr)
				return true;
			else
				return false;
		}
	} // namespace ECS
} // namespace Orbital
#endif
