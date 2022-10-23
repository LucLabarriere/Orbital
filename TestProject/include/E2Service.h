#pragma once
#include "ServiceDefinitions.h"

class Example2;

struct E2Service
{
    class E2Interface : public Service<Example2>
    {
    public:
        E2Interface(std::shared_ptr<Example2>& instance);
        void Print();
    };

   E2Interface E2;
};
