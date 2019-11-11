#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include <ctime>

#include <string>
#include <cstring>

#include "sort.h"
#include "Processor.h"
#include "Generator.h"

using namespace std;

void printUsage(char* name)
{
    cout << "Usage: " << name << " <subcommand>\n"
        << "Where subcommand could be the following:\n"
        << "generate <processors> <tasks> - creates new instance of problem for the algorithm with specified number of tasks and processors\n"
        << "It generates random number of processors and tasks from 1 to 1000 by default\n"
        << "solve <file> <type> - solves instances, where:\n"
        << "<file> is the name of the file in the directory for instance data\n"
        << "\"m30.txt\" by default\n"
        << "<type> algorithm type you want to use. Available ones are:\n"
        << "greedy - Tries to solve in the fastest way. Used by default.\n"
        << "presort - Sorts the array of tasks and then runs greedy algorithm.\n";
}

int main(int argc, char* argv[])
{
    if (argc <= 1)
    {
        // someTest();
        printUsage(argv[0]);
        return 0;
    }

    string cmd = argv[1];
    ///////////// Generacja pliku //////////////
    if (cmd == "generate" || cmd == "g")
    {
        int numb_proc = 1 + rand() % 1000;
        if (argc > 2)
        {
            numb_proc = atoi(argv[2]);
        }
        int numb_task = numb_proc + rand() % 1000;
        if (argc > 3)
        {
            numb_task = atoi(argv[3]);
        }

        Generator(numb_proc, numb_task);
    }
    ///////////// Rozwiazywanie zadania //////////////
    else if (cmd == "solve" || cmd == "s")
    {
        char* file = "m30.txt";
        if (argc > 2) file = argv[2];
        string type = "greedy";
        if (argc > 3) type = argv[3];
        clock_t start = clock();

        if (type == "greedy") Processor::solve(file);
        else if (type == "presort") Processor::solveSorted(file);
        else
        {
            printUsage(argv[0]);
            return 0;
        }

        printf( "Czas wykonywania: %lu ms\n", clock() - start );
    }
    else
    {
        printUsage(argv[0]);
    }

    return 0;
}
