#include "Colony.h"

#include <stdlib.h>
#include <iostream>

using namespace std;

Colony::Colony(int n, int a, int b)
{
    nDims = n;
    minx = a;
    maxx = b;
    range = 1;
    range2 = 2;
    its = 0;
    prevPow = 1;
    randoms = new int[nDims];
}

int Colony::sPow()
{
    if (range >= maxx - minx)
        return prevPow;
    int a = ++range;
    range2 = range << 1;
    for (int i = 1; i < nDims; i++)
        a *= range;
    return prevPow = a;
}

int* Colony::pull()
{
    for (int i = 0; i < nDims; i++)
    {
        int r = vec[i] + (rand() % range2) - range;
        if (r > maxx)
            r = maxx;
        if (r < minx)
            r = minx;
        randoms[i] = r;
    }
    if (prevPow <= ++its)
        sPow();
    return randoms;
}

int Colony::setRange(int val)
{
    range = val - 1;
    sPow();
    return range;
}

void Colony::test()
{
    Colony* col = new Colony(10, -1000, 1000);
    int* vec = new int[10]{ 0, 10, -10, 100, -100, 1000, -1000, 10000, -10000, 100000 };
    col->setVec(vec);
    int* rands = col->pull();
    for (int i = 0; i < 10; i++)
    {
        cout << rands[i] << endl;
    }
    cout << "---" << endl;
    for (int i = 0; i < 100; i++)
        col->pull();
    for (int i = 0; i < 10; i++)
    {
        cout << rands[i] << endl;
    }
}

Colony::~Colony()
{
    //dtor
}
