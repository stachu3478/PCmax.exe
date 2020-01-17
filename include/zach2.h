#ifndef ZACH2_H
#define ZACH2_H

#include "FruitMagazine.h"
#include "Guiness.h"

class zach2
{
    public:
        zach2(char* file, int type);
        zach2(int p, int* j, int n);
        virtual ~zach2();

        void bind2();
        void bind3();
        void reset();
        void step(bool bclpi);
        int getJobCount() { return nTasks; };
        int getSolution();
        int getLimit() { return cMaxLimit; };

        void setRecorder(Guiness* r) { recorder = r; };
        void pointRec(int id) { recordPtr = id; };
        bool wasRecord() { return lastRecord; };

    protected:

    private:
        int nProcessors;
        int nTasks;
        int cMaxLimit;
        int taskSum;
        int* tasks;
        int* pBind;
        int* sumP;
        int pos;
        FruitMagazine* procJobs;

        bool lastRecord;

        Guiness* recorder;
        int recordPtr;

        void bind1();
        void init();
};

#endif // ZACH2_H
