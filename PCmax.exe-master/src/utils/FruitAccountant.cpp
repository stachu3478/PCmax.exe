#include "FruitAccountant.h"

void FruitAccountant::init(int n)
{
    length = n;
    int minVal = 999999999;
    int maxVal = -999999999;
    total = 0;
    for (int i = 0; i < length; i++)
    {
        if (fruits[i] < minVal)
        {
            minVal = fruits[i];
            minId = i;
        };
        if (fruits[i] > maxVal)
        {
            maxVal = fruits[i];
            maxId = i;
        };
        total += fruits[i];
    }
}

FruitAccountant::FruitAccountant(int slots)
{
    fruits = new int[slots];
    length = slots;
    fdr = new finder(fruits, slots);
}

FruitAccountant::FruitAccountant(int* a, int slots)
{
    fruits = a;
    length = slots;
}

void FruitAccountant::repl(int id, int val)
{
    int prev = fruits[id];
    fruits[id] = val;
    total += val - prev;
    if (prev > val)
    {
        if (id == maxId)
            maxId = fdr->maxx();
        if (val < fruits[minId])
            minId = id;
    } else if (val > prev)
    {
        if (id == minId)
            minId = fdr->minx();
        if (val > fruits[maxId])
            maxId = id;
    }
}

FruitAccountant::~FruitAccountant()
{
    //dtor
}
