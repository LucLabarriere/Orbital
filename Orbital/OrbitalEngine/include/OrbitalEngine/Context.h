#pragma once

#ifdef _WIN32

#ifdef ORBITAL_ENGINE_EXPORT
#define ORBITAL_ENGINE_API __declspec(dllexport)
#else
#define ORBITAL_ENGINE_API __declspec(dllimport)
#endif

#else
#define ORBITAL_ENGINE_API
#endif

#include <any>
#include <cstdlib>
#include <functional>
#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "OrbitalInputs/Core.h"

#include "OrbitalTools/Errors.h"
#include "OrbitalTools/Logger.h"
#include "OrbitalTools/Maths.h"
#include "OrbitalTools/Pointers.h"
#include "OrbitalTools/Time.h"
#include "OrbitalTools/UUID.h"

namespace Orbital
{

	/************************
	 * FORWARD DECLARATIONS *
	 * **********************/

	// Third party
	namespace Physics
	{
		struct Transform;
		enum class ColliderType;
	} // namespace Physics

	// ECS
	using EntityID = UUID;
	class Entity;
	class ECSManager;
	template <typename T>
	class SafeHandle;

	// Components
	using TransformComponent = Physics::Transform;
	class PhysicsComponent;
	class NativeScript;
	class MeshComponent;
	class CameraComponent;
	struct MeshFilter;
	using MeshComponentHandle = SafeHandle<MeshComponent>;
	using MeshFilterHandle = SafeHandle<MeshFilter>;
	using TransformHandle = SafeHandle<TransformComponent>;
	using CameraHandle = SafeHandle<CameraComponent>;

	// Graphics
	class HighRenderer;
	class ShaderProgram;
	class VirtualRenderer;
	class BaseRenderer;
	class SphereRenderer;
	class VertexContainer;
	class VertexArray;
	class VertexBuffer;
	class IndexBuffer;
	class VertexContainer;

	// Logic
	class Scene;

	// Services
	template <typename... Args>
	class Services;

	class AccessECS;

} // namespace Orbital
