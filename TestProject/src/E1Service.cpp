#include "E1Service.h"
#include "Example1.h"

E1Service::E1Interface::E1Interface(std::shared_ptr<Example1>& instance)
    : Service<Example1>(instance)
{

}

void E1Service::E1Interface::Print()
{
    mInstance->print();
}
