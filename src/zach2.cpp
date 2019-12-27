#include <fstream>
#include <iostream>

#include "sort.h"
#include "zach2.h"

using namespace std;

/*void bind2(int p1, int p2, unsigned int m, unsigned int* tasks, unsigned int* pBind, unsigned int s1, unsigned int s2)
{
    int sum1 = 0, sum2 = 0;
    for (unsigned int j = 0; j < nTasks; j++)
    {
        if (pBind[j] != m) continue;
        int add = tasks[j];
        if (sum1 + add * p1 > sum2)
        {
            sum2 += add * p2;
            pBind[j] = s2;
        } else
        {
            sum1 += add * p1;
            pBind[j] = s1;
        }
    }
    sumP[i] /= i;
    cout << sum << " " << sumP[i] << endl;
}*/

zach2::zach2(char* file, bool v3)
{
    ifstream source(file);
    cout << "File opened\n";
    int nProcessors = 0, nTasks = 0;
    source >> nProcessors;
    source >> nTasks;
    cout << nProcessors << endl;
    cout << "Processors defined\n";

    unsigned int* procIds = new unsigned int[nTasks];

    unsigned int tasks[nTasks];
    unsigned int sumP[nProcessors];
    unsigned int pBind[nTasks];
    for (unsigned int i = 0; i < nTasks; i++)
    {
        source >> tasks[i];
        pBind[i] = 0;
    }
    sortItems(tasks, nTasks);

    for (unsigned int i = nProcessors - 1; i > 0; i--)
    {
        int sum = 0;
        sumP[i] = 0;
        for (unsigned int j = 0; j < nTasks; j++)
        {
            if (pBind[j] != 0) continue;
            int add = tasks[j];
            if (sum + add > sumP[i])
            {
                sumP[i] += add * i;
                pBind[j] = i;
            } else sum += add;
        }
        sumP[i] /= i;
        cout << sum << " " << sumP[i] << endl;
    };
    sumP[0] = 0;
    for (unsigned int i = 0; i < nTasks; i++)
    {
        if (pBind[i] == 0) sumP[0] += tasks[i];
    }
    cout << 0 << " " << sumP[0] << endl;
    int cmax = 0;
    for (unsigned int i = 0; i < nProcessors; i++)
    {
        if (sumP[i] > cmax) cmax = sumP[i];
    }
    cout << "Solution: " << cmax << endl;
}

zach2::~zach2()
{
    //dtor
}
