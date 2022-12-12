#include <gtest/gtest.h>

#include "OrbitalPhysics/Colliders.h"
#include "OrbitalPhysics/Engine.h"

using namespace Orbital;

class PhysicsTests : public ::testing::Test
{
protected:
	std::shared_ptr<Physics::PointCollider> mPoint = nullptr;
	std::shared_ptr<Physics::SphereCollider> mSphere1 = nullptr;
	std::shared_ptr<Physics::SphereCollider> mSphere2 = nullptr;

	Physics::Engine mEngine;

	void SetUp() override
	{
		//mPoint = std::shared_ptr<Physics::PointCollider>(new Physics::PointCollider({ 1.0f, 0.0f, 0.0f }));
		//mSphere1 = std::shared_ptr<Physics::SphereCollider>(new Physics::SphereCollider({ 3.0f, 0.0f, 0.0f }, 3.0f));
		//mSphere2 = std::shared_ptr<Physics::SphereCollider>(new Physics::SphereCollider({ -3.0f, 0.0f, 0.0f }, 2.0f));

		//mEngine.initialize();
		//mEngine.push(mPoint);
		//mEngine.push(mSphere1);
		//mEngine.push(mSphere2);
	}

	void TearDown() override
	{
	}
};

TEST_F(PhysicsTests, PointSphereCollideTest)
{
	//ASSERT_TRUE(mSphere1->checkCollision(*mPoint).collide);
	//ASSERT_FALSE(mSphere2->checkCollision(*mPoint).collide);
}

TEST_F(PhysicsTests, SphereSphereCollideTest)
{
	//ASSERT_TRUE(mSphere1->checkCollision(*mSphere1).collide);
	//ASSERT_FALSE(mSphere2->checkCollision(*mSphere1).collide);
}

int main(int argc, char** argv)
{
	//Physics::Engine engine;
	//engine.initialize();

	//engine.push(sphere);
	//engine.push(point);

	//engine.onUpdate(0.0166);
	//::testing::InitGoogleTest(&argc, argv);
	//return RUN_ALL_TESTS();
	return 0;
}
