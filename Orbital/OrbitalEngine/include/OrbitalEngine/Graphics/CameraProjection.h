#pragma once

#include "OrbitalEngine/Context.h"

namespace Orbital
{
	/**
	 * @class CameraProjection
	 * @brief Type of projection (Orthographic or Perspective)
	 *
	 */
	class OENGINE_API CameraProjection
	{
	public:
		enum class Type
		{
			Orthographic = 0,
			Perspective
		};

		/**
		 * @brief Constructor
		 *
		 * @param type [projection type]
		 */
		CameraProjection(CameraProjection::Type type) : mType(type){};

		/**
		 * @brief Destructor
		 */
		virtual ~CameraProjection(){};

		/**
		 * @brief Returns the projection matrix
		 */
		virtual const Maths::Mat4& getMatrix();

	protected:
		virtual void update() = 0;

	protected:
		CameraProjection::Type mType;
		Maths::Mat4 mMatrix = Maths::Mat4(1.0f);
	};
}
