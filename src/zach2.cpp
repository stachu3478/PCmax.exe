#include <fstream>
#include <iostream>

#include "sort.h"
#include "zach2.h"
#include "cmath"
#include "stdlib.h"

using namespace std;

void zach2::reset()
{
    pos = 0;
    for (int i = 0; i < nProcessors; i++)
        sumP[i] = 0;
}

// Before-Critical Least Processor Index
int zach2::step(bool bclpi)
{
    int cMin = 99999999;
    int assigned = false;
    int cMinIndex;
    for (int nP = 0; nP < nProcessors; nP++)
    {
        int afterAddSum = sumP[nP] + tasks[pos];
        // detect mode TODO to optimization
        if (bclpi && afterAddSum <= cMaxLimit) {
            sumP[nP] = afterAddSum;
            pBind[pos++] = nP;
            assigned = true;
            return nP;
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
        pBind[pos++] = cMinIndex;
        return cMinIndex;
    }

}

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

int zach2::getSolution()
{
    int solution = 0;
    for (unsigned int i = 0; i < nProcessors; i++)
    {
        if (sumP[i] > solution) solution = sumP[i];
    }
    if (recorder->process(recordPtr, solution))
    {
        lastRecord = true;
    }
    else
        lastRecord = false;
    return solution;
}

// For our master
void zach2::bind2()
{
    reset();
    procJobs = new FruitMagazine(nProcessors, 100);
    for (unsigned int j = 0; j < nTasks; j++)
    {
        int ass = step(true);
        procJobs->add(ass, tasks[j]);
    }
    procJobs->printContents();
}

void zach2::bind3()
{
    reset();
    procJobs = new FruitMagazine(nProcessors, 100);
    for (unsigned int j = 0; j < nTasks; j++)
    {
        int ass = step(false);
        procJobs->add(ass, tasks[j]);
    }
    procJobs->printContents();
}

void zach2::init()
{
    taskSum = 0;
    for (int i = 0; i < nTasks; i++)
        taskSum += tasks[i];
    sortInt(tasks, nTasks);
    cMaxLimit = (int)ceil((float)taskSum / (float)nProcessors);
    cout << "cmaxLimit: " << cMaxLimit << endl;
    recordPtr = 0;
    pos = 0;
}

zach2::zach2(int p, int* j, int n)
{
    tasks = j;
    nProcessors = p;
    nTasks = n;
    sumP = new int[p];
    pBind = new int[n];
    init();
}

zach2::zach2(char* file, int type)
{
    ifstream source(file);
    cout << "File opened\n";
    source >> nProcessors;
    source >> nTasks;
    cout << nProcessors << endl;
    cout << "Processors defined\n";
    tasks = new int[nTasks];
    sumP = new int[nProcessors];
    pBind = new int[nTasks];
    recorder = new Guiness(2, 999);
    for (unsigned int i = 0; i < nTasks; i++)
    {
        source >> tasks[i];
        pBind[i] = 0;
    }

    init();
    reset();
    if (type == 0)
        bind1();
    else if (type == 1)
        bind2();
    else if (type == 2) for (unsigned int j = 0; j < nTasks; j++)
        step((rand() % 2) == 1);
    else if (type == 3)
        bind3();
    else return;

    // procJobs->printContents();

    int cmax = getSolution();
    cout << "Solution: " << cmax << endl;
}

zach2::~zach2()
{
    //dtor
}
