#include "OrbitalEngine/ECS/Components/TransformComponent.h"
#include "OrbitalEngine/Graphics/FreeCamera.h"
#include "OrbitalEngine/Graphics/LockedCamera.h"
#include <glm/gtx/quaternion.hpp>
namespace Orbital
{
	CameraBehavior::CameraBehavior(
		const SharedApplication& app, const TransformHandle& transform, CameraBehavior::Type type
	)
		: CameraServices(app), mTransform(transform), mType(type)
	{
		CameraServices::InitializeServices();
	}

	void CameraBehavior::lookAt(const Maths::Vec3& target)
	{
		auto& transform = *mTransform;
		const auto& p = transform.position;
		auto& r = transform.rotation;

		mFront = - Maths::Normalize(target - p);
		Maths::Vec3 rotationAxis = Maths::Cross(mFront, Maths::Vec3{ 0.0f, 0.0f, 1.0f });
		float angle = Maths::Asin(Maths::Magnitude(rotationAxis));
		LOGVAR(Maths::Degree(rotationAxis));

		r = rotationAxis;
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
		const auto& up = Settings.Get<Maths::Vec3>(Setting::WorldUp);
		const auto& transform = *mTransform;
		Maths::Vec3 r = transform.rotation;
		glm::quat quaternion = glm::quat(r);
		Maths::Mat4 rotationMatrix = glm::toMat4(quaternion);
		// Maths::Mat4 rotationMatrix = glm::quat() glm::eulerAngleYXZ(r.y, r.x, r.z);

		mFront = rotationMatrix * Maths::Vec4{ 0.0f, 0.0f, 1.0f, 1.0f };

		mFront = Maths::Normalize(mFront);
		mRight = Maths::Normalize(Maths::Cross(mFront, up));
		mUp = Maths::Normalize(Maths::Cross(mRight, mFront));

		mView = Maths::LookAt(transform.position, mFront + transform.position, Maths::Vec3{ 0.0f, 1.0f, 0.0f });
	}
} // namespace Orbital
