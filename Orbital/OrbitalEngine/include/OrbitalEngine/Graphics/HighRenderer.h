#pragma once

#include "OrbitalEngine/Context.h"

// #include "OrbitalEngine/ECS/Components/MeshComponent.h"
#include "OrbitalEngine/ECS/Components/MeshFilter.h"
#include "OrbitalEngine/ECS/Components/TransformComponent.h"
#include "OrbitalEngine/Graphics/MeshRenderers/VirtualRenderer.h"
#include "OrbitalEngine/Services.h"
#include "OrbitalEngine/Services/ECSInterface.h"
#include "OrbitalEngine/Services/StatisticsInterface.h"

#include "OrbitalRenderer/LowRenderer.h"

namespace Orbital
{
	using HighRendererServices = Services<AccessECS, AccessStatistics>;

	/**
	 * @class HighRenderer
	 * @brief High level renderer class
	 *
	 * @todo Add an overload that can use Collider to initialize a meshComponent
	 * @todo Rename MeshComponent to RenderComponent
	 */
	class ORBITAL_ENGINE_API HighRenderer : public HighRendererServices
	{
	public:
		HighRenderer(const SharedApplication& app);
		HighRenderer(const HighRenderer&) = delete;
		HighRenderer(HighRenderer&&) = delete;
		virtual ~HighRenderer() = default;

		auto initialize(unsigned int windowWidth, unsigned int windowHeight)
			-> Option<Error>;
		auto terminate() -> void;

		auto draw(const MeshComponent& mc) -> void;
		auto bindCamera() -> void;
		auto onUpdate() -> void;

		/**
		 * @brief Get the renderer of the given MeshType
		 *
		 * @todo Move to the cpp file
		 *
		 * @param meshType
		 */
		auto getRenderer(MeshType meshType) -> WeakRef<VirtualRenderer>
		{
			WeakRef<VirtualRenderer> renderer;

			if (meshType == MeshType::Sphere)
			{
				return mMeshRenderers.at(MeshRendererType::Sphere);
			}
			else // Triangle, Quad, Cube
			{
				return mMeshRenderers.at(MeshRendererType::Base);
			}
		}

		auto registerMeshComponent(const MeshComponentHandle& meshComponent) -> void;
		auto unregisterMeshComponent(const EntityID& id) -> void;
		auto clearComponents() -> void;
		auto clearComponents(const EntityID& id) -> void;
		auto setRenderOrder(const EntityID& id, size_t position) -> void;
		auto setCamera(const CameraHandle& camera) -> void;
		[[nodiscard]] auto getWindow() -> UniqueHandle<Window>;

	private:
		LowRenderer mLowRenderer;
		CameraHandle mCamera;
		CameraHandle mDebugCamera;
		std::map<MeshRendererType, Ref<VirtualRenderer>> mMeshRenderers;
		std::map<EntityID, MeshComponentHandle> mMeshComponents;
	};
} // namespace Orbital
