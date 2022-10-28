#pragma once

#include "OrbitalEngine/Components/MeshComponent.h"
#include "OrbitalEngine/Entity.h"
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
		MeshComponentHandle PushMeshComponent(Entity& e, MeshType meshType, const TransformHandle& transform);

		Window& GetWindow();
		void OnUpdate();

	private:
		friend OrbitalApplication;
		HighRenderer* mInstance = nullptr;
	};
} // namespace Orbital
