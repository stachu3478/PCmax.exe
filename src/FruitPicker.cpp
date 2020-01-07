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

int FruitPicker::pickWild(int index)
{
    int fruit = fruits[index];
    int hideIndex = --remFruits;
    fruits[index] = fruits[hideIndex];
    fruits[hideIndex] = fruit;
    return fruit;
}

int FruitPicker::pickArr(int index)
{
    if (remFruits <= index)
        throw FruitNotFoundExcecption();
    return pickWild(index);
}

int FruitPicker::pick()
{
    if (remFruits == 0)
        throw NoFruitsException();
    int index = rand() % remFruits;
    return pickWild(index);
}

int FruitPicker::pick(int fruit)
{
    for (int index = 0; index < nFruits; index++)
        if (fruits[index] == fruit)
            return pickWild(index);
    throw FruitNotFoundExcecption();
}

void FruitPicker::dump()
{
    for (int i = 0; i < nFruits; i++)
    {
        cout << fruits[i] << " ";
    }
    cout << endl << "Rem: " << remFruits << endl;
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
    cout << "----" << endl;
    picker->reset();
    for (int i = 14; i >= 0; i--)
    {
        cout << picker->pickArr(rand() % (i + 1)) << endl;
    }
}

FruitPicker::~FruitPicker()
{
    delete fruits;
}
