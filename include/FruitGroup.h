#ifndef FRUITGROUP_H
#define FRUITGROUP_H

#include "finder.h"

class FruitGroup
{
    public:
        FruitGroup();
        virtual ~FruitGroup();

        void grow(int fruit, int s);
        void shrink(int percent);
        // useless
        // int getBiggest() { return biggest; };
        int getBiggest(int* indexes, int n);
        void setSize(int n);

    protected:

    private:
        int nFruits;
        int biggest;
        int* growth;

        double* shrinkStates;
};

#endif // FRUITGROUP_H
