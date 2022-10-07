#include "OrbitalLogger/Logger.h"
#include "OrbitalECS/Core.h"
#include "OrbitalTools/Time.h"
#include <initializer_list>
#include <iostream>
#include <chrono>

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

    size_t count = 1000000;

    Time t;

    for (size_t i = 0; i < count; i++)
    {
        Handle<Position> pos = reg.push<Position>(5.0f, 0.1f, 0.7f);
        Handle<Position> pos2 = reg.get<Position>(pos.getUUID());
    }
    
    Logger::Debug("Time: ", (Time() - t).seconds());

    /*
     * TODO:
     * Implement Vectors and Matrices
     * Implement Transform
     * Implement Registry
     * Implement Pool<T>
     * Implement push<T>
     * */

    /*
     * Registry reg;
     * reg.registerPool<Position>();
     * Entity entity = reg.createEntity();
     * Handle<Position> pos = reg.push<Position>(entity, { 0.0f, 0.0f, 0.7f });
     * UUID uuid = pos.getUUID();
     * Handle<Position> pos2 = reg.get<Position>(uuid); // from UUIV
     * Handle<Position> pos3 = reg.get<Position>(pos2); // from Handle
     * */
    
    return 0;
}
