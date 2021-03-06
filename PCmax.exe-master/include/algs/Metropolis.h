#ifndef METROPOLIS_H
#define METROPOLIS_H

#include "FruitPicker.h"
#include "FruitBins.h"
#include "FruitQualifier.h"
#include "Guiness.h"
#include "zach2.h"

class Metropolis
{
    public:
        /** Default constructor */
        Metropolis(char* file);
        /** Default destructor */
        virtual ~Metropolis();

        int acoIteration();
        int standardIteration();

        int assignJobId(int p, int id);
        void verify();
        int dryRun();
        int wetRun();

    protected:

    private:
        int vape;
        int totalTime;
        FruitQualifier* feromon;
        bool* decisionQueue;
        int* boolGroup;

        zach2* greedy;

        int worstGreedy;
        Guiness* recorder;
};

#endif // METROPOLIS_H
