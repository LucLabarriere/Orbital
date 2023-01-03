#pragma once

#include "OrbitalEngine/Graphics/CameraProjection.h"

namespace Orbital
{
	/**
	 * @class PerspectiveProjection
	 * @brief Perspective projection
	 */
	class OENGINE_API PerspectiveProjection : public CameraProjection
	{
	public:
		/**
		 * @brief Constructor
		 */
		PerspectiveProjection();

		/**
		 * @brief Destructor
		 */
		virtual ~PerspectiveProjection(){};

	protected:
		virtual void update() override;
	};
}
