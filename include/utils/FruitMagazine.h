#ifndef FRUITMAGAZINE_H
#define FRUITMAGAZINE_H

#include "FruitCase.h"

class FruitMagazine
{
    public:
        FruitMagazine(int cases, int initialCase);
        virtual ~FruitMagazine();

        int getSize(int caseId) { return cases[caseId]->getSize(); };
        void add(int caseId, int fruit) { cases[caseId]->add(fruit); };
        void printContents();
        int** release();

    protected:

    private:
        FruitCase** cases;
        int nCases;

        int** inventory;
};

#endif // FRUITMAGAZINE_H
