#include "MiniOpt.h"

#include <iostream>

#include "sort.h"

using namespace std;

void MiniOpt::exchange(int i, int j)
{
    int tmp = arr1[i];
    arr1[i] = arr2[j];
    arr2[j] = tmp;
    sum1 += arr1[i] - arr2[j];
    sum2 += arr2[j] - arr1[i];
    diff = sum1 - sum2;
    change = true;
    cout << "diff : " << diff << endl;
}

MiniOpt::MiniOpt(int* a1, int* a2, int size1, int size2)
{
    arr1 = a1;
    arr2 = a2;
    sum1 = 0, sum2 = 0;
    for (int i = 0; i < size1; i++)
        sum1 += arr1[i];
    for (int i = 0; i < size2; i++)
        sum2 += arr2[i];
    diff = sum1 - sum2;
    cout << "diff: " << diff << endl;

    do {
        sortInt(a1, size1);
        sortInt(a2, size2);
        change = false;
        int ptr1 = 0, ptr2 = 0;
        while (ptr1 < size1 && ptr2 < size2)
        {
            if (diff < 0)
            {
                if (arr1[ptr1] < arr2[ptr2])
                {
                    if (arr1[ptr1] - arr2[ptr2] >= diff)
                        exchange(ptr1, ptr2);
                    ptr2++;
                }
                else
                    ptr1++;
            } else if (diff > 0)
            {
                if (arr1[ptr1] > arr2[ptr2])
                {
                    if (arr1[ptr1] - arr2[ptr2] <= diff)
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
