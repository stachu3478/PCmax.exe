#ifndef FINDER_H
#define FINDER_H


class finder
{
    public:
        finder(int* arr, int len);
        virtual ~finder();

        int maxx();
        int minx();

    protected:

    private:
        int* arr;
        int length;
};

#endif // FINDER_H
