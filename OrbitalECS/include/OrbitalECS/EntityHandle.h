#pragma once

#include "OrbitalTools/UUID.h"

namespace Orbital
{
	class EntityHandle
	{
	public:
		EntityHandle(const UUID& uuid, size_t id) : mUUID(uuid), mId(id) { }
		const UUID& GetUUID() const { return mUUID; }
		size_t GetID() const { return mId; }

	private:
		UUID mUUID;
		size_t mId;
	};
}
