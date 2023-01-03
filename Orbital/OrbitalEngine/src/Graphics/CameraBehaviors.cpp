#include "OrbitalEngine/Graphics/FreeCamera.h"
#include "OrbitalEngine/Graphics/LockedCamera.h"
#include "OrbitalEngine/ECS/Components/TransformComponent.h"

namespace Orbital
{
	CameraBehavior::CameraBehavior(const TransformHandle& transform, CameraBehavior::Type type)
		: mTransform(transform), mType(type)
	{
	}

	const TransformHandle& CameraBehavior::getTransform() const
	{
		return mTransform;
	}

	const Maths::Vec3& CameraBehavior::getPosition() const
	{
		return mTransform->position;
	}

	LockedCamera::LockedCamera(const TransformHandle& transform)
		: CameraBehavior(transform, CameraBehavior::Type::Locked)
	{
	}
	
	void LockedCamera::updateView()
	{
	}

	FreeCamera::FreeCamera(const TransformHandle& transform) : CameraBehavior(transform, CameraBehavior::Type::Free)
	{
	}

	void FreeCamera::updateView()
	{

	}
} // namespace Orbital
