#pragma once

#include "OrbitalEngine/Graphics/CameraProjection.h"

namespace Orbital
{
	/**
	 * @class PerspectiveProjection
	 * @brief Perspective projection
	 */
	class ORBITAL_ENGINE_API PerspectiveProjection : public CameraProjection
	{
	public:
		/**
		 * @brief Constructor
		 */
		PerspectiveProjection(const SharedApplication& app);

		/**
		 * @brief Destructor
		 */
		virtual ~PerspectiveProjection(){};

	protected:
		virtual void update() override;
	};
} // namespace Orbital
