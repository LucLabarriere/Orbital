#pragma once

#include "OrbitalEngine/Graphics/CameraProjection.h"

namespace Orbital
{
	/**
	 * @class OrthographicProjection
	 * @brief Orthographic projection
	 *
	 */
	class OENGINE_API OrthographicProjection : public CameraProjection
	{
	public:
		/**
		 * @brief Constructor
		 */
		OrthographicProjection();

		/**
		 * @brief Destructor
		 */
		virtual ~OrthographicProjection(){};

	protected:
		virtual void update() override;
	};
}
