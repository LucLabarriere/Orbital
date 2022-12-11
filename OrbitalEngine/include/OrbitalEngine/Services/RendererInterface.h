#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/ECS/Components/MeshComponent.h"
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
		RendererInterface();
		RendererInterface(const SharedApplication& app);
		void Initialize();

		void Draw(MeshComponent& mc);
		MeshComponentHandle PushMeshComponent(Entity& e, const MeshFilterHandle& meshFilter, const TransformHandle& transform);

		Window& GetWindow();
		void OnUpdate();

	private:
		std::weak_ptr<HighRenderer> mInstance;
	};

	OCREATE_SERVICE(Renderer);

} // namespace Orbital
