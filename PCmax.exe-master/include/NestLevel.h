#ifndef NESTLEVEL_H
#define NESTLEVEL_H

#include "AntNode.h"

class NestLevel
{
    public:
        /** Default constructor */
        NestLevel(unsigned int verticesCount, unsigned int maxCount, unsigned int nextCount);
        NestLevel(unsigned int verticesCount, unsigned int maxCount, unsigned int nextCount, unsigned int level);
        /** Default destructor */
        virtual ~NestLevel();
        NestLevel* GetNext() { return m_Next; };
        unsigned int pickRandom( unsigned int maxId );
        unsigned int pickBestOrRandom( unsigned int maxId );
        unsigned int pickBest() { return m_TopVertex; };
        int assignFeromon(int f, unsigned int index);
        int vapeFeromon(unsigned int cycle);

        unsigned int SetTaskSize(unsigned int val) { return m_TaskSize = val; };
        unsigned int GetTaskSize() { return m_TaskSize; };

        static unsigned int FEROMON_INTEGRITY;
        static void test();
    protected:

    private:
        unsigned int m_TopVertex; //!< Member variable "m_TopVertex*"
        int m_AntiFeromon;
        unsigned int m_FeromonTime;
        NestLevel* m_Next; //!< Member variable "m_next*"
        unsigned int m_VertexCount; //!< Member variable "m_vertexCount"
        unsigned int m_TaskSize;
};

#endif // NESTLEVEL_H
