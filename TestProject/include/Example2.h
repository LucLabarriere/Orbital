#pragma once

#include <iostream>

class Example2
{
public:
    void print() { std::cout << mValue << std::endl; }

private:
    int mValue = 10;
};
