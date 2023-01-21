#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/Services/SettingsInterface.h"

namespace Orbital
{
	using CameraProjectionServices = Services<AccessSettings>;

	/**
	 * @class CameraProjection
	 * @brief Type of projection (Orthographic or Perspective)
	 *
	 */
	class ORBITAL_ENGINE_API CameraProjection : public CameraProjectionServices
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
		CameraProjection(const SharedApplication& app, CameraProjection::Type type)
			: CameraProjectionServices(app), mType(type)
		{
			CameraProjectionServices::InitializeServices();
		}

		/**
		 * @brief Destructor
		 */
		virtual ~CameraProjection(){};

		/**
		 * @brief Returns the projection matrix
		 */
		inline const Maths::Mat4& getMatrix()
		{
			update();
			return mMatrix;
		}

	protected:
		virtual void update() = 0;

	protected:
		CameraProjection::Type mType;
		Maths::Mat4 mMatrix = Maths::Mat4(1.0f);
	};
} // namespace Orbital
