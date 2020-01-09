#include "FruitMagazine.h"

#include "FruitCase.h"

FruitMagazine::FruitMagazine(int n, int initialCase)
{
    nCases = n;
    cases = new FruitCase*[n];
    for (int i = 0; i < n; i++)
        cases[i] = new FruitCase(initialCase);
}

int** FruitMagazine::release()
{
    inventory = new int*[nCases];
    for (int i = 0; i < nCases; i++)
        inventory[i] = cases[i]->open();
    return inventory;
}

void FruitMagazine::printContents()
{
    for (int i = 0; i < nCases; i++)
        cases[i]->printContents();
}

FruitMagazine::~FruitMagazine()
{
    //dtor
}
