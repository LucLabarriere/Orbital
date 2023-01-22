#include "FPSDemoLibrary/Application.h"

auto main(int argc, char** argv) -> int
{
	auto app = MakeRef<FPSDemo::Application>();

	{ // INITIALIZE
		auto error = app->initialize(argc, argv);
		if (error)
			return error->report();
	}

	{ // RUN
		auto error = app->run();
		if (error)
			return error->report();
	}

	{ // TERMINATE
		auto error = app->terminate();
		if (error)
			return error->report();
	}

	app.reset();
	return 0;
}
