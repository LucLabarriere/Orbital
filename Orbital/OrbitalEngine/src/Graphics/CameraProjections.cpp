#include "OrbitalEngine/Graphics/OrthographicProjection.h"
#include "OrbitalEngine/Graphics/PerspectiveProjection.h"
#include "OrbitalEngine/SettingsManager.h"

namespace Orbital
{
	OrthographicProjection::OrthographicProjection(const SharedApplication& app)
		: CameraProjection(app, CameraProjection::Type::Orthographic)
	{
	}

	void OrthographicProjection::update()
	{
		mMatrix = Maths::Orthographic(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	}

	PerspectiveProjection::PerspectiveProjection(const SharedApplication& app)
		: CameraProjection(app, CameraProjection::Type::Perspective)
	{
	}

	void PerspectiveProjection::update()
	{
		mMatrix = Maths::Perspective(
			Maths::Radian(Settings.Get<float>(Setting::FOV)),
			(float)Settings.Get<unsigned int>(Setting::WindowWidth) /
				(float)Settings.Get<unsigned int>(Setting::WindowHeight),
			0.1f, 100.0f
		);
	}
} // namespace Orbital
