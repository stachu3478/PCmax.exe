#include "Metropolis.h"

#include <stdlib.h>
#include <ctime>
#include <fstream>
#include <iostream>

#include "FruitPicker.h"
#include "FruitBins.h"
#include "zach2.h"

using namespace std;

int Metropolis::standardIteration()
{
    greedy->pointRec(0);
    greedy->reset();
    int nJobs = greedy->getJobCount();
    int lastDecision; // Brak wplywu
    greedy->step(true);
    for (int i = 1; i < nJobs; i++)
    {
        lastDecision = rand() % 2;
        greedy->step(lastDecision == 1);
        decisionQueue[i] = lastDecision;
    }
    return greedy->getSolution();
}

int Metropolis::acoIteration()
{
    int nJobs = greedy->getJobCount();
    int solution = standardIteration();
    for (int j = 1; j < nJobs - 1; j++)
        feromon->grow((j << 1) + (decisionQueue[j] ? 1 : 0), decisionQueue[j + 1] ? 1 : 0, worstGreedy - solution);
    return solution;
}

int Metropolis::dryRun()
{
    greedy->pointRec(1);
    greedy->reset(); // Brak wplywu
    greedy->step(true);
    int lastDecision = 1;
    for (int i = 1; i < greedy->getJobCount(); i++)
    {
        lastDecision = feromon->getBiggest((i << 1) + lastDecision, boolGroup, 2);
        greedy->step(
            lastDecision == 1
        );
        decisionQueue[i] = lastDecision;
        // cout << lastDecision << endl;
    }
    return greedy->getSolution();
}

int Metropolis::wetRun() {
    int solution = dryRun();
    int nJobs = greedy->getJobCount();
    for (int j = 0; j < nJobs; j++)
        feromon->grow((j << 1) + (decisionQueue[j] ? 1 : 0), decisionQueue[j + 1] ? 1 : 0, worstGreedy - solution);
    return solution;
}

Metropolis::Metropolis(char* file)
{
    ifstream source(file);
    cout << "File opened\n";
    int nProcs;
    int nJobs;
    source >> nProcs;
    source >> nJobs;
    cout << "Processors defined: " << nProcs << " Jobs: " << nJobs << endl;
    recorder = new Guiness(2, 294967295);
    recorder->setName(0, "CRAZY");
    recorder->setName(1, "ACO");
    boolGroup = new int[2];
    boolGroup[0] = 0;
    boolGroup[1] = 1;
    decisionQueue = new bool[nJobs];

    int* jobTime = new int[nJobs];
    totalTime = 0;
    for (int i = 0; i < nJobs; i++)
    {
        source >> jobTime[i];
        totalTime += jobTime[i];
    }
    worstGreedy = (totalTime / nProcs + 1) * 4 / 3;
    greedy = new zach2(nProcs, jobTime, nJobs);
    greedy->setRecorder(recorder);

    feromon = new FruitQualifier(nJobs << 2, 2);

    int limit = greedy->getLimit();
    greedy->bind2();
    int solution = greedy->getSolution();
    cout << worstGreedy << " " << solution << endl;
    for (int j = 0; j < nJobs; j++)
        feromon->grow((j << 1) + 1, 1, worstGreedy - solution);
    if (solution == limit)
    {
        cout << "Already optimal: " << solution << endl;
        exit(1);
    }

    greedy->bind3();
    solution = greedy->getSolution();
    for (int j = 0; j < nJobs; j++)
        feromon->grow(j << 1, 0, worstGreedy - solution);
    if (solution == limit)
    {
        cout << "Already optimal" << endl;
        recorder->report();
        exit(1);
    }

    for (int j = 0; j < 100000; j++)
    {
        for (int i = 0; i < 10; i++)
            if (wetRun() == limit)
                break;
        if (acoIteration() == limit)
            break;
    }
    recorder->report();
}

Metropolis::~Metropolis()
{
    delete greedy;
}
