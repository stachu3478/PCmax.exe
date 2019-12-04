#include "Ant.h"

#include <iostream>
#include "NestLevel.h"

using namespace std;

Ant::Ant(unsigned int cycle, unsigned int procs, unsigned int depth)
{
    m_Cycle = cycle;
    m_MaxProcId = 2;
    m_ProcTasks = new unsigned int[procs];
    m_ProcIds = new unsigned int[depth];
    m_Procs = procs;
}

void Ant::reset(unsigned int cycle)
{
    m_Cycle = cycle;
    m_MaxProcId = 2;
}

unsigned int Ant::walk(NestLevel* graph, unsigned int depth, bool first, unsigned int maxWalk)
{
    for (unsigned int i = 0; i < depth; i++)
        m_ProcTasks[i] = 0;
    m_Result = m_ProcTasks[0] = graph->GetTaskSize();

    NestLevel* t = graph->GetNext();
    for (unsigned int i = 1; i < depth; i++)
    {
        unsigned int procId = first ? t->pickRandom(m_Procs) : t->pickBestOrRandom(m_Procs);
        m_ProcIds[i] = procId;
        if ((m_ProcTasks[procId] += t->GetTaskSize()) > m_Result)
            if ((m_Result = m_ProcTasks[procId]) >= maxWalk)
                return m_Result;
        t = t->GetNext();
    }

    t = graph;
    for (unsigned int i = 1; i < depth; i++)
    {
        t->vapeFeromon(m_Cycle);
        t->assignFeromon(m_Result, m_ProcIds[i]);
        t = t->GetNext();
    }
    return m_Result;
}

Ant::~Ant()
{
    // cout << "Destroyed" << endl;
    // delete[] m_ProcTasks;
    // delete[] m_ProcIds;
}
