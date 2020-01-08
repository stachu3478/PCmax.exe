#include "FruitQualifier.h"

#include "FruitGroup.h"

FruitQualifier::FruitQualifier(int nGroups, int perGroup)
{
    groups = new FruitGroup[nGroups];
    for (int i = 0; i < nGroups; i++)
        groups[i].setSize(perGroup);
}

FruitQualifier::~FruitQualifier()
{
    //dtor
}
