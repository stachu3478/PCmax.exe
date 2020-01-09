#include "MiniOpt.h"

#include "sort.h"

MiniOpt::MiniOpt(int* arr1, int* arr2, int size1, int size2 )
{
    // TODO add int sorter
    sortItems(arr1, size1);
    sortItems(arr2, size2);
    int sum1 = 0, sum2 = 0;
    for (int i = 0; i < size1; i++)
        sum1 += arr1[i];
    for (int i = 0; i < size2; i++)
        sum2 += arr2[i];
    int diff = sum1 - sum2;

    int ptr1 = 0, ptr2 = 0;
    while (ptr1 < size1 && ptr2 < size2)
    {
        if (diff > 0)
        {
            //TODO
            //if (arr1[ptr1] )
        } else if (diff < 0)
        {

        } else return;
    }
}

MiniOpt::~MiniOpt()
{
    //dtor
}
