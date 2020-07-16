#include "AntColony.h"

#include <stdlib.h>
#include <ctime>
#include <fstream>
#include <iostream>

#include "FruitPicker.h"
#include "FruitBins.h"
#include "Colony.h"

using namespace std;

int AntColony::dryRun(int start)
{
    greedy->reset();
    greedy->step(start);
    FruitPicker* jobs = greedy->getJobs();
    int* jobQueue = greedy->getJobQueue();
    for (int i = 1; i < greedy->getJobCount(); i++)
        if (rand() % 100 < betaCurrent[0])
            greedy->stepId(
                feromon->getBiggest(greedy->getLastJob(), jobs->showList(), jobs->getRemFruits())
            );
        else
            greedy->step();

    return greedy->getSolution();
}

int AntColony::wetRun(int start) {
    int solution = dryRun(start);
    int* jobQueue = greedy->getJobQueue();
    for (int j = 0; j < greedy->getJobCount() - 1; j++)
        feromon->grow(jobQueue[j], jobQueue[j + 1], worstGreedy - solution);
    return solution;
}

AntColony::AntColony(char* file)
{
    ifstream source(file);
    cout << "File opened\n";
    int nProcs;
    int nJobs;
    source >> nProcs;
    source >> nJobs;
    cout << "Processors defined: " << nProcs << " Jobs: " << nJobs << endl;
    recorder = new Guiness(1, 294967295);
    recorder->setName(0, "ACO");

    int* jobTime = new int[nJobs];
    for (int i = 0; i < nJobs; i++)
        source >> jobTime[i];
    worstGreedy = (totalTime / nProcs + 1) * 2;
    greedy = new Greedy(nProcs, jobTime, nJobs);
    greedy->setRecorder(recorder);
    greedy->pointRec(0);

    beta = new Colony(1, 0, 100);
    betaCenter = new int[1]{ 50 };
    beta->setVec(betaCenter);

    feromon = new FruitQualifier(nJobs, nJobs);

    for (int j = 0; j < 10000; j++)
    {
        betaCurrent = beta->pull();
        for (int i = 0; i < nJobs; i++)
        {
            wetRun(i);
            if (greedy->wasRecord())
            {
                cout << "At beta: " << betaCurrent[0] << endl;
                betaCenter[0] = betaCurrent[0];
                beta->setRange(2);
            }
        }
    }
    recorder->report();
}

AntColony::~AntColony()
{
    delete greedy;
}
