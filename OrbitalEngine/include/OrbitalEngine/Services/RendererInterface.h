#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/Components/MeshComponent.h"
#include "OrbitalEngine/ECS/Entity.h"
#include "OrbitalEngine/Services.h"
#include "OrbitalEngine/Services/ServiceInterface.h"
#include "OrbitalRenderer/Window.h"

namespace Orbital
{
	class HighRenderer;

	class OENGINE_API RendererInterface : public ServiceInterface
	{
	public:
		RendererInterface(const SharedApplication& app);
		void Initialize();

		void Draw(MeshComponent& mc);
		MeshComponentHandle PushMeshComponent(Entity& e, const MeshFilterHandle& meshFilter, const TransformHandle& transform);

		Window& GetWindow();
		void OnUpdate();

	private:
		HighRenderer* mInstance = nullptr;
	};

	OCREATE_SERVICE(Renderer);

} // namespace Orbital
