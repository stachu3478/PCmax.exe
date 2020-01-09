#include <iostream>
#include <sort.h>
#include <ctime>
#include <stdlib.h>

using namespace std;

void sortItems(unsigned int* tItems, int length)
{
    int i = 0, j = length - 1;
    do
    {
        if (tItems[j] > tItems[i])
        {
            unsigned int tItem = tItems[j];
            tItems[j] = tItems[i];
            tItems[i] = tItem;
        }
    } while (++i < j);
    if (i > 1)
    {
        sortItems(tItems, i);
    }
    if (j < length - 2)
    {
        sortItems(tItems + j, length - j - 1);
    }
}

void someTest()
{
    unsigned int items[1000];
    srand(time(NULL));
    for (int i = 0; i < 1000; i++) {
        items[i] = rand() % 10000;
    }
    sortItems(items, 1000);
    for (int i = 0; i < 1000; i++)
    {
        cout << items[i] << endl;
    }
}
