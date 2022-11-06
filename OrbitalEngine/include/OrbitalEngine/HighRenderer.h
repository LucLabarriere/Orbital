#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/Components/MeshComponent.h"
#include "OrbitalEngine/MeshRenderers/VirtualRenderer.h"
#include "OrbitalEngine/Services.h"
#include "OrbitalEngine/Services/ECSInterface.h"
#include "OrbitalRenderer/LowRenderer.h"

namespace Orbital
{
	class VertexContainer;
	class BaseRenderer;
	class SphereRenderer;

	using HighRendererServices = Services<AccessECS>;

	class OENGINE_API HighRenderer : public HighRendererServices
	{
	public:
		HighRenderer(const SharedApplication& app);
		virtual ~HighRenderer();

		void initialize();
		void terminate();

		void draw(const MeshComponent& mc) const;
		void onUpdate() const;

		void render(const std::shared_ptr<BaseRenderer>& renderer) const;
		void render(const std::shared_ptr<SphereRenderer>& renderer) const;

		Window& getWindow()
		{
			return mLowRenderer.getWindow();
		}
		MeshComponentHandle pushMeshComponent(Entity& e, const MeshFilterHandle& meshFilter, const TransformHandle& transform);

	private:
		LowRenderer mLowRenderer;

		std::unordered_map<MeshRendererType, std::shared_ptr<VirtualRenderer>> mMeshRenderers;
	};
} // namespace Orbital
