#include "MiniOpt.h"

#include <iostream>

#include "sort.h"
#include "FruitAccountant.h"

using namespace std;

void MiniOpt::exchange(int i, int j)
{
    int tmp = juice1->get(i);
    juice1->repl(i, juice2->get(j));
    juice2->repl(j, tmp);
    diff = juice1->getSum() - juice2->getSum();
    change = true;
    cout << "diff : " << diff << endl;
}

void MiniOpt::init()
{
    diff = juice1->getSum() - juice2->getSum();
    cout << "diff: " << diff << endl;

    do {
        juice1->sortFruits();
        juice2->sortFruits();
        change = false;
        int ptr1 = 0, ptr2 = 0;
        int size1 = juice1->getLength(), size2 = juice2->getLength();
        while (ptr1 < size1 && ptr2 < size2)
        {
            int fruit1 = juice1->get(ptr1);
            int fruit2 = juice2->get(ptr2);
            if (diff < 0)
            {
                if (fruit1 < fruit2)
                {
                    if (fruit1 - fruit2 >= diff)
                        exchange(ptr1, ptr2);
                    ptr2++;
                }
                else
                    ptr1++;
            } else if (diff > 0)
            {
                if (fruit1 > fruit2)
                {
                    if (fruit1 - fruit2 <= diff)
                        exchange(ptr1, ptr2);
                    ptr1++;
                }
                else
                    ptr2++;
            } else
            {
                cout << "Optimal" << endl;
                return;
            }
        }
    } while (change);
    cout << "Not optimal" << endl;
}

MiniOpt::MiniOpt(FruitAccountant* a, FruitAccountant* b)
{
    juice1 = a;
    juice2 = b;
    init();
}

MiniOpt::MiniOpt(int* a1, int* a2, int size1, int size2)
{
    juice1 = new FruitAccountant(a1, size1);
    juice2 = new FruitAccountant(a2, size2);
    init();
}

void MiniOpt::test()
{
    int* arr1 = new int[10]{ 55, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int* arr2 = new int[5]{ 11, 22, 33, 44, 1 };
    MiniOpt* opt = new MiniOpt(arr1, arr2, 10, 5);
    cout << "Solution: " << opt->getSolution() << endl;
    for (int i = 0; i < 10; i++)
        cout << arr1[i] << " ";
    cout << endl;
    for (int i = 0; i < 5; i++)
        cout << arr2[i] << " ";
    cout << endl;
}

MiniOpt::~MiniOpt()
{
    //dtor
}
