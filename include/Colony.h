#ifndef COLONY_H
#define COLONY_H


class Colony
{
    public:
        Colony(int n, int minx, int maxx);
        virtual ~Colony();

        void setVec(int* v) { vec = v; };
        int* pull();
        int setRange(int val);
        static void test();

    protected:

    private:
        int* vec;
        int* randoms;
        int nDims;
        int minx;
        int maxx;

        int range;
        int range2;
        int prevPow;
        int its;

        int sPow();
};

#endif // COLONY_H
