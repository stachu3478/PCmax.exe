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
        int assignFeromon(int f, unsigned int index);
        int vapeFeromon(unsigned int cycle);

        static unsigned int FEROMON_INTEGRITY;
    protected:

    private:
        unsigned int m_TopVertex; //!< Member variable "m_TopVertex*"
        int m_AntiFeromon;
        unsigned int m_FeromonTime;
        NestLevel* m_Next; //!< Member variable "m_next*"
        unsigned int m_Level; //!< Member variable "m_Level"
        unsigned int m_VertexCount; //!< Member variable "m_vertexCount"
};

#endif // NESTLEVEL_H
