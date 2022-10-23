#pragma once
#include "ServiceDefinitions.h"

class Example1;

struct E1Service
{
    class E1Interface : public Service<Example1>
    {
    public:
        E1Interface(std::shared_ptr<Example1>& instance);
        void Print();
    };

    E1Interface E1;
};
