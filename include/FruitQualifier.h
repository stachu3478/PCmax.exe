#ifndef FRUITQUALIFIER_H
#define FRUITQUALIFIER_H

#include "FruitGroup.h"

class FruitQualifier
{
    public:
        FruitQualifier(int groups, int perGroup);
        virtual ~FruitQualifier();

        // useless
        // int getBiggest(int group) { return groups[group]->getBiggest(); };
        int getBiggest(int group, int* indexes, int n) { return groups[group].getBiggest(indexes, n); };
        void grow(int group, int fruit, int s) { groups[group].grow(fruit, s); };
        void shrink(int percent);

    protected:

    private:
        FruitGroup* groups;
};

#endif // FRUITQUALIFIER_H
