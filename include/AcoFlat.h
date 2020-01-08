#ifndef ACOFLAT_H
#define ACOFLAT_H

#include "FruitPicker.h"
#include "FruitBins.h"

class AcoFlat
{
    public:
        /** Default constructor */
        AcoFlat(char* file);
        /** Default destructor */
        virtual ~AcoFlat();

        void acoIteration();
        int standardIteration(int n);

        int pickAvailableNextJob(int j);
        // int assignJob(int p, int j);
        int assignJobId(int p, int id);
        void verify();
        int dryRun(int s);
        int wetRun(int s);
        int findNextJob(int j);

    protected:

    private:
        int vape;
        int totalTime;
        int* edgeFeromon;
        int nEdges;
        int* edgesRemaining;
        int nEdgesRemaining;

        int nJobs;
        int* jobTime;
        int* jobIds;
        FruitPicker* jobs;

        FruitBins* procs;
        int* jobQueue;
        int bestRecord;
        int bestAcoRecord;

        int worstGreedy;
};

#endif // ACOFLAT_H
