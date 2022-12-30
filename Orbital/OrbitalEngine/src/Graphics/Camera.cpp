#include "OrbitalEngine/Graphics/Camera.h"
#include "OrbitalEngine/ECS/Components/TransformComponent.h"

namespace Orbital
{
	CameraBehavior::CameraBehavior(const TransformHandle& transform, CameraBehavior::Type type)
		: mTransform(transform), mType(type)
	{
	}

	LockedCamera::LockedCamera(const TransformHandle& transform)
		: CameraBehavior(transform, CameraBehavior::Type::Locked)
	{
	}

	FreeCamera::FreeCamera(const TransformHandle& transform) : CameraBehavior(transform, CameraBehavior::Type::Free)
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

	Maths::Mat4 CameraBehavior::getLookAtMatrix() const
	{
		return Maths::LookAt(mTransform->position, getTargetVector(), mUp);
	}

	Maths::Vec3 LockedCamera::getTargetVector() const
	{
		return mVector;
	}

	Maths::Vec3 FreeCamera::getTargetVector() const
	{
		return mVector + mTransform->position;
	}

	OrthographicProjection::OrthographicProjection()
		: CameraProjection(CameraProjection::Type::Orthographic)
	{

	}

	Maths::Mat4 OrthographicProjection::getMatrix() const
	{
		return Maths::Orthographic(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	}

	PerspectiveProjection::PerspectiveProjection()
		: CameraProjection(CameraProjection::Type::Perspective)
	{
	}

	Maths::Mat4 PerspectiveProjection::getMatrix() const
	{
		return Maths::Perspective(Maths::Radian(60.0f), 640.0f / 480.0f, 0.1f, 100.0f);
	}


} // namespace Orbital
