#include "OrbitalEditor/EditorApplication.h"

using namespace Orbital;

int main(int argc, char** argv)
{
	auto app = std::make_shared<EditorApplication>();
	return app->run(argc, argv);
}
