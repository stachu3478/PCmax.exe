#ifndef FRUITPICKER_H
#define FRUITPICKER_H

class NoFruitsException {};
class FruitNotFoundExcecption {};

class FruitPicker
{
    public:
        FruitPicker(int n);
        virtual ~FruitPicker();

        static void test();

        int pick();
        int pick(int id);
        int pickArr(int id);
        int show(int arrId) { return fruits[arrId]; };
        int* showList() { return fruits; }; // should be readonly
        int getRemFruits() { return remFruits; };
        void reset() { remFruits = nFruits; };
        void dump();

    protected:

    private:
        int* fruits;
        int remFruits;
        int nFruits;

        int pickWild(int index);
};

#endif // FRUITPICKER_H
