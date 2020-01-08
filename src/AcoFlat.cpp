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

// Takes edge remaining
int AcoFlat::pickAvailableNextJob(int j)
{
    int edgeIndex = mat2Get(j, rand() % nEdgesRemaining, nJobs);
    int job = edgesRemaining[edgeIndex];
    int hideIndex = mat2Get(j, nEdgesRemaining - 1, nJobs);
    edgesRemaining[edgeIndex] = edgesRemaining[hideIndex];
    edgesRemaining[hideIndex] = job;
    return job;
}

/*int AcoFlat::assignJob(int p, int j)
{
    int jobId = jobIds[j];
    procTotalTime[p] += jobTime[jobId];
    jobIds[j] = jobIds[jobs->getRemFruits()];
    jobIds[jobs->getRemFruits()] = jobId;
    return jobId;
    // cout << "id: " << j << " Value: " << job << " TO: " << p << endl;
}*/

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
        jobQueue[i] = findNextJob(jobQueue[i - 1]);
        procs->addToLeast(jobTime[jobQueue[i]]);
    }

    int solution = procs->getMax();
    if (solution < bestRecord) {
        bestRecord = solution;
        cout << "New crazy record: " << solution << endl;
        verify();
    }
    return solution;
}

void AcoFlat::acoIteration()
{
    nEdgesRemaining = nJobs;
    for (int i = 0; i < nJobs; i++)
    {
        int solution = standardIteration(i);
        // TODO feromon assignation
        for (int j = 0; j < nJobs - 1; j++)
            edgeFeromon[mat2Get(jobQueue[j], jobQueue[j + 1], nJobs)] += totalTime - solution;
        nEdgesRemaining--;
    }
}

int AcoFlat::findNextJob(int j)
{
    int bestNode = -294967295;
    int bestId = 0;
    for (int i = 0; i < jobs->getRemFruits(); i++)
    {
        int idx = mat2Get(j, jobs->show(i), nJobs);
        if (edgeFeromon[idx] > bestNode)
        {
            bestNode = edgeFeromon[idx];
            bestId = i;
        }
    }
    int job = jobs->pickArr(bestId);
    // cout << bestId << " " << job << endl;
    return job;
}

// TODO think about remove
int AcoFlat::dryRun(int start)
{
    procs->reset();
    jobs->reset();
    int currentJob = start;
    for (int i = 0; i < nJobs; i++)
    {
        jobQueue[i] = findNextJob(currentJob);
        procs->addToLeast(jobTime[jobQueue[i]]);
    }

    int solution = procs->getMax();
    if (solution < bestAcoRecord)
        bestAcoRecord = solution;
    cout << "ACO Solution: " << solution << endl;
    return solution;
}

int AcoFlat::wetRun(int start) {
    procs->reset();
    jobs->reset();
    jobQueue[0] = jobs->pick(start);
    procs->addToLeast(jobTime[jobQueue[0]]);
    for (int i = 1; i < nJobs; i++)
    {
        jobQueue[i] = findNextJob(jobQueue[i - 1]);
        procs->addToLeast(jobTime[jobQueue[i]]);
    }

    int solution = procs->getMax();
    if (solution < bestAcoRecord)
    {
        bestAcoRecord = solution;
        cout << "New ACO record: " << solution << endl;
        verify();
    }
    for (int j = 0; j < nJobs - 1; j++)
        edgeFeromon[mat2Get(jobQueue[j], jobQueue[j + 1], nJobs)] += worstGreedy - solution;
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
    bestRecord = 294967295;
    bestAcoRecord = bestRecord;

    jobTime = new int[nJobs];
    jobIds = new int[nJobs];
    jobs = new FruitPicker(nJobs);
    totalTime = 0;
    for (int i = 0; i < nJobs; i++)
    {
        source >> jobTime[i];
        totalTime += jobTime[i];
        jobIds[i] = i;
    }
    worstGreedy = (totalTime / nProcs + 1) * 2;

    jobQueue = new int[nJobs];

    nEdges = nJobs * nJobs;
    edgesRemaining = new int[nEdges];
    int e = 0;
    for (int i = 0; i < nJobs; i++)
    {
        for (int j = 0; j < nJobs; j++)
            edgesRemaining[e++] = j;
    }

    edgeFeromon = new int[nEdges];
    for (int i = 0; i < nEdges; i++)
        edgeFeromon[i] = 0;

    nEdgesRemaining = nJobs;
    for (int j = 0; j < 10000; j++)
    {
        acoIteration();
        for (int i = 0; i < nJobs; i++)
        {
            wetRun(i);
        }
    }
    cout << "Best record: " << bestRecord << endl;
    cout << "Best ACO record: " << bestAcoRecord << endl;
    cout << "What is better?" << endl;
    if (bestRecord < bestAcoRecord)
        cout << "Randomizing!!!" << endl;
    else
        cout << "Feromon!!!" << endl;
}

AcoFlat::~AcoFlat()
{
    delete jobs;
}
