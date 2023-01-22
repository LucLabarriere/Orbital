#include "DemoLibrary/Application.h"

auto main(int argc, char** argv) -> int
{
	auto app = MakeRef<Demo::Application>();
	app->initialize(argc, argv);
	app->run();
	app.reset();

	return 0;
}
