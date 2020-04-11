#pragma once
#include <random>
#include <vector>

using namespace std;

class NumberGenerator {
public:
    int numbers[9];
    NumberGenerator();
    void Generate();
};
