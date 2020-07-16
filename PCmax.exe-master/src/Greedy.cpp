#include "Greedy.h"

#include <iostream>
#include "FruitBins.h"
#include "FruitMagazine.h"

using namespace std;

Greedy::Greedy(int p, int* j, int n)
{
    jobTime = j;
    nJobs = n;
    procs = new FruitBins(p);
    jobs = new FruitPicker(n);
    jobQueue = new int[n];
    bestJobQueue = new int[n];
    totalTime = 0;
    for (int i = 0; i < nJobs; i++)
    {
        totalTime += jobTime[i];
    }
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
    } else if (procs->getMax() == 150)
    {
        FruitMagazine* procJobs = new FruitMagazine(50, 10);
        jobs->reset();
        procs->reset();
        for (int i = 0; i < jobs->getRemFruits(); i++)
        {
            int proc = procs->addToLeast(jobTime[jobQueue[i]]);
            procJobs->add(proc, jobTime[jobQueue[i]]);
        }
        procJobs->printContents();
        exit(0);
    } // else cout << procs->getMax() << endl;
    for (int i = 0; i < jobs->getRemFruits(); i++)
        bestJobQueue[i] = jobQueue[i];
}

int Greedy::solve()
{
    while (jobPtr < nJobs)
        step();
    return getSolution();
}

int Greedy::step()
{
    return procs->addToLeast(jobTime[
                        jobQueue[jobPtr++] = jobs->pick()
                      ]);
}

int Greedy::step(int j)
{
    return procs->addToLeast(jobTime[
                        jobQueue[jobPtr++] = jobs->pick(j)
                      ]);
}

int Greedy::stepId(int jId)
{
    return procs->addToLeast(jobTime[
                        jobQueue[jobPtr++] = jobs->pickArr(jId)
                      ]);
}

int Greedy::getSolution()
{
    int solution = procs->getMax();
    if (recorder->process(recordPtr, solution))
    {
        lastRecord = true;
        verify();
    }
    else
        lastRecord = false;
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
