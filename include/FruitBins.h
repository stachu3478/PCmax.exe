#ifndef FRUITBINS_H
#define FRUITBINS_H


class FruitBins
{
    public:
        FruitBins(int bins);
        virtual ~FruitBins();

        int getLeast() { return getLeastWild(true); };
        int getMax();
        int getMin() { return getLeastWild(false); };
        int addToLeast(int fruit);
        int getTotal();
        void reset() { binPtr = 0; };

    protected:

    private:
        int nBins;
        int* bins;

        int binPtr;

        int getLeastWild(bool index);
};

#endif // FRUITBINS_H
