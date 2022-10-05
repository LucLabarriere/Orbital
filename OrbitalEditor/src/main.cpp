#include "OrbitalLogger/Logger.h"
#include "OrbitalECS/Core.h"
#include <initializer_list>
#include <iostream>
#include <chrono>

using namespace std::chrono;

struct Position
{
    float x;
    float y;
    float z;

    Position(float X, float Y, float Z) : x(X), y(Y), z(Z) { Orbital::Logger::Error("Creating Position"); }
    Position(const Position& other): x(other.x), y(other.y), z(other.z) { Orbital::Logger::Error("Copying Position"); }
    ~Position() { Orbital::Logger::Log("Destroying Position: ", x, " ", y, " ", z); }
};
using namespace Orbital;

int main()
{
    Registry reg;
    //reg.registerType<int>();
    reg.registerType<Position>();

    //Handle<int> integer = reg.push<int>(5)

    size_t count = 10000;
    
    Handle<Position> pos = reg.push<Position>(5.0f, 0.1f, 0.7f);
    //VAR(pos->x);

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
