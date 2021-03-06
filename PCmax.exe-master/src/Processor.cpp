#include <fstream>
#include <iostream>

#include "sort.h"
#include "Processor.h"

using namespace std;

Processor* Processor::s_processors = 0;
int Processor::s_nProcessors = 0;
int Processor::s_nTasks = 0;
int Processor::s_weight = 0;

Processor::Processor(int taskArraySize = s_nTasks - s_nProcessors + 1)
{
    m_weight = 0;
    m_total = 0;
    m_tasks = new unsigned int[taskArraySize];
}

Processor::~Processor()
{
    delete m_tasks;
}

unsigned int Processor::operator+=(const unsigned int task)
{
    return s_weight += (m_weight += (m_tasks[m_total++] = task));
}

unsigned int Processor::setNumberProcessors(int num, int nTasks)
{
    s_nTasks = nTasks;
    s_nProcessors = num;
    cout << "Creating procs\n" << num << endl;
    s_processors = new Processor[num];
    return num;
}

unsigned int Processor::findMin()
{
    unsigned int minWeight = 4294967295;
    unsigned int minIndex = 0;
    for (int i = 0; i < s_nProcessors; i++)
    {
        unsigned int weight = s_processors[i].m_weight;
        if (weight < minWeight)
        {
            minWeight = weight;
            minIndex = i;
        }
    }
    return minIndex;
}

unsigned int Processor::findMax()
{
    unsigned int maxWeight = 0;
    unsigned int maxIndex = 0;
    for (int i = 0; i < s_nProcessors; i++)
    {
        unsigned int weight = s_processors[i].m_weight;
        if (weight > maxWeight)
        {
            maxWeight = weight;
            maxIndex = i;
        }
    }
    return maxIndex;
}

unsigned int Processor::assignTask(const unsigned int task)
{
    unsigned int minp = Processor::findMin();
    s_processors[minp] += task;
    return minp;
}

unsigned int*& Processor::solve(char* file, unsigned int& sol)
{
    ifstream source(file);
    cout << "File opened\n";
    int nProcessors = 0, nTasks = 0;
    source >> nProcessors;
    source >> nTasks;
    cout << nProcessors << endl;
    setNumberProcessors(nProcessors, nTasks);
    cout << "Processors defined\n";

    unsigned int* procIds = new unsigned int[nTasks];

    int counter = 0;
    for (int i = 0; i < s_nProcessors && i < s_nTasks; i++, counter++)
    {
        unsigned int task;
        source >> task;
        s_processors[i] += task;
        procIds[i] = task;
    };
    cout << "First tasks assigned\n";
    while (counter < s_nTasks)
    {
        unsigned int task;
        source >> task;
        procIds[counter++] = assignTask(task);
    };
    sol = s_processors[findMax()].m_weight;
    cout << "The solution is: " << sol << endl;

    unsigned int*& procRef = procIds;
    return procRef;
}

unsigned int*& Processor::solveSorted(char* file, unsigned int& sol)
{
    ifstream source(file);
    cout << "File opened\n";
    int nProcessors = 0, nTasks = 0;
    source >> nProcessors;
    source >> nTasks;
    cout << nProcessors << endl;
    setNumberProcessors(nProcessors, nTasks);
    cout << "Processors defined\n";

    unsigned int* procIds = new unsigned int[nTasks];

    unsigned int tasks[nTasks];
    for (unsigned int i = 0; i < s_nTasks; i++)
    {
        source >> tasks[i];
    }
    sortItems(tasks, s_nTasks);

    int counter = 0;
    for (int i = 0; i < s_nProcessors && i < s_nTasks; i++, counter++)
    {
        s_processors[i] += tasks[i];
        procIds[counter] = counter;
    };
    cout << "First tasks assigned\n";
    while (counter < s_nTasks)
    {
        procIds[counter] = assignTask(tasks[counter++]);
    };
    sol = s_processors[findMax()].m_weight;
    cout << "The solution is: " << sol << endl;

    unsigned int*& procRef = procIds;
    return procRef;
}
