#pragma once

#include "OrbitalTools/UUID.h"
#include "OrbitalECS/Pool.h"

namespace Orbital
{
	class Registry;

	template <typename T>
	class Handle
	{
	public:
		Handle() { }
		operator T& () const { return *mPtr; }
		UUID GetUUID() const { return mUUID; }
		T* operator->() const { return mPtr; }
		T& operator*() const { return *mPtr; }

	private:
		Handle(const UUID& uuid, T* ptr) : mUUID(uuid), mPtr(ptr) { }

	private:
		friend Registry;

		UUID mUUID = UUID::Null();
		T* mPtr = nullptr;
	};
}

