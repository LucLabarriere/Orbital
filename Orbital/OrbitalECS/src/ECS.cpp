#include "OrbitalECS/ECS.h"

namespace Orbital::ECS
{
	auto Registry::createEntity() -> BaseEntity
	{
		BaseEntity e(this, *mEntities.emplace().first);

		return e;
	}

	void Registry::deleteEntity(const EntityID& id)
	{
		auto entity = mEntities.find(id);
		Orbital::Assert(entity != mEntities.end(), "the entity does not exist");

		for (auto& [typeId, pool] : mPools)
		{
			pool->tryRemove(id);
		}

		mEntities.erase(id);
	}

	auto Registry::getEntity(const EntityID& id) -> BaseEntity
	{
		auto entity = mEntities.find(id);
		return { this, *entity };
	}
} // namespace Orbital::ECS
