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

		Maths::Mat4 model(1.0f);
		model = Maths::Rotate(model, rotation.x, { 1.0f, 0.0f, 0.0f });
		model = Maths::Rotate(model, rotation.y, { 0.0f, 1.0f, 0.0f });
		model = Maths::Rotate(model, rotation.z, { 0.0f, 0.0f, 1.0f });

		mUp = model * Maths::Vec4{ 0.0f, 1.0f, 0.0f, 1.0f };
		mFront = model * Maths::Vec4{ 0.0f, 0.0f, 1.0f, 1.0f };
		mRight = Maths::Cross(mFront, mUp);

		mView = Maths::LookAt(position, mFront + position, mUp);
	}
} // namespace Orbital
