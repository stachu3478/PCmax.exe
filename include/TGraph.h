#ifndef TGRAPH_H
#define TGRAPH_H

#include "AntNode.h"

template <class Label>
class TGraph
{
    public:
        /** Default constructor */
        TGraph();
        TGraph(int nodes);
        /** Default destructor */
        virtual ~TGraph();

        Label& GetValue(){ return m_Value; }

        void expand(int nodes);
        void collapse();

        /** Access m_Size
         * \return The current value of m_Size
         */
         int GetSize() { return m_Size; }
         bool IsExpanded() { return m_Expanded; }
         TGraph operator[](int index) { return m_Nodes[index]; };

    protected:

    private:
         Label m_Value;
         TGraph* m_Nodes;
         int m_Size; //!< Member variable "m_Size"
         bool m_Expanded;
};

#endif // TGRAPH_H
