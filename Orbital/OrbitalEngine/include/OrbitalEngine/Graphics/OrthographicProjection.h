#pragma once

#include "OrbitalEngine/Graphics/CameraProjection.h"

namespace Orbital
{
	/**
	 * @class OrthographicProjection
	 * @brief Orthographic projection
	 *
	 */
	class ORBITAL_ENGINE_API OrthographicProjection : public CameraProjection
	{
	public:
		/**
		 * @brief Constructor
		 */
		OrthographicProjection(const SharedApplication& app);

		/**
		 * @brief Destructor
		 */
		virtual ~OrthographicProjection(){};

	protected:
		virtual void update() override;
	};
} // namespace Orbital
