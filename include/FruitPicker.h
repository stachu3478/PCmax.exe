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
        int getRemFruits() { return remFruits; };
        void reset() { remFruits = nFruits; };

    protected:

    private:
        int* fruits;
        int remFruits;
        int nFruits;
};

#endif // FRUITPICKER_H
