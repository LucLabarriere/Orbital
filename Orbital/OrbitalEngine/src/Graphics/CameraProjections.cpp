#include "OrbitalEngine/Graphics/OrthographicProjection.h"
#include "OrbitalEngine/Graphics/PerspectiveProjection.h"

namespace Orbital
{
	OrthographicProjection::OrthographicProjection()
		: CameraProjection(CameraProjection::Type::Orthographic)
	{

	}

	void OrthographicProjection::update()
	{
		mMatrix = Maths::Orthographic(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	}

	PerspectiveProjection::PerspectiveProjection()
		: CameraProjection(CameraProjection::Type::Perspective)
	{

	}

	void PerspectiveProjection::update()
	{
		mMatrix = Maths::Perspective(Maths::Radian(60.0f), 640.0f / 480.0f, 0.1f, 100.0f);
	}

}
