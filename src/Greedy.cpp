#include "Greedy.h"

#include <iostream>
#include "FruitBins.h"

using namespace std;

Greedy::Greedy(int p, int* j, int n)
{
    jobTime = j;
    nJobs = n;
    procs = new FruitBins(p);
    jobs = new FruitPicker(n);
    jobQueue = new int[n];
    totalTime = 0;
    for (int i = 0; i < nJobs; i++)
    {
        totalTime += jobTime[i];
    }
}

int mat2Get(int x, int y, int n)
{
    return x * n + y;
}

void Greedy::verify()
{
    int sum = 0;
    int sumProcs = procs->getTotal();
    for (int i = 0; i < nJobs; i++)
    {
        sum += jobTime[jobQueue[i]];
    };
    if (sum != totalTime)
    {
        cout << "Invalid task sum: " << sum << " differs " << totalTime << endl;
        for (int i = 0; i < nJobs; i++)
        {
            cout << jobQueue[i] << " ";
        };
        cout << endl;
        jobs->dump();
        throw exception();
    } else if (sumProcs != totalTime)
    {
        cout << "Invalid procs sum: " << sumProcs << " differs " << totalTime << endl;
        for (int i = 0; i < nJobs; i++)
        {
        //    cout << jobQueue[i] << " ";
        };
        cout << endl;
        //jobs->dump();
        throw exception();
    } else if (procs->getMax() == 151)
    {
        int* procJobs = new int[500];
        int* procN = new int[50];
        for (int i = 0; i < 50; i++)
            procN[i] = 0;
        jobs->reset();
        procs->reset();
        for (int i = 0; i < jobs->getRemFruits(); i++)
        {
            int proc = procs->addToLeast(jobTime[jobQueue[i]]);
            int poz = procN[proc]++;
            int idx = mat2Get(proc, poz, 10);
            procJobs[idx] = jobTime[jobQueue[i]];

        }
        for (int i = 0; i < 50; i++)
        {
            cout << "--" << endl;
            for (int j = 0; j < procN[i]; j++)
            {
                cout << procJobs[mat2Get(i, j, 10)] << " ";
            }
        }
        exit(0);
    }
}

int Greedy::solve()
{
    while (jobPtr < nJobs)
        step();
    return getSolution();
}

int Greedy::step()
{
    procs->addToLeast(jobTime[
                        jobQueue[jobPtr++] = jobs->pick()
                      ]);
}

int Greedy::step(int j)
{
    procs->addToLeast(jobTime[
                        jobQueue[jobPtr++] = jobs->pick(j)
                      ]);
}

int Greedy::stepId(int jId)
{
    procs->addToLeast(jobTime[
                        jobQueue[jobPtr++] = jobs->pickArr(jId)
                      ]);
}

int Greedy::getSolution()
{
    int solution = procs->getMax();
    if (recorder->process(recordPtr, solution))
        verify();
    return solution;
}

void Greedy::reset()
{
    jobs->reset();
    procs->reset();
    jobPtr = 0;
}

Greedy::~Greedy()
{
    //dtor
}
