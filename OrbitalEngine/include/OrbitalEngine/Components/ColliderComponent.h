#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/Components/Physics2D/RigidBody2D.h"
#include "OrbitalEngine/Components/Physics3D/RigidBody3D.h"
#include "OrbitalEngine/Components/TransformComponent.h"
#include "OrbitalEngine/Entity.h"

namespace Orbital
{
	struct Collision2DPoints
	{
		Maths::Vec2 A = { 0.0f, 0.0f };
		Maths::Vec2 B = { 0.0f, 0.0f };
		Maths::Vec2 penetrationVector = { 0.0f, 0.0f };
		Maths::Vec2 normal = { 0.0f, 0.0f };
		float relativeSpeed = 0.0f;
		float penetrationDistance = 0.0f;
		bool collide = false;
	};

	struct Collision3DPoints
	{
		Maths::Vec3 A = { 0.0f, 0.0f, 0.0f };
		Maths::Vec3 B = { 0.0f, 0.0f, 0.0f };
		Maths::Vec3 penetrationVector = { 0.0f, 0.0f, 0.0f };
		Maths::Vec3 normal = { 0.0f, 0.0f, 0.0f };
		float relativeSpeed = 0.0f;
		float penetrationDistance = 0.0f;
		bool collide = false;
	};

	struct Collision3D
	{
		Entity A;
		Entity B;
		Collision3DPoints points;
	};

	struct Collision2D
	{
		Entity A;
		Entity B;
		Collision2DPoints points;
	};

	class ColliderComponent
	{

	};

	class LineCollider2D;
	class QuadCollider2D;
	class CircleCollider2D;
	class PolygonCollider2D;

	class Collider2DComponent : public ColliderComponent
	{
	public:
		Collider2DComponent(const TransformHandle& transform, const RigidBody2DHandle& body)
			: mTransform(transform), mBody(body)
		{
		}

		inline const TransformHandle& getTransform() const
		{
			return mTransform;
		}

		virtual std::vector<Maths::Vec2> getGeometry() const { return { }; } 

		virtual Collision2DPoints getCollisionPoints(const Collider2DComponent& other) const
		{
			return {};
		};
		virtual Collision2DPoints getCollisionPoints(const LineCollider2D& other) const
		{
			return {};
		};
		virtual Collision2DPoints getCollisionPoints(const QuadCollider2D& other) const
		{
			return {};
		};
		virtual Collision2DPoints getCollisionPoints(const CircleCollider2D& other) const
		{
			return {};
		};
		virtual Collision2DPoints getCollisionPoints(const PolygonCollider2D& other) const
		{
			return {};
		};

	protected:
		TransformHandle mTransform;
		RigidBody2DHandle mBody;
	};

	class PlaneCollider3D;
	class SphereCollider3D;
	class BoxCollider3D;

	class Collider3DComponent : public ColliderComponent
	{
	public:
		Collider3DComponent(const TransformHandle& transform, const RigidBody3DHandle& body)
			: mTransform(transform), mBody(body)
		{
		}

		inline const TransformHandle& getTransform() const
		{
			return mTransform;
		}

		virtual Collision3DPoints getCollisionPoints(const Collider3DComponent& other) const
		{
			return {};
		};
		virtual Collision3DPoints getCollisionPoints(const PlaneCollider3D& other) const
		{
			return {};
		};
		virtual Collision3DPoints getCollisionPoints(const SphereCollider3D& other) const
		{
			return {};
		};
		virtual Collision3DPoints getCollisionPoints(const BoxCollider3D& other) const
		{
			return {};
		};

	protected:
		TransformHandle mTransform;
		RigidBody3DHandle mBody;
	};
} // namespace Orbital
