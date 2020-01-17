#include <fstream>
#include <iostream>

#include "sort.h"
#include "zach2.h"
#include "cmath"

using namespace std;

void zach2::bind1()
{
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
            } else
                sum += add;
        }
        sumP[i] /= i;
        cout << sum << " " << sumP[i] << endl;
    };
}

void zach2::bind2()
{
    taskSum = 0;
    for (int i = 0; i < nProcessors; i++)
        sumP[i] = 0;
    for (int i = 0; i < nTasks; i++)
        taskSum += tasks[i];
    cMaxLimit = (int)ceil((float)taskSum / (float)nProcessors);
    cout << "cmaxLimit: " << cMaxLimit << endl;
    for (unsigned int j = 0; j < nTasks; j++)
    {
        int cMin = 99999999;
        int assigned = false;
        int cMinIndex;
        for (int nP = 0; nP < nProcessors; nP++)
        {
            int afterAddSum;
            if ((afterAddSum = sumP[nP] + tasks[j]) <= cMaxLimit) {
                sumP[nP] = afterAddSum;
                pBind[j] = nP;
                assigned = true;
                procJobs->add(nP, tasks[j]);
                // cout << "Assigned: " << nP << endl;
                break;
            }
            if (afterAddSum < cMin)
            {
                cMin = afterAddSum;
                cMinIndex = nP;
            }
        }
        if (!assigned)
        {
            sumP[cMinIndex] = cMin;
            pBind[j] = cMinIndex;
            procJobs->add(cMinIndex, tasks[j]);
            // cout << "Not assigned: " << cMinIndex << endl;
        }
    }
}

zach2::zach2(char* file, bool v3)
{
    ifstream source(file);
    cout << "File opened\n";
    source >> nProcessors;
    source >> nTasks;
    cout << nProcessors << endl;
    cout << "Processors defined\n";
    tasks = new unsigned int[nTasks];
    sumP = new int[nProcessors];
    pBind = new int[nTasks];
    procJobs = new FruitMagazine(nProcessors, 100);
    for (unsigned int i = 0; i < nTasks; i++)
    {
        source >> tasks[i];
        pBind[i] = 0;
    }
    sortItems(tasks, nTasks);

    if (v3)
        bind2();
    else
        bind1();

    procJobs->printContents();

    sumP[0] = 0;
    for (unsigned int i = 0; i < nTasks; i++)
    {
        if (pBind[i] == 0) sumP[0] += tasks[i];
    }
    cout << 0 << " Total sum control: " << sumP[0] << endl;
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
