#ifndef FRUITACCOUNTANT_H
#define FRUITACCOUNTANT_H

#include "finder.h"
#include "sort.h"

class FruitAccountant
{
    public:
        FruitAccountant(){};
        FruitAccountant(int n);
        FruitAccountant(int* a, int n);
        virtual ~FruitAccountant();

        void repl(int id, int val);
        int getSum() { return total; };
        int getLength() { return length; };
        int getMax() { return maxId; };
        int getMin() { return minId; };
        int maxVal() { return fruits[maxId]; };
        int minVal() { return fruits[minId]; };
        int get(int id) { return fruits[id]; };
        void sortFruits() { sortInt(fruits, length); };
        int operator[](int id) { return fruits[id]; };

    protected:

    private:
        int* fruits;
        int length;
        int total;
        int maxId;
        int minId;
        finder* fdr;

        void init(int n);
};

#endif // FRUITACCOUNTANT_H
