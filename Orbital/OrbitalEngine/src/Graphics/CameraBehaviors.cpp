#include "OrbitalEngine/ECS/Components/TransformComponent.h"
#include "OrbitalEngine/Graphics/FreeCamera.h"
#include "OrbitalEngine/Graphics/LockedCamera.h"
#include "OrbitalEngine/Settings.h"
#include <glm/gtx/rotate_vector.hpp>

namespace Orbital
{
	CameraBehavior::CameraBehavior(
		const SharedApplication& app, const TransformHandle& transform,
		CameraBehavior::Type type
	)
		: CameraServices(app), mTransform(transform), mType(type)
	{
		CameraServices::InitializeServices();
	}

	void CameraBehavior::lookAt(const Maths::Vec3& target)
	{
		auto& transform = *mTransform;
		const auto& p = transform.position;

		// Maths::Vec3 front = { 0.0f, 0.0f, 1.0f };
		// Maths::Vec3 direction = Maths::Normalize(target - p);
		// float angle = Maths::Acos(Maths::Dot(direction, front));
		// Maths::Quaternion quaternion = Maths::AngleAxis(angle,
		// Maths::Normalize(Maths::Cross(front, direction)));

		// transform.rotation = Maths::EulerAngles(quaternion);
		const auto& up = Settings.Get<Maths::Vec3>(Setting::WorldUp);

		const Maths::Vec3 f(normalize(target - p));
		const Maths::Vec3 s(normalize(cross(f, up)));
		const Maths::Vec3 u(cross(s, f));

		float pitch = Maths::Asin(-f.y);
		float yaw = Maths::Atan2(f.x, f.z);
		float roll = Maths::Atan2(s.y, u.y);

		transform.rotation = Maths::Vec3(pitch, yaw, roll);
	}

	auto CameraBehavior::getTransform() const -> const TransformHandle&
	{
		return mTransform;
	}

	auto CameraBehavior::getPosition() const -> const Maths::Vec3&
	{
		return mTransform->position;
	}

	LockedCamera::LockedCamera(
		const SharedApplication& app, const TransformHandle& transform
	)
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
		const Maths::Vec4 front = { 0.0f, 0.0f, 1.0f, 1.0f };
		const auto& transform = *mTransform;
		const Maths::Vec3& p = transform.position;

		Maths::Quaternion quaternion(transform.rotation);
		Maths::Mat4 rotationMatrix = Maths::Mat4Cast(quaternion);

		mFront = Maths::Normalize(Maths::Vec3(rotationMatrix * front));
		mRight = Maths::Normalize(Maths::Cross(mFront, up));
		mUp = Maths::Normalize(Maths::Cross(mRight, mFront));

		mView = Maths::Mat4({
			{ mRight[0], mUp[0], -mFront[0], 0 },
			{ mRight[1], mUp[1], -mFront[1], 0 },
			{ mRight[2], mUp[2], -mFront[2], 0 },
			{ -Maths::Dot(mRight, p), -Maths::Dot(mUp, p), Maths::Dot(mFront, p), 1 },
		});
	}
} // namespace Orbital
