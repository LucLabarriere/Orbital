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

		Window& GetWindow();
		const WeakRef<HighRenderer>& Get() const { return mInstance; }
		void OnUpdate();

	private:
		WeakRef<HighRenderer> mInstance;
	};

	OCREATE_SERVICE(Renderer);

} // namespace Orbital
