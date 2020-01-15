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

Guiness::~Guiness()
{
    //dtor
}
