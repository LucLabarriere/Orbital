#include "FPSDemoLibrary/Application.h"

int main(int argc, char** argv)
{
	auto app = MakeRef<FPSDemo::Application>();
	app->run(argc, argv);
	app.reset();

	return 0;
}
