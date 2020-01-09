#include "AcoFlat.h"

#include <stdlib.h>
#include <ctime>
#include <fstream>
#include <iostream>

#include "FruitPicker.h"
#include "FruitBins.h"

using namespace std;

int AcoFlat::standardIteration(int n)
{
    greedy->pointRec(0);
    greedy->reset();
    greedy->step(n);
    return greedy->solve();
}

void AcoFlat::acoIteration()
{
    int nJobs = greedy->getJobCount();
    int* jobQueue = greedy->getJobQueue();
    for (int i = 0; i < nJobs; i++)
    {
        int solution = standardIteration(i);
        for (int j = 0; j < nJobs - 1; j++)
            feromon->grow(jobQueue[j], jobQueue[j + 1], worstGreedy - solution);
    }
}

int AcoFlat::dryRun(int start)
{
    greedy->pointRec(1);
    greedy->reset();
    greedy->step(start);
    FruitPicker* jobs = greedy->getJobs();
    int* jobQueue = greedy->getJobQueue();
    for (int i = 1; i < greedy->getJobCount(); i++)
    greedy->stepId(
        feromon->getBiggest(greedy->getLastJob(), jobs->showList(), jobs->getRemFruits())
    );
    return greedy->getSolution();
}

int AcoFlat::wetRun(int start) {
    int solution = dryRun(start);
    int* jobQueue = greedy->getJobQueue();
    for (int j = 0; j < greedy->getJobCount() - 1; j++)
        feromon->grow(jobQueue[j], jobQueue[j + 1], worstGreedy - solution);
    return solution;
}

AcoFlat::AcoFlat(char* file)
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

    int* jobTime = new int[nJobs];
    for (int i = 0; i < nJobs; i++)
        source >> jobTime[i];
    worstGreedy = (totalTime / nProcs + 1) * 2;
    greedy = new Greedy(nProcs, jobTime, nJobs);
    greedy->setRecorder(recorder);

    feromon = new FruitQualifier(nJobs, nJobs);

    for (int j = 0; j < 10000; j++)
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
    delete greedy;
}
