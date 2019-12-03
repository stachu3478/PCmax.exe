#include "NestLevel.h"

#include <stdlib.h>
#include <cmath>

#include "AntNode.h"

unsigned int NestLevel::FEROMON_INTEGRITY = 512;

NestLevel::NestLevel(unsigned int verticesCount, unsigned int maxCount, unsigned int nextCount)
{
    // m_Vertices = new AntNode[verticesCount];
    m_VertexCount = verticesCount;
    m_Level = 0;
    /* for (unsigned int i = 0; i < m_VertexCount; i++)
    {
        m_Vertices = new AntNode(i);
    } */
    m_FeromonTime = 0;
    if (m_TopVertex > m_VertexCount) m_TopVertex = 0;
    if (nextCount > 0)
        m_Next = new NestLevel(m_VertexCount + (m_VertexCount < maxCount ? 1 : 0), maxCount, nextCount - 1, 1);
}

NestLevel::NestLevel(unsigned int verticesCount, unsigned int maxCount, unsigned int nextCount, unsigned int lv)
{
    // m_Vertices = new AntNode[verticesCount];
    m_VertexCount = verticesCount;
    m_Level = lv;
    /*for (unsigned int i = 0; i < m_VertexCount; i++)
    {
        m_Vertices = new AntNode(i);
    }*/
    m_FeromonTime = 0;
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
    if (rand() % 1024 < FEROMON_INTEGRITY && m_TopVertex < maxId)
        return m_TopVertex;
    return pickRandom(maxId);
}

int NestLevel::assignFeromon(int f, unsigned int index)
{
    int antiF = -f;
    if (m_AntiFeromon < antiF)
    {
        m_AntiFeromon = -f;
        m_TopVertex = index;
    }
    return m_AntiFeromon;
};

int NestLevel::vapeFeromon(unsigned int cycle)
{
    return m_AntiFeromon -= (int)(m_FeromonTime - (m_FeromonTime = cycle));
}

NestLevel::~NestLevel()
{
    //dtor
}
