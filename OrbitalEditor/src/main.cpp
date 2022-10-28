#include "OrbitalECS/Registry.h"
#include "OrbitalECS/Handle.h"
#include "OrbitalECS/Registry.h"
#include "OrbitalEditor/EditorApplication.h"
#include "OrbitalTools/Random.h"

using namespace Orbital;

int main(int argc, char** argv)
{

	auto app = std::make_shared<EditorApplication>();
	return app->run(argc, argv);

	return 0;
}
