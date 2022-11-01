#include <gtest/gtest.h>

#include "OrbitalECS/ECS.h"
#include "OrbitalLogger/Logger.h"

struct Position
{
	float x;
	float y;
	float z;

	Position(float X, float Y, float Z) : x(X), y(Y), z(Z)
	{
	}
};

struct Mesh
{
	Position* pos;

	Mesh(Position* p) : pos(p)
	{
	}
};

class Parent
{
public:
	virtual ~Parent(){};

	virtual void increment() = 0;
	int getField() const
	{
		return mField;
	}

protected:
	int mField = 0;
};

class Derived1 : public Parent
{
public:
	virtual ~Derived1() override
	{
	}
	virtual void increment() override
	{
		mField += 1;
	}
};
class Derived2 : public Parent
{
public:
	virtual ~Derived2() override
	{
	}
	virtual void increment() override
	{
		mField += 2;
	}
};

class ECSTests : public ::testing::Test
{
protected:
	Orbital::Registry registry;
	Orbital::EntityID entityID;

	void SetUp() override
	{
		registry.registerComponentType<Position>();
		registry.registerComponentType<Mesh>();
		registry.registerDerivableComponentType<Parent>();
		Orbital::BaseEntity entity = registry.createEntity();
		entity.push<Parent, Derived1>();
		entity.push<Parent, Derived2>();
		entityID = entity.getID();
	}

	void TearDown() override
	{
		registry.cleanUp();
	}
};

TEST_F(ECSTests, CreateEntityTest)
{
	Orbital::BaseEntity entity = registry.createEntity();
	EXPECT_TRUE(entity.isValid());
}

TEST_F(ECSTests, PushComponentTest)
{
	Orbital::BaseEntity entity = registry.getEntity(entityID);
	Orbital::ComponentHandle<Position> pos = entity.push<Position>(0.5f, 0.7f, 0.1f);
	EXPECT_TRUE(pos.isValid());
}

TEST_F(ECSTests, PushDerivableComponentTest)
{
	Orbital::BaseEntity entity = registry.getEntity(entityID);
	Orbital::ComponentHandle<Derived1> d1 = entity.push<Parent, Derived1>();
	// EXPECT_TRUE(d1.isValid());
	d1->increment();
	EXPECT_EQ(d1->getField(), 1);

	Orbital::ComponentHandle<Derived2> d2 = entity.push<Parent, Derived2>();
	// EXPECT_TRUE(d2.isValid()); TODO : Remake the whole system to allow isValid on derivable components
	d2->increment();
	EXPECT_EQ(d2->getField(), 2);
}

TEST_F(ECSTests, GetComponentTest)
{
	Orbital::BaseEntity entity = registry.getEntity(entityID);
	Orbital::ComponentHandle<Position> pos = entity.push<Position>(0.5f, 0.7f, 0.1f);
	Orbital::ComponentHandle<Position> pos2 = entity.get<Position>();

	EXPECT_TRUE(pos2.isValid());
	pos2->x += 1.0f;
	EXPECT_TRUE(pos2->x == 1.5f);
	Orbital::ComponentHandle<Position> pos3 = entity.get<Position>();
	EXPECT_TRUE(pos3->x == 1.5f);
}

TEST_F(ECSTests, GetDerivableComponentTest)
{
	Orbital::BaseEntity entity = registry.getEntity(entityID);
	Orbital::ComponentHandle<Derived1> d1_0 = entity.push<Parent, Derived1>();
	Orbital::ComponentHandle<Derived1> d1_1 = entity.get<Parent, Derived1>();
	d1_0->increment();
	EXPECT_EQ(d1_1->getField(), 1);
}

TEST_F(ECSTests, LoopComponentTest)
{
	Orbital::BaseEntity entity = registry.getEntity(entityID);
	Orbital::ComponentHandle<Position> pos = entity.push<Position>(0.5f, 0.7f, 0.1f);
	pos->x += 1.0f;

	for (auto& [uuid, pos4] : registry.components<Position>())
	{
		EXPECT_TRUE(pos4.x == 1.5f);
		break;
	}
}

TEST_F(ECSTests, PtrComponentTest)
{
	Orbital::BaseEntity entity = registry.getEntity(entityID);
	Orbital::ComponentHandle<Position> pos = entity.push<Position>(0.5f, 0.7f, 0.1f);
	pos->x += 1.0f;
	Orbital::ComponentHandle<Mesh> mesh = entity.push<Mesh>(&(*pos));
	EXPECT_TRUE(mesh->pos->x == 1.5f);
	Orbital::ComponentHandle<Mesh> mesh2 = entity.get<Mesh>();
	EXPECT_TRUE(mesh2->pos->x == 1.5f);
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
