#include "AcoFlat.h"

#include <stdlib.h>
#include <ctime>
#include <fstream>
#include <iostream>

#include "FruitPicker.h"
#include "FruitBins.h"

using namespace std;

int mat2Get(int x, int y, int n)
{
    return x * n + y;
}

void AcoFlat::verify()
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

int AcoFlat::standardIteration(int n)
{
    procs->reset();
    jobs->reset();
    jobQueue[0] = jobs->pick(n);
    procs->addToLeast(jobTime[jobQueue[0]]);
    for (int i = 1; i < nJobs; i++)
    {
        jobQueue[i] = jobs->pick();
        procs->addToLeast(jobTime[jobQueue[i]]);
    }

    int solution = procs->getMax();
    if (recorder->process(0, solution))
        verify();
    return solution;
}

void AcoFlat::acoIteration()
{
    // nEdgesRemaining = nJobs;
    for (int i = 0; i < nJobs; i++)
    {
        int solution = standardIteration(i);
        for (int j = 0; j < nJobs - 1; j++)
            feromon->grow(jobQueue[j], jobQueue[j + 1], worstGreedy - solution);
            // edgeFeromon[mat2Get(jobQueue[j], jobQueue[j + 1], nJobs)] += totalTime - solution;
        // nEdgesRemaining--;
    }
}

int AcoFlat::dryRun(int start)
{
    procs->reset();
    jobs->reset();
    jobQueue[0] = jobs->pick(start);
    procs->addToLeast(jobTime[jobQueue[0]]);
    for (int i = 1; i < nJobs; i++)
    {
        int index = feromon->getBiggest(jobQueue[i - 1], jobs->showList(), jobs->getRemFruits());//jobQueue[i - 1]);
        jobQueue[i] = jobs->pickArr(index);
        procs->addToLeast(jobTime[jobQueue[i]]);
    }
    int solution = procs->getMax();
    if (recorder->process(1, solution))
        verify();
    return solution;
}

int AcoFlat::wetRun(int start) {
    int solution = dryRun(start);
    for (int j = 0; j < nJobs - 1; j++)
        feromon->grow(jobQueue[j], jobQueue[j + 1], worstGreedy - solution);
        //nEdgesRemaining--;
    return solution;
}

AcoFlat::AcoFlat(char* file)
{
    ifstream source(file);
    cout << "File opened\n";
    int nProcs;
    source >> nProcs;
    procs = new FruitBins(nProcs);
    source >> nJobs;
    cout << "Processors defined: " << nProcs << " Jobs: " << nJobs << endl;
    recorder = new Guiness(2, 294967295);
    recorder->setName(0, "CRAZY");
    recorder->setName(1, "ACO");

    jobTime = new int[nJobs];
    jobs = new FruitPicker(nJobs);
    totalTime = 0;
    for (int i = 0; i < nJobs; i++)
    {
        source >> jobTime[i];
        totalTime += jobTime[i];
    }
    worstGreedy = (totalTime / nProcs + 1) * 2;

    jobQueue = new int[nJobs];
    // skrót programowy, powinno byc o 1 mniej krawedzi
    feromon = new FruitQualifier(nJobs, nJobs);

    for (int j = 0; j < 10; j++)
    {
        for (int i = 0; i < nJobs; i++)
        {
            wetRun(i);
        }
        acoIteration();
    }
    recorder->report();
}

AcoFlat::~AcoFlat()
{
    delete jobs;
}
