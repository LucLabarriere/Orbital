#pragma once

#include "OrbitalEngine/Graphics/MeshRenderers/VirtualRenderer.h"

namespace Orbital
{
	class ORBITAL_ENGINE_API SphereRenderer : public VirtualRenderer
	{
	public:
		SphereRenderer() : VirtualRenderer() {}

		virtual ~SphereRenderer() override {}

		virtual void initialize() override;
		virtual void terminate() override;
		virtual void readyRender(const MeshComponent& mc) const override;
	};
} // namespace Orbital
