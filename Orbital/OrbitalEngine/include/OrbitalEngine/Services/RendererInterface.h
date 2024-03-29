#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/Services.h"
#include "OrbitalEngine/Services/ServiceInterface.h"
#include "OrbitalRenderer/Window.h"

namespace Orbital
{
	// Forward declarations
	class HighRenderer;
	class CameraComponent;
	class MeshComponent;
	template <typename T>
	class SafeHandle;
	using MeshComponentHandle = SafeHandle<MeshComponent>;
	using CameraHandle = SafeHandle<CameraComponent>;
	//

	class ORBITAL_ENGINE_API RendererInterface : public ServiceInterface
	{
	public:
		RendererInterface();
		RendererInterface(const SharedApplication& app);
		void InitializeInterface();

		void Draw(MeshComponent& mc);
		void BindCamera();
		void RegisterMeshComponent(const MeshComponentHandle& meshComponent);
		void UnregisterMeshComponent(const EntityID& id);
		void ClearComponents();
		void SetCamera(const CameraHandle& camera);

		[[nodiscard]] auto Get() const -> const WeakRef<HighRenderer>&
		{
			return mInstance;
		}
		void OnUpdate();

	private:
		WeakRef<HighRenderer> mInstance;
	};

	OCREATE_SERVICE(Renderer);

} // namespace Orbital
