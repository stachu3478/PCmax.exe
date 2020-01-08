#ifndef FRUITBINS_H
#define FRUITBINS_H


class FruitBins
{
    public:
        FruitBins(int bins);
        virtual ~FruitBins();

        int getLeast();
        int getMax();
        int addToLeast(int fruit);
        int getTotal();
        void reset() { binPtr = 0; };

    protected:

    private:
        int nBins;
        int* bins;

        int binPtr;
};

#endif // FRUITBINS_H
