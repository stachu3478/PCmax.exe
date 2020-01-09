#ifndef MINIOPT_H
#define MINIOPT_H

class MiniOpt
{
    public:
        MiniOpt(int* arr1, int* arr2, int size1, int size2);
        virtual ~MiniOpt();

    protected:

    private:
        int* arr1, arr2;

        void exchange(int i, int j);
};

#endif // MINIOPT_H
