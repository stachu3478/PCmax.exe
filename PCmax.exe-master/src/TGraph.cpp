#include "TGraph.h"

#include <iostream>

using namespace std;

template <class Label>
TGraph<Label>::TGraph()
{
    // m_Size = 0;
    // m_Expanded = false;
}

template <class Label>
TGraph<Label>::TGraph(int nodes):
    m_Nodes(new TGraph[nodes]),
    m_Value()
{
    m_Size = nodes;
    m_Expanded = false;
}

template <class Label>
void TGraph<Label>::expand(int nodes)
{
    for (int n = 0; n < m_Size; n++)
    {
        cout << "Init node " << n << " of " << m_Size << " size " << nodes << endl;
        m_Nodes[n] = *(new TGraph<Label>(nodes));
    }
    m_Expanded = true;
}

template <class Label>
void TGraph<Label>::collapse()
{
    for (int n = 0; n < m_Size; n++)
    {
        cout << "Delete node " << n << " of " << m_Size << " is expanded? " << m_Nodes[n].IsExpanded() << endl;
        if (m_Nodes[n].IsExpanded()) m_Nodes[n].collapse();
    }
    delete []m_Nodes;
    m_Expanded = false;
}

template <class Label>
TGraph<Label>::~TGraph()
{
    if (m_Expanded) collapse();
}

void doNothing()
{
    TGraph<int> graph(10);
    graph.expand(5);
    TGraph<AntNode> wtf;
}
