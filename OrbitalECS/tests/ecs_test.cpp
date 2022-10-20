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

struct Mesh
{
    Position* pos;

    Mesh(Position* p) : pos(p) { }
};

class ECSTests: public ::testing::Test
{
    protected:
        Orbital::Registry registry;
        Orbital::EntityID entityID;

        void SetUp() override
        {
            registry.registerComponentType<Position>();
            registry.registerComponentType<Mesh>();
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
    Orbital::ComponentHandle<Position> pos3 = entity.get<Position>();
    EXPECT_TRUE(pos3->x == 1.5f);
}

TEST_F(ECSTests, LoopComponentTest)
{
    Orbital::Entity entity = registry.getEntity(entityID);
    Orbital::ComponentHandle<Position> pos = entity.push<Position>(0.5f, 0.7f, 0.1f);
    pos->x += 1.0f;

    for (auto& [ uuid, pos4 ] : registry.components<Position>())
    {
        EXPECT_TRUE(pos4.x == 1.5f);
        break;
    }
}

TEST_F(ECSTests, PtrComponentTest)
{
    Orbital::Entity entity = registry.getEntity(entityID);
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
