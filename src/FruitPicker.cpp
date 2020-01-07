#include <iostream>
#include <stdlib.h>

#include "FruitPicker.h"

using namespace std;

FruitPicker::FruitPicker(int n)
{
    fruits = new int[n];
    for (int i = 0; i < n; i++)
    {
        fruits[i] = i;
    }
    nFruits = n;
    remFruits = n;
}

FruitPicker::pick()
{
    if (remFruits == 0)
        throw NoFruitsException();
    int index = rand() % remFruits;
    int fruit = fruits[index];
    int hideIndex = --remFruits;
    fruits[index] = fruits[hideIndex];
    fruits[hideIndex] = fruit;
    return fruit;
}

FruitPicker::pick(int fruit)
{
    for (int index = 0; index < nFruits; index++)
    {
        if (fruits[index] == fruit)
        {
            int hideIndex = remFruits - 1;
            fruits[index] = fruits[hideIndex];
            fruits[hideIndex] = fruit;
            return fruit;
        }
    }
    throw FruitNotFoundExcecption();
}

void FruitPicker::test()
{
    FruitPicker* picker = new FruitPicker(15);
    for (int i = 0; i < 15; i++)
    {
        cout << picker->pick() << endl;
    }
    cout << "----" << endl;
    picker->reset();
    cout << picker->pick(0) << endl;
    for (int i = 0; i < 14; i++)
    {
        cout << picker->pick() << endl;
    }
}

FruitPicker::~FruitPicker()
{
    delete fruits;
}
