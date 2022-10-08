#include "OrbitalLogger/Logger.h"
#include "OrbitalECS/ECS.h"
#include "OrbitalTools/Time.h"

#include <vector>

using namespace std::chrono;

struct Position
{
    float x;
    float y;
    float z;

    Position(float X, float Y, float Z) : x(X), y(Y), z(Z) {  }
    Position(const Position& other): x(other.x), y(other.y), z(other.z) {  }
    ~Position() {  }
};
using namespace Orbital;

int main()
{
    Registry reg;
    //reg.registerType<int>();
    reg.registerType<Position>();

    //Handle<int> integer = reg.push<int>(5)

    size_t entityCount = 1000000;
    std::vector<Entity> entities(entityCount);

    Time t;

    for (size_t i = 0; i < entityCount; i++)
    {
        entities[i] = reg.createEntity();
    }

    Logger::Debug("Creating entities Time: ", (Time() - t).seconds());
    t = Time();

    for (size_t i = 0; i < entityCount; i++)
    {
        entities[i].push<Position>(0.5f, 0.1f, 0.6f);
    }

    Logger::Debug("Creating components Time: ", (Time() - t).seconds());
    
    t = Time();

    for (size_t i = 0; i < entityCount; i++)
    {
        entities[i].get<Position>();
    }

    Logger::Debug("Getting components Time: ", (Time() - t).seconds());

    return 0;
}
