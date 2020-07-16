#ifndef ANT_H
#define ANT_H

#include "NestLevel.h"

class Ant
{
    public:
        /** Default constructor */
        Ant(unsigned int cycle, unsigned int procs, unsigned int depth);
        /** Default destructor */
        virtual ~Ant();

        unsigned int walk(NestLevel* graph, unsigned int depth, bool first, unsigned int maxWalk);
        unsigned int GetResult(){ return m_Result; };
        void reset(unsigned int cycle);

    protected:

    private:
        unsigned int* m_ProcTasks;
        unsigned int* m_ProcIds;
        unsigned int m_MaxProcId;
        unsigned int m_Cycle;
        unsigned int m_Result;
        unsigned int m_Procs;
};

#endif // ANT_H
