#include <iostream>
#include <fstream>
#include <time.h>
#include <ctime>

#include <stdlib.h>
#include <cstdio>

#include <string>
#include <cstring>

#include "sort.h"
#include "Processor.h"
#include "Generator.h"

#include "TGraph.h"
#include "NestLevel.h"
#include "AntSolver.h"
#include "zach2.h"
#include "AcoFlat.h"
#include "FruitPicker.h"
#include "MiniOpt.h"
#include "Colony.h"
#include "AntColony.h"
#include "Guiness.h"
#include "Metropolis.h"

using namespace std;

void printUsage(char* name)
{
    cout << "Usage: " << name << " <subcommand>\n"
        << "Where subcommand could be the following:\n"
        << "generate <processors> <tasks> - creates new instance of problem for the algorithm with specified number of tasks and processors\n"
        << "    It generates random number of processors and tasks from 1 to 1000 by default\n"
        << "solve <file> <type> - solves instances, where:\n"
        << "    <file> is the name of the file in the directory for instance data\n"
        << "    \"m30.txt\" by default\n"
        << "    <type> algorithm type you want to use. Available ones are:\n"
        << "    greedy - Tries to solve in the fastest way. Used by default.\n"
        << "    greedy2 - Some other point of view.\n"
        << "    greedy3 - greedy2 v2\n"
        << "    gg3 - grasp run of choice between LTP and greedy3"
        << "    presort - Sorts the array of tasks and then runs greedy algorithm.\n"
        << "    aco - Uses graph system and ant behavioral system.\n"
        << "    acosort - aco with task pre-sorting.\n"
        << "    acoflat - Uses graph system based on procs a vertices"
        << "    antcolony - ^^ + colony\n"
        << "    metropolis - -=<{[( TRY ME )]}>=-"
        << "test - tests new feature of topological graphs\n"
        << "test2 - tests another feature of topological graphs\n"
        << "test3 - integer allocation test\n"
        << "test4 - Tests fruit picker\n"
        << "test5 - tests MiniOpt class\n"
        << "test6 - tests colony class\n";
}

int main(int argc, char* argv[])
{
    string cmd;
    if (argc <= 1)
    {
        // someTest();
        printUsage(argv[0]);
        cmd = "s";
        //return 0;
    }
    else {
        cmd = argv[1];
    };
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
        string type = "acoflat";
        if (argc > 3) type = argv[3];
        clock_t start = clock();

        unsigned int o = 0;
        unsigned int& O = o;
        srand(time(NULL));

        if (type == "greedy") Processor::solve(file, o);
        else if (type == "presort") Processor::solveSorted(file, O);
        else if (type == "aco") new AntSolver(file, false);
        else if (type == "acosort") new AntSolver(file, true);
        else if (type == "greedy2") new zach2(file, 0);
        else if (type == "greedy3") new zach2(file, 1);
        else if (type == "gg3") new zach2(file, 2);
        else if (type == "acoflat") new AcoFlat(file);
        else if (type == "antcolony") new AntColony(file);
        else if (type == "metropolis") new Metropolis(file);
        else
        {
            printUsage(argv[0]);
            return 0;
        };

        cout<<"Czas wykonywania: "<< clock() - start <<" ms"<<endl;
    }
    else if (cmd == "test" || cmd == "t")
    {
        TGraph<int> graph(11); // A graph with 10 nodes
        cout << "Graph size " << graph.GetSize() << " and is " << (graph.IsExpanded() ? "expanded" : "collapsed") << endl;
        graph.expand(5);
        cout << "Graph size " << graph.GetSize() << " and is " << (graph.IsExpanded() ? "expanded" : "collapsed") << " Value " << graph.GetValue() << endl;
        for (int i = 0; i < 10; i++)
        {
            TGraph<int> grap = graph[i];
            cout << "Graph size " << grap.GetSize() << " and is " << (grap.IsExpanded() ? "expanded" : "collapsed") << " Value " << graph.GetValue() << endl;
        }
        cout << "Graph size " << graph.GetSize() << " and is " << (graph.IsExpanded() ? "expanded" : "collapsed") << endl;
        graph.collapse();
        cout << "Graph size " << graph.GetSize() << " and is " << (graph.IsExpanded() ? "expanded" : "collapsed") << endl;
    }
    else if (cmd == "test2" || cmd == "t2")
    {
        NestLevel::test();
    }
    else if (cmd == "test4" || cmd == "t4")
    {
        FruitPicker::test();
    }
    else if (cmd == "test3" || cmd == "t3")
    {
        int* arr = new int[10];
        for (int i = 0; i < 10; i++)
        {
            cout << arr[i] << endl;
        }
    }
    else if (cmd == "test5" || cmd == "t5")
    {
        MiniOpt::test();
    }
    else if (cmd == "test6" || cmd == "t6")
    {
        Colony::test();
    }
    else if (cmd == "test7" || cmd == "t7")
    {
        Guiness::test();
    }
    else {
        printUsage(argv[0]);
    }

    return 0;
}
