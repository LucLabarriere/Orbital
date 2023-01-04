#include "OrbitalEngine/ECS/Components/TransformComponent.h"
#include "OrbitalEngine/Graphics/FreeCamera.h"
#include "OrbitalEngine/Graphics/LockedCamera.h"

namespace Orbital
{
	CameraBehavior::CameraBehavior(
		const SharedApplication& app, const TransformHandle& transform, CameraBehavior::Type type
	)
		: CameraServices(app), mTransform(transform), mType(type)
	{
		CameraServices::InitializeServices();
	}

	const TransformHandle& CameraBehavior::getTransform() const
	{
		return mTransform;
	}

	const Maths::Vec3& CameraBehavior::getPosition() const
	{
		return mTransform->position;
	}

	LockedCamera::LockedCamera(const SharedApplication& app, const TransformHandle& transform)
		: CameraBehavior(app, transform, CameraBehavior::Type::Locked)
	{
	}

	void LockedCamera::updateView()
	{
	}

	FreeCamera::FreeCamera(const SharedApplication& app, const TransformHandle& transform)
		: CameraBehavior(app, transform, CameraBehavior::Type::Free)
	{
	}

	void FreeCamera::updateView()
	{
		const auto& transform = *mTransform;
		const Maths::Vec3& position = transform.position;
		const Maths::Vec3& rotation = transform.rotation;

		mFront.x = Maths::Cos(rotation.y) * Maths::Cos(rotation.x);
		mFront.y = Maths::Sin(rotation.x);
		mFront.z = Maths::Sin(rotation.y) * Maths::Cos(rotation.x);

		mFront = Maths::Normalize(mFront);
		mRight = Maths::Normalize(Maths::Cross(mFront, Maths::Vec3{ 0.0f, 1.0f, 0.0f }));
		mUp = Maths::Normalize(Maths::Cross(mRight, mFront));

		mView = Maths::LookAt(position, mFront + position, { 0.0f, 1.0f, 0.0f });
	}
} // namespace Orbital
