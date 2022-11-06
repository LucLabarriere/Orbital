#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/Components/ColliderComponent.h"

namespace Orbital
{
	class OENGINE_API Physics3D
	{
	public:
		static Collision3DPoints GetPlanePlaneCollisionPoints(const PlaneCollider3D& p1, const PlaneCollider3D& p2);
		static Collision3DPoints GetPlaneSphereCollisionPoints(const PlaneCollider3D& p, const SphereCollider3D& s);
		static Collision3DPoints GetPlaneBoxCollisionPoints(const PlaneCollider3D& p, const BoxCollider3D& b);

		static Collision3DPoints GetSphereSphereCollisionPoints(const SphereCollider3D& s1, const SphereCollider3D& s2);
		static Collision3DPoints GetSphereBoxCollisionPoints(const SphereCollider3D& s, const BoxCollider3D& b);

		static Collision3DPoints GetBoxBoxCollisionPoints(const BoxCollider3D& b1, const BoxCollider3D& b2);
	};

	class OENGINE_API Physics2D
	{
	public:
		static Collision2DPoints GetCircleCircleCollisionPoints(const CircleCollider2D& c1, const CircleCollider2D& c2);
		static Collision2DPoints GetCircleLineCollisionPoints(const CircleCollider2D& c, const LineCollider2D& l);
		static Collision2DPoints GetCircleQuadCollisionPoints(const CircleCollider2D& c, const QuadCollider2D& q);
		static Collision2DPoints GetCirclePolygonCollisionPoints(const CircleCollider2D& c, const PolygonCollider2D& p);

		static Collision2DPoints GetLineLineCollisionPoints(const LineCollider2D& l1, const LineCollider2D& l2);
		static Collision2DPoints GetLineQuadCollisionPoints(const LineCollider2D& l, const QuadCollider2D& q);
		static Collision2DPoints GetLinePolygonCollisionPoints(const LineCollider2D& l, const PolygonCollider2D& p);

		static Collision2DPoints GetQuadQuadCollisionPoints(const QuadCollider2D& q1, const QuadCollider2D& q2);
		static Collision2DPoints GetQuadPolygonCollisionPoints(const QuadCollider2D& q, const PolygonCollider2D& p);

		static Collision2DPoints GetPolygonPolygonCollisionPoints(const PolygonCollider2D& p1, const PolygonCollider2D& p2);
	};
} // namespace Orbital
