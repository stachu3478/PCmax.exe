#ifndef ANTCOLONY_H
#define ANTCOLONY_H

#include "FruitPicker.h"
#include "FruitBins.h"
#include "FruitQualifier.h"
#include "Guiness.h"
#include "Greedy.h"
#include "Colony.h"

class AntColony
{
    public:
        /** Default constructor */
        AntColony(char* file);
        /** Default destructor */
        virtual ~AntColony();

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

        Colony* beta;
        int* betaCenter;
        int* betaCurrent;
};

#endif // ANTCOLONY_H
