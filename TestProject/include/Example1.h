#pragma once

#include <iostream>

class Example1
{
public:
    void print() { std::cout << mValue << std::endl; }

private:
    int mValue = 5;
};
