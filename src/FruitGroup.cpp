#include "FruitGroup.h"

FruitGroup::FruitGroup()
{
    //ctor
}

void FruitGroup::setSize(int n)
{
    growth = new int[n];
    nFruits = n;
    shrinkStates = new double[n];
    for (int i = 0; i < n; i++)
    {
        growth[i] = 0;
        shrinkStates[i] = 1.0;
    }
}

void FruitGroup::grow(int fruit, int s)
{
    int current = growth[fruit] += s;
    // useless
    // if (current > biggest)
    //    biggest = current;
}

void FruitGroup::shrink(int percent)
{
 //TODO implement
}

int FruitGroup::getBiggest(int* indexes, int n)
{
    int bestFruit = -294967295;
    int bestId = 0;
    for (int i = 0; i < n; i++)
    {
        int prog = growth[indexes[i]];
        if (prog > bestFruit)
        {
            bestFruit = prog;
            bestId = i;
        }
    }
    return bestId;
}

FruitGroup::~FruitGroup()
{
    //dtor
}
