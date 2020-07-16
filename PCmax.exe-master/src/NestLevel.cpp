#include "NestLevel.h"

#include <iostream>
#include <stdlib.h>
#include <cmath>

#include "AntNode.h"

using namespace std;

unsigned int NestLevel::FEROMON_INTEGRITY = 977;

NestLevel::NestLevel(unsigned int verticesCount, unsigned int maxCount, unsigned int nextCount)
{
    m_VertexCount = verticesCount;
    m_FeromonTime = 0;
    m_AntiFeromon = 10000;
    if (m_TopVertex > m_VertexCount) m_TopVertex = 0;
    if (nextCount > 0)
        m_Next = new NestLevel(m_VertexCount + (m_VertexCount < maxCount ? 1 : 0), maxCount, nextCount - 1, 1);
}

NestLevel::NestLevel(unsigned int verticesCount, unsigned int maxCount, unsigned int nextCount, unsigned int lv)
{
    m_VertexCount = verticesCount;
    m_FeromonTime = 0;
    m_AntiFeromon = 10000;
    if (m_TopVertex > m_VertexCount) m_TopVertex = 0;
    if (nextCount > 0)
        m_Next = new NestLevel(m_VertexCount + (m_VertexCount < maxCount ? 1 : 0), maxCount, nextCount - 1, lv + 1);
}

unsigned int NestLevel::pickRandom( unsigned int maxId )
{
    return rand() % (maxId < m_VertexCount ? maxId : m_VertexCount);
}

// TODO solve returning best vertex for maxId < m_VertexCount
unsigned int NestLevel::pickBestOrRandom( unsigned int maxId )
{
    if (rand() % 1000 < FEROMON_INTEGRITY && m_TopVertex < maxId)
        return m_TopVertex;
    return pickRandom(maxId);
}

int NestLevel::assignFeromon(int f, unsigned int index)
{
    int antiF = f;
    if (m_AntiFeromon > antiF)
    {
        m_AntiFeromon = antiF;
        m_TopVertex = index;
    };
    return m_AntiFeromon;
};

int NestLevel::vapeFeromon(unsigned int cycle)
{
    return m_AntiFeromon -= (int)(m_FeromonTime - (m_FeromonTime = cycle));
}

NestLevel::~NestLevel()
{
    if (m_Next > 0) delete m_Next;
}

void NestLevel::test()
{
    NestLevel* lvl = new NestLevel(10, 12, 5);
    srand(123);

    cout << "Full randoms: " << endl;
    for (int n = 0; n < 5; n++)
    cout << lvl->pickRandom(100) << endl;

    cout << "Assigning" << endl;
    cout << lvl->assignFeromon(30, 3) << endl;
    cout << lvl->assignFeromon(40, 4) << endl;
    cout << lvl->assignFeromon(50, 5) << endl;

    cout << "Half randoms: " << endl;
    for (int n = 0; n < 5; n++)
    cout << lvl->pickBestOrRandom(10) << endl;

    cout << "Vaping" << endl;
    cout << lvl->vapeFeromon(20) << endl;
    cout << "Assigning 2" << endl;
    cout << lvl->assignFeromon(30, 6) << endl;
    cout << lvl->assignFeromon(40, 7) << endl;
    cout << lvl->assignFeromon(50, 8) << endl;

    cout << "Half randoms 2: " << endl;
    for (int n = 0; n < 5; n++)
    cout << lvl->pickBestOrRandom(10) << endl;

    cout << "Task set and get:" << endl;
    cout << lvl->SetTaskSize(123) << endl;
    cout << lvl->GetTaskSize() << endl;

    cout << "Next level randoms:" << endl;
    lvl = lvl->GetNext();
    for (int n = 0; n < 5; n++)
    cout << lvl->pickRandom(100) << endl;
}
