#include "NumberGenerator.h"


NumberGenerator::NumberGenerator() {
    Generate();
}

void NumberGenerator::Generate() {
    int indexSize = 9;
    vector<int> indexes;

    for (int i = 0; i < indexSize; i++) {
        indexes.push_back(i);
        numbers[i] = 0;
    }

    for(int currentNumber = 1; currentNumber < 7; currentNumber++, indexSize--){
        int index = rand() % indexSize;
        int position = indexes[index];
        indexes.erase(indexes.begin() + index);
        numbers[position] = currentNumber;
    }
}