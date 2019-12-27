#ifndef ACOFLAT_H
#define ACOFLAT_H


class AcoFlat
{
    public:
        /** Default constructor */
        AcoFlat(char* file);
        /** Default destructor */
        virtual ~AcoFlat();

        void acoIteration();
        int standardIteration(int n);

        int findMin();
        int findMax();
        int pickAvailableNextJob(int j);
        int assignJob(int p, int j);

    protected:

    private:
        int* edgeFeromon;
        int nEdges;
        int* edgesRemaining;
        int nEdgesRemaining;

        int nJobs;
        int* jobTime;
        int nJobsRemaining;

        int nProcs;
        int* procTotalTime;
        int* jobQueue;
        int bestRecord;
        int bestAcoRecord;
};

#endif // ACOFLAT_H
