#ifndef ACOFLAT_H
#define ACOFLAT_H

#include "FruitPicker.h"
#include "FruitBins.h"
#include "FruitQualifier.h"
#include "Guiness.h"
#include "Greedy.h"

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
        int assignJobId(int p, int id);
        void verify();
        int dryRun(int s);
        int wetRun(int s);

    protected:

    private:
        int vape;
        int totalTime;
        FruitQualifier* feromon;

        Greedy* greedy;

        int worstGreedy;
        Guiness* recorder;
};

#endif // ACOFLAT_H
