#ifndef ZACH2_H
#define ZACH2_H

#include "FruitMagazine.h"

class zach2
{
    public:
        zach2(char* file, bool v3);
        virtual ~zach2();

    protected:

    private:
        int nProcessors;
        int nTasks;
        int cMaxLimit;
        int taskSum;
        unsigned int* tasks;
        int* pBind;
        int* sumP;
        FruitMagazine* procJobs;

        void bind1();
        void bind2();
};

#endif // ZACH2_H
