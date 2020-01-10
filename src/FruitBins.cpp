#include "FruitBins.h"

#include <iostream>
#include "finder.h"

FruitBins::FruitBins(int n)
{
    nBins = n;
    bins = new int[n];
    binPtr = 0;
    fdr = new finder(bins, n);
}

int FruitBins::getLeastWild(bool index)
{
    int idx = fdr->minx();
    if (index)
        return idx;
    return bins[idx];
}

int FruitBins::getMax()
{
    int index = fdr->maxx();
    return bins[index];
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
