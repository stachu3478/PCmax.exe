#ifndef ANTSOLVER_H
#define ANTSOLVER_H

#include "NestLevel.h"
#include "Ant.h"

class AntSolver
{
    public:
        /** Default constructor */
        AntSolver(char* file);
        /** Default destructor */
        virtual ~AntSolver();

    protected:

    private:
        NestLevel* m_Graph; //!< Member variable "m_Graphr"
        Ant* m_BestAnt; //!< Member variable "m_BestAnt"
        int m_LastTime; //!< Member variable "m_LastTime"
        unsigned int m_Cycle; //!< Member variable "m_Cycle"
};

#endif // ANTSOLVER_H
