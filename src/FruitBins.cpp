#include "FruitBins.h"

#include <iostream>

FruitBins::FruitBins(int n)
{
    nBins = n;
    bins = new int[n];
    binPtr = 0;
}

int FruitBins::getLeastWild(bool index)
{
    int minWeight = 294967295;
    int minBin = 0;
    for (int i = 0; i < nBins; i++)
    {
        int weight = bins[i];
        if (weight < minWeight)
        {
            minWeight = weight;
            minBin = i;
        }
    }
    if (index)
        return minBin;
    return minWeight;
}

int FruitBins::getMax()
{
    int maxWeight = 0;
    int maxBin = 0;
    for (int i = 0; i < nBins; i++)
    {
        int weight = bins[i];
        if (weight > maxWeight)
        {
            maxWeight = weight;
            maxBin = i;
        }
    }
    return maxWeight;
}

int FruitBins::addToLeast(int fruit)
{
    if (binPtr < nBins)
    {
        bins[binPtr] = fruit;
        return binPtr++;
    }
    int least;
    bins[least = getLeast()] += fruit;
    return least;
}

int FruitBins::getTotal()
{
    int sum = 0;
    for (int i = 0; i < nBins; i++)
    {
        sum += bins[i];
    }
    return sum;
}

FruitBins::~FruitBins()
{
    //dtor
}
