#include "E2Service.h"
#include "Example2.h"

E2Service::E2Interface::E2Interface(std::shared_ptr<Example2>& instance)
    : Service<Example2>(instance)
{

}

void E2Service::E2Interface::Print()
{
    mInstance->print();
}
