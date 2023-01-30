#include "FPSDemoLibrary/Application.h"
#include "OrbitalTools/Misc.h"

auto main(int argc, char** argv) -> int
{
	return Orbital::Main<FPSDemo::Application>(argc, argv);
}
