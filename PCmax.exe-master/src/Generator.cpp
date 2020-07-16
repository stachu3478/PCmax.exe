#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <cstdio>
#include <ctime>

#include "Generator.h"

using namespace std;

Generator::Generator(int proc_n, int task_n)
{

    ofstream gen("gen_file.txt");
    srand(time(NULL));

    gen << proc_n << endl;
    gen << task_n << endl;

    for(int i=0; i<task_n; i++)
    {
        gen << 1 + rand() % 1000 << endl;   //range [1,1000]
    }
}

Generator::~Generator()
{
}
