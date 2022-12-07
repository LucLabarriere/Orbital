#include "OrbitalEditor/EditorApplication.h"

using namespace Orbital;

int main(int argc, char** argv)
{
	auto app = std::make_shared<EditorApplication>();
	app->run(argc, argv);
	app.reset();
	Logger::Log("Done");
	return 0;
}
