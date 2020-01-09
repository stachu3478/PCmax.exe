#ifndef FRUITCASE_H
#define FRUITCASE_H


class FruitCase
{
    public:
        FruitCase();
        FruitCase(int initN);
        virtual ~FruitCase();

        int getSize() { return length; };
        void add(int fruit);
        void printContents();
        int* open();

    protected:

    private:
        int initLength;
        int length;
        int maxLength;
        int lastTab;

        int* tabs[10];
        int* inventory;
};

#endif // FRUITCASE_H
