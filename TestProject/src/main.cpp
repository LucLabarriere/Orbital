#include "Example1.h"
#include "Example2.h"
#include "E1Service.h"
#include "E2Service.h"
#include "ServiceDefinitions.h"

#include <memory>

class Application
{
public:
    static void Run()
    {
        auto e1 = std::make_shared<Example1>();
        auto e2 = std::make_shared<Example2>();

        Services<E1Service, E2Service> services = {
            { .E1 = { e1 } },
            { .E2 = { e2 } }
        };

        auto services2 = Services<E1Service, E2Service>::Create(
            services.E1, 
            services.E2
        );

        services2.E1.Print();
        services2.E2.Print();
    }
};

int main(int argc, char** argv)
{
    Application::Run();
    return 0;
}
