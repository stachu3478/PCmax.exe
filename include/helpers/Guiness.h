#ifndef GUINESS_H
#define GUINESS_H

#include <string>

class Guiness
{
    public:
        Guiness(int nRecords, int worst);
        virtual ~Guiness();

        void setName(int index, std::string name) { names[index] = name; };
        bool process(int index, int record);
        void report();
    protected:

    private:
        int nRecords;
        std::string* names;
        int* records;
};

#endif // GUINESS_H
