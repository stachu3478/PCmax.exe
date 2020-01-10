#ifndef MINIOPT_H
#define MINIOPT_H

#include "FruitAccountant.h"

class MiniOpt
{
    public:
        MiniOpt(int* arr1, int* arr2, int size1, int size2);
        MiniOpt(FruitAccountant* arr1, FruitAccountant* arr2);
        virtual ~MiniOpt();

        int getSolution() { return juice1->getSum() > juice2->getSum() ? juice1->getSum() : juice2->getSum(); };
        static void test();

    protected:

    private:
        int diff;
        bool change;
        FruitAccountant* juice1;
        FruitAccountant* juice2;

        void exchange(int i, int j);
        void init();
};

#endif // MINIOPT_H
