#include "OrbitalDemo/DemoApplication.h"

using namespace Orbital;

int main(int argc, char** argv)
{
	auto app = MakeRef<DemoApplication>();
	app->run(argc, argv);
	app.reset();

	LOGFUNC();
	Logger::Log("return 0;");
	return 0;
}
