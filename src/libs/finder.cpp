#include "finder.h"

finder::finder(int* a, int len)
{
    arr = a;
    length = len;
}

finder::maxx()
{
    int maxWeight = -294967295;
    int maxId = 0;
    for (int i = 0; i < length; i++)
    {
        int weight = arr[i];
        if (weight > maxWeight)
        {
            maxWeight = weight;
            maxId = i;
        }
    }
    return maxId;
}

finder::minx()
{
    int minWeight = 294967295;
    int minId = 0;
    for (int i = 0; i < length; i++)
    {
        int weight = arr[i];
        if (weight < minWeight)
        {
            minWeight = weight;
            minId = i;
        }
    }
    return minId;
}

finder::~finder()
{
    //dtor
}
