#include "OrbitalDemo/DemoApplication.h"

int main(int argc, char** argv)
{
	auto app = MakeRef<DemoApplication>();
	app->run(argc, argv);
	app.reset();

	LOGFUNC();
	Orbital::Logger::Log("return 0;");
	return 0;
}
