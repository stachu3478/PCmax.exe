#ifndef FRUITGUINESS_H
#define FRUITGUINESS_H

#include "FruitAccountant.h"
#include "finder.h"

class FruitGuiness
{
    public:
        FruitGuiness(int n);
        virtual ~FruitGuiness();

        void reg(int acc, int idx, int val);
        void sign(int* arr, int len, int id);
        int getMax() { return maxId; };
        int getMin() { return minId; };
        int maxVal() { return sums[maxId]; };
        int minVal() { return sums[minId]; };
        FruitAccountant operator[](int id) { return accountants[id]; };

    protected:

    private:
        int nAccountants;
        FruitAccountant* accountants;

        int* sums;
        int maxId;
        int minId;
        finder* fdr;

        void afterSign(int prev, int next, int id);
};

#endif // FRUITGUINESS_H
