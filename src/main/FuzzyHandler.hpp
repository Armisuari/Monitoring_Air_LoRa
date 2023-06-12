#pragma once

#include <Fuzzy.h>

class FuzzyHandler
{
private:
    Fuzzy *fuzzy;

public:
    FuzzyHandler(); // constructor added to initialize fuzzy variable
    bool begin(unsigned int &);
    float output(int &);

    void addSet(FuzzyInput *input, FuzzySet *sets[]);
};