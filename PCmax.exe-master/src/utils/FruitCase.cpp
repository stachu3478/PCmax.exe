#include "FruitCase.h"
#include <iostream>

using namespace std;

FruitCase::FruitCase(int initN)
{
    tabs[0] = new int[initN];
    maxLength = initLength = initN;
    length = 0;
    lastTab = 0;
}

void FruitCase::add(int fruit)
{
    if (length == maxLength)
    {
        tabs[++lastTab] = new int[maxLength += length++ << 1];
        tabs[lastTab][0] = fruit;
    }
    tabs[lastTab][length++] = fruit;
}

int* FruitCase::open()
{
    inventory = new int[length];
    int tabSize = initLength;
    int tabId = 0;
    int local = 0;
    int n = 0;
    while (n < length)
    {
        if (local >= tabSize)
        {
            local = 0;
            tabId++;
            tabSize *= 2;
        }
        inventory[n++] = tabs[tabId][local++];
    }
    return inventory;
}

void FruitCase::printContents()
{
    int tabSize = initLength;
    int tabId = 0;
    int local = 1;
    int n = 1;
    if (length >= 1)
        cout << "[ " << tabs[0][0];
    else cout << "[";
    while (n++ < length)
    {
        if (local >= tabSize)
        {
            local = 0;
            tabId++;
            tabSize *= 2;
        }
        cout << ", " << tabs[tabId][local++];
    }
    cout << "]" << endl;
}

FruitCase::~FruitCase()
{
    //dtor
}
