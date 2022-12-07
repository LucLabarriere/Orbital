#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/ECS/Components/MeshComponent.h"
#include "OrbitalEngine/Graphics/MeshRenderers/VirtualRenderer.h"
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

		Window& getWindow()
		{
			return mLowRenderer.getWindow();
		}
		// TODO Add an overload that can use Collider to initialize a meshComponent
		// TODO Rename MeshComponent to RenderComponent
		MeshComponentHandle pushMeshComponent(Entity& e, const MeshFilterHandle& meshFilter, const TransformHandle& transform);

	private:
		LowRenderer mLowRenderer;

		std::unordered_map<MeshRendererType, std::shared_ptr<VirtualRenderer>> mMeshRenderers;
	};
} // namespace Orbital
