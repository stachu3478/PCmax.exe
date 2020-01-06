#include "AcoFlat.h"

#include <stdlib.h>
#include <ctime>
#include <fstream>
#include <iostream>

using namespace std;

int mat2Get(int x, int y, int n)
{
    return x * n + y;
}

int AcoFlat::findMin()
{
    int minWeight = 294967295;
    int minIndex = 0;
    for (int i = 0; i < nProcs; i++)
    {
        int weight = procTotalTime[i];
        if (weight < minWeight)
        {
            minWeight = weight;
            minIndex = i;
        }
    }
    return minIndex;
}

int AcoFlat::findMax()
{
    int maxWeight = 0;
    int maxIndex = 0;
    for (int i = 0; i < nProcs; i++)
    {
        int weight = procTotalTime[i];
        if (weight > maxWeight)
        {
            maxWeight = weight;
            maxIndex = i;
        }
    }
    return maxIndex;
}

int AcoFlat::pickAvailableNextJob(int j)
{
    int edgeIndex = mat2Get(j, rand() % nEdgesRemaining, nJobs);
    int job = edgesRemaining[edgeIndex];
    int hideIndex = mat2Get(j, nEdgesRemaining - 1, nJobs);
    edgesRemaining[edgeIndex] = edgesRemaining[hideIndex];
    edgesRemaining[hideIndex] = job;
    return job;
}

int AcoFlat::assignJob(int p, int j)
{
    int jobId = jobIds[j];
    procTotalTime[p] += jobTime[jobId];
    jobIds[j] = jobIds[--nJobsRemaining];
    jobIds[nJobsRemaining] = jobId;
    return jobId;
    // cout << "id: " << j << " Value: " << job << " TO: " << p << endl;
}

int AcoFlat::standardIteration(int n)
{
    for (int i = 0; i < nProcs; i++)
        procTotalTime[i] = 0;
    nJobsRemaining = nJobs;
    int currentJob = n;
    for (int i = 0; i < nJobs; i++)
    {
        int procId = findMin();
        jobQueue[i] = assignJob(procId, currentJob);
        currentJob = pickAvailableNextJob(currentJob);
    }

    int solution = procTotalTime[findMax()];
    if (solution < bestRecord)
        bestRecord = solution;
    cout << "Solution: " << solution << endl;
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
    for (int i = 0; i < nJobsRemaining; i++)
    {
        int idx = mat2Get(j, i, nJobs);
        if (edgeFeromon[idx] > bestNode)
        {
            bestNode = edgeFeromon[idx];
            bestId = i;
        }
    }
    int job = edgesRemaining[bestId];
    return job;
}

int AcoFlat::dryRun(int start)
{
    for (int i = 0; i < nProcs; i++)
        procTotalTime[i] = 0;
    nJobsRemaining = nJobs;
    int currentJob = start;
    for (int i = 0; i < nJobs; i++)
    {
        int procId = findMin();
        jobQueue[i] = assignJob(procId, currentJob);
        currentJob = findNextJob(currentJob);
    }

    int solution = procTotalTime[findMax()];
    if (solution < bestAcoRecord)
        bestAcoRecord = solution;
    cout << "ACO Solution: " << solution << endl;
    return solution;
}

AcoFlat::AcoFlat(char* file)
{
    ifstream source(file);
    cout << "File opened\n";
    source >> nProcs;
    source >> nJobs;
    cout << "Processors defined: " << nProcs << " Jobs: " << nJobs << endl;
    bestRecord = 294967295;
    bestAcoRecord = bestRecord;

    jobTime = new int[nJobs];
    jobIds = new int[nJobs];
    totalTime = 0;
    for (int i = 0; i < nJobs; i++)
    {
        source >> jobTime[i];
        totalTime += jobTime[i];
        jobIds[i] = i;
    }

    procTotalTime = new int[nProcs];
    jobQueue = new int[nJobs];

    nEdges = nJobs * nJobs;
    edgesRemaining = new int[nEdges];
    int e = 0;
    for (int i = 0; i < nJobs; i++)
        for (int j = 0; j < nJobs; j++)
            edgesRemaining[e++] = j;

    edgeFeromon = new int[nEdges];
    for (int i = 0; i < nEdges; i++)
        edgeFeromon[i] = 0;

    nEdgesRemaining = nJobs;
    acoIteration();
    acoIteration();
    for (int i = 0; i < nJobs; i++)
        dryRun(i);
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
    //dtor
}
