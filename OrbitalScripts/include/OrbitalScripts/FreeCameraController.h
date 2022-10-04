#pragma once

#include "OrbitalScripts/Context.h"
#include "OrbitalEngine/Events.h"
#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Logic/NativeScript.h"
#include "OrbitalEngine/Components/Camera.h"

namespace Orbital
{
	class OESCRIPTS_API FreeCameraController : public NativeScript
	{
	public:
		FreeCameraController(const Entity& e);
		FreeCameraController(const FreeCameraController& other);
		Ref<NativeScript> Make(const Entity& e) { return CreateRef<FreeCameraController>(e); }

		virtual void OnLoad() override;
		virtual void OnStart() override;
		virtual void OnUpdate(Time dt) override;
		virtual bool OnKeyPressed(const KeyPressedEvent& e) override;
		virtual bool OnMouseScrolled(const MouseScrolledEvent& e) override;

		void Rotate(const Vec2& rotation);
		void SetPosition(const Vec3& position);
		void SetTranslationSpeed(float speed);
		void SetRotationSpeed(float speed);
		void SetZoomSpeed(float speed);

		float& GetTranslationSpeed();
		float& GetRotationSpeed();
		float& GetZoomSpeed();
		float GetTranslationSpeed() const;
		float GetRotationSpeed() const;
		float GetZoomSpeed() const;

	private:
		Camera* mCamera = nullptr;
		float mTranslationSpeed = 10.0f;
		float mRotationSpeed = 35.0f;
		float mZoomSpeed = 0.1f;
		Vec2 mFormerMousePosition = { 0.0f, 0.0f };
	};
}