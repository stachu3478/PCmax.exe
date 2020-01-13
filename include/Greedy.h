#ifndef GREEDY_H
#define GREEDY_H

#include "FruitPicker.h"
#include "FruitBins.h"
#include "Guiness.h"

class Greedy
{
    public:
        Greedy(int p, int* j, int n);
        virtual ~Greedy();

        int solve();
        int solveWorst();
        int step();
        int step(int j);
        int stepId(int jId);
        int getSolution();
        int getMin() { return procs->getMin(); };
        void verify();
        void reset();

        FruitPicker* getJobs() { return jobs; };
        int getLastJob() { return jobQueue[jobPtr - 1]; };
        int getJobCount() { return nJobs; };
        int* getJobQueue() { return jobQueue; };
        bool wasRecord() { return lastRecord; };

        void setRecorder(Guiness* r) { recorder = r; };
        void pointRec(int id) { recordPtr = id; };

    protected:

    private:
        int nJobs;
        int* jobTime;
        int* jobQueue;
        int* bestJobQueue;
        int jobPtr;
        FruitPicker* jobs;
        FruitBins* procs;
        int totalTime;
        int worstSolution;

        bool lastRecord;

        Guiness* recorder;
        int recordPtr;
};

#endif // GREEDY_H
