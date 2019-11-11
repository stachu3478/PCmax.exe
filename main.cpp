<<<<<<< HEAD
#include <iostream>
#include <fstream>
#include <Processor.h>
#include <chrono>

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    auto start = std::chrono::system_clock::now();
    Processor::solve("m30.txt");
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";
    return 0;
}
=======
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
>>>>>>> fd799c0dfa9f7eaa7280bb74f7011181f2af82ce
