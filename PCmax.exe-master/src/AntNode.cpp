#include "AntNode.h"

AntNode::AntNode()
{}

AntNode::AntNode(unsigned int procId)
{
    m_ProcessorId = procId;
    m_AntiFeromon = 0;
    m_FeromonTime = 0;
}

int AntNode::vapeFeromon(unsigned int cycle)
{
    return m_AntiFeromon -= (int)(m_FeromonTime - (m_FeromonTime = cycle));
}

AntNode::~AntNode()
{
    //dtor
}
