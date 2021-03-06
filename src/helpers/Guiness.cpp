#include "Guiness.h"

#include <iostream>

using namespace std;

Guiness::Guiness(int n, int worst)
{
    nRecords = n;
    names = new string[n];
    records = new int[n];
    for (int i = 0; i < n; i++)
        records[i] = worst;
}

bool Guiness::process(int i, int rec)
{
    if (records[i] <= rec)
        return false;
    records[i] = rec;
    cout << "New record of " << names[i] << " : " << rec << endl;
    return true;
}

void Guiness::report()
{
    for (int i = 0; i < nRecords; i++)
        cout << "Best " << names[i] << " record: " << records[i] << endl;
}

void Guiness::test()
{
    Guiness* g = new Guiness(2, 200);
    g->setName(0, "zero");
    g->setName(1, "one");
    g->process(0, 100);
    g->process(1, 150);
    g->report();
}

Guiness::~Guiness()
{
    //dtor
}
