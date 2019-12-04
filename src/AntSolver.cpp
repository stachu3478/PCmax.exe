#include <fstream>
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <windows.h>

#include "AntSolver.h"

#include "sort.h"
#include "Processor.h"
#include "NestLevel.h"
#include "Ant.h"

using namespace std;

void hello()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 6);
    cout << "                       xxxxxxx\n"
    << "                  x xxxxxxxxxxxxx x\n"
    << "               x     xxxxxxxxxxx     x\n"
    << "                      xxxxxxxxx\n"
    << "            x          xxxxxxx          x\n"
    << "                ACO     xxxxx   Compute\n"
    << "           x             xxx    Warning   x\n"
    << "                          x\n"
    << "          xxxxxxxxxxxxxxx   xxxxxxxxxxxxxxx\n"
    << "           xxxxxxxxxxxxx     xxxxxxxxxxxxx\n"
    << "            xxxxxxxxxxx       xxxxxxxxxxx\n"
    << "             xxxxxxxxx         xxxxxxxxx\n"
    << "               xxxxxx           xxxxxx\n"
    << "                 xxx             xxx\n"
    << "                     x         x\n"
    << "                          x\n";
    SetConsoleTextAttribute(hConsole, 15);
}

AntSolver::AntSolver(char* file)
{
    hello();
    ifstream source(file);
    unsigned int nProcessors = 0, nTasks = 0;
    source >> nProcessors;
    source >> nTasks;

    unsigned int tasks[nTasks];
    for (unsigned int i = 0; i < nTasks; i++)
    {
        source >> tasks[i];
    }
    sortItems(tasks, nTasks);

    unsigned int greedySolution = 0;
    unsigned int& solRef = greedySolution;
    unsigned int* cond = Processor::solveSorted(file, solRef);

    m_Graph = new NestLevel(nTasks - 1, nProcessors, nTasks - 1);
    NestLevel* t = m_Graph;
    int sum = 0;
    for (unsigned int i = 0; i < nTasks; i++)
    {
        t->SetTaskSize(tasks[i]);
        t->assignFeromon(greedySolution, cond[i]);
        t = t->GetNext();
        sum += tasks[i];
    }
    m_Cycle = 0;

    srand(time(NULL));

    cout << nProcessors << endl;
    cout << nTasks << endl;
    cout << "Total jobs length: " << sum << endl;
    m_BestAnt = new Ant(m_Cycle, nProcessors, nTasks);
    m_BestAnt->walk(m_Graph, nTasks, true, sum);

    unsigned int bestResult = m_BestAnt->GetResult();
    int records = 0;
    for (unsigned int i = 0; i < 10000000; i++)
    {
        m_BestAnt->reset(m_Cycle++);
        unsigned int result = m_BestAnt->walk(m_Graph, nTasks, false, bestResult);
        if (result < bestResult)
        {
            cout << "New record: " << (bestResult = result) << endl;
            records++;
        }
    }
    cout << "So ... the solution is: " << bestResult << " Records: " << records << endl;
}

AntSolver::~AntSolver()
{
    //dtor
}
