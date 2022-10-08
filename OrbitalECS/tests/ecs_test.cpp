#include <gtest/gtest.h>

#include "OrbitalECS/ECS.h"
#include "OrbitalLogger/Logger.h"

struct Position
{
    float x;
    float y;
    float z;

    Position(float X, float Y, float Z) : x(X), y(Y), z(Z) {  }
};

class ECSTests: public ::testing::Test
{
    protected:
        Orbital::Registry registry;
        Orbital::EntityID entityID;

        void SetUp() override
        {
            registry.registerType<Position>();
            Orbital::Entity entity = registry.createEntity();
            entityID = entity.getID();
        }
};

TEST_F(ECSTests, CreateEntityTest)
{
    Orbital::Entity entity = registry.createEntity();
    EXPECT_TRUE(entity.isValid());
}

TEST_F(ECSTests, PushComponentTest)
{
    Orbital::Entity entity = registry.getEntity(entityID);
    Orbital::ComponentHandle<Position> pos = entity.push<Position>(0.5f, 0.7f, 0.1f);
    EXPECT_TRUE(pos.isValid());
}

TEST_F(ECSTests, GetComponentTest)
{
    Orbital::Entity entity = registry.getEntity(entityID);
    Orbital::ComponentHandle<Position> pos = entity.push<Position>(0.5f, 0.7f, 0.1f);
    Orbital::ComponentHandle<Position> pos2 = entity.get<Position>();
    EXPECT_TRUE(pos2.isValid());
    pos2->x += 1.0f;
    EXPECT_TRUE(pos2->x == 1.5f);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

