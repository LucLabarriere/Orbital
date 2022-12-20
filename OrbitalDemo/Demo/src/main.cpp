#include "DemoLibrary/Application.h"

int main(int argc, char** argv)
{
	auto app = MakeRef<Demo::Application>();
	app->run(argc, argv);
	app.reset();

	return 0;
}
