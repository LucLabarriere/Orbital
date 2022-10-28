#ifndef OECS_INCLUDED
#define OECS_INCLUDED

#include "OrbitalECS/Context.h"

namespace Orbital
{
	using EntityID = UUID;
	class Registry;
}

#include "OrbitalECS/Containers.h"
#include "OrbitalECS/Handle.h"
#include "OrbitalECS/Registry.h"
#include "OrbitalECS/BaseEntity.h"

namespace Orbital
{
	// IMPLEMENTATIONS
	template <typename T>
	bool ComponentHandle<T>::isValid() const
	{
		if (mRegistry->getPool<T>()->tryGet(mEntityID) != nullptr)
			return true;
		else
			return false;
	}
} // namespace Orbital
#endif
