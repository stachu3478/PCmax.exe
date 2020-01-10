#ifndef MINIOPT_H
#define MINIOPT_H

class MiniOpt
{
    public:
        MiniOpt(int* arr1, int* arr2, int size1, int size2);
        virtual ~MiniOpt();

        int getSolution() { return sum1 > sum2 ? sum1 : sum2; };
        static void test();

    protected:

    private:
        int diff;
        int* arr1;
        int* arr2;
        int sum1, sum2;
        bool change;

        void exchange(int i, int j);
};

#endif // MINIOPT_H
