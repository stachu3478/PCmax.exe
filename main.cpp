#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include <ctime>
#include <Processor.h>
#include <Generator.h>

using namespace std;

int main()
{
    clock_t start = clock();

    Processor::solve("m30.txt");

    printf( "Czas wykonywania: %lu ms\n", clock() - start );

///////////// Generacja pliku //////////////

    srand(time(NULL));

    int numb_proc = 1 + rand() % 1000;
    int numb_task = numb_proc + rand() % 1000;

   Generator(numb_proc, numb_task);

    return 0;
}
