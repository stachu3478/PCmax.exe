#include "FruitGuiness.h"

#include "FruitAccountant.h"

FruitGuiness::FruitGuiness(int n)
{
    nAccountants = n;
    accountants = new FruitAccountant[n];
    sums = new int[n];
    fdr = new finder(sums, n);
}

void FruitGuiness::afterSign(int prev, int val, int id)
{
    if (prev > val)
    {
        if (id == maxId)
            maxId = fdr->maxx();
        if (val < sums[minId])
            minId = id;
    } else if (val > prev)
    {
        if (id == minId)
            minId = fdr->minx();
        if (val > sums[maxId])
            maxId = id;
    }
    sums[id] = val;
}

void FruitGuiness::sign(int* arr, int len, int id)
{
    accountants[id] = FruitAccountant(arr, len);
    afterSign(sums[id], accountants[id].getSum(), id);
}

FruitGuiness::~FruitGuiness()
{
    //dtor
}
